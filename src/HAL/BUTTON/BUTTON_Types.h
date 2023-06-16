/*************************************************************
 * 
 * Filename: BUTTON_Types.h
 * Description: Types header file of the BUTTON driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __BUTTON_TYPES_H__
#define __BUTTON_TYPES_H__

#include "GPIO.h"
#include "Std_Types.h"


/*************************************************************
 * Description: (Type) Various type-defs.
 *
 *************************************************************/
typedef uint8_t BUTTON_activeMode_t;
typedef uint8_t BUTTON_state_t;


/*************************************************************
 * Description: (Type) BUTTON configuration.
 *
 *************************************************************/
typedef struct {
	GPIO_port_t port;
	GPIO_pinNumber_t pinNumber;
	GPIO_pinMode_t pinMode;
	BUTTON_activeMode_t activeMode;
} BUTTON_cfg_t;

#endif /* __BUTTON_TYPES_H__ */
