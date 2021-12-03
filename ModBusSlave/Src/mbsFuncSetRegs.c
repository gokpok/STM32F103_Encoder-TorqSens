
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме slave-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль, обрабатывающий запрос с функцией задания значений серии регистров (0x10)
// ------------------------------------------------------------------------------------------------

#include "mbsFuncSetRegs.h"
#include "mbsSendData.h"
#include "mbsError.h"
#include "mbsUtils.h"
#include "mbsData.h"
#include "mbsCRC.h"

	 

// Возврат ответа на запрос с функцией получения серии регистров (0x03) ---------------------------
FuncRes mbs_FuncSetRegs(void)
{
	// Получаем начальный адрес и длинну запрашиваемых данных
	mbsDataBegin = (mbsRxBuf[2] << 8) | mbsRxBuf[3];
	mbsDataNum   = (mbsRxBuf[4] << 8) | mbsRxBuf[5];
	
	// Проверяем запрошенные данные на доступность
	if(mbs_CheckQuerySeries() == FRES_ERR)
		return FRES_ERR;
	
	// Формируем заголовок ответа
	mbsTxBuf[0] = mbsAddr;        // Указаваем адрес slave-устройства
	mbsTxBuf[1] = MBS_FUNC_SET_REGS;  // Указываем код выполняемой функции
	mbsTxBuf[2] = mbsRxBuf[2];        // Указываем адрес первого запрошенного регистра (Hi)
	mbsTxBuf[3] = mbsRxBuf[3];        // Указываем адрес первого запрошенного регистра (Low)
	mbsTxBuf[4] = mbsRxBuf[4];        // Указываем кол-во запрошенных регистров (Hi)
	mbsTxBuf[5] = mbsRxBuf[5];        // Указываем кол-во запрошенных регистров (Low)
	
	// Получаем конечный адрес запрашиваемых данных
	mbsDataEnd = mbsDataBegin + mbsDataNum;
	
	mbsCount1 = mbsDataBegin;   // 1й счетчик задаем как стартовый адрес запрошенных данных
	mbsCount2 = 7;                  // 2й счетчик задаем как стартовый адрес запрошенных данных в пакете
		
	// Забираем из пакета запрошенные данные
	for( ; mbsCount1 < mbsDataEnd; mbsCount1++, mbsCount2 += 2)
		mbsData[mbsCount1] = mbsRxBuf[mbsCount2] << 8 | mbsRxBuf[mbsCount2 + 1];
	
	// Получаем контрольную сумму сформированнных данных и добавляем в конец пакета
	mbsCRC = mbs_GetCrc16(mbsTxBuf, 6);
	mbsTxBuf[6] = mbsCRC & 0x00ff;
	mbsTxBuf[7] = mbsCRC >> 8;	
	
	// Инициируем отправку данных
	mbs_SendDataIni(8);
	
	return FRES_OK;
} // mbs_FuncSetRegs()
