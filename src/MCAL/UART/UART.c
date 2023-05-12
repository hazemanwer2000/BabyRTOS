/*************************************************************
 * 
 * Filename: UART.c
 * Description: Source file of the UART driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "UART_Priv.h"
#include "UART_Types.h"
#include "UART.h"

#include "DMA.h"

#include "Std_Types.h"
#include "Bit_Utils.h"


/*************************************************************
 * Description: TX tracking variables.
 * 
 *************************************************************/
static const uint8_t *UART_TX_buffer[UART_module_Count];
static uint32_t UART_TX_size[UART_module_Count];
static uint32_t UART_TX_idx[UART_module_Count];
static void (*UART_TX_callback[UART_module_Count])(void);


/*************************************************************
 * Description: RX tracking variables.
 * 
 *************************************************************/
static uint8_t *UART_RX_buffer[UART_module_Count];
static uint32_t UART_RX_size[UART_module_Count];
static uint32_t UART_RX_idx[UART_module_Count];
static void (*UART_RX_callback[UART_module_Count])(void);


/*************************************************************
 * Description: Register files of the UART modules.
 * 
 *************************************************************/
static volatile UART_t *UART_regs[UART_module_Count] = {
    [UART_module_1] = UART1,
    [UART_module_2] = UART2,
    [UART_module_6] = UART6
};


/*************************************************************
 * Description: Mapping UART modules to DMA modules.
 * 
 *************************************************************/
static DMA_module_t UART_mapToDMAModuleRX[UART_module_Count] = {
    [UART_module_1] = DMA_module_USART1_RX,
    [UART_module_2] = DMA_module_USART2_RX,
    [UART_module_6] = DMA_module_USART6_RX
};

static DMA_module_t UART_mapToDMAModuleTX[UART_module_Count] = {
    [UART_module_1] = DMA_module_USART1_TX,
    [UART_module_2] = DMA_module_USART2_TX,
    [UART_module_6] = DMA_module_USART6_TX
};


/*************************************************************
 * Description: Mapping UART modules to DMA streams.
 * 
 *************************************************************/
static DMA_module_t UART_mapToDMAStreamRX[UART_module_Count] = {
    [UART_module_1] = DMA_stream_USART1_RX,
    [UART_module_2] = DMA_stream_USART2_RX,
    [UART_module_6] = DMA_stream_USART6_RX
};

static DMA_module_t UART_mapToDMAStreamTX[UART_module_Count] = {
    [UART_module_1] = DMA_stream_USART1_TX,
    [UART_module_2] = DMA_stream_USART2_TX,
    [UART_module_6] = DMA_stream_USART6_TX
};


/*************************************************************
 * Description: Mapping UART modules to DMA channels.
 * 
 *************************************************************/
static DMA_module_t UART_mapToDMAChannelRX[UART_module_Count] = {
    [UART_module_1] = DMA_channel_USART1_RX,
    [UART_module_2] = DMA_channel_USART2_RX,
    [UART_module_6] = DMA_channel_USART6_RX
};

static DMA_module_t UART_mapToDMAChannelTX[UART_module_Count] = {
    [UART_module_1] = DMA_channel_USART1_TX,
    [UART_module_2] = DMA_channel_USART2_TX,
    [UART_module_6] = DMA_channel_USART6_TX
};


/*************************************************************
 * Description: (Interrupt) UART6.
 * 
 *************************************************************/
void __attribute__ ((section(".after_vectors")))
USART1_IRQHandler(void) {
	UART_IRQHandler(UART_module_1);
}


/*************************************************************
 * Description: (Interrupt) UART6.
 * 
 *************************************************************/
void __attribute__ ((section(".after_vectors")))
USART2_IRQHandler(void) {
	UART_IRQHandler(UART_module_2);
}


/*************************************************************
 * Description: (Interrupt) UART6.
 * 
 *************************************************************/
void __attribute__ ((section(".after_vectors")))
USART6_IRQHandler(void) {
	UART_IRQHandler(UART_module_6);
}


/*************************************************************
 * Description: (Interrupt) UART.
 * 
 *************************************************************/
