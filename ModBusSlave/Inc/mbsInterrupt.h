
#ifndef __mbsInterrupt_H
#define __mbsInterrupt_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

void mbs_UsartInterrupt(USART_TypeDef *uart);    // ���������� ���������� �� USART slave
void mbs_TimInterrupt(TIM_TypeDef *tim);         // ���������� ���������� �� ������� slave

#ifdef __cplusplus
}
#endif
#endif
