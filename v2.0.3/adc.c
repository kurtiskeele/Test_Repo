/************************************************************************************************
 Author        : Jordan Baczuk
 Date          : March 19 2018
 File          : adc.c
 Hardware      : ADuC7060
 Description   : ADC functions
 Revision			 : v2.0
*************************************************************************************************/

#include "adc.h"
#include <aduc7060.h>
#include "aduc7060_helpers.h"

void readAdcChannels(int *adc0, int *adc1, unsigned int ADC0Chan, unsigned int ADC1Chan)
{
	
	ADC0CON = 
		(ADC0Chan << 6) | 		  	// Single ended mode
		BIT10 + BIT15;		      	// Unipolar, Channel 0 Enable
	
	ADC1CON = 
		(ADC1Chan << 7) |        	// Single Ended Mode
		BIT11 + BIT15;			  		// Unipolar, Channel 1 Enable 
	
	while(1)
	{
		if((ADCSTA & 0x03) == 0x03)			// Both ADC channels data ready
		{
			//   To ensure that primary ADC and auxiliary ADC
			// conversion data are synchronous, user code should first read
			// the ADC1DAT MMR and then the ADC0DAT MMR.  See p.42
			(*adc1) = ADC1DAT;
			(*adc0) = ADC0DAT;
			return;
		}
	}
}


int readAdc0Channel(unsigned int ADC0Chan)
{
	ADC0CON = 
		(ADC0Chan << 6) | 		  	// Single ended mode
		BIT10 + BIT15;		      	// Unipolar, Channel 0 Enable
	
	while(1)
	{
		if((ADCSTA & 0x01) == 0x01)			// ADC Channel 0 data ready
		{
			return ADC0DAT;
		}
	}
}

int readAdc1Channel(unsigned int ADC1Chan)
{
	ADC1CON = 
		(ADC1Chan << 7) |        	// Single Ended Mode
		BIT11 + BIT15;			  		// Unipolar, Channel 1 Enable 
	
	while(1)
	{
		if((ADCSTA & 0x02) == 0x02)			// ADC Channel 1 data ready
		{
			return ADC1DAT;
		}
	}
}
