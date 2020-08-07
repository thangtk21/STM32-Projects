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

#define send_data_Pin GPIO_PIN_0
#define send_data_GPIO_Port GPIOC
#define send_data_EXTI_IRQn EXTI0_IRQn
#define get_data_Pin GPIO_PIN_2
#define get_data_GPIO_Port GPIOC
#define get_data_EXTI_IRQn EXTI2_TSC_IRQn
#define channel_b_Pin GPIO_PIN_0
#define channel_b_GPIO_Port GPIOA
#define channel_a_Pin GPIO_PIN_1
#define channel_a_GPIO_Port GPIOA
#define channel_a_EXTI_IRQn EXTI1_IRQn
#define press_encoder_Pin GPIO_PIN_4
#define press_encoder_GPIO_Port GPIOA
#define press_encoder_EXTI_IRQn EXTI4_IRQn
#define D7_Pin GPIO_PIN_5
#define D7_GPIO_Port GPIOA
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOA
#define D5_Pin GPIO_PIN_7
#define D5_GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOC
#define EN_Pin GPIO_PIN_5
#define EN_GPIO_Port GPIOC
#define RW_Pin GPIO_PIN_0
#define RW_GPIO_Port GPIOB
#define RS_Pin GPIO_PIN_1
#define RS_GPIO_Port GPIOB
#define led1_Pin GPIO_PIN_4
#define led1_GPIO_Port GPIOB
#define led2_Pin GPIO_PIN_5
#define led2_GPIO_Port GPIOB
#define choose_mode_Pin GPIO_PIN_8
#define choose_mode_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

#define Lcd_goto_n1_chuc	 	Lcd_goto(2,16)
#define Lcd_goto_n1_donvi		Lcd_goto(2,17)			
#define Lcd_goto_n2_chuc		Lcd_goto(3,5)
#define Lcd_goto_n2_donvi		Lcd_goto(3,6)

#define Lcd_goto_B_nghin		Lcd_goto(3,16)
#define Lcd_goto_B_tram			Lcd_goto(3,17)
#define Lcd_goto_B_chuc			Lcd_goto(3,18)
#define Lcd_goto_B_donvi		Lcd_goto(3,19)
#define Lcd_goto_C_nghin		Lcd_goto(4,5)
#define Lcd_goto_C_tram			Lcd_goto(4,6)
#define Lcd_goto_C_chuc			Lcd_goto(4,7)
#define Lcd_goto_C_donvi		Lcd_goto(4,8)
#define Lcd_goto_D_nghin		Lcd_goto(4,16)
#define Lcd_goto_D_tram			Lcd_goto(4,17)
#define Lcd_goto_D_chuc			Lcd_goto(4,18)
#define Lcd_goto_D_donvi		Lcd_goto(4,19)

#define Lcd_goto_B1_nghin		Lcd_goto(3,16)
#define Lcd_goto_B1_tram		Lcd_goto(3,17)
#define Lcd_goto_B1_chuc		Lcd_goto(3,18)
#define Lcd_goto_B1_donvi		Lcd_goto(3,19)
#define Lcd_goto_C1_nghin		Lcd_goto(4,5)
#define Lcd_goto_C1_tram		Lcd_goto(4,6)
#define Lcd_goto_C1_chuc		Lcd_goto(4,7)
#define Lcd_goto_C1_donvi		Lcd_goto(4,8)
#define Lcd_goto_B2_nghin		Lcd_goto(4,16)
#define Lcd_goto_B2_tram		Lcd_goto(4,17)
#define Lcd_goto_B2_chuc		Lcd_goto(4,18)
#define Lcd_goto_B2_donvi		Lcd_goto(4,19)

#define Lcd_goto_D1_nghin		Lcd_goto(3,5)
#define Lcd_goto_D1_tram		Lcd_goto(3,6)
#define Lcd_goto_D1_chuc 		Lcd_goto(3,7)
#define Lcd_goto_D1_donvi 	Lcd_goto(3,8)
#define Lcd_goto_E_chucnghin	Lcd_goto(3,16)
#define Lcd_goto_E_nghin		Lcd_goto(3,17)
#define Lcd_goto_E_tram			Lcd_goto(3,18)
#define Lcd_goto_E_chuc			Lcd_goto(3,19)
#define Lcd_goto_E_donvi		Lcd_goto(3,20)
#define Lcd_goto_D2_nghin		Lcd_goto(4,5)
#define Lcd_goto_D2_tram		Lcd_goto(4,6)
#define Lcd_goto_D2_chuc		Lcd_goto(4,7)
#define Lcd_goto_D2_donvi		Lcd_goto(4,8)
#define Lcd_goto_C2_nghin		Lcd_goto(4,16)
#define Lcd_goto_C2_tram		Lcd_goto(4,17)
#define Lcd_goto_C2_chuc		Lcd_goto(4,18)
#define Lcd_goto_C2_donvi		Lcd_goto(4,19)

#define Lcd_gotoContro_n1		Lcd_goto(2,12)
#define Lcd_gotoContro_n2		Lcd_goto(3,1)
#define Lcd_gotoContro_B		Lcd_goto(3,12)
#define Lcd_gotoContro_C		Lcd_goto(4,1)
#define Lcd_gotoContro_D		Lcd_goto(4,12)
#define Lcd_gotoContro_B1		Lcd_goto(3,12)
#define Lcd_gotoContro_C1		Lcd_goto(4,1)
#define Lcd_gotoContro_B2		Lcd_goto(4,12)
#define Lcd_gotoContro_D1		Lcd_goto(3,1)
#define Lcd_gotoContro_E		Lcd_goto(3,12)
#define Lcd_gotoContro_D2		Lcd_goto(4,1)
#define Lcd_gotoContro_C2		Lcd_goto(4,12)

#define READ_PATTERN HAL_GPIO_ReadPin(choose_mode_GPIO_Port,choose_mode_Pin)
#define address_24lc08 (0x50<<1)

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