static void UART_IRQHandler(UART_module_t module) {
    if (GET_BIT(UART_regs[module]->SR, TXE)) {          /* 'TXE' flag */
        if (UART_TX_idx[module] < UART_TX_size[module]) {
            UART_regs[module]->DR = UART_TX_buffer[module][UART_TX_idx[module]++];
        } else {
            UART_TX_buffer[module] = NULL;
            UART_regs[module]->CR1 &= ~(1 << TXEIE);   /* Disable 'TXE' interrupt */
            if (UART_TX_callback[module] != NULL) {
                UART_TX_callback[module]();
            }
        }
    }

    if (GET_BIT(UART_regs[module]->SR, RXNE)) {          /* 'RXNE' flag */
        UART_RX_buffer[module][UART_RX_idx[module]++] = UART_regs[module]->DR;
        if (UART_RX_idx[module] >= UART_RX_size[module]) {
            UART_RX_buffer[module] = NULL;
            UART_regs[module]->CR1 &= ~(1 << RXNEIE);   /* Disable 'RXNE' interrupt */
            if (UART_RX_callback[module] != NULL) {
                UART_RX_callback[module]();
            }
        }
    }
}


/*************************************************************
 * Description: Enable module.
 * Parameters:
 * 		[1] UART module.
 * Return:
 *      None.
 *************************************************************/
void UART_enable(UART_module_t module) {
    UART_regs[module]->CR1 |= (1 << UE) | (1 << TE) | (1 << RE);
}


/*************************************************************
 * Description: Enable DMA mode.
 * Parameters:
 * 		[1] UART module.
 * Return:
 *      None.
 *************************************************************/
void UART_enableDMAMode(UART_module_t module) {
    DMA_module_t moduleDMA_RX = UART_mapToDMAModuleRX[module];
    DMA_stream_t streamDMA_RX = UART_mapToDMAStreamRX[module];

    DMA_module_t moduleDMA_TX = UART_mapToDMAModuleTX[module];
    DMA_stream_t streamDMA_TX = UART_mapToDMAStreamTX[module];

        /* DMA (RX) */
    DMA_enableInterrupt(moduleDMA_RX, streamDMA_RX, DMA_interrupt_TransferComplete);
    DMA_selectChannel(moduleDMA_RX, streamDMA_RX, UART_mapToDMAChannelRX[module]);
    DMA_selectDataDirection(moduleDMA_RX, streamDMA_RX, DMA_dataDirection_PeripheralToMemory);
    DMA_selectDataSize(moduleDMA_RX, streamDMA_RX, DMA_dataSize_Byte);
    DMA_selectMemoryIncrementMode(moduleDMA_RX, streamDMA_RX, DMA_incrementMode_PerTransfer);
    DMA_selectPeripheralIncrementMode(moduleDMA_RX, streamDMA_RX, DMA_incrementMode_Fixed);
    DMA_setPeripheralAddress(moduleDMA_RX, streamDMA_RX, (void *) &UART_regs[module]->DR);

        /* DMA (TX) */
    DMA_enableInterrupt(moduleDMA_TX, streamDMA_TX, DMA_interrupt_TransferComplete);
    DMA_selectChannel(moduleDMA_TX, streamDMA_TX, UART_mapToDMAChannelTX[module]);
    DMA_selectDataDirection(moduleDMA_TX, streamDMA_TX, DMA_dataDirection_MemoryToPeripheral);
    DMA_selectDataSize(moduleDMA_TX, streamDMA_TX, DMA_dataSize_Byte);
    DMA_selectMemoryIncrementMode(moduleDMA_TX, streamDMA_TX, DMA_incrementMode_PerTransfer);
    DMA_selectPeripheralIncrementMode(moduleDMA_TX, streamDMA_TX, DMA_incrementMode_Fixed);
    DMA_setPeripheralAddress(moduleDMA_TX, streamDMA_TX, (void *) &UART_regs[module]->DR);

        /* UART */
    UART_regs[module]->CR3 |= (1 << DMAT) | (1 << DMAR);
}


/*************************************************************
 * Description: Set baud rate.
 * Parameters:
 * 		[1] UART module.
 *      [2] Baud-rate option.
 * Return:
 *      None.
 *************************************************************/
