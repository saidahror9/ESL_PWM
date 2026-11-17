#include "leds.h"

static const uint32_t m_leds[LED_COUNT] = {LED1_G, LED2_R, LED2_G, LED2_B};

void leds_init(void)
{
    for (uint32_t i = 0; i < LED_COUNT; i++)
    {
        nrf_gpio_cfg_output(m_leds[i]);
        led_off(i);
    }
}

void led_on(uint32_t led_idx)
{
    nrf_gpio_pin_write(m_leds[led_idx], 0);
}

void led_off(uint32_t led_idx)
{
    nrf_gpio_pin_write(m_leds[led_idx], 1);
}
