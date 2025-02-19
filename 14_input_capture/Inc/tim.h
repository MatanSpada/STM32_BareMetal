/*
 * tim.h
 *
 *  Created on: Dec 12, 2024
 *      Author: matan
 */

#ifndef TIM_H_
#define TIM_H_

#define TIMX_SR_UIF		(1U << 0)
#define TIMER_SR_CC1IF	(1U << 1)	// timer status register capture/compare ch1 interupt flag

void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);
void tim3_pa6_input_capture(void);

#endif /* TIM_H_ */
