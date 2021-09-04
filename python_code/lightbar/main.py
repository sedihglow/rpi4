from button_led import led
import RPi.GPIO as gpio

if __name__ == "__main__":
    led_pins = [11, 12, 13, 15, 16, 18, 22, 7, 3, 5]
    light = []

    # fill light list with led objects
    for x in range(0, 10):
        light.append(led(led_pins[x], gpio.HIGH))

    try:
        while True:
            for i in light:
                i.blink_led(.1)
            pass
    except KeyboardInterrupt:
        light[0].clean_gpio()
