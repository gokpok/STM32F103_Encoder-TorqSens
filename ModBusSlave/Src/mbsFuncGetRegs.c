
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме slave-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль, обрабатывающий запрос с функцией получения значений серии регистров (0x03)
// ------------------------------------------------------------------------------------------------

#include "mbsFuncGetRegs.h"
#include "mbsSendData.h"
#include "mbsError.h"
#include "mbsUtils.h"
#include "mbsData.h"
#include "mbsCRC.h"

	 

// Возврат ответа на запрос с функцией получения серии регистров (0x03) ---------------------------
FuncRes mbs_FuncGetRegs(void)
{
	// Получаем начальный адрес и длинну запрашиваемых данных
	mbsDataBegin = (mbsRxBuf[2] << 8) | mbsRxBuf[3];
	mbsDataNum   = (mbsRxBuf[4] << 8) | mbsRxBuf[5];
	
	// Проверяем запрошенные данные на доступность
	if(mbs_CheckQuerySeries() == FRES_ERR)
		return FRES_ERR;
	
	// Формируем заголовок ответа
	mbsTxBuf[0] = mbsAddr;            // Указаваем адрес slave-устройства
	mbsTxBuf[1] = MBS_FUNC_GET_REGS;  // Указываем код выполняемой функции
	mbsTxBuf[2] = mbsDataNum * 2;     // Указываем кол-во данных в ответе
	
	// Получаем конечный адрес запрашиваемых данных
	mbsDataEnd = mbsDataBegin + mbsDataNum;
	
	mbsCount1 = mbsDataBegin;   // первый счетчик задаем как стартовый адрес запрошенных данных
	mbsCount2 = 3;              // второй счетчик задаем как стартовый адрес запрошенных данных в пакете
		
	// Добавляем в пакет запрошенные данные
	for( ; mbsCount1 <= mbsDataEnd; mbsCount1++, mbsCount2++)
	{
		mbsTxBuf[mbsCount2]   = mbsData[mbsCount1] >> 8;
		mbsTxBuf[++mbsCount2] = mbsData[mbsCount1] & 0x00FF;
	} // for	
	
	// Получаем контрольную сумму сформированнных данных и добавляем в конец пакета
	mbsCRC = mbs_GetCrc16(mbsTxBuf, mbsCount2 - 2);
	mbsTxBuf[mbsCount2 - 2] = mbsCRC & 0x00ff;
	mbsTxBuf[mbsCount2 - 1] = mbsCRC >> 8;	
	
	// Инициируем отправку данных
	mbs_SendDataIni(mbsCount2);
	
	return FRES_OK;
} // mbs_FuncGetRegs()
