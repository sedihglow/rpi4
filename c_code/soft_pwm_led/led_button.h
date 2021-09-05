#include <stdio.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <softPwm.h>

#define SEC_MS 1000
#define SPWM_MIN 0
#define SPWM_MAX 100
#define SPWM_DELAY_MS 20

typedef struct led {
    int pin;
    bool state;
} led_s;

typedef struct spwm_led {
    int pin;
    int value;
} spwm_led_s;

typedef struct button {
    int pin;
    int pud; // pull up/down, PUD_UP, PUD_DOWN, PUD_OFF
    long capture_time; // threshold of time button needs to be pressed in ms
    long last_change; // time button last changed
    bool state;
    bool last_state;
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

/* software PWM LED functions */
void init_spwm_led_struct(spwm_led_s *led, int pin, int value);
void setup_spwm_led_pin(spwm_led_s *led);
void spwm_set_led(spwm_led_s *led, int value);
void spwm_dim_to_bright(spwm_led_s *led);
void spwm_bright_to_dim(spwm_led_s *led);

/* Button Functions */
void init_button_struct(button_s *button, int pin, int pud, bool state, 
                        long capture_time);
void setup_button_pin(button_s *button);
int read_button(button_s *button);
