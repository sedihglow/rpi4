#include "adc.h"

#define SUCCESS 0
#define FAILURE -1

/* wiringPi GPIO funcionalitiy */
void setup_wiringpi_interface()
{
    wiringPiSetup();
    printf("Wiring pi interface setup\n");
}

void init_adc_dev_struct(adc_s *adc, int fd, int addr)
{
    adc->fd = fd;
    adc->addr = addr;
    adc->cmd = 0;
}

int setup_adc(adc_s *adc)
{
    adc->fd = wiringPiI2CSetup(adc->addr);
    if (adc->fd < 0) {
        fprintf(stderr, "Failed to get wipi i2c file descriptor.\n");
        return FAILURE;
    }
    
    if (!adc_i2c_detect(adc)) {
        fprintf(stderr, "i2c not found for address %x\n", adc->addr);
        return FAILURE;
    }

    return SUCCESS;
}

bool adc_i2c_detect(adc_s *adc)
{
    if(wiringPiI2CWrite(adc->fd, 0) < 0){
	    printf("Device found at address 0x%x \n",adc->addr);
	    return false;
	} else {
	    printf("Found device at address 0x%x \n",adc->addr);
	    return true;
	}
}
