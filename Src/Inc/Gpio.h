
#ifndef INC_GPIO_H_
#define INC_GPIO_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "stm32f4xx.h"


typedef enum
{
	Green_Led,
	Red_Led,

}Led;


//extern Led Led_State;


void Gpio_Out_init(void);
void Gpio_In_Init(void);
void Inp_ExtI_Init(void);


void Gpio_on(Led Led_state);
void Gpio_off(Led Led_state);
void Gpio_toggle(Led Led_state);
uint8_t Gpio_read(void);










/* C++ detection */
#ifdef __cplusplus
}
#endif



#endif /* INC_GPIO_H_ */
