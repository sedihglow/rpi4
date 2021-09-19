from servo import soft_pwm_servo

DUTY_OFFSET = 0.5 # pulse offset for error
SERVO_DUTY_MIN = 2.5 + DUTY_OFFSET
SERVO_DUTY_MAX = 12.5 + DUTY_OFFSET
INIT_ANGLE = 90 
INIT_PWM_FREQ = 50 # hz


SERVO_PIN_1 = 12 # gpio18

if __name__ == "__main__":
    servo = soft_pwm_servo(SERVO_PIN_1, INIT_ANGLE, INIT_PWM_FREQ, 
                           SERVO_DUTY_MIN, SERVO_DUTY_MAX)

    servo.setup()

    try:
        while (True):
            servo.sweep_up(0,180)
    except KeyboardInterrupt:
       servo.cleanup() 
