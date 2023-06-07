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

#define AIRCR							(*(volatile uint32_t *) 0xE000ED0C)
#define AIRCR_DEF                       0x05FA0000
#define AIRCR_DEF_MSK                   0xFFFF0000
#define PRIGROUP0						8
#define PRIGROUPN						10
#define PRIGROUP_NO_PREMPT              0x0700


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

    /* Set 'PendSV' interrupt as pending. */  
#define SVC()               __asm("SVC #0"); SYNC()
#define SVC_CALL()          __asm("MOV R0, SP"); SVC()


/*************************************************************
 * Description: OS request type-ids'.
 * 
 *************************************************************/
typedef enum {
    OS_REQ_id_WAIT = 0,
    OS_REQ_id_READY,
    OS_REQ_id_DELAY,

    OS_REQ_id_GIVE,
    OS_REQ_id_TAKE,
    
    OS_REQ_id_LOCK,
    OS_REQ_id_UNLOCK,
    
    OS_REQ_id_ENQUEUE,
    OS_REQ_id_DEQUEUE
} OS_REQ_id_t;


/*************************************************************
 * Description: OS request argument types.
 * 
 *************************************************************/
typedef struct {
    OS_REQ_id_t id;
    OS_REQ_status_t status;
} OS_REQ_base_t;

typedef struct {
    OS_REQ_base_t base;
    OS_task *task;
} OS_REQ_wait_t;

typedef struct {
    OS_REQ_base_t base;
    OS_task *task;
} OS_REQ_ready_t;

typedef struct {
    OS_REQ_base_t base;
    OS_task *task;
    uint32_t delay;
} OS_REQ_delay_t;

typedef struct {
    OS_REQ_base_t base;
    OS_semaphore *sem;
} OS_REQ_give_t;

typedef struct {
    OS_REQ_base_t base;
    OS_task *task;
    OS_semaphore *sem;
} OS_REQ_take_t;

typedef struct {
    OS_REQ_base_t base;
    OS_task *task;
    OS_queue *queue;
    void *args;
} OS_REQ_enqueue_t;

typedef struct {
    OS_REQ_base_t base;
    OS_task *task;
    OS_queue *queue;
    void **args;
} OS_REQ_dequeue_t;


/*************************************************************
 * Description: Priority mapping-related variables.
 * 
 *************************************************************/
static uint8_t groups = 0;
static uint8_t group[8] = {0};
static LL_list tasks[64];

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
 * Description: List of tasks.
 * 
 *************************************************************/
static LL_list tasks_delayed;
static LL_list tasks_waiting;


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
static LL_list * OS_getHighestPriorityTasks(void);
static void OS_makeTaskWait(OS_task *task);
static void OS_makeTaskReady(OS_task *task);
static void OS_priorityOn(uint8_t priority);
static void OS_priorityOff(uint8_t priority);
static uint8_t OS_comparator(void *arg1, void *arg2);
static void OS_schedule(void);
static void OS_stackInit(OS_task *task, void *args);


/*************************************************************
 * Description: (interrupt) Interrupt handler, comes every tick.
 * 
 *************************************************************/
void __attribute__ ((section(".after_vectors")))
SysTick_Handler (void) {
    LL_list *list;
    LL_node *node, *node_tmp;
    OS_task *task;

        /* Count-down for delayed tasks. */
    
    node = tasks_delayed.head;
    while (node != NULL) {
        task = (OS_task *) node->data;
        task->delay--;

        if (task->delay == 0) {       /* Dispatch again. */
            task->state = OS_task_state_READY;

            node_tmp = node->next;

            LL_remove(&tasks_delayed, node);
            LL_enqueue(&tasks[task->priority], node);

            OS_priorityOn(task->priority);

            node = node_tmp;
        } else {
            node = node->next;
        }
    }

        /* Time-sharing between tasks of similar priority. */

    list = OS_getHighestPriorityTasks();
    LL_enqueue(list, LL_dequeue(list));
    task = (OS_task *) list->head->data;

    if (task != nextTask) {
        prevTask = nextTask;
        nextTask = task;
        PENDSV();
    }
}


/*************************************************************
 * Description: (interrupt) Interrupt handler, supervisory call.
 * 
 *************************************************************/
