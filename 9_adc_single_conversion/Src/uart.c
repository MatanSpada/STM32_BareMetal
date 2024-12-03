/*
 * uart.c
 *
 *  Created on: Nov 25, 2024
 *      Author: matan
 */

#include "uart.h"

#define RCC_GPIOAEN			(1U << 0)
#define UART2EN 			(1U << 17) // we chose uart2 instead of 1 cause it's conected to the USB (where it's written?)
#define SYS_FREQ			(16000000) // MHrz
#define APB1_CLK			(SYS_FREQ)
#define UART_BAUDRATE		(115200)

#define CR1_TE				(1U << 3)  // control register 1 - transmitter enabled
#define CR1_RE				(1U << 2)  // control register 1 - reciever enabled
#define CR1_UE				(1U << 13) // control register 1 - UART enabled
#define SR1_TXE				(1U << 7)  // status register - tx (transmit) data register empty
#define SR1_RXNE			(1U << 5)  // status register - rx not empty


static void UartSetBaudrate(USART_TypeDef *USARTx, uint32_t periph_clock, uint32_t baudrate);
static uint16_t ComputeUart(uint32_t periph_clock, uint32_t baudrate);

void uart2_rxtx_init(void) // PA2-tx and PA3-rx
{
	/****** configure UART GPIO pin *******/

	// enable clock to GPIOA (cause PA2 and PA3 are the UART pins)
	RCC->AHB1ENR |= RCC_GPIOAEN;

	// set PA2 mode to Alternate function mode
	// by page 158 reference manual, MODER, to set pin 2 in port A to uart, we need to set it to an alternate.
	// by the description, we need to set bit's 4 and 5 in MODER(mode register) (MODER2) to 10.
	GPIOA->MODER &= ~(1U << 4); // MODER2
	GPIOA->MODER |= (1U << 5); 	// MODER2

	// set PA2 Alternate function type to UART_TX (AF07 - by table 9 in datasheet).
	// by the reference manual on page 162 (8.4.9) we'll choose AFRL2 cause we need PA2.
	// it means we need to change bits: 8-11. to what? according to the alternate function's type,
	// which is: AF7 - as we already know from the prev section - 0111
	// we go to the gpioa resposible register: AF (alternate function) - 0 = low (0-7), 1 = high (8-15)
	GPIOA->AFR[0] |= (1UL << 8);
	GPIOA->AFR[0] |= (1UL << 9);
	GPIOA->AFR[0] |= (1UL << 10);
	GPIOA->AFR[0] &= ~(1UL << 11);


	// set PA3 mode to Alternate function mode
	GPIOA->MODER &= ~(1U << 6); // MODER3
	GPIOA->MODER |= (1U << 7); 	// MODER3


	// set PA2 Alternate function type to UART_RX (AF07 - by table 9 in datasheet).
	GPIOA->AFR[0] |= (1UL << 12);
	GPIOA->AFR[0] |= (1UL << 13);
	GPIOA->AFR[0] |= (1UL << 14);
	GPIOA->AFR[0] &= ~(1UL << 15);

	/****** configure UART settings *******/
	// enable clock to UART2 (?) to this gpio
	RCC->APB1ENR |= UART2EN;

	// configure baud rate
	UartSetBaudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// configure transfer direction - with USART_CR1 - control register (why 1?)
	// TE - transmitter enable.
	// RA - receiver enable.
	// go to "USART2_CR1" in reference manual and look for TE(bit 3) and RE(bit 2) and make a macro for them.

	USART2->CR1 = CR1_TE | CR1_RE; // = cause we wanna set all the other bits to 0 (pairity bit, length...) cause 0 is the default

	// enable UART (?)
	USART2->CR1 |= CR1_UE; // |= cause we add to prev conf.

}

void uart2_tx_init(void) // PA2
{
	/****** configure UART GPIO pin *******/

	// enable clock to GPIOA (cause PA2 and PA3 are the UART pins)
	RCC->AHB1ENR |= RCC_GPIOAEN;

	// set PA2 mode to Alternate function mode
	// by page 157 datasheet, MODER, to set pin 2 in port A to uart, we need to set it to an alternate.
	// by the description, we need to set bit's 4 and 5 in MODER(mode register) (MODER2) to 10.
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);

	// set PA2 Alternate function type to UART_TX (AF07 - by table 9 in datasheet).
	// by the reference manual on page 161 (8.4.9) we'll choose AFRL2 cause we need PA2.
	// it means we need to change bits: 8-11. to what? according to the alternate function's type,
	// which is: AF7 - as we already know from the prev section - 0111
	// we go to the gpioa resposible register: AF (alternate function) - 0 = low (0-7), 1 = high (8-15)
	GPIOA->AFR[0] |= (1UL << 8);
	GPIOA->AFR[0] |= (1UL << 9);
	GPIOA->AFR[0] |= (1UL << 10);
	GPIOA->AFR[0] &= ~(1UL << 11);

	/****** configure UART settings *******/
	// enable clock to UART2 (?) to this gpio
	RCC->APB1ENR |= UART2EN;

	// configure baud rate
	UartSetBaudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// configure transfer direction - with USART_CR1 - control register (why 1?)
	USART2->CR1 = (CR1_TE | CR1_RE); // = cause we set all other bits to 0 (pairity bit, length...)

	// enable UART (?)
	USART2->CR1 |= CR1_UE; // |= cause we add to prev conf.

}

void uart_write(int c)
{
	/* make sure the transmit data register is empty */
	// we need to wait fot the status register to be empty, so we need to check it
	while(!(USART2->SR & SR1_TXE)) {} // while SR1_TXE is not empty (there's still a set bit)

	/* write to transmit data register */
	USART2->DR = c & 0xFF; // D1 - data register
}

char uart_read(void)
{
	/* make sure the recieve data register is not empty */
	// we need to wait fot the status register in bit number 5 to be not-empty, so we need to check it
	//RXNT - receiver not empty
	while((USART2->SR & SR1_RXNE) == 0) {} // while SR1_TXE is not empty (there's still a set bit)

	return USART2->DR; //  data register
}




/******** Auxiliary functions *********/

static uint16_t ComputeUart(uint32_t periph_clock, uint32_t baudrate)
{
	return ((periph_clock + (baudrate/2U))/baudrate);
}

static void UartSetBaudrate(USART_TypeDef *USARTx, uint32_t periph_clock, uint32_t baudrate)
{
	// BRR - baud rate register
	USARTx->BRR = ComputeUart(periph_clock, baudrate);
}


// for printf function
int __io_putchar(int c)
{
	uart_write(c);
	return c;
}
