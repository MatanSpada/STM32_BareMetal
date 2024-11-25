// where is the led connected?
// what is the port and pin?
// according to the nucleo_user_guide:
// port: A
// pin: 5

// gpio's are available through a BUS.
// APB - Advancede Peripheral Bus.
// AHPB - Advanced High Preformance Bus.
// Bus provides clock.
// in this case, GPIO PORT A is connected to AHPB1.
// therefore, we need to access this gpio through this bus.
// we define bus base (AHBP1) and then offset.
// than we need to enable the clock for this bus rcc (resetting clock control).
// each bus has its own RCC module address, that can be found in the bus's addr range.
// we define the RCC
//
// mode - which mode we need for the pin? input/output/analog/alternate?
// alternate means - uart/spi/i2c pin

// *(volatile unsigned int *) - this is requierd in order to write to this address.
// first we tell the compiler that this is an address and than, we want to dereference it to be able to write.

// reference manual - registers and the meaning of every bit in them
// data sheet -
// user guide -

#define PERIPHERAL_BASE		(0x40000000UL)

#define OFFSET_TO_AHB1 	    (0x00020000UL)
#define AHB1_BASE			(PERIPHERAL_BASE + OFFSET_TO_AHB1) // 0x40020000

#define OFFSET_TO_GPIOA		(0x0UL)
#define GPIOA_BASE			(AHB1_BASE + OFFSET_TO_GPIOA)

#define OFFSET_TO_RCC		(0x00003800UL) // offset from start addr of bus AHPB1;
#define RCC_BASE			(AHB1_BASE + OFFSET_TO_RCC) // enable clock control

// within the rcc address, go to bus1's enable-register
#define OFFSET_TO_AHB1EN_R	(0x30UL) 					// RCC offset to get to bus1 register to enable the clock
#define RCC_AHB1_R			(*(volatile unsigned int *)(RCC_BASE + OFFSET_TO_AHB1EN_R)) // RCC register fo BUS1

#define OFFSET_TO_GPIO_MODE	(0X00UL)						// mode of each port pins
#define GPIOA_MODE_R		(*(volatile unsigned int *)(GPIOA_BASE + OFFSET_TO_GPIO_MODE))

#define OFFSET_TO_GPIO_ODR_R (0x14)	// output data register offset
#define GPIOA_OD_R 			(*(volatile unsigned int *)(GPIOA_BASE + OFFSET_TO_GPIO_ODR_R)) // output data register

#define PIN_5 				(1U << 5)
#define LED_PIN 			(PIN_5)

#define RCC_GPIOAEN				(1UL << 0) // GPIOAEN - gpio A enable


int main()
{
	// 1. enable clock access to GPIOA.
	RCC_AHB1_R |= (RCC_GPIOAEN);

	// 2. set PA5 to output pin (using the MODE)
	GPIOA_MODE_R |= (1U << 10); // set bit 10 to 1
	GPIOA_MODE_R &= ~(1U << 11); // set bit 11 to 0

	while(1)
	{
		// 3. Set PA5 to HIGE - set led on
		// GPIOA_OD_R |= LED_PIN;

		// 4. toggle
		GPIOA_OD_R ^= LED_PIN;

		for(int i = 0; i < 100000; ++i){}; // delay
	}
}









