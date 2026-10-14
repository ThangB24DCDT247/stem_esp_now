#include "DHT11.h"

DHT11_Sensor::DHT11_Sensor(uint8_t dhtPin, uint8_t ctrlPin, uint8_t type)
    : _ctrlPin(ctrlPin),
      _dht(dhtPin, type),
      _lastTemp(0.0f),
      _lastHumi(0.0f) 
{}

void DHT11_Sensor::begin()
{
    pinMode(_ctrlPin, OUTPUT);
    digitalWrite(_ctrlPin, HIGH);

    delay(1000); 

    _dht.begin();

    float t = _dht.readTemperature();
    float h = _dht.readHumidity();

    if (!isnan(t)) _lastTemp = t;
    if (!isnan(h)) _lastHumi = h;
}

float DHT11_Sensor::readTemp() {
    float t = _dht.readTemperature();
    if (isnan(t))
        return _lastTemp;

    if (abs(t - _lastTemp) <= 5.0f)
        _lastTemp = t;

    return _lastTemp;
}

float DHT11_Sensor::readHumi() {
    float h = _dht.readHumidity();
    if (isnan(h))
        return _lastHumi;

    if (abs(h - _lastHumi) <= 10.0f)
        _lastHumi = h;

    return _lastHumi;
}