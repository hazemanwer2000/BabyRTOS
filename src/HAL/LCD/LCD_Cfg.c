/*************************************************************
 * 
 * Filename: LCD_Cfg.c
 * Description: Configuration source file of the LCD driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "LCD_Cfg.h"
#include "LCD_Types.h"
#include "LCD.h"

#include "GPIO.h"


/*************************************************************
 * Description: LCD configuration.
 * 
 *************************************************************/
LCD_cfg_t LCD_cfg = {
    .port = GPIOB,
    .pinNumber_D = {
        GPIO_pinNumber_12,
        GPIO_pinNumber_13,
        GPIO_pinNumber_14,
        GPIO_pinNumber_15
    },
    .pinNumber_RS = GPIO_pinNumber_1,
    .pinNumber_E = GPIO_pinNumber_2
};