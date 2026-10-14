#ifndef VARISTOR_H
#define VARISTOR_H

#include <Arduino.h>

#define VARISTOR_PIN 35

class Varistor {
    public:
        Varistor(uint8_t analogPin);
        void begin();
        int readRaw();           // 0 - 4095
        float readVoltage();     // 0.0 - 3.3V
        int readPercent();       // 0 - 100%
        float mapToRange(float outMin, float outMax);

    private:
        uint8_t _pin;
};

#endif