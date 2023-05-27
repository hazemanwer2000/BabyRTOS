
/*************************************************************
 * 
 * Filename: OS_kernel.h
 * Description: Header file of the OS Kernel.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __OS_KERNEL_H__
#define __OS_KERNEL_H__

#include "Std_Types.h"
#include "LinkedList.h"


/*************************************************************
 * Description: Enumeration of task states.
 * 
 *************************************************************/
typedef enum {
    OS_task_state_READY = 0,
    OS_task_state_WAITING,
    OS_task_state_DELAYED,
    OS_task_state_WAITING_ON_SEMAPHORE
} OS_task_state_t;


/*************************************************************
 * Description: Enumeration of request responses.
 * 
 *************************************************************/
typedef enum {
    OS_REQ_status_OK = 0,
    OS_REQ_status_NOK
} OS_REQ_status_t;


/*************************************************************
 * Description: Structure of an OS task.
 * 
 *************************************************************/
typedef struct {
        /* Must be first, for easy stack pointer switching. */
    uint32_t *stackPtr;
    
    void (*fptr)(void *);
    void *args;
    uint8_t priority;
    OS_task_state_t state;

    LL_node node;

        /* Request-related. */
    uint32_t delay;
} OS_task;


/*************************************************************
 * Description: Structure of an OS semaphore.
 * 
 *************************************************************/
typedef struct {
    uint32_t current;
    uint32_t max;
    LL_list waiting;
} OS_semaphore;


/*************************************************************
 * Description: Structure of an OS semaphore.
 * 
 *************************************************************/
typedef struct {
    LL_list content;
    LL_list waiting_enqueue;
    LL_list waiting_dequeue;
} OS_queue;


/*************************************************************
 * Description: Initialize the OS.
 * Parameters:
 *      [X]
 * Return:
 *      Error Status.
 *************************************************************/
void OS_init(void);


/*************************************************************
 * Description: Setup task.
 * Parameters:
 *      [1] Pointer to 'OS_Task'.
 *      [2] Pointer to function, accepts argument as 'void *'.
 *      [3] Argument, as 'void *'.
 *      [4] Task priority.
 *      [5] Pointer to stack beginning.
 *      [6] Stack size.
 * Return:
 *      None.
 *************************************************************/
void OS_setupTask(OS_task *task, void (*fptr)(void *), void *args, 
        uint8_t priority, uint8_t *stackBegin, uint32_t stackSize);


/*************************************************************
 * Description: Setup semaphore.
 * Parameters:
 *      [1] Pointer to 'OS_semaphore'.
 *      [2] Initial value.
 * Return:
 *      None.
 *************************************************************/
void OS_setupSemaphore(OS_semaphore *sem, uint32_t initial, uint32_t maximum);


/*************************************************************
 * Description: Kick-start the OS.
 * Parameters:
 *      [X]
 * Return:
 *      Error Status.
 *************************************************************/
void OS_start(void);


/*************************************************************
 * Description: Put a task in the waiting state.
 * Parameters:
 *      [1] Pointer to task.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_wait(OS_task *task);


/*************************************************************
 * Description: (ISR-specific) Put a task in the waiting state.
 * Parameters:
 *      [1] Pointer to task.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_wait(OS_task *task);


/*************************************************************
 * Description: Put a task in the ready state.
 * Parameters:
 *      [1] Pointer to task.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ready(OS_task *task);


/*************************************************************
 * Description: (ISR-specific) Put a task in the ready state.
 * Parameters:
 *      [1] Pointer to task.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_ready(OS_task *task);


/*************************************************************
 * Description: Delay the execution of a task.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Delay (in ticks).
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_delay(OS_task *task, uint32_t delay);


/*************************************************************
 * Description: Delay the execution of a task.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Delay (in ticks).
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_delay(OS_task *task, uint32_t delay);


/*************************************************************
 * Description: Increase semaphore's value.
 * Parameters:
 *      [1] Pointer to semaphore.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_give(OS_semaphore *sem);


/*************************************************************
 * Description: Increase semaphore's value.
 * Parameters:
 *      [1] Pointer to semaphore.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_give(OS_semaphore *sem);


/*************************************************************
 * Description: Decrease semaphore's value.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to semaphore.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_take(OS_task *task, OS_semaphore *sem);


/*************************************************************
 * Description: Decrease semaphore's value.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to semaphore.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_take(OS_task *task, OS_semaphore *sem);


#endif /* __OS_KERNEL_H__ */