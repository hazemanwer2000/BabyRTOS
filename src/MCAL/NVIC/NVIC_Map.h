/*************************************************************
 * 
 * Filename: NVIC_Map.h
 * Description: Map file of the NVIC driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __NVIC_MAP_H__
#define __NVIC_MAP_H__

#include "Std_Types.h"


/*************************************************************
 * Description: NVIC Base Address.
 *
 *************************************************************/
#define NVIC_BASE						0xE000E000
#define NVIC_x(OFFSET)					(*(volatile uint32_t *) ((NVIC_BASE) + (OFFSET)))


/*************************************************************
 * Description: Set-Enable register.
 *
 *************************************************************/
#define NVIC_ISER						NVIC_x(0x100)


/*************************************************************
 * Description: Clear-Enable register.
 *
 *************************************************************/
#define NVIC_ICER						NVIC_x(0x180)


/*************************************************************
 * Description: Set-Pending register.
 *
 *************************************************************/
#define NVIC_ISPR						NVIC_x(0x200)


/*************************************************************
 * Description: Clear-Pending register.
 *
 *************************************************************/
#define NVIC_ICPR						NVIC_x(0x280)


/*************************************************************
 * Description: Active-Bit register.
 *
 *************************************************************/
#define NVIC_IABR						NVIC_x(0x300)


/*************************************************************
 * Description: Priority register.
 *
 *************************************************************/
#define NVIC_IPR						NVIC_x(0x400)


/*************************************************************
 * Description: Software trigger interrupt register.
 *
 *************************************************************/
#define NVIC_STIR						NVIC_x(0xE00)


/*************************************************************
 * Description: Application interrupt and reset control register.
 *
 *************************************************************/
#define AIRCR							(*(volatile uint32_t *) 0xE000ED0C)
#define PRIGROUP0						8
#define PRIGROUP1						9
#define PRIGROUP2						10


#endif /* __NVIC_MAP_H__ */
