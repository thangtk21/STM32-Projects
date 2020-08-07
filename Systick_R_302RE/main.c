#include "stm32f3xx.h"                  // Device header
void RCC_Init()
{
	//enable pll and hse clock
	RCC->CR |= RCC_CR_PLLON|RCC_CR_HSEON;
	
	//wait stable
	while((RCC->CR & RCC_CR_PLLRDY) == 0||(RCC->CR & RCC_CR_HSERDY) == 0);		
	
	RCC->CFGR &= ~(0xf<<18);
	RCC->CFGR |= 7<<18;
	
	
}
int main()
{
	return 0;
}