void __attribute__ ((section(".after_vectors")))
SVC_Handler (OS_REQ_base_t *request) {
    OS_REQ_status_t status = OS_REQ_status_OK;

    switch (request->id) {
        case OS_REQ_id_WAIT:
            status = OS_ISR_wait(((OS_REQ_wait_t *) request)->task);
            break;
        case OS_REQ_id_READY:
            status = OS_ISR_ready(((OS_REQ_ready_t *) request)->task);
            break;
        case OS_REQ_id_DELAY:
            status = OS_ISR_delay(
                ((OS_REQ_delay_t *) request)->task,
                ((OS_REQ_delay_t *) request)->delay
            );
            break;
        case OS_REQ_id_GIVE:
            status = OS_ISR_give(((OS_REQ_give_t *) request)->sem);
            break;
        case OS_REQ_id_TAKE:
            status = OS_ISR_take(
                ((OS_REQ_take_t *) request)->task,
                ((OS_REQ_take_t *) request)->sem
            );
            break;
        case OS_REQ_id_ENQUEUE:
            status = OS_ISR_enqueue(
                ((OS_REQ_enqueue_t *) request)->task,
                ((OS_REQ_enqueue_t *) request)->queue,
                ((OS_REQ_enqueue_t *) request)->args
            );
            break;
        case OS_REQ_id_DEQUEUE:
            status = OS_ISR_dequeue(
                ((OS_REQ_dequeue_t *) request)->task,
                ((OS_REQ_dequeue_t *) request)->queue,
                ((OS_REQ_enqueue_t *) request)->args
            );
            break;
    }

    request->status = status;
}


/*************************************************************
 * Description: (interrupt) Interrupt handler, responsible for context-switching.
 *                  Note: Must be the least priority in the whole system.
 * 
 *************************************************************/
void __attribute__ ((section(".after_vectors"), naked))
PendSV_Handler(void) {

        /* If not first time, skip to 'save'. */
    __asm("LDR R0, =prevTask");
    __asm("LDR R0, [ R0 ]");
    __asm("CBNZ R0, save");

__asm("init:");

        /* Unprivileged mode in thread state. */
    __asm("MRS R0, CONTROL");
    __asm("ORR R0, R0, #0x1");
    __asm("MSR CONTROL, R0");

        /* Skip to 'restore'. */
    __asm("B restore");

__asm("save:");
        
        /* Load 'PSP' into 'R0' and offset. */
    __asm("MRS R0, PSP");
    __asm("SUB R0, R0, #32");

        /* Save registers. */
    __asm("STMIA R0, {R4-R11}");

        /* Store 'PSP' in task-related info. */
    __asm("LDR R1, =prevTask");
    __asm("LDR R1, [ R1 ]");
    __asm("STR R0, [ R1 ]");

__asm("restore:");
    
        /* Get stack pointer of next task into 'R0'. */
    __asm("LDR R0, =nextTask");
    __asm("LDR R0, [ R0 ]");
    __asm("LDR R0, [ R0 ]");

        /* Restore registers. */
    __asm("LDMIA R0, {R4-R11}");

        /* Offset and store 'R0' into 'PSP'. */
    __asm("ADD R0, R0, #32");
    __asm("MSR PSP, R0");

    __asm("BX LR");
}


/*************************************************************
 * Description: (task) Idle task of the OS.
 * 
 *************************************************************/
static void OS_idleTask(void *args) {
    while (1);                      /* Infinite mind-less loop. */
}


/*************************************************************
 * Description: (static) Get highest priority task(s).
 * Parameters:
 *      [X]
 * Return:
 *      Pointer to 'OS_task'.
 *************************************************************/
static LL_list * OS_getHighestPriorityTasks(void) {
    uint8_t group_index = bitmap[groups];
    uint8_t task_index = bitmap[group[group_index]];

    return &tasks[8 * group_index + task_index];
}

static OS_task * OS_getHighestPriorityTask(void) {
    return (OS_task *) (OS_getHighestPriorityTasks()->head->data);
}


/*************************************************************
 * Description: (static) Schedule task.
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
static void OS_schedule(void) {
    OS_task *task = OS_getHighestPriorityTask();
    if (task != nextTask) {
        prevTask = nextTask;
        nextTask = task;
        PENDSV();
    }
}


/*************************************************************
 * Description: (static) Task into wait state.
 * Parameters:
 *      [1] Task.
 * Return:
 *      None.
 *************************************************************/
