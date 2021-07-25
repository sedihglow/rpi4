#include "blink.h"
#include <stdlib.h>

void main()
{
    setup_wiringpi_gpio_interface();
    setup_led_pin(LED_PIN, LOW);

    for (;;)
        blink_led(LED_PIN, LOW, SEC_MS);

    exit(EXIT_SUCCESS);
}
