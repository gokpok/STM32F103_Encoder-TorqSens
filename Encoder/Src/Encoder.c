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
	// Инициализация работы с энкодером
	
	// EncDigit - разрядность энкодера на оборот
	// htim_m   - указатель на структуру таймера энкодера
	// htim_h   - указатель на структуру таймера обработчика энкодера
	// Zero_Cnt - условный ноль энкодера (для определения направления вращения)
	
	//Определение ноля энкодера
	ZeroCnt = Zero_Cnt;
	
	//Объявление предделителя таймера для расчета
	uint16_t div = 0;
	
	//Получение адресса таймера энкодера
	Mhtim = htim_m;
		
	//Получение адресса таймера обработки энкодера
	Hhtim = htim_h;
	
	//Расчет количества тиков таймера для обеспечения времени, достаточного для захвата 2 (2.0F) импульсов
	//энкодера при скорости вала 1об/мин (60.0F в сек.) при заданном разрешение энкодера (EncDigit) на оборот
	Tcnt = (((2.0F * 60.0F) / EncDigit) * HAL_RCC_GetSysClockFreq());
	
	//Если количество тиков превышает регистр перезагрузки таймера, то ищем достаточный предделитель div
	if (Tcnt > 65536)
	{
		uint16_t i = 0;
		do
		{
			i++;
		}
		while (!(((uint32_t)HAL_RCC_GetSysClockFreq() % i) == 0 && (Tcnt / i) < 65536)); //Количество тиков после предделителя должно быть целым и меньше 65536
		
		div = i - 1;
		Tcnt = ceil(Tcnt / i);
		AbsTime = Tcnt / (float)(HAL_RCC_GetSysClockFreq() / (float)i);									 // Время (с), требуемое на заполнение таймера обработки энкодера
	}
		
	// Инициализация таймера обработки энкодера
	__HAL_TIM_SET_PRESCALER(Hhtim,div);
	__HAL_TIM_SET_AUTORELOAD(Hhtim,Tcnt);
		
	
	// Инициализация таймера энкодера
	__HAL_TIM_SET_PRESCALER(Mhtim,0);
	__HAL_TIM_SET_AUTORELOAD(Mhtim,2U * ZeroCnt);
	
	// Запуск таймера энкодера
	HAL_TIM_Encoder_Start(Mhtim,TIM_CHANNEL_ALL);
	
	//Запуск прерываний таймера обработки энкодера и самого таймера
	__HAL_TIM_ENABLE_IT(Hhtim,TIM_IT_UPDATE);
	__HAL_TIM_ENABLE(Hhtim);
	
	
	//Индикация удачной инициализации
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//	HAL_Delay(500);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}


void Encoder_IRQ(void)
{
	//Обработка прерываний таймера обработки энкодера
	
	// Mhtim   - указатель на структуру таймера энкодера
	// Hhtim   - указатель на структуру таймера обработки энкодера
	
	//Получение количества тиков энкодера
	 
	En_Ticks = __HAL_TIM_GET_COUNTER(Mhtim) - ZeroCnt;
	
	//Сброс счетчика таймера энкодера
	__HAL_TIM_SET_COUNTER(Mhtim,ZeroCnt);	
	
	//Сброс прерывания таймера обработки энкодера
	__HAL_TIM_CLEAR_IT(Hhtim, TIM_IT_UPDATE);
	
}