static void OS_makeTaskWait(OS_task *task) {
    LL_remove(&tasks[task->priority], &task->node);

    if (tasks[task->priority].length == 0) {
        OS_priorityOff(task->priority);
    }
}


/*************************************************************
 * Description: (static) Task into ready state.
 * Parameters:
 *      [1] Task.
 * Return:
 *      None.
 *************************************************************/
static void OS_makeTaskReady(OS_task *task) {
    LL_enqueue(&tasks[task->priority], &task->node);

    OS_priorityOn(task->priority);
}


/*************************************************************
 * Description: (static) Turns a specific priority on.
 * Parameters:
 *      [1] Priority.
 * Return:
 *      None.
 *************************************************************/
static void OS_priorityOn(uint8_t priority) {
    uint8_t group_index, task_index;

    group_index = priority >> 3;
    task_index = priority & 0b111;

    groups |= (1 << group_index);
    group[group_index] |= (1 << task_index);
}


/*************************************************************
 * Description: (static) Turns a specific priority off.
 * Parameters:
 *      [1] Priority.
 * Return:
 *      None.
 *************************************************************/
static void OS_priorityOff(uint8_t priority) {
    uint8_t group_index, task_index;

    group_index = priority >> 3;
    task_index = priority & 0b111;

    group[group_index] &= ~(1 << task_index);
    if (group[group_index] == 0) {
        groups &= ~(1 << group_index);
    }
}


/*************************************************************
 * Description: (static) Compare two tasks, which has higher priority.
 * Parameters:
 *      [1] Pointer to task 'A'.
 *      [2] Pointer to task 'B'.
 * Return:
 *      '1' if Task 'A' has higher priority, else '0'.
 *************************************************************/
static uint8_t OS_comparator(void *arg1, void *arg2) {
    uint8_t res = 0;

    if (((OS_task *) arg1)->priority < ((OS_task *) arg2)->priority) {
        res = 1;
    }

    return res;
}


/*************************************************************
 * Description: (static) Initialize stack.
 * Parameters:
 *      [1] Task.
 * Return:
 *      None.
 *************************************************************/
static void OS_stackInit(OS_task *task, void *args) {
    uint32_t *stackPtr = task->stackPtr;

	*--stackPtr = (uint32_t) (1 << 24);		// xPSR (Thumb-State Enabled)
	*--stackPtr = (uint32_t) task->fptr;	// Return Address
	*--stackPtr = (uint32_t) 14;			// LR (Note: Never returns from task.)
	*--stackPtr = (uint32_t) 12;			// R12
	*--stackPtr = (uint32_t) 3;				// R3
	*--stackPtr = (uint32_t) 2;				// R2
	*--stackPtr = (uint32_t) 1;				// R1
	*--stackPtr = (uint32_t) args;	        // R0 (args)

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
    AIRCR = (AIRCR & ~(MSK_I2J(PRIGROUP0, PRIGROUPN) | AIRCR_DEF_MSK)) | AIRCR_DEF | PRIGROUP_NO_PREMPT;

    OS_setupTask(&idleTask, OS_idleTask, NULL, PRIORITY_LOWEST, idleStack, IDLE_STACK_SIZE);
}


/*************************************************************
 * Description: Setup task.
 * Parameters:
 *      [1] Pointer to 'OS_task'.
 *      [2] Pointer to function, accepts argument as 'void *'.
 *      [3] Argument, as 'void *'.
 *      [4] Task priority.
 *      [5] Pointer to stack beginning.
 *      [6] Stack size.
 * Return:
 *      None.
 *************************************************************/
void OS_setupTask(OS_task *task, void (*fptr)(void *), void *args, 
        uint8_t priority, uint8_t *stackBegin, uint32_t stackSize) {
    uint8_t bit_group = priority >> 3;             /* Div 8. */
    uint8_t bit_task = priority & 0b111;           /* Mod 8. */

    groups |= (1 << bit_group);
    group[bit_group] |= (1 << bit_task);
    LL_enqueue(&tasks[priority], &task->node);

    task->fptr = fptr;
    task->stackPtr = (uint32_t *) ALIGN_8((uint32_t) (stackBegin + stackSize));
    task->priority = priority;
    task->delay = 0;
    task->node.data = (void *) task;
    task->state = OS_task_state_READY;

    OS_stackInit(task, args);
}


