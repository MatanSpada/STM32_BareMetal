#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h" // for registers
#include "uart.h"





int main()
{
	uart2_tx_init();

	while(1)
	{
		printf("hello, this is a sentence\n");
	}
}
