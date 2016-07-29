#ifndef TACHOMETER_H_
#define TACHOMETER_H_

volatile uint16_t rps_counter;    //Main revolution counter
volatile uint16_t rpm;   
volatile uint16_t rps;   

void initTacho();


#endif /* TACHOMETER_H_ */