/*************************************************************
 * 
 * Filename: RCC.h
 * Description: Header (interface) file of the RCC driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __RCC_H__
#define __RCC_H__

#include "Std_Types.h"
#include "RCC_Map.h"


/*************************************************************
 * Description: System clock options.
 *
 *************************************************************/
#define	RCC_systemClock_HSI				0
#define	RCC_systemClock_HSE				1
#define	RCC_systemClock_PLL				2


/*************************************************************
 * Description: Clock state options.
 *
 *************************************************************/
#define	RCC_clockState_Off					0
#define	RCC_clockState_On					1


/*************************************************************
 * Description: Peripheral options.
 *
 *************************************************************/
#define RCC_peripheral_DMA2					(DMA2EN)
#define RCC_peripheral_DMA1					(DMA1EN)

#define RCC_peripheral_CRC					(CRCEN)

#define RCC_peripheral_GPIOH				(GPIOHEN)
#define RCC_peripheral_GPIOE				(GPIOEEN)
#define RCC_peripheral_GPIOD				(GPIODEN)
#define RCC_peripheral_GPIOC				(GPIOCEN)
#define RCC_peripheral_GPIOB				(GPIOBEN)
#define RCC_peripheral_GPIOA				(GPIOAEN)

#define RCC_peripheral_OTGFS				(OTGFSEN + 32)

#define RCC_peripheral_PWR					(PWREN + 32*4)

#define RCC_peripheral_I2C3					(I2C3EN + 32*4)
#define RCC_peripheral_I2C2					(I2C2EN + 32*4)
#define RCC_peripheral_I2C1					(I2C1EN + 32*4)

#define RCC_peripheral_USART2				(USART2EN + 32*4)

#define RCC_peripheral_SPI3					(SPI3EN + 32*4)
#define RCC_peripheral_SPI2					(SPI2EN + 32*4)

#define RCC_peripheral_WWDG					(WWDGEN + 32*4)

#define RCC_peripheral_TIM5					(TIM5EN + 32*4)
#define RCC_peripheral_TIM4					(TIM4EN + 32*4)
#define RCC_peripheral_TIM3					(TIM3EN + 32*4)
#define RCC_peripheral_TIM2					(TIM2EN + 32*4)

#define RCC_peripheral_TIM11				(TIM11EN + 32*5)
#define RCC_peripheral_TIM10				(TIM10EN + 32*5)
#define RCC_peripheral_TIM9					(TIM9EN + 32*5)

#define RCC_peripheral_SYSCFG				(SYSCFGEN + 32*5)

#define RCC_peripheral_SPI4					(SPI4EN + 32*5)
#define RCC_peripheral_SPI1					(SPI1EN + 32*5)

#define RCC_peripheral_SDIO					(SDIOEN + 32*5)

#define RCC_peripheral_ADC1					(ADC1EN + 32*5)

#define RCC_peripheral_USART6				(USART6EN + 32*5)
#define RCC_peripheral_USART1				(USART1EN + 32*5)

#define RCC_peripheral_TIM1					(TIM1EN + 32*5)


/*************************************************************
 * Description: PLL Prescale (P) options.
 *
 *************************************************************/
#define RCC_PLLPrescaleP_2					0
#define RCC_PLLPrescaleP_4					1
#define RCC_PLLPrescaleP_6					2
#define RCC_PLLPrescaleP_8					3


/*************************************************************
 * Description: PLL source clock options.
 *
 *************************************************************/
#define	RCC_PLLSourceClock_HSI				0
#define	RCC_PLLSourceClock_HSE				1


/*************************************************************
 * Description: PLL factor (N) minimum and maximum.
 *
 *************************************************************/
#define	RCC_PLLFactorN_Min					192
#define	RCC_PLLFactorN_Max					432


/*************************************************************
 * Description: PLL prescale (M) minimum and maximum.
 *
 *************************************************************/
#define	RCC_PLLPrescaleM_Min				2
#define	RCC_PLLPrescaleM_Max				63


/*************************************************************
 * Description: Bus (AHB, APB) prescale options.
 *
 *************************************************************/
