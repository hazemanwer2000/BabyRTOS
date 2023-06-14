/*************************************************************
 * 
 * Filename: DMA_Map.h
 * Description: Map file of the DMA driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __DMA_MAP_H__
#define __DMA_MAP_H__

#include "Std_Types.h"


/*************************************************************
 * Description: Number of streams in a DMA module.
 *
 *************************************************************/
#define DMA_streamCount                     8


/*************************************************************
 * Description: Register layout of the module.
 *
 *************************************************************/
typedef struct {
	uint32_t DMA_CR;
	uint32_t DMA_NDTR;
	uint32_t DMA_PAR;
	uint32_t DMA_M0AR;
	uint32_t DMA_M1AR;
	uint32_t DMA_FCR;
} __attribute__((packed, aligned(4))) DMA_S_t;

typedef struct {
	uint32_t DMA_LISR;
	uint32_t DMA_HISR;
	uint32_t DMA_LIFCR;
	uint32_t DMA_HIFCR;
    DMA_S_t DMA_S[DMA_streamCount];
} __attribute__((packed, aligned(4))) DMA_t;


/*************************************************************
 * Description: Bits numbers.
 *
 *************************************************************/
#define DMA_CHSEL0              25
#define DMA_CHSELN              27

#define DMA_PSIZE0              11
#define DMA_PSIZEN              12

#define DMA_MINC                10
#define DMA_PINC                9

#define DMA_DIR0                6
#define DMA_DIRN                7

#define DMA_EN                  0


#endif /* __DMA_MAP_H__ */