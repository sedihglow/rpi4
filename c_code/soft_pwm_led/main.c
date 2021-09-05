#include "led_button.h"
#include <stdlib.h>
#include <wiringPi.h>

#define TRAN_DELAY_MS 300
#define LED_PIN 1

int main()
{
    spwm_led_s led;

    setup_wiringpi_gpio_interface();

    init_spwm_led_struct(&led, LED_PIN, SPWM_MIN);
    setup_spwm_led_pin(&led);

    for (;;) {
        spwm_dim_to_bright(&led);
        delay(TRAN_DELAY_MS);
        spwm_bright_to_dim(&led);
        delay(TRAN_DELAY_MS);
    }

    exit(EXIT_SUCCESS);
}
