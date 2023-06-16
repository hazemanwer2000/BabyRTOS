/*************************************************************
 * 
 * Filename: LED_Types.h
 * Description: Types header file of the LED driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __LED_TYPES_H__
#define __LED_TYPES_H__

#include "GPIO.h"
#include "Std_Types.h"


/*************************************************************
 * Description: (Type) Various type-defs.
 *
 *************************************************************/
typedef uint8_t LED_activeMode_t;
typedef uint8_t LED_state_t;


/*************************************************************
 * Description: (Type) LED configuration.
 *
 *************************************************************/
typedef struct {
	GPIO_port_t port;
	GPIO_pinNumber_t pinNumber;
	LED_activeMode_t activeMode;
} LED_cfg_t;

#endif /* __LED_TYPES_H__ */
