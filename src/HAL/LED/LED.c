/*************************************************************
 * 
 * Filename: LED.c
 * Description: Source file of the LED driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "LED_Cfg.h"
#include "LED_Priv.h"
#include "LED_Types.h"
#include "LED.h"
#include "GPIO.h"


/*************************************************************
 * Description: LED initialization (based on configuration files).
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
void LED_init() {
	uint8_t i = 0;
	GPIO_pinConfiguration_t pinCfg = {
		.pinMode = GPIO_mode_Output_PushPull_Float,
		.pinSpeed = GPIO_speed_High
	};

	for (i = 0; i < LED_name_Count; i++) {
		pinCfg.port = LED_cfgs[i].port;
		pinCfg.pinNumber = LED_cfgs[i].pinNumber;

		GPIO_initializePin(&pinCfg);
	}
}


/*************************************************************
 * Description: Set LED state.
 * Parameters:
 *      [1] LED name (configuration files).
 *      [2] LED state option.
 * Return:
 *      None.
 *************************************************************/
void LED_setState(LED_name_t name, LED_state_t state) {
	GPIO_setPinState(LED_cfgs[name].port, LED_cfgs[name].pinNumber, LED_cfgs[name].activeMode ^ state);
}


/*************************************************************
 * Description: Toggle LED state.
 * Parameters:
 *      [1] LED name (configuration files).
 *      [2] LED state option.
 * Return:
 *      None.
 *************************************************************/
void LED_toggle(LED_name_t name) {
	GPIO_togglePinState(LED_cfgs[name].port, LED_cfgs[name].pinNumber);
}
