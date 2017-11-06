/*
 * timer.h
 *
 *  Created on: 29 oct. 2017
 *      Author: xabie
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include <xscutimer.h>
#include <xscugic.h>

#include "config.h"

void initTimer(unsigned int msecs);
unsigned int getStep();
unsigned int getTimerCount();
void timerCallback(XScuTimer *TimerInstance);

#endif /* SRC_TIMER_H_ */
