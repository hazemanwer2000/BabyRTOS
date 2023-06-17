MCAL/UART/UART.o: MCAL/UART/UART.c MCAL/UART/UART_Priv.h \
 MCAL/UART/UART_Types.h MCAL/UTIL/Std_Types.h MCAL/UART/UART.h \
 MCAL/UART/UART_Map.h MCAL/DMA/DMA.h MCAL/DMA/DMA_Types.h \
 MCAL/DMA/DMA_Map.h UTIL/Bit_Utils.h
	arm-none-eabi-gcc -c -I./OS -I./HAL/ssd1306 -I./HAL/LED -I./HAL/BUTTON -I./HAL/LCD -I./UTIL -I./UTIL/LinkedList -I./UTIL/Heap -I./UTIL/Queue -I./MCAL/RCC -I./MCAL/UART -I./MCAL/GPIO -I./MCAL/SYSTICK -I./MCAL/I2C -I./MCAL/UTIL -I./MCAL/NVIC -I./MCAL/DMA -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -std=c99 -g3 -Og -fno-move-loop-invariants -ffunction-sections -fdata-sections -nostartfiles -ffreestanding --specs=nano.specs MCAL/UART/UART.c -o MCAL/UART/UART.o