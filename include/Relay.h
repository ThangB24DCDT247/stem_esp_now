#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>

/* ===== PIN DEFINE ===== */
#define RELAY_PIN        4

/* ===== RELAY LOGIC ===== */
#define RELAY_ON_LEVEL   HIGH
#define RELAY_OFF_LEVEL  LOW

class Relay {
  public:
    static void begin();
    static void on();
    static void off();
    static void toggle();
    static bool state();

  private:
    static bool _state;
};

#endif
