
#include "Gpio.h"





//Led Led_State=Red_Led;

//GPIOD HAVE AHB1  IS WORKING ON 84MH in Max
// GPIOD [D0 ,D1]  as output
void Gpio_Out_init(void)
{
	// clock configuration
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN ;
	// select direction of gpio as output
	GPIOD->MODER &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1)  ;
	GPIOD->MODER |= (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0)  ;
	// select two pin as  push pull mean the output is "1" or "0"
	GPIOD->OTYPER &= ~(GPIO_OTYPER_OT0 |GPIO_OTYPER_OT1  );
	// the output speed is high speed (10)
	GPIOD->OSPEEDR |= (GPIO_OSPEEDR_OSPEED0_1 | GPIO_OSPEEDR_OSPEED1_1);

	/* Enable SYSCFG clock */
	RCC->APB2ENR |= RCC_APB2LPENR_SYSCFGLPEN;

	//Compensation Cell for high speed output
	SYSCFG->CMPCR |= SYSCFG_CMPCR_CMP_PD  ;

//	 while(SYSCFG_CMPCR_READY != (SYSCFG->CMPCR & SYSCFG_CMPCR_READY) )
//	 {
//		 //nothing
//	 }


     /* Select no pull */
     GPIOD->PUPDR &= ~(GPIO_PUPDR_PUPDR0|GPIO_PUPDR_PUPDR1);





}


//GPIOC [C1] as input interrupt with EXtI1
void Gpio_In_Init(void)
{
	/* Enable post GPIOC clock in RCC */
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

		/* Select input mode for PC1 */
		GPIOC->MODER &= ~(GPIO_MODER_MODER1);

		/* Select pull down(10)  */
		GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD1);
		GPIOC->PUPDR |=  (GPIO_PUPDR_PUPD1_1);

}


void Inp_ExtI_Init(void)
{

	  /* Enable SYSCFG clock */
	  RCC->APB2ENR |= RCC_APB2LPENR_SYSCFGLPEN;

	  /* Map PC1 to EXTI1 */
	  SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PC;

	  /* Enable rising edge trigger */
	  EXTI->RTSR |= EXTI_RTSR_TR1;
	  /* Disable falling edge trigger */
	  EXTI->FTSR &= ~(EXTI_FTSR_TR1);
	  /* Enable interrupt line (UnMasking)*/
	  EXTI->IMR |= EXTI_IMR_MR1;
	  /* Enable event line (UnMasking) */
	  EXTI->EMR |= EXTI_EMR_MR1;



}


void Gpio_on(Led Led_state)
{
	switch( Led_state)
	{
		case(Green_Led):
		    GPIOD->BSRR = (GPIO_BSRR_BS0 );
				break;
		case(Red_Led):
		    GPIOD->BSRR = (GPIO_BSRR_BS1 );
				break;
		default:
			break;

	}



}
void Gpio_off(Led Led_state)
{

	switch( Led_state)
		{
			case(Green_Led):
				GPIOD->BSRR = (GPIO_BSRR_BR0 );
					break;
			case(Red_Led):
				GPIOD->BSRR = (GPIO_BSRR_BR1 );
					break;
			default:
				break;
		}
}


void Gpio_toggle(Led Led_state)
{
	switch( Led_state)
	{
			case(Green_Led):
				 GPIOD->ODR ^= GPIO_ODR_OD0;
					break;
			case(Red_Led):
				 GPIOD->ODR ^= GPIO_ODR_OD1;
					break;
			default:
				break;
	}
}

uint8_t Gpio_read(void)
{

	if( GPIO_IDR_ID1 == (GPIOC->IDR & GPIO_IDR_ID1 ))
	{
		return(1);
	}

	else{
		return(0);
	}

}




