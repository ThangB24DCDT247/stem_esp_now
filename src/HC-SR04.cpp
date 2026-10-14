#include "HC-SR04.h"

HCSR04::HCSR04()
{
    trigPin = TRIG_PIN;
    echoPin = ECHO_PIN;
}

void HCSR04::begin()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float HCSR04::getDistance()
{
    digitalWrite(trigPin, LOW);
    ets_delay_us(2);
    digitalWrite(trigPin, HIGH);
    ets_delay_us(10);
    digitalWrite(trigPin, LOW);

    unsigned long duration = pulseIn(echoPin, HIGH, 20000);

    // timeout → trả giá trị cũ
    if (duration == 0)
        return lastDistance;

    float distance = (duration * 0.0343f) / 2.0f;

    // lọc giá trị rác
    if (distance < 2.0f || distance > 400.0f)
        return lastDistance;

    // cập nhật giá trị hợp lệ
    lastDistance = distance;
    return distance;
}
