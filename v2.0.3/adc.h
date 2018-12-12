/************************************************************************************************
 Author        : Jordan Baczuk
 Date          : March 19 2018
 File          : adc.h
 Hardware      : ADuC7060
 Description   : ADC functions
 Revision			 : v2.0
*************************************************************************************************/

/* ADC Register values */
// ADC0CH Single Ended Mode
#define CH0_ADC0		0x01 // 0b0001
#define	CH0_ADC1		0x02 // 0b0010
#define CH0_ADC2		0x06 // 0b0110
#define CH0_ADC3		0x07 // 0b0111

// ADC1CH Single Ended Mode
#define CH1_ADC2		0x04 // 0b0100
#define CH1_ADC3		0x05 // 0b0101
#define CH1_ADC4		0x06 // 0b0110
#define CH1_ADC6		0x07 // 0b0111
#define CH1_ADC7		0x08 // 0b1000
#define CH1_ADC8		0x09 // 0b1001
#define CH1_ADC9		0x0A // 0b1010
#define CH1_DieTmp	0x0B // 0b1011

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
	
	int Die_Temperature;
} mudmax_raw_data;

void readAdcChannels(int *adc0, int *adc1, unsigned int ADC0Chan, unsigned int ADC1Chan);
int readAdc0Channel(unsigned int ADC0Chan);
int readAdc1Channel(unsigned int ADC1Chan);
