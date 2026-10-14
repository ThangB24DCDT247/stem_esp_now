#include "oled.h"

// Bitmap 32x32 (Logo)
const unsigned char logo_40x40[] PROGMEM = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80,
    0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x0f, 0xf0, 0x01, 0x80, 0x00,
    0x1c, 0xf0, 0x01, 0x80, 0x00, 0x70, 0x38, 0x01, 0x80, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x01, 0x80,
    0x18, 0x01, 0x80, 0x01, 0x00, 0x18, 0x01, 0x80, 0x02, 0x00, 0x18, 0x01, 0x80, 0x06, 0x00, 0x18,
    0x01, 0x80, 0x04, 0x00, 0x10, 0x01, 0x80, 0x0c, 0x00, 0x10, 0x01, 0x80, 0x08, 0x00, 0x10, 0x01,
    0x80, 0x18, 0x00, 0x40, 0x01, 0x80, 0x18, 0x00, 0x80, 0x01, 0x80, 0x37, 0xbd, 0xfe, 0x01, 0x80,
    0x36, 0xd9, 0x88, 0x01, 0x80, 0x36, 0xdb, 0x88, 0x01, 0x80, 0x37, 0x99, 0x88, 0x01, 0x80, 0x76,
    0x1b, 0x88, 0x01, 0x80, 0x76, 0x1f, 0x88, 0x01, 0x80, 0x70, 0x0e, 0x00, 0x01, 0x80, 0x30, 0x1c,
    0x00, 0x01, 0x80, 0x38, 0x38, 0x00, 0x01, 0x80, 0x1c, 0xf0, 0x00, 0x01, 0x80, 0x1f, 0xe0, 0x00,
    0x01, 0x80, 0x0f, 0x80, 0x00, 0x01, 0x80, 0x7f, 0xff, 0xfe, 0x01, 0x80, 0xff, 0xff, 0xfe, 0x01,
    0x80, 0x7f, 0xff, 0xfe, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80,
    0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00,
    0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff};
const uint8_t temp_logo_16x16[] PROGMEM = {
    0b00001100, 0b00000000,
    0b00010010, 0b00000000,
    0b00010010, 0b00000000,
    0b00010010, 0b00000000,
    0b00010010, 0b00000000,
    0b00010010, 0b00000000,
    0b00010010, 0b00000000,
    0b00010010, 0b00000000,
    0b00010010, 0b00000000,
    0b00010010, 0b00000000,
    0b00010010, 0b00000000,
    0b00010010, 0b00000000,
    0b00011110, 0b00000000,
    0b00001100, 0b00000000,
    0b00001100, 0b00000000,
    0b00001100, 0b00000000};
const uint8_t humi_logo_16x16[] PROGMEM = {
    0b00000010, 0b00000000,
    0b00000111, 0b00000000,
    0b00001111, 0b10000000,
    0b00001111, 0b10000000,
    0b00011111, 0b11000000,
    0b00011111, 0b11000000,
    0b00111111, 0b11100000,
    0b00111111, 0b11100000,
    0b00111111, 0b11100000,
    0b00111111, 0b11100000,
    0b00111111, 0b11100000,
    0b00011111, 0b11000000,
    0b00011111, 0b11000000,
    0b00001111, 0b10000000,
    0b00000111, 0b00000000,
    0b00000010, 0b00000000};
const uint8_t refresh_icon_16x16[] PROGMEM = {
    0x00, 0x00, 0x00, 0xC0, 0x07, 0xF0, 0x1C, 0xC0,
    0x30, 0x04, 0x20, 0x04, 0x60, 0x06, 0x60, 0x06,
    0x60, 0x06, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C,
    0x01, 0x18, 0x07, 0xF0, 0x03, 0x00, 0x01, 0x00};
const uint8_t arrow_right_bitmap[] = {
    0b00000000, 0b00000000, // Hàng 1
    0b00000000, 0b00000000, // Hàng 2
    0b00000000, 0b00000000, // Hàng 3
    0b00000000, 0b00000000, // Hàng 4
    0b00011111, 0b11100000, // Hàng 5
    0b00011111, 0b11110000, // Hàng 6
    0b11111111, 0b11111111, // Hàng 7
    0b11111111, 0b11111111, // Hàng 8
    0b00011111, 0b11110000, // Hàng 9
    0b00011111, 0b11100000, // Hàng 10
    0b00000000, 0b00000000, // Hàng 11
    0b00000000, 0b00000000, // Hàng 12
    0b00000000, 0b00000000, // Hàng 13
    0b00000000, 0b00000000, // Hàng 14
    0b00000000, 0b00000000, // Hàng 15
    0b00000000, 0b00000000  // Hàng 16
};

