/************************************************************************************************
 Author        : Jordan Baczuk
 Date          : 2018/3/22
 File          : aduc7060_helpers.h
 Hardware      : ADuC7060
 Description   : Configuration of common aduc7060 registers and some helpers
 Revision      : Revision 2.0
*************************************************************************************************/

#ifndef __aduc7060_helpers_h
#define __aduc7060_helpers_h

#include <stdint.h>

// Bit Definitions
#define BIT0  0x01
#define BIT1  0x02
#define BIT2  0x04
#define BIT3  0x08
#define BIT4  0x10
#define BIT5  0x20
#define BIT6  0x40
#define BIT7  0x80
#define BIT8  0x100
#define BIT9  0x200
#define BIT10 0x400
#define BIT11 0x800
#define BIT12 0x1000
#define BIT13 0x2000
#define BIT14 0x4000
#define BIT15 0x8000
#define BIT16 0x10000
#define BIT17 0x20000
#define BIT18 0x40000
#define BIT19 0x80000
#define BIT20 0x100000
#define BIT21 0x200000
#define BIT22 0x400000
#define BIT23 0x800000
#define BIT24 0x1000000
#define BIT25 0x2000000
#define BIT26 0x4000000
#define BIT27 0x8000000
#define BIT28 0x10000000
#define BIT29 0x20000000
#define BIT30 0x40000000

// I2C
#define ADG729_I2C_ADDR		0x44
#define I2C_WRITE	0x0
#define I2C_READ	BIT0

// Mux channels
#define S1A		BIT0
#define S2A		BIT1
#define S3A		BIT2
#define S4A		BIT3
#define S1B		BIT4
#define S2B		BIT5
#define S3B		BIT6
#define S4B		BIT7

void initGpio(void);
void initInterrupts(void);
void initI2C(void);
void initAdc(void);
void initUart(void);
void sleep(void);
void wake(void);
void turn_on_led(void);
void turn_off_led(void);
void turn_on_avdd(void);
void turn_off_avdd(void); 
/**
 * @brief Enable mux channels for sensor #
 * @param mux_channels channel bits S1A through S4B, 0 for none
 * @example enables S1A and S1B on mux:
 * @example enable_sensor_channel(S1A + S1B);
 */
void enable_mux_channel(uint8_t mux_channels);
	
	


#endif
