/*
 * atmega328_e2prom_lib_test.cpp
 *
 * Created: 04/08/2021 19:12:35
 * Author : Rhenzo Losso
 
 It writes a small string into Non-Volatile Memory (EEPROM) of ATmega328PB. Then, it reads the 12 first bytes of the string.
 The examples does not use interruption but it is possible to implement a read / write operation interruption based.
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/delay.h>
#include <string.h>
#include "eeprom.h"

int main(void)
{
	char text_nome [] = "Hello world! I'm alive!";
	char text_read[12];
	
	eeprom_memory memory_driver;
	
	//Setting read / write operation to start at 16° byte of EEPROM memory.
	memory_driver.set_offset(0x110);
	
	//It will write the entire string into EEPROM.
	memory_driver.write_data_into_e2prom((uint8_t*) text_nome, strlen(text_nome));
	//It will read only the part "Hello world!"
	memory_driver.read_data_from_e2prom((uint8_t*) text_read, sizeof(text_read));
	
	//it Just flash lights to inform the operations ware executed.	
    DDRD |= (0x1 << PIND5);
	
    while (1) 
    {
		PORTD |= (0x1 << PIND5);
		_delay_ms(1000);
		PORTD &= ~(0x1 << PIND5);
		_delay_ms(1000);
    }
}