/*************************************************************
 * Description: Setup semaphore.
 * Parameters:
 *      [1] Pointer to 'OS_semaphore'.
 *      [2] Initial value.
 * Return:
 *      None.
 *************************************************************/
void OS_setupSemaphore(OS_semaphore *sem, uint32_t initial, uint32_t maximum) {
    sem->current = initial;
    sem->max = maximum;
}


/*************************************************************
 * Description: Setup queue.
 * Parameters:
 *      [1] Pointer to 'OS_queue'.
 *      [2] Array of 'void *'.
 *      [3] Array length.
 * Return:
 *      None.
 *************************************************************/
void OS_setupQueue(OS_queue *q, void **array, uint32_t length) {
    Queue_init(&q->queue, array, length);
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
    
        /* Set 'PSP' to stack pointer of idle task. */
    __asm("LDR R0, =idleTask");
    __asm("LDR R0, [ R0 ]");
    __asm("MSR PSP, R0");

        /* PSP selected. */
    __asm("MRS R0, CONTROL");
    __asm("ORR R0, R0, #0x2");
    __asm("MSR CONTROL, R0");

    nextTask = OS_getHighestPriorityTask();
    PENDSV();
}


/*************************************************************
 * Description: Put a task in the waiting state.
 * Parameters:
 *      [1] Pointer to task.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_wait(OS_task *task) {
    OS_REQ_wait_t req = {
        .base.id = OS_REQ_id_WAIT,
        .task = task
    };

    SVC_CALL();

    return req.base.status;
}


/*************************************************************
 * Description: (ISR-specific) Put a task in the waiting state.
 * Parameters:
 *      [1] Pointer to task.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_wait(OS_task *task) {
    OS_REQ_status_t status = OS_REQ_status_OK;

    if (task->state != OS_task_state_READY) {
        status = OS_REQ_status_NOK;
    } else {
        task->state = OS_task_state_WAITING;

        OS_makeTaskWait(task);
        LL_enqueue(&tasks_waiting, &task->node);

        OS_schedule();
    }

    return status;
}


/*************************************************************
 * Description: Put a task in the ready state.
 * Parameters:
 *      [1] Pointer to task.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ready(OS_task *task) {
    OS_REQ_ready_t req = {
        .base.id = OS_REQ_id_READY,
        .task = task
    };

    SVC_CALL();

    return req.base.status;
}


/*************************************************************
 * Description: (ISR-specific) Put a task in the ready state.
 * Parameters:
 *      [1] Pointer to task.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_ready(OS_task *task) {
    OS_REQ_status_t status = OS_REQ_status_OK;

    if (task->state != OS_task_state_WAITING) {
        status = OS_REQ_status_NOK;
    } else {
        task->state = OS_task_state_READY;

        LL_remove(&tasks_waiting, &task->node);
        OS_makeTaskReady(task);

        OS_schedule();
    }

    return status;
}


/*************************************************************
 * Description: Delay the execution of a task.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Delay (in ticks).
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_delay(OS_task *task, uint32_t delay) {
    volatile OS_REQ_delay_t req = {
        .base.id = OS_REQ_id_DELAY,
        .task = task,
        .delay = delay
    };

    SVC_CALL();

    return req.base.status;
}


/*************************************************************
 * Description: Delay the execution of a task.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Delay (in ticks).
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_delay(OS_task *task, uint32_t delay) {
    OS_REQ_status_t status = OS_REQ_status_OK;

    if (task->state != OS_task_state_READY) {
        status = OS_REQ_status_NOK;
    } else {
        task->state = OS_task_state_DELAYED;
        task->delay = delay;

        OS_makeTaskWait(task);
        LL_enqueue(&tasks_delayed, &task->node);

        OS_schedule();
    }

    return status;
}


/*************************************************************
 * Description: Increase semaphore's value.
 * Parameters:
 *      [1] Pointer to semaphore.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_give(OS_semaphore *sem) {
    volatile OS_REQ_give_t req = {
        .base.id = OS_REQ_id_GIVE,
        .sem = sem
    };

    SVC_CALL();

    return req.base.status;
}


/*************************************************************
 * Description: Increase semaphore's value.
 * Parameters:
 *      [1] Pointer to semaphore.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_give(OS_semaphore *sem) {
    OS_REQ_status_t status = OS_REQ_status_OK;

    if (sem->waiting.length > 0) {
        OS_task *task = (OS_task *) LL_pop(&sem->waiting)->data;
        OS_makeTaskReady(task);

        task->state = OS_task_state_READY;

        OS_schedule();
    } else if (sem->current < sem->max) {
        sem->current++;
    } else {
        status = OS_REQ_status_NOK;
    }

    return status;
}


/*************************************************************
 * Description: Decrease semaphore's value.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to semaphore.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_take(OS_task *task, OS_semaphore *sem) {
    volatile OS_REQ_take_t req = {
        .base.id = OS_REQ_id_TAKE,
        .task = task,
        .sem = sem
    };

    SVC_CALL();

    return req.base.status;
}


/*************************************************************
 * Description: Decrease semaphore's value.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to semaphore.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_take(OS_task *task, OS_semaphore *sem) {
    if (sem->current > 0) {
        sem->current--;
    } else {
        task->state = OS_task_state_WAITING_ON_SEMAPHORE;

        OS_makeTaskWait(task);
        LL_priority_enqueue(&sem->waiting, &task->node, &OS_comparator);

        OS_schedule();
    }

    return OS_REQ_status_OK;
}


/*************************************************************
 * Description: Enqueue.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to queue.
 *      [3] Argument, as 'void *'.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_enqueue(OS_task *task, OS_queue *queue, void *args) {
    volatile OS_REQ_enqueue_t req = {
        .base.id = OS_REQ_id_ENQUEUE,
        .task = task,
        .queue = queue,
        .args = args
    };

    SVC_CALL();

    return req.base.status;
}


/*************************************************************
 * Description: Enqueue.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to queue.
 *      [3] Argument, as 'void *'.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_enqueue(OS_task *task, OS_queue *q, void *args) {
    task->args = args;

    if (q->waiting_dequeue.length > 0) {
        OS_task *task_deq = (OS_task *) LL_dequeue(&q->waiting_dequeue)->data;
        OS_makeTaskReady(task_deq);

        task_deq->state = OS_task_state_READY;
        *((void **) task_deq->args) = task->args;

        OS_schedule();
    } else {
        Queue_status_t status = Queue_enqueue(&q->queue, task->args);
        
        if (status == Queue_status_Full) {
            task->state = OS_task_state_WAITING_TO_ENQUEUE;

            OS_makeTaskWait(task);
            LL_priority_enqueue(&q->waiting_enqueue, &task->node, &OS_comparator);

            OS_schedule();
        }
    }

    return OS_REQ_status_OK;
}


/*************************************************************
 * Description: Dequeue.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to queue.
 *      [3] Argument to return, as 'void **'.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_dequeue(OS_task *task, OS_queue *queue, void **args) {
    volatile OS_REQ_dequeue_t req = {
        .base.id = OS_REQ_id_DEQUEUE,
        .task = task,
        .queue = queue,
        .args = args
    };

    SVC_CALL();

    return req.base.status;
}


/*************************************************************
 * Description: Dequeue.
 * Parameters:
 *      [1] Pointer to task.
 *      [2] Pointer to queue.
 *      [3] Argument to return, as 'void **'.
 * Return:
 *      None.
 *************************************************************/
OS_REQ_status_t OS_ISR_dequeue(OS_task *task, OS_queue *q, void **args) {
    task->args = (void *) args;

    Queue_status_t status = Queue_dequeue(&q->queue, (void **) task->args);

    if (status == Queue_status_Empty) {
        task->state = OS_task_state_WAITING_TO_DEQUEUE;
        
        OS_makeTaskWait(task);
        LL_priority_enqueue(&q->waiting_dequeue, &task->node, &OS_comparator);

        OS_schedule();
    } else if (q->waiting_enqueue.length > 0) {
        OS_task *task_deq = (OS_task *) LL_dequeue(&q->waiting_enqueue)->data;
        OS_makeTaskReady(task_deq);

        task_deq->state = OS_task_state_READY;
        Queue_enqueue(&q->queue, task_deq->args);

        OS_schedule();
    }

    return OS_REQ_status_OK;
}