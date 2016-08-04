#include <avr/io.h>
#include "lib/i2c/i2c_master.h"
#include <util/twi.h>
#include "clock.h"


uint8_t decToBcd(uint8_t val)
{
	return ( ((val/10)<<4) + (val%10) );
}

uint8_t bcdToDec(uint8_t val)
{
	return( ((val>>4)*10) + (val%16) );
}

void initClock(){
	i2c_init();
}

void readClock(uint8_t* sec, uint8_t* min, uint8_t* hour, uint8_t* day, uint8_t* month, uint8_t* year, uint8_t* weekday){
	i2c_start(I2C_WRITE_ADDRESS);			//reset of transmission
	/*if(TWSR != 0x18) {                    
		clock not work
	} */  
	i2c_write(0);							//write to beginning of memory
	i2c_start(I2C_READ_ADDRESS);                   
	*sec = bcdToDec(i2c_read_ack());
	*min = bcdToDec(i2c_read_ack());
	*hour = bcdToDec(i2c_read_ack());
	*weekday = i2c_read_ack();
	*day = bcdToDec(i2c_read_ack());
	*month = bcdToDec(i2c_read_ack());
	*year = bcdToDec(i2c_read_nack());
	i2c_stop();
}


void writeClock(uint8_t min, uint8_t hour, uint8_t day, uint8_t month, uint8_t year, uint8_t weekday) {               
	i2c_start(I2C_WRITE_ADDRESS);
	/*if(TWSR != 0x18) {             
		clock not work
	}*/
	
	i2c_write(0);							//write to beginning of memory

	i2c_write(0);
	i2c_write(decToBcd(min));
	i2c_write(decToBcd(hour));
	i2c_write(weekday);
	i2c_write(decToBcd(day));
	i2c_write(decToBcd(month));
	i2c_write(decToBcd(year));
	
	i2c_stop();
	
}
	
	