#include "stm32f4xx.h" // for registers
#include "adc.h"


#define ADCEN 			(1U << 8) // for clock
#define RCC_GPIOAEN		(1U << 0)
#define PA1				(1)
#define MODER_BITS  	(2)
#define ADC_CH1			(1U << 0)
#define ADC_SEQ_LEN		(0X00) // By tr ref-man p.236, writing 0 to bits 20-23 equals to: len(channel number)= 1
#define ADC1_CR2_ADON	(1U << 0)	// enable adc - ADC - ON
#define ADC1_CR2_SWSTART	(1U << 30)	// Software start - ADC starts conversion
#define ADC1_SR_EOC		(1U << 1)	// adc status register - end of conversion flag

// adc1_1 (adc 1 channel 1) corresponding to PA1, so:
void pa1_adc_init(void)
{
	/***configure the ADC GPIO pin ***/

	// enable clock to adc port GPIOA
	RCC->AHB1ENR |= RCC_GPIOAEN;

	// set the mode of PA1 to analog
	GPIOA->MODER |= (3U << (MODER_BITS * PA1));
	/*
	 * GPIPA->MODER |= (1U << 2);
	 * GPIPA->MODER |= (1U << 3);
	 */

	/***configure the ADC module ***/

	// enable clock access to ADC
	RCC->APB2ENR |= ADCEN;

	// sequence registers - SQR3
	// SQR3 - cause the sequence starts from here sq1 - sq16 (16 channels)
	// this register is responsible for the order of the channels
	// each "port" in the register has 5 bits.
	// if we want to sample ch5, then ch2, then ch3, we'll write the channle number
	// into the relevant port: 0x5 to "port" SQ1, 0x2 to "port" SQ2, 0x3 to "port" SQ3.

	//the sequence of channels must be contiguous.
	//that's why we need to specify the start and the size of the sequence.

	// start channel - put 0x01/0001 (ch1) into the full register.
	// we use only "port1" of the reg so  it's ok.
	ADC1->SQR3 = ADC_CH1; // no |= cause we want to init the other channels we dont use

	// len/size
	ADC1->SQR1 = ADC_SEQ_LEN; // write the len (number of channels)we dont use ADC_SQR1, so we can just assign 0 to the register, instead on just "port" L (bits 20-23).

	/********* make sure u know how multiple channles setting looks like *******/

	// enable ADC module - by the ref-man p.232 and 234 ADON - CR2 - control register
	ADC1->CR2 |= ADC1_CR2_ADON;
}

void adc_start_conversion(void)
{
	// start conversion - in the CR2 we look for SWSTART - software start, bit30
	ADC1->CR2 |= ADC1_CR2_SWSTART;
}

uint32_t adc_read(void)
{
	// wait for conversion to be complete
	while((ADC1->SR & ADC1_SR_EOC) == 0) {}

	// read converted result
	return (ADC1->DR);	// data register
}




