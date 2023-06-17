/*************************************************************
 * 
 * Filename: LED_Cfg.h
 * Description: Configuration header file of the LED driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __LED_CFG_H__
#define __LED_CFG_H__

#include "LED_Types.h"


/*************************************************************
 * Description: LED active mode options.
 *
 *************************************************************/
#define LED_activeMode_ActiveHigh 			0
#define LED_activeMode_ActiveLow 			1


/*************************************************************
 * Description: (Type-Enum) LED names.
 *
 *************************************************************/
typedef enum {
	LED_name_Buzzer = 0,

	LED_name_Count
} LED_name_t;


/*************************************************************
 * Description: (Declaration) LED configurations.
 *
 *************************************************************/
extern LED_cfg_t LED_cfgs[LED_name_Count];


#endif /* __LED_CFG_H__ */
