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

	while(1)
	{
		adc_start_conversion(); // basically this should be above the loop for 1 conversion.
		sensor_value = adc_read();
		printf("value: %lu\n", sensor_value);
	}
}
