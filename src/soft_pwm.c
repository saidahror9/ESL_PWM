#include "soft_pwm.h"

#include "nrfx_systick.h"

#include "leds.h"

static nrfx_systick_state_t m_period_start;
static uint32_t m_led;
static uint8_t m_duty;
static bool m_led_is_on;

void soft_pwm_init(void)
{
    nrfx_systick_init();
    nrfx_systick_get(&m_period_start);
    m_led = 0;
    m_duty = 0;
    m_led_is_on = false;
}

void soft_pwm_set_led(uint32_t led_idx)
{
    led_off(m_led);
    m_led_is_on = false;
    m_led = led_idx;
}

void soft_pwm_set_duty(uint8_t duty_percent)
{
    if (duty_percent > 100)
    {
        duty_percent = 100;
    }
    m_duty = duty_percent;
}

bool soft_pwm_process(void)
{
    if (nrfx_systick_test(&m_period_start, PWM_PERIOD_US))
    {
        nrfx_systick_get(&m_period_start);

        if (m_duty > 0)
        {
            led_on(m_led);
            m_led_is_on = true;
        }
        return true;
    }

    uint32_t t_on_us = (PWM_PERIOD_US * m_duty) / 100;

    if (m_led_is_on && m_duty < 100 && nrfx_systick_test(&m_period_start, t_on_us))
    {
        led_off(m_led);
        m_led_is_on = false;
    }

    return false;
}
