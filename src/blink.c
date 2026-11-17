#include "blink.h"

#include <stdint.h>

#include "nrf_log.h"

#include "leds.h"
#include "soft_pwm.h"

static const uint8_t m_device_id[LED_COUNT] = {7, 1, 9, 8};

#define DUTY_STEP_PERIODS 5

static bool m_running;
static uint32_t m_led_idx;
static uint32_t m_blinks_done;
static int32_t m_duty;
static int32_t m_direction;
static uint32_t m_period_cnt;

void blink_init(void)
{
    m_running = false;
    m_led_idx = 0;
    m_blinks_done = 0;
    m_duty = 0;
    m_direction = +1;
    m_period_cnt = 0;

    soft_pwm_set_led(m_led_idx);
    soft_pwm_set_duty(0);
}

void blink_toggle(void)
{
    m_running = !m_running;

    if (m_running)
    {
        NRF_LOG_INFO("Blinking started (LED %d, duty %d%%)", m_led_idx, m_duty);
    }
    else
    {
        NRF_LOG_INFO("Blinking frozen (LED %d, duty %d%%)", m_led_idx, m_duty);
    }
}

bool blink_is_running(void)
{
    return m_running;
}

static void next_led_if_done(void)
{
    m_blinks_done++;

    if (m_blinks_done < m_device_id[m_led_idx])
    {
        return;
    }

    m_blinks_done = 0;
    m_led_idx = (m_led_idx + 1) % LED_COUNT;
    soft_pwm_set_led(m_led_idx);

    NRF_LOG_INFO("Next LED: %d (%d blinks)", m_led_idx, m_device_id[m_led_idx]);
}

void blink_on_pwm_period(void)
{
    if (!m_running)
    {
        return;
    }

    m_period_cnt++;
    if (m_period_cnt < DUTY_STEP_PERIODS)
    {
        return;
    }
    m_period_cnt = 0;

    m_duty += m_direction;

    if (m_duty >= 100)
    {
        m_duty = 100;
        m_direction = -1;
    }
    else if (m_duty <= 0)
    {
        m_duty = 0;
        m_direction = +1;
        next_led_if_done();
    }

    soft_pwm_set_duty((uint8_t)m_duty);
}
