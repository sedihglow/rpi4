#include "led_button.h"

#define LED_PIN 0 // gpio17 on rpi
#define BUTTON_PIN 1 // gpio18 on rpi

int main(void)
{
    led_s led;
    init_led_struct(&led, LED_PIN, LOW);
}
