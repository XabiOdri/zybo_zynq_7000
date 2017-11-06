/*
 * leds.c
 *
 *  Created on: 29 oct. 2017
 *      Author: xabie
 */

#include "xgpiops.h"

#include "config.h"
#include "leds.h"


static XGpioPs Gpio;

void init_led(void)
{
	XGpioPs_Config *ConfigPtr;

	ConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&Gpio, ConfigPtr, ConfigPtr->BaseAddr);
	XGpioPs_SetOutputEnablePin(&Gpio,LED4,OUT);
	XGpioPs_SetDirectionPin(&Gpio,LED4,OUT);
}

void turnON_led(int led)
{
	XGpioPs_WritePin(&Gpio,led,1);
}

void turnOFF_led(int led)
{
	XGpioPs_WritePin(&Gpio,led,0);
}