#define	RCC_busPrescale_AHB_1				0
#define	RCC_busPrescale_AHB_2				8
#define	RCC_busPrescale_AHB_4				9
#define	RCC_busPrescale_AHB_8				10
#define	RCC_busPrescale_AHB_16				11
#define	RCC_busPrescale_AHB_64				12
#define	RCC_busPrescale_AHB_128				13
#define	RCC_busPrescale_AHB_256				14
#define	RCC_busPrescale_AHB_512				15

#define	RCC_busPrescale_APB_1				0
#define	RCC_busPrescale_APB_2				4
#define	RCC_busPrescale_APB_4				5
#define	RCC_busPrescale_APB_8				6
#define	RCC_busPrescale_APB_16				7


/*************************************************************
 * Description: Various type-definitions.
 *
 *************************************************************/
typedef uint8_t RCC_systemClock_t;
typedef uint8_t RCC_clockState_t;
typedef uint8_t RCC_peripheral_t;

typedef uint8_t RCC_PLLPrescaleP_t;
typedef uint8_t RCC_PLLSourceClock_t;

typedef uint8_t RCC_busPrescale_t;


/*************************************************************
 * Description: Status returned by some API calls (context-dependent).
 *
 *************************************************************/
typedef enum {
	RCC_status_Ok,
	RCC_status_Timeout,
	RCC_status_PLLLocked,
	RCC_status_InvalidConfiguration
} RCC_status_t;


/*************************************************************
 * Description: Bus type.
 *
 *************************************************************/
typedef enum {
	RCC_bus_AHB,
	RCC_bus_APB1,
	RCC_bus_APB2
} RCC_bus_t;


/*************************************************************
 * Description: Select system clock, and wait until it is used. (with timeout).
 * 					Note: System clock must be [ON] beforehand.
 * Parameters:
 *      [1] System clock option.
 * Return:
 *      Status:
 *      	[status_Ok] - System clock has been switched to.
 *      	[status_Timeout] - System clock has not been switched to.
 *************************************************************/
RCC_status_t RCC_selectSystemClock(RCC_systemClock_t systemClock);


/*************************************************************
 * Description: Set system clock state.
 * Parameters:
 *      [1] System clock option.
 *      [2] Clock state option.
 * Return:
 *      Status:
 *      	[status_Ok] - System clock state altered.
 *      	[status_Timeout] - Occurs when [clockState = ON], means failed
 *      						to get system clock ready within time.
 *************************************************************/
RCC_status_t RCC_setSystemClockState(RCC_systemClock_t systemClock, RCC_clockState_t clockState);


/*************************************************************
 * Description: Set peripheral clock state.
 * Parameters:
 *      [1] Peripheral option.
 *      [2] Clock state option.
 * Return:
 *      None.
 *************************************************************/
void RCC_setPeripheralClockState(RCC_peripheral_t peripheral, RCC_clockState_t clockState);


/*************************************************************
 * Description: Configure PLL, using the equation (Clock = (SourceClock * N) / (M * P)).
 * 					Note: PLL must be [OFF] beforehand.
 * Parameters:
 *      [1] PLL source clock option.
 *      [2] PLL factor (N), from [PLLFactorN_Min] to [PLLFactorN_Max].
 *      [3] PLL prescale (M), from [PLLPrescaleM_Min] to [PLLPrescaleM_Max].
 *      [4] PLL prescale (P) option.
 * Return:
 *      Status:
 *      	[status_Ok] - PLL configured.
 *      	[status_PLLLocked] - Failed to configure, PLL is on.
 *************************************************************/
RCC_status_t RCC_configurePLLClock(RCC_PLLSourceClock_t PLLSourceClock, uint16_t PLLFactorN, uint8_t PLLPrescaleM, RCC_PLLPrescaleP_t PLLPrescaleP);


/*************************************************************
 * Description: Configure bus clock.
 * Parameters:
 *      [1] Bus type option.
 *      [2] Bus-specific prescale option.
 * Return:
 *      None
 *************************************************************/
void RCC_configureBusClock(RCC_bus_t bus, RCC_busPrescale_t busPrescale);


#endif /* __RCC_H__ */
