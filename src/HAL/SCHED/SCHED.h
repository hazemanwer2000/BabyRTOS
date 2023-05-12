/*************************************************************
 * 
 * Filename: SCHED.h
 * Description: Header (interface) file of the SCHED driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "SCHED_Cfg.h"
#include "SCHED_Types.h"


/*************************************************************
 * Description: Micro-seconds in a tick.
 *
 *************************************************************/
#define SCHED_Tick_us                    (SCHED_Tick_N * SCHED_SysTick_Period_us)


/*************************************************************
 * Description: Status type.
 *
 *************************************************************/
typedef enum {
    SCHED_status_Ok,
    SCHED_status_SystickPeriodNotPossibe,
    SCHED_status_RunnablePeriodNotPossible
} SCHED_status_t;


/*************************************************************
 * Description: Initialize scheduler.
 * Parameters:
 * 		[X]
 * Return:
 *      Status.
 *************************************************************/
SCHED_status_t SCHED_init(void);


/*************************************************************
 * Description: Start scheduler.
 * Parameters:
 * 		[X]
 * Return:
 *      None.
 *************************************************************/
void SCHED_start(void);


#endif /* __SCHED_H__ */