const uint8_t music_note_bitmap[] = {
    0b00000000, 0b00000000, // Hàng 1
    0b00000000, 0b00000000, // Hàng 2
    0b00000000, 0b01100000, // Hàng 3
    0b00000000, 0b11110000, // Hàng 4
    0b00000000, 0b11110000, // Hàng 5
    0b00000000, 0b11110000, // Hàng 6
    0b00000000, 0b11110000, // Hàng 7
    0b00001111, 0b11110000, // Hàng 8
    0b00011111, 0b11100000, // Hàng 9
    0b00011111, 0b11100000, // Hàng 10
    0b00001111, 0b11100000, // Hàng 11
    0b00000000, 0b00000000, // Hàng 12
    0b00000000, 0b00000000, // Hàng 13
    0b00000000, 0b00000000, // Hàng 14
    0b00000000, 0b00000000, // Hàng 15
    0b00000000, 0b00000000  // Hàng 16
};
const unsigned char logo_distance[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x40, 0x0e, 0x00, 0x00, 0x60, 0x1e, 0x00, 0x00, 0x70, 0x3f, 0xff, 0xff, 0xf8,
    0x3f, 0xff, 0xff, 0xf8, 0x0e, 0x00, 0x00, 0x70, 0x06, 0x00, 0x00, 0x60, 0x06, 0x00, 0x00, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};

Adafruit_SH1106G OLED::_display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET);

void OLED::begin()
{
  _display.begin(I2C_ADDRESS, true);
  _display.clearDisplay();
  _display.display();
}

void OLED::showBitmap()
{
  _display.clearDisplay();
  _display.drawBitmap(
      (SCREEN_WIDTH - 40) / 2,
      (SCREEN_HEIGHT - 40) / 2,
      logo_40x40,
      40,
      40,
      SH110X_WHITE);
  _display.display();
}

void OLED::showText()
{
  _display.clearDisplay();
  _display.setCursor(15, 0);
  _display.setTextSize(1);
  _display.setTextColor(SH110X_WHITE);
  _display.write("STEM - PTIT");
  _display.display();
}

void OLED::showData(
    unsigned int pot_value,
    unsigned int distance,
    unsigned int humi,
    unsigned int temp)
{
  _display.clearDisplay();

  _display.drawBitmap(46, 18, logo_40x40, 40, 40, SH110X_WHITE);

  _display.setCursor(36, 0);
  _display.setTextSize(1);
  _display.setTextColor(SH110X_WHITE);
  _display.write("STEM - PTIT");

  // TEMP
  _display.drawBitmap(0, 15, temp_logo_16x16, 16, 16, SH110X_WHITE);
  _display.setCursor(14, 15);
  _display.print("Temp");
  _display.setCursor(16, 25);
  _display.print(temp);
  _display.write(248);
  _display.println("C");

  // HUMI
  _display.drawBitmap(0, 42, humi_logo_16x16, 16, 16, SH110X_WHITE);
  _display.setCursor(14, 45);
  _display.print("Humi");
  _display.setCursor(16, 55);
  _display.print(humi);
  _display.print(" %");

  // DISTANCE
  _display.drawBitmap(90, 7, logo_distance, 32, 25, SH110X_WHITE);
  _display.setCursor(98, 25);
  _display.print(distance);

  // POT
  _display.drawBitmap(98, 38, refresh_icon_16x16, 16, 16, SH110X_WHITE);
  _display.setCursor(95, 57);
  _display.print(pot_value);

  _display.display();
}

void OLED::showMusic(uint8_t count_song)
{
  _display.clearDisplay();
  _display.setCursor(15, 0);
  _display.setTextSize(1);
  _display.setTextColor(SH110X_WHITE);
  _display.write("EMBEDDED AIOT LAB");

  _display.drawBitmap(98, 50, music_note_bitmap, 16, 16, SH110X_WHITE);
  _display.drawBitmap(115, 45, music_note_bitmap, 16, 16, SH110X_WHITE);

  _display.setCursor(30, 18);
  _display.write("Mario Song");
  _display.setCursor(35, 31);
  _display.write("QUOC CA!!");
  _display.setCursor(30, 44);
  _display.write("__NOKIA__");

  if (count_song == 1)
    _display.drawBitmap(0, 15, arrow_right_bitmap, 16, 16, SH110X_WHITE);
  else if (count_song == 2)
    _display.drawBitmap(0, 25, arrow_right_bitmap, 16, 16, SH110X_WHITE);
  else if (count_song == 3)
    _display.drawBitmap(0, 40, arrow_right_bitmap, 16, 16, SH110X_WHITE);

  _display.display();
}