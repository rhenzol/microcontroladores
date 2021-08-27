/*
 * e2prom_lib.cpp
 *
 * Created: 04/08/2021 19:13:12
 * Author : Rhenzo Losso
 */ 

#include "eeprom.h"

eeprom_memory::eeprom_memory()
{
	this->offset = EEPROM_MEM_INITIAL_OFFSET;
}

eeprom_memory::~eeprom_memory()
{
	
}

int eeprom_memory::write_data_into_e2prom(uint8_t* ptr, uint16_t data_size)
{
	uint16_t i;
	
	if(data_size > EEPRON_MEM_SIZE) {
		return EEPROM_DATA_TOO_BIG;
	} else {
	//Some standard (as MISRA) requires a empty declaration.
    }
		
	if(this->offset > EEPRON_MEM_SIZE) {
	    return EEPROM_OFFSET_TOO_BIG;
	} else {
	//Some standard (as MISRA) requires a empty declaration.
    }
	
	if(this->offset + data_size > EEPROM_OFFSET_TOO_BIG) {
		return INVALID_EEPROM_REGION;
	} else {
	//Some standard (as MISRA) requires a empty declaration.
    }
	
	//Configuring EEPROM to erase and write memory location atomically.
	EECR &= ~((0x01 << EEPM1) + (0x01 << EEPM1));

	//Writing each byte of string into EEPROM.
	for(i = 0; i < data_size; i++)
	{
		//Informing the location of byte inside the EEPROM. This location is
		//based on offset from EEPROM start address. Each device starts in different
		//address location. Consult the right data sheet / user manual of your device.
		EEAR = i + this->offset;
		//Loading byte from input buffer into EEPROM transfer register.
		EEDR = ptr[i];
		//Signaling the EEPROM  that you want do perform an operation.
		EECR += (0x01 << EEMPE);
		//Writing in EEPROM.
		EECR += 0x2;
		//Waiting until EEPROM is ready for next operation. This "busy wait" could be substitute for
		//an interruption.
		while((EECR & (0x1 << EEPE)) != 0);
	}
	
	return EEPROM_OPERATION_SUCCESSFULLY;
}

int eeprom_memory::read_data_from_e2prom(uint8_t* ptr, uint16_t data_size)
{
	uint16_t i;
	
	if(data_size > EEPRON_MEM_SIZE) {
		return EEPROM_DATA_TOO_BIG;
	} else {
		//Some standard (as MISRA) requires a empty declaration.
	}
	
	if(this->offset > EEPRON_MEM_SIZE) {
		return EEPROM_OFFSET_TOO_BIG;
	} else {
	//Some standard (as MISRA) requires a empty declaration.
    }
	
	if(this->offset + data_size > EEPROM_OFFSET_TOO_BIG) {
		return INVALID_EEPROM_REGION;
	} else {
		//Some standard (as MISRA) requires a empty declaration.
	}
	
	for(i = 0; i < data_size; i++)
	{
		//Informing the location of byte inside the EEPROM. This location is
		//based on offset from EEPROM start address. Each device starts in different
		//address location. Consult the right data sheet / user manual of your device.
		EEAR = i + this->offset;
		//Signaling the EEPROM  that you want do perform an operation.
		EECR += (0x01 << EEMPE);
		//Reading from EEPROM.
		EECR += 0x1;
		//Storing byte read from EEPROM transfer register in output buffer.
		ptr[i] = (char) EEDR;
		//Waiting until EEPROM is ready for next operation. This "busy wait" could be substitute for
		//an interruption.
		while((EECR & (0x1 << EEPE)) != 0);
	}
	
	return EEPROM_OPERATION_SUCCESSFULLY;
}

int eeprom_memory::set_offset(uint16_t offset)
{
	if(offset > EEPRON_MEM_SIZE) {
		return EEPROM_OFFSET_TOO_BIG;
	} else {
		this->offset = offset;
		return EEPROM_OPERATION_SUCCESSFULLY;
	}
}

uint16_t eeprom_memory::get_current_offset()
{
	return this->offset;	
}

