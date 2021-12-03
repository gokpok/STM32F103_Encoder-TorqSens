
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме slave-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль, реализующий обработчик обмена данными slave-устройства
// ------------------------------------------------------------------------------------------------

#include "mbsHandler.h"
#include "mbsError.h"
#include "mbsFuncGetRegs.h"
#include "mbsFuncSetRegs.h"
#include "mbsFuncCmd.h"
#include "mbsData.h"
#include "mbsCRC.h"


// Переменные подмодуля
uint64_t lastLinkTime;     // Время последней связи


// Функции модуля
FuncRes mbs_CheckTimeout(void);   // Проверка таймаута связи
FuncRes mbs_CheckCRC(void);       // Проверка контрольной суммы
FuncRes mbs_RequestProc(void);    // Обработка запроса



// Обработчик обмена данными ----------------------------------------------------------------------
FuncRes mbs_Handler(void)
{	
	// Если принятых данных нет - возвращаем результат проверки таймаута
	if(mbsEndReciev == 0) return mbs_CheckTimeout();
	
	// Сбрасываем флаг принятых данных
	mbsEndReciev = 0;
	
	// Если адрес запроса не наш - возвращаем результат проверки таймаута
	if(mbsRxBuf[0] != mbsAddr) return mbs_CheckTimeout();
	
	// Если наш аддрес = 0 (защита от широковещательных запросов) - возвращаем результат проверки таймаута
	if(mbsAddr == 0) return mbs_CheckTimeout();
	
	// Если контрольная сумма на сходится - возвращаем результат проверки таймаута
	if(mbs_CheckCRC() != FRES_OK) return mbs_CheckTimeout();
		
	// Выполняем обработку запроса с проверкой и если
	// обработка не вернула Ok - возвращаем результат проверки таймаута
	if(mbs_RequestProc() != FRES_OK) return mbs_CheckTimeout();
	
	// Если предыдущие условия не сработали, то...
	lastLinkTime = *mbsTime;  // Запоминаем время обработки запроса
	return FRES_OK;               // Возвращаем положительный результат
} // mbs_Handler



// Проверка таймаута связи ------------------------------------------------------------------------
FuncRes mbs_CheckTimeout(void)
{
	// Если время таймаута вышло - возвращаем ошибку, иначе - отсутствие результата
	if(*mbsTime < (lastLinkTime + mbsTimeout))
		return FRES_NONE;
	else
		return FRES_ERR;
} // mbs_CheckTimeOut()



// Проверка контрольной суммы ---------------------------------------------------------------------
FuncRes mbs_CheckCRC(void)
{
	// Подсчет контрольной суммы принятых данных
	mbsCRC = mbs_GetCrc16(mbsRxBuf, (mbsRxLen - 2));
	
	// Сравниваем полученную сумму с заяваленной в запросе
	if((mbsRxBuf[mbsRxLen - 2] == (mbsCRC & 0x0F)) && (mbsRxBuf[mbsRxLen - 1] == (mbsCRC >> 8)))
		return FRES_OK;
	else
		return FRES_ERR;
} // mbs_CheckCRC()



// Обработка запроса ------------------------------------------------------------------------------
FuncRes mbs_RequestProc(void)
{
	// Обрабатываем запрос в соответствии с заданной функцией
	switch(mbsRxBuf[1])
	{
		// Функция получения серии регистров
		case MBS_FUNC_GET_REGS:
			return mbs_FuncGetRegs();
		
		// Функция задания серии регистров
		case MBS_FUNC_SET_REGS:
			return mbs_FuncSetRegs();
		
		// Функция задания серии регистров
//		case MBS_FUNC_CMD:
//			return mbs_FuncCmd();
				
		// Если функция запроса не поддерживается, то...
		default:
			mbs_ReturnErr(MBS_ERR_BADFUNC);  // Отправляем ответ ошибки
			return mbs_CheckTimeout();       // Возвращаем результат проверки таймаута
	} // switch
} // mbs_RequestProc()
