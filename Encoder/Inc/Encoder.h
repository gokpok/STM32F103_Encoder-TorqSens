

#include "main.h"


void Encoder_Init(uint16_t EncDigit, uint16_t ZeroCnt, TIM_HandleTypeDef* htim_m, TIM_HandleTypeDef* htim_h);   //������� ������������� ��������
void Encoder_IRQ(void);												//������� ��� ��������� ���������� ������� ��������(!)

extern volatile int16_t En_Ticks;																														//���������� ����� (�������) �������� (� 4 ���� ������ ���-�� ���������)
extern float AbsTime;																																					//���������� �����, �� �-� ���������� ��������� ���-�� ����� ��������





