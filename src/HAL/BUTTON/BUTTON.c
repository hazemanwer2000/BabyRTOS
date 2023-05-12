/*************************************************************
 * 
 * Filename: BUTTON.c
 * Description: Source file of the BUTTON driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "BUTTON_Cfg.h"
#include "BUTTON_Priv.h"
#include "BUTTON.h"
#include "BUTTON_Types.h"


/*************************************************************
 * Description: Button states.
 * 
 *************************************************************/
static BUTTON_state_t BUTTON_states[BUTTON_name_Count];


/*************************************************************
 * Description: Button previous states.
 * 
 *************************************************************/
static BUTTON_state_t BUTTON_previousStates[BUTTON_name_Count];


/*************************************************************
 * Description: Button debounce counters.
 * 
 *************************************************************/
static uint8_t BUTTON_debouceCounters[BUTTON_name_Count];


/*************************************************************
 * Description: Button initialization (based on configuration files).
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
void BUTTON_init() {
	uint8_t i = 0;
	GPIO_pinConfiguration_t pinCfg = {
		.pinSpeed = GPIO_speed_High
	};

	for (i = 0; i < BUTTON_name_Count; i++) {
		pinCfg.port = BUTTON_cfgs[i].port;
		pinCfg.pinNumber = BUTTON_cfgs[i].pinNumber;
		pinCfg.pinMode = BUTTON_cfgs[i].pinMode;

		GPIO_initializePin(&pinCfg);
	}
}


/*************************************************************
 * Description: A service, to negate the debouncing effect.
 * 					Note: Runs every 5 ms.
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
void BUTTON_service_debounceHandling(void) {
	uint8_t i = 0;
	BUTTON_state_t currentState = BUTTON_state_Released;

	for (i = 0; i < BUTTON_name_Count; i++) {
		currentState = BUTTON_getQuick(i);

		if (currentState == BUTTON_previousStates[i]) {
			if (BUTTON_debouceCounters[i] == BUTTON_debounceCountMaximum) {
				BUTTON_states[i] = currentState;
			} else {
				BUTTON_debouceCounters[i]++;
			}
		} else {
			BUTTON_debouceCounters[i] = 0;
		}

		BUTTON_previousStates[i] = currentState;
	}
}


/*************************************************************
 * Description: Get Button state.
 * Parameters:
 *      [1] Button name (configuration files).
 * Return:
 *      Button state.
 *************************************************************/
static BUTTON_state_t BUTTON_getQuick(BUTTON_name_t name) {
	return BUTTON_cfgs[name].activeMode ^ GPIO_readPinState(BUTTON_cfgs[name].port, BUTTON_cfgs[name].pinNumber);
}


/*************************************************************
 * Description: Get Button state.
 * Parameters:
 *      [1] Button name (configuration files).
 * Return:
 *      Button state.
 *************************************************************/
BUTTON_state_t BUTTON_get(BUTTON_name_t name) {
	return BUTTON_states[name];
}

