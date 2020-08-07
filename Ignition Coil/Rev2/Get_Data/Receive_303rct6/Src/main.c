
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
  * COPYRIGHT(c) 2019 STMicroelectronics
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
#include "stm32f3xx_hal.h"

/* USER CODE BEGIN Includes */
#include "variable.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_I2C2_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
static void CAN_FilterConfig(void);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */


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
  MX_CAN_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
	hcan.pTxMsg = &CanTx;
	hcan.pTxMsg->RTR = CAN_RTR_DATA;
	hcan.pTxMsg->IDE = CAN_ID_STD;
  hcan.pRxMsg = &CanRx;
	
  CAN_FilterConfig();
  if (HAL_CAN_Receive_IT(&hcan, CAN_FIFO0) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_NVIC_DisableIRQ(in1_falling_EXTI_IRQn);
  HAL_NVIC_DisableIRQ(in1_rising_EXTI_IRQn);
  HAL_NVIC_DisableIRQ(in2_falling_EXTI_IRQn);
  HAL_NVIC_DisableIRQ(in2_rising_EXTI_IRQn);
  HAL_NVIC_DisableIRQ(in3_falling_EXTI_IRQn);
  HAL_NVIC_DisableIRQ(in3_rising_EXTI_IRQn);
  HAL_NVIC_DisableIRQ(in4_falling_EXTI_IRQn);
  HAL_NVIC_DisableIRQ(in4_rising_EXTI_IRQn);
	
	//Get Parameter from EEPROM
	HAL_I2C_Mem_Read(&hi2c2,address_24LC08,0x00,1,buffer_read1,8,100);
	HAL_Delay(10);
	n1_pa = buffer_read1[0];
	n2_pa = buffer_read1[1];
	B_H = buffer_read1[2];
	B_L = buffer_read1[3];
	C_H = buffer_read1[4];
	C_L = buffer_read1[5];
	D_H = buffer_read1[6];
	D_L = buffer_read1[7];
	
	HAL_I2C_Mem_Read(&hi2c2,address_24LC08,0x20,1,buffer_read2,8,100);
	HAL_Delay(10);
	n1_pb = buffer_read2[0];
	n2_pb = buffer_read2[1];
	B1_H = buffer_read2[2];
	B1_L = buffer_read2[3];
	C1_H = buffer_read2[4];
	C1_L = buffer_read2[5];
	B2_H = buffer_read2[6];
	B2_L = buffer_read2[7];
	
	HAL_I2C_Mem_Read(&hi2c2,address_24LC08,0x40,1,buffer_read3,5,100);
	HAL_Delay(10);
	D1_H = buffer_read3[0];
	D1_L = buffer_read3[1];
	E_HH = buffer_read3[2];
	E_H = buffer_read3[3];
	E_L = buffer_read3[4];
	
	HAL_I2C_Mem_Read(&hi2c2,address_24LC08,0x60,1,buffer_read4,5,100);
	HAL_Delay(10);
	D2_H = buffer_read4[0];
	D2_L = buffer_read4[1];
	C2_H = buffer_read4[2];
	C2_L = buffer_read4[3];
	
	B = (B_H << 8) | B_L;
	C = (C_H << 8) | C_L;
	D = (D_H << 8) | D_L;

	B1 = (B1_H << 8) | B1_L;
	C1 = (C1_H << 8) | C1_L;
	B2 = (B2_H << 8) | B2_L;

	D1 = (D1_H << 8) | D1_L;
	E = (E_HH << 16) | (E_H << 8) | E_L;

	D2 = (D2_H << 8) | D2_L;
	C2 = (C2_H << 8) | C2_L;
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		//---------------------------------------------------------------------------------Neu ben truyen nhan send_data

		////---------------------------------------------------------------------------------pattern a
    if (can_rx_int1 == 1)
    {
			can_rx_int1 = 0;
			
      __HAL_GPIO_EXTI_CLEAR_IT(in1_falling_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in1_rising_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in2_falling_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in2_rising_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in3_falling_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in3_rising_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in4_falling_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in4_rising_Pin);

      HAL_NVIC_EnableIRQ(in1_falling_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in1_rising_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in2_falling_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in2_rising_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in3_falling_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in3_rising_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in4_falling_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in4_rising_EXTI_IRQn);

      B = (B_H << 8) | B_L;
      C = (C_H << 8) | C_L;
      D = (D_H << 8) | D_L;
			
			
			buffer_write1[0] = n1_pa;
			buffer_write1[1] = n2_pa;
			buffer_write1[2] = B_H;
			buffer_write1[3] = B_L;
			buffer_write1[4] = C_H;
			buffer_write1[5] = C_L;
			buffer_write1[6] = D_H;
			buffer_write1[7] = D_L;
			HAL_I2C_Mem_Write(&hi2c2,address_24LC08,0x00,1,buffer_write1,8,100);
			HAL_Delay(10);
			
			
			
			if(D >= 20)	D = D - 10;
			if(D < 10) D = 10;
			
				
			
			
			if(D == 0 && n1_pa == 0 && n2_pa == 0)
			{
				HAL_TIM_Base_Stop_IT(&htim1);
				HAL_TIM_Base_Stop_IT(&htim2);
			}
			else
			{
			//Generate Pulse
				HAL_TIM_Base_Start_IT(&htim1);
				HAL_TIM_Base_Stop_IT(&htim2);
			}
			
    }
		
		////---------------------------------------------------------------------------------pattern b    
    if (can_rx_int2 == 1 && can_rx_int3 == 1 && can_rx_int4 == 1)
    {
			can_rx_int2 = 0;
      can_rx_int3 = 0;
      can_rx_int4 = 0;
			
      __HAL_GPIO_EXTI_CLEAR_IT(in1_falling_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in1_rising_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in2_falling_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in2_rising_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in3_falling_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in3_rising_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in4_falling_Pin);
      __HAL_GPIO_EXTI_CLEAR_IT(in4_rising_Pin);

      HAL_NVIC_EnableIRQ(in1_falling_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in1_rising_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in2_falling_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in2_rising_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in3_falling_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in3_rising_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in4_falling_EXTI_IRQn);
      HAL_NVIC_EnableIRQ(in4_rising_EXTI_IRQn);
			
      B1 = (B1_H << 8) | B1_L;
      C1 = (C1_H << 8) | C1_L;
      B2 = (B2_H << 8) | B2_L;
      D1 = (D1_H << 8) | D1_L;
      E = (E_HH << 16) | (E_H << 8) | E_L;
      D2 = (D2_H << 8) | D2_L;
      C2 = (C2_H << 8) | C2_L;
			
			//write byte to EEPROM
			buffer_write2[0] = n1_pb;
			buffer_write2[1] = n2_pb;
			buffer_write2[2] = B1_H;
			buffer_write2[3] = B1_L;
			buffer_write2[4] = C1_H;
			buffer_write2[5] = C1_L;
			buffer_write2[6] = B2_H;
			buffer_write2[7] = B2_L;
			HAL_I2C_Mem_Write(&hi2c2,address_24LC08,0x20,1,buffer_write2,8,100);
			HAL_Delay(10);
			
			buffer_write3[0] = D1_H;
			buffer_write3[1] = D1_L;
			buffer_write3[2] = E_HH;
			buffer_write3[3] = E_H;
			buffer_write3[4] = E_L;
			HAL_I2C_Mem_Write(&hi2c2,address_24LC08,0x40,1,buffer_write3,5,100);
			HAL_Delay(10);
			
			buffer_write4[0] = D2_H;
			buffer_write4[1] = D2_L;
			buffer_write4[2] = C2_H;
			buffer_write4[3] = C2_L;
			HAL_I2C_Mem_Write(&hi2c2,address_24LC08,0x60,1,buffer_write4,5,100);
			HAL_Delay(10);
   
			//Calibration
			if(D1 >= 10)	D1 = D1 - 10;
			if(B1 >= 20) B1 = B1 - 10;
			
			if(n1_pb == 0) C1 = 0;
			if(C1 == 0) n1_pb = 0;
			if(n2_pb == 0) C2 = 0;
			if(C2 == 0) n2_pb = 0;
			if(n1_pb == 0 && n2_pb == 0 && B1 == 0 && C1 == 0 && D1 == 0 && E == 0 && D2 == 0 && C2 == 0)	D1 = 100;
			
			
			
			//Generate Pulse
			HAL_TIM_Base_Start_IT(&htim2);
			HAL_TIM_Base_Stop_IT(&htim1);
			
    }
		
		////---------------------------------------------------------------------------------Neu ben truyen an request data
		if(flag_request_data == 1)
		{
			flag_request_data = 0;
			
			if(flag_choose_mode == pattern_a)
			{
				CanTx.StdId = 0x201;
				CanTx.DLC = 8;
				CanTx.Data[0] = n1_pa;
				CanTx.Data[1] = n2_pa;
				CanTx.Data[2] = B_H;
				CanTx.Data[3] = B_L;
				CanTx.Data[4] = C_H;
				CanTx.Data[5] = C_L;
				CanTx.Data[6] = D_H;
				CanTx.Data[7] = D_L;
				HAL_CAN_Transmit(&hcan, 10);
				HAL_Delay(10);
			}
			
			if(flag_choose_mode == pattern_b)
			{
				CanTx.StdId = 0x202;
				CanTx.DLC = 8;
				CanTx.Data[0] = n1_pb;
				CanTx.Data[1] = n2_pb;
				CanTx.Data[2] = B1_H;
				CanTx.Data[3] = B1_L;
				CanTx.Data[4] = C1_H;
				CanTx.Data[5] = C1_L;
				CanTx.Data[6] = B2_H;
				CanTx.Data[7] = B2_L;
				HAL_CAN_Transmit(&hcan, 10);
				HAL_Delay(10);

				CanTx.StdId = 0x203;
				CanTx.DLC = 5;
				CanTx.Data[0] = D1_H;
				CanTx.Data[1] = D1_L;
				CanTx.Data[2] = E_HH;
				CanTx.Data[3] = E_H;
				CanTx.Data[4] = E_L;
				HAL_CAN_Transmit(&hcan, 10);
				HAL_Delay(10);

				CanTx.StdId = 0x204;
				CanTx.DLC = 4;
				CanTx.Data[0] = D2_H;
				CanTx.Data[1] = D2_L;
				CanTx.Data[2] = C2_H;
				CanTx.Data[3] = C2_L;
				HAL_CAN_Transmit(&hcan, 10);
				HAL_Delay(10);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
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

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C2|RCC_PERIPHCLK_TIM1;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_HSI;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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

/* CAN init function */
static void MX_CAN_Init(void)
{

  hcan.Instance = CAN;
  hcan.Init.Prescaler = 400;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SJW = CAN_SJW_1TQ;
  hcan.Init.BS1 = CAN_BS1_12TQ;
  hcan.Init.BS2 = CAN_BS2_5TQ;
  hcan.Init.TTCM = DISABLE;
  hcan.Init.ABOM = DISABLE;
  hcan.Init.AWUM = DISABLE;
  hcan.Init.NART = DISABLE;
  hcan.Init.RFLM = DISABLE;
  hcan.Init.TXFP = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* I2C2 init function */
static void MX_I2C2_Init(void)
{

  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x2000090E;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Analogue filter 
    */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Digital filter 
    */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 8;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 79;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 79;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, out4b_Pin|out4a_Pin|out3b_Pin|out3a_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, out2b_Pin|out2a_Pin|out1b_Pin|out1a_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : in1_rising_Pin in2_rising_Pin in3_rising_Pin in4_rising_Pin */
  GPIO_InitStruct.Pin = in1_rising_Pin|in2_rising_Pin|in3_rising_Pin|in4_rising_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : in4_falling_Pin in3_falling_Pin */
  GPIO_InitStruct.Pin = in4_falling_Pin|in3_falling_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : in2_falling_Pin in1_falling_Pin */
  GPIO_InitStruct.Pin = in2_falling_Pin|in1_falling_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : out4b_Pin out4a_Pin out3b_Pin out3a_Pin */
  GPIO_InitStruct.Pin = out4b_Pin|out4a_Pin|out3b_Pin|out3a_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : out2b_Pin out2a_Pin out1b_Pin out1a_Pin */
  GPIO_InitStruct.Pin = out2b_Pin|out2a_Pin|out1b_Pin|out1a_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  //HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
  //HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_TSC_IRQn, 2, 0);
  //HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
  //HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0);
  //HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
  //HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
  //HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
//---------------------------------------------------------------------------------------------------Init Can Filter
static void CAN_FilterConfig(void)
{
  sFilterConfig.BankNumber = 14;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  sFilterConfig.FilterIdHigh = 0;
  sFilterConfig.FilterIdLow = 0;
  sFilterConfig.FilterMaskIdHigh = 0;
  sFilterConfig.FilterMaskIdLow = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterNumber = 0;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

void RxIntEnable(CAN_HandleTypeDef *CanHandle) 
{
	if(CanHandle->State == HAL_CAN_STATE_BUSY_TX)
	  CanHandle->State = HAL_CAN_STATE_BUSY_TX_RX0;
	else 
	{
	  CanHandle->State = HAL_CAN_STATE_BUSY_RX0;

		/* Set CAN error code to none */
		CanHandle->ErrorCode = HAL_CAN_ERROR_NONE;

		/* Enable Error warning Interrupt */
		__HAL_CAN_ENABLE_IT(CanHandle, CAN_IT_EWG);

		/* Enable Error passive Interrupt */
		__HAL_CAN_ENABLE_IT(CanHandle, CAN_IT_EPV);

		/* Enable Bus-off Interrupt */
		__HAL_CAN_ENABLE_IT(CanHandle, CAN_IT_BOF);

		/* Enable Last error code Interrupt */
		__HAL_CAN_ENABLE_IT(CanHandle, CAN_IT_LEC);

		/* Enable Error Interrupt */
		__HAL_CAN_ENABLE_IT(CanHandle, CAN_IT_ERR);
	}

	// Enable FIFO 0 message pending Interrupt
	__HAL_CAN_ENABLE_IT(CanHandle, CAN_IT_FMP0);
}

//---------------------------------------------------------------------------------------------------Can Receive Interrupt
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* CanHandle)
{
  if (CanHandle->pRxMsg->StdId == 0x101)
  {
    can_rx_int1 = 1;
    n1_pa = CanHandle->pRxMsg->Data[0];
    n2_pa = CanHandle->pRxMsg->Data[1];
    B_H = CanHandle->pRxMsg->Data[2];
    B_L = CanHandle->pRxMsg->Data[3];
    C_H = CanHandle->pRxMsg->Data[4];
    C_L = CanHandle->pRxMsg->Data[5];
    D_H = CanHandle->pRxMsg->Data[6];
    D_L = CanHandle->pRxMsg->Data[7];
  }
  if (CanHandle->pRxMsg->StdId == 0x102)
  {
    can_rx_int2 = 1;
		n1_pb = CanHandle->pRxMsg->Data[0];
    n2_pb = CanHandle->pRxMsg->Data[1];
    B1_H = CanHandle->pRxMsg->Data[2];
    B1_L = CanHandle->pRxMsg->Data[3];
    C1_H = CanHandle->pRxMsg->Data[4];
    C1_L = CanHandle->pRxMsg->Data[5];
    B2_H = CanHandle->pRxMsg->Data[6];
    B2_L = CanHandle->pRxMsg->Data[7];
  }
  if (CanHandle->pRxMsg->StdId == 0x103)
  {
    can_rx_int3 = 1;
    D1_H = CanHandle->pRxMsg->Data[0];
    D1_L = CanHandle->pRxMsg->Data[1];
    E_HH = CanHandle->pRxMsg->Data[2];
    E_H = CanHandle->pRxMsg->Data[3];
    E_L = CanHandle->pRxMsg->Data[4];
  }
  if (CanHandle->pRxMsg->StdId == 0x104)
  {
    can_rx_int4 = 1;
    D2_H = CanHandle->pRxMsg->Data[0];
    D2_L = CanHandle->pRxMsg->Data[1];
    C2_H = CanHandle->pRxMsg->Data[2];
    C2_L = CanHandle->pRxMsg->Data[3];
  }
	if(CanHandle->pRxMsg->StdId == 0x10A)
	{
		flag_request_data = 1;
		flag_choose_mode = CanHandle->pRxMsg->Data[0];
	}
  RxIntEnable(&hcan);
}
//---------------------------------------------------------------------------------------------------External Interrupt
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == in1_rising_Pin)
  {
		HAL_GPIO_WritePin(out1a_GPIO_Port, out1a_Pin, 0);
		
		if(flag_choose_mode == pattern_a && D == 0)
			HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 0);
		
    flag_in1_rising_a_tim1 = 1;
    flag_in1_rising_b_tim1 = 1;
    flag_in1_rising_a_tim2 = 1;
    flag_in1_rising_b_tim2 = 1;
  }
  if (GPIO_Pin == in1_falling_Pin)
  {
    HAL_GPIO_WritePin(out1a_GPIO_Port, out1a_Pin, 1);
		
		if(flag_choose_mode == pattern_a && D == 0)
			HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 1);
		
    flag_in1_falling_a_tim1 = 1;
    flag_in1_falling_b_tim1 = 1;
    flag_in1_falling_a_tim2 = 1;
    flag_in1_falling_b_tim2 = 1;
  }
  if (GPIO_Pin == in2_rising_Pin)
  {
    HAL_GPIO_WritePin(out2a_GPIO_Port, out2a_Pin, 0);
		
		if(flag_choose_mode == pattern_a && D == 0)
			HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 0);
		
    flag_in2_rising_a_tim1 = 1;
    flag_in2_rising_b_tim1 = 1;
    flag_in2_rising_a_tim2 = 1;
    flag_in2_rising_b_tim2 = 1;
  }
  if (GPIO_Pin == in2_falling_Pin)
  {
		HAL_GPIO_WritePin(out2a_GPIO_Port, out2a_Pin, 1);
		
		if(flag_choose_mode == pattern_a && D == 0)
			HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 1);
		
    flag_in2_falling_a_tim1 = 1;
    flag_in2_falling_b_tim1 = 1;
    flag_in2_falling_a_tim2 = 1;
    flag_in2_falling_b_tim2 = 1;
  }
  if (GPIO_Pin == in3_rising_Pin)
  {
		HAL_GPIO_WritePin(out3a_GPIO_Port, out3a_Pin, 0);
		
		if(flag_choose_mode == pattern_a && D == 0)
			HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 0);
		
    flag_in3_rising_a_tim1 = 1;
    flag_in3_rising_b_tim1 = 1;
    flag_in3_rising_a_tim2 = 1;
    flag_in3_rising_b_tim2 = 1;
    
  }
  if (GPIO_Pin == in3_falling_Pin)
  {
		HAL_GPIO_WritePin(out3a_GPIO_Port, out3a_Pin, 1);
		
		if(flag_choose_mode == pattern_a && D == 0)
			HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 1);
		
    flag_in3_falling_a_tim1 = 1;
    flag_in3_falling_b_tim1 = 1;
    flag_in3_falling_a_tim2 = 1;
    flag_in3_falling_b_tim2 = 1;
    
  }
  if (GPIO_Pin == in4_rising_Pin)
  {
		HAL_GPIO_WritePin(out4a_GPIO_Port, out4a_Pin, 0);
		
		if(flag_choose_mode == pattern_a && D == 0)
			HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 0);
		
    flag_in4_rising_a_tim1 = 1;
    flag_in4_rising_b_tim1 = 1;
    flag_in4_rising_a_tim2 = 1;
    flag_in4_rising_b_tim2 = 1;
    
  }
  if (GPIO_Pin == in4_falling_Pin)
  {
		HAL_GPIO_WritePin(out4a_GPIO_Port, out4a_Pin, 1);
		
		if(flag_choose_mode == pattern_a && D == 0)
			HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 1);
		
    flag_in4_falling_a_tim1 = 1;
    flag_in4_falling_b_tim1 = 1;
    flag_in4_falling_a_tim2 = 1;
    flag_in4_falling_b_tim2 = 1;
    
  }
}
//---------------------------------------------------------------------------------------------------Timer Interrupt
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  //--------------------------------------------------------------------------Timer 1
  if (htim->Instance == TIM1)
  {
    //-----------------------------------------------------------channel 1
    //------------------------------------------output 1a
    if (flag_in1_falling_a_tim1 == 1)
    {
      if (counter_out1a_tim1 < B / 10)
      {
        HAL_GPIO_WritePin(out1a_GPIO_Port, out1a_Pin, 1);
      }
      if (counter_out1a_tim1 >= B / 10 && counter_out1a_tim1 < (B + C) / 10)
      {
        HAL_GPIO_WritePin(out1a_GPIO_Port, out1a_Pin, 0);
      }
      if (counter_out1a_tim1 == (B + C) / 10 || B == 0 || C == 0)
      {
        counter_out1a_tim1 = 0;
        HAL_GPIO_WritePin(out1a_GPIO_Port, out1a_Pin, 1);
        n1_times_tim1_in1++;
      }
      counter_out1a_tim1++;
      if (n1_times_tim1_in1 == n1_pa||n1_pa == 0)
      {
        counter_out1a_tim1 = 0;
        n1_times_tim1_in1 = 0;
        flag_in1_falling_a_tim1 = 0;
      }
    }
    //------------------------------------------output 1b //
    if (flag_in1_rising_b_tim1 == 1 && D!=0)
    {
      if (counter_out1b_tim1_before < D / 10)
      {
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 1);
      }
      if (counter_out1b_tim1_before == D / 10)
      {
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 0);
        counter_out1b_tim1_before = UINT16_MAX;
        flag_in1_rising_b_tim1 = 0;
      }
      counter_out1b_tim1_before++;
    }
    if (flag_in1_falling_b_tim1 == 1&& D!=0)
    {
      if (counter_out1b_tim1_after < D / 10)
      {
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 0);
      }
      if (counter_out1b_tim1_after >= D / 10 && counter_out1b_tim1_after < (D + B) / 10)
      {
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 1);
      }
      if (counter_out1b_tim1_after >= (D + B) / 10 && counter_out1b_tim1_after < (D + B + C) / 10)
      {
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 0);
      }
      if (counter_out1b_tim1_after == (D + B + C) / 10)
      {
        counter_out1b_tim1_after = D / 10;
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 1);
        n2_times_tim1_in1++;
      }
      counter_out1b_tim1_after++;
      if ((n2_times_tim1_in1 == n2_pa && n2_pa > 0)||(n2_pa == 0 && counter_out1b_tim1_after == D/ 10))
      {
				HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 1);
        counter_out1b_tim1_after = 0;
        n2_times_tim1_in1 = 0;
        flag_in1_falling_b_tim1 = 0;
      }
    }
    //-----------------------------------------------------------channel 2
    //------------------------------------------output 2a
    if (flag_in2_falling_a_tim1 == 1)
    {
      if (counter_out2a_tim1 < B / 10)
      {
        HAL_GPIO_WritePin(out2a_GPIO_Port, out2a_Pin, 1);
      }
      if (counter_out2a_tim1 >= B / 10 && counter_out2a_tim1 < (B + C) / 10)
      {
        HAL_GPIO_WritePin(out2a_GPIO_Port, out2a_Pin, 0);
      }
      if (counter_out2a_tim1 == (B + C) / 10|| B == 0 || C == 0)
      {
        counter_out2a_tim1 = 0;
        HAL_GPIO_WritePin(out2a_GPIO_Port, out2a_Pin, 1);
        n1_times_tim1_in2++;
      }
      counter_out2a_tim1++;
      if (n1_times_tim1_in2 == n1_pa||n1_pa == 0)
      {
        counter_out2a_tim1 = 0;
        n1_times_tim1_in2 = 0;
        flag_in2_falling_a_tim1 = 0;
      }
    }
    //------------------------------------------output 2b
    if (flag_in2_rising_b_tim1 == 1&& D!=0)
    {
      if (counter_out2b_tim1_before < D / 10)
      {
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 1);
      }
      if (counter_out2b_tim1_before == D / 10)
      {
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 0);
        counter_out2b_tim1_before = UINT16_MAX;
        flag_in2_rising_b_tim1 = 0;
      }
      counter_out2b_tim1_before++;
    }
    if (flag_in2_falling_b_tim1 == 1&& D!=0)
    {
      if (counter_out2b_tim1_after < D / 10)
      {
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 0);
      }
      if (counter_out2b_tim1_after >= D / 10 && counter_out2b_tim1_after < (D + B) / 10)
      {
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 1);
      }
      if (counter_out2b_tim1_after >= (D + B) / 10 && counter_out2b_tim1_after < (D + B + C) / 10)
      {
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 0);
      }
      if (counter_out2b_tim1_after == (D + B + C) / 10)
      {
       counter_out2b_tim1_after = D / 10;
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 1);
        n2_times_tim1_in2++;
      }
      counter_out2b_tim1_after++;
      if ((n2_times_tim1_in2 == n2_pa && n2_pa > 0)||(n2_pa == 0 && counter_out2b_tim1_after == D/ 10))
      {
				HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 1);
        counter_out2b_tim1_after = 0;
        n2_times_tim1_in2 = 0;
        flag_in2_falling_b_tim1 = 0;
      }
    }
    //-----------------------------------------------------------channel 3
    //------------------------------------------output 3a
    if (flag_in3_falling_a_tim1 == 1)
    {
      if (counter_out3a_tim1 < B / 10)
      {
        HAL_GPIO_WritePin(out3a_GPIO_Port, out3a_Pin, 1);
      }
      if (counter_out3a_tim1 >= B / 10 && counter_out3a_tim1 < (B + C) / 10)
      {
        HAL_GPIO_WritePin(out3a_GPIO_Port, out3a_Pin, 0);
      }
      if (counter_out3a_tim1 == (B + C) / 10|| B == 0 || C == 0)
      {
        counter_out3a_tim1 = 0;
        HAL_GPIO_WritePin(out3a_GPIO_Port, out3a_Pin, 1);
        n1_times_tim1_in3++;
      }
      counter_out3a_tim1++;
      if (n1_times_tim1_in3 == n1_pa||n1_pa == 0)
      {
        counter_out3a_tim1 = 0;
        n1_times_tim1_in3 = 0;
        flag_in3_falling_a_tim1 = 0;
      }
    }
    //------------------------------------------output 3b
    if (flag_in3_rising_b_tim1 == 1&& D!=0)
    {
      if (counter_out3b_tim1_before < D / 10)
      {
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 1);
      }
      if (counter_out3b_tim1_before == D / 10)
      {
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 0);
        counter_out3b_tim1_before = UINT16_MAX;
        flag_in3_rising_b_tim1 = 0;
      }
      counter_out3b_tim1_before++;
    }
    if (flag_in3_falling_b_tim1 == 1&& D!=0)
    {
      if (counter_out3b_tim1_after < D / 10)
      {
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 0);
      }
      if (counter_out3b_tim1_after >= D / 10 && counter_out3b_tim1_after < (D + B) / 10)
      {
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 1);
      }
      if (counter_out3b_tim1_after >= (D + B) / 10 && counter_out3b_tim1_after < (D + B + C) / 10)
      {
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 0);
      }
      if (counter_out3b_tim1_after == (D + B + C) / 10)
      {
        counter_out3b_tim1_after = D / 10;
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 1);
        n2_times_tim1_in3++;
      }
      counter_out3b_tim1_after++;
      if ((n2_times_tim1_in3 == n2_pa && n2_pa > 0)||(n2_pa == 0 && counter_out3b_tim1_after == D/ 10))
      {
				HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 1);
        counter_out3b_tim1_after = 0;
        n2_times_tim1_in3 = 0;
        flag_in3_falling_b_tim1 = 0;
      }
    }
    //-----------------------------------------------------------channel 4
    //------------------------------------------output 4a
    if (flag_in4_falling_a_tim1 == 1)
    {
      if (counter_out4a_tim1 < B / 10)
      {
        HAL_GPIO_WritePin(out4a_GPIO_Port, out4a_Pin, 1);
      }
      if (counter_out4a_tim1 >= B / 10 && counter_out4a_tim1 < (B + C) / 10)
      {
        HAL_GPIO_WritePin(out4a_GPIO_Port, out4a_Pin, 0);
      }
      if (counter_out4a_tim1 == (B + C) / 10|| B == 0 || C == 0)
      {
        counter_out4a_tim1 = 0;
        HAL_GPIO_WritePin(out4a_GPIO_Port, out4a_Pin, 1);
        n1_times_tim1_in4++;
      }
      counter_out4a_tim1++;
      if (n1_times_tim1_in4 == n1_pa||n1_pa == 0)
      {
        counter_out4a_tim1 = 0;
        n1_times_tim1_in4 = 0;
        flag_in4_falling_a_tim1 = 0;
      }
    }
    //------------------------------------------output 4b
    if (flag_in4_rising_b_tim1 == 1&& D!=0)
    {
      if (counter_out4b_tim1_before < D / 10)
      {
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 1);
      }
      if (counter_out4b_tim1_before == D / 10)
      {
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 0);
        counter_out4b_tim1_before = UINT16_MAX;
        flag_in4_rising_b_tim1 = 0;
      }
      counter_out4b_tim1_before++;
    }
    if (flag_in4_falling_b_tim1 == 1 && D!=0)
    {
      if (counter_out4b_tim1_after < D / 10)
      {
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 0);
      }
      if (counter_out4b_tim1_after >= D / 10 && counter_out4b_tim1_after < (D + B) / 10)
      {
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 1);
      }
      if (counter_out4b_tim1_after >= (D + B) / 10 && counter_out4b_tim1_after < (D + B + C) / 10)
      {
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 0);
      }
      if (counter_out4b_tim1_after == (D + B + C) / 10)
      {
        counter_out4b_tim1_after = D / 10;
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 1);
        n2_times_tim1_in4++;
      }
      counter_out4b_tim1_after++;
      if ((n2_times_tim1_in4 == n2_pa && n2_pa > 0)||(n2_pa == 0 && counter_out4b_tim1_after == D/ 10))
      {
				HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 1);
        counter_out4b_tim1_after = 0;
        n2_times_tim1_in4 = 0;
        flag_in4_falling_b_tim1 = 0;
      }
    }
  }
  //--------------------------------------------------------------------------Timer 2 pattern b
  if (htim->Instance == TIM2)
  {
    //-----------------------------------------------------------output 1a
    if (flag_in1_falling_a_tim2 == 1)
    {
      if (counter_out1a_tim2 < B1 / 10)
      {
        HAL_GPIO_WritePin(out1a_GPIO_Port, out1a_Pin, 1);
      }
      if (counter_out1a_tim2 >= B1 / 10 && counter_out1a_tim2 < (B1 + C1) / 10)
      {
        HAL_GPIO_WritePin(out1a_GPIO_Port, out1a_Pin, 0);
      }
      if (counter_out1a_tim2 >= (B1 + C1) / 10 && counter_out1a_tim2 < (B1 + C1 + B2) / 10)
      {
        HAL_GPIO_WritePin(out1a_GPIO_Port, out1a_Pin, 1);
      }
      if (counter_out1a_tim2 >= (B1 + C1 + B2) / 10 && counter_out1a_tim2 < (B1 + C1 + B2 + C1) / 10)
      {
        HAL_GPIO_WritePin(out1a_GPIO_Port, out1a_Pin, 0);
      }
      if (counter_out1a_tim2 == (B1 + C1 + B2 + C1) / 10)
      {
        counter_out1a_tim2 = (B1 + C1) / 10;
        HAL_GPIO_WritePin(out1a_GPIO_Port, out1a_Pin, 1);
        n1_times_tim2_in1++;
      }
      counter_out1a_tim2++;
      if ((n1_times_tim2_in1 == n1_pb - 1 && n1_pb >= 2)|| (n1_pb == 1 && counter_out1a_tim2 == (B1+C1)/ 10)|| n1_pb == 0)
      {
				HAL_GPIO_WritePin(out1a_GPIO_Port, out1a_Pin, 1);
        counter_out1a_tim2 = 0;
        n1_times_tim2_in1 = 0;
        flag_in1_falling_a_tim2 = 0;
      }
    }
    //-----------------------------------------------------------output 1b
    if (flag_in1_falling_b_tim2 == 1)
    {
      if (counter_out1b_tim2 < D1 / 10)
      {
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 1);
      }
      if (counter_out1b_tim2 >= D1 / 10 && counter_out1b_tim2 < (D1 + E) / 10)
      {
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 0);
      }
      if (counter_out1b_tim2 >= (D1 + E) / 10 && counter_out1b_tim2 < (B1 + C1 + D2) / 10)
      {
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 1);
      }
      if (counter_out1b_tim2 >= (B1 + C1 + D2) / 10 && counter_out1b_tim2 < (B1 + C1 + D2 + C2) / 10)
      {
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 0);
      }
      if (counter_out1b_tim2 >= (B1 + C1 + D2 + C2) / 10 && counter_out1b_tim2 < (B1 + C1 + B2 + C1 + D2) / 10)
      {
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 1);
      }
      if (counter_out1b_tim2 >= (B1 + C1 + B2 + C1 + D2) / 10 && counter_out1b_tim2 < (B1 + C1 + B2 + C1 + D2 + C2) / 10)
      {
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 0);
      }
      if (counter_out1b_tim2 == (B1 + C1 + B2 + C1 + D2 + C2) / 10)
      {
        counter_out1b_tim2 = (B1 + C1 + D2 + C2) / 10;
        n2_times_tim2_in1++;
        HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 1);
      }
      counter_out1b_tim2++;
      if ((n2_times_tim2_in1 == n2_pb - 1 && n2_pb >=2)|| (counter_out1b_tim2 == (B1+C1+D2+C2)/ 10 && n2_pb == 1 ) || (n2_pb == 0 && counter_out1b_tim2 == (D1+E)/ 10))
      {
				HAL_GPIO_WritePin(out1b_GPIO_Port, out1b_Pin, 1);
        counter_out1b_tim2 = 0;
        n2_times_tim2_in1 = 0;
        flag_in1_falling_b_tim2 = 0;
      }
    }
    //-----------------------------------------------------------output 2a
    if (flag_in2_falling_a_tim2 == 1)
    {
      if (counter_out2a_tim2 < B1 / 10)
      {
        HAL_GPIO_WritePin(out2a_GPIO_Port, out2a_Pin, 1);
      }
      if (counter_out2a_tim2 >= B1 / 10 && counter_out2a_tim2 < (B1 + C1) / 10)
      {
        HAL_GPIO_WritePin(out2a_GPIO_Port, out2a_Pin, 0);
      }
      if (counter_out2a_tim2 >= (B1 + C1) / 10 && counter_out2a_tim2 < (B1 + C1 + B2) / 10)
      {
        HAL_GPIO_WritePin(out2a_GPIO_Port, out2a_Pin, 1);
      }
      if (counter_out2a_tim2 >= (B1 + C1 + B2) / 10 && counter_out2a_tim2 < (B1 + C1 + B2 + C1) / 10)
      {
        HAL_GPIO_WritePin(out2a_GPIO_Port, out2a_Pin, 0);
      }
      if (counter_out2a_tim2 == (B1 + C1 + B2 + C1) / 10)
      {
        counter_out2a_tim2 = (B1 + C1) / 10;
        HAL_GPIO_WritePin(out2a_GPIO_Port, out2a_Pin, 1);
        n1_times_tim2_in2++;
      }
      counter_out2a_tim2++;
      if ((n1_times_tim2_in2 == n1_pb - 1 && n1_pb >= 2)|| (n1_pb == 1 && counter_out2a_tim2 == (B1+C1)/ 10)|| n1_pb == 0)
      {
        HAL_GPIO_WritePin(out2a_GPIO_Port, out2a_Pin, 1);
				counter_out2a_tim2 = 0;
        n1_times_tim2_in2 = 0;
        flag_in2_falling_a_tim2 = 0;
      }
    }
    //-----------------------------------------------------------output 2b
    if (flag_in2_falling_b_tim2 == 1)
    {
      if (counter_out2b_tim2 < D1 / 10)
      {
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 1);
      }
      if (counter_out2b_tim2 >= D1 / 10 && counter_out2b_tim2 < (D1 + E) / 10)
      {
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 0);
      }
      if (counter_out2b_tim2 >= (D1 + E) / 10 && counter_out2b_tim2 < (B1 + C1 + D2) / 10)
      {
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 1);
      }
      if (counter_out2b_tim2 >= (B1 + C1 + D2) / 10 && counter_out2b_tim2 < (B1 + C1 + D2 + C2) / 10)
      {
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 0);
      }
      if (counter_out2b_tim2 >= (B1 + C1 + D2 + C2) / 10 && counter_out2b_tim2 < (B1 + C1 + B2 + C1 + D2) / 10)
      {
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 1);
      }
      if (counter_out2b_tim2 >= (B1 + C1 + B2 + C1 + D2) / 10 && counter_out2b_tim2 < (B1 + C1 + B2 + C1 + D2 + C2) / 10)
      {
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 0);
      }
      if (counter_out2b_tim2 == (B1 + C1 + B2 + C1 + D2 + C2) / 10)
      {
        counter_out2b_tim2 = (B1 + C1 + D2 + C2) / 10;
        n2_times_tim2_in2++;
        HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 1);
      }

      counter_out2b_tim2++;
      if ((n2_times_tim2_in2 == n2_pb - 1 && n2_pb >=2)|| (counter_out2b_tim2 == (B1+C1+D2+C2)/ 10 && n2_pb == 1)|| (n2_pb == 0 && counter_out2b_tim2 == (D1+E)/ 10))
      {
				HAL_GPIO_WritePin(out2b_GPIO_Port, out2b_Pin, 1);
        counter_out2b_tim2 = 0;
        n2_times_tim2_in2 = 0;
        flag_in2_falling_b_tim2 = 0;
      }
    }
    //-----------------------------------------------------------output 3a
    if (flag_in3_falling_a_tim2 == 1)
    {
      if (counter_out3a_tim2 < B1 / 10)
      {
        HAL_GPIO_WritePin(out3a_GPIO_Port, out3a_Pin, 1);
      }
      if (counter_out3a_tim2 >= B1 / 10 && counter_out3a_tim2 < (B1 + C1) / 10)
      {
        HAL_GPIO_WritePin(out3a_GPIO_Port, out3a_Pin, 0);
      }
      if (counter_out3a_tim2 >= (B1 + C1) / 10 && counter_out3a_tim2 < (B1 + C1 + B2) / 10)
      {
        HAL_GPIO_WritePin(out3a_GPIO_Port, out3a_Pin, 1);
      }
      if (counter_out3a_tim2 >= (B1 + C1 + B2) / 10 && counter_out3a_tim2 < (B1 + C1 + B2 + C1) / 10)
      {
        HAL_GPIO_WritePin(out3a_GPIO_Port, out3a_Pin, 0);
      }
      if (counter_out3a_tim2 == (B1 + C1 + B2 + C1) / 10)
      {
        counter_out3a_tim2 = (B1 + C1) / 10;
        HAL_GPIO_WritePin(out3a_GPIO_Port, out3a_Pin, 1);
        n1_times_tim2_in3++;
      }
      counter_out3a_tim2++;
      if ((n1_times_tim2_in3 == n1_pb - 1 && n1_pb >= 2)|| (n1_pb == 1 && counter_out3a_tim2 == (B1+C1)/ 10) || n1_pb == 0)
      {
				HAL_GPIO_WritePin(out3a_GPIO_Port, out3a_Pin, 1);
        counter_out3a_tim2 = 0;
        n1_times_tim2_in3 = 0;
        flag_in3_falling_a_tim2 = 0;
      }
    }
    //-----------------------------------------------------------output 3b
    if (flag_in3_falling_b_tim2 == 1)
    {
      if (counter_out3b_tim2 < D1 / 10)
      {
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 1);
      }
      if (counter_out3b_tim2 >= D1 / 10 && counter_out3b_tim2 < (D1 + E) / 10)
      {
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 0);
      }
      if (counter_out3b_tim2 >= (D1 + E) / 10 && counter_out3b_tim2 < (B1 + C1 + D2) / 10)
      {
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 1);
      }
      if (counter_out3b_tim2 >= (B1 + C1 + D2) / 10 && counter_out3b_tim2 < (B1 + C1 + D2 + C2) / 10)
      {
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 0);
      }
      if (counter_out3b_tim2 >= (B1 + C1 + D2 + C2) / 10 && counter_out3b_tim2 < (B1 + C1 + B2 + C1 + D2) / 10)
      {
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 1);
      }
      if (counter_out3b_tim2 >= (B1 + C1 + B2 + C1 + D2) / 10 && counter_out3b_tim2 < (B1 + C1 + B2 + C1 + D2 + C2) / 10)
      {
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 0);
      }
      if (counter_out3b_tim2 == (B1 + C1 + B2 + C1 + D2 + C2) / 10)
      {
        counter_out3b_tim2 = (B1 + C1 + D2 + C2) / 10;
        n2_times_tim2_in3++;
        HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 1);
      }

      counter_out3b_tim2++;
      if ((n2_times_tim2_in3 == n2_pb - 1 && n2_pb >=2)|| (counter_out3b_tim2 == (B1+C1+D2+C2)/ 10 && n2_pb == 1) || (n2_pb == 0 && counter_out3b_tim2 == (D1+E)/ 10))
      {
				HAL_GPIO_WritePin(out3b_GPIO_Port, out3b_Pin, 1);
        counter_out3b_tim2 = 0;
        n2_times_tim2_in3 = 0;
        flag_in3_falling_b_tim2 = 0;
      }
    }
    //-----------------------------------------------------------output 4a
    if (flag_in4_falling_a_tim2 == 1)
    {
      if (counter_out4a_tim2 < B1 / 10)
      {
        HAL_GPIO_WritePin(out4a_GPIO_Port, out4a_Pin, 1);
      }
      if (counter_out4a_tim2 >= B1 / 10 && counter_out4a_tim2 < (B1 + C1) / 10)
      {
        HAL_GPIO_WritePin(out4a_GPIO_Port, out4a_Pin, 0);
      }
      if (counter_out4a_tim2 >= (B1 + C1) / 10 && counter_out4a_tim2 < (B1 + C1 + B2) / 10)
      {
        HAL_GPIO_WritePin(out4a_GPIO_Port, out4a_Pin, 1);
      }
      if (counter_out4a_tim2 >= (B1 + C1 + B2) / 10 && counter_out4a_tim2 < (B1 + C1 + B2 + C1) / 10)
      {
        HAL_GPIO_WritePin(out4a_GPIO_Port, out4a_Pin, 0);
      }
      if (counter_out4a_tim2 == (B1 + C1 + B2 + C1) / 10)
      {
        counter_out4a_tim2 = (B1 + C1) / 10;
        HAL_GPIO_WritePin(out4a_GPIO_Port, out4a_Pin, 1);
        n1_times_tim2_in4++;
      }
      counter_out4a_tim2++;
       if ((n1_times_tim2_in4 == n1_pb - 1 && n1_pb >= 2)|| (n1_pb == 1 && counter_out4a_tim2 == (B1+C1)/ 10) || n1_pb == 0)
      {
				HAL_GPIO_WritePin(out4a_GPIO_Port, out4a_Pin, 1);
        counter_out4a_tim2 = 0;
        n1_times_tim2_in4 = 0;
        flag_in4_falling_a_tim2 = 0;
      }
    }
    //-----------------------------------------------------------output 4b
    if (flag_in4_falling_b_tim2 == 1)
    {
      if (counter_out4b_tim2 < D1 / 10)
      {
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 1);
      }
      if (counter_out4b_tim2 >= D1 / 10 && counter_out4b_tim2 < (D1 + E) / 10)
      {
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 0);
      }
      if (counter_out4b_tim2 >= (D1 + E) / 10 && counter_out4b_tim2 < (B1 + C1 + D2) / 10)
      {
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 1);
      }
      if (counter_out4b_tim2 >= (B1 + C1 + D2) / 10 && counter_out4b_tim2 < (B1 + C1 + D2 + C2) / 10)
      {
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 0);
      }
      if (counter_out4b_tim2 >= (B1 + C1 + D2 + C2) / 10 && counter_out4b_tim2 < (B1 + C1 + B2 + C1 + D2) / 10)
      {
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 1);
      }
      if (counter_out4b_tim2 >= (B1 + C1 + B2 + C1 + D2) / 10 && counter_out4b_tim2 < (B1 + C1 + B2 + C1 + D2 + C2) / 10)
      {
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 0);
      }
      if (counter_out4b_tim2 == (B1 + C1 + B2 + C1 + D2 + C2) / 10)
      {
       counter_out4b_tim2 = (B1 + C1 + D2 + C2) / 10;
        n2_times_tim2_in4++;
        HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 1);
      }
      counter_out4b_tim2++;
      if ((n2_times_tim2_in4 == n2_pb - 1 && n2_pb >=2)|| (counter_out4b_tim2 == (B1+C1+D2+C2)/ 10 && n2_pb == 1) || (n2_pb == 0 && counter_out4b_tim2 == (D1+E)/ 10) )
      {
				HAL_GPIO_WritePin(out4b_GPIO_Port, out4b_Pin, 1);
        counter_out4b_tim2 = 0;
        n2_times_tim2_in4 = 0;
        flag_in4_falling_b_tim2 = 0;
      }
    }
  }
}
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
  while (1)
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
