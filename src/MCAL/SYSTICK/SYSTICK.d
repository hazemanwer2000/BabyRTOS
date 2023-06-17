MCAL/SYSTICK/SYSTICK.o: MCAL/SYSTICK/SYSTICK.c MCAL/SYSTICK/SYSTICK_Cfg.h \
 MCAL/SYSTICK/SYSTICK_Priv.h MCAL/SYSTICK/SYSTICK_Types.h \
 MCAL/UTIL/Std_Types.h MCAL/SYSTICK/SYSTICK_Map.h MCAL/SYSTICK/SYSTICK.h \
 UTIL/Bit_Utils.h
	arm-none-eabi-gcc -c -I./OS -I./HAL/ssd1306 -I./HAL/LED -I./HAL/BUTTON -I./HAL/LCD -I./UTIL -I./UTIL/LinkedList -I./UTIL/Heap -I./UTIL/Queue -I./MCAL/RCC -I./MCAL/UART -I./MCAL/GPIO -I./MCAL/SYSTICK -I./MCAL/I2C -I./MCAL/UTIL -I./MCAL/NVIC -I./MCAL/DMA -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -std=c99 -g3 -Og -fno-move-loop-invariants -ffunction-sections -fdata-sections -nostartfiles -ffreestanding --specs=nano.specs MCAL/SYSTICK/SYSTICK.c -o MCAL/SYSTICK/SYSTICK.o