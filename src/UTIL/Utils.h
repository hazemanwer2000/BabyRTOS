/*************************************************************
 *
 * Filename: Utils.h
 * Description: Macros and function prototypes, performing various convenience operations.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 *
 *************************************************************/

#ifndef __UTILS_H__
#define __UTILS_H__

#include "Std_Types.h"


/*************************************************************
 * Description: If-else for expressions.
 *
 *************************************************************/
#define IF_ELSE(COND, X, Y)			((COND) ? (X) : (Y))


/*************************************************************
 * Description: Get string length.
 *
 *************************************************************/
uint16_t strlen(const char * const ptr);


#endif /* __UTILS_H__ */
