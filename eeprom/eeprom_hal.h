#ifndef EEPROM_HAL_H_
#define EEPROM_HAL_H_

#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define EEPROM_SIZE 1023

enum{
	EEPROM_OK,
	EEPROM_WRITE_FAIL,
	EEPROM_INVALID_ADDR
	};

uint8_t EEPROM_read(uint16_t uiAddress, uint8_t *ucData);
uint8_t EEPROM_write(uint16_t uiAddress, uint8_t ucData);
uint8_t EEPROM_update(uint16_t uiAddress, uint8_t ucData);
uint8_t EEPROM_update_batch(uint16_t uiAddress, void *data, uint16_t length);
uint8_t EEPROM_read_batch(uint16_t uiAddress, void *data, uint16_t length);


#endif