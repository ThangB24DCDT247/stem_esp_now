#include "GY33.h"

GY33::GY33(uint8_t sda, uint8_t scl)
    : sda_(sda),
      scl_(scl),
      tcs_(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X)
{
    r_ = g_ = b_ = c_ = 0;
}

bool GY33::begin(void)
{
    Wire.begin(sda_, scl_);

    uint32_t t0 = millis();
    while (!tcs_.begin())
    {
        if (millis() - t0 > 3000)
            return false;
    }
    return true;
}

void GY33::readRaw(uint16_t &r, uint16_t &g, uint16_t &b, uint16_t &c)
{
    tcs_.getRawData(&r_, &g_, &b_, &c_);
    r = r_;
    g = g_;
    b = b_;
    c = c_;
}

void GY33::readNormalized(float &r, float &g, float &b)
{
    tcs_.getRawData(&r_, &g_, &b_, &c_);

    if (c_ == 0)
    {
        r = g = b = 0;
        return;
    }

    r = (float)r_ / c_;
    g = (float)g_ / c_;
    b = (float)b_ / c_;
    // Serial.printf("R: %f, G: %f, B: %f\n", r, g, b);
}

GY33_Color GY33::detectColor(void)
{
    float r, g, b;
    readNormalized(r, g, b);

    if (r > 0.45 && g < 0.27 && b < 0.25)
        return COLOR_RED;

    if (g > 0.45 && r < 0.35 && b < 0.35)
        return COLOR_GREEN;

    if (b > 0.45 && r < 0.35 && g < 0.35)
        return COLOR_BLUE;

    if (r > 0.45 && g > 0.25 && g < 0.3 && b < 0.2)
        return COLOR_ORANGE;

    if (r > 0.35 && r < 0.41 && g > 0.35 && r > 0.13 && r < 2)
        return COLOR_YELLOW;

    return COLOR_NONE;
}

void GY33::debugPrint(void)
{
    tcs_.getRawData(&r_, &g_, &b_, &c_);
    Serial.printf("R:%d G:%d B:%d C:%d\n", r_, g_, b_, c_);
}