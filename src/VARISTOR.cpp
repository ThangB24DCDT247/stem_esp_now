#include "VARISTOR.h"

Varistor::Varistor(uint8_t analogPin) : _pin(analogPin) {}

void Varistor::begin() {
    pinMode(_pin, INPUT);
}

int Varistor::readRaw() {
    return analogRead(_pin); //value: 0 - 4095
}

float Varistor::readVoltage() {
    return (analogRead(_pin) / 4095.0) * 3.3; 
}

int Varistor::readPercent() {
    return map(analogRead(_pin), 0, 4095, 0, 100);
}
float Varistor::mapToRange(float outMin, float outMax) {
    int raw = analogRead(_pin);
    float scaled = ((float)raw / 4095.0) * (outMax - outMin) + outMin;
    return scaled;
}