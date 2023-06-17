
#include "ssd1306.h"

#include "NVIC.h"
#include "RCC.h"
#include "SYSTICK.h"
#include "GPIO.h"
#include "OS.h"
#include "BUTTON.h"
#include "LED.h"

#define SSD1306_MIN_DIM						MIN(SSD1306_HEIGHT, SSD1306_WIDTH)

#define NUM_2_CHAR(X)						((X) + '0')

#define MAX(X, Y)							((X) > (Y) ? (X) : (Y))
#define MIN(X, Y)							((X) < (Y) ? (X) : (Y))

int32_t min(int32_t x, int32_t y) {
	return MIN(x, y);
}

int32_t max(int32_t x, int32_t y) {
	return MAX(x, y);
}

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
#define BUTTON_STACK_SIZE					256

uint8_t GUI_stack[GUI_STACK_SIZE];
uint8_t debounce_stack[BUTTON_STACK_SIZE];
uint8_t buttonInput_stack[BUTTON_STACK_SIZE];

volatile OS_task GUI_task;
volatile OS_task debounce_task;
volatile OS_task buttonInput_task;

void * volatile buttonEvent_queueArr[GUI_QUEUE_CAPACITY];

volatile OS_semaphore sem_I2C1;

volatile OS_queue buttonEvent_queue;

typedef enum {
	GUI_state_BouncingBall = 0,
	GUI_state_Logo,
	GUI_state_StopWatch
} GUI_state_t;

typedef struct {
	int16_t x, y;
} Point_t;

void GUI_pointLimit(int16_t *val, int16_t *dir, uint8_t lim, uint8_t step) {
	*val += step * (*dir);

	if (*val < 0) {
		*val = 0;
		*dir = 1;
	} else if (*val >= lim) {
		*val = lim - 1;
		*dir = -1;
	}
}

#define AL_STEP_X1								1
#define AL_STEP_X2								2

#define AL_STEP_Y1								2
#define AL_STEP_Y2								1

void GUI_animation_Lines(uint8_t color) {
	static Point_t pt = {
		.x = 0,
		.y = SSD1306_HEIGHT / 2
	};

	static Point_t pt2 = {
		.x = (SSD1306_WIDTH / 4) * 3,
		.y = SSD1306_HEIGHT / 3
	};

	static Point_t dir = {
		.x = 1,
		.y = 1
	};

	static Point_t dir2 = {
		.x = 1,
		.y = -1
	};

	GUI_pointLimit(&pt.x, &dir.x, SSD1306_WIDTH, AL_STEP_X1);
	GUI_pointLimit(&pt2.x, &dir2.x, SSD1306_WIDTH, AL_STEP_X2);

	GUI_pointLimit(&pt.y, &dir.y, SSD1306_HEIGHT, AL_STEP_Y1);
	GUI_pointLimit(&pt2.y, &dir2.y, SSD1306_HEIGHT, AL_STEP_Y2);

	ssd1306_Line(pt.x, 0, pt2.x, SSD1306_HEIGHT - 1, color);
	ssd1306_Line(0, pt.y, SSD1306_WIDTH - 1, pt2.y, color);
}

#define BB_MIN_SPEED							1
#define BB_MAX_SPEED							5
#define BB_STEP_SPEED							1
#define BB_INIT_SPEED							((BB_MIN_SPEED + BB_MAX_SPEED) / 3)

#define BB_MIN_RADIUS							(((SSD1306_MIN_DIM / 6) * 2) / 2)
#define BB_MAX_RADIUS							(((SSD1306_MIN_DIM / 6) * 5) / 2)
#define BB_STEP_RADIUS							3
#define BB_INIT_RADIUS							((BB_MIN_RADIUS + BB_MAX_RADIUS) / 2)

