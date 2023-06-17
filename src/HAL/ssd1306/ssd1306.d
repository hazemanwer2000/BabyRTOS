HAL/ssd1306/ssd1306.o: HAL/ssd1306/ssd1306.c HAL/ssd1306/ssd1306.h \
 HAL/ssd1306/ssd1306_conf.h MCAL/I2C/I2C.h MCAL/I2C/I2C_Types.h \
 MCAL/UTIL/Std_Types.h HAL/ssd1306/ssd1306_fonts.h OS/OS.h \
 UTIL/LinkedList/LinkedList.h UTIL/Queue/Queue.h
	arm-none-eabi-gcc -c -I./OS -I./HAL/ssd1306 -I./HAL/LED -I./HAL/BUTTON -I./HAL/LCD -I./UTIL -I./UTIL/LinkedList -I./UTIL/Heap -I./UTIL/Queue -I./MCAL/RCC -I./MCAL/UART -I./MCAL/GPIO -I./MCAL/SYSTICK -I./MCAL/I2C -I./MCAL/UTIL -I./MCAL/NVIC -I./MCAL/DMA -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -std=c99 -g3 -Og -fno-move-loop-invariants -ffunction-sections -fdata-sections -nostartfiles -ffreestanding --specs=nano.specs HAL/ssd1306/ssd1306.c -o HAL/ssd1306/ssd1306.o