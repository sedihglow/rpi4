import RPi.GPIO as gpio
from button_led import led
from button_led import button as b


class lamp:

    BOUNCE_TIME = 300 # in ms

    def __init__(self, lpin, bpin, pud, edge):
        self.light = led(lpin, gpio.LOW)
        self.button = b(bpin, pud, edge)
        gpio.add_event_detect(bpin, gpio.FALLING, callback = self.button_pressed, bouncetime = self.BOUNCE_TIME)

    def button_pressed(self, channel):
        self.light.toggle_state()

    def cleanup(self):
        self.light.clean_gpio()
