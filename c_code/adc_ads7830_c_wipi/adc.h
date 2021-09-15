#ifndef _ADC_H_
#define _ADC_H_

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

typedef struct adc_input {
    int reading;
    float voltage;
} adc_in_s;

typedef struct adc_dev {
    int fd;
    int addr;
    int msg;
    float vcc; // input voltage used to convert raw input to voltage
    adc_in_s input;
} adc_s;

typedef struct ads7830_cmd {
    int sd; // single ended or differential inputs
    int channel; // channel number
    int pd; // power down selection
} ads7830_cmd_s;

void setup_wiringpi_interface();

void init_adc_dev_struct(adc_s *adc, int addr, int vcc);
void set_ads7830_cmd(ads7830_cmd_s *cmd, int sd, int channel, int pd);

int setup_adc(adc_s *adc);
bool adc_i2c_detect(adc_s *adc);
int analog_read(adc_s *adc);

int create_ads7830_msg(adc_s *adc, ads7830_cmd_s *ads_cmd);
#endif
