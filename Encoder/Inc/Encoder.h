

#include "main.h"


void Encoder_Init(uint16_t EncDigit, uint16_t ZeroCnt, TIM_HandleTypeDef* htim_m, TIM_HandleTypeDef* htim_h);   //Функция инициализации энкодера
void Encoder_IRQ(void);												//Функция для обработки прерываний таймера энкодера(!)

extern volatile int16_t En_Ticks;																														//Количество тиков (фронтов) энкодера (в 4 раза больше кол-ва импульсов)
extern float AbsTime;																																					//Абсолютное время, за к-е проводится измерение кол-ва тиков энкодера





