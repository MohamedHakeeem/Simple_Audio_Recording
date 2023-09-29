#include "Audio.h"
#include "Gpio.h"
#include "Systick.h"


typedef enum
{
	idle_state,
	recordname_starting,
	recordname_Playing,

}Audio_State;


Audio_State State=idle_state;
//Number of audio samples[sample time from timer2=125 us], recording length =40000*125*10^(-6)= 5s
uint16_t Name_Buffer[40000]={0};
uint8_t recordingFinished = 0;



/****with GPIOC [C0] as analog [ADC1_IN10}****/
void Audio_Adc_Init(void)
{

	/***********init gpioc as analog*************/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN ;
	/*select direction of gpio as analog mode(11)*/
	GPIOC->MODER &= ~GPIO_MODER_MODE0  ;
	GPIOC->MODER |= GPIO_MODER_MODE0   ;
	/* Select no pull (reset state)  */
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR0;

	/********init continues reguler ADC1  ********/
		  /* Enable ADC1 clock */
		    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
		  /*Resolution 12bit (00)(15cycle for one sample)*/
		   ADC1->CR1 &= ~ADC_CR1_RES;
		   /* Enable ADC */
		   ADC1->CR2 |= ADC_CR2_ADON;

		   /* Select external event for regular group [1000]: Timer 3 TRGO event*/
		   ADC1->CR2 &= ~ADC_CR2_EXTSEL;
		   ADC1->CR2 |= (ADC_CR2_EXTSEL_3);

		   /* Select ADC1_IN110 regular */
		    ADC1->SQR1 &= ~ADC_SQR1_L;
		    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
		    ADC1->SQR3 |= (ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_3);
		   /* Continuous DMA requests */
		    ADC1->CR2 |= ADC_CR2_DDS;

		   /* Enable DMA mode in ADC */
		    ADC1->CR2 |= ADC_CR2_DMA;

	/*********init DMA 2***************/
	/* Enable DMA clock in RCC */
	  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	/*chech it is disabled*/
	if(DMA_SxCR_EN ==(DMA2_Stream0->CR & DMA_SxCR_EN))
	{
		DMA2_Stream0->CR &= ~DMA_SxCR_EN ;  //disable stream before configuration
		while(DMA_SxCR_EN ==(DMA2_Stream0->CR & DMA_SxCR_EN))
		{
			//wait until the Dma become disable
		}
	}

	else
	{
	}

	/* Select the DMA channel 0 in CHSEL[2:0] in the DMA_SxCR */
	  DMA2_Stream0->CR &= ~DMA_SxCR_CHSEL;
	  /* Select stream priority very high */
	  DMA2_Stream0->CR |= DMA_SxCR_PL;
	  /* Select the data transfer direction peripheral(ADC)-to-memory */
	  DMA2_Stream0->CR &= ~DMA_SxCR_DIR;
	  /* Select memory and peripherals sizes 2 bytes for buffer register type it is uint16_t*/
	  DMA2_Stream0->CR |= DMA_SxCR_MSIZE_0;
	  DMA2_Stream0->CR |= DMA_SxCR_PSIZE_0;
	  /* Select FIFO mode */
	  DMA2_Stream0->FCR |= DMA_SxFCR_DMDIS;
	  /* Select FIFO threshold level half FIFO */
	  DMA2_Stream0->FCR |= (DMA_SxFCR_FTH_0 | DMA_SxFCR_FTH_1);
	  /* Select memory incremented mode, peripheral shall has fixed address */
	  DMA2_Stream0->CR |= DMA_SxCR_MINC;
	  /* Enable DMA transfer complete interrupt */
	  DMA2_Stream0->CR |= DMA_SxCR_TCIE;
	  /* Set peripheral address */
	  DMA2_Stream0->PAR = (uint32_t)&ADC1->DR;
	  /* Set memory address */
	  DMA2_Stream0->M0AR = (uint32_t)Name_Buffer;
	  /* Set number of data items */
	  DMA2_Stream0->NDTR =40000;

}

/*******[Timer 3 TRGO event]************/

void Audio_Timer_Init(void)
{

	/*  configuration of clock */
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN ;
	/*up_counter*/
	TIM3->CR1 &= ~TIM_CR1_DIR;
	/* Set timer Pre_scaler, bus clock = 42 MHz, Tim_Clock = 84 MHz   if the prescaler isnot set to (1)
	   * the bus timer clock is twice of the APB1 bus clock
	   * fCK_PSC / (PSC[15:0] + 1)
	   * CK_CNT = 84000000 / (83 + 1) -> 1000000 Hz -> time base = 1 us */
	 TIM3->PSC =83;
	 /*overflow occur 125us */
 	 TIM3->ARR = 125;
	/* Timer2 as master (update:010) for triggering of adc1*/
	TIM3->CR2 &= ~TIM_CR2_MMS;
	TIM3->CR2 |= TIM_CR2_MMS_1 ;

	 /* Enable TIM3 counter */
	TIM3->CR1 |= TIM_CR1_CEN;


}





void Audio_Process(void)
{
	 switch(State)
	 {
	     case(idle_state):
	 	 	 break;
	 	 case(recordname_starting):
		     Gpio_on(Red_Led);
	 		 /* Enable DMA 2 stream 0 */
	 		 DMA2_Stream0->CR |= DMA_SxCR_EN;
	         /* Enable external trigger on rising edge */
	 		 ADC1->CR2 |= ADC_CR2_EXTEN_0;
			 State=recordname_Playing;

			 break;
	 	case(recordname_Playing):
	 		 if(recordingFinished==1)
	 		 {
	 			 /* Disable external trigger */
	 			  ADC1->CR2 &= ~ADC_CR2_EXTEN;
	 			  Gpio_off(Red_Led);
	 			  /* Reset recording finished flag */
	 			  recordingFinished = 0;
	 			   /* Change current mode */
	 			  State=idle_state;

	 		 }
	 		 else
	 		 {
	 			 //nothing
	 		 }
	 		 break;

	 	default:
	 		break;

	 }
}

void EXTI1_Callback(void)
{
	uint32_t current_tick=0;

	//Clear pending bit */
		EXTI->PR |= EXTI_PR_PR1;

	uint32_t start_tick=SysTick_GetCurrentTick();

	while(Gpio_read()==1)
	{
		current_tick=SysTick_GetCurrentTick();

		if((current_tick-start_tick)>=500)   //wait the button pressed until 0.5second
			{
			   State=recordname_starting;
			   //Gpio_on(Green_Led);
			}
		else
			{
			      /* Do nothing */
			}

	}



}


void AUDIO_DMA2_Stream0_Callback(void)
{
  /* Check transfer complete flag */
  if(DMA_LISR_TCIF0 == (DMA_LISR_TCIF0 & DMA2->LISR))
  {
    /* Clear all interrupt flags */
    DMA2->LIFCR = (DMA_LIFCR_CFEIF0 | DMA_LIFCR_CDMEIF0 | DMA_LIFCR_CTEIF0
        | DMA_LIFCR_CHTIF0 | DMA_LIFCR_CTCIF0);

    /* Set Recording finished flag */
    recordingFinished = 1;
  }
  else
  {
    /* Do nothing, this interrupt is not handled */
  }
}




