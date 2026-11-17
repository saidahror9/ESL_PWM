#include "button.h"

#include <stdint.h>

#include "app_error.h"
#include "app_timer.h"
#include "nrf_log.h"
#include "nrfx_gpiote.h"

APP_TIMER_DEF(m_debounce_timer);
APP_TIMER_DEF(m_double_click_timer);

static volatile bool m_is_pressed;
static volatile uint32_t m_click_cnt;
static volatile bool m_double_click_flag;

static void button_gpiote_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    ret_code_t err = app_timer_start(m_debounce_timer, APP_TIMER_TICKS(BUTTON_DEBOUNCE_MS), NULL);
    APP_ERROR_CHECK(err);
}

static void on_click(void)
{
    m_click_cnt++;

    if (m_click_cnt == 1)
    {
        ret_code_t err = app_timer_start(m_double_click_timer, APP_TIMER_TICKS(BUTTON_DOUBLE_CLICK_MS), NULL);
        APP_ERROR_CHECK(err);
    }
    else
    {
        app_timer_stop(m_double_click_timer);
        m_click_cnt = 0;
        m_double_click_flag = true;
        NRF_LOG_INFO("Double click");
    }
}

static void debounce_timer_handler(void * p_context)
{
    bool pressed_now = (nrf_gpio_pin_read(BUTTON_1) == BUTTON_PRESSED_LEVEL);

    if (pressed_now && !m_is_pressed)
    {
        on_click();
    }

    m_is_pressed = pressed_now;
}

static void double_click_timer_handler(void * p_context)
{
    m_click_cnt = 0;
}

void button_init(void)
{
    ret_code_t err;

    err = app_timer_create(&m_debounce_timer, APP_TIMER_MODE_SINGLE_SHOT, debounce_timer_handler);
    APP_ERROR_CHECK(err);

    err = app_timer_create(&m_double_click_timer, APP_TIMER_MODE_SINGLE_SHOT, double_click_timer_handler);
    APP_ERROR_CHECK(err);

    if (!nrfx_gpiote_is_init())
    {
        err = nrfx_gpiote_init();
        APP_ERROR_CHECK(err);
    }

    nrfx_gpiote_in_config_t cfg = NRFX_GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    cfg.pull = NRF_GPIO_PIN_PULLUP;

    err = nrfx_gpiote_in_init(BUTTON_1, &cfg, button_gpiote_handler);
    APP_ERROR_CHECK(err);

    nrfx_gpiote_in_event_enable(BUTTON_1, true);

    m_is_pressed = (nrf_gpio_pin_read(BUTTON_1) == BUTTON_PRESSED_LEVEL);
    m_click_cnt = 0;
    m_double_click_flag = false;
}

bool button_double_click_happened(void)
{
    if (m_double_click_flag)
    {
        m_double_click_flag = false;
        return true;
    }
    return false;
}
