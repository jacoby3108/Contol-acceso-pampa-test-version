/*
 * door.h
 *
 *  Created on: 12/08/2014
 *      Author: Administrador
 */

#ifndef DOOR_H_
#define DOOR_H_


void init_door(void);
void OpenDoor(void);
void CloseDoor(void);
void trigger_door_to_close(void);
void trigger_door_to_open(void);
void Extend_open_delay(void);
void isr_door(void);






#endif /* DOOR_H_ */
