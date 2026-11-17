#include <stdbool.h>
#include <stdint.h>

#include "app_error.h"
#include "app_timer.h"
#include "nrf_drv_clock.h"
#include "nrf_log.h"

#include "blink.h"
#include "button.h"
#include "leds.h"
#include "logs.h"
#include "soft_pwm.h"

static void lfclk_init(void)
{
    if (!nrf_drv_clock_init_check())
    {
        ret_code_t err = nrf_drv_clock_init();
        APP_ERROR_CHECK(err);
    }

    nrf_drv_clock_lfclk_request(NULL);
    while (!nrf_drv_clock_lfclk_is_running())
    {
    }
}

int main(void)
{
    lfclk_init();
    logs_init();

    ret_code_t err = app_timer_init();
    APP_ERROR_CHECK(err);

    leds_init();
    soft_pwm_init();
    blink_init();
    button_init();

    NRF_LOG_INFO("ESL_PWM started. Double click to start/freeze blinking.");

    while (true)
    {
        if (soft_pwm_process())
        {
            blink_on_pwm_period();
        }

        if (button_double_click_happened())
        {
            blink_toggle();
        }

        logs_process();
    }
}
