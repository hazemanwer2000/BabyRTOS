/*************************************************************
 * 
 * Filename: SCHED_Cfg.c
 * Description: Configuration source file of the SCHED driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "SCHED_Cfg.h"
#include "SCHED_Types.h"
#include "SCHED.h"

#include "main.h"

#include "LCD.h"

#include "BUTTON.h"


/*************************************************************
 * Description: Runnables configurations.
 *
 *************************************************************/
SCHED_runnable_cfg_t SCHED_runnable_cfgs[SCHED_runnable_count] = {
    
    [SCHED_runnable_LED_1s] = {
        .callback = &APP_LED_1s,
        .period = 1000000,
        .startDelay = 0
    },
    
    [SCHED_runnable_LED_2s] = {
        .callback = &APP_LED_2s,
        .period = 2000000,
        .startDelay = 0
    },

    [SCHED_runnable_LED_4s] = {
        .callback = &APP_LED_4s,
        .period = 4000000,
        .startDelay = 0
    },

    [SCHED_runnable_Toggler] = {
        .callback = &APP_Toggler,
        .period = 50000,
        .startDelay = 0
    },

    [SCHED_runnable_service_deboucingHandling] = {
        .callback = &BUTTON_service_debounceHandling,
        .period = 5000,
        .startDelay = 0
    },

    [SCHED_runnable_service_LCD] = {
        .callback = &LCD_service,
        .period = 5000,
        .startDelay = 20000
    }
};