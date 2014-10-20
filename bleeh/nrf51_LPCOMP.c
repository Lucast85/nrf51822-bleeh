/***************************************************************************************************
** -------------------------------------------------------------------------------------------------
** Filename: nrf51_LPCOMP.c																																																	
** -------------------------------------------------------------------------------------------------	
** Description: comparator driver for Nordic Semiconductor nRF51822 																
** -------------------------------------------------------------------------------------------------
** Author: Luca Buccolini																																						
** -------------------------------------------------------------------------------------------------
** Date:	Oct 18, 2014    																																		
** -------------------------------------------------------------------------------------------------
***************************************************************************************************/

#include "nrf51_LPCOMP.h"

#include <nrf51.h>
#include <nrf51_bitfields.h>
#include <pca10001.h>

/**
 * Initialize the comparator
 *
 * @param  none
 * @return none
 *
 * @brief  Configures and enables the LPCOMP
 *
 */
 
 void LPCOMP_init (void)
	{
	//Enable interrupt on LPCOMP UPWARD-CROSSING event
	NRF_LPCOMP->INTENSET = LPCOMP_INTENCLR_UP_Msk;
	//Enable the device-specific interrupt in the NVIC interrupt controller
	NVIC_EnableIRQ(LPCOMP_IRQn);

	//Configure LPCOMP - set reference input source to AIN pin 4 (P0.03)
	NRF_LPCOMP->PSEL |= (LPCOMP_PSEL_PSEL_AnalogInput4 << LPCOMP_PSEL_PSEL_Pos);
	//Configure LPCOMP - set input source to AVDD*4/8 (= 1.5 V)
	NRF_LPCOMP->REFSEL |= (LPCOMP_REFSEL_REFSEL_SupplyFourEighthsPrescaling << LPCOMP_REFSEL_REFSEL_Pos);

	//Enable and start the low power comparator
	NRF_LPCOMP->ENABLE = LPCOMP_ENABLE_ENABLE_Enabled;	
	NRF_LPCOMP->TASKS_START = 1;
	}
	 
/**
 * Interrupt handler for LPCOMP
 *
 * @param  none
 * @return none
 *
 * @brief  	ISR for LPCOMP: 
 * 					clear event's flag, 
 *					sample LPCOMP and write result to LED_0 
 *					toggle LED_1 to indicate triggering of event	
 */
//--------------------------------------------------------------------------------------------------
	
	 /* Interrupt handler for LPCOMP */
void LPCOMP_IRQHandler(void)
	{
	// Clear event
	NRF_LPCOMP->EVENTS_UP = 0;
	}
//--------------------------------------------------------------------------------------------------
