/*************************************************************
 * 
 * Filename: NVIC.h
 * Description: Header (interface) file of the NVIC driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __NVIC_H__
#define __NVIC_H__

#include "NVIC_Types.h"
#include "NVIC_Map.h"
#include "NVIC_Priv.h"
#include "Std_Types.h"


/*************************************************************
 * Description: Priority grouping options (Group priorities, Sub priorities).
 *
 *************************************************************/
#define NVIC_priorityGrouping_16G			(0x05FA0000 | (0 << PRIGROUP0))
#define NVIC_priorityGrouping_8G_2S			(0x05FA0000 | (4 << PRIGROUP0))
#define NVIC_priorityGrouping_4G_4S			(0x05FA0000 | (5 << PRIGROUP0))
#define NVIC_priorityGrouping_2G_8S			(0x05FA0000 | (6 << PRIGROUP0))
#define NVIC_priorityGrouping_16S			(0x05FA0000 | (7 << PRIGROUP0))


/*************************************************************
 * Description: Interrupt number options.
 *
 *************************************************************/
#define NVIC_interruptNumber_WWDG                                               0
#define NVIC_interruptNumber_EXTI16_PVD                                         1
#define NVIC_interruptNumber_EXTI21_TAMP_STAMP                                  2
#define NVIC_interruptNumber_EXTI22_RTC_WKUP                                    3
#define NVIC_interruptNumber_FLASH                                              4
#define NVIC_interruptNumber_RCC                                                5
#define NVIC_interruptNumber_EXTI0                                              6
#define NVIC_interruptNumber_EXTI1                                              7
#define NVIC_interruptNumber_EXTI2                                              8
#define NVIC_interruptNumber_EXTI3                                              9
#define NVIC_interruptNumber_EXTI4                                              10
#define NVIC_interruptNumber_DMA1_Stream0                                       11
#define NVIC_interruptNumber_DMA1_Stream1                                       12
#define NVIC_interruptNumber_DMA1_Stream2                                       13
#define NVIC_interruptNumber_DMA1_Stream3                                       14
#define NVIC_interruptNumber_DMA1_Stream4                                       15
#define NVIC_interruptNumber_DMA1_Stream5                                       16
#define NVIC_interruptNumber_DMA1_Stream6                                       17
#define NVIC_interruptNumber_ADC                                                18
#define NVIC_interruptNumber_EXTI9_5                                            23
#define NVIC_interruptNumber_TIM1_BRK_TIM9                                      24
#define NVIC_interruptNumber_TIM1_UP_TIM10                                      25
#define NVIC_interruptNumber_TIM1_TRG_COM_TIM11                                 26
#define NVIC_interruptNumber_TIM1_CC                                            27
#define NVIC_interruptNumber_TIM2                                               28
#define NVIC_interruptNumber_TIM3                                               29
#define NVIC_interruptNumber_TIM4                                               30
#define NVIC_interruptNumber_I2C1_EV                                            31
#define NVIC_interruptNumber_I2C1_ER                                            32
#define NVIC_interruptNumber_I2C2_EV                                            33
#define NVIC_interruptNumber_I2C2_ER                                            34
#define NVIC_interruptNumber_SPI1                                               35
#define NVIC_interruptNumber_SPI2                                               36
#define NVIC_interruptNumber_USART1                                             37
#define NVIC_interruptNumber_USART2                                             38
#define NVIC_interruptNumber_EXTI15_10                                          40
#define NVIC_interruptNumber_EXTI17_RTC_Alarm                                   41
#define NVIC_interruptNumber_EXTI18_OTG_FS_WKUP                                 42
#define NVIC_interruptNumber_DMA1_Stream7                                       47
#define NVIC_interruptNumber_SDIO                                               49
#define NVIC_interruptNumber_TIM5                                               50
#define NVIC_interruptNumber_SPI3                                               51
#define NVIC_interruptNumber_DMA2_Stream0                                       56
#define NVIC_interruptNumber_DMA2_Stream1                                       57
#define NVIC_interruptNumber_DMA2_Stream2                                       58
#define NVIC_interruptNumber_DMA2_Stream3                                       59
#define NVIC_interruptNumber_DMA2_Stream4                                       60
#define NVIC_interruptNumber_OTG_FS                                             67
#define NVIC_interruptNumber_DMA2_Stream5                                       68
#define NVIC_interruptNumber_DMA2_Stream6                                       69
#define NVIC_interruptNumber_DMA2_Stream7                                       70
#define NVIC_interruptNumber_USART6                                             71
#define NVIC_interruptNumber_I2C3_EV                                            72
#define NVIC_interruptNumber_I2C3_ER                                            73
#define NVIC_interruptNumber_FPU                                                81
#define NVIC_interruptNumber_SPI4                                               84


