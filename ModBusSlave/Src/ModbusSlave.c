
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ��������� ���������� ������
// ------------------------------------------------------------------------------------------------

#include "ModbusSlave.h"
#include "mbsInit.h"
#include "mbsInterrupt.h"
#include "mbsHandler.h"



// ������������� slave-��������� ------------------------------------------------------------------
void MBS_Init(uint8_t addr, uint16_t bufLen, uint8_t maxLen, uint16_t timeout, USART_TypeDef *uart,
              TIM_TypeDef *tim, GPIO_TypeDef *dirPort, uint16_t dirPin, uint64_t *time)
{
	mbs_Init(addr, bufLen, maxLen, timeout, uart, tim, dirPort, dirPin, time);
} // MBS_Init()



// ���������� slave-���������� --------------------------------------------------------------------
FuncRes MBS_Handler(void)
{
	return mbs_Handler();
} // MBS_Handler()



// ���������� ���������� �� USATR (�����/��������) ------------------------------------------------
void MBS_UART_Interrupt(USART_TypeDef *uart)
{
	mbs_UsartInterrupt(uart);
} // MBS_UART_Interrupt()



// ���������� ���������� �� TIM (���������� ������) ------------------------------------------------
void MBS_TIM_Interrupt(TIM_TypeDef *tim)
{
	mbs_TimInterrupt(tim);
} // MBS_TIM_Interrupt()


