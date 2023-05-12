/*************************************************************
 * 
 * Filename: NVIC_Types.h
 * Description: Types header file of the NVIC driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __NVIC_TYPES_H__
#define __NVIC_TYPES_H__

#include "Std_Types.h"


/*************************************************************
 * Description: Priority grouping type.
 *
 *************************************************************/
typedef uint32_t NVIC_priorityGrouping_t;


/*************************************************************
 * Description: Interrupt number type.
 *
 *************************************************************/
typedef uint8_t NVIC_interruptNumber_t;


/*************************************************************
 * Description: Priority type.
 *
 *************************************************************/
typedef uint8_t NVIC_priority_t;


/*************************************************************
 * Description: Active status type.
 *
 *************************************************************/
typedef uint8_t NVIC_activeStatus_t;


/*************************************************************
 * Description: Pending status type.
 *
 *************************************************************/
typedef uint8_t NVIC_pendingStatus_t;


#endif /* __NVIC_TYPES_H__ */
