/*************************************************************
 * 
 * Filename: DMA.h
 * Description: Header (interface) file of the DMA driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __DMA_H__
#define __DMA_H__

#include "DMA_Types.h"


/*************************************************************
 * Description: DMA module options.
 * 
 *************************************************************/
#define DMA_module_USART1_RX                    DMA_module_2
#define DMA_module_USART1_TX                    DMA_module_2

#define DMA_module_USART2_RX                    DMA_module_1
#define DMA_module_USART2_TX                    DMA_module_1

#define DMA_module_USART6_RX                    DMA_module_2
#define DMA_module_USART6_TX                    DMA_module_2


/*************************************************************
 * Description: DMA stream options.
 * 
 *************************************************************/
#define DMA_stream_USART1_RX                    DMA_stream_2
#define DMA_stream_USART1_TX                    DMA_stream_7

#define DMA_stream_USART2_RX                    DMA_stream_5
#define DMA_stream_USART2_TX                    DMA_stream_6

#define DMA_stream_USART6_RX                    DMA_stream_2
#define DMA_stream_USART6_TX                    DMA_stream_7


/*************************************************************
 * Description: DMA interrupt option.
 * 
 *************************************************************/
#define DMA_interrupt_TransferComplete          (1 << 3)


/*************************************************************
 * Description: DMA channel option.
 * 
 *************************************************************/
#define DMA_channel_0                           0
#define DMA_channel_1                           1
#define DMA_channel_2                           2
#define DMA_channel_3                           3
#define DMA_channel_4                           4
#define DMA_channel_5                           5
#define DMA_channel_6                           6
#define DMA_channel_7                           7

#define DMA_channel_USART1_RX                   DMA_channel_4
#define DMA_channel_USART1_TX                   DMA_channel_4

#define DMA_channel_USART2_RX                   DMA_channel_4
#define DMA_channel_USART2_TX                   DMA_channel_4

#define DMA_channel_USART6_RX                   DMA_channel_5
#define DMA_channel_USART6_TX                   DMA_channel_5


/*************************************************************
 * Description: DMA data size option.
 * 
 *************************************************************/
#define DMA_dataSize_Byte                       0
#define DMA_dataSize_HalfWord                   1
#define DMA_dataSize_Word                       2


/*************************************************************
 * Description: DMA data direction option.
 * 
 *************************************************************/
#define DMA_dataDirection_PeripheralToMemory        0
#define DMA_dataDirection_MemoryToPeripheral        1


/*************************************************************
 * Description: DMA increment mode option.
 * 
 *************************************************************/
#define DMA_incrementMode_Fixed                 0
#define DMA_incrementMode_PerTransfer           1


/*************************************************************
 * Description: API(s).
 * 
 *************************************************************/
void DMA_enableInterrupt(DMA_module_t, DMA_stream_t, DMA_interrupt_t);
void DMA_clearInterruptFlags(DMA_module_t, DMA_stream_t);

void DMA_selectChannel(DMA_module_t, DMA_stream_t, DMA_channel_t);
void DMA_selectDataSize(DMA_module_t, DMA_stream_t, DMA_dataSize_t);
void DMA_selectDataDirection(DMA_module_t, DMA_stream_t, DMA_dataDirection_t);

void DMA_selectMemoryIncrementMode(DMA_module_t, DMA_stream_t, DMA_incrementMode_t);
void DMA_selectPeripheralIncrementMode(DMA_module_t, DMA_stream_t, DMA_incrementMode_t);

void DMA_enable(DMA_module_t, DMA_stream_t);

void DMA_setCallback(DMA_module_t, DMA_stream_t, void (*)(void));

void DMA_setItemCount(DMA_module_t, DMA_stream_t, uint16_t);

void DMA_setPeripheralAddress(DMA_module_t, DMA_stream_t, void *);
void DMA_setMemoryAddress(DMA_module_t, DMA_stream_t, void *);


#endif /* __DMA_H__ */