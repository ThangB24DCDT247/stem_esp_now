#include "JOYSTICK.h"

Joystick::Joystick()
    : rawX(0), rawY(0),
      xValue(0), yValue(0),
      swState(false), lastSwState(false),
      wasPressedFlag(false),
      lastDebounceTime(0)
{
}

void Joystick::begin()
{
    pinMode(JOY_SW_PIN, INPUT_PULLUP);
}

void Joystick::update()
{
    rawX = analogRead(JOY_VRX_PIN);
    rawY = analogRead(JOY_VRY_PIN);

    xValue = map(rawX, ADC_MIN, ADC_MAX, MAP_MIN, MAP_MAX);
    yValue = map(rawY, ADC_MIN, ADC_MAX, MAP_MIN, MAP_MAX);

    bool reading = (digitalRead(JOY_SW_PIN) == LOW);

    if (reading != lastSwState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != swState) {
            swState = reading;
            if (swState) {
                wasPressedFlag = true;
            }
        }
    }

    lastSwState = reading;
}

int Joystick::getX() { return xValue; }
int Joystick::getY() { return yValue; }
int Joystick::getRawX() { return rawX; }
int Joystick::getRawY() { return rawY; }

Direction Joystick::getDirection()
{
    if ((xValue >= 3 && xValue <= 4) && (yValue >= 3 && yValue <= 4)) return CENTER;

    if (xValue <= 2 && yValue <= 2) return UP_RIGHT;
    if (xValue >= 5 && yValue <= 2) return UP_LEFT;
    if (xValue <= 2 && yValue >= 5) return DOWN_RIGHT;
    if (xValue >= 5 && yValue >= 5) return DOWN_LEFT;

    if (yValue <= 2) return UP;
    if (yValue >= 5) return DOWN;
    if (xValue <= 2) return RIGHT;
    if (xValue >= 5) return LEFT;

    return CENTER;
}

const char* Joystick::getDirectionName()
{
    switch (getDirection()) {
        case UP: return "UP";
        case DOWN: return "DOWN";
        case LEFT: return "LEFT";
        case RIGHT: return "RIGHT";
        case UP_LEFT: return "UP_LEFT";
        case UP_RIGHT: return "UP_RIGHT";
        case DOWN_LEFT: return "DOWN_LEFT";
        case DOWN_RIGHT: return "DOWN_RIGHT";
        default: return "CENTER";
    }
}

bool Joystick::isPressed()
{
    return swState;
}

bool Joystick::wasPressed()
{
    if (wasPressedFlag) {
        wasPressedFlag = false;
        return true;
    }
    return false;
}