#include <stdio.h>
#include <stdbool.h>
#include <wiringPi.h>

#define LED_PIN 0 // gpio17 on rpi
#define SEC_MS 1000

void setup_wiringpi_gpio_interface();
void setup_led_pin(int pnum, bool init);
void set_led(int pnum, bool mode);
void toggle_led(int pnum, bool mode);
void blink_led(int pnum, bool start, int millis); // LED starts HIGH or LOW
