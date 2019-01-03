/*
 * EEprom.c
 *
 *  Created on: 31/07/2014
 *      Author: Administrador
 */


#include <msp430.h>
#include "hardware.h"
#include "iic.h"
#include "timer.h"

//==== Driver internal variables and definitions =====
#define TIMER_ILDE 1
#define TIMER_IS_RUNNING 2
#define TIMER_TRIGGERED 3


static UINT timer;
static UINT timer_status;

static void EE_Timer_Set_Delay(UINT dly); // dly in milisecons (min 100ms)
static UINT EE_Timer_Get_Status(void);



//====================EE SERVICES========================================

void WriteEE(u8 *pdata,u16 address)
{

	i2c_trans(1, 0xA0, pdata, address,WRITE_M); //i2c TX 1 byte
//	 __delay_cycles(20000); //Just a start up delay
//	dummy_read();



	EE_Timer_Set_Delay(10);						//set write EE time
    while(EE_Timer_Get_Status()!=TIME_OUT);		//Wait Write Time

}

void ReadEE(u8 *pdata,u16 address)
{
	i2c_trans(1, 0xA0, pdata, address,READ_M);  // i2c RX 1 byte

	//EE_Timer_Set_Delay(10);                       //set write EE time
    //while(EE_Timer_Get_Status()!=TIME_OUT);        //Wait Write Time

	while (!i2c_ready());					    // wait for read operation complete
}

void isr_EEprom(void)
{

    if (timer){                           // if software timer has not expired
            timer--;                          // update count

            if(!timer)                        // if count expired ( change from  1 to 0)
                timer_status=TIMER_TRIGGERED; // signal trigger
        }


}


/* ==============================================================================
 * EE_Timer_Set_Delay() Sets software timer expire time in Milliseconds.
 * Timer resolution is 10ms
 * e.g:   EE_Timer_Set_Delay(500); //500 ms
 * Timer status can be requested using the service: EE_Timer_Get_Status() at
 * any time.
 *
 * ==============================================================================*/

void EE_Timer_Set_Delay(UINT dly) // dly in milisecons (min 100ms)
{
    timer=dly/10;
    timer_status=TIMER_IS_RUNNING;
}



/*================================================================================
 * EE_Timer_Get_Status(void) returns the software timer status
 *
 * return values are: TIME_OUT or TIMER_IS_BUSY (names are self explanatory).
 *
 * EE_Timer_Get_Status() can be called any time after a EE_Timer_Set_Delay() was issued
 * This function is useful in polled schemas or in main loops.
 *
 * e.g.:     main loop
 *
 *           if( EE_Timer_Get_Status() == TIME_OUT)
 *
 *                  do_ scheduled_tasks();
 *
 *           Continue with main loop
 *
 *
 *
 *========================================================================*/

UINT EE_Timer_Get_Status(void)
{

    if(timer_status==TIMER_TRIGGERED)  // Has timer elapsed
    {

        timer_status=TIMER_ILDE;      // reset timer status
        return (TIME_OUT);            // Inform timer state
    }
    else

    return(TIMER_IS_BUSY);          // Inform timer state


}




