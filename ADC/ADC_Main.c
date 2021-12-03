
#include "ADC_Main.h"
#include "stdlib.h"

ADC_HandleTypeDef* Mhadc;
uint16_t* ADC_buf;
uint8_t ADC_len;

void ADC_Init(uint16_t* buf, uint8_t len, ADC_HandleTypeDef* hadc)
{
	
	// Присвоение внешнего указателя АЦП внутреннему
	Mhadc = hadc;
	
	// Получение длины массива для опроса (количество опросов)
	ADC_len = len;

	// Получение адреса внешнего буфера
	ADC_buf = buf;
	
	// Начальный старт АЦП
	HAL_ADC_Start(Mhadc);
  HAL_Delay(1);

	// Калибровка АЦП
	HAL_ADCEx_Calibration_Start(Mhadc);
	HAL_Delay(1);
	
	// СТарт АЦП с DMA
	HAL_ADC_Start_DMA(Mhadc, (uint32_t*) ADC_buf, len);
	
	// Выделение памяти под массив АЦП
	//ADC_buf = (uint16_t*) malloc( len * sizeof(uint16_t) );
	
	
}

//void ADC_Start (void)
//{
//	
//	for(uint8_t i=0; i < ADC_len; i++)
//	{
//		// Старт оцифровки
//		HAL_ADC_Start(Mhadc);
//		
//		// Ожидание завершения оцифровки канала
//		HAL_ADC_PollForConversion(Mhadc,1);
//			
//	  // Получение оцифрованного значения
//		ADC_buf[i] = HAL_ADC_GetValue (Mhadc); 
//	}
//	
//}