void GUI_stateHandler_BouncingBall(GUI_state_t *state, BUTTON_name_t input)
{
	static int16_t radius = BB_INIT_RADIUS;
	static uint8_t speed = BB_INIT_SPEED;

	static Point_t dir = {
		.x = 1,
		.y = 1
	};

	static Point_t center = {
		.x = BB_MIN_RADIUS,
		.y = BB_MIN_RADIUS
	};

	static uint8_t color = 0;

	switch (input) 
	{
		case BUTTON_name_UP:
			radius += BB_STEP_RADIUS;
			if (radius > BB_MAX_RADIUS) {
				radius = BB_MAX_RADIUS;
			}
			break;
		case BUTTON_name_DOWN:
			radius -= BB_STEP_RADIUS;
			if (radius < BB_MIN_RADIUS) {
				radius = BB_MIN_RADIUS;
			}
			break;
		case BUTTON_name_LEFT:
			speed -= BB_STEP_SPEED;
			if (speed < BB_MIN_SPEED) {
				speed = BB_MIN_SPEED;
			}
			break;
		case BUTTON_name_RIGHT:
			speed += BB_STEP_SPEED;
			if (speed > BB_MAX_SPEED) {
				speed = BB_MAX_SPEED;
			}
			break;
		case BUTTON_name_ENTER:
			color = !color;
			break;
	}

	center.x += speed * dir.x;
	center.y += speed * dir.y;

	Point_t bounds_topLeft = {
		.x = center.x - radius,
		.y = center.y - radius
	};

	Point_t bounds_bottomRight = {
		.x = center.x + radius,
		.y = center.y + radius
	};

	if (bounds_topLeft.x < 0) {
		center.x = radius;
		dir.x = 1;
	} else if (bounds_bottomRight.x >= SSD1306_WIDTH) {
		center.x = SSD1306_WIDTH - radius - 1;
		dir.x = -1;
	}

	if (bounds_topLeft.y < 0) {
		center.y = radius;
		dir.y = 1;
	} else if (bounds_bottomRight.y >= SSD1306_HEIGHT) {
		center.y = SSD1306_HEIGHT - radius - 1;
		dir.y = -1;
	}

	ssd1306_Fill(color);
	ssd1306_FillCircle(center.x, center.y, radius - 1, !color);

	GUI_animation_Lines(color);
}

#define LOGO_STRING								"BabyRTOS."
#define LOGO_CHAR_COUNT							(sizeof(LOGO_STRING) - 1)
#define LOGO_BG_COLOR							Black
#define LOGO_FRAME_COUNT						(300)
#define LOGO_SLICT_COUNT						(LOGO_FRAME_COUNT / ((int) (LOGO_CHAR_COUNT * 1.75)))
#define LOGO_CURSOR_FLICKER_RATE				((LOGO_SLICT_COUNT * 3) / 4)
#define LOGO_FONT								Font_11x18
#define LOGO_OFFSET_Y							((SSD1306_HEIGHT - LOGO_FONT.FontHeight) / 2)
#define LOGO_OFFSET_X							((SSD1306_WIDTH - (LOGO_FONT.FontWidth * LOGO_CHAR_COUNT)) / 2)
#define LOGO_NEXT_STATE							GUI_state_StopWatch

void GUI_stateHandler_Logo(GUI_state_t *state, BUTTON_name_t input)
{
	
	static uint32_t timeout = 0;
	static uint32_t slice = 0;
	static uint32_t i = 0;
	static char buffer[LOGO_CHAR_COUNT] = {0};
	static const char *logoString = LOGO_STRING;
	static uint8_t cursorColor = 0;

	if (i < LOGO_CHAR_COUNT) {
		if (slice >= LOGO_SLICT_COUNT) {
			buffer[i] = logoString[i];
			buffer[i+1] = '\0';

			slice = 0; i++;
		}

		slice++;
	}

	if (timeout % LOGO_CURSOR_FLICKER_RATE == 0) {
		cursorColor = !cursorColor;
	}

	ssd1306_Fill(LOGO_BG_COLOR);
	ssd1306_SetCursor(LOGO_OFFSET_X, LOGO_OFFSET_Y);
	ssd1306_WriteString(buffer, LOGO_FONT, !LOGO_BG_COLOR);
	if (cursorColor == !LOGO_BG_COLOR) {
		ssd1306_WriteChar('|', LOGO_FONT, cursorColor);
	}
	GUI_animation_Lines(!LOGO_BG_COLOR);

	if (++timeout >= LOGO_FRAME_COUNT) {
		*state = LOGO_NEXT_STATE;
	}
}

#define SW_BG_COLOR								Black
#define SW_FONT									Font_16x26
#define SW_CHAR_COUNT							4
#define SW_OFFSET_Y								((SSD1306_HEIGHT - LOGO_FONT.FontHeight) / 2)
#define SW_OFFSET_X								((int) (SSD1306_WIDTH / 5.3))
#define SW_SLICE_COUNT							12
#define SW_TIME_MAX								59
#define SW_INDEX_LIMIT							2

void timeFormat(uint8_t num, char *buffer)
{
	buffer[0] = NUM_2_CHAR(num / 10);
	buffer[1] = NUM_2_CHAR(num % 10);
}

