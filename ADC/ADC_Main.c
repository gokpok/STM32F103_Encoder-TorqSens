
#include "ADC_Main.h"
#include "stdlib.h"

ADC_HandleTypeDef* Mhadc;
uint16_t* ADC_buf;
uint8_t ADC_len;

void ADC_Init(uint16_t* buf, uint8_t len, ADC_HandleTypeDef* hadc)
{
	
	// ���������� �������� ��������� ��� �����������
	Mhadc = hadc;
	
	// ��������� ����� ������� ��� ������ (���������� �������)
	ADC_len = len;

	// ��������� ������ �������� ������
	ADC_buf = buf;
	
	// ��������� ����� ���
	HAL_ADC_Start(Mhadc);
  HAL_Delay(1);

	// ���������� ���
	HAL_ADCEx_Calibration_Start(Mhadc);
	HAL_Delay(1);
	
	// ����� ��� � DMA
	HAL_ADC_Start_DMA(Mhadc, (uint32_t*) ADC_buf, len);
	
	// ��������� ������ ��� ������ ���
	//ADC_buf = (uint16_t*) malloc( len * sizeof(uint16_t) );
	
	
}

//void ADC_Start (void)
//{
//	
//	for(uint8_t i=0; i < ADC_len; i++)
//	{
//		// ����� ���������
//		HAL_ADC_Start(Mhadc);
//		
//		// �������� ���������� ��������� ������
//		HAL_ADC_PollForConversion(Mhadc,1);
//			
//	  // ��������� ������������� ��������
//		ADC_buf[i] = HAL_ADC_GetValue (Mhadc); 
//	}
//	
//}


