#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "GY33.h"
#include "RGB_Led.h"
#include "HC-SR04.h"
#include "Relay.h"
#include "DF_Player.h"
#include "DHT11.h"
#include "VARISTOR.h"
#include "JOYSTICK.h"
#include "MOTOR.h"
#include "oled.h"

// Obj
GY33 gy33;
RGB rgb_led;
HCSR04 hc_sr04;
Relay relay;
DFPlayer loa;
DHT11_Sensor dht_sensor;
Varistor pot(VARISTOR_PIN);
Joystick joy;
Motor fan;
OLED screen;

// Variable
uint8_t flag_color = 0;
float distance = 0.0f;
float humi = 0.0f, temp = 0.0f;
float volt = 0.0f;

// Cấu trúc gói tin từ bên gửi
struct __attribute__((packed)) SpellEspNowPacket {
  uint8_t magic[2];      // 'S', 'P'
  uint8_t spell_index;   // số thứ tự spell
  char spell_name[16];   // tên spell
  uint8_t confidence;    // độ tin cậy 0-100%
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

// Queue nhận dữ liệu ESP-NOW
QueueHandle_t espNowQueue = NULL;

// Callback khi nhận dữ liệu qua ESP-NOW
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{
  if (len > 0)
  {
    SpellEspNowPacket rx_packet;
    memset(&rx_packet, 0, sizeof(rx_packet));

    // Nếu nhận được trọn vẹn gói tin SpellEspNowPacket
    if (len >= sizeof(SpellEspNowPacket))
    {
      memcpy(&rx_packet, incomingData, sizeof(SpellEspNowPacket));
    }
    else
    {
      // Nếu gói tin chỉ gửi 1 byte đơn lẻ
      rx_packet.spell_index = incomingData[0];
    }

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xQueueSendFromISR(espNowQueue, &rx_packet, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken)
    {
      portYIELD_FROM_ISR();
    }
  }
}

// ========================= TASK ESP-NOW =========================
void resetToNormal()
{
  relay.off();
  fan.stop();
  loa.stop();
  rgb_led.rainbowStatic();
}

void ESPNow_Task(void *pvParameters)
{
  SpellEspNowPacket packet;
  bool isActionActive = false;

  while (1)
  {
    // Nếu đang có case chạy: chờ case mới tối đa 2000ms (2 giây)
    // Nếu chưa có case nào chạy: chờ vô hạn đến khi có case mới (portMAX_DELAY)
    TickType_t waitTicks = isActionActive ? pdMS_TO_TICKS(2000) : portMAX_DELAY;

    // Đợi nhận lệnh từ Queue
    if (xQueueReceive(espNowQueue, &packet, waitTicks) == pdTRUE)
    {
      // Có case mới nhảy vào (kể cả khi đang chạy case cũ) -> Ưu tiên chạy case mới ngay!
      if (packet.magic[0] == 'S' && packet.magic[1] == 'P')
      {
        char spellName[17] = {0};
        memcpy(spellName, packet.spell_name, 16);
        Serial.printf("[ESP-NOW] Nhan case moi: Index=%d | Name=%s | Conf=%d%% | RGB=(%d, %d, %d)\n",
                      packet.spell_index, spellName, packet.confidence, packet.r, packet.g, packet.b);
      }
      else
      {
        Serial.print("[ESP-NOW] Nhan du lieu moi: ");
        Serial.println(packet.spell_index);
      }

      // Hỗ trợ cả định dạng số (1-5, 23-27) lẫn ký tự ASCII ('1'-'5')
      uint8_t caseNum = packet.spell_index;
      if (packet.spell_index >= '1' && packet.spell_index <= '5')
      {
        caseNum = packet.spell_index - '0';
      }

      // Tắt trạng thái cũ trước khi chuyển sang case mới (để tránh xung đột quạt/relay/nhạc)
      relay.off();
      fan.stop();
      loa.stop();

      switch (caseNum)
      {
        case 23:
          Serial.println(" -> Case 1 (23): Bat Relay, Phat nhac bai 1 & Den LED Do");
          relay.on();
          loa.play(1);
          rgb_led.set(COLOR_RED);
          isActionActive = true;
          break;

        case 24:
          Serial.println(" -> Case 2 (24): Tat Relay, Tat nhac & Den LED Xanh la");
          relay.off();
          loa.stop();
          rgb_led.set(COLOR_GREEN);
          isActionActive = true;
          break;

        case 25:
          Serial.println(" -> Case 3 (25): Bat quat QUAY THUAN & Den LED Xanh duong");
          fan.forward(200);
          rgb_led.set(COLOR_BLUE);
          isActionActive = true;
          break;

        case 26:
          Serial.println(" -> Case 4 (26): Bat quat QUAY NGUOC & Den LED Vang");
          fan.backward(200);
          rgb_led.set(COLOR_YELLOW);
          isActionActive = true;
          break;

        case 27:
          Serial.println(" -> Case 5 (27): Dung quat & Hieu ung LED Cau vong");
          fan.stop();
          rgb_led.rainbowStatic();
          isActionActive = true;
          break;

        default:
          Serial.print(" -> Case khong hop le: ");
          Serial.println(packet.spell_index);
          resetToNormal();
          isActionActive = false;
          break;
      }
    }
    else
    {
      // Không có case nào nhảy vào trong vòng 2 giây -> Hết 2s thì tự động trở về ban đầu
      if (isActionActive)
      {
        Serial.println("[ESP-NOW] Khong co case moi -> Het 2s tro ve trang thai ban dau");
        resetToNormal();
        isActionActive = false;
      }
    }
  }
}

// ========================= TASK ĐỌC CẢM BIẾN MÀU =========================
void TCS_Read_Task(void *pvParameters)
{
  while (1)
  {
    flag_color = gy33.detectColor();
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// ========================= TASK HIỂN THỊ RGB =========================
void RGB_Task(void *pvParameters)
{
  static uint8_t last_color = 255;

  while (1)
  {
    if (flag_color != last_color)
    {
      if (flag_color != COLOR_NONE)
      {
        rgb_led.set(flag_color);
        loa.play(flag_color);   // chỉ play khi đổi màu
      }
      else
      {
        rgb_led.rainbowStatic();
        loa.stop();             // không phát khi NONE
      }

      last_color = flag_color;
    }
    vTaskDelay(pdMS_TO_TICKS(150));
  }
}

void HCSR04_Task(void *pvParameters)
{
  while (1)
  {
    distance = hc_sr04.getDistance();

    if(distance > 0 && distance < 30)
    {
      relay.on();
    }
    else
    {
      relay.off();
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void Joystick_Task(void *pvParameters)
{
  Direction lastDir = CENTER;
  const uint8_t FAN_SPEED = 200; // tốc độ quạt
  static bool isPlaying = false; // trạng thái nhạc

  while (1)
  {
    joy.update();
    Direction dir = joy.getDirection();

    // ===== Điều khiển quạt theo hướng =====
    if (dir != lastDir)
    {
      Serial.printf("Joystick dir: %s (Raw X: %d, Y: %d)\n", joy.getDirectionName(), joy.getRawX(), joy.getRawY());

      switch (dir)
      {
        case UP:
        case UP_LEFT:
        case UP_RIGHT:
        case LEFT:
          fan.forward(FAN_SPEED);
          Serial.println("Fan FORWARD");
          break;

        case DOWN:
        case DOWN_LEFT:
        case DOWN_RIGHT:
        case RIGHT:
          fan.backward(FAN_SPEED);
          Serial.println("Fan BACKWARD");
          break;

        default:
          fan.stop();
          Serial.println("Fan STOP");
          break;
      }

      lastDir = dir;
    }

    // ===== Nhấn nút joystick -> PLAY / STOP =====
    if (joy.wasPressed())
    {
      if (!isPlaying)
      {
        Serial.println("Joystick PRESSED -> PLAY song 1");
        loa.play(1);
        isPlaying = true;
      }
      else
      {
        Serial.println("Joystick PRESSED -> STOP music");
        loa.stop();
        isPlaying = false;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(120));
  }
}

void setup()
{
  Serial.begin(115200);

  // ===== KHỞI TẠO WIFI & ESP-NOW =====
  WiFi.mode(WIFI_STA);
  Serial.print("ESP32 MAC Address: ");
  Serial.println(WiFi.macAddress());

  // Tạo Queue cho ESP-NOW (chứa tối đa 10 gói tin SpellEspNowPacket)
  espNowQueue = xQueueCreate(10, sizeof(SpellEspNowPacket));

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Loi khoi tao ESP-NOW!");
  }
  else
  {
    Serial.println("Khoi tao ESP-NOW thanh cong!");
    esp_now_register_recv_cb(OnDataRecv);
  }

  gy33.begin();
  rgb_led.begin();
  hc_sr04.begin();
  relay.begin();
  loa.begin();
  dht_sensor.begin();
  pot.begin();
  joy.begin();
  fan.begin();
  screen.begin();

  xTaskCreate(TCS_Read_Task, "TCS-34725", 2048, NULL, 1, NULL);
  xTaskCreate(RGB_Task, "RGB", 2048, NULL, 1, NULL);
  xTaskCreate(HCSR04_Task, "HC_SR04", 2048, NULL, 3, NULL);
  xTaskCreate(Joystick_Task, "JOYSTICK", 2048, NULL, 2, NULL);
  xTaskCreate(ESPNow_Task, "ESP_NOW", 2048, NULL, 2, NULL);
}

void loop()

{
  humi = dht_sensor.readHumi();
  temp = dht_sensor.readTemp();
  volt = pot.readRaw();
  screen.showData((unsigned int)volt, (unsigned int)distance, (unsigned int)humi, (unsigned int)temp);
  delay(500);
}

