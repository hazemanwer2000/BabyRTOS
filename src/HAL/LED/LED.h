/*************************************************************
 * 
 * Filename: LED.h
 * Description: Header (interface) file of the LED driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __LED_H__
#define __LED_H__

#include "LED_Cfg.h"
#include "LED_Types.h"


/*************************************************************
 * Description: LED state options.
 *
 *************************************************************/
#define LED_state_On				1
#define LED_state_Off				0


/*************************************************************
 * Description: LED initialization (based on configuration files).
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
void LED_init();


/*************************************************************
 * Description: Set LED state.
 * Parameters:
 *      [1] LED name (configuration files).
 *      [2] LED state option.
 * Return:
 *      None.
 *************************************************************/
void LED_setState(LED_name_t name, LED_state_t state);


/*************************************************************
 * Description: Toggle LED state.
 * Parameters:
 *      [1] LED name (configuration files).
 *      [2] LED state option.
 * Return:
 *      None.
 *************************************************************/
void LED_toggle(LED_name_t name);


#endif /* __LED_H__ */
