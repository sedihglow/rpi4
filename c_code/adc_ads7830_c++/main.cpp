#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <ADCDevice.hpp>

#define VCC 3.3 // volts
#define ADC_8BIT_FLOAT_MAX 255.0 // 2^8-1 as a float for adc step max

#define PCF8591_ADDR 0x48
#define ADS7830_ADDR 0x4b

#define A0_PIN 0

int main()
{
    ADCDevice *adc;
    int adc_value = 0;
    float voltage = 0.0;

    adc = new ADCDevice();

    if (adc->detectI2C(PCF8591_ADDR)) {
        delete adc;
        adc = new PCF8591();
    } else if (adc->detectI2C(ADS7830_ADDR)) {
        delete adc;
        adc = new ADS7830();
    } else {
        exit(EXIT_FAILURE);
    }

    for (;;) {
        adc_value = adc->analogRead(A0_PIN);
        voltage = (float)adc_value/ADC_8BIT_FLOAT_MAX * VCC;
        printf("ADC value: %d,\tVoltage: %.2fV\n", adc_value, voltage);
        delay(100);
    }

    exit(EXIT_SUCCESS);
}
