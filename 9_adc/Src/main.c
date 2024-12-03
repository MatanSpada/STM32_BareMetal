#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h" // for registers
#include "uart.h"

#define RCC_GPIOAEN		(1U << 0)
#define LED_PIN			(1U << 5)

char c;

int main()
{
	RCC->AHB1ENR |= RCC_GPIOAEN;		// enable clock to GPIO port A
	GPIOA->MODER |= (1U << 10);			// set mode for pin 5 to output
	GPIOA->MODER &= ~(1U << 11);

	uart2_rxtx_init();					// init uart

	while(1)
	{
		c = uart_read();
		if(c == '1')
		{
			GPIOA->ODR |= LED_PIN;
			//uart_write(c);
		}
		else if (c != '\n' && c != '\r') // Ignore newline and carriage return
		{
			GPIOA->ODR &= ~LED_PIN; // Turn LED OFF for other characters
			uart_write(c);          // Echo the character (if needed)
		}
	}
}
