
#ifndef __mbsInterrupt_H
#define __mbsInterrupt_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

void mbs_UsartInterrupt(USART_TypeDef *uart);    // Обработчик прерывыний от USART slave
void mbs_TimInterrupt(TIM_TypeDef *tim);         // Обработчик прерываний от таймера slave

#ifdef __cplusplus
}
#endif
#endif
