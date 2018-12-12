/************************************************************************************************
 Author        : Jordan Baczuk
 Date          : 2018/3/22
 File          : main.c
 Hardware      : ADuC7060
 Description   : MudMax Transmitter Firmware Main File
 Revision      : v2.0
*************************************************************************************************/

#ifndef __aduc7060_h
#define __aduc7060_h
	#include <aduc7060.h>
#endif
#include "aduc7060_helpers.h"
#include "interrupt_handlers.h"
#include "config.h"

int cycle1_complete = 0;
int power_saving_mode_en = 1;

int main(void)
{
		
	initInterrupts();
	initUart();
	initAdc();
  initGpio();
	initI2C();
	wake();
//test change for git	
	while(1)
	{		
		if(cycle1_complete)
		{
			//if(power_saving_mode_en)
				//sleep();
		}
	}
}

//-----------------------------------------------------------------------------------------------
void IRQ_Handler(void) __irq
{	
	unsigned long IRQSTATUS = IRQSTA; // Read off IRQSTA register
	unsigned int I2CMSTATUS = 0;
	
	if ((IRQSTATUS & BIT4) == BIT4) //Timer 1 interrupt source
	{ 
		timer1_handler(power_saving_mode_en);
		cycle1_complete = 1;
		T1CLRI = 0x55;							// Clear the currently active Timer1 Irq	
	}
	
	// FIXME: this is not firing for some reason
	if ((IRQSTATUS & BIT13) == BIT13)	//push button interrupt source
	{
		// Software Debounce
		int delay = 4096;
		int t = 0;
		for (t=0; t<delay; t++){}
		// toggle power saving mode
	  power_saving_mode_en = !power_saving_mode_en;
		// Clear interrupt
		IRQCLRE |= BIT13;	
	}
	
	if ((IRQSTATUS & BIT15) == BIT15)	//If I2C Master interrupt source
	{
		I2CMSTATUS = I2CMSTA; // <-- zRequired to allow uC to sleep
		IRQCLRE |= BIT15;  // Clear I2C interrupt flag
	}
}

