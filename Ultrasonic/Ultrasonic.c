/*
 * Ultrasonic.c
 *
 *  Created on: Oct 20, 2023
 *      Author: Amira
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "common_macros.h"
#include "std_types.h"
#include "Ultrasonic.h"
#include "icu.h"

uint8 g_edgeCount = 0;
uint16 g_timeEcho = 0;


void Ultrasonic_init(void)
{
	ICU_ConfigType ICU_State = {F_CPU_8,RAISING};
	ICU_init(&ICU_State);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TRIGGER_PORT, TRIGGER_PIN, PIN_OUTPUT);
}

void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		g_timeEcho = ICU_getInputCaptureValue();
	}
}


void Ultrasonic_Trigger(void)
{
	g_timeEcho = 0;
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void)
{
	uint16 distance = 0;
	Ultrasonic_Trigger();
	while(!g_timeEcho); /* wait until the sensor catches the signal */
	distance = ((((float)0.034 * g_timeEcho)/2) + 2);
	return distance;
}


