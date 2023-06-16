
#include "ssd1306.h"

#include "NVIC.h"
#include "RCC.h"
#include "SYSTICK.h"
#include "GPIO.h"
#include "OS.h"
#include "BUTTON.h"

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

				/* Peripherals */
			RCC_setPeripheralClockState(RCC_peripheral_GPIOA, RCC_clockState_On);
			RCC_setPeripheralClockState(RCC_peripheral_GPIOB, RCC_clockState_On);
			RCC_setPeripheralClockState(RCC_peripheral_I2C1, RCC_clockState_On);
			RCC_setPeripheralClockState(RCC_peripheral_DMA1, RCC_clockState_On);
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

void quickly_NVIC(void) {
	NVIC_setPriority(NVIC_interruptNumber_DMA1_Stream6, NVIC_priority_1);
	NVIC_enableInterrupt(NVIC_interruptNumber_DMA1_Stream6);
}

void quickly_GPIO(void) {
		/* I2C1 (SCL) */
	GPIO_pinConfiguration_t pinCfg = {
		.pinMode = GPIO_mode_AF_OpenDrain_PullUp,
		.port = GPIOB,
		.pinNumber = GPIO_pinNumber_6,
		.pinSpeed = GPIO_speed_VeryHigh
	};
	GPIO_initializePin(&pinCfg);
	GPIO_selectAF(pinCfg.port, pinCfg.pinNumber, GPIO_AF_4);

		/* I2C1 (SDA) */
	pinCfg.pinNumber = GPIO_pinNumber_7;
	GPIO_initializePin(&pinCfg);
	GPIO_selectAF(pinCfg.port, pinCfg.pinNumber, GPIO_AF_4);
}

#define GUI_TASK_PRIORITY					1
#define GUI_STACK_SIZE						4096
#define GUI_QUEUE_CAPACITY					5

#define BUTTON_TASK_PRIORITY				0
#define BUTTON_STACK_SIZE					2560

uint8_t GUI_stack[GUI_STACK_SIZE];
uint8_t debounce_stack[BUTTON_STACK_SIZE];

volatile OS_task GUI_task;
volatile OS_task debounce_task;

volatile void *GUI_queueArr[GUI_QUEUE_CAPACITY];

volatile OS_semaphore sem_I2C1;

volatile OS_queue GUI_queue;

typedef enum {
	GUI_state_BouncingBall = 0
} GUI_state_t;

void I2C1_TX_Handler(void) 
{
    OS_ISR_give(&sem_I2C1);
}

#define BB_RATE							1

GUI_stateHandler_BouncingBall(GUI_state_t *state, BUTTON_name_t name) {
	static int16_t x1, x2, y1, y2;
	static int16_t xdir = rate, ydir = rate;

	switch (name) {
		case BUTTON_name_UP:
			if (rate < BB_RATE_MAX) {
				rate++;
			}
			break;
		case BUTTON_name_DOWN:
			if (rate > BB_RATE_MIN) {
				rate--;
			}
			break;
	}

	const uint8_t xlimit = 128 - 1, ylimit = 64 - 1;
	const uint8_t dim = 5;
	const 

	int16_t x1 = 0, x2 = dim, y1 = 0, y2 = dim;
	int16_t xdir = rate, ydir = rate;

	uint8_t color = 0;

	while (1) 
	{
		x1 += xdir; x2 += xdir;
		y1 += ydir; y2 += ydir;

		if (x2 >= xlimit) {
			xdir = -1 * rate;
			x2 = xlimit;
			x1 = x2 - dim;
		} else if (x1 <= 0) {
			xdir = 1 * rate;
			x1 = 0;
			x2 = dim;
		}

		if (y2 >= ylimit) {
			ydir = -1 * rate;
			y2 = ylimit;
			y1 = y2 - dim;
		} else if (y1 <= 0) {
			ydir = 1 * rate;
			y1 = 0;
			y2 = dim;
		}

		color = 0;

		ssd1306_Fill(color);
		ssd1306_FillRectangle(x1, y1, x2, y2, !color);

		ssd1306_UpdateScreen();
	}
}

void GUI_taskHandler(void *args)
{
	Button_name_t buttonCurr, buttonPrev = BUTTON_name_Count, button;
	GUI_state_t state = GUI_state_BouncingBall;

	OS_delay(&GUI_task, 100);
	
	ssd1306_Init();

	while (1) {
		for (buttonCurr = 0; buttonCurr < BUTTON_name_Count; buttonCurr++) {
			if(BUTTON_get(buttonCurr)) {
				break;
			}
		}

		button = (buttonCurr != buttonPrev ? buttonCurr : BUTTON_name_Count);
		buttonPrev = buttonCurr;
		
		switch (state) {
			case GUI_state_BouncingBall:
				GUI_stateHandler_BouncingBall(&state, button);
				break;
		}

		ssd1306_UpdateScreen();
	}
}

void BUTTON_debounce_taskHandler(void *args) {
	while (1) {
		BUTTON_service_debounceHandling();
		OS_delay(NULL, 5);
	}
}

void main(void)
{
	if (quickly_RCC() != RCC_status_Ok) return;
	if (quickly_SYSTICK() != SYSTICK_status_Ok) return;
	
	quickly_GPIO();
	quickly_NVIC();

	BUTTON_init();

	I2C_init(I2C1);
	I2C_initDMAMode(I2C1);
	I2C_setCallbackTX(I2C1, &I2C1_TX_Handler);

	OS_init();

	OS_setupTask(&GUI_task, &GUI_taskHandler, NULL,
		GUI_TASK_PRIORITY, GUI_stack, GUI_STACK_SIZE);
	
	OS_setupTask(&debounce_task, &BUTTON_debounce_taskHandler, NULL,
		BUTTON_TASK_PRIORITY, debounce_stack, BUTTON_STACK_SIZE);

	OS_setupSemaphore(&sem_I2C1, 1, 1);

	OS_setupQueue(&GUI_queue, GUI_queueArr, GUI_QUEUE_CAPACITY);

	OS_start();
}