/*
 * EEprom.h
 *
 *  Created on: 31/07/2014
 *      Author: Administrador
 */

#ifndef EEPROM_H_
#define EEPROM_H_


#define EE_START 0x0000


//====================EE SERVICES========================================

void WriteEE(u8 *pdata,u16 address);
void ReadEE(u8 *pdata,u16 address);

void isr_EEprom(void);

#endif /* EEPROM_H_ */
