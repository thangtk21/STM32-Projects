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
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
	int counter = 0;
	char data_uart_AT[] = "AT\r";//"ATD0344383980;<CR><LF>";
	char data_uart_ATH[] = "ATH\r";
	char data_uart_SMS_mode_text[] = "AT+CMGF=1\r";
//	char data_uart_SMS_start[] = "AT+CMGS=\"0382643699\"\r";//"AT+CMGS=\"0382643699\"\r\n";
//	char data_uart_SMS_content[] = "New Temple and Page Autumn"; // ? 
	char data_uart_SMS_end[1] = {0x1A};
	char check_sms_transmit_line[] = "AT\r";
	
	char data_uart_receive[30]; // string to save feedback data from SIM800C
	char data_uart_receive2[15]; // string to save feedback data from SIM800C
	char data_uart_receive3[30]; // string to save feedback data from SIM800C
	char data_uart_receive4[15]; // string to save feedback data from SIM800C
	char data_uart_receive5[15]; // string to save feedback data from SIM800C
	int call_enable = 0;
	int call_end = 0;
	int SMS_enable = 0;
	int read_SMS_enable = 1;
	
	//char str_number[16];
	
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
void phone_call(char* phone_number)
{
	char str_number[16];
	if (call_enable == 1)
	{
		sprintf(str_number, "ATD%s;\r", phone_number);
		HAL_UART_Transmit(&huart3, (uint8_t *)str_number, strlen(str_number), 5000);
		//HAL_UART_Receive(&huart3, (uint8_t *)&data_uart_receive, sizeof(data_uart_receive), 3739);
		//call_enable = 0;
	}
	if ( call_end == 1)
	{
		HAL_UART_Transmit(&huart3, (uint8_t *)&data_uart_ATH, sizeof(data_uart_ATH), 3799); // command to end of the call
		HAL_UART_Receive(&huart3, (uint8_t *)&data_uart_receive, sizeof(data_uart_receive), 3739); // data feedback from the SIM800C
		call_end = 0;
	}
}

void send_sms(char* phone_number_2, char* sms_content)
	{
	char data_uart_SMS_start[21]; // = "AT+CMGS=\"0382643699\"\r";//"AT+CMGS=\"0382643699\"\r\n";
	sprintf(data_uart_SMS_start, "AT+CMGS=\"%s\"\r", phone_number_2);
		
		if ( SMS_enable == 1) // flag cho phep gui tin nhan
		{
			HAL_UART_Transmit(&huart3, (uint8_t*)data_uart_SMS_start, 21, 100);
			HAL_Delay(1000); // wait for > symbol
			HAL_UART_Transmit(&huart3, (uint8_t *)sms_content, strlen(sms_content), 1000);//no dung tin nhan
			HAL_UART_Transmit(&huart3, (uint8_t *)&data_uart_SMS_end[0] , 1, 1000);
			SMS_enable = 0;
		}
	}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
		HAL_GPIO_WritePin(PWRKEY_GPIO_Port, PWRKEY_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ON_OFF_SIM_GPIO_Port, ON_OFF_SIM_Pin, GPIO_PIN_SET); // on power sim
		HAL_Delay(1000);  //
		
		HAL_GPIO_WritePin(PWRKEY_GPIO_Port, PWRKEY_Pin, GPIO_PIN_SET);
		HAL_Delay(1100); // delay at least 1 second  //luc nay do anh chua cho 5-10s khi purkey thoi
		HAL_GPIO_WritePin(PWRKEY_GPIO_Port, PWRKEY_Pin, GPIO_PIN_RESET);
		HAL_Delay(10000);  // wait for about 10senconds for SIM ready
		//HAL_UART_Transmit(&huart3, (uint8_t*)"AT+CMGF=1\r",10, 100); // config tin nhan dang text
		//HAL_Delay(2000);
		
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//		call_enable = 0;
//		// test module SIM with a phone call
//			phone_call("0344383980"); // if u wanna call to phone number: 0382643699 

//		// Cau lenh gui tin nhan
//			send_sms("0344383980", "DEVN, sms from MCU");
//		
//		if (read_SMS_enable == 1)
//		{
//			HAL_UART_Transmit(&huart3, (uint8_t*)"AT\r", 3, 10000);
//			HAL_UART_Receive(&huart3, (uint8_t *)data_uart_receive2, sizeof(data_uart_receive2), 3739);
//			
//			HAL_UART_Transmit(&huart3, (uint8_t*)"AT+CMGR=1\r",11, 10000);
//			HAL_UART_Receive(&huart3, (uint8_t *)data_uart_receive3, sizeof(data_uart_receive3), 3739);
//			read_SMS_enable = 0;
//		}
//		// check feedback from SIM
//		HAL_UART_Transmit(&huart3, (uint8_t*)"AT\r", 3, 10000);
//		HAL_UART_Receive(&huart3, (uint8_t *)data_uart_receive2, sizeof(data_uart_receive2), 3739);
//		
//		
//// LED indicatior
//		HAL_GPIO_WritePin(GPIOB, LED4_Pin|LED3_Pin|LED2_Pin, GPIO_PIN_SET); // turn off all the LED indicator
//		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
//		//HAL_Delay(5000);
////		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
////		HAL_Delay(37399);
////		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
////		HAL_Delay(37399);
////		HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
////		HAL_Delay(37399);
//		
//		counter ++;
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED4_Pin|LED3_Pin|LED2_Pin|LED1_Pin 
                          |ON_OFF_SIM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PWRKEY_GPIO_Port, PWRKEY_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED4_Pin LED3_Pin LED2_Pin LED1_Pin 
                           ON_OFF_SIM_Pin */
  GPIO_InitStruct.Pin = LED4_Pin|LED3_Pin|LED2_Pin|LED1_Pin 
                          |ON_OFF_SIM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PWRKEY_Pin */
  GPIO_InitStruct.Pin = PWRKEY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PWRKEY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : NETLIGHT_Pin */
  GPIO_InitStruct.Pin = NETLIGHT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(NETLIGHT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SIM_STATUS_Pin */
  GPIO_InitStruct.Pin = SIM_STATUS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SIM_STATUS_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
// ham de truyen uart su dung printf

_ARMABI int fputc(int c, FILE * stream) 
{
	HAL_UART_Transmit(&huart3, (uint8_t *)&c, 1, 100);
	
	return 0;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
