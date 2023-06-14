
#include "ssd1306.h"

#include "NVIC.h"
#include "RCC.h"
#include "SYSTICK.h"
#include "GPIO.h"
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

				/* Peripherals */
			RCC_setPeripheralClockState(RCC_peripheral_GPIOB, RCC_clockState_On);
			RCC_setPeripheralClockState(RCC_peripheral_I2C1, RCC_clockState_On);
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

#define HIGH_TASK_PRIORITY				0
#define MED_TASK_PRIORITY				1
#define LOW_TASK_PRIORITY				2
#define STACK_SIZE						256

OS_task highTask;
OS_task medTask;
OS_task lowTask;

uint8_t highStack[STACK_SIZE];
uint8_t medStack[STACK_SIZE];
uint8_t lowStack[STACK_SIZE];

OS_semaphore sem;
OS_mutex m;
#define QUEUE_CAP		20
OS_queue queue;
void *array[QUEUE_CAP];

typedef struct {
	uint32_t high;
	uint32_t med;
	uint32_t low;
} counter_t;

counter_t counter;

void highTask_Handler(void *args) {
	while (1) {
		OS_lock(&highTask, &m);
		OS_delay(&highTask, 1000);
		OS_unlock(&highTask, &m);
	}
}

void medTask_Handler(void *args) {
	while (1) {
		OS_lock(&medTask, &m);
		counter.med++;
		OS_unlock(&medTask, &m);
	}
}

void lowTask_Handler(void *args) {
	while (1) {
		OS_wait(&lowTask);
	}
}

void main(void) {
	if (quickly_RCC() != RCC_status_Ok) return;
	if (quickly_SYSTICK() != SYSTICK_status_Ok) return;
	quickly_GPIO();
	I2C_init(I2C1);
	I2C_initDMAMode(I2C1);
	ssd1306_Init();

	const uint8_t xlimit = 128 - 1, ylimit = 64 - 1;
	const uint8_t xdim = 10, ydim = 10;
	const uint8_t rate = 3;

	int16_t x1 = 0, x2 = xdim, y1 = 0, y2 = ydim;
	int16_t xdir = rate, ydir = rate;

	while (1) {
		x1 += xdir; x2 += xdir;
		y1 += ydir; y2 += ydir;

		if (x2 >= xlimit) {
			xdir = -1 * rate;
			x2 = xlimit;
			x1 = x2 - xdim;
		} else if (x1 <= 0) {
			xdir = 1 * rate;
			x1 = 0;
			x2 = xdim;
		}

		if (y2 >= ylimit) {
			ydir = -1 * rate;
			y2 = ylimit;
			y1 = y2 - ydim;
		} else if (y1 <= 0) {
			ydir = 1 * rate;
			y1 = 0;
			y2 = ydim;
		}

		ssd1306_FillRectangle(0, 0, xlimit, ylimit, White);
		ssd1306_FillRectangle(x1, y1, x2, y2, Black);
		ssd1306_UpdateScreen();
	}

	while (1);

/*
	OS_init();

	OS_setupTask(&highTask, &highTask_Handler, (void *) HIGH_TASK_PRIORITY,
		HIGH_TASK_PRIORITY, highStack, STACK_SIZE);

	OS_setupTask(&medTask, &medTask_Handler, (void *) MED_TASK_PRIORITY,
		MED_TASK_PRIORITY, medStack, STACK_SIZE);

	OS_setupTask(&lowTask, &lowTask_Handler, (void *) LOW_TASK_PRIORITY,
		LOW_TASK_PRIORITY, lowStack, STACK_SIZE);

	OS_setupSemaphore(&sem, 0, 2);
	OS_setupQueue(&queue, array, QUEUE_CAP);
	OS_setupMutex(&m);

	OS_start();
*/

}