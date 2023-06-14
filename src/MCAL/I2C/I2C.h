/*************************************************************
 * 
 * Filename: I2C.h
 * Description: Header (interface) file of the I2C driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __I2C_H__
#define __I2C_H__

#include "I2C_Types.h"


/*************************************************************
 * Description: Initialize module.
 * 
 *************************************************************/
void I2C_init(I2C_module_t mod);


/*************************************************************
 * Description: Initialize DMA mode.
 * 
 *************************************************************/
void I2C_initDMAMode(I2C_module_t mod);


/*************************************************************
 * Description: Master-Write (Synchronous).
 * 
 *************************************************************/
void I2C_masterWrite_sync(I2C_module_t mod, uint8_t deviceAddress,
        uint8_t *dataAddress, uint32_t dataAddressSize,
        uint8_t *dataBuffer, uint32_t dataBufferSize);


/*************************************************************
 * Description: Master-Write (DMA).
 * 
 *************************************************************/
void I2C_masterWrite_DMA(I2C_module_t mod, uint8_t deviceAddress,
        uint8_t *dataAddress, uint32_t dataAddressSize,
        uint8_t *dataBuffer, uint32_t dataBufferSize);


#endif /* __I2C_H__ */