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
#define IDLE_STACK_SIZE                     256
#define PRIORITY_HIGHEST                    0
#define PRIORITY_LOWEST                     63


/*************************************************************
 * Description: Registers-definitions.
 * 
 *************************************************************/
#define ICSR                (* (volatile uint32_t *) 0xE000ED04)
#define PENDSVSET           28
#define PENDSTSET           26

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

    /* Set 'SYSTICK' interrupt as pending. */
#define PEND_SYSTICK()      ICSR |= (1 << PENDSTSET); SYNC()


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
 * Description: Idle-Task variables.
 * 
 *************************************************************/
static OS_task idleTask;
static uint8_t idleStack[IDLE_STACK_SIZE];


/*************************************************************
 * Description: Idle-Task variables.
 * 
 *************************************************************/
static OS_task* nextTask;
static OS_task* prevTask;


/*************************************************************
 * Description: Static function declarations.
 * 
 *************************************************************/
static OS_task * OS_getHighestPriorityTask(void);
static void OS_stackInit(OS_task *task);


/*************************************************************
 * Description: (interrupt) Interrupt handler, comes every tick.
 * 
 *************************************************************/
void __attribute__ ((section(".after_vectors")))
SysTick_Handler (void) {}


/*************************************************************
 * Description: (interrupt) Interrupt handler, responsible for context-switching.
 *                  Note: Must be the least priority in the whole system.
 * 
 *************************************************************/
void __attribute__ ((section(".after_vectors"), naked))
PendSV_Handler(void) {

}


/*************************************************************
 * Description: (task) Idle task of the OS.
 * 
 *************************************************************/
static void OS_idleTask(void *args) {
    while (1);                      /* Infinite mind-less loop. */
}


/*************************************************************
 * Description: (static) Get highest priority task.
 * Parameters:
 *      [X]
 * Return:
 *      Pointer to 'OS_task'.
 *************************************************************/
static OS_task * OS_getHighestPriorityTask(void) {
    uint8_t group_index = bitmap[groups];
    uint8_t task_index = bitmap[group[group_index]];

    return tasks[8 * group_index + task_index];
}


static void OS_stackInit(OS_task *task) {
    uint32_t *stackPtr = task->stackPtr;

	*--stackPtr = (uint32_t) (1 << 24);		// xPSR (Thumb-State Enabled)
	*--stackPtr = (uint32_t) task->fptr;	// Return Address
	*--stackPtr = (uint32_t) 14;			// LR (Note: Never returns from task.)
	*--stackPtr = (uint32_t) 12;			// R12
	*--stackPtr = (uint32_t) 3;				// R3
	*--stackPtr = (uint32_t) 2;				// R2
	*--stackPtr = (uint32_t) 1;				// R1
	*--stackPtr = (uint32_t) task->args;	// R0 (args)

	*--stackPtr = (uint32_t) 11;		    // R11
	*--stackPtr = (uint32_t) 10;			// R10
	*--stackPtr = (uint32_t) 9;				// R9
	*--stackPtr = (uint32_t) 8;				// R8
	*--stackPtr = (uint32_t) 7;				// R7
	*--stackPtr = (uint32_t) 6;				// R6
	*--stackPtr = (uint32_t) 5;				// R5
	*--stackPtr = (uint32_t) 4;				// R4

    task->stackPtr = stackPtr;
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

    OS_setupTask(&idleTask, OS_idleTask, NULL, PRIORITY_LOWEST, idleStack, IDLE_STACK_SIZE);
}


/*************************************************************
 * Description: Setup task.
 * Parameters:
 *      [1] Pointer to 'OS_Task'.
 *      [2] Pointer to 
 * Return:
 *      None.
 *************************************************************/
void OS_setupTask(OS_task *task, void (*fptr)(void *), void *args, uint8_t priority, uint8_t *stackBegin, uint32_t stackSize) {
    uint8_t bit_group = priority / 8;
    uint8_t bit_task = priority % 8;

    groups |= (1 << bit_group);
    group[bit_group] |= (1 << bit_task);
    tasks[priority] = task;

    task->fptr = fptr;
    task->args = args;
    task->stackPtr = (uint32_t *) (stackBegin + ALIGN_8(stackSize));

    OS_stackInit(task);
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
    
    nextTask = OS_getHighestPriorityTask();
    PENDSV();
}