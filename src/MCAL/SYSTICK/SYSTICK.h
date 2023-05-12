/*************************************************************
 * 
 * Filename: SYSTICK.h
 * Description: Header (interface) file of the SYSTICK driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "SYSTICK_Types.h"


/*************************************************************
 * Description: Clock source options.
 *
 *************************************************************/
#define SYSTICK_clockSource_AHB						0b100
#define SYSTICK_clockSource_AHB_DIV_8				0b000


/*************************************************************
 * Description: Status returned by some API calls (context-dependent).
 *
 *************************************************************/
typedef enum {
	SYSTICK_status_Ok = 0,
	SYSTICK_status_PeriodLimitExceeded,
	SYSTICK_status_PeriodCannotBeZero,
	SYSTICK_status_PeriodResolutionIssue
} SYSTICK_status_t;


/*************************************************************
 * Description: Enable counter.
 * Parameters:
 * 		[X]
 * Return:
 *      None.
 *************************************************************/
void SYSTICK_enable();


/*************************************************************
 * Description: Disable counter.
 * Parameters:
 * 		[X]
 * Return:
 *      None.
 *************************************************************/
void SYSTICK_disable();


/*************************************************************
 * Description: Enable exception (when counter goes from 1 to 0).
 * Parameters:
 * 		[X]
 * Return:
 *      None.
 *************************************************************/
void SYSTICK_enableException();


/*************************************************************
 * Description: Disable exception (when counter goes from 1 to 0).
 * Parameters:
 * 		[X]
 * Return:
 *      None.
 *************************************************************/
void SYSTICK_disableException();


/*************************************************************
 * Description: Configure clock source.
 * Parameters:
 * 		[1] Clock source.
 * Return:
 *      None.
 *************************************************************/
void SYSTICK_configureClockSource(SYSTICK_clockSource_t clockSource);


/*************************************************************
 * Description: Set period (in micro-seconds).
 *					Note: Period is integral, ranges from 1 to (2^24 / SYSTICK_CLK_MHz).
 * Parameters:
 * 		[1] Period.
 * Return:
 *      Status.
 *************************************************************/
SYSTICK_status_t SYSTICK_setPeriod_us(SYSTICK_period_t period);


/*************************************************************
 * Description: Set callback.
 * Parameters:
 * 		[1] Function pointer.
 * Return:
 *      None.
 *************************************************************/
void SYSTICK_setCallback(void (*fcnPtr)(void));


#endif /* __SYSTICK_H__ */
