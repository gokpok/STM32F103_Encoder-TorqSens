
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// ------------------------------------------------------------------------------------------------
// ��������� ������������� �������� ������ ������
// ------------------------------------------------------------------------------------------------

#include "mbsData.h"
         
				 
// �������� ���������� ������
uint16_t *mbsData;       // ����� ������ ������
uint16_t  mbsBufLen;     // ������ ������ ������ ������	
uint8_t   mbsMaxLen;     // ������������ ������ ������
uint8_t   mbsAddr;       // ����� save-����������
uint16_t  mbsTimeout;    // �������� �������� �����


// �������� ���������� ������
uint8_t  *mbsRxBuf;      // ����� ������
uint8_t  *mbsTxBuf;      // ����� ��������
uint8_t   mbsEndReciev;  // ���� ���������� ������
uint16_t  mbsDataBegin;  // ������ ������������� ������
uint16_t  mbsDataNum;    // ������ ������������� ������
uint16_t  mbsDataEnd;    // ����� ������������� ������
uint16_t  mbsRxLen;      // ������ ����������� ������
uint16_t  mbsTxLen;      // ������ ������������� ������
uint16_t  mbsCRC;        // ����������� �����
uint64_t *mbsTime;       // ������� ���������� �����
uint16_t  mbsCount1;     // 1� ������� ����������� ����
uint16_t  mbsCount2;     // 2� ������� ����������� ����


// ���������� ��������� slave-����������
USART_TypeDef *mbsUart;     // ����������������
TIM_TypeDef   *mbsTim;      // ������ ���������� ������
GPIO_TypeDef  *mbsDirPort;  // ���� ������ ���������� RS485
uint16_t       mbsDirPin;   // ��� ������ ���������� RS485