
// ------------------------------------------------------------------------------------------------
// ?????? ?????? ??????? ?? ????????? ModbusRTU ? ?????? slave-??????????
// ??????????? ?? ??????? ?. ?. (edmahalich@yandex.ua)
// 
// ????????? ????????? ??????????
// ------------------------------------------------------------------------------------------------

#include "mbsInterrupt.h"
#include "mbsData.h"

uint16_t  rxCount = 0;     // ??????? ???????? ??????
uint16_t  txCount = 0;     // ??????? ????????? ??????

void mbs_RxInterrupt(void);      // ????? ?????? ?? USART
void mbs_TxInterrupt(void);      // ???????? ?????? ?? USART



// ????????? ?????????? ?? USART ------------------------------------------------------------------
void mbs_UsartInterrupt(USART_TypeDef *uart)
{	
	// ????????? ????????? ?????????????? ???? ??????????
	if(uart->SR & USART_SR_TC)
		// ???????????? ????????
		mbs_TxInterrupt();                  
	else if(uart->SR & USART_SR_RXNE)
		// ???????????? ?????
		mbs_RxInterrupt(); 

	// ?????????? ??????????
	uart->SR = 0;	
} // mbs_UsartInterrupt



// ????????? ?????????? ?? TIM --------------------------------------------------------------------
void mbs_TimInterrupt(TIM_TypeDef *tim)
{
	// ????????????? ??????
	mbsTim->CR1 &=~ TIM_CR1_CEN;	
	
	// ?????????? ??????????
	tim->SR = 0;
	
	// ?????????? ???????? ?????????? ???????? ?????? ?????? (????? ??????)
	// ?????? ???? ???????????? ??????? ????????? ??????
	mbsEndReciev = 1;
	
	// ?????????? ?????? ?????? ? ?????????? ??????? ?????????? ??????
	mbsRxLen = rxCount;
	rxCount = 0;
} // mbs_TimInterrupt()



// ????? ?????? ?? USART --------------------------------------------------------------------------
void mbs_RxInterrupt(void)
{
	// ????????? ?????????? ????? ?? ?????? USART
	mbsRxBuf[rxCount] = mbsUart->DR;

	rxCount++;				// ??????????? ??????? ?????????? ??????

	// ????????????? ?????? ?????????? ?????? (????? ????????????)
	mbsTim->CNT = 0;             // ?????????? ??????? ???????
	mbsTim->CR1 |= TIM_CR1_CEN;  // ????????? ??????
} // mbs_RxInterrupt()



// ???????? ?????? ?? USART -----------------------------------------------------------------------
void mbs_TxInterrupt(void)
{	
//	// ???? ???????? ?????? ????, ??
//	// ???????? ??? ?????????? ? ???????? ????? (?????????:)
//	if(txCount == 0)
//	{
//		MBS_DIR_ON;
//		for(int i = 0; i < 8; i++) __NOP();
//	} // if
	
	// ????????? ????? ?????? ?????? ? USART
	if (txCount >= mbsTxLen)
	{
		// ???? ???????? ????????:		
		MBS_DIR_OFF;  // ????????? ??? ??????????
		txCount = 0;  // ?????????? ??????? ???????????? ??????
	} else
	{
		// ???? ???????? ?? ????????, ??...				
		mbsUart->DR = mbsTxBuf[txCount];  // ?????????? ????????? ????? ? ????? USART
		txCount++;                         // ??????????? ??????? ???????????? ??????
	} // if-else
} // mbs_TxInterrupt()
