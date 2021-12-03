
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, ��������������� ��������������� ������� ������
// ------------------------------------------------------------------------------------------------

#include "mbsUtils.h"
#include "mbsError.h"
#include "mbsData.h"


// �������� ����������� ����� ������������� ������
FuncRes mbs_CheckQuerySeries(void)
{
	// ��������� �� ����������� ������ ����������� �����	
	if(mbsDataNum > mbsMaxLen)
	{
		mbs_ReturnErr(MBS_ERR_BADADDR);
		return FRES_ERR;
	} // if
	
	// ��������� �� ����� �� ������� ������� ������
	if((mbsDataBegin + mbsDataNum) > mbsBufLen)
	{
		mbs_ReturnErr(MBS_ERR_BADADDR);
		return FRES_ERR;
	} // if
	
	// ���� ���������� ������� �� ��������� - ���������� ������������� ����������
	return FRES_OK;
} // mbs_CheckQuerySeries()
