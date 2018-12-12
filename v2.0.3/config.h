/************************************************************************************************
 Author        : Jordan Baczuk
 Date          : 2018/3/22
 File          : config.h
 Hardware      : ADuC7060
 Description   : Configuration of common aduc7060 registers and some helpers
 Revision      : v2.0
*************************************************************************************************/

#ifndef __config_h
#define __config_h

#include "aduc7060_helpers.h"

#define ADG729_I2C_ADDR		0x44
#define LED_REG						BIT21
#define AVDD_REG					BIT20
#define XBEE_PWR_REG			BIT22

unsigned long setIRQEN(void);
unsigned long setIRQCONE(void);
unsigned long setT1CON(void);

#endif // __config_h
