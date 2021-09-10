#ifndef _ADC_H_
#define _ADC_H_

#include <stdio.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

typedef struct adc_dev {
    int fd;
    int addr;
    int cmd; 
} adc_s;

void setup_wiringpi_gpio_interface();

void init_adc_dev_struct(adc_s *adc, int fd, int addr);
bool adc_i2c_detect(adc_s *adc);

#endif
