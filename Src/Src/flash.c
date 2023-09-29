#include"flash.h"
#include "Gpio.h"
#include "Systick.h"

/*

 Block Name Block base addresses Size
Main memory:
              Sector 0 0x0800 0000 - 0x0800 3FFF 16 Kbytes
              Sector 1 0x0800 4000 - 0x0800 7FFF 16 Kbytes
              Sector 2 0x0800 8000 - 0x0800 BFFF 16 Kbytes
              Sector 3 0x0800 C000 - 0x0800 FFFF 16 Kbytes
              Sector 4 0x0801 0000 - 0x0801 FFFF 64 Kbytes
              Sector 5 0x0802 0000 - 0x0803 FFFF 128 Kbytes
              Sector 6 0x0804 0000 - 0x0805 FFFF 128 Kbytes
              Sector 7 0x0806 0000 - 0x0807 FFFF 128 Kbytes
System memory:
                       0x1FFF 0000 - 0x1FFF 77FF 30 Kbytes
OTP area :
                       0x1FFF 7800 - 0x1FFF 7A0F 528 bytes

Option bytes :
                        0x1FFF C000 - 0x1FFF C00F 16 byte

*/


uint8_t counter_push=0;
uint32_t Reading_value=0;



void flash_init(void)
{

	/**** unlocking ****/
	 /* Write KEY1 */
	FLASH->KEYR = 0x45670123;
	 /* Write KEY2 */
	FLASH->KEYR = 0xCDEF89AB;


	//select zero  wait cycles for  allowing to  operating flash
	//FLASH->ACR |= FLASH_ACR_LATENCY_0WS;

	/* Select flash parallelism x32 */
	  FLASH->CR &= ~FLASH_CR_PSIZE;
	  FLASH->CR |= FLASH_CR_PSIZE_1;

	/* Write lock bit */
	 FLASH->CR |= FLASH_CR_LOCK;

}




void unlock(void)
{
	// two keys for unlockig the flash interface :)a KEY1 = 0x45670123  [32bits]
	//b) KEY2 = 0xCDEF89AB [32bits]
	FLASH->KEYR |= 0x45670123  ;
	FLASH->KEYR |= 0xCDEF89AB  ;


}




void lock(void)
{
	FLASH->CR |=FLASH_CR_LOCK;

}



void read_word(uint32_t address,uint32_t value)
{
	unlock();
	value= * (uint32_t *)address; // (uint32_t *) address to make address pointer point to 32bit data

}





void write_word(uint32_t address ,uint32_t data)
{

	unlock();
	//check the busy flag is_not ready to can write .
	 while(0 != (FLASH->SR & FLASH_SR_BSY))
		   {
		         /* Waiting */
		     }

	//to activate the program operation
	FLASH->CR |=FLASH_CR_PG;

	*(volatile uint32_t*)(address) = data;   // it is very pretty ^_^


	/* Wait busy flag */
    while(0 != (FLASH->SR & FLASH_SR_BSY))
	   {
	         /* Waiting */
	     }

	 /* Disable flash programming */
	   FLASH->CR &= ~FLASH_CR_PG;



}





void erase_sector(uint8_t sector_num)
{
	unlock();
	//check the busy flag is_not ready to can write .
	 while(0 != (FLASH->SR & FLASH_SR_BSY))
		{
		      /* Waiting */
		}

    //to activate the erase operation
   	FLASH->CR |=FLASH_CR_SER ;

    if(12 <= sector_num)
    {
      /* Bank 2 */
      sector_num = sector_num + 4;
      //so sector_num return to the first sectors
    }
    else
    {

    }


    /* Write sector number */
    FLASH->CR |= (FLASH_CR_SNB & (sector_num << 3));

	//Start programming operation
	FLASH->CR |= FLASH_CR_STRT;

	 while(0 != (FLASH->SR & FLASH_SR_BSY))
		 {
		     /* Waiting */
		 }

	/* Disable sector erase */
	  FLASH->CR &= ~FLASH_CR_SER;


}


void ExtI1_Callback_Flash(void)
{
	 // Clear pending bit
	    EXTI->PR |= EXTI_PR_PR1;
	    counter_push++;

}


void flash_process(void)
{

	 if (counter_push == 1)
		{
		    //  Sector 4 - 0x08010000 -
		    erase_sector(4);
		 	write_word(0x08010000 ,800);
		 	Gpio_on(Green_Led);
		 	SysTick_Delay(100);
		 	Gpio_off(Green_Led);
			SysTick_Delay(100);
		 }
	 else if (counter_push == 2)
		  {
		    //Gpio_on(Red_Led);
		    //  Sector 4 0x08010000
		    read_word(0x08010000,Reading_value);
		    if(Reading_value==800)
		    {
		    	Gpio_on(Green_Led);
		    }
		    else
		    {
		    	Gpio_on(Red_Led);
		    }
		  }
	 else if (counter_push == 3)
		  {
		 	 erase_sector(4);
			Gpio_off(Red_Led);
			Gpio_off(Green_Led);
			lock();
			counter_push =0;
		  }
	else
		   {
		       // Perform any other necessary actions when counter_push is not 1, 2, or 3
		   }


}
