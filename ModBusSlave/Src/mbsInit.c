
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме slave-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль инициализации модуля
// ------------------------------------------------------------------------------------------------

#include "mbsInit.h"
#include "mbsData.h"
#include "stdlib.h"



// Инициализация интерфейса modbus master ---------------------------------------------------------
void mbs_Init(uint8_t addr, uint16_t bufLen, uint8_t maxLen, uint16_t timeout, USART_TypeDef *uart,
              TIM_TypeDef *tim, GPIO_TypeDef *dirPort, uint16_t dirPin, uint64_t *time)
{
	// Сохраняем переменные инициализации
	mbsAddr    = addr;
	mbsBufLen  = bufLen;
	mbsMaxLen  = maxLen > bufLen ? bufLen : maxLen;
	mbsTimeout = timeout;
	mbsTime    = time;
	
	// Запоминаем перефирийные переменные
	mbsUart    = uart;
	mbsTim     = tim;
	mbsDirPort = dirPort;
	mbsDirPin  = dirPin;
	
	// Выделяем память под буферы модуля
	mbsData  = (uint16_t*) malloc(mbsBufLen * sizeof(uint16_t));
	mbsRxBuf = (uint8_t*)  malloc(mbsMaxLen * sizeof(uint8_t) * 2 + 10);
	mbsTxBuf = (uint8_t*)  malloc(mbsMaxLen * sizeof(uint8_t) * 2 + 10);
} // mbs_Init()
