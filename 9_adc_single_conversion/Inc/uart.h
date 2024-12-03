/*
 * uart.h
 *
 *  Created on: Nov 25, 2024
 *      Author: matan
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h" // for registers

//void uart2_tx_init(void);
char uart_read(void);
void uart_write(int c);
void uart2_rxtx_init(void);

#endif /* UART_H_ */
