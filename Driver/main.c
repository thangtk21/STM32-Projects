#include "stm32f1_gpio.h"


void delay()
{
	for(uint32_t i = 0;i<500000;i++);
}
int main()
{
	
	GPIOC_CLK_EN();
	GPIOA_CLK_EN();
	
	GPIO_Handle_struct gpio;
	
	gpio.pGPIO = GPIOC;
	gpio.GPIO_PinConfig.Mode = GPIO_MODE_OUTPUT_PP_HIGH;
	gpio.GPIO_PinConfig.Pin = GPIO_PIN_13;
	GPIO_Init(&gpio);
	
	
	gpio.pGPIO = GPIOA;
	gpio.GPIO_PinConfig.Mode = GPIO_MODE_IT_FALLING;
	gpio.GPIO_PinConfig.Pin = GPIO_PIN_9;
	gpio.GPIO_PinConfig.Pull = GPIO_PULLUP;
	GPIO_Init(&gpio);
	
	GPIO_IRQPriorityConfig(IRQ_NUMBER_EXTI9_5,NVIC_IRQ_PRIORITY_15);
	GPIO_IRQInterruptConfig(IRQ_NUMBER_EXTI9_5,ENABLE);
	
	while(1)
	{
		
	}
	return 0;
} 

void EXTI9_5_IRQHandler()
{
	GPIO_IRQHandling(9);
	GPIO_TogglePin(GPIOC,13);
}