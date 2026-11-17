# ESL_PWM

ESTC workshop: software PWM, GPIOTE, double click, USB logs. Board: nRF52840 dongle (pca10059), device ID #7198.

## What it does

- LEDs blink in the same order as in ESL_GPIO: LED1_G ×7, LED2_R ×1, LED2_G ×9, LED2_B ×8.
- Every blink is smooth: duty cycle 0% → 100% → 0% (1 s per blink).
- PWM frequency: 1 kHz (software PWM on SysTick).
- Double click: start blinking / freeze it (LED keeps the current duty cycle).
- Logs over USB: `picocom /dev/ttyACM0` (exit: Ctrl+a, Ctrl+q).

## Structure

| File | What is inside |
|------|----------------|
| `main.c` | init + main loop only |
| `src/leds.*` | LED pins, on/off |
| `src/soft_pwm.*` | software PWM with `nrfx_systick` |
| `src/blink.*` | sequence by device ID, smooth duty cycle, start/freeze |
| `src/button.*` | GPIOTE interrupt, debounce (50 ms app_timer), double click |
| `src/logs.*` | `NRF_LOG` init and processing |
| `config/sdk_config.h` | from `examples/peripheral/dongle_logs` |
| `config/app_config.h` | from `dongle_logs` + our overrides (GPIOTE, SysTick) |

## Build and flash

```
make
make dfu
```

SDK path is `/home/user/devel/esl-nsdk` by default, change it with `make SDK_ROOT=...`.
