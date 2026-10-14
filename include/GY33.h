#ifndef GY33_H
#define GY33_H

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

enum GY33_Color
{
    COLOR_NONE = 0,
    COLOR_RED  = 2,
    COLOR_GREEN = 3,
    COLOR_BLUE = 4,
    COLOR_ORANGE = 5,
    COLOR_YELLOW = 6
};

class GY33
{
    public:
        GY33(uint8_t sda = 21, uint8_t scl = 22);
        bool begin(void);
        void readRaw(uint16_t &r, uint16_t &g, uint16_t &b, uint16_t &c);
        void readNormalized(float &r, float &g, float &b);
        GY33_Color detectColor(void);
        void debugPrint(void);

    private:
        uint8_t sda_, scl_;
        uint16_t r_, g_, b_, c_;
        Adafruit_TCS34725 tcs_;
};

#endif