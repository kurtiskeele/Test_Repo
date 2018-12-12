/************************************************************************************************
 Author        : Jordan Baczuk
 Date          : 2018/3/22
 File          : interrupt_handlers.c
 Hardware      : ADuC7060
 Description   : MudMax Transmitter Firmware Interrupt Handlers
 Revision      : v2.0
*************************************************************************************************/

#include "interrupt_handlers.h"
#include "aduc7060_helpers.h"
#include "adc.h"
#ifndef __aduc7060_h
#define __aduc7060_h
	#include <aduc7060.h>
#endif
#include "stdio.h"
#include "string.h"

void delay(int delay)
{
	int i;
	for(i=0; i<delay; i++){}
}



int timer1_handler(int power_saving_mode_en)
{	
	int cycles = 500;
	mudmax_raw_data buffer;		//ADC_Data;
	int adc0;
	int adc1;
	int DP_POS = 0;
	int DP_NEG = 0;
	int Temp = 0;
	unsigned char szTemp[1024] = "";
	unsigned char nLen = 0;
	unsigned int xbee_cts = 0;
	int i;
		
	T1CON &= ~BIT7;							// disable timer1
	
	wake();
	turn_on_led();
	turn_on_avdd();
	initAdc();
	
	enable_mux_channel(0);
	delay(cycles); // TODO: make this asynchronous
	
	enable_mux_channel(S1A + S1B);
	//delay(cycles); // TODO: make this asynchronous
	// actual delay before writing i2c again is about 12ms
	{
		// Read positive side of sensor
		readAdcChannels(&adc0, &adc1, CH0_ADC1, CH1_ADC6);
		DP_POS = adc0;
		Temp = adc1;
		
		// Read negative side of sensor
		readAdcChannels(&adc0, &adc1, CH0_ADC0, CH1_ADC6);
		DP_NEG = adc0;
		Temp = adc1;

		buffer.pressure_1 = DP_POS - DP_NEG; 				// Get differential pressure value
		buffer.temperature_1 = Temp;
	}
	
	enable_mux_channel(S2A + S2B);
	//delay(cycles); // TODO: make this asynchronous
	// actual delay before writing i2c again is about 9.5ms
	{
		// Read positive side of sensor
		readAdcChannels(&adc0, &adc1, CH0_ADC1, CH1_ADC7);
		DP_POS = adc0;
		Temp = adc1;
		
		// Read negative side of sensor
		readAdcChannels(&adc0, &adc1, CH0_ADC0, CH1_ADC7);
		DP_NEG = adc0;
		Temp = adc1;

		buffer.pressure_2 = DP_POS - DP_NEG; 				// Get differential pressure value
		buffer.temperature_2 = Temp;
	}
	
	enable_mux_channel(S3A + S3B);
	//delay(cycles); // TODO: make this asynchronous
	// actual delay before writing i2c again is about 9.5ms
	{
		// Read positive side of sensor
		readAdcChannels(&adc0, &adc1, CH0_ADC1, CH1_ADC8);
		DP_POS = adc0;
		Temp = adc1;
		
		// Read negative side of sensor
		readAdcChannels(&adc0, &adc1, CH0_ADC0, CH1_ADC8);
		DP_NEG = adc0;
		Temp = adc1;

		buffer.pressure_3 = DP_POS - DP_NEG; 				// Get differential pressure value
		buffer.temperature_3 = Temp;
	}
	
	enable_mux_channel(S4A + S4B);
	//delay(cycles); // TODO: make this asynchronous
	// actual delay before writing i2c again is about 9.5ms
	{
		// Read positive side of sensor
		readAdcChannels(&adc0, &adc1, CH0_ADC1, CH1_ADC9);
		readAdcChannels(&adc0, &adc1, CH0_ADC1, CH1_ADC9);
		DP_POS = adc0;
		Temp = adc1;
		
		// Read negative side of sensor
		readAdcChannels(&adc0, &adc1, CH0_ADC0, CH1_ADC9);
		DP_NEG = adc0;
		Temp = adc1;

		buffer.pressure_4 = DP_POS - DP_NEG; 				// Get differential pressure value
		buffer.temperature_4 = Temp;
	}
	
	enable_mux_channel(0);
	//delay(cycles); // TODO: make this asynchronous
	buffer.battery_voltage = readAdc1Channel(CH1_ADC4);
	
	enable_mux_channel(0);
	//delay(cycles); // TODO: make this asynchronous
	buffer.Die_Temperature = readAdc1Channel(CH1_DieTmp);
	
	sprintf ( (char*)szTemp, "Data - D1: %d T1: %i D2: %i T2: %i D3: %i T3: %i D4: %i T4: %i V: %i Td: %i \r\n", 
		buffer.pressure_1, buffer.temperature_1, buffer.pressure_2, buffer.temperature_2, buffer.pressure_3, buffer.temperature_3, buffer.pressure_4, buffer.temperature_4, 
		buffer.battery_voltage, buffer.Die_Temperature);
	//sprintf ( (char*)szTemp, "Test String\n");
	nLen = strlen((char*)szTemp);
	// Using XBEE cyclic sleep
	xbee_cts = !(GP0DAT & BIT6);
	while(!xbee_cts) // Wait for CTS from XBEE
	{
		xbee_cts = !(GP0DAT & BIT6);
	} 
	xbee_cts = 0;
	for ( i = 0 ; i < nLen ; i++ )	// loop to send opening String
	{
		 COMTX = szTemp[i];
		 while ((COMSTA0 & 0x40) == 0x00){}	  // Wait for Tx buffer empty bit to be set
	}
			
	//digital_write(LED_REG, LOW);
	T1CON |= BIT7;		// enable timer1
	
//	if(power_saving_mode_en)
//	{
//		turn_off_led();
//		turn_off_avdd();
//	}
	return 0;
}
