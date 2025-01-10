#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h" // for registers
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

int timestamp = 0;

// setup
// connect a jumper wire from PA5 tp PA6
// cause both functions as timers, PA5 in compare (creates events) and PA6 (capture the events)

int main()
{
	tim2_pa5_output_compare(); // creates a toggle pin each second.
	tim3_pa6_input_capture();  // "activate" and capture on rising edge (currenly)

	// we need to read the timer-status_register flag bit and when it's set, it means it captured an event.


	while(1)
	{
		// wait untill flag is capture
		while((TIM3->SR & TIMER_SR_CC1IF) ==  0) {}

		// read value
		timestamp = TIM3->CCR1; // CCR1 stands for capture/compare register.
		//  stores the timer counter value at the exact moment an external event occurs
		// (e.g., a rising or falling edge on a GPIO pin linked to the timer).
	}
}
