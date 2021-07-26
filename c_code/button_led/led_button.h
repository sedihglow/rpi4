#include <stdio.h>
#include <stdbool.h>
#include <wiringPi.h>

#define LED_PIN 0 // gpio17 on rpi
#define BUTTON_PIN 1 // gpio18 on rpi
#define SEC_MS 1000

/* wiringPi GPIO funcionalitiy */
void setup_wiringpi_gpio_interface();
void set_gpio_pull(int pnum, bool mode);
void set_gpio_pull_off(int pnum);

/* LED functions */
void setup_led_pin(int pnum, bool init);
void set_led(int pnum, bool mode);
void toggle_led(int pnum, bool mode);
void blink_led(int pnum, bool start, int millis); // LED starts HIGH or LOW

/* Button Functions */
void init_button_pin(int pnum, bool pullup, bool mode);
int read_button(int pnum);
