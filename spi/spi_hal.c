//spi_hal.c

volatile uint8_t spi_rx_data = 0;
volatile uint8_t spi_rxtx_done = 0;

ISR(SPI_STC_vect){
	if(SPSR & 0x40){
		spi_rx_data = SPDR;
		spi_rx_data = 0;
		spi_rxtx_done = 1;
	}
	else{
		spi_rx_data = SPDR;
		spi_rxtx_done = 1;
	}
}

void spi_master_init(void){
	DDRB |= (1 << DDB5) | (1 << DDB3) | (1 << DDB2);
	PORTB |= (1 << PORTB2);

	SPCR = (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (0 << CPHA) | (3 << SPR0);
}

static void spi_send(uint8_t *tx, uint8_t *rx){
	spi_rxtx_done = 0;
	SPDR = *tx;
	while(spi_rxtx_done == 0);
	*rx = spi_rx_data;
}

void spi_transfer(uint8_t *tx, uint8_t *rx, uint16_t length){
	PORTB &= ~(1 << PORTB2);
	_delay_us(1000);
	
	for(uint16_t i = 0; i < length; i++){
		spi_send(&tx[i],rx[i]);
	}
	
	PORTB |= (1 << PORTB2);
	_delay_us(1000);
	
}