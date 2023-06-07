
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
#include "Queue.h"


/*************************************************************
 * Description: Enumeration of task states.
 * 
 *************************************************************/
typedef enum {
    OS_task_state_READY = 0,
    OS_task_state_WAITING,
    OS_task_state_DELAYED,
    OS_task_state_WAITING_ON_SEMAPHORE,
    OS_task_state_WAITING_TO_ENQUEUE,
    OS_task_state_WAITING_TO_DEQUEUE,
    OS_task_state_WAITING_ON_MUTEX
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
    uint8_t priority;
    OS_task_state_t state;

    LL_node node;

        /* Request-related. */
    uint32_t delay;
    void *args;
    uint8_t saved_priority;
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
 * Description: Structure of an OS queue.
 * 
 *************************************************************/
typedef struct {
    Queue_t queue;
    LL_list waiting_enqueue;
    LL_list waiting_dequeue;
} OS_queue;


/*************************************************************
 * Description: Structure of an OS mutex.
 * 
 *************************************************************/
typedef struct {
    OS_task *task;
    LL_list waiting;
} OS_mutex;


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
 * Description: Setup queue.
 * Parameters:
 *      [1] Pointer to 'OS_queue'.
 *      [2] Array of 'void *'.
 *      [3] Array length.
 * Return:
 *      None.
 *************************************************************/
void OS_setupQueue(OS_queue *q, void **array, uint32_t length);


/*************************************************************
 * Description: Setup mutex.
 * Parameters:
 *      [1] Pointer to 'OS_mutex'.
 * Return:
 *      None.
 *************************************************************/
void OS_setupMutex(OS_mutex *m);


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


/*************************************************************
 * Description: Enqueue.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to queue.
 *      [3] Argument, as 'void *'.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_enqueue(OS_task *task, OS_queue *queue, void *args);


/*************************************************************
 * Description: Enqueue.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to queue.
 *      [3] Argument, as 'void *'.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_enqueue(OS_task *task, OS_queue *q, void *args);


/*************************************************************
 * Description: Dequeue.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to queue.
 *      [3] Argument to return, as 'void **'.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_dequeue(OS_task *task, OS_queue *queue, void **args);


/*************************************************************
 * Description: Dequeue.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to queue.
 *      [3] Argument to return, as 'void **'.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_dequeue(OS_task *task, OS_queue *q, void **args);


/*************************************************************
 * Description: Lock mutex.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to mutex.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_lock(OS_task *task, OS_mutex *m);


/*************************************************************
 * Description: Lock mutex.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to mutex.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_lock(OS_task *task, OS_mutex *m);


/*************************************************************
 * Description: Unlock mutex.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to mutex.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_unlock(OS_task *task, OS_mutex *m);


/*************************************************************
 * Description: Unlock mutex.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to mutex.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_unlock(OS_task *task, OS_mutex *m);


#endif /* __OS_KERNEL_H__ */