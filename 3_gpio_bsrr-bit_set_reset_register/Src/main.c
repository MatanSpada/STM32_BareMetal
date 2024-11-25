/*
 * This example shows how to:
 * - Enable the GPIOA peripheral clock.
 * - Configure pin PA5 as an output.
 * - Toggle the LED connected to PA5 by setting and resetting the pin
 *   using the Bit Set/Reset Register (BSRR).
 * - Introduce a simple delay loop to control the LED blink frequency.
 */

#include "stm32f4xx.h"


#define RCC_GPIOAEN			(1U << 0)
#define PIN5			(1U << 5)
#define LED_PIN			(PIN5)


int main()
{
	RCC->AHB1ENR |= RCC_GPIOAEN;

	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	while(1)
	{
		GPIOA->BSRR = LED_PIN;
		for(int i = 0; i < 1000000; ++i){}; // delay

		GPIOA->BSRR = (1U << 21);
		for(int i = 0; i < 1000000; ++i){}; // delay
	}
}
