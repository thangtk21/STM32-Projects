#include "stm32f10x.h"                  // Device header
int main()
{
	//disable interrupt
	__disable_irq();
	
	//clock
	RCC->CR |= (1<<16)|(1<<24); // hse pll on
	RCC->CFGR |= 7<<18;//pll mul = 9
	RCC->CFGR |= 1<<16;//pll source hsi/2 or hse 
	RCC->CFGR |= 1<<2;//system clock switch -> pll selected				F = 72MHz
	
	//gpio config
	RCC->APB2ENR |= 1<<4;//gpioc enable
	GPIOC->CRH &= ~(0xf<<20);
	GPIOC->CRH |= 2<<20;//c13 output
	
	RCC->APB2ENR |= 1<<3;//gpiob enable
	GPIOB->CRH &= ~(0xf<<4);//clear 4 5 6 7
	
	GPIOB->CRH |= (1<<7);//pull up down pin 9
	GPIOB->ODR |= (1<<9);//pull up pin B9
	
	//AFIO config
	RCC->APB2ENR |= 1;//afio enable
	AFIO->EXTICR[2] = 1<<4;//[2]->8 to 11, B:0001, EXTI9[3:0]
	EXTI->IMR = 1<<9;//request line 9
	EXTI->FTSR = 1<<9;//falling edge
	
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	__enable_irq();
	
	while(1)
	{}
}
void EXTI9_5_IRQHandler ()
{
	if((EXTI->PR & (1<<9)) !=0)
	{
		EXTI->PR = 1<<9; // clear pending
		GPIOC->ODR ^= 1<<13;
	}
}