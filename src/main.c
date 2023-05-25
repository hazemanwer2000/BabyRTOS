
#include "NVIC.h"
#include "RCC.h"
#include "SYSTICK.h"
#include "Std_Types.h"
#include "OS.h"

#define TICK_US								1000

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
OS_task lowTask;

uint8_t highStack[STACK_SIZE];
uint8_t high2Stack[STACK_SIZE];
uint8_t lowStack[STACK_SIZE];

volatile uint32_t counter = 0;
volatile uint32_t counter2 = 0;

void highTask_Handler(void *args) {
	while (1) {
		counter++;
	}
}

void high2Task_Handler(void *args) {
	while (1) {
		counter2++;		
	}
}

void lowTask_Handler(void *args) {
	while (1) {}
}

void main(void) {
	if (quickly_RCC() != RCC_status_Ok) return;
	if (quickly_SYSTICK() != SYSTICK_status_Ok) return;

	OS_init();

	OS_setupTask(&highTask, &highTask_Handler, (void *) HIGH_TASK_PRIORITY,
		HIGH_TASK_PRIORITY, highStack, STACK_SIZE);

	OS_setupTask(&high2Task, &high2Task_Handler, (void *) HIGH_TASK_PRIORITY,
		HIGH_TASK_PRIORITY, high2Stack, STACK_SIZE);

	OS_setupTask(&lowTask, &lowTask_Handler, (void *) LOW_TASK_PRIORITY,
		LOW_TASK_PRIORITY, lowStack, STACK_SIZE);

	OS_start();
}