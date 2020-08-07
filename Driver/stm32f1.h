#include <stdint.h>

#define __IO						volatile

/*
Macro NVIC
*/
#define NVIC_ISER0			((__IO uint32_t*)0xE000E100)
#define NVIC_ISER1			((__IO uint32_t*)0xE000E104)


#define NVIC_ICER0			((__IO uint32_t*)0xE000E180)
#define NVIC_ICER1			((__IO uint32_t*)0xE000E184)


#define NVIC_IPR				((__IO uint32_t*)0xE000E400)
/*
Macro memory address
*/
#define FLASH_ADD 			0x80000000U
#define SRAM_ADD 				0x20000000U

/*
Macro bus address
*/
#define AHB_ADD					0x40020000U
#define APB1_ADD				0x40000000U
#define APB2_ADD				0x40010000U


/*
Macro peripheral address
*/
#define GPIOA_ADD				(APB2_ADD+0x0800)
#define GPIOB_ADD				(APB2_ADD+0x0C00)
#define GPIOC_ADD				(APB2_ADD+0x1000)
#define GPIOD_ADD				(APB2_ADD+0x1400)
#define GPIOE_ADD				(APB2_ADD+0x1800)
#define GPIOF_ADD				(APB2_ADD+0x1C00)
#define GPIOG_ADD				(APB2_ADD+0x2000)

#define RCC_ADD					(AHB_ADD+0x1000)

#define EXTI_ADD				(APB2_ADD+0x0400)

#define AFIO_ADD				APB2_ADD
typedef struct
{
	__IO uint32_t CR[2];
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t BRR;
	__IO uint32_t LCKR;
}GPIO_struct;

typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t CFGR;
	__IO uint32_t CIR;
	__IO uint32_t APB2RSTR;
	__IO uint32_t APB1RSTR;
	__IO uint32_t AHBENR;
	__IO uint32_t APB2ENR;
	__IO uint32_t APB1ENR;
	__IO uint32_t BDCR;
	__IO uint32_t CSR;
}RCC_struct;

typedef struct
{
	__IO uint32_t IMR;
	__IO uint32_t EMR;
	__IO uint32_t RTSR;
	__IO uint32_t FTSR;
	__IO uint32_t SWIER;
	__IO uint32_t PR;
}EXTI_struct;

typedef struct
{
	__IO uint32_t EVCR;
	__IO uint32_t MAPR;
	__IO uint32_t EXTICR[4];
	__IO uint32_t MAPR2;
}AFIO_struct;

#define GPIOA 					((GPIO_struct*)GPIOA_ADD)
#define GPIOB 					((GPIO_struct*)GPIOB_ADD)
#define GPIOC 					((GPIO_struct*)GPIOC_ADD)
#define GPIOD 					((GPIO_struct*)GPIOD_ADD)
#define GPIOE 					((GPIO_struct*)GPIOE_ADD)
#define GPIOF 					((GPIO_struct*)GPIOF_ADD)
#define GPIOG 					((GPIO_struct*)GPIOG_ADD)

#define RCC							((RCC_struct*)RCC_ADD)

#define EXTI						((EXTI_struct*)EXTI_ADD)

#define AFIO						((AFIO_struct*)AFIO_ADD)

#define GPIOA_CLK_EN()	(RCC->APB2ENR |= (1<<2))
#define GPIOB_CLK_EN()	(RCC->APB2ENR |= (1<<3))
#define GPIOC_CLK_EN()	(RCC->APB2ENR |= (1<<4))
#define GPIOD_CLK_EN()	(RCC->APB2ENR |= (1<<5))
#define GPIOE_CLK_EN()	(RCC->APB2ENR |= (1<<6))
#define GPIOF_CLK_EN()	(RCC->APB2ENR |= (1<<7))
#define GPIOG_CLK_EN()	(RCC->APB2ENR |= (1<<8))

#define GPIOA_CLK_DI()	(RCC->APB2ENR &= ~(1<<2))
#define GPIOB_CLK_DI()	(RCC->APB2ENR &= ~(1<<3))
#define GPIOC_CLK_DI()	(RCC->APB2ENR &= ~(1<<4))
#define GPIOD_CLK_DI()	(RCC->APB2ENR &= ~(1<<5))
#define GPIOE_CLK_DI()	(RCC->APB2ENR &= ~(1<<6))
#define GPIOF_CLK_DI()	(RCC->APB2ENR &= ~(1<<7))
#define GPIOG_CLK_DI()	(RCC->APB2ENR &= ~(1<<8))

#define GPIOA_REG_RESET()	do{RCC->APB2RSTR |= (1<<2);RCC->APB2RSTR &= ~(1<<2);}while(0)
#define GPIOB_REG_RESET()	do{RCC->APB2RSTR |= (1<<3);RCC->APB2RSTR &= ~(1<<3);}while(0)
#define GPIOC_REG_RESET()	do{RCC->APB2RSTR |= (1<<4);RCC->APB2RSTR &= ~(1<<4);}while(0)
#define GPIOD_REG_RESET()	do{RCC->APB2RSTR |= (1<<5);RCC->APB2RSTR &= ~(1<<5);}while(0)
#define GPIOE_REG_RESET()	do{RCC->APB2RSTR |= (1<<6);RCC->APB2RSTR &= ~(1<<6);}while(0)
#define GPIOF_REG_RESET()	do{RCC->APB2RSTR |= (1<<7);RCC->APB2RSTR &= ~(1<<7);}while(0)
#define GPIOG_REG_RESET()	do{RCC->APB2RSTR |= (1<<8);RCC->APB2RSTR &= ~(1<<8);}while(0)

#define AFIO_CLK_EN()		(RCC->APB2ENR |= (1<<0))

#define ENABLE 					1
#define DISABLE 				0
#define SET 						ENABLE
#define RESET 					DISABLE
#define GPIO_PIN_SET		SET
#define GPIo_PIN_RESET	RESET

#define GPIO_ADD_TO_CODE(port) 				((port == GPIOA)?0:\
																			(port == GPIOB)?1:\
																			(port == GPIOC)?2:\
																			(port == GPIOD)?3:\
																			(port == GPIOE)?4:\
																			(port == GPIOF)?5:6)
																			
#define IRQ_NUMBER_EXTI0					6
#define IRQ_NUMBER_EXTI1					7
#define IRQ_NUMBER_EXTI2					8
#define IRQ_NUMBER_EXTI3					9
#define IRQ_NUMBER_EXTI4					10
#define IRQ_NUMBER_EXTI9_5				23
#define IRQ_NUMBER_EXTI15_10			40

#define NVIC_IRQ_PRIORITY_0				0
#define NVIC_IRQ_PRIORITY_1				1
#define NVIC_IRQ_PRIORITY_2				2
#define NVIC_IRQ_PRIORITY_3				3
#define NVIC_IRQ_PRIORITY_4				4
#define NVIC_IRQ_PRIORITY_5				5
#define NVIC_IRQ_PRIORITY_6				6
#define NVIC_IRQ_PRIORITY_7				7
#define NVIC_IRQ_PRIORITY_8				8
#define NVIC_IRQ_PRIORITY_9				9
#define NVIC_IRQ_PRIORITY_10			10
#define NVIC_IRQ_PRIORITY_11			11
#define NVIC_IRQ_PRIORITY_12			12
#define NVIC_IRQ_PRIORITY_13			13
#define NVIC_IRQ_PRIORITY_14			14
#define NVIC_IRQ_PRIORITY_15			15

