/*************************************************************
 * 
 * Filename: GPIO_Map.h
 * Description: Register map header file of the GPIO driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __GPIO_CFG_H__
#define __GPIO_CFG_H__

#include "Std_Types.h"


/*************************************************************
 * Description: Register layout of the module.
 *
 *************************************************************/
typedef struct {
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;

	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;

	uint32_t AFRL;
	uint32_t AFRH;
} __attribute__((packed, aligned(4))) GPIO_t;


/*************************************************************
 * Description: Size of different bitfields.
 *
 *************************************************************/
#define SIZE_MODE 				2
#define SIZE_OTYPE 				1
#define SIZE_SPEED 				2
#define SIZE_PUPD 				2
#define SIZE_AF 				4


#endif /* __GPIO_CFG_H__ */