void UART_setBaudRate(UART_module_t module, UART_baudRate_t baudRate) {
    UART_regs[module]->BRR = baudRate;
}


/*************************************************************
 * Description: Set callback function (TX).
 * Parameters:
 * 		[1] UART module.
 *      [2] Callback function.
 * Return:
 *      None.
 *************************************************************/
void UART_setCallbackTX(UART_module_t module, void (*callback)(void)) {
    UART_TX_callback[module] = callback;
}


/*************************************************************
 * Description: Set callback function (RX).
 * Parameters:
 * 		[1] UART module.
 *      [2] Callback function.
 * Return:
 *      None.
 *************************************************************/
void UART_setCallbackRX(UART_module_t module, void (*callback)(void)) {
    UART_RX_callback[module] = callback;
}


/*************************************************************
 * Description: Send buffer (non-blocking).
 * Parameters:
 * 		[1] UART module.
 *      [2] Buffer.
 *      [3] Size.
 * Return:
 *      Status.
 *************************************************************/
UART_status_t UART_sendBufferAsync(UART_module_t module, const uint8_t *buffer, uint32_t size) {
    UART_status_t status = UART_status_Ok;
    
    if (UART_TX_buffer[module] == NULL) {
        UART_TX_buffer[module] = buffer;
        UART_TX_size[module] = size;
        UART_TX_idx[module] = 0;
            
            /* Send first byte, and enable 'TXE' interrupt */
        UART_regs[module]->DR = UART_TX_buffer[module][UART_TX_idx[module]++];
        UART_regs[module]->CR1 |= (1 << TXEIE);
    } else {
        status = UART_status_Busy;       
    }

    return status;
}


/*************************************************************
 * Description: Receive buffer (non-blocking).
 * Parameters:
 * 		[1] UART module.
 *      [2] Buffer.
 *      [3] Size.
 * Return:
 *      Status.
 *************************************************************/
UART_status_t UART_recvBufferAsync(UART_module_t module, uint8_t *buffer, uint32_t size) {
    UART_status_t status = UART_status_Ok;
    
    if (UART_RX_buffer[module] == NULL) {
        UART_RX_buffer[module] = buffer;
        UART_RX_size[module] = size;
        UART_RX_idx[module] = 0;

        UART_regs[module]->SR &= ~(1 << RXNE);     /* Clear 'RXNE' flag */
        UART_regs[module]->CR1 |= (1 << RXNEIE);   /* Enable 'RXNE' interrupt */
    } else {
        status = UART_status_Busy;       
    }

    return status;
}


/*************************************************************
 * Description: Receive buffer (DMA).
 * Parameters:
 * 		[1] UART module.
 *      [2] Buffer.
 *      [3] Size.
 * Return:
 *      None.
 *************************************************************/
void UART_recvBufferDMA(UART_module_t module, uint8_t *buffer, uint16_t size) {
    DMA_module_t moduleDMA_RX = UART_mapToDMAModuleRX[module];
    DMA_stream_t streamDMA_RX = UART_mapToDMAStreamRX[module];

    DMA_setCallback(moduleDMA_RX, streamDMA_RX, UART_RX_callback[module]);
    DMA_setMemoryAddress(moduleDMA_RX, streamDMA_RX, buffer);
    DMA_setItemCount(moduleDMA_RX, streamDMA_RX, size);
    DMA_enable(moduleDMA_RX, streamDMA_RX);
}


/*************************************************************
 * Description: Send buffer (DMA).
 * Parameters:
 * 		[1] UART module.
 *      [2] Buffer.
 *      [3] Size.
 * Return:
 *      None.
 *************************************************************/
void UART_sendBufferDMA(UART_module_t module, uint8_t *buffer, uint16_t size) {
    DMA_module_t moduleDMA_TX = UART_mapToDMAModuleTX[module];
    DMA_stream_t streamDMA_TX = UART_mapToDMAStreamTX[module];

    DMA_setCallback(moduleDMA_TX, streamDMA_TX, UART_TX_callback[module]);
    DMA_setMemoryAddress(moduleDMA_TX, streamDMA_TX, buffer);
    DMA_setItemCount(moduleDMA_TX, streamDMA_TX, size);
    DMA_enable(moduleDMA_TX, streamDMA_TX);
}
