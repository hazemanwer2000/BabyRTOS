/*************************************************************
 * 
 * Filename: BUTTON_Priv.h
 * Description: Private header file of the BUTTON driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __BUTTON_PRIV_H__
#define __BUTTON_PRIV_H__


/*************************************************************
 * Description: Number of counts before debounce is considered handled.
 * 
 *************************************************************/
#define BUTTON_debounceCountMaximum         5


/*************************************************************
 * Description: Get Button state.
 * Parameters:
 *      [1] Button name (configuration files).
 * Return:
 *      Button state.
 *************************************************************/
static BUTTON_state_t BUTTON_getQuick(BUTTON_name_t name);


#endif /* __BUTTON_PRIV_H__ */