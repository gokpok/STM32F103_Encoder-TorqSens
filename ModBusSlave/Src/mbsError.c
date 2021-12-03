
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, �������������� ������� ������ �� ������ � ������� (������������ ������)
// ------------------------------------------------------------------------------------------------

#include "mbsError.h"
#include "mbsSendData.h"
#include "mbsData.h"
#include "mbsCRC.h"
	 

// ������� ������ �� ������ � ������� -------------------------------------------------------------
void mbs_ReturnErr(MBS_ErrEnum err)
{
	// ��������� ����� ������
	mbsTxBuf[0] = mbsAddr;         // ��������� ����� slave-���������
	mbsTxBuf[1] = 0x80 | mbsRxBuf[1];  // ��������� ��� ����������� ������� � ��������� ������
	mbsTxBuf[2] = err;                 // ��������� ��� ������ ���������� �������
	
	// �������� ����������� ����� ��������������� ������ � ��������� � ����� ������
	mbsCRC = mbs_GetCrc16((uint8_t *)mbsTxBuf, 3);
	mbsTxBuf[3] = mbsCRC & 0x00ff;
	mbsTxBuf[4] = mbsCRC >> 8;
		
	// ���������� �������� ������
	mbs_SendDataIni(5);
} // mbs_ReturnErr()
