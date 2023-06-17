MCAL/NVIC/NVIC.o: MCAL/NVIC/NVIC.c MCAL/NVIC/NVIC_Priv.h UTIL/Bit_Utils.h \
 MCAL/NVIC/NVIC_Types.h MCAL/UTIL/Std_Types.h MCAL/NVIC/NVIC.h \
 MCAL/NVIC/NVIC_Map.h
	arm-none-eabi-gcc -c -I./OS -I./HAL/ssd1306 -I./HAL/LED -I./HAL/BUTTON -I./HAL/LCD -I./UTIL -I./UTIL/LinkedList -I./UTIL/Heap -I./UTIL/Queue -I./MCAL/RCC -I./MCAL/UART -I./MCAL/GPIO -I./MCAL/SYSTICK -I./MCAL/I2C -I./MCAL/UTIL -I./MCAL/NVIC -I./MCAL/DMA -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -std=c99 -g3 -Og -fno-move-loop-invariants -ffunction-sections -fdata-sections -nostartfiles -ffreestanding --specs=nano.specs MCAL/NVIC/NVIC.c -o MCAL/NVIC/NVIC.o