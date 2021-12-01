#ifndef I2C_HAL_H_
#define I2C_HAL_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define TWI_TIMEOUT 1600

#define TWI_START		0x08
#define TWI_RSTART		0x10
#define TWIT_ADDR_ACK	0x18
#define TWIT_ADDR_NACK	0x20
#define TWIT_DATA_ACK	0x28
#define TWIT_DATA_NACK	0x30

#define TWIR_ADDR_ACK	0x40
#define TWIR_ADDR_NACK	0x48
#define TWIR_DATA_ACK	0x50
#define TWIR_DATA_NACK	0x58

#define TWI_ERROR		0x38
#define TWI_NONE		0xF8

enum{
	TWI_OK,
	TWI_ERROR_START,
	TWI_ERROR_RSTART,
	TWI_NACK
};

static uint8_t i2c_start(void);
static void i2c_stop(void);
static uint8_t i2c_restart(void);
static uint8_t i2c_addr_write_ack(void);
static uint8_t i2c_data_write_ack(void);
static uint8_t i2c_addr_read_ack(void);
static uint8_t i2c_data_read_ack(uint8_t ack);
void i2c_init(uint32_t speed);
uint8_t i2c_write(uint8_t addr,uint8_t reg,uint8_t *data,uint16_t length);
uint8_t i2c_read(uint8_t addr,uint8_t reg,uint8_t *data,uint16_t length);

#endif
