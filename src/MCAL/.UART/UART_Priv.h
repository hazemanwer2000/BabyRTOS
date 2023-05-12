/*************************************************************
 * 
 * Filename: UART_Priv.h
 * Description: Private header file of the UART driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __UART_PRIV_H__
#define __UART_PRIV_H__

#include "UART_Types.h"


/*************************************************************
 * Description: (Interrupt) UART.
 * 
 *************************************************************/
static void UART_IRQHandler(UART_module_t module);


#endif /* __UART_PRIV_H__ */