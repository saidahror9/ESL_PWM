#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

#include "nrf_gpio.h"

#define BUTTON_1             NRF_GPIO_PIN_MAP(1, 6)
#define BUTTON_PRESSED_LEVEL 0

#define BUTTON_DEBOUNCE_MS     50
#define BUTTON_DOUBLE_CLICK_MS 400

void button_init(void);

bool button_double_click_happened(void);

#endif
