#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

#include "nrf_gpio.h"

#define LED1_G NRF_GPIO_PIN_MAP(0, 6)
#define LED2_R NRF_GPIO_PIN_MAP(0, 8)
#define LED2_G NRF_GPIO_PIN_MAP(1, 9)
#define LED2_B NRF_GPIO_PIN_MAP(0, 12)

#define LED_COUNT 4

void leds_init(void);
void led_on(uint32_t led_idx);
void led_off(uint32_t led_idx);

#endif
