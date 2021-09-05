#include "led_button.h"

/* wiringPi GPIO funcionalitiy */
void setup_wiringpi_gpio_interface()
{
    wiringPiSetup();
    printf("Wiring pi interface setup\n");
}

void set_gpio_pull(int pnum, int pud)
{
    pullUpDnControl(pnum, pud);
}

/* LED FUNCTIONS */

void init_led_struct(led_s *led, int pin, bool state)
{
    led->pin = pin;
    led->state = state;
}

void setup_led_pin(led_s *led)
{
    pinMode(led->pin, OUTPUT);
    printf("Using wringPi LED pin %d\n", led->pin);
    set_led(led, led->state);
}

void set_led(led_s *led, bool mode)
{
    led->state = mode;
    digitalWrite(led->pin, mode);
}

void toggle_led(led_s *led)
{
    set_led(led, !led->state);
}

void blink_led(led_s *led, int ms)
{
    toggle_led(led);
    delay(ms);
    toggle_led(led);
    delay(ms);
}

/* PWM LED functions */

void init_spwm_led_struct(spwm_led_s *led, int pin, int value)
{
    led -> pin = pin;
    led-> value = value;
}

void setup_spwm_led_pin(spwm_led_s *led)
{
    softPwmCreate(led->pin, SPWM_MIN, SPWM_MAX);
    spwm_set_led(led, led->value);
}

void spwm_set_led(spwm_led_s *led, int value)
{
    led->value = value;
    softPwmWrite(led->pin, value);
}

void spwm_dim_to_bright(spwm_led_s *led)
{
    int i;

    for (i=SPWM_MIN; i <= SPWM_MAX; ++i) {
        spwm_set_led(led, i);
        delay(SPWM_DELAY_MS);
    }
}

void spwm_bright_to_dim(spwm_led_s *led)
{
    int i;
    
    for (i=SPWM_MAX; i >= SPWM_MIN; --i) {
        spwm_set_led(led, i);
        delay(SPWM_DELAY_MS);
    }
}

/* Button Functions */

void init_button_struct(button_s *button, int pin, int pud, bool state, 
                        long capture_time)
{
    button->pin          = pin;
    button->pud          = pud;
    button->state        = state;
    button->last_state   = state;
    button->capture_time = capture_time;
    button->last_change  = 0;
    button->state_changed = false;
}

void setup_button_pin(button_s *button)
{
    pinMode(button->pin, INPUT); 
    set_gpio_pull(button->pin, button->pud);
}

/* 
 * read button with debouncing
 * saves reading into buttons state
 * returns button state variable
 */
int read_button(button_s *button)
{
    int in = 0;

    in = digitalRead(button->pin);
    if (in != button->last_state)
        button->last_change = millis();

    if ((millis() - button->last_change) > button->capture_time) {
        button->state_changed = false;
        if (in != button->state) {
            button->state = in; 
            button->state_changed = true;
        }
    }
    
    button->last_state = in;
    return button->state;
}
