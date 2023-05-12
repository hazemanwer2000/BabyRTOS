
#include "NVIC.h"
#include "RCC.h"
#include "SYSTICK.h"

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

#define STACK_SIZE			400
#define TICK_US				500000

uint8_t stack1[STACK_SIZE];
uint8_t stack2[STACK_SIZE];

void *stack1_ptr = (void *) (&stack1 + STACK_SIZE);
void *stack2_ptr = (void *) (&stack2 + STACK_SIZE);

uint64_t counter = 0;

void SYSTICK_callback() {
	counter++;
}

void main(void) {
	if (quickly_RCC() == RCC_status_Ok) {

		// Configure SysTick
		SYSTICK_enableException();
		SYSTICK_setPeriod_us(TICK_US);
		SYSTICK_setCallback(&SYSTICK_callback);
		SYSTICK_enable();
	}

	while (1); 		/* Something went wrong... */
}
