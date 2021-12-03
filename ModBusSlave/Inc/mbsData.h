
#ifndef __mbsData_H
#define __mbsData_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"


// ����������� ��� ���� ���������� RS485
#define MBS_DIR_ON     HAL_GPIO_WritePin(mbsDirPort, mbsDirPin, GPIO_PIN_SET)
#define MBS_DIR_OFF    HAL_GPIO_WritePin(mbsDirPort, mbsDirPin, GPIO_PIN_RESET)
	 
	 
// ������������ �������������� ������ ������
typedef enum
{
	MBS_FUNC_GET_REGS = 0x03,   // ��������� �������� ����� ���������
	MBS_FUNC_SET_REGS = 0x10,	  // ������� �������� ����� ���������
	MBS_FUNC_CMD      = 0x64,   // ���������� �������
} MBS_FuncsEnum;


// �������� ���������� ������
extern uint8_t  *mbsRxBuf;      // ����� ������
extern uint8_t  *mbsTxBuf;      // ����� ��������
extern uint8_t   mbsEndReciev;  // ���� ���������� ������
extern uint16_t  mbsDataBegin;  // ������ ������������� ������
extern uint16_t  mbsDataNum;    // ������ ������������� ������
extern uint16_t  mbsDataEnd;    // ����� ������������� ������
extern uint16_t  mbsRxLen;      // ������ ����������� ������
extern uint16_t  mbsTxLen;      // ������ ������������� ������
extern uint16_t  mbsCRC;        // ����������� �����
extern uint64_t *mbsTime;       // ������� ���������� �����
extern uint16_t  mbsCount1;     // 1� ������� ����������� ����
extern uint16_t  mbsCount2;     // 2� ������� ����������� ����


// ���������� ��������� slave-����������
extern USART_TypeDef *mbsUart;     // ����������������
extern TIM_TypeDef   *mbsTim;      // ������ ���������� ������
extern GPIO_TypeDef  *mbsDirPort;  // ���� ������ ���������� RS485
extern uint16_t       mbsDirPin;   // ��� ������ ���������� RS485

#ifdef __cplusplus
}
#endif
#endif
