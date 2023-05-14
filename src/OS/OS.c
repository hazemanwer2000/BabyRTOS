/*************************************************************
 * 
 * Filename: OS_kernel.c
 * Description: Source file of the OS Kernel.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "OS.h"
#include "Std_Types.h"
#include "Bit_Utils.h"


/*************************************************************
 * Description: Macro configurations.
 * 
 *************************************************************/
#define IDLE_TASK_STACK_SIZE                256


/*************************************************************
 * Description: Registers-definitions.
 * 
 *************************************************************/
#define ICSR                (* (volatile uint32_t *) 0xE000ED04)
#define PENDSVSET           28

#define SHPR3               (* (volatile uint32_t *) 0xE000ED20)
#define PRI_14_N            23
#define PRI_14_0            16

#define SYSTICK_CTRL	    (* (volatile uint32_t *) 0xE000E010)
#define BIT_ENABLE	        0
#define BIT_TICKINT	        1


/*************************************************************
 * Description: Macro functions.
 * 
 *************************************************************/

    /* Memory-Barrier Sync. Instructions. */
#define SYNC()              __asm("DSB"); __asm("ISB")

    /* Set 'PendSV' interrupt as pending. */  
#define PENDSV()            ICSR |= (1 << PENDSVSET); SYNC()


/*************************************************************
 * Description: Priority mapping-related variables.
 * 
 *************************************************************/
static uint8_t groups = 0;
static uint8_t group[8] = {0};
static OS_task *tasks[64];

static uint8_t bitmap[256] = {
    -1, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    4, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    5, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    4, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    6, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    4, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    5, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    4, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    7, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    4, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    5, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    4, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    6, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    4, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    5, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0, 
    4, 0, 1, 0, 2, 0, 1, 0, 
    3, 0, 1, 0, 2, 0, 1, 0
};


/*************************************************************
 * Description: Idle-task variables.
 * 
 *************************************************************/
static OS_task idleTask;
static uint8_t stack[IDLE_TASK_STACK_SIZE];


/*************************************************************
 * Description: Interrupt handler, comes every tick.
 * 
 *************************************************************/
void __attribute__ ((section(".after_vectors")))
SysTick_Handler (void) {

}


/*************************************************************
 * Description: Interrupt handler, responsible for context-switching.
 *                  Note: Must be the least priority in the whole system.
 * 
 *************************************************************/
void __attribute__ ((section(".after_vectors"), naked))
PendSV_Handler(void) {

}


/*************************************************************
 * Description: Idle task of the OS.
 * 
 *************************************************************/
void OS_idleTask(void *args) {
    while (1);                      /* Infinite mind-less loop. */
}


/*************************************************************
 * Description: Initialize the OS.
 * Parameters:
 *      [X]
 * Return:
 *      Error Status.
 *************************************************************/
void OS_init(void) {


    SYSTICK_CTRL |= (1 << BIT_TICKINT);             /* Enable 'SysTick' interrupt. */
    SHPR3 |= MSK_I2J(PRI_14_0, PRI_14_N);           /* Set 'PendSV' interrupt with least priority. */

    OS_setupTask(&idleTask, OS_idleTask, NULL, 63, )
}


/*************************************************************
 * Description: Setup task.
 * Parameters:
 *      [1] 
 * Return:
 *      Error Status.
 *************************************************************/
void OS_setupTask(OS_task *task, void (*fptr)(void), void *args, uint8_t priority, uint8_t *stackBegin, uint32_t stackSize) {
    uint8_t bit_group = priority / 8;
    uint8_t bit_task = priority % 8;

    groups |= (1 << bit_group);
    group[bit_group] |= (1 << bit_task);
    tasks[priority] = task;

    task->fptr = fptr;
    task->args = args;
    task->stackPtr = (uint32_t *) (stackBegin + ALIGN_8(stackSize));
}


/*************************************************************
 * Description: Kick-start the OS.
 * Parameters:
 *      [X]
 * Return:
 *      Error Status.
 *************************************************************/
void OS_start(void) {
    SYSTICK_CTRL |= (1 << BIT_ENABLE);      /* Enable 'SysTick' timer. */
    PENDSV();
}