#include "stm32f3xx.h"                  // Device header

#define AHB2_BASEADD 0x48000000U
#define GPIOB_ADDR (AHB2_BASEADD + 0x0400)
#define GPIOB_ODR (GPIOB_ADDR)

uint32_t *p = (uint32_t*)GPIOB_ODR;
void delay()
{
	for(int i = 0;i<500000;i++)
	{}
}


int main()
{
	//enable gpiob
	RCC->AHBENR |= 1<<18;
	
	//gpio B 12 is output
	GPIOB->MODER = 1<<24;
	
	while(1)
	{
		//GPIOB->ODR ^= 1<<12;
		*(p+5)^= (1<<12);
		delay();
		
	}		
	
}