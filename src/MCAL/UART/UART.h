/*************************************************************
 * 
 * Filename: UART.h
 * Description: Header (interface) file of the UART driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __UART_H__
#define __UART_H__

#include "UART_Types.h"
#include "UART_Map.h"


/*************************************************************
 * Description: Baud rate options (CLK = 25 Mhz, OVER8 = 0)
 * 
 *************************************************************/
#define UART_baudRate_115200                        0xD9


/*************************************************************
 * Description: Enable module.
 * Parameters:
 * 		[1] UART module.
 * Return:
 *      None.
 *************************************************************/
void UART_enable(UART_module_t module);


/*************************************************************
 * Description: Enable DMA mode.
 * Parameters:
 * 		[1] UART module.
 * Return:
 *      None.
 *************************************************************/
void UART_enableDMAMode(UART_module_t module);


/*************************************************************
 * Description: Set baud rate.
 * Parameters:
 * 		[1] UART module.
 *      [2] Baud-rate option.
 * Return:
 *      None.
 *************************************************************/
void UART_setBaudRate(UART_module_t module, UART_baudRate_t);


/*************************************************************
 * Description: Set callback function (TX).
 * Parameters:
 * 		[1] UART module.
 *      [2] Callback function.
 * Return:
 *      None.
 *************************************************************/
void UART_setCallbackTX(UART_module_t module, void (*callback)(void));


/*************************************************************
 * Description: Set callback function (RX).
 * Parameters:
 * 		[1] UART module.
 *      [2] Callback function.
 * Return:
 *      None.
 *************************************************************/
void UART_setCallbackRX(UART_module_t module, void (*callback)(void));


/*************************************************************
 * Description: Send buffer (non-blocking).
 * Parameters:
 * 		[1] UART module.
 *      [2] Buffer.
 *      [3] Size.
 * Return:
 *      Status.
 *************************************************************/
UART_status_t UART_sendBufferAsync(UART_module_t module, const uint8_t *buffer, uint32_t size);


/*************************************************************
 * Description: Receive buffer (non-blocking).
 * Parameters:
 * 		[1] UART module.
 *      [2] Buffer.
 *      [3] Size.
 * Return:
 *      Status.
 *************************************************************/
UART_status_t UART_recvBufferAsync(UART_module_t module, uint8_t *buffer, uint32_t size);


/*************************************************************
 * Description: Receive buffer (DMA).
 * Parameters:
 * 		[1] UART module.
 *      [2] Buffer.
 *      [3] Size.
 * Return:
 *      None.
 *************************************************************/
void UART_recvBufferDMA(UART_module_t module, uint8_t *buffer, uint16_t size);


/*************************************************************
 * Description: Send buffer (DMA).
 * Parameters:
 * 		[1] UART module.
 *      [2] Buffer.
 *      [3] Size.
 * Return:
 *      None.
 *************************************************************/
void UART_sendBufferDMA(UART_module_t module, uint8_t *buffer, uint16_t size);


#endif /* __UART_H__ */