void GUI_stateHandler_StopWatch(GUI_state_t *state, BUTTON_name_t input)
{
	static int8_t time[2] = {0};
	static char buffer[2][3] = {0};
	static uint8_t index = 0;
	static uint8_t slice = 0;
	static uint8_t colors[2] = {!SW_BG_COLOR, !SW_BG_COLOR};

	switch (input) {
		case BUTTON_name_UP:
			time[index]++;
			if (time[index] >= SW_TIME_MAX) {
				time[index] = 0;
			}
			break;
		case BUTTON_name_DOWN:
			time[index]--;
			if (time[index] < 0) {
				time[index] = SW_TIME_MAX;
			}
			break;
		case BUTTON_name_LEFT:
			if (index > 0) {
				index--;
				slice = SW_SLICE_COUNT;
			}
			break;
		case BUTTON_name_RIGHT:
			index++;
			if (index == SW_INDEX_LIMIT) {
				index--;
				*state = GUI_state_BouncingBall;
			} else {
				slice = SW_SLICE_COUNT;
			}
			break;
	}

	if (++slice >= SW_SLICE_COUNT) {
		colors[index] = !colors[index];
		colors[!index] = !SW_BG_COLOR;
		slice = 0;
	}

	timeFormat(time[0], buffer[0]);
	timeFormat(time[1], buffer[1]);

	ssd1306_Fill(SW_BG_COLOR);
	ssd1306_SetCursor(SW_OFFSET_X, SW_OFFSET_Y);
	ssd1306_WriteString(buffer[0], SW_FONT, colors[0]);
	ssd1306_WriteChar(':', SW_FONT, !SW_BG_COLOR);
	ssd1306_WriteString(buffer[1], SW_FONT, colors[1]);

	GUI_animation_Lines(!SW_BG_COLOR);
}

#define GUI_INIT_STATE							GUI_state_StopWatch

void GUI_taskHandler(void *args)
{
	BUTTON_name_t button = BUTTON_name_Count;

	GUI_state_t state = GUI_INIT_STATE;

	OS_delay(&GUI_task, 100);
	
	ssd1306_Init();

	while (1) {
		if (buttonEvent_queue.queue.length > 0) {
			OS_dequeue(NULL, &buttonEvent_queue, (void **) &button);
		} else {
			button = BUTTON_name_Count;
		}

		switch (state) {
			case GUI_state_Logo:
				GUI_stateHandler_Logo(&state, button);
				break;
			case GUI_state_BouncingBall:
				GUI_stateHandler_BouncingBall(&state, button);
				break;
			case GUI_state_StopWatch:
				GUI_stateHandler_StopWatch(&state, button);
				break;
		}

		ssd1306_UpdateScreen();
	}
}

void I2C1_TX_Handler(void) 
{
    OS_ISR_give(&sem_I2C1);
}

void BUTTON_debounce_taskHandler(void *args) {
	while (1) {
		BUTTON_service_debounceHandling();
		OS_delay(NULL, 5);
	}
}

void BUTTON_input_taskHandler(void *args) {
	BUTTON_name_t buttonCurr, buttonPrev = BUTTON_name_Count, button;

	while (1) {
		for (buttonCurr = 0; buttonCurr < BUTTON_name_Count; buttonCurr++) {
			if(BUTTON_get(buttonCurr)) {
				break;
			}
		}

		button = (buttonCurr != buttonPrev ? buttonCurr : BUTTON_name_Count);
		buttonPrev = buttonCurr;

		OS_enqueue(NULL, &buttonEvent_queue, (void *) button);

		OS_delay(NULL, 50);
	}
}

void main(void)
{
	if (quickly_RCC() != RCC_status_Ok) return;
	if (quickly_SYSTICK() != SYSTICK_status_Ok) return;
	
	quickly_GPIO();
	quickly_NVIC();

	BUTTON_init();
	LED_init();

	I2C_init(I2C1);
	I2C_initDMAMode(I2C1);
	I2C_setCallbackTX(I2C1, &I2C1_TX_Handler);

	OS_init();

	OS_setupTask(&GUI_task, &GUI_taskHandler, NULL,
		GUI_TASK_PRIORITY, GUI_stack, GUI_STACK_SIZE);
	
	OS_setupTask(&debounce_task, &BUTTON_debounce_taskHandler, NULL,
		BUTTON_TASK_PRIORITY, debounce_stack, BUTTON_STACK_SIZE);

	OS_setupTask(&buttonInput_task, &BUTTON_input_taskHandler, NULL,
		BUTTON_TASK_PRIORITY, buttonInput_stack, BUTTON_STACK_SIZE);

	OS_setupSemaphore(&sem_I2C1, 1, 1);

	OS_setupQueue(&buttonEvent_queue, buttonEvent_queueArr, GUI_QUEUE_CAPACITY);

	OS_start();
}