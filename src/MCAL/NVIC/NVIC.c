/*************************************************************
 * 
 * Filename: NVIC.c
 * Description: Source file of the NVIC driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "NVIC_Priv.h"
#include "NVIC_Types.h"
#include "NVIC.h"
#include "NVIC_Map.h"
#include "Std_Types.h"


/*************************************************************
 * Description: Set priority grouping.
 * Parameters:
 *      [1] Priority grouping option.
 * Return:
 * 		None.
 *************************************************************/
void NVIC_setPriorityGrouping(NVIC_priorityGrouping_t priorityGrouping) {
	AIRCR = (AIRCR & ~(MSK_I2J(PRIGROUP0, PRIGROUP2) | 0xFFFF0000)) | priorityGrouping;
}


/*************************************************************
 * Description: Enable interrupt.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		None.
 *************************************************************/
void NVIC_enableInterrupt(NVIC_interruptNumber_t interruptNumber) {
	*(&NVIC_ISER + (interruptNumber >> 5)) |= (1 << (interruptNumber % 32));
}


/*************************************************************
 * Description: Disable interrupt.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		None.
 *************************************************************/
void NVIC_disableInterrupt(NVIC_interruptNumber_t interruptNumber) {
	*(&NVIC_ICER + (interruptNumber >> 5)) |= (1 << (interruptNumber % 32));
}


/*************************************************************
 * Description: Get pending status.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		Pending status.
 *************************************************************/
NVIC_pendingStatus_t NVIC_getPendingStatus(NVIC_interruptNumber_t interruptNumber) {
	return (*(&NVIC_ISPR + (interruptNumber >> 5)) & (1 << (interruptNumber % 32))) != 0;
}


/*************************************************************
 * Description: Set pending status.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		None.
 *************************************************************/
void NVIC_setPendingStatus(NVIC_interruptNumber_t interruptNumber) {
	*(&NVIC_ISPR + (interruptNumber >> 5)) |= (1 << (interruptNumber % 32));
}


/*************************************************************
 * Description: Clear pending status.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		None.
 *************************************************************/
void NVIC_clearPendingStatus(NVIC_interruptNumber_t interruptNumber) {
	*(&NVIC_ICPR + (interruptNumber >> 5)) |= (1 << (interruptNumber % 32));
}


/*************************************************************
 * Description: Get active status.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		Active status.
 *************************************************************/
NVIC_activeStatus_t NVIC_getActiveStatus(NVIC_interruptNumber_t interruptNumber) {
	return (*(&NVIC_IABR + (interruptNumber >> 5)) & (1 << (interruptNumber % 32))) != 0;
}


/*************************************************************
 * Description: Get priority.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		Priority.
 *************************************************************/
NVIC_priority_t NVIC_getPriority(NVIC_interruptNumber_t interruptNumber) {
	volatile uint32_t *reg = &NVIC_IPR + (interruptNumber / 4);
	uint8_t startBit = 8 * (interruptNumber % 4);

	return EXTRACT_FIELD(*reg, startBit, startBit + 7);
}


/*************************************************************
 * Description: Set priority.
 * Parameters:
 *      [1] Interrupt number.
 *      [2] Priority.
 * Return:
 *		None.
 *************************************************************/
void NVIC_setPriority(NVIC_interruptNumber_t interruptNumber, NVIC_priority_t priority) {
	volatile uint32_t *reg = &NVIC_IPR + (interruptNumber / 4);
	uint8_t startBit = 8 * (interruptNumber % 4);

	*reg = (*reg & ~(NVIC_PRIORITY_MASK << startBit)) | (priority << startBit);
}


/*************************************************************
 * Description: Trigger interrupt (Software Interrupt).
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		None.
 *************************************************************/
void NVIC_triggerInterrupt(NVIC_interruptNumber_t interruptNumber) {
	NVIC_STIR = interruptNumber;
}
