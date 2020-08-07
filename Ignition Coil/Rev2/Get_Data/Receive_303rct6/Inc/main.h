/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define in1_rising_Pin GPIO_PIN_0
#define in1_rising_GPIO_Port GPIOA
#define in1_rising_EXTI_IRQn EXTI0_IRQn
#define in2_rising_Pin GPIO_PIN_1
#define in2_rising_GPIO_Port GPIOA
#define in2_rising_EXTI_IRQn EXTI1_IRQn
#define in3_rising_Pin GPIO_PIN_2
#define in3_rising_GPIO_Port GPIOA
#define in3_rising_EXTI_IRQn EXTI2_TSC_IRQn
#define in4_rising_Pin GPIO_PIN_3
#define in4_rising_GPIO_Port GPIOA
#define in4_rising_EXTI_IRQn EXTI3_IRQn
#define in4_falling_Pin GPIO_PIN_4
#define in4_falling_GPIO_Port GPIOC
#define in4_falling_EXTI_IRQn EXTI4_IRQn
#define in3_falling_Pin GPIO_PIN_5
#define in3_falling_GPIO_Port GPIOC
#define in3_falling_EXTI_IRQn EXTI9_5_IRQn
#define in2_falling_Pin GPIO_PIN_10
#define in2_falling_GPIO_Port GPIOB
#define in2_falling_EXTI_IRQn EXTI15_10_IRQn
#define in1_falling_Pin GPIO_PIN_11
#define in1_falling_GPIO_Port GPIOB
#define in1_falling_EXTI_IRQn EXTI15_10_IRQn
#define out4b_Pin GPIO_PIN_12
#define out4b_GPIO_Port GPIOB
#define out4a_Pin GPIO_PIN_13
#define out4a_GPIO_Port GPIOB
#define out3b_Pin GPIO_PIN_14
#define out3b_GPIO_Port GPIOB
#define out3a_Pin GPIO_PIN_15
#define out3a_GPIO_Port GPIOB
#define out2b_Pin GPIO_PIN_6
#define out2b_GPIO_Port GPIOC
#define out2a_Pin GPIO_PIN_7
#define out2a_GPIO_Port GPIOC
#define out1b_Pin GPIO_PIN_8
#define out1b_GPIO_Port GPIOC
#define out1a_Pin GPIO_PIN_9
#define out1a_GPIO_Port GPIOC

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

#define pattern_a 1
#define pattern_b 0
#define address_24LC08 0xA0

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
