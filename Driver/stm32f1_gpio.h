#include "stm32f1.h"

#define GPIO_MODE_ANALOG								0			
#define GPIO_MODE_INPUT_FLOATING				4					
#define GPIO_MODE_INPUT_PULL						8																
#define GPIO_MODE_OUTPUT_PP_LOW					2
#define GPIO_MODE_OUTPUT_PP_HIGH				1
#define GPIO_MODE_OUTPUT_PP_VERYHIGH		3
#define GPIO_MODE_OUTPUT_OD_LOW					6
#define GPIO_MODE_OUTPUT_OD_HIGH				5
#define GPIO_MODE_OUTPUT_OD_VERYHIGH		7
#define GPIO_MODE_AF_PP_LOW							10
#define GPIO_MODE_AF_PP_HIGH						9
#define GPIO_MODE_AF_PP_VERYHIGH				11
#define GPIO_MODE_AF_OD_LOW							14
#define GPIO_MODE_AF_OD_HIGH						13
#define GPIO_MODE_AF_OD_VERYHIGH				15

#define GPIO_MODE_IT_FALLING						16
#define GPIO_MODE_IT_RISING							17
#define GPIO_MODE_IT_RISING_AND_FALLING	18

#define GPIO_PULLUP											1
#define GPIO_PULLDOWN										0

#define GPIO_PIN_0											0
#define GPIO_PIN_1											1
#define GPIO_PIN_2											2
#define GPIO_PIN_3											3
#define GPIO_PIN_4											4
#define GPIO_PIN_5											5
#define GPIO_PIN_6											6
#define GPIO_PIN_7											7
#define GPIO_PIN_8											8
#define GPIO_PIN_9											9
#define GPIO_PIN_10											10
#define GPIO_PIN_11											11
#define GPIO_PIN_12											12
#define GPIO_PIN_13											13
#define GPIO_PIN_14											14
#define GPIO_PIN_15											15




typedef struct
{
	uint8_t Pin;
	uint8_t Mode;
	uint8_t Pull;
}GPIO_PinConfig_struct;

typedef struct
{
	GPIO_struct *pGPIO; 											/*Keep address GPIO base*/
	GPIO_PinConfig_struct GPIO_PinConfig;			/*GPIO Config Settting*/
}GPIO_Handle_struct;

/*
Init and DeInit
*/
void GPIO_Init(GPIO_Handle_struct *pGPIO_Handle);
void GPIO_DeInit(GPIO_struct *pGPIO);

/*
	Read and Write
*/
uint8_t GPIO_ReadPin(GPIO_struct *pGPIO,uint8_t PinNumber);
uint16_t GPIO_ReadPort(GPIO_struct *pGPIO);
void GPIO_WritePin(GPIO_struct *pGPIO,uint8_t PinNumber,uint8_t Value);
void GPIO_WritePort(GPIO_struct *pGPIO,uint16_t Value);
void GPIO_TogglePin(GPIO_struct *pGPIO,uint8_t PinNumber);

/*
IRQ Config and ISR handling
*/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t En_Or_Dis);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);