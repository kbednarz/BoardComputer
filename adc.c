#include <avr/io.h>
#include "adc.h"

void initAdc(){
	  ADCSRA = (1<<ADEN) //ADC Enable
	  |(1<<ADPS0) //prescaler=8
	  |(1<<ADPS1)
	  |(0<<ADPS2);
	  
	  //adc default on ADC0
}


float measureADC(){
	float volt;
	ADCSRA |= (1<<ADSC); //start convertion 
	while(ADCSRA & (1<<ADSC)); //wait for finish
	const float vref = 4.83,
				volt_divider_factor = 3.64;
	volt = (ADC * vref / 1024)*volt_divider_factor;
	
	return volt;
}