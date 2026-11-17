#ifndef BLINK_H
#define BLINK_H

#include <stdbool.h>

void blink_init(void);

void blink_toggle(void);

bool blink_is_running(void);

void blink_on_pwm_period(void);

#endif
