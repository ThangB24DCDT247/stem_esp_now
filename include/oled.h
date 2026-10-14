#ifndef OLED_H
#define OLED_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

/* ===== OLED CONFIG ===== */
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  64
#define OLED_RESET     -1
#define I2C_ADDRESS    0x3C

class OLED {
  public:
    static void begin();

    static void showBitmap();
    static void showText();
    static void showData(
        unsigned int pot_value,
        unsigned int distance,
        unsigned int humi,
        unsigned int temp
    );

    static void showMusic(uint8_t count_song);

  private:
    static Adafruit_SH1106G _display;
};

#endif
