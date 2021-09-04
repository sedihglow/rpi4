import RPi.GPIO as gpio
import time

class led:
    def __init__(self, pin, state):
        self.pin = pin
        self.state = state

        self.setup()

    def setup(self):
        gpio.setmode(gpio.BOARD) # physical GPIO numbering
        gpio.setup(self.pin, gpio.OUT)
        gpio.output(self.pin, self.state)

    def set_state(self, state):
        self.state = state
        gpio.output(self.pin, state)

    def toggle_state(self):
        self.set_state(not self.state)

    def blink_led(self, sec):
        self.toggle_state()
        time.sleep(sec)
        self.toggle_state()
        time.sleep(sec)

    def clean_gpio(self):
        gpio.cleanup()

class button:
    def __init__(self, pin, pud, edge):
        self.pin = pin
        self.pud = pud
        self.edge = edge

        self.setup()

    def setup(self):
        gpio.setmode(gpio.BOARD) # physical GPIO numbering
        gpio.setup(self.pin, gpio.IN, self.pud)
