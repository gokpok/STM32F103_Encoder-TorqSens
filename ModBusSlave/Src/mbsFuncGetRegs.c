
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, �������������� ������ � �������� ��������� �������� ����� ��������� (0x03)
// ------------------------------------------------------------------------------------------------

#include "mbsFuncGetRegs.h"
#include "mbsSendData.h"
#include "mbsError.h"
#include "mbsUtils.h"
#include "mbsData.h"
#include "mbsCRC.h"

	 

// ������� ������ �� ������ � �������� ��������� ����� ��������� (0x03) ---------------------------
FuncRes mbs_FuncGetRegs(void)
{
	// �������� ��������� ����� � ������ ������������� ������
	mbsDataBegin = (mbsRxBuf[2] << 8) | mbsRxBuf[3];
	mbsDataNum   = (mbsRxBuf[4] << 8) | mbsRxBuf[5];
	
	// ��������� ����������� ������ �� �����������
	if(mbs_CheckQuerySeries() == FRES_ERR)
		return FRES_ERR;
	
	// ��������� ��������� ������
	mbsTxBuf[0] = mbsAddr;            // ��������� ����� slave-����������
	mbsTxBuf[1] = MBS_FUNC_GET_REGS;  // ��������� ��� ����������� �������
	mbsTxBuf[2] = mbsDataNum * 2;     // ��������� ���-�� ������ � ������
	
	// �������� �������� ����� ������������� ������
	mbsDataEnd = mbsDataBegin + mbsDataNum;
	
	mbsCount1 = mbsDataBegin;   // ������ ������� ������ ��� ��������� ����� ����������� ������
	mbsCount2 = 3;              // ������ ������� ������ ��� ��������� ����� ����������� ������ � ������
		
	// ��������� � ����� ����������� ������
	for( ; mbsCount1 <= mbsDataEnd; mbsCount1++, mbsCount2++)
	{
		mbsTxBuf[mbsCount2]   = mbsData[mbsCount1] >> 8;
		mbsTxBuf[++mbsCount2] = mbsData[mbsCount1] & 0x00FF;
	} // for	
	
	// �������� ����������� ����� ��������������� ������ � ��������� � ����� ������
	mbsCRC = mbs_GetCrc16(mbsTxBuf, mbsCount2 - 2);
	mbsTxBuf[mbsCount2 - 2] = mbsCRC & 0x00ff;
	mbsTxBuf[mbsCount2 - 1] = mbsCRC >> 8;	
	
	// ���������� �������� ������
	mbs_SendDataIni(mbsCount2);
	
	return FRES_OK;
} // mbs_FuncGetRegs()
