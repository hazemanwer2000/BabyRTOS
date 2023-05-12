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
	[BUTTON_name_Toggler] = {GPIOA, GPIO_pinNumber_7, GPIO_mode_Input_PullUp, BUTTON_activeMode_ActiveLow}
};
