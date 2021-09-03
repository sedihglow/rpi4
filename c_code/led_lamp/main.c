#include "led_button.h"
#include "unistd.h"

#define LED_PIN 0 // gpio17 on rpi
#define BUTTON_PIN 1 // gpio18 on rpi

#define BUTTON_CAPTURE_TIME 50 // in ms
#define BUTTON_DELAY 1000 // in ms

int main(void)
{
    led_s led;
    button_s button;
    int count = 0;

    /* init wiringPi functionality */
    setup_wiringpi_gpio_interface();

    /* init led and button */
    init_led_struct(&led, LED_PIN, LOW);
    init_button_struct(&button, BUTTON_PIN, PUD_UP, HIGH, BUTTON_CAPTURE_TIME);
    
    setup_led_pin(&led);
    setup_button_pin(&button);
    
    for (;;) {
        read_button(&button);
        if (button.state_changed == true && button.state == LOW) { // button is pushed
            ++count;
            printf("button is pressed, %d\n", count);
            toggle_led(&led);
        }
    }
}
