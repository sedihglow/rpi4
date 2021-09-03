import RPi.GPIO as gpio
from lamp import lamp as led_lamp

if __name__ == "__main__":
    LED_PIN = 11
    BUTTON_PIN = 12

    lamp = led_lamp(LED_PIN, BUTTON_PIN, gpio.PUD_UP, gpio.FALLING)
    
    print(lamp.light.state)

    try:
        while True:
            pass
    except KeyboardInterrupt:
        lamp.cleanup()

