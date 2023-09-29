

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "stm32f4xx.h"




void flash_init(void);
void unlock(void);
void lock(void);
void read_word(uint32_t address,uint32_t value);
void write_word(uint32_t address ,uint32_t data);
void erase_sector(uint8_t sector_num);
void ExtI1_Callback_Flash(void);
void flash_process(void);


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* INC_FLASH_H_ */


