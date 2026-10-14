#include "Relay.h"

bool Relay::_state = false;

void Relay::begin()
{
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, RELAY_OFF_LEVEL);
    _state = false;
}

void Relay::on()
{
    _state = true;
    digitalWrite(RELAY_PIN, RELAY_ON_LEVEL);
}

void Relay::off()
{
    _state = false;
    digitalWrite(RELAY_PIN, RELAY_OFF_LEVEL);
}

void Relay::toggle()
{
    _state = !_state;
    digitalWrite(RELAY_PIN, _state ? RELAY_ON_LEVEL : RELAY_OFF_LEVEL);
}

bool Relay::state()
{
    return _state;
}
