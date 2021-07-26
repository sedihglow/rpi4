#include "led.h"

void setup_wiringpi_gpio_interface()
{
    wiringPiSetup();
    printf("Wiring pi interface setup\n");
}

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
