/*
 * buttons.c
 *
 *  Created on: 29 oct. 2017
 *      Author: xabie
 */

#include "xgpiops.h"

#include "config.h"
#include "buttons.h"

static XGpioPs Gpio;

void initButtons(void)
{
	XGpioPs_Config *ConfigPtr;

	ConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&Gpio, ConfigPtr, ConfigPtr->BaseAddr);
}

int getButtonStatus(int btn)
{
	return XGpioPs_ReadPin(&Gpio,btn);
}
