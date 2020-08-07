#include "stm32f10x.h"                  // Device header
volatile uint16_t counter = 0;
uint8_t time_s = 0;
void RCC_Init()
{
	RCC->APB2ENR |= (1<<4);//gpioc
	RCC->CR |= (1<<16)|(1<<24);//hse on,pll on
	RCC->CFGR |= 7<<18; //PLL mul = 9
	RCC->CFGR |= 1<<16; //
	RCC->CFGR |= 1<<2; 
	RCC->CFGR |= 9<<4; // 72Mhz/4 = 18MHz
}

void SysTick_Init(uint32_t ticks)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = ticks - 1;
	SysTick->VAL = 0;
	SysTick->CTRL |= 7;
}
void SysTick_Handler()
{
	counter++;
}
	
int main()
{
	RCC_Init();
	SysTick_Init(36000);
	GPIOC->CRH |= (1<<21);
	while(1)
	{
		if(counter == 1000)
		{
			counter = 0;
			GPIOC->ODR ^= (1<<13);
			time_s++;
		}
	}
}	