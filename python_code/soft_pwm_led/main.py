from button_led import soft_pwm_led
import time

LED_PIN = 12
DELAY_SEC = 1

if __name__ == "__main__":
    led = soft_pwm_led(LED_PIN, soft_pwm_led.PWM_MIN_CYCLE)

    led.setup()

    try:
        while(True):
            led.dim_to_bright()
            time.sleep(DELAY_SEC)
            led.bright_to_dim()
            time.sleep(DELAY_SEC)
    except KeyboardInterrupt:
        led.clean_gpio()

