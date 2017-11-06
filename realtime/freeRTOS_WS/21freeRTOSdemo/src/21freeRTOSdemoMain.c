#include <stdio.h>

#include "xil_printf.h"
#include "xgpiops.h"
#include "FreeRTOS.h"
#include "task.h"

void initLed(void);
static void vTask1(void *pvParameters);
void vTask2( void *pvParameters );

XGpioPs Gpio;

int main( void )
{
  xTaskCreate( vTask1, (const char *)"Task 1",200,NULL,0,NULL );
  xTaskCreate( vTask2, (const char *) "Task 2", 200, NULL, 1, NULL );
  vTaskStartScheduler();
  for( ;; );
}
/*-----------------------------------------------------------*/

void vTask1( void *pvParameters )
{
  portTickType xDelay;
  int ledOn=1;

  xDelay = 1000;
  initLed();

  while(1)
  {
	XGpioPs_WritePin(&Gpio,7,ledOn);
    ledOn=!ledOn;
	vTaskDelay(xDelay);
  }
}
/*-----------------------------------------------------------*/

void vTask2( void *pvParameters )
{
  char str[16];
  int cnt=0;
  portTickType xDelay = 2000;

  xil_printf("\r\n21FreeRTOSdemo\r\n\r\n");
  while(1)
  {
    sprintf(str,"%d\r\n",cnt);
    xil_printf(str);
    cnt++;
	vTaskDelay(xDelay);
  }
}

void initLed(void)
{
  XGpioPs_Config *ConfigPtr;

  ConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
  XGpioPs_CfgInitialize(&Gpio, ConfigPtr, ConfigPtr->BaseAddr);
  XGpioPs_SetOutputEnablePin(&Gpio,7,1);
  XGpioPs_SetDirectionPin(&Gpio,7,1);
}

