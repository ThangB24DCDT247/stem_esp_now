#ifndef RGB_LED_H
#define RGB_LED_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

/* ===== LED CONFIG ===== */
#define RGB_LED_PIN     15
#define RGB_LED_COUNT   15
#define RGB_BRIGHTNESS  50


class RGB {
  public:
    static void begin();
    static void set(uint8_t color_type);
    static void rainbow();
    static void rainbowStatic();
    static uint32_t wheel(byte pos);

  private:
    static Adafruit_NeoPixel _strip;
};

#endif
