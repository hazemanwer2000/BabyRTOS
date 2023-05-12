/*************************************************************
 * 
 * Filename: SYSTICK_Cfg.h
 * Description: Configuration header file of the SYSTICK driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __SYSTICK_CFG_H__
#define __SYSTICK_CFG_H__


/*************************************************************
 * Description: Clock to SysTick timer in MHz, as a whole number and a division factor.
 * 					For example, 12.5 MHz becomes (12.5, 25, 2).
 *              Note: Must match actual clock configuration. These values
 *                      are merely used for error checking.
 *
 *************************************************************/
#define SYSTICK_CLK_MHz							25
#define SYSTICK_CLK_MHz_WHOLE					25
#define SYSTICK_CLK_MHz_DIV_FACTOR				1


#endif /* __SYSTICK_CFG_H__ */
