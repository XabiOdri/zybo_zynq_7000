/*
 * serial.c
 *
 *  Created on: 29 oct. 2017
 *      Author: xabie
 */


#include "xil_printf.h"

#include "config.h"
#include "serial.h"

#define clear_terminal	xil_printf("\x1B[2J"); 		//Clear terminal
#define setCursorLeft	xil_printf("\x1B[H"); 		//Set cursor to top left of terminal

void printSerial(char str[])
{
	setCursorLeft;
	clear_terminal;
	xil_printf(str);
}

void readSerial(void)
{
	char userInput[30];
	while(kar !='\r')
	{
		while (!XUartPs_IsReceiveData(UART_BASEADDR))
		{}
		/* Store the first character in the UART recieve FIFO and echo it */
		kar = XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);
		xil_printf("%c", kar);
		userInput[i]=kar;
		i++;
	}
		userInput[i]='\0';
}
