/*************************************************************
 * 
 * Filename: SCHED_Cfg.h
 * Description: Configuration header file of the SCHED driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __SCHED_CFG_H__
#define __SCHED_CFG_H__

#include "SCHED_Types.h"
#include "SYSTICK.h"


/*************************************************************
 * Description: SysTick clock source in micro-seconds.
 *                  Note: Make sure clock (in MHz) in SysTick configuration files,
 *                          matches RCC's AHB bus configuration, as well as the one ere'.
 *
 *************************************************************/
#define SCHED_SysTick_clockSource       SYSTICK_clockSource_AHB


/*************************************************************
 * Description: SysTick period in micro-seconds.
 *
 *************************************************************/
#define SCHED_SysTick_Period_us         5000


/*************************************************************
 * Description: How many SysTick periods represent a tick?
 *
 *************************************************************/
#define SCHED_Tick_N                    1


/*************************************************************
 * Description: Runnable enumeration type.
 *                  Note: Order matters, first enumeration executes first.
 *
 *************************************************************/
typedef enum {
    SCHED_runnable_LED_1s = 0, 
    SCHED_runnable_LED_2s, 
    SCHED_runnable_LED_4s,
    SCHED_runnable_Toggler,
    SCHED_runnable_service_deboucingHandling,
    SCHED_runnable_service_LCD,

    SCHED_runnable_count
} SCHED_runnable_t;


/*************************************************************
 * Description: Runnable configurations.
 *
 *************************************************************/
extern SCHED_runnable_cfg_t SCHED_runnable_cfgs[SCHED_runnable_count];


#endif /* __SCHED_CFG_H__ */