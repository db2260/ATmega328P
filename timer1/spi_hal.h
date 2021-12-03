#ifndef SPI_HAL_H_
#define SPI_HAL_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void spi_master_init(void);
static void spi_send(uint8_t *tx, uint8_t *rx);
void spi_transfer(uint8_t *tx, uint8_t *rx, uint16_t length);


#endif