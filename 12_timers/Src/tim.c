#include "stm32f4xx.h" // for registers
#include "tim.h"

#define TIM2EN			(1U << 0)
#define TIMX_CR1_CEN	(1U << 0)

// steps:
	// enable clock for timer2
	// set the prescaler value
	// set the auto-reload value
	// clear counter
	// enable timer

// 1 cycle/event per second
void tim2_1hz_init(void) // chose timer 2 which connected to APB1 BUS
{
	// enable clock for timer2
	RCC->APB1ENR |= TIM2EN;

	// set the prescaler value
	TIM2->PSC = 16000 - 1;

	// set the auto-reload value
	TIM2->ARR = 1000 - 1;

	// clear counter
	TIM2->CNT = 0;

	// enable timer
	TIM2->CR1 |= TIMX_CR1_CEN;

}
