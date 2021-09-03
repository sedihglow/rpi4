#include "led_button.h"
#include <stdlib.h>

#define LED_COUNT 10
#define DELAY_BETWEEN_LIGHTS 100 // in ms

int main()
{
    int i;
    int k;
    led_s led[LED_COUNT];

    setup_wiringpi_gpio_interface();
    
    for (i=0, k=1; i < LED_COUNT; ++i, ++k)
        init_led_struct(&led[i], i, HIGH);

    for (i=0; i < LED_COUNT; ++i)
        setup_led_pin(&led[i]);

    for (;;) {
        for (i=0; i < LED_COUNT; ++i)
            blink_led(&led[i], DELAY_BETWEEN_LIGHTS);

        for (i=LED_COUNT-1; i > -1; --i)
            blink_led(&led[i], DELAY_BETWEEN_LIGHTS);
    }

    exit(EXIT_SUCCESS);
}
