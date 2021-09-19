import RPi.GPIO as gpio
import time

class soft_pwm_servo:
    PWM_INIT_DUTY_CYCLE = 0
    SERVO_ANGLE_MIN = 0
    SERVO_ANGLE_MAX = 180
    THOUSANDTH_SEC = 0.001
    HALF_SEC = 0.5

    def __init__(self, pin, angle, freq, duty_min, duty_max):
        self.DUTY_MIN = duty_min
        self.DUTY_MAX = duty_max
        self.FREQ =  freq # in hz
        self.pin = pin
        self.angle = angle
        self.servo = 0 # will be a gpio.PWM object

    def setup(self):
        gpio.setmode(gpio.BOARD) # physical GPIO numbering
        gpio.setup(self.pin, gpio.OUT)
        gpio.output(self.pin, gpio.LOW)

        self.servo = gpio.PWM(self.pin, self.FREQ)
        self.servo.start(self.PWM_INIT_DUTY_CYCLE)

        #set default angle
        self.angle = self.check_angle(self.angle)
        self.set_angle(self.angle)
        time.sleep(self.THOUSANDTH_SEC)

    def map(self, value, inlow, inhigh, tolow, tohigh):
        return (tohigh-tolow)*(value-inlow) / (inhigh-inlow) + tolow
    
    def set_angle(self, angle):
        self.angle = self.check_angle(angle)
        dc = self.map(self.angle, self.SERVO_ANGLE_MIN, 
                      self.SERVO_ANGLE_MAX, self.DUTY_MIN, 
                      self.DUTY_MAX)
        self.servo.ChangeDutyCycle(dc)

    def check_angle(self, angle):
        if (angle < self.SERVO_ANGLE_MIN):
            return self.SERVO_ANGLE_MIN
        elif (angle > self.SERVO_ANGLE_MAX):
            return self.SERVO_ANGLE_MAX

        return angle
        
    def sweep(self, start, finish):
        start = self.check_angle(start)
        finish = self.check_angle(finish)
        
        if (start < finish):
            self.sweep_up(start, finish)
            time.sleep(self.HALF_SEC)
            self.sweep_down(finish, start)
            time.sleep(self.HALF_SEC) # TODO: may remove after testing
        else:
            self.sweep_down(start, finish)
            time.sleep(self.HALF_SEC)
            self.sweep_up(finish, start)
            time.sleep(self.HALF_SEC) # TODO: may remove after testing

    def sweep_down(self, start, finish):
        start = self.check_angle(start)
        finish = self.check_angle(finish)

        if (start < finish):
            print("error: invalid start or finish sweeping down")
            return
        
        self.set_angle(start) # init the servo
        time.sleep(self.THOUSANDTH_SEC)

        for ang in range(start, finish-1, -1):
            self.set_angle(ang)
            time.sleep(self.THOUSANDTH_SEC)

    def sweep_up(self, start, finish):
        start = self.check_angle(start)
        finish = self.check_angle(finish)

        if (start > finish):
            print("error: invalid start of finish sweeping up")
            return

        self.set_angle(start) # init the servo
        time.sleep(2)

        for ang in range(start, finish+1, 1):
            self.set_angle(ang)
            time.sleep(self.THOUSANDTH_SEC)

    def cleanup(self):
        self.servo.stop()
        gpio.cleanup() # not sure if i want to call this if having multiple servos
