
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2020 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "dwt_delay.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
Lcd_PortType ports[] = {D4_GPIO_Port, D5_GPIO_Port, D6_GPIO_Port, D7_GPIO_Port};
Lcd_PinType pins[] = {D4_Pin, D5_Pin, D6_Pin, D7_Pin};
Lcd_HandleTypeDef lcd;

enum BIT
{
	LOW,
	HIGH
};
uint8_t lcd_col = 1,lcd_row = 1;
uint8_t key,key_last;
char key_str[2];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void ShiftBit(enum BIT bit)
{
	HAL_GPIO_WritePin(data_74hc164_GPIO_Port,data_74hc164_Pin,(GPIO_PinState)bit);
	DWT_Delay(5);
	HAL_GPIO_WritePin(clock_74hc164_GPIO_Port,clock_74hc164_Pin,1);
	DWT_Delay(5);
	HAL_GPIO_WritePin(clock_74hc164_GPIO_Port,clock_74hc164_Pin,0);
	DWT_Delay(5);
}
void ShiftByte(uint8_t byte)
{
	uint8_t i,bit;
	for(i = 7;i!=255;i--)
	{
		bit = byte & (1<<i);
		if(bit)
			ShiftBit(1);
		else
			ShiftBit(0);
	}
}
uint8_t GetKeyPad()
{
	ShiftByte(0xff);
	
	ShiftBit(0);
	if(HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin));
		return '1';
	}
	if(HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin));
		return '7';
	}
	
	ShiftBit(1);
	if(HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin));
		return '2';
	}
	if(HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin));
		return '8';
	}
	
	ShiftBit(1);
	if(HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin));
		return '3';
	}
	if(HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin));
		return '9';
	}
	
	ShiftBit(1);
	if(HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin));
		return 'X';
	}
	if(HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin));
		return 'v';
	}
	
	ShiftBit(1);
	if(HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin));
		return '4';
	}
	if(HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin));
		return '<';
	}
	
	ShiftBit(1);
	if(HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin));
		return '5';
	}
	if(HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin));
		return '0';
	}
	
	ShiftBit(1);
	if(HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin));
		return '6';
	}
	if(HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin));
		return '>';
	}
	
	ShiftBit(1);
	if(HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R1_GPIO_Port,R1_Pin));
		return '^';
	}
	if(HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin) == 0)
	{
		while(!HAL_GPIO_ReadPin(R2_GPIO_Port,R2_Pin));
		return 'O';
	}
	
	return 1;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
	lcd = Lcd_create(ports, pins, RS_GPIO_Port, RS_Pin, EN_GPIO_Port, EN_Pin, LCD_4_BIT_MODE);
	Lcd_clear(&lcd);
	DWT_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		key = GetKeyPad();
		if(key != 1)
		{
			key_last = key;
			Lcd_cursor(&lcd,lcd_row,lcd_col);
			sprintf(key_str,"%c",(char)key);
			Lcd_string(&lcd,key_str);
			lcd_col++;
			if(lcd_col == 17)
			{
				lcd_col = 1;
				lcd_row++;
				if(lcd_row == 3)
					lcd_row = 1;
			}
		}
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(clock_74hc164_GPIO_Port, clock_74hc164_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, data_74hc164_Pin|RS_Pin|EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D4_Pin|D5_Pin|D6_Pin|D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : clock_74hc164_Pin */
  GPIO_InitStruct.Pin = clock_74hc164_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(clock_74hc164_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : data_74hc164_Pin RS_Pin EN_Pin */
  GPIO_InitStruct.Pin = data_74hc164_Pin|RS_Pin|EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : R1_Pin R2_Pin */
  GPIO_InitStruct.Pin = R1_Pin|R2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D4_Pin D5_Pin D6_Pin D7_Pin */
  GPIO_InitStruct.Pin = D4_Pin|D5_Pin|D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
