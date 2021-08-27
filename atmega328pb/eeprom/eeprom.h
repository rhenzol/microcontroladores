/*
 * eeprom.h
 *
 * Created: 04/08/2021 19:20:26
 *  Author: Rhenzo Losso
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>

#define EEPROM_MEM_INITIAL_OFFSET                0x00

#define EEPRON_MEM_SIZE                          1023

#define EEPROM_OPERATION_SUCCESSFULLY            0

#define EEPROM_DATA_TOO_BIG                     -1

#define EEPROM_OFFSET_TOO_BIG                   -2

#define INVALID_EEPROM_REGION                   -3

class eeprom_memory {
public:
	eeprom_memory();
	~eeprom_memory();
	int write_data_into_e2prom(uint8_t* ptr, uint16_t data_size);
	int read_data_from_e2prom(uint8_t* ptr, uint16_t data_size);
	int set_offset(uint16_t offset);
	uint16_t get_current_offset(void);
private:
	int16_t offset;
	};

#endif /* EEPROM_H_ */