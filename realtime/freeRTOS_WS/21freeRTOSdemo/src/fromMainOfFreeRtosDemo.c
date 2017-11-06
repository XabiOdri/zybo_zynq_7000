#include <limits.h>
#include "FreeRTOS.h"
#include "task.h"

XScuWdt xWatchDogInstance;

void vAssertCalled( const char * pcFile, unsigned long ulLine )
{
volatile unsigned long ul = 0;

	( void ) pcFile;
	( void ) ulLine;

	taskENTER_CRITICAL();
	{
		/* Set ul to a non-zero value using the debugger to step out of this
		function. */
		while( ul == 0 )
		{
			portNOP();
		}
	}
	taskEXIT_CRITICAL();
}

void vApplicationMallocFailedHook( void )
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

void vApplicationIdleHook( void )
{
volatile size_t xFreeHeapSpace;

	/* This is just a trivial example of an idle hook.  It is called on each
	cycle of the idle task.  It must *NOT* attempt to block.  In this case the
	idle task just queries the amount of FreeRTOS heap that remains.  See the
	memory management section on the http://www.FreeRTOS.org web site for memory
	management options.  If there is a lot of heap memory free then the
	configTOTAL_HEAP_SIZE value in FreeRTOSConfig.h can be reduced to free up
	RAM. */
	xFreeHeapSpace = xPortGetFreeHeapSize();

	/* Remove compiler warning about xFreeHeapSpace being set but never used. */
	( void ) xFreeHeapSpace;
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

void vApplicationTickHook( void )
{
	#if( mainSELECTED_APPLICATION == 1 )
	{
		/* The full demo includes a software timer demo/test that requires
		prodding periodically from the tick interrupt. */
		vTimerPeriodicISRTests();

		/* Call the periodic queue overwrite from ISR demo. */
		vQueueOverwritePeriodicISRDemo();

		/* Call the periodic event group from ISR demo. */
		vPeriodicEventGroupsProcessing();
	}
	#endif
}

void vInitialiseTimerForRunTimeStats( void )
{
XScuWdt_Config *pxWatchDogInstance;
uint32_t ulValue;
const uint32_t ulMaxDivisor = 0xff, ulDivisorShift = 0x08;

	 pxWatchDogInstance = XScuWdt_LookupConfig( XPAR_SCUWDT_0_DEVICE_ID );
	 XScuWdt_CfgInitialize( &xWatchDogInstance, pxWatchDogInstance, pxWatchDogInstance->BaseAddr );

	 ulValue = XScuWdt_GetControlReg( &xWatchDogInstance );
	 ulValue |= ulMaxDivisor << ulDivisorShift;
	 XScuWdt_SetControlReg( &xWatchDogInstance, ulValue );

	 XScuWdt_LoadWdt( &xWatchDogInstance, UINT_MAX );
	 XScuWdt_SetTimerMode( &xWatchDogInstance );
	 XScuWdt_Start( &xWatchDogInstance );
}
