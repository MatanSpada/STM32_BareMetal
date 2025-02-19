#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h" // for registers
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

#define GPIOA_EN		(1U << 0)
#define PA5				(1U << 5)
#define LED_PIN			(PA5)

int main()
{
	// enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOA_EN;

	// set PA5 as output
	GPIOA->MODER |=   (1U << 10);
	GPIOA->MODER &=  ~(1U << 11);

	uart2_rxtx_init();
	tim2_1hz_init();

	while(1)
	{
		// wait for UIF
		while((TIM2->SR & TIMX_SR_UIF) == 0) {} // can be written as an API func

		//clear flag
		TIM2->SR &= ~TIMX_SR_UIF;

		printf("a second passed!\n\r");
		GPIOA->ODR ^= LED_PIN;
	}
}
