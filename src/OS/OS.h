
/*************************************************************
 * 
 * Filename: OS_kernel.h
 * Description: Header file of the OS Kernel.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __OS_KERNEL_H__
#define __OS_KERNEL_H__

#include "Std_Types.h"


/*************************************************************
 * Description: Structure of an OS task.
 * 
 *************************************************************/
typedef struct {
        /* Must be first, for easy stack pointer switching. */
    uint32_t *stackPtr;

    void (*fptr)(void *);
    void *args;
} OS_task;


/*************************************************************
 * Description: Initialize the OS.
 * Parameters:
 *      [X]
 * Return:
 *      Error Status.
 *************************************************************/
void OS_init(void);


/*************************************************************
 * Description: Kick-start the OS.
 * Parameters:
 *      [X]
 * Return:
 *      Error Status.
 *************************************************************/
void OS_start(void);


#endif /* __OS_KERNEL_H__ */