/*
 * leds.h
 *
 *  Created on: 29 oct. 2017
 *      Author: xabie
 */

#ifndef SRC_LEDS_H_
#define SRC_LEDS_H_

#define LED4	7

#define OUT		1

void init_led(void);
void turnON_led(int led);
void turnOFF_led(int led);

#endif /* SRC_LEDS_H_ */
