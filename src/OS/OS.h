
/*************************************************************
 * 
 * Filename: OS_kernel.h
 * Description: Header file of the OS Kernel.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

/** @file Header file of the OS. */

#ifndef __OS_KERNEL_H__
#define __OS_KERNEL_H__

#include "Std_Types.h"
#include "LinkedList.h"
#include "Queue.h"


/** @enum OS_task_state_t
 *  @brief An enumeration of all possible task states in the system.
 */
typedef enum {
    OS_task_state_READY = 0,
    OS_task_state_WAITING,
    OS_task_state_DELAYED,
    OS_task_state_WAITING_ON_SEMAPHORE,
    OS_task_state_WAITING_TO_ENQUEUE,
    OS_task_state_WAITING_TO_DEQUEUE,
    OS_task_state_WAITING_ON_MUTEX
} OS_task_state_t;


/** @enum OS_REQ_status_t
 *  @brief An enumeration of all possible responses from a system request (i.e, system call).
 */
typedef enum {
    OS_REQ_status_OK = 0,
    OS_REQ_status_NOK,

    OS_REQ_status_MAX = UINT32_MAX
} OS_REQ_status_t;


/** @struct OS_task
 *  @brief A struct that the OS manages, to track a registered task in the system.
 */
typedef struct {
        /* Must be first, for easy stack pointer switching. */
    uint32_t *stackPtr;                 /**< (Internal use only) Tracks the stack pointer of the task. */
    
    uint8_t priority;                   /**< (Internal use only) Current task priority in the system. */
    OS_task_state_t state;              /**< (Internal use only) Current task state in the system. */

    LL_node node;                       /**< (Internal use only) A linked-list node, representative of the task in the system. */

        /* Request-related. */
    uint32_t delay;                     /**< (Internal use only) Remaining number of ticks before task is ready again. */
    void *args;                         /**< (Internal use only) Stores arguments, to be enqueued or dequeued by a waiting task. */
    uint8_t saved_priority;             /**< (Internal use only) Default task priority in the system. */
} OS_task;


/** @struct OS_semaphore
 *  @brief A struct that the OS manages, to track a registered semaphore in the system.
 */
typedef struct {
    uint32_t current;                   /**< (Internal use only) Current value. */
    uint32_t max;                       /**< (Internal use only) Maximum value. */
    LL_list waiting;                    /**< (Internal use only) Waiting tasks. */
} OS_semaphore;


/** @struct OS_queue
 *  @brief A struct that the OS manages, to track a registered queue in the system.
 */
typedef struct {
    Queue_t queue;                      /**< (Internal use only) Queue. */
    LL_list waiting_enqueue;            /**< (Internal use only) Waiting tasks, to enqueue. */
    LL_list waiting_dequeue;            /**< (Internal use only) Waiting tasks, to dequeue. */
} OS_queue;


/** @struct OS_mutex
 *  @brief A struct that the OS manages, to track a registered mutex in the system.
 */
typedef struct {
    volatile OS_task *task;             /**< (Internal use only) Currently locking task. */
    LL_list waiting;                    /**< (Internal use only) Waiting tasks, to unlock. */
} OS_mutex;


/**
 *  @brief Initialize the OS, must be called before any OS related function.
 */
void OS_init(void);


/**
 *  @brief Register a task into the system.
 *  @param task Pointer to 'OS_Task'.
 *  @param fptr Pointer to function, accepts argument as 'void *'.
 *  @param args Argument, as 'void *'.
 *  @param priority Task priority.
 *  @param stackBegin Pointer to stack beginning.
 *  @param stackSize Stack size.
 */
void OS_setupTask(volatile OS_task *task, void (*fptr)(void *), void *args, 
        uint8_t priority, volatile uint8_t *stackBegin, uint32_t stackSize);


/**
 *  @brief Register a semaphore into the system.
 *  @param sem Pointer to 'OS_semaphore'.
 *  @param initial Initial value.
 *  @param maximum Maximum value.
 */
void OS_setupSemaphore(volatile OS_semaphore *sem, uint32_t initial, uint32_t maximum);


/**
 *  @brief Register a queue into the system.
 *  @param q Pointer to 'OS_queue'.
 *  @param array Array of 'void *'.
 *  @param length Array of length.
 */
void OS_setupQueue(volatile OS_queue *q, void * volatile *array, uint32_t length);


/**
 *  @brief Register a mutex into the system.
 *  @param m Pointer to 'OS_mutex'.
 */
void OS_setupMutex(volatile OS_mutex *m);


/**
 *  @brief Kick-start the OS.
 */
void OS_start(void);


/**
 *  @brief Request a task to transition into the WAITING state, must be READY before-hand.
 *  @param task Pointer to 'OS_task'.
 */
OS_REQ_status_t OS_wait(volatile OS_task *task);


/**
 *  @brief (ISR-specific) Request a task to transition into the WAITING state, must be READY before-hand.
 *  @param task Pointer to 'OS_task'.
 */
OS_REQ_status_t OS_ISR_wait(volatile OS_task *task);


/**
 *  @brief Request a task to transition into the READY state, must be WAITING before-hand.
 *  @param task Pointer to 'OS_task'.
 */
OS_REQ_status_t OS_ready(volatile OS_task *task);


/**
 *  @brief (ISR-specific) Request a task to transition into the READY state, must be WAITING before-hand.
 *  @param task Pointer to 'OS_task'.
 */
OS_REQ_status_t OS_ISR_ready(volatile OS_task *task);


