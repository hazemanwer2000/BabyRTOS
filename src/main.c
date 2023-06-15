
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

#define GUI_TASK_PRIORITY					0
#define GUI_STACK_SIZE						4096

uint8_t GUI_stack[GUI_STACK_SIZE];

volatile OS_task GUI_task;

void GUI_taskHandler(void *args)
{
	OS_delay(&GUI_task, 100);

	ssd1306_Init();

	const uint8_t xlimit = 128 - 1, ylimit = 64 - 1;
	const uint8_t dim = 20;
	const uint8_t rate = 1;

	int16_t x1 = 0, x2 = dim, y1 = 0, y2 = dim;
	int16_t xdir = rate, ydir = rate;

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

		ssd1306_Fill(White);
		ssd1306_FillRectangle(x1, y1, x2, y2, Black);

		ssd1306_UpdateScreen();
	}
}

volatile OS_semaphore sem_I2C1;
void I2C1_TX_Handler(void) 
{
    OS_ISR_give(&sem_I2C1);
}

void main(void)
{
	if (quickly_RCC() != RCC_status_Ok) return;
	if (quickly_SYSTICK() != SYSTICK_status_Ok) return;
	
	quickly_GPIO();
	quickly_NVIC();

	I2C_init(I2C1);
	I2C_initDMAMode(I2C1);
	I2C_setCallbackTX(I2C1, &I2C1_TX_Handler);

	OS_init();

	OS_setupTask(&GUI_task, &GUI_taskHandler, NULL,
		GUI_TASK_PRIORITY, GUI_stack, GUI_STACK_SIZE);

	OS_setupSemaphore(&sem_I2C1, 1, 1);

	OS_start();
}