import blink as led

HIGH = 1
LOW = 0
SECOND = 1

if __name__ == "__main__":
    led.setup_gpio(led.LED_PIN, LOW)
    try : 
        while True :
            led.blink_led(led.LED_PIN, LOW, SECOND)
    except KeyboardInterrupt :
        led.cleanup_gpio()
