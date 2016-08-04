#include <avr/io.h>
#include <avr/interrupt.h>

void initInterruptions(){
	//Init INT0 for tachometer
	MCUCR|=((1<<ISC01)|(1<<ISC00));   //Raising edge on INT0 triggers interrupt.

	GICR|=(1<<INT0);  //Enable INT0 interrupt

	//Prescaler = 8
	//Mode = CTC (Clear Timer On Compare)
	TCCR1B|=((1<<WGM12)|(1<<CS11));

	//Compare value F_CPU/Prescaler*1/2sec =62500 == 500ms
	OCR1A=62500;

	TIMSK|=(1<<OCIE1A);  //Timer counts 0-62500 and calls interrupt A

	
	
	//Enable interrupts globally
	sei();
}