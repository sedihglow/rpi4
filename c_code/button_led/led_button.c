#include "led_button.h"

/* wiringPi GPIO funcionalitiy */
void setup_wiringpi_gpio_interface()
{
    wiringPiSetup();
    printf("Wiring pi interface setup\n");
}
void set_gpio_pull(int pnum, bool mode)
{
    pullUpDnControl(pnum, (mode) ? PUD_UP : PUD_DOWN);
}

void set_gpio_pull_off(int pnum)
{
    pullUpDnControl(pnum, PUD_OFF);
}

/* LED FUNCTIONS */

void setup_led_pin(int pnum, bool init)
{
    pinMode(pnum, OUTPUT);
    printf("Using wiringPi LED pin %d\n", pnum);
    set_led(pnum, init);
}

void set_led(int pnum, bool mode)
{
    digitalWrite(pnum, mode);
}

void toggle_led(int pnum, bool start)
{
    set_led(pnum, !start);
}

void blink_led(int pnum, bool start, int millis)
{
    toggle_led(pnum, start);
    delay(millis);
    toggle_led(pnum, !start);
    delay(millis);
}

/* Button Functions */

/* 
 * If pullup is false, mode is ignored
 */
void init_button_pin(int pnum, bool pullup, bool mode)
{
    pinMode(pnum, INPUT); 

    if (pullup)
        set_gpio_pull(pnum, mode);
    else
        set_gpio_pull_off(pnum);
}

int read_button(int pnum)
{
    return digitalRead(pnum);
}
