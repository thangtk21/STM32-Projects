#include "stm32f10x.h"                  // Device header
uint8_t time_s = 0;
uint16_t timing = 0;


void RCC_Init()
{
	RCC->APB2ENR |= (1<<4);//gpioc
	RCC->CR |= (1<<16)|(1<<24);//hse on,pll on
	RCC->CFGR |= 7<<18; //PLL mul = 9
	RCC->CFGR |= 1<<16; //
	RCC->CFGR |= 1<<2; 
}

//void SysTick_Init(uint32_t ticks)
//{
//	SysTick->CTRL = 0;
//	SysTick->LOAD = ticks - 1;
//	SysTick->VAL = 0;
//	SysTick->CTRL |= 7;
//}
//void SysTick_Handler()
//{
//	counter++;
//}

void Delay(uint16_t time_ms)
{
	timing = 0;
	while(timing<time_ms);
}
void SysTick_Handler()
{
	timing++;
}



int main()
{
	RCC_Init();
	//SysTick->CTRL |= 1<<2;// clock core, = 0 => clock/8
	SysTick->LOAD = 8999;
	GPIOC->CRH |= (1<<21);// c13 output
	
	SysTick->CTRL |= SysTick_CTRL_TICKINT|SysTick_CTRL_ENABLE;
	
	while(1)
	{
		
		GPIOC->ODR ^= (1<<13);
		Delay(7);
	}
}	