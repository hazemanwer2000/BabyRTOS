/*************************************************************
 * 
 * Filename: SCHED_Types.h
 * Description: Types header file of the SCHED driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __SCHED_TYPES_H__
#define __SCHED_TYPES_H__

#include "Std_Types.h"


/*************************************************************
 * Description: Runnable configuration type.
 *
 *************************************************************/
typedef struct {
    void (*callback)(void);
    uint32_t period;
    uint32_t startDelay;
} SCHED_runnable_cfg_t;


/*************************************************************
 * Description: Runnable status type.
 *
 *************************************************************/
typedef struct {
    uint32_t remainingTime;
} SCHED_runnable_status_t;


#endif /* __SCHED_TYPES_H__ */