/*************************************************************
 * Description: Priority options.
 *
 *************************************************************/
#define NVIC_priority_0										(0 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_1										(1 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_2										(2 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_3										(3 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_4										(4 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_5										(5 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_6										(6 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_7										(7 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_8										(8 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_9										(9 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_10									(10 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_11									(11 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_12									(12 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_13									(13 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_14									(14 << NVIC_PRIORITY_SHIFT)
#define NVIC_priority_15									(15 << NVIC_PRIORITY_SHIFT)


/*************************************************************
 * Description: Pending status.
 *
 *************************************************************/
#define NVIC_pendingStatus_Off								0
#define NVIC_pendingStatus_On								1


/*************************************************************
 * Description: Active status.
 *
 *************************************************************/
#define NVIC_activeStatus_Off								0
#define NVIC_activeStatus_On								1


/*************************************************************
 * Description: Set priority grouping.
 * Parameters:
 *      [1] Priority grouping option.
 * Return:
 * 		None.
 *************************************************************/
void NVIC_setPriorityGrouping(NVIC_priorityGrouping_t priorityGrouping);


/*************************************************************
 * Description: Enable interrupt.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		None.
 *************************************************************/
void NVIC_enableInterrupt(NVIC_interruptNumber_t interruptNumber);


/*************************************************************
 * Description: Disable interrupt.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		None.
 *************************************************************/
void NVIC_disableInterrupt(NVIC_interruptNumber_t interruptNumber);


/*************************************************************
 * Description: Get pending status.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		Pending status.
 *************************************************************/
NVIC_pendingStatus_t NVIC_getPendingStatus(NVIC_interruptNumber_t interruptNumber);


/*************************************************************
 * Description: Set pending status.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		None.
 *************************************************************/
void NVIC_setPendingStatus(NVIC_interruptNumber_t interruptNumber);


/*************************************************************
 * Description: Clear pending status.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		None.
 *************************************************************/
void NVIC_clearPendingStatus(NVIC_interruptNumber_t interruptNumber);


/*************************************************************
 * Description: Get active status.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		Active status.
 *************************************************************/
NVIC_activeStatus_t NVIC_getActiveStatus(NVIC_interruptNumber_t interruptNumber);


/*************************************************************
 * Description: Get priority.
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		Priority.
 *************************************************************/
NVIC_priority_t NVIC_getPriority(NVIC_interruptNumber_t interruptNumber);


/*************************************************************
 * Description: Set priority.
 * Parameters:
 *      [1] Interrupt number.
 *      [2] Priority.
 * Return:
 *		None.
 *************************************************************/
void NVIC_setPriority(NVIC_interruptNumber_t interruptNumber, NVIC_priority_t priority);


/*************************************************************
 * Description: Trigger interrupt (Software Interrupt).
 * Parameters:
 *      [1] Interrupt number.
 * Return:
 * 		None.
 *************************************************************/
void NVIC_triggerInterrupt(NVIC_interruptNumber_t interruptNumber);


#endif /* __NVIC_H__ */
