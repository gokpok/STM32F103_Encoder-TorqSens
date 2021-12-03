
#ifndef __mbsData_H
#define __mbsData_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"


// Определение для пина управления RS485
#define MBS_DIR_ON     HAL_GPIO_WritePin(mbsDirPort, mbsDirPin, GPIO_PIN_SET)
#define MBS_DIR_OFF    HAL_GPIO_WritePin(mbsDirPort, mbsDirPin, GPIO_PIN_RESET)
	 
	 
// Перечисление обрабатываемых фукций обмена
typedef enum
{
	MBS_FUNC_GET_REGS = 0x03,   // Получение значений серии регистров
	MBS_FUNC_SET_REGS = 0x10,	  // Задание значений серии регистров
	MBS_FUNC_CMD      = 0x64,   // Выполнение команды
} MBS_FuncsEnum;


// Закрытые переменные модуля
extern uint8_t  *mbsRxBuf;      // Буфер приема
extern uint8_t  *mbsTxBuf;      // Буфер передачи
extern uint8_t   mbsEndReciev;  // Флаг завершения приема
extern uint16_t  mbsDataBegin;  // Начало запрашиваемых данных
extern uint16_t  mbsDataNum;    // Длинна запрашиваемых данных
extern uint16_t  mbsDataEnd;    // Конец запрашиваемых данных
extern uint16_t  mbsRxLen;      // Длинна полученного пакета
extern uint16_t  mbsTxLen;      // Длинна передаваемого пакета
extern uint16_t  mbsCRC;        // Контрольная сумма
extern uint64_t *mbsTime;       // Счетчик глобальных тиков
extern uint16_t  mbsCount1;     // 1й счетчик собственных нужд
extern uint16_t  mbsCount2;     // 2й счетчик собственных нужд


// Переменные перефирии slave-устройства
extern USART_TypeDef *mbsUart;     // Приемопередатчик
extern TIM_TypeDef   *mbsTim;      // Таймер завершения приема
extern GPIO_TypeDef  *mbsDirPort;  // Порт вывода управления RS485
extern uint16_t       mbsDirPin;   // Пин вывода управления RS485

#ifdef __cplusplus
}
#endif
#endif
