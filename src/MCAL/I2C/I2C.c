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


/*************************************************************
 * Description: Write buffer.
 * 
 *************************************************************/
static void I2C_writeBuffer_sync(volatile I2C_t *instance,
            uint8_t *buffer, uint32_t bufferSize)
{
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

        /* I2C-DMA enable. */
    instance->CR2 |= (1 << I2C_BIT_DMAEN);

        /* Setup DMA module and stream. */
}


/*************************************************************
 * Description: Master-Write (Synchronous).
 * 
 *************************************************************/
void I2C_masterWrite_sync(I2C_module_t mod, uint8_t deviceAddress,
            uint8_t *dataAddress, uint32_t dataAddressSize,
            uint8_t *dataBuffer, uint32_t dataBufferSize)
{
    volatile uint32_t tmp;
    volatile I2C_t *instance = I2C_numberToModule[mod];

        /* Start CONDITION. */
    instance->CR1 |= (1 << I2C_BIT_START);
    while (GET_BIT(instance->SR1, I2C_BIT_SB) == 0);

        /* Write DEVICE ADDRESS. */
    instance->DR = deviceAddress << 1;
    while (GET_BIT(instance->SR1, I2C_BIT_ADDR) == 0);
    tmp = instance->SR1 | instance->SR2;

        /* Write DATA ADDRESS. */
    I2C_writeBuffer_sync(instance, dataAddress, dataAddressSize);

        /* Write DATA BUFFER. */
    I2C_writeBuffer_sync(instance, dataBuffer, dataBufferSize);

        /* Stop CONDITION. */
    instance->CR1 |= (1 << I2C_BIT_STOP);
}


/*************************************************************
 * Description: Master-Write (DMA).
 * 
 *************************************************************/
void I2C_masterWrite_DMA(I2C_module_t mod, uint8_t deviceAddress,
        uint8_t *dataAddress, uint32_t dataAddressSize,
        uint8_t *dataBuffer, uint32_t dataBufferSize)
{
    volatile uint32_t tmp;
    volatile I2C_t *instance = I2C_numberToModule[mod];

        /* Start CONDITION. */
    instance->CR1 |= (1 << I2C_BIT_START);
    while (GET_BIT(instance->SR1, I2C_BIT_SB) == 0);

        /* Write DEVICE ADDRESS. */
    instance->DR = deviceAddress << 1;
    while (GET_BIT(instance->SR1, I2C_BIT_ADDR) == 0);
    tmp = instance->SR1 | instance->SR2;

        /* Write DATA ADDRESS. */
    I2C_writeBuffer_sync(instance, dataAddress, dataAddressSize);

        /* Write DATA BUFFER. */
    I2C_writeBuffer_sync(instance, dataBuffer, dataBufferSize);

        /* Stop CONDITION. */
    instance->CR1 |= (1 << I2C_BIT_STOP);
}
