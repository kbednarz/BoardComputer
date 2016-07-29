#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "tachometer.h"


void initTacho(){
	rps=0;
	rpm=0;
	rps_counter=0;
	
	//Init INT0
	MCUCR|=(1<<ISC01);   //Falling edge on INT0 triggers interrupt.

	GICR|=(1<<INT0);  //Enable INT0 interrupt

	//Timer1 is used as 1 sec time base
	//Timer Clock = 1/1024 of sys clock
	//Mode = CTC (Clear Timer On Compare)
	TCCR1B|=((1<<WGM12)|(1<<CS12)|(1<<CS10));

	//Compare value=976

	OCR1A=976;

	TIMSK|=(1<<OCIE1A);  //Timer counts 0-976 and calls interrupt A

	//Enable interrupts globally
	sei();
	
}