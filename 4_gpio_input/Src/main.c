/*
 * In this example we want the push button on the nucleo board to function as an input.
 * That's why we need to search in the "nucleo_user_guide".
 * In the section "Push-buttons" on page 23 we can see that the user-button is connected to pc13: GPIOC pin 13.
 * First we need to enable the clock for this port, so we check in the data sheet (block diagram), which bus has this port.
 * Bus AHB1. now we search in the reference manual to see which bits in AHB1-enable registration is required.
 * we look for ahb1enr - advanced high performance bus 1. enable register (RCC_AHB1ENR).
 * we need to write to bit number 2.
 *
 *
 */

#include "stm32f4xx.h"


#define RCC_GPIOAEN			(1U << 0)
#define RCC_GPIOCEN			(1U << 2) // by the chart: A=0, B=1, C=2...

#define PIN5				(1U << 5)
#define PIN13				(1U << 13)

#define LED_PIN				(PIN5)
#define BUTTON_PIN			(PIN13)

int main()
{
	// LED is on by default.
	// when we press the button - it turns off.

	// Ebable clock access to GPIOA and GPIOC
	RCC->AHB1ENR |= RCC_GPIOAEN;
	RCC->AHB1ENR |= RCC_GPIOCEN;

	// Set PA5 as output pin (LED)
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	// Set PC13 as input pin (BUTTON)
	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 26); // both zero's

	// active low button means: initially high, when pressed it turns low
	// it means that to detect a press, need to detect a low signal
	// IDR - input data register - stores the output of the input data
	while(1)
	{
		if(GPIOC->IDR & BUTTON_PIN ) // if button pressed
		{
			// set the LED
			GPIOA->BSRR = LED_PIN;
		}
		else
		{
			// unset the LED
			GPIOA->BSRR = (1U << 21);
		}

	}
}
