/*************************************************************
 *
 * Filename: Utils.c
 * Description: Macros and function prototypes, performing various convenience operations.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 *
 *************************************************************/

#include "Std_Types.h"
#include "Utils.h"


/*************************************************************
 * Description: Get string length.
 *
 *************************************************************/
uint16_t strlen(const char * const ptr) {
    uint16_t i = 0;

    while (ptr[i] != '\0') {
        i++;
    }

    return i;
}