/*************************************************************
 * 
 * Filename: DMA_Types.h
 * Description: Types header file of the DMA driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __DMA_TYPES_H__
#define __DMA_TYPES_H__

#include "DMA_Map.h"
#include "Std_Types.h"


/*************************************************************
 * Description: DMA module.
 * 
 *************************************************************/
typedef enum {
    DMA_module_1 = 0,
    DMA_module_2,

    DMA_module_Count
} DMA_module_t;


/*************************************************************
 * Description: DMA stream.
 * 
 *************************************************************/
typedef enum {
    DMA_stream_0 = 0,
    DMA_stream_1,
    DMA_stream_2,
    DMA_stream_3,
    DMA_stream_4,
    DMA_stream_5,
    DMA_stream_6,
    DMA_stream_7,

    DMA_stream_Count
} DMA_stream_t;


/*************************************************************
 * Description: DMA interrupt.
 * 
 *************************************************************/
typedef uint8_t DMA_interrupt_t;


/*************************************************************
 * Description: DMA channel.
 * 
 *************************************************************/
typedef uint8_t DMA_channel_t;


/*************************************************************
 * Description: DMA data size.
 * 
 *************************************************************/
typedef uint8_t DMA_dataSize_t;


/*************************************************************
 * Description: DMA data direction.
 * 
 *************************************************************/
typedef uint8_t DMA_dataDirection_t;


/*************************************************************
 * Description: DMA increment mode.
 * 
 *************************************************************/
typedef uint8_t DMA_incrementMode_t;


#endif /* __DMA_TYPES_H__ */