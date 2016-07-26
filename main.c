/*
 * BoardComputer.c
 *
 * Created: 2016-07-26 12:47:15
 * Author : Kamil
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include "lib/lcd/hd44780.h"


int main(void)
{
    lcd_init();
    lcd_clrscr();
    lcd_puts("Hello World...");
	
    while (1) 
    {
    }
}

