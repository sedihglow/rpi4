#include "led_button.h"
#include <stdlib.h>

int main()
{
    setup_wiringpi_gpio_interface();

    setup_led_pin(LED_PIN, LOW);

    init_button_pin(BUTTON_PIN, true, HIGH);

    for (;;) {
        if (!read_button(BUTTON_PIN)) {
            set_led(LED_PIN, HIGH);
            printf("Button is pressed, LED on\n");
        } else {
            set_led(LED_PIN, LOW);
            printf("NOT PRESSED, LED off\n");
        }
    }

    exit(EXIT_SUCCESS);
}
