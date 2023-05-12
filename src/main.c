
#include "NVIC.h"
#include "RCC.h"
#include "GPIO.h"
#include "UART.h"

#include "LED.h"
#include "BUTTON.h"
#include "SCHED.h"
#include "LCD.h"

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

			// Enable Peripherals' Clock
			RCC_setPeripheralClockState(RCC_peripheral_GPIOA, RCC_clockState_On);
			RCC_setPeripheralClockState(RCC_peripheral_GPIOB, RCC_clockState_On);
		}
	}

	return status;
}

#define STACK_SIZE			400

uint8_t stack1[STACK_SIZE];
uint8_t stack2[STACK_SIZE];

void *stack1_ptr = (void *) (&stack1 + STACK_SIZE);
void *stack2_ptr = (void *) (&stack2 + STACK_SIZE);

void main(void) {
	if (quickly_RCC() == RCC_status_Ok) {
		
	}

	while (1); 		/* Something went wrong... */
}
