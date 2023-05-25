/*************************************************************
 *
 * Filename: Utils.c
 * Description: Macros and function prototypes, performing various convenience operations.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 *
 *************************************************************/

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


/*************************************************************
 * Description: Swap void args.
 *
 *************************************************************/
void swap(void **args1, void **args2) {
    void *tmp = *args1;
    *args1 = *args2;
    *args2 = tmp;
}