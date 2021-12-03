//eeprom_hal.c

#include "eeprom_hal.h"

 
 uint8_t EEPROM_read(uint16_t uiAddress, uint8_t *ucData)
 {
	 if(uiAddress > EEPROM_SIZE){
		 return EEPROM_INVALID_ADDR;
	 }
	 
	 /* Wait for completion of previous write */
	 while(EECR & (1<<EEPE));
	 
	 /* Set up address register */
	 EEARH = (uiAddress & 0xFF00) >> 8;
	 EEARL = (uiAddress & 0x00FF);
	 
	 /* Start eeprom read by writing EERE */
	 EECR |= (1<<EERE);
	 
	 /* Return data from Data Register */
	 *ucData = EEDR;
	 
	 return EEPROM_OK;
 }
 uint8_t EEPROM_write(uint16_t uiAddress, uint8_t ucData)
 {
	   if(uiAddress > EEPROM_SIZE){
		   return EEPROM_INVALID_ADDR;
	   }
	  
	  /* Wait for completion of previous write */
	  while(EECR & (1<<EEPE));
	  
	  /* Set up address and Data Registers */
	  EEARH = (uiAddress & 0xFF00) >> 8;
	  EEARL = (uiAddress & 0x00FF);
	  
	  EEDR = ucData;
	  
	  /* Write logical one to EEMPE */
	  EECR |= (1<<EEMPE);
	  
	  /* Start eeprom write by setting EEPE */
	  EECR |= (1<<EEPE);
	  
	  return EEPROM_OK;
  }
		  return EEPROM_INVALID_ADDR;
	  }
	  
	  uint8_t value = 0;
	  err = EEPROM_read(uiAddress,&value);
	  if(err != EEPROM_OK){
		  return err;
	  }
	  if(value == ucData)
	  {
		  return EEPROM_OK;
	  }
		   
		  return err;
	  }
	   if(err != EEPROM_OK){
		   return err;
	   }
	   if(value != ucData)
	   {
		   return EEPROM_WRITE_FAIL;
	   }
			  return err;
		  }
			  return err;
		  }