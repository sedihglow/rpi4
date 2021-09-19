from servo import soft_pwm_servo
import argparse

DUTY_OFFSET = 0.5 # pulse offset for error
SERVO_DUTY_MIN = 2.5 + DUTY_OFFSET
SERVO_DUTY_MAX = 12.5 + DUTY_OFFSET
INIT_PWM_FREQ = 50 # hz

if __name__ == "__main__": 
    parser = argparse.ArgumentParser(description="initializes and sets servo "
                                                  "angle using soft pwm.")
    parser.add_argument("-p", dest="pin",  nargs='+', type=int, default=-1)
    parser.add_argument("-a", dest="angle", nargs='?', type=int, default=0)
     
    args = parser.parse_args()
    
    i = 0
    servo = []
    servo.append(soft_pwm_servo(args.pin[i], args.angle, INIT_PWM_FREQ, 
                                SERVO_DUTY_MIN, SERVO_DUTY_MAX))

    servo[i].setup()
    print(servo[i].pin)

    servo[i].cleanup()
