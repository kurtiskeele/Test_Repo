/************************************************************************************************
 Author        : Jordan Baczuk
 Date          : March 19 2018
 File          : pressure.h
 Hardware      : ADUC7060
 Description   : Pressure functions
 Revision			 : v2.0
*************************************************************************************************/

#ifndef _PRESSURE_H__
#define _PRESSURE_H__

#include <stdint.h>

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

void readPressureSensor(mudmax_raw_data *buffer, int sensor);

#endif // _PRESSURE_H__
