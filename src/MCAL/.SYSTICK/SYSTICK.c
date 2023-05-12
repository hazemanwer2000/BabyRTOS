/*************************************************************
 * 
 * Filename: SYSTICK.c
 * Description: Source file of the SYSTICK driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "SYSTICK_Cfg.h"
#include "SYSTICK_Priv.h"
#include "SYSTICK_Types.h"
#include "SYSTICK_Map.h"
#include "SYSTICK.h"
#include "Bit_Utils.h"
#include "Std_Types.h"


/*************************************************************
 * Description: Interrupt callback.
 * 
 *************************************************************/
static void (*SYSTICK_callback)(void) = NULL;


/*************************************************************
 * Description: (Interrupt) SysTick '1' to '0' transition.
 * 
 *************************************************************/
void __attribute__ ((section(".after_vectors")))
SysTick_Handler (void) {
	if (SYSTICK_callback != NULL) {
		SYSTICK_callback();
	}
}


/*************************************************************
 * Description: Enable counter.
 * Parameters:
 * 		[X]
 * Return:
 *      None.
 *************************************************************/
void SYSTICK_enable() {
	SYSTICK_CTRL |= (1 << BIT_ENABLE);
}


/*************************************************************
 * Description: Disable counter.
 * Parameters:
 * 		[X]
 * Return:
 *      None.
 *************************************************************/
void SYSTICK_disable() {
	SYSTICK_CTRL &= ~(1 << BIT_ENABLE);
}


/*************************************************************
 * Description: Enable exception (when counter goes from 1 to 0).
 * Parameters:
 * 		[X]
 * Return:
 *      None.
 *************************************************************/
void SYSTICK_enableException() {
	SYSTICK_CTRL |= (1 << BIT_TICKINT);
}


/*************************************************************
 * Description: Disable exception (when counter goes from 1 to 0).
 * Parameters:
 * 		[X]
 * Return:
 *      None.
 *************************************************************/
void SYSTICK_disableException() {
	SYSTICK_CTRL &= ~(1 << BIT_TICKINT);
}


/*************************************************************
 * Description: Configure clock source.
 * Parameters:
 * 		[1] Clock source.
 * Return:
 *      None.
 *************************************************************/
void SYSTICK_configureClockSource(SYSTICK_clockSource_t clockSource) {
	SYSTICK_CTRL = (SYSTICK_CTRL & ~SYSTICK_clockSource_MASK) | clockSource;
}


/*************************************************************
 * Description: Set period (in micro-seconds).
 *					Note: Period is integral, ranges from 1 to (2^24 / SYSTICK_CLK_MHz).
 * Parameters:
 * 		[1] Period.
 * Return:
 *      Status.
 *************************************************************/
SYSTICK_status_t SYSTICK_setPeriod_us(SYSTICK_period_t period) {
	SYSTICK_status_t status = SYSTICK_status_Ok;

	if (period == 0) {
		status = SYSTICK_status_PeriodCannotBeZero;
	} else if (period > ((SYSTICK_period_t) (SYSTICK_COUNTER_MAX / SYSTICK_CLK_MHz))) {
		status = SYSTICK_status_PeriodLimitExceeded;
	} else if (period % SYSTICK_CLK_MHz_DIV_FACTOR != 0) {
		status = SYSTICK_status_PeriodResolutionIssue;
	} else {
		SYSTICK_LOAD = (period / SYSTICK_CLK_MHz_DIV_FACTOR) * SYSTICK_CLK_MHz_WHOLE - 1;
	}

	return status;
}


/*************************************************************
 * Description: Set callback.
 * Parameters:
 * 		[1] Function pointer.
 * Return:
 *      None.
 *************************************************************/
void SYSTICK_setCallback(void (*fcnPtr)(void)) {
	SYSTICK_callback = fcnPtr;
}