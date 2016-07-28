#ifndef CLOCK_H_
#define CLOCK_H_
#define I2C_READ_ADDRESS 209
#define I2C_WRITE_ADDRESS 208

void readClock(uint8_t* sec, uint8_t* min, uint8_t* hour, uint8_t* day, uint8_t* month, uint8_t* year, uint8_t* weekday);
void writeClock(uint8_t min, uint8_t hour, uint8_t day, uint8_t month, uint8_t year, uint8_t weekday);
void initClock();

#endif /* CLOCK_H_ */