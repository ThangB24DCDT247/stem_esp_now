#include "MOTOR.h"

void Motor::begin()
{
    pinMode(MOTOR_FAULT_PIN, INPUT_PULLUP);

    ledcSetup(MOTOR_PWM_CH1, MOTOR_PWM_FREQ, MOTOR_PWM_RES);
    ledcSetup(MOTOR_PWM_CH2, MOTOR_PWM_FREQ, MOTOR_PWM_RES);

    ledcAttachPin(MOTOR_B1_PIN, MOTOR_PWM_CH1);
    ledcAttachPin(MOTOR_B2_PIN, MOTOR_PWM_CH2);

    stop();
}

void Motor::forward(uint32_t speed)
{
    ledcWrite(MOTOR_PWM_CH1, speed);
    ledcWrite(MOTOR_PWM_CH2, 0);
}

void Motor::backward(uint32_t speed)
{
    ledcWrite(MOTOR_PWM_CH1, 0);
    ledcWrite(MOTOR_PWM_CH2, speed);
}

void Motor::stop()
{
    ledcWrite(MOTOR_PWM_CH1, 0);
    ledcWrite(MOTOR_PWM_CH2, 0);
}