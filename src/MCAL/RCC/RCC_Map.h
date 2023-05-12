/*************************************************************
 *
 * Filename: IO_Map.h
 * Description: Macro definitions of the relevant I/O registers in the RCC module,
 * 					in the STM32F401CC.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 *
 *************************************************************/

#ifndef __RCC_MAP_H__
#define __RCC_MAP_H__

#include "Std_Types.h"


/*************************************************************
 * Description: Register layout of the RCC module.
 *
 *************************************************************/
typedef struct {
	uint32_t CR;
	uint32_t PLLCFGR;
	uint32_t CFGR;
	uint32_t CIR;

	uint32_t AHB1RSTR;
	uint32_t AHB2RSTR;

	uint32_t RESERVED0[2];

	uint32_t APB1RSTR;
	uint32_t APB2RSTR;

	uint32_t RESERVED1[2];

	uint32_t AHB1ENR;
	uint32_t AHB2ENR;

	uint32_t RESERVED2[2];

	uint32_t APB1ENR;
	uint32_t APB2ENR;

	uint32_t RESERVED3[2];

	uint32_t AHB1LPENR;
	uint32_t AHB2LPENR;

	uint32_t RESERVED4[2];

	uint32_t APB1LPENR;
	uint32_t APB2LPENR;

	uint32_t RESERVED5[2];

	uint32_t BDCR;
	uint32_t CSR;

	uint32_t RESERVED6[2];

	uint32_t SSCGR;
	uint32_t PLLI2SCFGR;

	uint32_t RESERVED7[1];

	uint32_t DCKCFGR;
} __attribute__((packed, aligned(4))) RCC_t;



/*************************************************************
 * Description: Bit layout of the RCC_CR register.
 *
 *************************************************************/
#define PLLRDY						25
#define PLLON						24

#define CSSON						19

#define HSEBYP						18
#define HSERDY						17
#define HSEON						16

#define HSIRDY						1
#define HSION						0



/*************************************************************
 * Description: Bit layout of the RCC_PLLCFGR register.
 *
 *************************************************************/
#define PLLQ3						27
#define PLLQ2						26
#define PLLQ1						25
#define PLLQ0						24

#define PLLSRC						22

#define PLLP1						17
#define PLLP0						16

#define PLLN8						14
#define PLLN7						13
#define PLLN6						12
#define PLLN5						11
#define PLLN4						10
#define PLLN3						9
#define PLLN2						8
#define PLLN1						7
#define PLLN0						6

#define PLLM5						5
#define PLLM4						4
#define PLLM3						3
#define PLLM2						2
#define PLLM1						1
#define PLLM0						0



/*************************************************************
 * Description: Bit layout of the RCC_CFGR register.
 *
 *************************************************************/
#define	PPRE22						15
#define PPRE21						14
#define PPRE20						13

#define PPRE12						12
#define PPRE11						11
#define PPRE10						10

#define HPRE3						7
#define HPRE2						6
#define HPRE1						5
#define HPRE0						4

#define SWS1						3
#define SWS0						2

#define SW1							1
#define SW0							0



/*************************************************************
 * Description: Bit layout of the RCC_AHB1ENR register.
 *
 *************************************************************/
#define DMA2EN						22
#define DMA1EN						21

#define CRCEN						12

#define GPIOHEN						7
#define GPIOEEN						4
#define GPIODEN						3
#define GPIOCEN						2
#define GPIOBEN						1
#define GPIOAEN						0



/*************************************************************
 * Description: Bit layout of the RCC_AHB2ENR register.
 *
 *************************************************************/
#define OTGFSEN						7



/*************************************************************
 * Description: Bit layout of the RCC_APB1ENR register.
 *
 *************************************************************/
#define PWREN						28

#define I2C3EN						23
#define I2C2EN						22
#define I2C1EN						21

#define USART2EN					17

#define SPI3EN						15
#define SPI2EN						14

#define WWDGEN						11

#define TIM5EN						3
#define TIM4EN						2
#define TIM3EN						1
#define TIM2EN						0



/*************************************************************
 * Description: Bit layout of the RCC_APB2ENR register.
 *
 *************************************************************/
#define TIM11EN						18
#define TIM10EN						17
#define TIM9EN						16

#define SYSCFGEN					14
#define SPI4EN						13
#define SPI1EN						12

#define SDIOEN						11

#define ADC1EN						8

#define USART6EN					5
#define USART1EN					4

#define TIM1EN						0



/*************************************************************
 * Description: Bit layout of the RCC_DCKCFGR register.
 *
 *************************************************************/
#define TIMPRE						24



/*************************************************************
 * Description: Base address of RCC module in the uC.
 *
 *************************************************************/
#define	RCC_BASE					0x40023800



/*************************************************************
 * Description: Structure pointer-macro to RCC module.
 *
 *************************************************************/
#define RCC 				((volatile RCC_t *) RCC_BASE)


#endif /* __RCC_MAP_H__ */
