/*************************************************************
 * 
 * Filename: DMA.c
 * Description: Source file of the DMA driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "DMA_Priv.h"
#include "DMA_Types.h"
#include "DMA.h"
#include "DMA_Map.h"

#include "NVIC.h"

#include "Bit_Utils.h"


/*************************************************************
 * Description: Variables.
 * 
 *************************************************************/
static volatile DMA_t *DMA_registers[DMA_module_Count] = {
    [DMA_module_1] = ((volatile DMA_t *) 0x40026000),
    [DMA_module_2] = ((volatile DMA_t *) 0x40026400)
};

static void (*DMA_callbacks[DMA_module_Count][DMA_stream_Count])(void);


/*************************************************************
 * Description: Handler(s) Implementation.
 * 
 *************************************************************/
void __attribute__ ((section(".after_vectors")))
DMA2_Stream2_IRQHandler(void) {
    const DMA_module_t module = DMA_module_2;
    const DMA_stream_t stream = DMA_stream_2;

    DMA_clearInterruptFlags(module, stream);
    if (DMA_callbacks[module][stream] != NULL) {
        DMA_callbacks[module][stream]();
    }
}

void __attribute__ ((section(".after_vectors")))
DMA2_Stream7_IRQHandler(void) {
    const DMA_module_t module = DMA_module_2;
    const DMA_stream_t stream = DMA_stream_7;

    DMA_clearInterruptFlags(module, stream);
    if (DMA_callbacks[module][stream] != NULL) {
        DMA_callbacks[module][stream]();
    }
}


/*************************************************************
 * Description: API(s) Implementation.
 * 
 *************************************************************/
void DMA_enableInterrupt(DMA_module_t module, DMA_stream_t stream, DMA_interrupt_t interrupt) {
    DMA_registers[module]->DMA_S[stream].DMA_CR |= interrupt << 1;
}

void DMA_clearInterruptFlags(DMA_module_t module, DMA_stream_t stream) {
    DMA_stream_t isHighReg = stream / 4;
    DMA_stream_t range4 = stream % 4;
    DMA_stream_t isHighTwoBytes = range4 / 2;
    DMA_stream_t isHighByte = range4 % 2;

    *(&DMA_registers[module]->DMA_LIFCR + isHighReg) = (0b111101 << (6*isHighByte + 16*isHighTwoBytes));
}

void DMA_selectChannel(DMA_module_t module, DMA_stream_t stream, DMA_channel_t channel) {
    volatile uint32_t *reg = &DMA_registers[module]->DMA_S[stream].DMA_CR;
    *reg = REPLACE_FIELD(*reg, DMA_CHSEL0, DMA_CHSELN, channel);
}

void DMA_selectDataSize(DMA_module_t module, DMA_stream_t stream, DMA_dataSize_t dataSize) {
    volatile uint32_t *reg = &DMA_registers[module]->DMA_S[stream].DMA_CR;
    *reg = REPLACE_FIELD(*reg, DMA_PSIZE0, DMA_PSIZEN, dataSize);
}

void DMA_selectDataDirection(DMA_module_t module, DMA_stream_t stream, DMA_dataDirection_t dataDirection) {
    volatile uint32_t *reg = &DMA_registers[module]->DMA_S[stream].DMA_CR;
    *reg = REPLACE_FIELD(*reg, DMA_DIR0, DMA_DIRN, dataDirection);
}

void DMA_selectMemoryIncrementMode(DMA_module_t module, DMA_stream_t stream, DMA_incrementMode_t incrementMode) {
    volatile uint32_t *reg = &DMA_registers[module]->DMA_S[stream].DMA_CR;
    *reg = REPLACE_BIT(*reg, DMA_MINC, incrementMode);
}

void DMA_selectPeripheralIncrementMode(DMA_module_t module, DMA_stream_t stream, DMA_incrementMode_t incrementMode) {
    volatile uint32_t *reg = &DMA_registers[module]->DMA_S[stream].DMA_CR;
    *reg = REPLACE_BIT(*reg, DMA_PINC, incrementMode);
}

void DMA_enable(DMA_module_t module, DMA_stream_t stream) {
    DMA_registers[module]->DMA_S[stream].DMA_CR |= 1 << DMA_EN;
}

void DMA_setCallback(DMA_module_t module, DMA_stream_t stream, void (*cb)(void)) {
    DMA_callbacks[module][stream] = cb;
}

void DMA_setItemCount(DMA_module_t module, DMA_stream_t stream, uint16_t byteCount) {
    DMA_registers[module]->DMA_S[stream].DMA_NDTR = byteCount;
}

void DMA_setPeripheralAddress(DMA_module_t module, DMA_stream_t stream, void *ptr) {
    DMA_registers[module]->DMA_S[stream].DMA_PAR = (uint32_t) ptr;
}

void DMA_setMemoryAddress(DMA_module_t module, DMA_stream_t stream, void *ptr) {
    DMA_registers[module]->DMA_S[stream].DMA_M0AR = (uint32_t) ptr;
}