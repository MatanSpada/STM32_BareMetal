#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void pa1_adc_init(void);	// specific to channel 1, coresponding to pin PA1.
void adc_start_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
