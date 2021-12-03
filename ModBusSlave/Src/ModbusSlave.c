
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме slave-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль интерфейса модуля
// ------------------------------------------------------------------------------------------------

#include "ModbusSlave.h"
#include "mbsInit.h"
#include "mbsInterrupt.h"
#include "mbsHandler.h"



// Инициализация slave-усройства ------------------------------------------------------------------
void MBS_Init(uint8_t addr, uint16_t bufLen, uint8_t maxLen, uint16_t timeout, USART_TypeDef *uart,
              TIM_TypeDef *tim, GPIO_TypeDef *dirPort, uint16_t dirPin, uint64_t *time)
{
	mbs_Init(addr, bufLen, maxLen, timeout, uart, tim, dirPort, dirPin, time);
} // MBS_Init()



// Обработчик slave-устройства --------------------------------------------------------------------
FuncRes MBS_Handler(void)
{
	return mbs_Handler();
} // MBS_Handler()



// Обработчик прерывания по USATR (прием/передача) ------------------------------------------------
void MBS_UART_Interrupt(USART_TypeDef *uart)
{
	mbs_UsartInterrupt(uart);
} // MBS_UART_Interrupt()



// Обработчик прерывания по TIM (завершение приема) ------------------------------------------------
void MBS_TIM_Interrupt(TIM_TypeDef *tim)
{
	mbs_TimInterrupt(tim);
} // MBS_TIM_Interrupt()


