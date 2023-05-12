/*************************************************************
 * 
 * Filename: RCC.c
 * Description: Source file of the RCC driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "Std_Types.h"
#include "RCC_Map.h"
#include "RCC.h"
#include "RCC_Priv.h"
#include "Bit_Utils.h"


/*************************************************************
 * Description: Select system clock, and wait until it is used. (with timeout).
 * 					Note: System clock must be [ON] beforehand.
 * Parameters:
 *      [1] System clock option.
 * Return:
 *      Status:
 *      	[status_Ok] - System clock has been switched to.
 *      	[status_Timeout] - System clock has not been switched to.
 *************************************************************/
RCC_status_t RCC_selectSystemClock(RCC_systemClock_t systemClock) {
	RCC_status_t status = RCC_status_Ok;
	uint16_t timeout = RCC_selectSystemClock_TIMEOUT;

	RCC->CFGR = REPLACE_FIELD(RCC->CFGR, SW0, SW1, systemClock);

	while (EXTRACT_FIELD(RCC->CFGR, SWS0, SWS1) != systemClock && --timeout > 0);

	if (timeout == 0) {
		status = RCC_status_Timeout;
	}

	return status;
}


/*************************************************************
 * Description: Set system clock state.
 * Parameters:
 *      [1] System clock option.
 *      [2] Clock state option.
 * Return:
 *      Status:
 *      	[status_Ok] - System clock state altered.
 *      	[status_Timeout] - Occurs when [clockState = ON], means failed
 *      						to get system clock ready within time.
 *************************************************************/
RCC_status_t RCC_setSystemClockState(RCC_systemClock_t systemClock, RCC_clockState_t clockState) {
	RCC_status_t status = RCC_status_Ok;
	uint8_t bitON = 0;
	uint8_t bitRDY = 0;
	uint16_t timeout = RCC_setSystemClockState_TIMEOUT;

	switch (systemClock) {
	case RCC_systemClock_HSI:
		bitON = HSION;
		bitRDY = HSIRDY;
		break;
	case RCC_systemClock_HSE:
		bitON = HSEON;
		bitRDY = HSERDY;
		break;
	case RCC_systemClock_PLL:
		bitON = PLLON;
		bitRDY = PLLRDY;
	}

	if (clockState == RCC_clockState_On) {
		RCC->CR = SET_BIT(RCC->CR, bitON);
		while (!GET_BIT(RCC->CR, bitRDY) && --timeout > 0);
	} else {
		RCC->CR = CLR_BIT(RCC->CR, bitON);
		while (GET_BIT(RCC->CR, bitON) && --timeout > 0);
	}

	if (timeout == 0) {
		status = RCC_status_Timeout;
	}

	return status;
}


/*************************************************************
 * Description: Set peripheral clock state.
 * Parameters:
 *      [1] Peripheral option.
 *      [2] Clock state option.
 * Return:
 *      None.
 *************************************************************/
void RCC_setPeripheralClockState(RCC_peripheral_t peripheral, RCC_clockState_t clockState) {
	volatile uint32_t *reg = &RCC->AHB1ENR + (peripheral >> 5);

	*reg = REPLACE_BIT(*reg, peripheral % 32, clockState);
}


/*************************************************************
 * Description: Configure PLL, using the equation (Clock = (SourceClock * N) / (M * P)).
 * 					Note: PLL must be [OFF] beforehand.
 * Parameters:
 *      [1] PLL source clock option.
 *      [2] PLL factor (N), from [PLLFactorN_Min] to [PLLFactorN_Max].
 *      [3] PLL prescale (M), from [PLLPrescaleM_Min] to [PLLPrescaleM_Max].
 *      [4] PLL prescale (P) option.
 * Return:
 *      Status:
 *      	[status_Ok] - PLL configured.
 *      	[status_PLLLocked] - Failed to configure, PLL is on.
 *************************************************************/
RCC_status_t RCC_configurePLLClock(RCC_PLLSourceClock_t PLLSourceClock, uint16_t PLLFactorN, uint8_t PLLPrescaleM, RCC_PLLPrescaleP_t PLLPrescaleP) {
	RCC_status_t status = RCC_status_Ok;
	uint32_t regVal = 0;

	if (PLLFactorN < RCC_PLLFactorN_Min || PLLFactorN > RCC_PLLFactorN_Max ||
			PLLPrescaleM < RCC_PLLPrescaleM_Min || PLLPrescaleM > RCC_PLLPrescaleM_Max) {
		status = RCC_status_InvalidConfiguration;
	} else if (GET_BIT(RCC->CR, PLLON)) {
		status = RCC_status_PLLLocked;
	} else {
		regVal = RCC->PLLCFGR;
		regVal = REPLACE_FIELD(regVal, PLLM0, PLLM5, PLLPrescaleM);
		regVal = REPLACE_FIELD(regVal, PLLN0, PLLN8, PLLFactorN);
		regVal = REPLACE_FIELD(regVal, PLLP0, PLLP1, PLLPrescaleP);
		regVal = REPLACE_BIT(regVal, PLLSRC, PLLSourceClock);
		RCC->PLLCFGR = regVal;
	}

	return status;
}


/*************************************************************
 * Description: Configure bus clock.
 * Parameters:
 *      [1] Bus type option.
 *      [2] Bus-specific prescale option.
 * Return:
 *      None
 *************************************************************/
void RCC_configureBusClock(RCC_bus_t bus, RCC_busPrescale_t busPrescale) {
	switch (bus) {
	case RCC_bus_AHB:
		RCC->CFGR = REPLACE_FIELD(RCC->CFGR, HPRE0, HPRE3, busPrescale);
		break;
	case RCC_bus_APB1:
		RCC->CFGR = REPLACE_FIELD(RCC->CFGR, PPRE10, PPRE12, busPrescale);
		break;
	case RCC_bus_APB2:
		RCC->CFGR = REPLACE_FIELD(RCC->CFGR, PPRE20, PPRE22, busPrescale);
		break;
	}
}
