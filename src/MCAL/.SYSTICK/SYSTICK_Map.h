/*************************************************************
 * 
 * Filename: SYSTICK_Map.h
 * Description: Map file of the SYSTICK driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __SYSTICK_MAP_H__
#define __SYSTICK_MAP_H__

#include "Std_Types.h"


/*************************************************************
 * Description: Register map of the SYSTICK timer.
 *
 *************************************************************/
#define SYSTICK_CTRL					(* (volatile uint32_t *) 0xE000E010)
#define SYSTICK_LOAD					(* (volatile uint32_t *) 0xE000E014)
#define SYSTICK_VAL						(* (volatile uint32_t *) 0xE000E018)
#define SYSTICK_CALIB					(* (volatile uint32_t *) 0xE000E01C)


/*************************************************************
 * Description: Bit numbers in SYSTICK_CTRL.
 *
 *************************************************************/
#define BIT_COUNTFLAG					16
#define BIT_CLKSOURCE					2
#define BIT_TICKINT						1
#define BIT_ENABLE						0


/*************************************************************
 * Description: Bit numbers in SYSTICK_LOAD.
 *
 *************************************************************/
#define BIT_RELOAD0						0
#define BIT_RELOADN						23


/*************************************************************
 * Description: Bit numbers in SYSTICK_VAL.
 *
 *************************************************************/
#define BIT_CURRENT0					0
#define BIT_CURRENTN					23


#endif /* __SYSTICK_MAP_H__ */
