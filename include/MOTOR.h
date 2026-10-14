#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

/* ====== PIN DEFINE ====== */
#define MOTOR_B1_PIN    23
#define MOTOR_B2_PIN    19
#define MOTOR_FAULT_PIN 18

/* ====== PWM CONFIG ====== */
#define MOTOR_PWM_FREQ  20000
#define MOTOR_PWM_RES   8      // 0–255
#define MOTOR_PWM_CH1   0
#define MOTOR_PWM_CH2   1

class Motor {
  public:
    static void begin();
    static void forward(uint32_t speed);   // 0-255
    static void backward(uint32_t speed);
    static void stop();
};

#endif
