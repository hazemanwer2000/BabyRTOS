HAL/BUTTON/BUTTON.o: HAL/BUTTON/BUTTON.c HAL/BUTTON/BUTTON_Cfg.h \
 HAL/BUTTON/BUTTON_Types.h MCAL/GPIO/GPIO.h MCAL/GPIO/GPIO_Map.h \
 MCAL/UTIL/Std_Types.h HAL/BUTTON/BUTTON_Priv.h HAL/BUTTON/BUTTON.h \
 OS/OS.h UTIL/LinkedList/LinkedList.h UTIL/Queue/Queue.h
	arm-none-eabi-gcc -c -I./OS -I./HAL/ssd1306 -I./HAL/LED -I./HAL/BUTTON -I./HAL/LCD -I./UTIL -I./UTIL/LinkedList -I./UTIL/Heap -I./UTIL/Queue -I./MCAL/RCC -I./MCAL/UART -I./MCAL/GPIO -I./MCAL/SYSTICK -I./MCAL/I2C -I./MCAL/UTIL -I./MCAL/NVIC -I./MCAL/DMA -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -std=c99 -g3 -Og -fno-move-loop-invariants -ffunction-sections -fdata-sections -nostartfiles -ffreestanding --specs=nano.specs HAL/BUTTON/BUTTON.c -o HAL/BUTTON/BUTTON.o