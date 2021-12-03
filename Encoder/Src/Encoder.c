#include "Encoder.h"
#include "math.h"

TIM_HandleTypeDef* Mhtim;
TIM_HandleTypeDef* Hhtim;

float Tcnt = 0;
float AbsTime = 0;
uint16_t ZeroCnt = 0;


volatile int16_t En_Ticks = 0;

void Encoder_Init(uint16_t EncDigit, uint16_t Zero_Cnt, TIM_HandleTypeDef* htim_m, TIM_HandleTypeDef* htim_h)
{
	// ������������� ������ � ���������
	
	// EncDigit - ����������� �������� �� ������
	// htim_m   - ��������� �� ��������� ������� ��������
	// htim_h   - ��������� �� ��������� ������� ����������� ��������
	// Zero_Cnt - �������� ���� �������� (��� ����������� ����������� ��������)
	
	//����������� ���� ��������
	ZeroCnt = Zero_Cnt;
	
	//���������� ������������ ������� ��� �������
	uint16_t div = 0;
	
	//��������� ������� ������� ��������
	Mhtim = htim_m;
		
	//��������� ������� ������� ��������� ��������
	Hhtim = htim_h;
	
	//������ ���������� ����� ������� ��� ����������� �������, ������������ ��� ������� 2 (2.0F) ���������
	//�������� ��� �������� ���� 1��/��� (60.0F � ���.) ��� �������� ���������� �������� (EncDigit) �� ������
	Tcnt = (((2.0F * 60.0F) / EncDigit) * HAL_RCC_GetSysClockFreq());
	
	//���� ���������� ����� ��������� ������� ������������ �������, �� ���� ����������� ������������ div
	if (Tcnt > 65536)
	{
		uint16_t i = 0;
		do
		{
			i++;
		}
		while (!(((uint32_t)HAL_RCC_GetSysClockFreq() % i) == 0 && (Tcnt / i) < 65536)); //���������� ����� ����� ������������ ������ ���� ����� � ������ 65536
		
		div = i - 1;
		Tcnt = ceil(Tcnt / i);
		AbsTime = Tcnt / (float)(HAL_RCC_GetSysClockFreq() / (float)i);									 // ����� (�), ��������� �� ���������� ������� ��������� ��������
	}
		
	// ������������� ������� ��������� ��������
	__HAL_TIM_SET_PRESCALER(Hhtim,div);
	__HAL_TIM_SET_AUTORELOAD(Hhtim,Tcnt);
		
	
	// ������������� ������� ��������
	__HAL_TIM_SET_PRESCALER(Mhtim,0);
	__HAL_TIM_SET_AUTORELOAD(Mhtim,2U * ZeroCnt);
	
	// ������ ������� ��������
	HAL_TIM_Encoder_Start(Mhtim,TIM_CHANNEL_ALL);
	
	//������ ���������� ������� ��������� �������� � ������ �������
	__HAL_TIM_ENABLE_IT(Hhtim,TIM_IT_UPDATE);
	__HAL_TIM_ENABLE(Hhtim);
	
	
	//��������� ������� �������������
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//	HAL_Delay(500);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}


void Encoder_IRQ(void)
{
	//��������� ���������� ������� ��������� ��������
	
	// Mhtim   - ��������� �� ��������� ������� ��������
	// Hhtim   - ��������� �� ��������� ������� ��������� ��������
	
	//��������� ���������� ����� ��������
	 
	En_Ticks = __HAL_TIM_GET_COUNTER(Mhtim) - ZeroCnt;
	
	//����� �������� ������� ��������
	__HAL_TIM_SET_COUNTER(Mhtim,ZeroCnt);	
	
	//����� ���������� ������� ��������� ��������
	__HAL_TIM_CLEAR_IT(Hhtim, TIM_IT_UPDATE);
	
}

