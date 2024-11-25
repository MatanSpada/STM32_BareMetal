/*
 * This example demonstrates:
 * - Enabling the GPIOA peripheral clock.
 * - Configuring pin PA5 as an output pin.
 * - Toggling the LED connected to PA5 using the Output Data Register (ODR).
 * - Implementing a delay loop to control the LED blink frequency.
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
		GPIOA->ODR ^= LED_PIN;

		for(int i = 0; i < 1000000; ++i){}; // delay
	}
}
