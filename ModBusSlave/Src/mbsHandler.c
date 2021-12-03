
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, ����������� ���������� ������ ������� slave-����������
// ------------------------------------------------------------------------------------------------

#include "mbsHandler.h"
#include "mbsError.h"
#include "mbsFuncGetRegs.h"
#include "mbsFuncSetRegs.h"
#include "mbsFuncCmd.h"
#include "mbsData.h"
#include "mbsCRC.h"


// ���������� ���������
uint64_t lastLinkTime;     // ����� ��������� �����


// ������� ������
FuncRes mbs_CheckTimeout(void);   // �������� �������� �����
FuncRes mbs_CheckCRC(void);       // �������� ����������� �����
FuncRes mbs_RequestProc(void);    // ��������� �������



// ���������� ������ ������� ----------------------------------------------------------------------
FuncRes mbs_Handler(void)
{	
	// ���� �������� ������ ��� - ���������� ��������� �������� ��������
	if(mbsEndReciev == 0) return mbs_CheckTimeout();
	
	// ���������� ���� �������� ������
	mbsEndReciev = 0;
	
	// ���� ����� ������� �� ��� - ���������� ��������� �������� ��������
	if(mbsRxBuf[0] != mbsAddr) return mbs_CheckTimeout();
	
	// ���� ��� ������ = 0 (������ �� ����������������� ��������) - ���������� ��������� �������� ��������
	if(mbsAddr == 0) return mbs_CheckTimeout();
	
	// ���� ����������� ����� �� �������� - ���������� ��������� �������� ��������
	if(mbs_CheckCRC() != FRES_OK) return mbs_CheckTimeout();
		
	// ��������� ��������� ������� � ��������� � ����
	// ��������� �� ������� Ok - ���������� ��������� �������� ��������
	if(mbs_RequestProc() != FRES_OK) return mbs_CheckTimeout();
	
	// ���� ���������� ������� �� ���������, ��...
	lastLinkTime = *mbsTime;  // ���������� ����� ��������� �������
	return FRES_OK;               // ���������� ������������� ���������
} // mbs_Handler



// �������� �������� ����� ------------------------------------------------------------------------
FuncRes mbs_CheckTimeout(void)
{
	// ���� ����� �������� ����� - ���������� ������, ����� - ���������� ����������
	if(*mbsTime < (lastLinkTime + mbsTimeout))
		return FRES_NONE;
	else
		return FRES_ERR;
} // mbs_CheckTimeOut()



// �������� ����������� ����� ---------------------------------------------------------------------
FuncRes mbs_CheckCRC(void)
{
	// ������� ����������� ����� �������� ������
	mbsCRC = mbs_GetCrc16(mbsRxBuf, (mbsRxLen - 2));
	
	// ���������� ���������� ����� � ����������� � �������
	if((mbsRxBuf[mbsRxLen - 2] == (mbsCRC & 0x0F)) && (mbsRxBuf[mbsRxLen - 1] == (mbsCRC >> 8)))
		return FRES_OK;
	else
		return FRES_ERR;
} // mbs_CheckCRC()



// ��������� ������� ------------------------------------------------------------------------------
FuncRes mbs_RequestProc(void)
{
	// ������������ ������ � ������������ � �������� ��������
	switch(mbsRxBuf[1])
	{
		// ������� ��������� ����� ���������
		case MBS_FUNC_GET_REGS:
			return mbs_FuncGetRegs();
		
		// ������� ������� ����� ���������
		case MBS_FUNC_SET_REGS:
			return mbs_FuncSetRegs();
		
		// ������� ������� ����� ���������
//		case MBS_FUNC_CMD:
//			return mbs_FuncCmd();
				
		// ���� ������� ������� �� ��������������, ��...
		default:
			mbs_ReturnErr(MBS_ERR_BADFUNC);  // ���������� ����� ������
			return mbs_CheckTimeout();       // ���������� ��������� �������� ��������
	} // switch
} // mbs_RequestProc()
