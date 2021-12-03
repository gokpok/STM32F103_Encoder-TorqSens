
#ifndef __ModbusSlave_H
#define __ModbusSlave_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
	 
// �������� ���������� ������
extern uint16_t *mbsData;       // ����� ������ ������
extern uint16_t  mbsBufLen;     // ������ ������ ������ ������	
extern uint8_t   mbsMaxLen;     // ������������ ������ ������
extern uint8_t   mbsAddr;       // ����� save-����������
extern uint16_t  mbsTimeout;    // �������� �������� �����
	 
	 
// ������������� slave-���������
void MBS_Init(uint8_t addr, uint16_t bufLen, uint8_t maxLen, uint16_t timeout, USART_TypeDef *uart,
              TIM_TypeDef *tim, GPIO_TypeDef *dirPort, uint16_t dirPin, uint64_t *time);
	 
// ���������� slave-���������
FuncRes MBS_Handler(void);
	 
// ���������� ���������� �� USATR (�����/��������)
void MBS_UART_Interrupt(USART_TypeDef *uart);
	 
// ���������� ���������� �� TIM (���������� ������)
void MBS_TIM_Interrupt(TIM_TypeDef *tim);
	 

#ifdef __cplusplus
}
#endif
#endif
