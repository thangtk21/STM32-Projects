
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
#include "stdio.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

Lcd_PortType ports[] = {D4_GPIO_Port, D5_GPIO_Port, D6_GPIO_Port, D7_GPIO_Port};
Lcd_PinType pins[] = {D4_Pin, D5_Pin, D6_Pin, D7_Pin};
uint8_t key = 0;
uint8_t keypad[4][4] = 
{
	{'1','2','3','/'},
	{'4','5','6','*'},
	{'7','8','9','-'},
	{'#','0','=','+'}
};

char str[2];
uint8_t lcd_col = 1, lcd_row = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

uint8_t GetKeyPad()
{
	HAL_GPIO_WritePin(col1_GPIO_Port,col1_Pin,1);
	HAL_GPIO_WritePin(col2_GPIO_Port,col2_Pin,1);
	HAL_GPIO_WritePin(col3_GPIO_Port,col3_Pin,1);
	HAL_GPIO_WritePin(col3_GPIO_Port,col4_Pin,1);
	
	HAL_GPIO_WritePin(col1_GPIO_Port,col1_Pin,0);
	if(HAL_GPIO_ReadPin(row1_GPIO_Port,row1_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row1_GPIO_Port,row1_Pin) == 0);
		return keypad[0][0];
	}
	if(HAL_GPIO_ReadPin(row2_GPIO_Port,row2_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row2_GPIO_Port,row2_Pin) == 0);
		return keypad[1][0];
	}
	if(HAL_GPIO_ReadPin(row3_GPIO_Port,row3_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row3_GPIO_Port,row3_Pin) == 0);
		return keypad[2][0];
	}
	if(HAL_GPIO_ReadPin(row4_GPIO_Port,row4_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row4_GPIO_Port,row4_Pin) == 0);
		return keypad[3][0];
	}
	
	HAL_GPIO_WritePin(col2_GPIO_Port,col2_Pin,0);
	if(HAL_GPIO_ReadPin(row1_GPIO_Port,row1_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row1_GPIO_Port,row1_Pin) == 0);
		return keypad[0][1];
	}
	if(HAL_GPIO_ReadPin(row2_GPIO_Port,row2_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row2_GPIO_Port,row2_Pin) == 0);
		return keypad[1][1];
	}
	if(HAL_GPIO_ReadPin(row3_GPIO_Port,row3_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row3_GPIO_Port,row3_Pin) == 0);
		return keypad[2][1];
	}
	if(HAL_GPIO_ReadPin(row4_GPIO_Port,row4_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row4_GPIO_Port,row4_Pin) == 0);
		return keypad[3][1];
	}
	
	HAL_GPIO_WritePin(col3_GPIO_Port,col3_Pin,0);
	if(HAL_GPIO_ReadPin(row1_GPIO_Port,row1_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row1_GPIO_Port,row1_Pin) == 0);
		return keypad[0][2];
	}
	if(HAL_GPIO_ReadPin(row2_GPIO_Port,row2_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row2_GPIO_Port,row2_Pin) == 0);
		return keypad[1][2];
	}
	if(HAL_GPIO_ReadPin(row3_GPIO_Port,row3_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row3_GPIO_Port,row3_Pin) == 0);
		return keypad[2][2];
	}
	if(HAL_GPIO_ReadPin(row4_GPIO_Port,row4_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row4_GPIO_Port,row4_Pin) == 0);
		return keypad[3][2];
	}
	
	HAL_GPIO_WritePin(col4_GPIO_Port,col4_Pin,0);
	if(HAL_GPIO_ReadPin(row1_GPIO_Port,row1_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row1_GPIO_Port,row1_Pin) == 0);
		return keypad[0][3];
	}
	if(HAL_GPIO_ReadPin(row2_GPIO_Port,row2_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row2_GPIO_Port,row2_Pin) == 0);
		return keypad[1][3];
	}
	if(HAL_GPIO_ReadPin(row3_GPIO_Port,row3_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row3_GPIO_Port,row3_Pin) == 0);
		return keypad[2][3];
	}
	if(HAL_GPIO_ReadPin(row4_GPIO_Port,row4_Pin) == 0)
	{
		while(HAL_GPIO_ReadPin(row4_GPIO_Port,row4_Pin) == 0);
		return keypad[3][3];
	}
	
	return 2;
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
	Lcd_HandleTypeDef lcd = Lcd_create(ports, pins, RS_GPIO_Port, RS_Pin, EN_GPIO_Port, EN_Pin, LCD_4_BIT_MODE);
	Lcd_clear(&lcd);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		key = GetKeyPad();
		if(key != 2)
		{
			Lcd_cursor(&lcd,lcd_row,lcd_col);
			sprintf(str,"%c",(char)key);
			Lcd_string(&lcd,str);
			
			lcd_col++;
			if(lcd_col == 17)
			{
				lcd_col = 1;
				lcd_row++;
				if(lcd_row == 3)
					lcd_row = 1;
			}
		}
		HAL_Delay(10);
		
		
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
  HAL_GPIO_WritePin(GPIOC, RS_Pin|RW_Pin|EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, col1_Pin|col2_Pin|col3_Pin|col4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D4_Pin|D5_Pin|D6_Pin|D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RS_Pin RW_Pin EN_Pin */
  GPIO_InitStruct.Pin = RS_Pin|RW_Pin|EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : col1_Pin col2_Pin col3_Pin col4_Pin */
  GPIO_InitStruct.Pin = col1_Pin|col2_Pin|col3_Pin|col4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D4_Pin D5_Pin D6_Pin D7_Pin */
  GPIO_InitStruct.Pin = D4_Pin|D5_Pin|D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : row4_Pin row3_Pin row2_Pin row1_Pin */
  GPIO_InitStruct.Pin = row4_Pin|row3_Pin|row2_Pin|row1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
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
