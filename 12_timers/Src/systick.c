#include "stm32f4xx.h" // for registers

#define SYS_CLK					(16000000)
#define MILI_SEC				(0.001) // 1/1000
#define SYSTICK_VAL_MILI		(SYS_CLK * MILI_SEC) // same as 16,000,000 / 1000 = 16,000

// by arm cortex m4 user guide, page.249
#define SYSTICK_EN				(1U << 0)
#define SYSTICK_CLK_SOURCE		(1U << 2) // use internal clock
#define SYSTICK_COUNT_FLAG		(1U << 16) // flag to check if timer finished

void SystickDelayMs(int n)
{
	// load with number of cycles per 1 milisecond
	// the timer "runs" this time X n
	SysTick->LOAD = SYSTICK_VAL_MILI;

	// clear systick current val register
	//  VAL register holds the current countdown value.
	SysTick->VAL = 0;

	// enable systick and select internal clock source;
	SysTick->CTRL = SYSTICK_EN | SYSTICK_CLK_SOURCE;

	// create the delay
	for(int i = 0; i < n; ++i)
	{
		// wait untill the count flag is set - means timer's done
		while((SysTick->CTRL & SYSTICK_COUNT_FLAG) == 0) {} // waits for 1 millisecond every time
	}

	// disable the timer
	SysTick->CTRL = 0;

}
