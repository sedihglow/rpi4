#include "led.h"
#include <stdlib.h>

int main()
{
    setup_wiringpi_gpio_interface();
    setup_led_pin(LED_PIN, LOW);

    for (;;)
        blink_led(LED_PIN, HIGH, SEC_MS);

    exit(EXIT_SUCCESS);
}
