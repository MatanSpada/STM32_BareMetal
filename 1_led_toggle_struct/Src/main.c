#include <stdint.h>


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


#define __IO volatile // Misra C


/* for working with structs */
typedef struct
{
/*	  __IO uint32_t CR;              !< RCC clock control register,                                  Address offset: 0x00
	  __IO uint32_t PLLCFGR;         !< RCC PLL configuration register,                              Address offset: 0x04
	  __IO uint32_t CFGR;            !< RCC clock configuration register,                            Address offset: 0x08
	  __IO uint32_t CIR;             !< RCC clock interrupt register,                                Address offset: 0x0C
	  __IO uint32_t AHB1RSTR;        !< RCC AHB1 peripheral reset register,                          Address offset: 0x10
	  __IO uint32_t AHB2RSTR;        !< RCC AHB2 peripheral reset register,                          Address offset: 0x14
	  __IO uint32_t AHB3RSTR;        !< RCC AHB3 peripheral reset register,                          Address offset: 0x18
	  uint32_t RESERVED0;            !< Reserved, 0x1C                                                Address offset: 0x1C
	  __IO uint32_t APB1RSTR;        !< RCC APB1 peripheral reset register,                          Address offset: 0x20
	  __IO uint32_t APB2RSTR;        !< RCC APB2 peripheral reset register,                          Address offset: 0x24
	  uint32_t RESERVED1[2];         !< Reserved, 0x28-0x2C                                           */

	// the above replace with this dummy offset :
		volatile uint32_t dummy[12];

		volatile uint32_t AHB1ENR;         /*!< RCC AHB1 peripheral clock enable register,                   Address offset: 0x30 */

	  // not in use
/*	  __IO uint32_t AHB2ENR;         !< RCC AHB2 peripheral clock enable register,                   Address offset: 0x34
	  __IO uint32_t AHB3ENR;         !< RCC AHB3 peripheral clock enable register,                   Address offset: 0x38
	  uint32_t RESERVED2;            !< Reserved, 0x3C                                                Address offset: 0x3C
	  __IO uint32_t APB1ENR;         !< RCC APB1 peripheral clock enable register,                   Address offset: 0x40
	  __IO uint32_t APB2ENR;         !< RCC APB2 peripheral clock enable register,                   Address offset: 0x44
	  uint32_t RESERVED3[2];         !< Reserved, 0x48-0x4C
	  __IO uint32_t AHB1LPENR;       !< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50
	  __IO uint32_t AHB2LPENR;       !< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54
	  __IO uint32_t AHB3LPENR;       !< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58
	  uint32_t RESERVED4;            !< Reserved, 0x5C                                                Address offset: 0x5C
	  __IO uint32_t APB1LPENR;       !< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60
	  __IO uint32_t APB2LPENR;       !< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64
	  uint32_t RESERVED5[2];         !< Reserved, 0x68-0x6C
	  __IO uint32_t BDCR;            !< RCC Backup domain control register,                          Address offset: 0x70
	  __IO uint32_t CSR;             !< RCC clock control & status register,                         Address offset: 0x74
	  uint32_t RESERVED6[2];         !< Reserved, 0x78-0x7C
	  __IO uint32_t SSCGR;           !< RCC spread spectrum clock generation register,               Address offset: 0x80
	  __IO uint32_t PLLI2SCFGR;      !< RCC PLLI2S configuration register,                           Address offset: 0x84
	  uint32_t RESERVED7[1];         !< Reserved, 0x88
	  __IO uint32_t DCKCFGR;         !< RCC Dedicated Clocks configuration register,                 Address offset: 0x8C */
} RCC_t;



typedef struct
{
	volatile uint32_t MODER;		/* mode register				 offset: 0x00		*/
/*	__IO uint32_t OTYPER;		 output type register			 offset: 0x04
	__IO uint32_t OSPEEDR;		 output speed register		 offset: 0x08
	__IO uint32_t PUODR; 		 pull-up/pull-down register	 offset: 0x0C
	__IO uint32_t IDR;			 input data register			 offset: 0x10		*/

	// the above replace with this dummy offset :
	volatile uint32_t dummy[4];

	volatile uint32_t ODR;			/* output data register			 offset: 0x14		*/

	// no use
/*	__IO uint32_t BSRR;			 bit set/reset register		 offset: 0x18
	__IO uint32_t LCKR;			 configuration lock register 	 offset: 0x1C
	__IO uint32_t AFR[2];		 alternate function registers  offset: 0x20-0x24	*/
} GPIO_t;


/* typecast and fetch the addresses */
#define RCC			((RCC_t *) RCC_BASE)
#define GPIOA		((GPIO_t *) GPIOA_BASE)



int main()
{
	// 1. enable clock access to GPIOA.

	//RCC_AHB1_R |= (RCC_GPIOAEN);
	// or with struct method:
	RCC->AHB1ENR |= RCC_GPIOAEN;

	// 2. set PA5 to output pin (using the MODE) according to datasheet

	// GPIOA_MODE_R |= (1U << 10); // set bit 10 to 1
	// GPIOA_MODE_R &= ~(1U << 11); // set bit 11 to 0

	// or with struct method:
	GPIOA->MODER |= (1U << 10); // set bit 10 to 1
	GPIOA->MODER &= ~(1U << 11); // set bit 11 to 0

	while(1)
	{
/*
		// 3. Set PA5 to HIGE - set led on
		GPIOA_OD_R |= LED_PIN;

		// 4. Set led to toggle
		GPIOA_OD_R ^= LED_PIN;
*/


		//  Set led to toggle with the struct method
		GPIOA->ODR ^= LED_PIN;

		for(int i = 0; i < 10000000; ++i){}; // delay
	}
}









