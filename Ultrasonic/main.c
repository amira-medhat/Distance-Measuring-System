/*
 * main.c
 *
 *  Created on: Oct 20, 2023
 *      Author: Amira
 */
#include <avr/io.h>
#include "Ultrasonic.h"
#include "lcd.h"
#include "icu.h"


int main(void)
{
	uint16 distance;
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	LCD_init();
	while(1)
	{
		 Ultrasonic_init();
		 distance = Ultrasonic_readDistance();
		 if(g_edgeCount == 2)
		 {

			 ICU_deInit(); /* Disable ICU Driver */
			 g_edgeCount = 0;


			 LCD_displayStringRowColumn(0, 0, "distance=");
			 /* display the dutyCycle on LCD screen */
			 LCD_moveCursor(0, 10);
			 if(distance <100 && distance >58) /* the condition is based on an error observed in the simulation in the interval <58 */
			 {
				 LCD_intgerToString(distance);
				 LCD_displayCharacter(' ');
			 }
			 else if(distance <=58)
			 {
				 LCD_intgerToString(distance - 1);
				 LCD_displayCharacter(' ');
			 }
			 else if(distance<10)
			 {

				 LCD_intgerToString(distance);
				 LCD_displayString("  ");
			 }
			 else
			 {
				 LCD_intgerToString(distance);
			 }
			 LCD_displayStringRowColumn(0,14, "cm");

		 }
	}

}
