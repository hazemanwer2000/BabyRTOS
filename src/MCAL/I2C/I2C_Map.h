/*************************************************************
 * 
 * Filename: I2C_Map.h
 * Description: Map file of the I2C driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __I2C_MAP_H__
#define __I2C_MAP_H__

#include "Std_Types.h"


/*************************************************************
 * Description: 'CR1' register bit numbers.
 * 
 *************************************************************/
#define I2C_BIT_SWRST                       15
#define I2C_BIT_STOP                        9
#define I2C_BIT_START                       8
#define I2C_BIT_PE                          0


/*************************************************************
 * Description: 'CR2' register bit numbers.
 * 
 *************************************************************/
#define I2C_BIT_DMAEN                       11


/*************************************************************
 * Description: 'SR1' register bit numbers.
 * 
 *************************************************************/
#define I2C_BIT_TXE                         7
#define I2C_BIT_BTF                         2
#define I2C_BIT_ADDR                        1
#define I2C_BIT_SB                          0


/*************************************************************
 * Description: 'CCR' register bit numbers.
 * 
 *************************************************************/
#define I2C_BIT_FS                          15


#endif /* __I2C_MAP_H__ */