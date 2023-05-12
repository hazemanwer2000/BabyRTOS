/*************************************************************
 * 
 * Filename: SCHED.c
 * Description: Source file of the SCHED driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "SCHED_Cfg.h"
#include "SCHED_Priv.h"
#include "SCHED_Types.h"
#include "SCHED.h"

#include "SYSTICK.h"


/*************************************************************
 * Description: Runnables' statuses.
 * 
 *************************************************************/
static SCHED_runnable_status_t SCHED_runnable_stats[SCHED_runnable_count];


/*************************************************************
 * Description: Tracks number of SysTick periods before a tick fires.
 * 
 *************************************************************/
static uint32_t SCHED_counter;


/*************************************************************
 * Description: Signal from SCHED_callback to SCHED_start 'while' loop.
 * 
 *************************************************************/
static uint8_t SCHED_signal = 0;


/*************************************************************
 * Description: Initialize scheduler.
 * Parameters:
 * 		[X]
 * Return:
 *      None.
 *************************************************************/
void SCHED_Systick_callback(void) {
    SCHED_signal = 1;
}


/*************************************************************
 * Description: Start scheduler.
 * Parameters:
 * 		[X]
 * Return:
 *      None.
 *************************************************************/
void SCHED_start(void) {
    uint32_t i = 0;

    SYSTICK_enable();
    
    while (1) {
        if (SCHED_signal != 0) {
            SCHED_signal = 0;
            i = 0;
            
            if (SCHED_counter == 0) {
                for (i = 0; i < SCHED_runnable_count; i++) {
                    if (SCHED_runnable_stats[i].remainingTime == 0) {
                        SCHED_runnable_cfgs[i].callback();
                        SCHED_runnable_stats[i].remainingTime = SCHED_runnable_cfgs[i].period - SCHED_Tick_us;
                    } else {
                        SCHED_runnable_stats[i].remainingTime -= SCHED_Tick_us;
                    }
                }

                SCHED_counter = SCHED_Tick_N - 1;
            } else {
                SCHED_counter--;
            }
        }
    }
}


/*************************************************************
 * Description: Initialize scheduler.
 * Parameters:
 * 		[X]
 * Return:
 *      Status.
 *************************************************************/
SCHED_status_t SCHED_init(void) {
    SCHED_status_t status = SCHED_status_Ok;
    uint32_t i = 0;

    SYSTICK_enableException();
    SYSTICK_configureClockSource(SCHED_SysTick_clockSource);
    SYSTICK_setCallback(&SCHED_Systick_callback);
 
    if (SYSTICK_setPeriod_us(SCHED_SysTick_Period_us) == SYSTICK_status_Ok) {
        for (i = 0; i < SCHED_runnable_count; i++) {
            if (SCHED_runnable_cfgs[i].period % SCHED_Tick_us != 0 ||
                    SCHED_runnable_cfgs[i].startDelay % SCHED_Tick_us != 0) {
                status = SCHED_status_RunnablePeriodNotPossible;
                break;
            }
        }

        if (status == SCHED_status_Ok) {
            SCHED_counter = SCHED_Tick_N - 1;

            for (i = 0; i < SCHED_runnable_count; i++) {
                SCHED_runnable_stats[i].remainingTime = SCHED_runnable_cfgs[i].startDelay;
            }
        }
    } else {
        status = SCHED_status_SystickPeriodNotPossibe;
    }

    return status;
}