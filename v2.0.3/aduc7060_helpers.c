/************************************************************************************************
 Author        : Jordan Baczuk
 Date          : 2018/3/22
 File          : aduc7060_helpers.c
 Hardware      : ADuC7060
 Description   : Configuration of common aduc7060 registers and some helpers
 Revision      : v2.0
*************************************************************************************************/

#include "aduc7060_helpers.h"
#ifndef __aduc7060_h
#define __aduc7060_h
	#include <aduc7060.h>
#endif
#include "config.h"
#include <stdint.h>

void initGpio()
{
	// Initialize GPIO
	GP0DAT &= ~BIT28;				//Configure P0.4 as an input **Used for sleep mode toggle
	//GP0DAT &= ~BIT30;				//Configure P0.6 as an input **Used for XBEE CTS
	//GP1DAT |= BIT30;        //Configure P1.6 as an output **Used for XBEE
	GP1DAT |= BIT29;				//Configure P1.5 as an output **Used for analog power (avdd)
	GP1DAT |= BIT28;				//Configure P1.4 as an output **Used for LED
//	
//	GP1DAT &= ~XBEE_PWR_REG;  //set bit -> voltage high = XBEE off
//	GP1DAT &= ~AVDD_REG; //clear bit -> voltage low = Analog Power Off
//	GP1DAT &= ~LED_REG; //clear bit -> voltage low = LED Off
	
}

void initInterrupts()
{
	IRQCONE = setIRQCONE();		  //	External Interrupt Edge/Level triggering MMR	
	IRQEN = setIRQEN(); 				//	set up IRQ MMR
	// Initilize Timer 1 in Periodic mode with
	T1CON = setT1CON();
	//T1LD = 0x3F99A; 					// 7.95 second toggle rate
	//T1LD = 0x14000;							// 2 second toggle rate
	T1LD = 0xA000;							// 1 second toggle rate
}

void initI2C()
{
	IRQCONE = BIT1;				// Rising edge trigger on XIRQ0
	// Configure P0.1 and P0.3 for I2C mode. Configure P1.0 and P1.1 for UART mode. 
	GP0CON0 = BIT4 + BIT12; // Select SPI/I2C alternative function for P0.1 & P0.3
	GP0KEY1 = 0x7;		   	// Write to GP0KEY1
	GP0CON1	= BIT1;		   	// Select I2C functionality for P0.1 & P0.3
	GP0KEY2 = 0x13;		   	// Write to GP0KEY2

	// Enable I2C Master mode, baud rate and interrupt sources
	I2CMCON = BIT0 + BIT4 // Enable I2C Master + Enable Rx interrupt
			+ BIT5 + BIT8; 		// Enable Tx interrupt + Enable transmission complete interrupt
	I2CDIV  = 0x3131;	   	// Select 100.3kHz clock rate
	//I2CSCON |= BIT1;			// Enable normal address mode
	IRQEN = BIT15;// + BIT16 + BIT13; // Enable I2C Master, Slave and XIRQ0 interrupts
}

void initAdc()
{
	ADCFLT = 0x7;	// Chop off, 1Khz samping rate, SF = 7.	No averaging
	ADCCFG = 0;
	ADCMDE = BIT0 + BIT7;	// Continuous Conversion mode, Normal mode, 4Mhz clock source to ADC.
}

// FIXME: this doesn't appear to be changing the baud at all (always 9600)
void initUart()
{
	// Initialize the UART for 9600-8-N
	GP1CON += BIT0 + BIT4;  // Select UART functionality for P1.0/P1.1
	COMCON0 = BIT7;			// Enable access to COMDIV registers
	COMDIV0 = 0x21;			// Set baud rate to 9600.
	COMDIV1 = 0x00;
	// Enable fractional divider for baud accuracy (COMDIV2 set bit 15)
	// baud: 115200 (115218)
	// DL -> COMDIV0 = 0x2
	// M -> bits 12:11 = 0x1
	// N -> bits 10:0 = 0x31C (796)
	//COMDIV0 = 0x10;			// Set baud rate to 19200.
	//COMDIV0 = 0x2;			// Set baud rate to 115200.
	//COMDIV2 = BIT15 + BIT11 + 0x31C; // 0x8B1C
	COMCON0 = BIT0 + BIT1 + BIT2;
}

void sleep(void)
{
	int i;
	POWKEY1 = 0x1;
	//POWCON0 = 0x70; // Enter pause mode
	//POWCON0 = 0x60; // Enter nap mode
	POWCON0 = 0x40; // Enter sleep mode
	//POWCON0 = 0x00; // Enter stop mode
	POWKEY2 = 0xF4;
	
	// Dummy cycle
	for(i=0; i<1; i++){}
}

void wake(void)
{
	POWKEY1 = 0x1;
	POWCON0 = 0x78;		   	// Set core to max CPU speed of 10.24Mhz
	POWKEY2 = 0xF4;
	
	POWKEY3 = 0x76;
	POWCON0 = 0x124;	   	// Set the Peripheral clocks to max speed of 10.24Mhz
	POWKEY4 = 0xB1;
}

void turn_on_led(void)
{
	GP1DAT |= BIT20;
}

void turn_off_led(void)
{
	GP1DAT &= ~BIT20;
}

void turn_on_avdd(void)
{
	GP1DAT |= BIT21;
}

void turn_off_avdd(void)
{
	GP1DAT &= ~BIT21;
}

void enable_mux_channel(uint8_t mux_channels)
{
	// Begin Master Transmit sequence
	I2CFSTA = BIT9;			// Flush Master Tx FIFO
	I2CFSTA &= ~BIT9;
	I2CMTX = mux_channels;
	I2CADR0 = ADG729_I2C_ADDR << 1 | I2C_WRITE; 
}

