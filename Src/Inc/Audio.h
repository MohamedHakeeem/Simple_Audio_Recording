

#ifndef INC_AUDIO_H_
#define INC_AUDIO_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif


/* Includes */
#include "stm32f4xx.h"




void Audio_Adc_Init(void);
void Audio_Timer_Init(void);
void Transmit_DMA(const uint16_t *Buffer,uint16_t size);
void Audio_Process(void);
void AUDIO_DMA2_Stream0_Callback(void);
void EXTI1_Callback(void);
void ADC_IRQ_Callback(void);












/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* INC_AUDIO_H_ */
