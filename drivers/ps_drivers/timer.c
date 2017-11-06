/*
 * timer.c
 *
 *  Created on: 29 oct. 2017
 *      Author: xabie
 */


#include "timer.h"

#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define TIMER_DEVICE_ID		XPAR_SCUTIMER_DEVICE_ID
#define INTC_BASE_ADDR		XPAR_SCUGIC_CPU_BASEADDR
#define INTC_DIST_BASE_ADDR	XPAR_SCUGIC_DIST_BASEADDR
#define TIMER_IRPT_INTR		XPAR_SCUTIMER_INTR

static unsigned int count=0;
static float step = 0;
static XScuTimer TimerInstance;

static void enableInterrupts();
static void setupInterrupts();
static void setupTimer(int msecs);

void initTimer(unsigned int msecs)
{
	setupTimer(msecs);
	setupInterrupts();
	enableInterrupts();
}

unsigned int getStep()
{
	return step;
}

unsigned int getTimerCount()
{
	return count;
}

static void enableInterrupts()
{
	/* Enable non-critical exceptions.*/
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
	XScuTimer_EnableInterrupt(&TimerInstance);
	XScuTimer_Start(&TimerInstance);
	return;
}

static void setupInterrupts()
{
	Xil_ExceptionInit();

	XScuGic_DeviceInitialize(INTC_DEVICE_ID);

	/*Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor*/
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
			(Xil_ExceptionHandler)XScuGic_DeviceInterruptHandler,
			(void *)INTC_DEVICE_ID);
	/*Connect the device driver handler that will be called when an interrupt for the device occurs, the handler defined above performs
	the specific interrupt processing for the device.*/
	XScuGic_RegisterHandler(INTC_BASE_ADDR, TIMER_IRPT_INTR,
			(Xil_ExceptionHandler)timerCallback,
			(void *)&TimerInstance);
	/*Enable the interrupt for scu timer.*/
	XScuGic_EnableIntr(INTC_DIST_BASE_ADDR, TIMER_IRPT_INTR);
	return;
}

static void setupTimer(int msecs)
{
	XScuTimer_Config *ConfigPtr;
	int TimerLoadValue = 0;
	step = 1000/msecs;
	ConfigPtr = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
	XScuTimer_CfgInitialize(&TimerInstance, ConfigPtr, ConfigPtr->BaseAddr);
	int a = XScuTimer_SelfTest(&TimerInstance);
	XScuTimer_EnableAutoReload(&TimerInstance);
	/*El dos es debido  que el clock del timer va a la mitad del de la cpu*/
	TimerLoadValue = XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / (step*2);
	XScuTimer_LoadTimer(&TimerInstance, TimerLoadValue);

}

void timerCallback(XScuTimer *ptrTimerInstance)
{
	count++;
	XScuTimer_ClearInterruptStatus(ptrTimerInstance);
}
