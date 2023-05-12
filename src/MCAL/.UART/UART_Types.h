/*************************************************************
 * 
 * Filename: UART_Types.h
 * Description: Types header file of the UART driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __UART_TYPES_H__
#define __UART_TYPES_H__

#include "Std_Types.h"


/*************************************************************
 * Description: Type of module.
 *
 *************************************************************/
typedef enum {
    UART_module_1 = 0,
    UART_module_2,
    UART_module_6,

    UART_module_Count
} UART_module_t;


/*************************************************************
 * Description: Type of status.
 *
 *************************************************************/
typedef enum {
    UART_status_Ok,
    UART_status_Busy
} UART_status_t;


/*************************************************************
 * Description: Type of baud rate.
 *
 *************************************************************/
typedef uint16_t UART_baudRate_t;


#endif /* __UART_TYPES_H__ */