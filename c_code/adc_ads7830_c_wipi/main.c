#include "adc.h"
#include <stdio.h>
#include <stdlib.h>

#define SLAVE_ADDR 0x4b
#define VCC 3.3

int main()
{
    adc_s adc;
    ads7830_cmd_s ads_cmd;


    setup_wiringpi_interface();
    init_adc_dev_struct(&adc, SLAVE_ADDR, VCC);
    setup_adc(&adc);


    set_ads7830_cmd(&ads_cmd, 0, 0, 1);
    
    create_ads7830_msg(&adc, &ads_cmd);
   
    for (;;) {
        analog_read(&adc);
        printf("ADC value: %d,\tVoltage: %.2fV\n", 
                adc.input.reading, adc.input.voltage);
    }

    exit(EXIT_SUCCESS); 
}
