/*
 * wiegand.h
 *
 *  Created on: 19/12/2013
 *      Author: Administrador
 */

#ifndef WIEGAND_H_
#define WIEGAND_H_


void init_wiegand();
unsigned char wiegand_get_status(void);
unsigned int wiegand_get_card_number(void);
unsigned int wiegand_get_card_fc(void);
void enable_card_reader(void);
void disable_card_reader(void);


#endif /* WIEGAND_H_ */
