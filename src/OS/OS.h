
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
#include "Heap.h"


/*************************************************************
 * Description: Configuration.
 * 
 *************************************************************/
#define OS_MAX_WAITING_TASKS_PER_SEMAPHORE              10


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
    uint32_t delay;

    LL_node node;
} OS_task;


/*************************************************************
 * Description: Structure of an OS semaphore.
 * 
 *************************************************************/
typedef struct {
    uint32_t current;
    Heap_t wait_heap;
    void *wait_array[OS_MAX_WAITING_TASKS_PER_SEMAPHORE];
} OS_semaphore;


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
void OS_setupSemaphore(OS_semaphore *sem, uint32_t initial);


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
void OS_wait(OS_task *task);


/*************************************************************
 * Description: (ISR-specific) Put a task in the waiting state.
 * Parameters:
 *      [1] Pointer to task.
 * Return:
 *      None.
 *************************************************************/
void OS_ISR_wait(OS_task *task);


/*************************************************************
 * Description: Put a task in the ready state.
 * Parameters:
 *      [1] Pointer to task.
 * Return:
 *      None.
 *************************************************************/
void OS_ready(OS_task *task);


/*************************************************************
 * Description: (ISR-specific) Put a task in the ready state.
 * Parameters:
 *      [1] Pointer to task.
 * Return:
 *      None.
 *************************************************************/
void OS_ISR_ready(OS_task *task);


/*************************************************************
 * Description: Delay the execution of a task.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Delay (in ticks).
 * Return:
 *      None.
 *************************************************************/
void OS_delay(OS_task *task, uint32_t delay);


/*************************************************************
 * Description: Delay the execution of a task.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Delay (in ticks).
 * Return:
 *      None.
 *************************************************************/
void OS_ISR_delay(OS_task *task, uint32_t delay);


/*************************************************************
 * Description: Increase semaphore's value.
 * Parameters:
 *      [1] Pointer to semaphore.
 * Return:
 *      None.
 *************************************************************/
void OS_give(OS_semaphore *sem);


/*************************************************************
 * Description: Increase semaphore's value.
 * Parameters:
 *      [1] Pointer to semaphore.
 * Return:
 *      None.
 *************************************************************/
void OS_ISR_give(OS_semaphore *sem);


/*************************************************************
 * Description: Decrease semaphore's value.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to semaphore.
 * Return:
 *      None.
 *************************************************************/
void OS_take(OS_task *task, OS_semaphore *sem);


/*************************************************************
 * Description: Decrease semaphore's value.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to semaphore.
 * Return:
 *      None.
 *************************************************************/
void OS_ISR_take(OS_task *task, OS_semaphore *sem);


#endif /* __OS_KERNEL_H__ */