/*******************************************************************************
 * @file    main.c
 * @author  Ahmed Eldeep
 * @email   ahmed@almohandes.org
 * @website http://almohandes.org/stm32
 * @date    21.03.2018
 *
 * @brief   main application called after startup
 * @note
 *
@verbatim
Copyright (C) Almohandes.org, 2018

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.
@endverbatim
*******************************************************************************/

/* Includes */
#include "stm32f4xx.h"
#include "Nvic.h"
#include "Gpio.h"
#include"Audio.h"
#include "Systick.h"
#include"flash.h"


/**
 * @addtogroup stm32_examples
 * @{
 */

/**
 * @defgroup main
 * @brief
 * @{
 */

/**
 * @defgroup main_private_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_private_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_private_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_private_variables
 * @{
 */


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup main_exported_functions
 * @{
 */

/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
int main(void)
{




	/******************Basic_Initializations*************/
	SysTick_Init();  //must Systick is before Nvic to alolow the Systick to be configured without ant crash
	Nvic_Init();
	Gpio_Out_init();
	Gpio_In_Init();
	Inp_ExtI_Init();

	/******************* Audio_file*********************/
	Audio_Adc_Init();
	Audio_Timer_Init();

	/********************Flash_Init**********************/
     //flash_init();



	__enable_irq();
  /* Infinite loop */
  while(1)
  {

	  Audio_Process();
	 // flash_process();
	  //SysTick_Delay(100);

  }

}

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
