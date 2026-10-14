#include "RGB_Led.h"

/* ===== STRIP OBJECT ===== */
Adafruit_NeoPixel RGB::_strip(
    RGB_LED_COUNT,
    RGB_LED_PIN,
    NEO_GRB + NEO_KHZ800
);

void RGB::begin()
{
    _strip.begin();
    _strip.setBrightness(RGB_BRIGHTNESS);
    _strip.show();   // clear all
}

void RGB::set(uint8_t color_type)
{
    uint32_t color;

    switch (color_type)
    {
        case 2: color = _strip.Color(255,   0,   0); break; // Red
        case 3: color = _strip.Color(  0, 255,   0); break; // Green
        case 4: color = _strip.Color(  0,   0, 255); break; // Blue
        case 5: color = _strip.Color(255,  80,  20); break; // Orange
        case 6: color = _strip.Color(255, 185,   0); break; // Yellow
        default:
            rainbowStatic();
            return;
    }

    for (uint16_t i = 0; i < _strip.numPixels(); i++) {
        _strip.setPixelColor(i, color);
    }
    _strip.show();
}

void RGB::rainbowStatic()
{
    for (uint16_t i = 0; i < _strip.numPixels(); i++)
        _strip.setPixelColor(
            i,
            wheel((i * 256 / _strip.numPixels()) & 255)
        );

    _strip.show();
}

void RGB::rainbow()
{
    for (uint16_t j = 0; j < 256 * 5; j++)
    {
        for (uint16_t i = 0; i < _strip.numPixels(); i++)
        {
            _strip.setPixelColor(
                i,
                wheel(((i * 256 / _strip.numPixels()) + j) & 255)
            );
        }
        _strip.show();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

uint32_t RGB::wheel(byte pos)
{
    pos = 255 - pos;
    if (pos < 85)
        return _strip.Color(255 - pos * 3, 0, pos * 3);
    if (pos < 170)
    {
        pos -= 85;
        return _strip.Color(0, pos * 3, 255 - pos * 3);
    }
    pos -= 170;
    return _strip.Color(pos * 3, 255 - pos * 3, 0);
}
