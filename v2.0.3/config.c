/************************************************************************************************
 Author        : Jordan Baczuk
 Date          : 2018/3/22
 File          : config.c
 Hardware      : ADuC7060
 Description   : Configuration of common aduc7060 registers and some helpers
 Revision      : v2.0
*************************************************************************************************/

#include "aduc7060_helpers.h"
#include "config.h"

unsigned long setIRQEN()
{
	
		volatile unsigned long IRQEN = 
//				BIT0	+				//	All interrupts OR'ed (FIQ Only)		This bit is set if any FIQ is active
//				BIT1	+				//	Software Interrupt								User programmable interrupt source
//				BIT2	+				//	Undefined													This bit is not used
//				BIT3	+				//	Timer0														General-Purpose Timer0
				BIT4  + 			// 	Timer1 or wake up timer						General-Purpose Timer1 or wake uptimer
//				BIT5	+				//	Timer2 or watchdog timer					General-Purpose Timer2 or watchdog timer
//				BIT6	+				//	Timer3 or STI timer								General-Purpose Timer3
//				BIT7	+				//	Undefined													This bit is not used
//				BIT8	+				//	Undefined													This bit is not used
//				BIT9	+				//	Undefined													This bit is not used
//					BIT10 +				//	ADC																ADC interrupt source bit
//					BIT11 +				//	UART															UART interrupt source bit
//				BIT12	+				//	SPI																SPI interrupt source bit
//  			BIT13	+				//	XIRQ0 (GPIO IRQ0)									External Interrupt 0
//				BIT14	+				//	XIRQ1 (GPIO IRQ1)									External Interrupt 1
//				BIT15	+				//	I2C Master IRQ										I2C master interrupt source bit
//				BIT16	+				//	I2C Slave IRQ											I2C slave interrupt source bit
//				BIT17	+				//	PWM																PWM trip interrupt source bit
//				BIT18	+				//	XIRQ2 (GPIO IRQ2)									External Interrupt 2
//				BIT19	+				//	XIRQ3 (GPIO IRQ3)									External Interrupt 3
					0;	//End of Bit Set

	return IRQEN;

}

unsigned long setIRQCONE()
{
	volatile unsigned long IRQCONE = 
//				BIT0	+				//	IRQ0SRC[0]												Set Bit if IRQ is active _low or on Falling Edge, Clear for Active high or Rising Edge
				BIT1	+				//	IRQ0SRC[1]												Set Bit if IRQ is Edge triggered, Clear for Level Triggered
//				BIT2	+				//	IRQ1SRC[0]												Set Bit if IRQ is active _low or on Falling Edge, Clear for Active high or Rising Edge
//				BIT3	+				//	IRQ1SRC[1]												Set Bit if IRQ is Edge triggered, Clear for Level Triggered
//				BIT4  + 			// 	IRQ2SRC[0]												Set Bit if IRQ is active _low or on Falling Edge, Clear for Active high or Rising Edge
//				BIT5	+				//	IRQ2SRC[1]												Set Bit if IRQ is Edge triggered, Clear for Level Triggered
//				BIT6	+				//	IRQ3SRC[0]												Set Bit if IRQ is active _low or on Falling Edge, Clear for Active high or Rising Edge
//				BIT7	+				//	IRQ3SRC[1]												Set Bit if IRQ is Edge triggered, Clear for Level Triggered
//				BIT8:31				//	Reserved													These Bits are reserved and should not be written to.
					0;	//End of Bit Set
	return IRQCONE;
}


unsigned long setT1CON()
{
	
	//timeout period=(TxLD * Prescaler)/Source_Clock
	
	
	volatile unsigned long T1CON = 
//				BITS[3:0]			//	T1SCALE													Prescaler.
					0x00	+			//																	Source clock/1 (default).
//					0x04	+			//																	Source clock/16
//					0x08	+			//																	Source clock/256 (used with hours:minutes:seconds:hundredths
//					0x0F	+			//																	Source clock/32,768
//				BIT [5:4]			//	T1FORMAT												Format.
					0x00	+			//																	binary (default).
//					0x10				//																	reserved
//					0x20	+			//																	H:M:S:hundredth's (23 hours to 0 hours) only valid with 32kHz clock.
//					0x30	+			//																	H:M:S:hundredth's (255 hours to 0 hours) only valid with 32kHz clock.
				BIT6	+				//	T1MOD														Timer Mode, Set for Periodic, Clear for Free Running (default cleared)
				BIT7	+				//	T1EN														Timer Enable
//				BIT8	+				//	T1DIR														Count Up, Clear to count down
//				BIT [10:9]		//	T1CLKSEL												Clock Source Select
					0x000	+			//																	32.768 kHz oscillator
//					0x200	+			//																	10.24 MHz/CD
//					0x400	+			//																	XTALI
//					0x600	+			//																	10.24 MHz
//				BIT [15:11]		//	Reserved
					0;	//End of Bit Set
	return T1CON;
}
