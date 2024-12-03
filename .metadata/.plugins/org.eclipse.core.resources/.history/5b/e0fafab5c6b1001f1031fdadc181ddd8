#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h" // for registers
#include "uart.h"
#include "adc.h"

uint32_t sensor_value;

int main()
{
	uart2_rxtx_init();

	pa1_adc_init();
	adc_start_conversion();

	while(1)
	{
		sensor_value = adc_read();
		printf("value: %lu\n", sensor_value);
	}
}
