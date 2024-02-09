/*
 * Ultrasonic.h
 *
 *  Created on: Oct 20, 2023
 *      Author: Amira
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "gpio.h"
#include "std_types.h"

extern uint8 g_edgeCount;

#define TRIGGER_PORT PORTB_ID
#define TRIGGER_PIN PIN5_ID

void Ultrasonic_edgeProcessing(void);
void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);

#endif /* ULTRASONIC_H_ */
