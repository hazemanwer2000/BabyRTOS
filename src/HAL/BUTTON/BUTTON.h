/*************************************************************
 * 
 * Filename: BUTTON.h
 * Description: Header (interface) file of the BUTTON driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "BUTTON_Cfg.h"
#include "BUTTON_Types.h"


/*************************************************************
 * Description: Button state options.
 *
 *************************************************************/
#define BUTTON_state_Pressed				1
#define BUTTON_state_Released				0


/*************************************************************
 * Description: Button initialization (based on configuration files).
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
void BUTTON_init();


/*************************************************************
 * Description: Get Button state.
 * Parameters:
 *      [1] Button name (configuration files).
 * Return:
 *      Button state.
 *************************************************************/
BUTTON_state_t BUTTON_get(BUTTON_name_t name);


/*************************************************************
 * Description: A service, to negate the debouncing effect.
 * 					Note: Runs every 5 ms.
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
void BUTTON_service_debounceHandling(void);


#endif /* __BUTTON_H__ */
