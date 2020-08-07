#include "stm32f10x.h"                  // Device header
#include "string.h"
#include "stdio.h"
void delay()
{
	for(uint32_t i = 0;i<500000;i++){}
}

void SystemClock_Init()
{
	RCC->CSR |= RCC_CR_HSEON|RCC_CR_PLLON;
	while((RCC->CR & RCC_CR_HSERDY) == 0);
	while((RCC->CR & RCC_CR_PLLRDY) == 0);
	
	RCC->CFGR |= RCC_CFGR_PLLMULL9;
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
}

/*
USART1
Baudrate: 9600 Kbps
Parity: None
Stop bit: 1
Data Length = 8
*/
void USART_Init()
{
	//on gpiob
	//on usart1
	//on afio
	
	RCC->APB2ENR |= (1<<14);
	RCC->APB2ENR |= (1<<3);
	RCC->APB2ENR |= (1<<0);

	//remap
	AFIO->MAPR |= (1<<2);
	
	//pin setup
	//pb 6 is af_pp
	GPIOB->CRL |= GPIO_CRL_MODE6_0;
	GPIOB->CRL |= GPIO_CRL_CNF6_1;
	
	//pb7 input floating
	
	//enable usart1, tx, rx
	USART1->CR1 |= USART_CR1_UE|USART_CR1_TE|USART_CR1_RE;
	
	//enable interrupt rx
	USART1->CR1 |= USART_CR1_RXNEIE;
	
	//baudrate 9600
	USART1->BRR = 0x1d4c;
	//parity none
	
	//stopbit 1
	
	//data length 8
	
	
	
}
uint8_t USART1_Transmit(uint8_t *data_send, uint8_t length)
{
	uint8_t *p = data_send;
	for(uint8_t i = 0;i<length;i++)
	{
		while((USART1->SR & (1<<7)) == 0); /* wait empty*/
		USART1->DR = *(p+i);
		while((USART1->SR & (1<<6)) == 0); /* wait transmit completed */
	}
}

uint8_t  *a = "Tran Minh Thang\n",i = 0,len;
uint8_t str[20];
volatile uint8_t j = 0;

volatile uint8_t buf_rx[20];
int main()
{
	SystemClock_Init();
	USART_Init();
	NVIC_EnableIRQ(USART1_IRQn);
	while(1)
	{
//		sprintf(str,"%d %s",i,a);
//		USART1_Transmit(str,strlen(str));
//		i++;
//		len = strlen(str);
//		delay();
//		delay();
//		delay();
	}
	
}

void USART1_IRQHandler()
{
	if(USART1->SR & USART_SR_RXNE) /* if can read data */
	{
		buf_rx[j] = USART1->DR;
		j++;
		if(j == 20) j = 0;
	}
}