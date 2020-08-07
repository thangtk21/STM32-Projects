#include "stm32f1_gpio.h"


/*
Init and DeInit
*/
void GPIO_Init(GPIO_Handle_struct *pGPIO_Handle)
{
	//1.Config Mode
	uint32_t temp = 0;
	if(pGPIO_Handle->GPIO_PinConfig.Mode < 16)
	{
		if(pGPIO_Handle->GPIO_PinConfig.Pin < 8)
		{
			temp = (pGPIO_Handle->GPIO_PinConfig.Mode << (4*pGPIO_Handle->GPIO_PinConfig.Pin));
			pGPIO_Handle->pGPIO->CR[0] = (pGPIO_Handle->pGPIO->CR[0]&~(0xF<<(4*pGPIO_Handle->GPIO_PinConfig.Pin)))|temp;
		}
		else
		{
			temp = (pGPIO_Handle->GPIO_PinConfig.Mode << (4*(pGPIO_Handle->GPIO_PinConfig.Pin-8)));
			pGPIO_Handle->pGPIO->CR[1] = (pGPIO_Handle->pGPIO->CR[1]&~(0xF<<(4*(pGPIO_Handle->GPIO_PinConfig.Pin-8))))|temp;
		}
	}
	else
	{
		if(pGPIO_Handle->GPIO_PinConfig.Mode == GPIO_MODE_IT_FALLING)
		{
			//1. Falling Config = set bit falling and clear bit rising
			EXTI->FTSR |= (1<<pGPIO_Handle->GPIO_PinConfig.Pin);
			EXTI->RTSR &= ~(1<<pGPIO_Handle->GPIO_PinConfig.Pin);
		}else if(pGPIO_Handle->GPIO_PinConfig.Mode == GPIO_MODE_IT_RISING)
		{
			//1. Rising Config	
			EXTI->RTSR |= (1<<pGPIO_Handle->GPIO_PinConfig.Pin);
			EXTI->FTSR &= ~(1<<pGPIO_Handle->GPIO_PinConfig.Pin);
		}else if(pGPIO_Handle->GPIO_PinConfig.Mode == GPIO_MODE_IT_RISING_AND_FALLING)
		{
			//1. Both of them Config			
			EXTI->RTSR |= (1<<pGPIO_Handle->GPIO_PinConfig.Pin);
			EXTI->FTSR |= (1<<pGPIO_Handle->GPIO_PinConfig.Pin);
		}
		//2. Config GPIO Port
		uint8_t temp1 = pGPIO_Handle->GPIO_PinConfig.Pin/4;
		uint8_t temp2 = pGPIO_Handle->GPIO_PinConfig.Pin%4;
		
		uint8_t portcode = GPIO_ADD_TO_CODE(pGPIO_Handle->pGPIO);
		AFIO_CLK_EN();
		AFIO->EXTICR[temp1] = portcode << (4*temp2); 
		
		
		//3. enable Delivery
		EXTI->IMR |= (1<<pGPIO_Handle->GPIO_PinConfig.Pin);
		
	}
	//2.Config Pull
	temp = 0;
	if(pGPIO_Handle->GPIO_PinConfig.Pull == GPIO_PULLUP)
	{
		pGPIO_Handle->pGPIO->ODR |= (1<<pGPIO_Handle->GPIO_PinConfig.Pin);
	}
	else
	{
		pGPIO_Handle->pGPIO->ODR &= ~(1<<pGPIO_Handle->GPIO_PinConfig.Pin);
	}
}
void GPIO_DeInit(GPIO_struct *pGPIO)
{
	if(pGPIO == GPIOA)
	{
		GPIOA_REG_RESET();
	}else if(pGPIO == GPIOB)
	{
		GPIOB_REG_RESET();
	}else if(pGPIO == GPIOC)
	{
		GPIOC_REG_RESET();
	}else if(pGPIO == GPIOD)
	{
		GPIOD_REG_RESET();
	}else if(pGPIO == GPIOE)
	{
		GPIOE_REG_RESET();
	}else if(pGPIO == GPIOF)
	{
		GPIOF_REG_RESET();
	}else if(pGPIO == GPIOG)
	{
		GPIOG_REG_RESET();
	}
}


/*
	Read and Write
*/
uint8_t GPIO_ReadPin(GPIO_struct *pGPIO,uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIO->IDR >> PinNumber) & 0x00000001);
	return value;
}
uint16_t GPIO_ReadPort(GPIO_struct *pGPIO);
void GPIO_WritePin(GPIO_struct *pGPIO,uint8_t PinNumber,uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		pGPIO->ODR |= (1<<PinNumber);
	}
	else
	{
		pGPIO->ODR &=~(1<<PinNumber);
	}
}
void GPIO_WritePort(GPIO_struct *pGPIO,uint16_t Value);
void GPIO_TogglePin(GPIO_struct *pGPIO,uint8_t PinNumber)
{
	pGPIO->ODR ^= (1<<PinNumber);
}

/*
IRQ Config and ISR handling
*/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t En_Or_Dis)
{
	//1. enable and disable irq number
	if(En_Or_Dis == ENABLE)
	{
		if(IRQNumber < 32)
		{
			*NVIC_ISER0 |= (1<<IRQNumber);
		}
		else if(IRQNumber >= 32 && IRQNumber < 64)
		{
			*NVIC_ISER1 |= (1<<(IRQNumber%32));
		}
		
	}
	else
	{
		if(IRQNumber < 32)
		{
			*NVIC_ICER0 |= (1<<IRQNumber);
		}
		else if(IRQNumber >= 32 && IRQNumber < 64)
		{
			*NVIC_ICER1 |= (1<<(IRQNumber%32));
		}
	}
	
}
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	uint8_t IPRX = IRQNumber / 4;
	uint8_t IPRX_seg = IRQNumber % 4;
	
	*(NVIC_IPR + IPRX) |= (IRQPriority<<(8*IPRX_seg))<<4; 
}
void GPIO_IRQHandling(uint8_t PinNumber)
{
	//if have interrupt
	if((EXTI->PR & (1<<PinNumber)) != 0)
	{
		//clear bit pending
		EXTI->PR |= 1<<PinNumber;
	}
}