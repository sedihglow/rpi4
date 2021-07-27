import RPi.GPIO as gpio
import time

LED_PIN = 11    # gpio17 physical pin number
BUTTON_PIN = 12 # gpio18 physical pin number

def setup_gpio(led_pin, button_pin, init_led) :
    # physical gpio numbering
    gpio.setmode(gpio.BOARD)

    # setup LED
    gpio.setup(led_pin, gpio.OUT)
    gpio.output(led_pin, init_led)
    
    # setup button as input with pull up
    gpio.setup(button_pin, gpio.IN, pull_up_down=gpio.PUD_UP)

def set_led(pin, mode) :
    gpio.output(pin, mode)

def toggle_led(pin, start) :
    if (start == gpio.HIGH) :
        set_led(pin, gpio.LOW)
    else :
        set_led(pin, gpio.HIGH)

def blink_led(pin, start, delay_sec) :
    toggle_led(pin, start)
    time.sleep(delay_sec)
    toggle_led(pin, gpio.LOW if start else gpio.HIGH)
    time.sleep(delay_sec)

def cleanup_gpio() :
    gpio.cleanup()

def read_button(pin) :
    return gpio.input(pin)
