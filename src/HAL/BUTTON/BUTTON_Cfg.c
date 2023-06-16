/*************************************************************
 * 
 * Filename: BUTTON_Cfg.c
 * Description: Configuration source file of the BUTTON driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "BUTTON_Cfg.h"
#include "BUTTON_Types.h"
#include "BUTTON.h"
#include "GPIO.h"


/*************************************************************
 * Description: (Definition) BUTTON configurations.
 *
 *************************************************************/
BUTTON_cfg_t BUTTON_cfgs[BUTTON_name_Count] = {
	[BUTTON_name_UP] = {
		.port = GPIOB,
		.pinNumber = GPIO_pinNumber_12,
		.activeMode = BUTTON_activeMode_ActiveLow,
		.pinMode = GPIO_mode_Input_PullUp
	},

	[BUTTON_name_DOWN] = {
		.port = GPIOB,
		.pinNumber = GPIO_pinNumber_13,
		.activeMode = BUTTON_activeMode_ActiveLow,
		.pinMode = GPIO_mode_Input_PullUp
	},

	[BUTTON_name_LEFT] = {
		.port = GPIOB,
		.pinNumber = GPIO_pinNumber_14,
		.activeMode = BUTTON_activeMode_ActiveLow,
		.pinMode = GPIO_mode_Input_PullUp
	},

	[BUTTON_name_RIGHT] = {
		.port = GPIOB,
		.pinNumber = GPIO_pinNumber_15,
		.activeMode = BUTTON_activeMode_ActiveLow,
		.pinMode = GPIO_mode_Input_PullUp
	},

	[BUTTON_name_ENTER] = {
		.port = GPIOA,
		.pinNumber = GPIO_pinNumber_8,
		.activeMode = BUTTON_activeMode_ActiveLow,
		.pinMode = GPIO_mode_Input_PullUp
	},

	[BUTTON_name_BACK] = {
		.port = GPIOA,
		.pinNumber = GPIO_pinNumber_9,
		.activeMode = BUTTON_activeMode_ActiveLow,
		.pinMode = GPIO_mode_Input_PullUp
	}
};
