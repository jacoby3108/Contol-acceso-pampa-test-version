/*
 * door.c
 *
 *  Created on: 12/08/2014
 *      Author: Administrador
 */

#include "msp430g2553.h"
#include "hardware.h"
#include "door.h"
#include "timer.h"
#include "led.h"
#include "wiegand.h"

static UINT door_timer=0;

// USADOS EN EL REAL
//#define DOOR_PULSE_WIDTH  1000  // 1 seg  Pulse width to close the door
//#define TIME_DOOR_STAYS_OPEN  15000 // 15 seg Time to wait before send a command to close the door
//#define TIME_DOOR_TILL_CLOSED 16000 // 16 seg Time used by the door to close 13 i enough

// USADOS para TEST
#define DOOR_PULSE_WIDTH  1000  // 1 seg  Pulse width to close the door
#define TIME_DOOR_STAYS_OPEN  1500 // 1,5 seg Time to wait before send a command to close the door
#define TIME_DOOR_TILL_CLOSED 1600 // 1,6 seg Time used by the door to close 13 i enough




void init_door(void)
{

	  P2OUT &= ~(DOOR);			// Prevent
	  P2SEL|=IO_FUNCTION;		// Primary function as I/O port
	  P2SEL2|=IO_FUNCTION;
	  P2DIR |= (DOOR);			// set port direction


}


void OpenDoor(void)
{

	 P2OUT |= DOOR;

}

void CloseDoor(void)
{

	 P2OUT &= ~DOOR;

}

void isr_door(void)
{
    if (door_timer)
    {                           // if software timer has not expired
        door_timer--;                          // update count

        if(!door_timer)                        // if count expired ( change from  1 to 0)
            CloseDoor();                       // end of pulse
    }

}


void trigger_door_to_open(void)
{
    OpenDoor();                             // Start pulse
    door_timer=DOOR_PULSE_WIDTH/10;         // Set Pulse width
    flash_led(GREEN,100,0);
    Timer_Set_Delay(TIME_DOOR_STAYS_OPEN);  // Set time door stays open
}

void trigger_door_to_close(void)
{

    disable_card_reader();
    OpenDoor();                          // Start pulse
    door_timer=DOOR_PULSE_WIDTH/10;      // Set Pulse width
    led_off(GREEN);
    flash_led(RED,100,0);
    Timer_Set_Delay(TIME_DOOR_TILL_CLOSED);  // Set time door gets closed

}

void Extend_open_delay(void)
{
    Timer_Set_Delay(TIME_DOOR_STAYS_OPEN);  //  Set time door stays open
}
