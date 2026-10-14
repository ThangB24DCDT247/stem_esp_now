#ifndef DFPLAYER_H
#define DFPLAYER_H

#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>

/* ===== DEFAULT CONFIG ===== */
#define DFPLAYER_UART_NUM   2
#define DFPLAYER_RX_PIN     16
#define DFPLAYER_TX_PIN     17
#define DFPLAYER_BAUDRATE   9600
#define DFPLAYER_VOLUME     25 

class DFPlayer {
  public:
    static void begin(
        uint8_t rxPin  = DFPLAYER_RX_PIN,
        uint8_t txPin  = DFPLAYER_TX_PIN,
        uint32_t baud  = DFPLAYER_BAUDRATE
    );

    static void play(uint16_t song);
    static void stop();
    static void volume(uint8_t vol);

  private:
    static HardwareSerial* _serial;
    static DFRobotDFPlayerMini _player;
};

#endif
