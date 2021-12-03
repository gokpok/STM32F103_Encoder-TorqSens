
#ifndef __ModbusSlave_H
#define __ModbusSlave_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
	 
// Открытые переменные модуля
extern uint16_t *mbsData;       // Масив данных обмена
extern uint16_t  mbsBufLen;     // Размер масива данных обмена	
extern uint8_t   mbsMaxLen;     // Максимальный размер обмена
extern uint8_t   mbsAddr;       // Адрес save-устройства
extern uint16_t  mbsTimeout;    // Величина таймаута связи
	 
	 
// Инициализация slave-усройства
void MBS_Init(uint8_t addr, uint16_t bufLen, uint8_t maxLen, uint16_t timeout, USART_TypeDef *uart,
              TIM_TypeDef *tim, GPIO_TypeDef *dirPort, uint16_t dirPin, uint64_t *time);
	 
// Обработчик slave-усройства
FuncRes MBS_Handler(void);
	 
// Обработчик прерывания по USATR (прием/передача)
void MBS_UART_Interrupt(USART_TypeDef *uart);
	 
// Обработчик прерывания по TIM (завершение приема)
void MBS_TIM_Interrupt(TIM_TypeDef *tim);
	 

#ifdef __cplusplus
}
#endif
#endif
