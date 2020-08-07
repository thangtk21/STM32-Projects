#include "stm32f10x.h"                  // Device header
uint16_t counter = 0;
int main()
{
	//disable interrupt
	__disable_irq();
	
	//clock
	RCC->CR |= (1<<16)|(1<<24); // hse pll on
	RCC->CFGR |= 7<<18;//pll mul = 9
	RCC->CFGR |= 1<<16;//pll source hsi/2 or hse
	RCC->CFGR |= 1<<2;//system clock switch -> pll selected
	
	//gpio config
	RCC->APB2ENR |= 1<<4;//gpioc enable
	GPIOC->CRH |= 1<<21;//c13 output
	
	//timer 2 config
	RCC->APB1ENR |= 1; //timer 2 enable
	TIM2->PSC = 7199;// 72000000/7200 = 10KHz 
	TIM2->ARR = 9;//10KHz/10 = 1KHz -> T = 1ms
	TIM2->CNT = 0;
	TIM2->CR1 |= 1; //counter enable
	TIM2->DIER |= 1; //update interrupt enable
	
	//enable NVIC and interrupt system
	NVIC_EnableIRQ(TIM2_IRQn);
	__enable_irq();
	
	while(1)
	{
		
	}
}

void TIM2_IRQHandler()
{
	TIM2->SR = 0;
	counter++;
	if(counter == 4)
	{
		GPIOC->ODR ^= (1<<13);
		counter = 0;
	}
	
}