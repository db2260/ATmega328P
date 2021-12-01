//i2c_hal.c

#include "i2c_hal.h"

volatile uint8_t status = 0xF8;

ISR(TWI_vect){
	status = (TWSR & 0xF8);
}

static uint8_t i2c_start(void){
	uint16_t i = 0;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE);
	
	while(status != TWI_START){
		i++;
		if(i >= TWI_TIMEOUT){
			return TWI_ERROR_START;
		}
	}
	
	return TWI_OK;
	
}

static void i2c_stop(void){
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE);


}

static uint8_t i2c_restart(void){
	uint16_t i = 0;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE);

	while(status != TWI_RSTART){
		i++;
		if(i >= TWI_TIMEOUT){
			return TWI_ERROR_START;
		}
	}

	return TWI_OK;

}

static uint8_t i2c_addr_write_ack(void){
	uint16_t i = 0;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE);

	while(status != TWIT_ADDR_ACK){
		i++;
		if(i >= TWI_TIMEOUT){
			return TWI_ERROR_START;
		}	
	}

	return TWI_OK;

}

static uint8_t i2c_data_write_ack(void){
	uint16_t i = 0;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE);

	while(status != TWIT_DATA_ACK){
		i++;
		if(i >= TWI_TIMEOUT){
			return TWI_ERROR_START;
		}
	}

	return TWI_OK;
	
}


static uint8_t i2c_addr_read_ack(void){
	uint16_t i = 0;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE);

	while(status != TWIR_ADDR_ACK){
		i++;
		if(i >= TWI_TIMEOUT){
			return TWI_ERROR_START;
		}
	}

return TWI_OK;

}

static uint8_t i2c_data_read_ack(uint8_t ack){
	uint16_t i = 0;
	
	if(ack != 0){
		TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE) | (1 << TWEA);

		while(status != TWIR_DATA_ACK){
			i++;
			if(i >= TWI_TIMEOUT){
				return TWI_ERROR_START;
			}
		}
	}
	else{
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);

		while(status != TWIR_DATA_NACK){
			i++;
			if(i >= TWI_TIMEOUT){
				return TWI_ERROR_START;
			}
		}
	}
	
	return TWI_OK;

}

uint8_t i2c_read(uint8_t addr,uint8_t reg,uint8_t *data,uint16_t length){
	uint16_t i = 0;
	uint8_t err = TWI_OK;
	
	err = i2c_start();
	
	if(err != TWI_OK){
		i2c_stop();
		return err;
	}
	
	TWDR = (addr << 1) | 0;
	
	err = i2c_addr_write_ack();
	
	if(err != TWI_OK){
		i2c_stop();
		return err;
	}
	
	TWDR = reg;
	
	err = i2c_data_write_ack();
	
	if(err != TWI_OK){
		i2c_stop();
		return err;
	}
	
	err = i2c_restart();
	
	if(err != TWI_OK){
		i2c_stop();
		return err;
	}
	
	TWDR = (addr << 1) | 1;
	
	err = i2c_addr_read_ack();
	
	if(err != TWI_OK){
		i2c_stop();
		return err;
	}
	
	for(i = 0; i < (length - 1); i++){
		err = i2c_data_read_ack(1);
		
		if(err != TWI_OK){
			i2c_stop();
			return err;
		}
		data[i] = TWDR;
	}
	
	err = i2c_data_read_ack(0);
	
	if(err != TWI_OK){
		i2c_stop();
		return err;
	}
	data[i] = TWDR;
	
	i2c_stop();
	
	return TWI_OK;
}


uint8_t i2c_write(uint8_t addr,uint8_t reg,uint8_t *data,uint16_t length){
	uint16_t i = 0;
	uint8_t err = TWI_OK;
	
	err = i2c_start();
	
	if(err != TWI_OK){
		i2c_stop();
		return err;
	}
	
	TWDR = (addr << 1) | 0;
	
	err = i2c_addr_write_ack();
	
	if(err != TWI_OK){
		i2c_stop();
		return err;
	}
	
	TWDR = reg;
	
	err = i2c_data_write_ack();
	
	if(err != TWI_OK){
		i2c_stop();
		return err;
	}
	
	for(i = 0; i < length; i++){
		TWDR = data[i];
		err = i2c_data_write_ack();
		
		if(err != TWI_OK){
			i2c_stop();
			return err;
		}
		
	}
	
	i2c_stop();
	
	return TWI_OK;
	
}


void i2c_init(uint32_t speed){
	uint32_t gen_t = 0;
	gen_t - (((F_CPU/speed) - 16) / 2)& 0xFF;
	TWBR = gen_t & 0xFF;
	TWCR = (1 << TWEN) | (1 << TWIE);
	
	//PORTC |= (1 << PORTC5 | 1 << PORTC4);
	
	
}