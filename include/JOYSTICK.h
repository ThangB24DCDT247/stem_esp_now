#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

/* ===== PIN CONFIG ===== */
#define JOY_VRX_PIN 39
#define JOY_VRY_PIN 34
#define JOY_SW_PIN  36

/* ===== ADC CONFIG ===== */
#define ADC_MIN 0
#define ADC_MAX 4095
#define MAP_MIN 0
#define MAP_MAX 7

enum Direction {
    CENTER,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT
};

class Joystick {
public:
    Joystick();

    void begin();
    void update();

    int getX();        // 0–7
    int getY();        // 0–7
    int getRawX();     // ADC raw
    int getRawY();

    Direction getDirection();
    const char* getDirectionName();

    bool isPressed();      // trạng thái giữ
    bool wasPressed();     // sự kiện nhấn (1 lần)

private:
    int rawX;
    int rawY;
    int xValue;
    int yValue;

    bool swState;
    bool lastSwState;
    bool wasPressedFlag;

    unsigned long lastDebounceTime;
    static const unsigned long debounceDelay = 50;
};

#endif