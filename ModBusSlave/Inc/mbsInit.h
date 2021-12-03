
#ifndef __mbsInit_H
#define __mbsInit_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "ModbusSlave.h"
	 
// Инициализация модуля
void mbs_Init(uint8_t addr, uint16_t bufLen, uint8_t maxLen, uint16_t timeout, USART_TypeDef *uart,
              TIM_TypeDef *tim, GPIO_TypeDef *dirPort, uint16_t dirPin, uint64_t *time);

#ifdef __cplusplus
}
#endif
#endif
