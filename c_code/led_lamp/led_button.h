#include <stdio.h>
#include <stdbool.h>
#include <wiringPi.h>

#define SEC_MS 1000

typedef struct led {
    int pin;
    bool state;
} led_s;

typedef struct button {
    int pin;
    int pud; // pull up/down, PUD_UP, PUD_DOWN, PUD_OFF
    bool state;
    bool last_state;
    long capture_time; // threshold of time button needs to be pressed in ms
    long last_change; // time button last changed
    bool state_changed;
} button_s;

/* wiringPi GPIO funcionalitiy */
void setup_wiringpi_gpio_interface();
void set_gpio_pull(int pnum, int pud);

/* LED functions */
void init_led_struct(led_s *led, int pin, bool state);

void setup_led_pin(led_s *led);
void set_led(led_s *led, bool mode);
void toggle_led(led_s *led);
void blink_led(led_s *led, int ms);

/* Button Functions */
void init_button_struct(button_s *button, int pin, int pud, bool state, 
                        long capture_time);
void setup_button_pin(button_s *button);
int read_button(button_s *button);
