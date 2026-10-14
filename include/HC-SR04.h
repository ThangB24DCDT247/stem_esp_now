#ifndef HC_SR04_H
#define HC_SR04_H

#include <Arduino.h>

#define TRIG_PIN 26
#define ECHO_PIN 27

class HCSR04 {
private:
    int trigPin;
    int echoPin;
    float lastDistance;   // 🔥 lưu giá trị hợp lệ gần nhất

public:
    HCSR04(void);
    void begin();
    float getDistance();
};

#endif
