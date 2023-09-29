#include "Nvic.h"





void Nvic_Init(void)
{

	//set Group of Priority
	/* bits[3:0] are the sub-priority,
	bits[7:4] are the pre-empt priority */
	 NVIC_SetPriorityGrouping(3);



	 //Set Priority
	 NVIC_SetPriority(SysTick_IRQn, 0);
	 NVIC_SetPriority(EXTI1_IRQn, 1);
	 NVIC_SetPriority(  DMA2_Stream0_IRQn, 2);
	// NVIC_SetPriority( TIM3_IRQn , 2);


	 //Enabling IRQn
	// NVIC_EnableIRQ(SysTick_IRQn);  //idon't need to be configured is system clock
	 NVIC_EnableIRQ(EXTI1_IRQn);
	 NVIC_EnableIRQ( DMA2_Stream0_IRQn);
	// NVIC_EnableIRQ(  TIM3_IRQn );





}

