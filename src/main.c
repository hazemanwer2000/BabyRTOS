
#include "NVIC.h"
#include "RCC.h"

#include "Std_Types.h"

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

#define STACK_SIZE			(256 / 4)
#define TICK_US				500000

volatile uint32_t stack1[STACK_SIZE];
volatile uint32_t stack2[STACK_SIZE];

volatile uint32_t *stack1_ptr = (volatile uint32_t *) (stack1 + STACK_SIZE);
volatile uint32_t *stack2_ptr = (volatile uint32_t *) (stack2 + STACK_SIZE);

volatile uint64_t counter = 0;

void task1() {
	while (1) {
		if (counter < 1000) {
			counter++;
		}
	}
}

void task2() {
	while (1) {
		if (counter > 0) {
			counter--;
		}
	}
}

void __attribute__ ((section(".after_vectors"), naked))
PendSV_Handler (void) {
	__asm("LDR R0, =stack1_ptr");
	__asm("LDR SP, [ R0 ]");
	__asm("POP {R4-R11}");
	__asm("BX LR");
}

void stack_init(volatile uint32_t **stack_ptr, void (*task_ptr)(void)) {
	*--*stack_ptr = (uint32_t) (1 << 24);		// xPSR (Thumb-State Enabled)
	*--*stack_ptr = (uint32_t) task_ptr;		// Return Address
	*--*stack_ptr = (uint32_t) 14;				// LR (Note: Never returns from task.)
	*--*stack_ptr = (uint32_t) 12;				// R12
	*--*stack_ptr = (uint32_t) 3;				// R3
	*--*stack_ptr = (uint32_t) 2;				// R2
	*--*stack_ptr = (uint32_t) 1;				// R1
	*--*stack_ptr = (uint32_t) 0;				// R0

	*--*stack_ptr = (uint32_t) 11;				// R11
	*--*stack_ptr = (uint32_t) 10;				// R10
	*--*stack_ptr = (uint32_t) 9;				// R9
	*--*stack_ptr = (uint32_t) 8;				// R8
	*--*stack_ptr = (uint32_t) 7;				// R7
	*--*stack_ptr = (uint32_t) 6;				// R6
	*--*stack_ptr = (uint32_t) 5;				// R5
	*--*stack_ptr = (uint32_t) 4;				// R4
}

void main(void) {
	if (quickly_RCC() == RCC_status_Ok) {

		stack_init(&stack1_ptr, &task1);
		stack_init(&stack2_ptr, &task2);

		*(volatile uint32_t *) 0xE000ED04 |= (1 << 28);
	}

	while (1); 		/* Something went wrong... */
}
