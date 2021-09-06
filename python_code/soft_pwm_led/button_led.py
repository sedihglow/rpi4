import RPi.GPIO as gpio
import time

class digital_led:
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

class soft_pwm_led:
    PWM_FREQ_HZ = 500
    PWM_MIN_CYCLE = 0
    PWM_MAX_CYCLE = 100
    HUNDRETH_SEC = 0.01

    def __init__(self, pin, value):
        self.pin = pin
        self.value = value
        self.pwm = 0 # will be gpio.PWM object

    def setup(self):
        gpio.setmode(gpio.BOARD)
        gpio.setup(self.pin, gpio.OUT)
        gpio.output(self.pin, gpio.LOW)

        self.pwm = gpio.PWM(self.pin, self.PWM_FREQ_HZ)
        self.pwm.start(self.value) 
    
    def dim_to_bright(self):
        for dc in range(self.PWM_MIN_CYCLE, self.PWM_MAX_CYCLE+1, 1):
            self.pwm.ChangeDutyCycle(dc)
            time.sleep(self.HUNDRETH_SEC)

    def bright_to_dim(self):
        for dc in range(self.PWM_MAX_CYCLE, self.PWM_MIN_CYCLE-1, -1):
            self.pwm.ChangeDutyCycle(dc)
            time.sleep(self.HUNDRETH_SEC)
        
    def clean_gpio(self):
        self.pwm.stop()
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

    def clean_gpio(self):
        gpio.cleanup()
