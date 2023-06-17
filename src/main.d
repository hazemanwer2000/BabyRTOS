main.o: main.c HAL/ssd1306/ssd1306.h HAL/ssd1306/ssd1306_conf.h \
 MCAL/I2C/I2C.h MCAL/I2C/I2C_Types.h MCAL/UTIL/Std_Types.h \
 HAL/ssd1306/ssd1306_fonts.h MCAL/NVIC/NVIC.h MCAL/NVIC/NVIC_Types.h \
 MCAL/NVIC/NVIC_Map.h MCAL/NVIC/NVIC_Priv.h UTIL/Bit_Utils.h \
 MCAL/RCC/RCC.h MCAL/RCC/RCC_Map.h MCAL/SYSTICK/SYSTICK.h \
 MCAL/SYSTICK/SYSTICK_Types.h MCAL/GPIO/GPIO.h MCAL/GPIO/GPIO_Map.h \
 OS/OS.h UTIL/LinkedList/LinkedList.h UTIL/Queue/Queue.h \
 HAL/BUTTON/BUTTON.h HAL/BUTTON/BUTTON_Cfg.h HAL/BUTTON/BUTTON_Types.h
	arm-none-eabi-gcc -c -I./OS -I./HAL/ssd1306 -I./HAL/LED -I./HAL/BUTTON -I./HAL/LCD -I./UTIL -I./UTIL/LinkedList -I./UTIL/Heap -I./UTIL/Queue -I./MCAL/RCC -I./MCAL/UART -I./MCAL/GPIO -I./MCAL/SYSTICK -I./MCAL/I2C -I./MCAL/UTIL -I./MCAL/NVIC -I./MCAL/DMA -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -std=c99 -g3 -Og -fno-move-loop-invariants -ffunction-sections -fdata-sections -nostartfiles -ffreestanding --specs=nano.specs main.c -o main.o