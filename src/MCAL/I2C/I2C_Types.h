/*************************************************************
 * 
 * Filename: I2C_Types.h
 * Description: Types header file of the I2C driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __I2C_TYPES_H__
#define __I2C_TYPES_H__

#include "Std_Types.h"


/*************************************************************
 * Description: I2C register file type.
 * 
 *************************************************************/
typedef struct {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t OAR1;
    uint32_t OAR2;

    uint32_t DR;
    uint32_t SR1;
    uint32_t SR2;
    uint32_t CCR;
    
    uint32_t TRISE;
    uint32_t FLTR;
} I2C_t;


/*************************************************************
 * Description: I2C status type.
 * 
 *************************************************************/
typedef enum {
    I2C_status_OK = 0,
    I2C_status_NACK
} I2C_status_t;


/*************************************************************
 * Description: I2C module type.
 * 
 *************************************************************/
typedef enum {
    I2C1 = 0
} I2C_module_t;


#endif /* __I2C_TYPES_H__ */