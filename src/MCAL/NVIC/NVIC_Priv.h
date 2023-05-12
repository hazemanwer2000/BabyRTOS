/*************************************************************
 * 
 * Filename: NVIC_Priv.h
 * Description: Private header file of the NVIC driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __NVIC_PRIV_H__
#define __NVIC_PRIV_H__

#include "Bit_Utils.h"


/*************************************************************
 * Description: (Macros) Priority.
 *
 *************************************************************/
#define NVIC_PRIORITY_SHIFT						4
#define NVIC_PRIORITY_MASK						MSK_I2J(0, 7)

#endif /* __NVIC_PRIV_H__ */
