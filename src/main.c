
#include "NVIC.h"
#include "RCC.h"
#include "SYSTICK.h"
#include "Std_Types.h"
#include "OS.h"

#define TICK_US								1000
#define SECOND								1000

RCC_status_t quickly_RCC(void) {
	RCC_status_t status = RCC_status_Ok;

	status = RCC_setSystemClockState(RCC_systemClock_HSE, RCC_clockState_On);
	if (status == RCC_status_Ok) {
		status = RCC_selectSystemClock(RCC_systemClock_HSE);
		if (status == RCC_status_Ok) {
			RCC_configureBusClock(RCC_bus_AHB, RCC_busPrescale_AHB_1);
			RCC_configureBusClock(RCC_bus_APB1, RCC_busPrescale_APB_1);
			RCC_configureBusClock(RCC_bus_APB2, RCC_busPrescale_APB_1);
		}
	}

	return status;
}

SYSTICK_status_t quickly_SYSTICK(void) {
	SYSTICK_status_t status = SYSTICK_status_Ok;

	SYSTICK_configureClockSource(SYSTICK_clockSource_AHB);
	status = SYSTICK_setPeriod_us(TICK_US);

	return status;
}

#define HIGH_TASK_PRIORITY				11
#define LOW_TASK_PRIORITY				23
#define STACK_SIZE						256

OS_task highTask;
OS_task high2Task;
OS_task high3Task;
OS_task lowTask;

uint8_t highStack[STACK_SIZE];
uint8_t high2Stack[STACK_SIZE];
uint8_t high3Stack[STACK_SIZE];
uint8_t lowStack[STACK_SIZE];

OS_semaphore sem;

#define QUEUE_CAP		1

OS_queue queue;
void *array[QUEUE_CAP];

typedef struct {
	uint32_t high;
	uint32_t high2;
	uint32_t high3;
	uint32_t low;
	uint32_t sync;
} counter_t;

counter_t counter;

void highTask_Handler(void *args) {
	while (1) {
		OS_enqueue(&highTask, &queue, (void *) ++counter.high);
	}
}

void high2Task_Handler(void *args) {
	while (1) {
		OS_delay(&high2Task, SECOND);
		OS_dequeue(&high2Task, &queue, &args);
		counter.high2 = (uint32_t) args;
	}
}

void high3Task_Handler(void *args) {
	while (1) {
		OS_delay(&high3Task, SECOND * 3);
		OS_dequeue(&high3Task, &queue, &args);
		counter.high3 = (uint32_t) args;
	}
}

void lowTask_Handler(void *args) {
	while (1) {
		// OS_delay(&lowTask, 1000);
		// counter.low++;
	}
}

void main(void) {
	if (quickly_RCC() != RCC_status_Ok) return;
	if (quickly_SYSTICK() != SYSTICK_status_Ok) return;

	OS_init();

	OS_setupTask(&highTask, &highTask_Handler, (void *) HIGH_TASK_PRIORITY,
		HIGH_TASK_PRIORITY, highStack, STACK_SIZE);

	OS_setupTask(&high2Task, &high2Task_Handler, (void *) HIGH_TASK_PRIORITY,
		HIGH_TASK_PRIORITY, high2Stack, STACK_SIZE);

	OS_setupTask(&high3Task, &high3Task_Handler, (void *) HIGH_TASK_PRIORITY,
		HIGH_TASK_PRIORITY, high3Stack, STACK_SIZE);

	OS_setupTask(&lowTask, &lowTask_Handler, (void *) LOW_TASK_PRIORITY,
		LOW_TASK_PRIORITY, lowStack, STACK_SIZE);

	OS_setupSemaphore(&sem, 0, 2);

	OS_setupQueue(&queue, array, QUEUE_CAP);

	OS_start();
}