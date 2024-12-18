#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h" // for registers
#include "uart.h"
#include "adc.h"
#include "systick.h"

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

	while(1)
	{
		printf("a second passed!\n\r");
		GPIOA->ODR ^= LED_PIN;

		SystickDelayMs(1000);
		//for(int i = 0; i < 1000000; ++i){}; // delay
	}
}
