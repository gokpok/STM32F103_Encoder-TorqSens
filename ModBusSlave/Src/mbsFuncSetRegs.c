
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, �������������� ������ � �������� ������� �������� ����� ��������� (0x10)
// ------------------------------------------------------------------------------------------------

#include "mbsFuncSetRegs.h"
#include "mbsSendData.h"
#include "mbsError.h"
#include "mbsUtils.h"
#include "mbsData.h"
#include "mbsCRC.h"

	 

// ������� ������ �� ������ � �������� ��������� ����� ��������� (0x03) ---------------------------
FuncRes mbs_FuncSetRegs(void)
{
	// �������� ��������� ����� � ������ ������������� ������
	mbsDataBegin = (mbsRxBuf[2] << 8) | mbsRxBuf[3];
	mbsDataNum   = (mbsRxBuf[4] << 8) | mbsRxBuf[5];
	
	// ��������� ����������� ������ �� �����������
	if(mbs_CheckQuerySeries() == FRES_ERR)
		return FRES_ERR;
	
	// ��������� ��������� ������
	mbsTxBuf[0] = mbsAddr;        // ��������� ����� slave-����������
	mbsTxBuf[1] = MBS_FUNC_SET_REGS;  // ��������� ��� ����������� �������
	mbsTxBuf[2] = mbsRxBuf[2];        // ��������� ����� ������� ������������ �������� (Hi)
	mbsTxBuf[3] = mbsRxBuf[3];        // ��������� ����� ������� ������������ �������� (Low)
	mbsTxBuf[4] = mbsRxBuf[4];        // ��������� ���-�� ����������� ��������� (Hi)
	mbsTxBuf[5] = mbsRxBuf[5];        // ��������� ���-�� ����������� ��������� (Low)
	
	// �������� �������� ����� ������������� ������
	mbsDataEnd = mbsDataBegin + mbsDataNum;
	
	mbsCount1 = mbsDataBegin;   // 1� ������� ������ ��� ��������� ����� ����������� ������
	mbsCount2 = 7;                  // 2� ������� ������ ��� ��������� ����� ����������� ������ � ������
		
	// �������� �� ������ ����������� ������
	for( ; mbsCount1 < mbsDataEnd; mbsCount1++, mbsCount2 += 2)
		mbsData[mbsCount1] = mbsRxBuf[mbsCount2] << 8 | mbsRxBuf[mbsCount2 + 1];
	
	// �������� ����������� ����� ��������������� ������ � ��������� � ����� ������
	mbsCRC = mbs_GetCrc16(mbsTxBuf, 6);
	mbsTxBuf[6] = mbsCRC & 0x00ff;
	mbsTxBuf[7] = mbsCRC >> 8;	
	
	// ���������� �������� ������
	mbs_SendDataIni(8);
	
	return FRES_OK;
} // mbs_FuncSetRegs()
