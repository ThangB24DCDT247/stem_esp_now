#ifndef DHT11_H
#define DHT11_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

class DHT11_Sensor {
public:
    DHT11_Sensor(uint8_t pin = 32, uint8_t ctrlPin = 33, uint8_t type = DHT11);

    void begin();
    float readTemp();
    float readHumi();

private:
    DHT _dht;
    uint8_t _ctrlPin;
    float _lastTemp;
    float _lastHumi;
};

#endif