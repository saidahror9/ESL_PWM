#ifndef SOFT_PWM_H
#define SOFT_PWM_H

#include <stdbool.h>
#include <stdint.h>

#define PWM_FREQUENCY_HZ 1000
#define PWM_PERIOD_US    (1000000 / PWM_FREQUENCY_HZ)

void soft_pwm_init(void);

void soft_pwm_set_led(uint32_t led_idx);

void soft_pwm_set_duty(uint8_t duty_percent);

bool soft_pwm_process(void);

#endif
