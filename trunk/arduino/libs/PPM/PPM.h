/*
	Author: pankratov.vs
	Site:	www.en.mishinmachines.com
	
	WARNING: Now this library is written only for Arduino UNO
*/
#ifndef PPM_H
#define PPM_H

#include <Arduino.h>

#define FCPU 16000000 // cpu frequency
#define TIMER_PRESCALER 8
#define DEFAULT_LENGTH 20000 // cycle time in microseconds

int length = DEFAULT_LENGTH;
long t16 =  (DEFAULT_LENGTH/TIMER_PRESCALER)*(FCPU/1000000); // 16-bit timer cycle
char tccr1a = 0;

void setPPMLength (int value) {
	length = value;
	t16 =  (length/TIMER_PRESCALER)*(FCPU/1000000);
}

void ppmMode(int pin, bool way) {
	pinMode(pin, way);
	if(way == OUTPUT) {	
		if(pin==6 || pin==5) {
			// Timer 0 (8bit)
			// this timer is using for delay
		} else if(pin==9 || pin==10) {
			// Timer 1 (16bit)
			ICR1 = t16;
			if(pin==9) {
				tccr1a |= (1<<COM1A1)|(1<<WGM11);
			} else {
				tccr1a |= (1<<COM1B1)|(1<<WGM11);
			}	
			TCCR1A = tccr1a; 		
			TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11); // fast pwm mode, ICR-top, prescaler 8
		} else if(pin==11 || pin==3) {
			// Timer 2 (8bit)
		}
	}
}

void ppmWrite(int pin, int value) {
	long lval;	
	switch(pin) {
		case 6:
		break;
		case 5:
		break;
		case 9:
			lval = value*t16/length;			
			OCR1A = lval;
		break;
		case 10:
			lval = value*t16/length;			
			OCR1B = lval;
		break;
		case 11:
		break;
		case 3:
		break;
	}
}

long ppmRead(int pin) {
	return pulseIn(pin, HIGH, length); // pulseIn
}

#endif
