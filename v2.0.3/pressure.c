/************************************************************************************************
 Author        : Jordan Baczuk
 Date          : March 19 2018
 File          : pressure.c
 Hardware      : ADUC7060
 Description   : Pressure functions
 Revision			 : v2.0
*************************************************************************************************/


//#include "adg729.h"
#include "config.h"
//#include "pressure.h"
#include "adc.h"


typedef struct {
	// All int values are actually 24 bits (see adc spec)
	int pressure_1;
	int pressure_2;
	int pressure_3;
	int pressure_4;
	
	int temperature_1;
	int temperature_2;
	int temperature_3;
	int temperature_4;
	
	int battery_voltage;
} mudmax_raw_data;

void readPressureSensor(mudmax_raw_data *buffer, int sensor)
{
	int adc0;
	int adc1;
	int adc1_channel = 0;
	int DP_POS = 0;
	int DP_NEG = 0;
	int Temp1 = 0;
	int Temp2 = 0;
	
	// Set ADC input based on the sensor
	switch(sensor)
	{
		case 1:
			adc1_channel = CH1_ADC6;
			break;
		case 2:
			adc1_channel = CH1_ADC7;
			break;
		case 3:
			adc1_channel = CH1_ADC8;
			break;
		case 4:
			adc1_channel = CH1_ADC9;
			break;
		default:
			break;
	}
	
	//readAdcChannels(&adc0, &adc1, CH0_ADC1, adc1_channel); // Clear ADC0DAT buffer

	// Set MUX to the channel corresponding to the sensor
	// FIXME: This is keeping the uC from going to sleep even if a sleep() is issued
	adg729_select_ch_pair(ADG729_I2C_ADDR, sensor);
			
	// Clear buffer
	readAdcChannels(&adc0, &adc1, CH0_ADC1, adc1_channel);
	DP_POS = adc0;
	Temp1 = adc1;
	
	// Read positive side of sensor
	//readAdcChannels(adc_buffer, CH0_ADC0, adc1_channel); // pos and neg outputs were switched on schematic
	readAdcChannels(&adc0, &adc1, CH0_ADC1, adc1_channel);
	DP_POS = adc0;
	Temp1 = adc1;
	
	// Read negative side of sensor
	//readAdcChannels(adc_buffer, CH0_ADC1, adc1_channel); // pos and neg outputs were switched on schematic
	readAdcChannels(&adc0, &adc1, CH0_ADC0, adc1_channel);
	DP_NEG = adc0;
	Temp2 = adc1;
	
	switch(sensor)
	{
		case 1:
			buffer -> pressure_1 = DP_POS - DP_NEG; 				// Get differential pressure value
			buffer -> temperature_1 = (Temp1 + Temp2) / 2; 	// Average temperature reading
			break;
		case 2:
			buffer -> pressure_2 = DP_POS - DP_NEG; 				// Get differential pressure value
			buffer -> temperature_2 = (Temp1 + Temp2) / 2; 	// Average temperature reading
			break;
		case 3:
			buffer -> pressure_3 = DP_POS - DP_NEG; 				// Get differential pressure value
			buffer -> temperature_3 = (Temp1 + Temp2) / 2; 	// Average temperature reading
			break;
		case 4:
			buffer -> pressure_4 = DP_POS - DP_NEG; 				// Get differential pressure value
			buffer -> temperature_4 = (Temp1 + Temp2) / 2; 	// Average temperature reading
			break;
		default:
			break;
	}
}
