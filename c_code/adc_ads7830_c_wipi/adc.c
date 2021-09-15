#include "adc.h"

#define SUCCESS 0
#define FAILURE -1

#define CH_MASK 0x7 // 3 bit channel mask

#define STEP_MAX_F 255.0 // 2^8-1 as a float for adc step max

/* wiringPi GPIO funcionalitiy */
void setup_wiringpi_interface()
{
    wiringPiSetup();
    printf("Wiring pi interface setup\n");
}

void init_adc_dev_struct(adc_s *adc, int addr, int vcc)
{
    adc->fd = 0;
    adc->addr = addr;
    adc->msg = 0;
    adc->vcc = vcc;
    adc->input.reading = 0;
    adc->input.voltage = 0.0;
}

/* fills in ads7830 message struct */
void set_ads7830_cmd(ads7830_cmd_s *cmd, int sd, int channel, int pd)
{
    cmd->sd = sd;
    cmd->channel = channel;
    cmd->pd = pd;
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

/* sends current message to device and reads the response */
int analog_read(adc_s *adc)
{
    wiringPiI2CWrite(adc->fd, adc->msg);
    adc->input.reading = wiringPiI2CRead(adc->fd);
    adc->input.voltage = (float)adc->input.reading/STEP_MAX_F * adc->vcc;
    return adc->input.reading;
}

/* creats a message in format for the ads7830 cmd byte */
int create_ads7830_msg(adc_s *adc, ads7830_cmd_s *ads_cmd)
{
    int channel_cmd;
    channel_cmd = ((ads_cmd->channel << 2 | ads_cmd->channel >> 1) & CH_MASK);
    adc->msg = ((ads_cmd->sd << 7) | (channel_cmd << 4) | (ads_cmd->pd << 2));
    return adc->msg;
}
