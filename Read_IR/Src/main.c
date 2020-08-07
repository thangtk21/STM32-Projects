/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dwt_delay.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint16_t read_ir;
uint8_t bit = 0;
uint8_t count = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint16_t read_data()
{
	uint16_t data = 0;
	while(HAL_GPIO_ReadPin(IR_Signal_GPIO_Port,IR_Signal_Pin) == 0);//wait go to high
	
	for(uint8_t i = 0;i <12;i++)
	{
		while(HAL_GPIO_ReadPin(IR_Signal_GPIO_Port,IR_Signal_Pin) == 1);
		DWT_Delay(700);
		if(HAL_GPIO_ReadPin(IR_Signal_GPIO_Port,IR_Signal_Pin) == 0)
		{
			data |= 1<<(11-i);
		
		}
		else {}
			
		
		while(HAL_GPIO_ReadPin(IR_Signal_GPIO_Port,IR_Signal_Pin) == 0);
	}
	return data&0x0fff;
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
	
	DWT_Init();


	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		
		while(HAL_GPIO_ReadPin(IR_Signal_GPIO_Port,IR_Signal_Pin) == 1);
		read_ir = read_data();
		HAL_Delay(200);
		if(read_ir == 0x0A90)
		{
			count++;
			if(count%2)
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,0);
				HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,0);
				HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,0);
				HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,0);
			}
			else
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,1);
				HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,1);
				HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,1);
				HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,1);
			}
			
		}
		if(read_ir == 0x0010)
		{
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,0);
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,1);
			HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,1);
			HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,1);
		}
		if(read_ir == 0x0810)
		{
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,1);
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,0);
			HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,1);
			HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,1);
		}
		if(read_ir == 0x0410)
		{
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,1);
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,1);
			HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,0);
			HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,1);
		}
		if(read_ir == 0x0c10)
		{
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,1);
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,1);
			HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,1);
			HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,0);
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
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
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(IR_Tran_GPIO_Port, IR_Tran_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED2_Pin|LED1_Pin|LED3_Pin|LED4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : IR_Signal_Pin */
  GPIO_InitStruct.Pin = IR_Signal_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(IR_Signal_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : IR_Tran_Pin */
  GPIO_InitStruct.Pin = IR_Tran_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IR_Tran_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED2_Pin LED1_Pin LED3_Pin LED4_Pin */
  GPIO_InitStruct.Pin = LED2_Pin|LED1_Pin|LED3_Pin|LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */




/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
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
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