/**
 *  @brief Request a task to transition into the DELAYED state, must be READY before-hand.
 *  @param task Pointer to 'OS_task'.
 *  @param delay Number of ticks to delay task by.
 */
OS_REQ_status_t OS_delay(volatile OS_task *task, uint32_t delay);


/**
 *  @brief (ISR-specific) Request a task to transition into the DELAYED state, must be READY before-hand.
 *  @param task Pointer to 'OS_task'.
 *  @param delay Number of ticks to delay task by.
 */
OS_REQ_status_t OS_ISR_delay(volatile OS_task *task, uint32_t delay);


/**
 *  @brief Request to increase a semaphore's value, must not be at its maximum.
 *  @param sem Pointer to 'OS_semaphore'.
 */
OS_REQ_status_t OS_give(volatile OS_semaphore *sem);


/**
 *  @brief (ISR-specific) Request to increase a semaphore's value, must not be at its maximum.
 *  @param sem Pointer to 'OS_semaphore'.
 */
OS_REQ_status_t OS_ISR_give(volatile OS_semaphore *sem);


/**
 *  @brief Request to decrease a semaphore's value, transitions into WAITING_ON_SEMAPHORE state if value is zero.
 *  @param task Pointer to 'OS_task'.
 *  @param sem Pointer to 'OS_semaphore'.
 */
OS_REQ_status_t OS_take(volatile OS_task *task, volatile OS_semaphore *sem);


/**
 *  @brief (ISR-specific) Request to decrease a semaphore's value, transitions into WAITING_ON_SEMAPHORE state if value is zero.
 *  @param task Pointer to 'OS_task'.
 *  @param sem Pointer to 'OS_semaphore'.
 */
OS_REQ_status_t OS_ISR_take(volatile OS_task *task, volatile OS_semaphore *sem);


/**
 *  @brief Request to enqueue arguments, transitions into WAITING_TO_ENQUEUE state if queue is full.
 *  @param task Pointer to 'OS_task'.
 *  @param queue Pointer to 'OS_queue'.
 *  @param args Pointer to arguments.
 */
OS_REQ_status_t OS_enqueue(volatile OS_task *task, volatile OS_queue *queue, void *args);


/**
 *  @brief (ISR-specific) Request to enqueue arguments, transitions into WAITING_TO_ENQUEUE state if queue is full.
 *  @param task Pointer to 'OS_task'.
 *  @param queue Pointer to 'OS_queue'.
 *  @param args Pointer to arguments.
 */
OS_REQ_status_t OS_ISR_enqueue(volatile OS_task *task, volatile OS_queue *q, void *args);


/**
 *  @brief Request to dequeue arguments, transitions into WAITING_TO_DEQUEUE state if queue is empty.
 *  @param task Pointer to 'OS_task'.
 *  @param queue Pointer to 'OS_queue'.
 *  @param args Pointer to arguments.
 */
OS_REQ_status_t OS_dequeue(volatile OS_task *task, volatile OS_queue *queue, void * volatile *args);


/**
 *  @brief (ISR-specific) Request to dequeue arguments, transitions into WAITING_TO_DEQUEUE state if queue is empty.
 *  @param task Pointer to 'OS_task'.
 *  @param queue Pointer to 'OS_queue'.
 *  @param args Pointer to arguments.
 */
OS_REQ_status_t OS_ISR_dequeue(volatile OS_task *task, volatile OS_queue *q, void * volatile *args);


/**
 *  @brief Request to lock mutex, transitions into WAITING_ON_MUTEX state if already locked.
 *  @param task Pointer to 'OS_task'.
 *  @param queue Pointer to 'OS_mutex'.
 */
OS_REQ_status_t OS_lock(volatile OS_task *task, volatile OS_mutex *m);


/**
 *  @brief (ISR-specific) Request to lock mutex, transitions into WAITING_ON_MUTEX state if already locked.
 *  @param task Pointer to 'OS_task'.
 *  @param m Pointer to 'OS_mutex'.
 */
OS_REQ_status_t OS_ISR_lock(volatile OS_task *task, volatile OS_mutex *m);


/**
 *  @brief Request to unlock mutex, must be already locked by the same task.
 *  @param task Pointer to 'OS_task'.
 *  @param m Pointer to 'OS_mutex'.
 */
OS_REQ_status_t OS_unlock(volatile OS_task *task, volatile OS_mutex *m);


/**
 *  @brief (ISR-specific) Request to unlock mutex, must be already locked by the same task.
 *  @param task Pointer to 'OS_task'.
 *  @param m Pointer to 'OS_mutex'.
 */
OS_REQ_status_t OS_ISR_unlock(volatile OS_task *task, volatile OS_mutex *m);


/**
 *  @brief Request to disable all interrupts (except SVC, and Fault exceptions), before entering a critical section.
 */
OS_REQ_status_t OS_criticalEnter();


/**
 *  @brief Request to enable all interrupts (except SVC, and Fault exceptions), after exiting a critical section.
 */
OS_REQ_status_t OS_criticalExit();


/**
 *  @brief Request the current time, OS-maintained since a hard-reset occured, in milli-seconds.
 *  @param t Pointer to 'uint64_t'.
 */
OS_REQ_status_t OS_getTime(volatile uint64_t *t);


/**
 *  @brief (ISR-specific) Request the current time, OS-maintained since a hard-reset occured, in milli-seconds.
 *  @param t Pointer to 'uint64_t'.
 *  @return Request status.
 */
OS_REQ_status_t OS_ISR_getTime(volatile uint64_t *t);


#endif /* __OS_KERNEL_H__ */