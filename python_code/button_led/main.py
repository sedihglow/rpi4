import button_led

LED_PIN = button_led.LED_PIN
BUTTON_PIN = button_led.BUTTON_PIN

LOW = button_led.gpio.LOW
HIGH = button_led.gpio.HIGH

if __name__ == "__main__" :
    button_led.setup_gpio(LED_PIN, BUTTON_PIN, LOW) 

    try :
        while True :
            if button_led.read_button(BUTTON_PIN) == LOW :
                button_led.set_led(LED_PIN, HIGH)
            else :
                button_led.set_led(LED_PIN, LOW)
    except KeyboardInterrupt :
        button_led.cleanup_gpio()
