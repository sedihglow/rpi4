import RPi.GPIO as gpio
import time

LED_PIN = 11 # gpio17 physical pin number

def setup_gpio(pin, init) :
    gpio.setmode(gpio.BOARD)
    gpio.setup(pin, gpio.OUT)
    gpio.output(pin, init)

    print("using pin %d" %pin);

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
