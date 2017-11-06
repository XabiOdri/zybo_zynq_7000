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

}
