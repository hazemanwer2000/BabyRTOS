/*************************************************************
 * 
 * Filename: I2C.c
 * Description: Source file of the I2C driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "I2C_Map.h"
#include "I2C_Types.h"
#include "I2C.h"
#include "Bit_Utils.h"
#include "DMA.h"


/*************************************************************
 * Description: Map number to module.
 * 
 *************************************************************/
volatile I2C_t *I2C_numberToModule[] = {
    [I2C1] = ((volatile I2C_t *) 0x40005400)
};

DMA_module_t I2C_numberToDMAModuleTX[] = {
    [I2C1] = DMA_module_I2C1_TX
};

DMA_stream_t I2C_numberToDMAStreamTX[] = {
    [I2C1] = DMA_stream_I2C1_TX
};

DMA_channel_t I2C_numberToDMAChannelTX[] = {
    [I2C1] = DMA_channel_I2C1_TX
};

void (*I2C_callbackTX[])(void) = {
    [I2C1] = NULL
};


/*************************************************************
 * Description: Start CONDITION.
 * 
 *************************************************************/
static void I2C_start(I2C_module_t mod)
{
    volatile I2C_t *instance = I2C_numberToModule[mod];

        /* Start CONDITION. */
    instance->CR1 |= (1 << I2C_BIT_START);
    while (GET_BIT(instance->SR1, I2C_BIT_SB) == 0);
}

volatile uint32_t tmp;

/*************************************************************
 * Description: Write device's address.
 * 
 *************************************************************/
static void I2C_writeAddress(I2C_module_t mod, uint8_t deviceAddress)
{
    volatile I2C_t *instance = I2C_numberToModule[mod];

        /* Write DEVICE ADDRESS. */
    instance->DR = deviceAddress << 1;
    while (GET_BIT(instance->SR1, I2C_BIT_ADDR) == 0);
    tmp = instance->SR1 | instance->SR2;
}


/*************************************************************
 * Description: Write buffer.
 * 
 *************************************************************/
static void I2C_writeBuffer_sync(I2C_module_t mod,
            uint8_t *buffer, uint32_t bufferSize)
{
    volatile I2C_t *instance = I2C_numberToModule[mod];
    uint32_t i = 0;

    for (i = 0; i < bufferSize; i++) 
    {
        while (GET_BIT(instance->SR1, I2C_BIT_TXE) == 0);
        instance->DR = buffer[i];
        while (GET_BIT(instance->SR1, I2C_BIT_BTF) == 0);
    }
}


/*************************************************************
 * Description: Initialize module.
 * 
 *************************************************************/
void I2C_init(I2C_module_t mod)
{
    volatile I2C_t *instance = I2C_numberToModule[mod];

        /* Fast mode. */
    instance->CCR |= (1 << I2C_BIT_FS);

        /* Initialize clock. */
    instance->CR2 |= (25 << 0);
    instance->CCR |= (23 << 0);
    instance->TRISE |= (8 << 0);

        /* Enable module. */
    instance->CR1 |= (1 << I2C_BIT_PE);
}


/*************************************************************
 * Description: Initialize DMA mode.
 * 
 *************************************************************/
void I2C_initDMAMode(I2C_module_t mod)
{
    volatile I2C_t *instance = I2C_numberToModule[mod];
    DMA_module_t moduleDMA_TX = I2C_numberToDMAModuleTX[mod];
    DMA_stream_t streamDMA_TX = I2C_numberToDMAStreamTX[mod];
    DMA_channel_t channelDMA_TX = I2C_numberToDMAChannelTX[mod];

        /* I2C-DMA enable. */
    instance->CR2 |= (1 << I2C_BIT_DMAEN);

        /* Setup DMA module (TX). */
    DMA_enableInterrupt(moduleDMA_TX, streamDMA_TX, DMA_interrupt_TransferComplete);
    DMA_selectChannel(moduleDMA_TX, streamDMA_TX, channelDMA_TX);
    DMA_selectDataDirection(moduleDMA_TX, streamDMA_TX, DMA_dataDirection_MemoryToPeripheral);
    DMA_selectDataSize(moduleDMA_TX, streamDMA_TX, DMA_dataSize_Byte);
    DMA_selectMemoryIncrementMode(moduleDMA_TX, streamDMA_TX, DMA_incrementMode_PerTransfer);
    DMA_selectPeripheralIncrementMode(moduleDMA_TX, streamDMA_TX, DMA_incrementMode_Fixed);
    DMA_setPeripheralAddress(moduleDMA_TX, streamDMA_TX, (void *) &instance->DR);
}


/*************************************************************
 * Description: Set callback (TX).
 * 
 *************************************************************/
void I2C_setCallbackTX(I2C_module_t mod, void (*fptr)(void))
{
    I2C_callbackTX[mod] = fptr;
}


/*************************************************************
 * Description: Master-Write (Synchronous).
 * 
 *************************************************************/
void I2C_masterWrite_sync(I2C_module_t mod, uint8_t deviceAddress,      
            uint8_t *memAdd, uint32_t memAddSize,
            uint8_t *buffer, uint32_t bufferSize)
{
    I2C_start(mod);
    I2C_writeAddress(mod, deviceAddress);
    I2C_writeBuffer_sync(mod, memAdd, memAddSize);
    I2C_writeBuffer_sync(mod, buffer, bufferSize);
    I2C_stop(mod);
}


/*************************************************************
 * Description: Master-Write (DMA).
 * 
 *************************************************************/
void I2C_masterWrite_DMA(I2C_module_t mod, uint8_t deviceAddress,
        uint8_t *buffer, uint32_t bufferSize)
{
    DMA_module_t moduleDMA_TX = I2C_numberToDMAModuleTX[mod];
    DMA_stream_t streamDMA_TX = I2C_numberToDMAStreamTX[mod];

    I2C_start(mod);
    I2C_writeAddress(mod, deviceAddress);

    DMA_setCallback(moduleDMA_TX, streamDMA_TX, I2C_callbackTX[mod]);
    DMA_setMemoryAddress(moduleDMA_TX, streamDMA_TX, buffer);
    DMA_setItemCount(moduleDMA_TX, streamDMA_TX, bufferSize);
    DMA_enable(moduleDMA_TX, streamDMA_TX);
}


/*************************************************************
 * Description: Stop CONDITION.
 * 
 *************************************************************/
void I2C_stop(I2C_module_t mod)
{
    I2C_numberToModule[mod]->CR1 |= (1 << I2C_BIT_STOP);
}