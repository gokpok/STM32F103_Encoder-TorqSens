
// ------------------------------------------------------------------------------------------------
// ?????? ?????? ??????? ?? ????????? ModbusRTU ? ?????? slave-??????????
// ??????????? ?? ??????? ?. ?. (edmahalich@yandex.ua)
// 
// ?????????, ??????????? ????????? ???????? ?????????????? ??????
// ------------------------------------------------------------------------------------------------

#include "mbsSendData.h"
#include "mbsData.h"

extern uint16_t txCount;
	 
// ????????? ???????? ??????
void mbs_SendDataIni(uint16_t len)
{		
	// ?????? ????? ????????????? ??????
	mbsTxLen = len;
	
	
	// ???? ???????? ?????? ????, ??
	// ???????? ??? ?????????? ? ???????? ????? (?????????:)
	if(txCount == 0)
	{
		MBS_DIR_ON;
		for(int i = 0; i < 8; i++) __NOP();
	} // if
	
	// ?????????? ?????? ???? ?????? ? UART	
	mbsUart->DR = mbsTxBuf[0];
	txCount++;
	// ?????????? ??????? ???????? ?????????????? ? ???????????
} // mbs_SendDataIni()
