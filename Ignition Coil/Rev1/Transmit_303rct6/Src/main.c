
/**
  ******************************************************************************
    @file           : main.c
    @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
    that are not between comment pairs USER CODE BEGIN and
    USER CODE END. Other portions of this file, whether
    inserted by the user or by software development tools
    are owned by their respective copyright owners.

    COPYRIGHT(c) 2019 STMicroelectronics

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:
      1. Redistributions of source code must retain the above copyright notice,
         this list of conditions and the following disclaimer.
      2. Redistributions in binary form must reproduce the above copyright notice,
         this list of conditions and the following disclaimer in the documentation
         and/or other materials provided with the distribution.
      3. Neither the name of STMicroelectronics nor the names of its contributors
         may be used to endorse or promote products derived from this software
         without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  ******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"

/* USER CODE BEGIN Includes */
#include "lcd.h"
#define pattern_a 1
#define pattern_b 0
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
CanTxMsgTypeDef CanTx;
volatile uint8_t can_tx_int = 0;
volatile uint8_t rotary_value = 0;
volatile uint16_t timer_counter = 0;
volatile uint8_t timer_int = 0;
volatile uint8_t press_counter = 0;
volatile uint8_t review_data_int = 0;

volatile static uint8_t n1_chuc = 0, n1_donvi = 0;
volatile static uint8_t n2_chuc = 0, n2_donvi = 0;
volatile static uint8_t B_nghin = 0, B_tram = 0, B_chuc, B_donvi = 0;
volatile static uint8_t C_nghin = 0, C_tram = 0, C_chuc = 0, C_donvi = 0;
volatile static uint8_t D_nghin = 0, D_tram = 0, D_chuc = 0, D_donvi = 0;

volatile static uint8_t B1_nghin = 0, B1_tram = 0, B1_chuc = 0, B1_donvi = 0;
volatile static uint8_t C1_nghin = 0, C1_tram = 0, C1_chuc = 0, C1_donvi = 0;
volatile static uint8_t B2_nghin = 0, B2_tram = 0, B2_chuc = 0, B2_donvi = 0;

volatile static uint8_t D1_nghin = 0, D1_tram = 0, D1_chuc = 0, D1_donvi = 0;
volatile static uint8_t E_chucnghin = 0, E_nghin = 0, E_tram = 0, E_chuc = 0, E_donvi = 0;

volatile static uint8_t D2_nghin = 0, D2_tram = 0, D2_chuc = 0, D2_donvi = 0;
volatile static uint8_t C2_nghin = 0, C2_tram = 0, C2_chuc = 0, C2_donvi = 0;

uint8_t choose_mode;

uint8_t flag_choose_mode;
uint8_t flag_enable_send_data = 0;
//package 1
uint8_t n1 = 0, n2 = 0;
uint16_t B = 0, C = 0, D = 0;
uint8_t B_H = 0, B_L = 0, C_H = 0, C_L = 0, D_H = 0, D_L = 0;

//package 2
uint16_t B1 = 0, C1 = 0, B2 = 0;
uint8_t B1_H = 0, B1_L = 0, C1_H = 0, C1_L = 0, B2_H = 0, B2_L = 0;

//package 3
uint16_t D1 = 0;
uint32_t E = 0;
uint8_t D1_H = 0, D1_L = 0, E_HH = 0, E_H = 0, E_L = 0;

//package 4
uint16_t D2 = 0, C2 = 0;
uint8_t D2_H = 0, D2_L = 0, C2_H = 0, C2_L = 0;

Lcd_PortType ports[] = {D4_GPIO_Port, D5_GPIO_Port, D6_GPIO_Port, D7_GPIO_Port};
Lcd_PinType pins[] = {D4_Pin, D5_Pin, D6_Pin, D7_Pin};
Lcd_HandleTypeDef lcd;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_TIM2_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void lcd_form_init(void);
void lcd_form1_pattern_a(void);
void lcd_form1_pattern_b(void);
void lcd_form2_pattern_b(void);
void lcd_form1_viewdata(void);
void lcd_form2_viewdata(void);
void lcd_form3_viewdata(void);
void lcd_form4_viewdata(void);
void lcd_form0_viewdata(void);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
    @brief  The application entry point.

    @retval None
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim2);

  hcan.pTxMsg = &CanTx;
  CanTx.RTR = CAN_RTR_DATA;
  CanTx.IDE = CAN_ID_STD;

  lcd = Lcd_create(ports, pins, RS_GPIO_Port, RS_Pin, EN_GPIO_Port, EN_Pin, LCD_4_BIT_MODE);
  Lcd_clear(&lcd);
  lcd_form_init();

  HAL_NVIC_DisableIRQ(send_data_EXTI_IRQn);
  HAL_NVIC_DisableIRQ(review_data_EXTI_IRQn);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    if (press_counter == 0)
    {
      if (HAL_GPIO_ReadPin(choose_mode_GPIO_Port, choose_mode_Pin))
      {
        lcd_form1_pattern_a();
        Lcd_cursor(&lcd, 2, 11);
        if (timer_int)
        {
          Lcd_string(&lcd, "a");
        }
        else
        {
          Lcd_string(&lcd, " ");
        }
      }
      else
      {
        lcd_form1_pattern_b();
        Lcd_cursor(&lcd, 2, 11);
        if (timer_int)
        {
          Lcd_string(&lcd, "b");
        }
        else
        {
          Lcd_string(&lcd, " ");
        }
      }
    }
    //----------------------------------------------------------------1 time----------------------------------------------------------------------------------
    if (press_counter == 1)
    {

      Lcd_cursor(&lcd, 2, 11);
      if (flag_choose_mode == 1)
      {
        Lcd_string(&lcd, "a");
      }
      else
      {
        Lcd_string(&lcd, "b");
      }

      Lcd_cursor(&lcd, 2, 16);
      if (timer_int)
      {
        Lcd_int(&lcd, rotary_value);
      }
      else
      {
        Lcd_string(&lcd, "_");
      }
    }
    //----------------------------------------------------------------2 times
    if (press_counter == 2)
    {
      Lcd_cursor(&lcd, 2, 16);
      Lcd_int(&lcd, n1_chuc);
      Lcd_cursor(&lcd, 2, 17);
      if (timer_int)
      {
        Lcd_int(&lcd, rotary_value);
      }
      else
      {
        Lcd_string(&lcd, "_");
      }
    }
    //----------------------------------------------------------------3 times
    if (press_counter == 3)
    {
      Lcd_cursor(&lcd, 2, 17);
      Lcd_int(&lcd, n1_donvi);
      Lcd_cursor(&lcd, 3, 5);
      if (timer_int)
      {
        Lcd_int(&lcd, rotary_value);
      }
      else
      {
        Lcd_string(&lcd, "_");
      }
    }
    //----------------------------------------------------------------4 times
    if (press_counter == 4)
    {
      Lcd_cursor(&lcd, 3, 5);
      Lcd_int(&lcd, n2_chuc);
      Lcd_cursor(&lcd, 3, 6);
      if (timer_int)
      {
        Lcd_int(&lcd, rotary_value);
      }
      else
      {
        Lcd_string(&lcd, "_");
      }
    }
    //----------------------------------------------------------------5 times
    if (press_counter == 5)
    {
      Lcd_cursor(&lcd, 3, 6);
      Lcd_int(&lcd, n2_donvi);
      Lcd_cursor(&lcd, 3, 16);
      if (timer_int)
      {
        Lcd_int(&lcd, rotary_value);
      }
      else
      {
        Lcd_string(&lcd, "_");
      }
    }
    //----------------------------------------------------------------------------------------------------------pattern a
    //----------------------------------------------------------------6 times
    if (flag_choose_mode == 1 && press_counter >= 6)
    {
      if (press_counter == 6)
      {
        Lcd_cursor(&lcd, 3, 16);
        Lcd_int(&lcd, B_nghin);
        Lcd_cursor(&lcd, 3, 17);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------7 times
      if (press_counter == 7)
      {
        Lcd_cursor(&lcd, 3, 17);
        Lcd_int(&lcd, B_tram);
        Lcd_cursor(&lcd, 3, 18);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------8 times
      if (press_counter == 8)
      {
        Lcd_cursor(&lcd, 3, 18);
        Lcd_int(&lcd, B_chuc);
        Lcd_cursor(&lcd, 3, 19);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------9 times
      if (press_counter == 9)
      {
        Lcd_cursor(&lcd, 3, 19);
        Lcd_int(&lcd, B_donvi);
        Lcd_cursor(&lcd, 4, 5);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------10 times
      if (press_counter == 10)
      {
        Lcd_cursor(&lcd, 4, 5);
        Lcd_int(&lcd, C_nghin);
        Lcd_cursor(&lcd, 4, 6);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------11 times
      if (press_counter == 11)
      {
        Lcd_cursor(&lcd, 4, 6);
        Lcd_int(&lcd, C_tram);
        Lcd_cursor(&lcd, 4, 7);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------12 times
      if (press_counter == 12)
      {
        Lcd_cursor(&lcd, 4, 7);
        Lcd_int(&lcd, C_chuc);
        Lcd_cursor(&lcd, 4, 8);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------13 times
      if (press_counter == 13)
      {
        Lcd_cursor(&lcd, 4, 8);
        Lcd_int(&lcd, C_donvi);
        Lcd_cursor(&lcd, 4, 16);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------14 times
      if (press_counter == 14)
      {
        Lcd_cursor(&lcd, 4, 16);
        Lcd_int(&lcd, D_nghin);
        Lcd_cursor(&lcd, 4, 17);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------15 times
      if (press_counter == 15)
      {
        Lcd_cursor(&lcd, 4, 17);
        Lcd_int(&lcd, D_tram);
        Lcd_cursor(&lcd, 4, 18);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------16 times
      if (press_counter == 16)
      {
        Lcd_cursor(&lcd, 4, 18);
        Lcd_int(&lcd, D_chuc);
        Lcd_cursor(&lcd, 4, 19);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------17 times
      if (press_counter == 17)
      {
        Lcd_cursor(&lcd, 4, 19);
        Lcd_int(&lcd, D_donvi);
				press_counter = 37;
      }
    }
    //----------------------------------------------------------------------------------------------------------pattern b
    //----------------------------------------------------------------6 times
    if (flag_choose_mode == 0 && press_counter >= 6)
    {
      if (press_counter == 6)
      {
        Lcd_cursor(&lcd, 3, 16);
        Lcd_int(&lcd, B1_nghin);
        Lcd_cursor(&lcd, 3, 17);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------7 times
      if (press_counter == 7)
      {
        Lcd_cursor(&lcd, 3, 17);
        Lcd_int(&lcd, B1_tram);
        Lcd_cursor(&lcd, 3, 18);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------8 times
      if (press_counter == 8)
      {
        Lcd_cursor(&lcd, 3, 18);
        Lcd_int(&lcd, B1_chuc);
        Lcd_cursor(&lcd, 3, 19);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------9 times
      if (press_counter == 9)
      {
        Lcd_cursor(&lcd, 3, 19);
        Lcd_int(&lcd, B1_donvi);
        Lcd_cursor(&lcd, 4, 5);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------10 times
      if (press_counter == 10)
      {
        Lcd_cursor(&lcd, 4, 5);
        Lcd_int(&lcd, C1_nghin);
        Lcd_cursor(&lcd, 4, 6);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------11 times
      if (press_counter == 11)
      {
        Lcd_cursor(&lcd, 4, 6);
        Lcd_int(&lcd, C1_tram);
        Lcd_cursor(&lcd, 4, 7);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------12 times
      if (press_counter == 12)
      {
        Lcd_cursor(&lcd, 4, 7);
        Lcd_int(&lcd, C1_chuc);
        Lcd_cursor(&lcd, 4, 8);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------13 times
      if (press_counter == 13)
      {
        Lcd_cursor(&lcd, 4, 8);
        Lcd_int(&lcd, C1_donvi);
        Lcd_cursor(&lcd, 4, 16);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------14 times
      if (press_counter == 14)
      {
        Lcd_cursor(&lcd, 4, 16);
        Lcd_int(&lcd, B2_nghin);
        Lcd_cursor(&lcd, 4, 17);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------15 times
      if (press_counter == 15)
      {
        Lcd_cursor(&lcd, 4, 17);
        Lcd_int(&lcd, B2_tram);
        Lcd_cursor(&lcd, 4, 18);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------16 times
      if (press_counter == 16)
      {
        Lcd_cursor(&lcd, 4, 18);
        Lcd_int(&lcd, B2_chuc);
        Lcd_cursor(&lcd, 4, 19);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------17 times
      if (press_counter == 17)
      {
        Lcd_cursor(&lcd, 4, 19);
        Lcd_int(&lcd, B2_donvi);
      }
      //----------------------------------------------------------------18 times
      if (press_counter == 18)
      {
        lcd_form2_pattern_b();
      }
      //----------------------------------------------------------------19 times
      if (press_counter == 19)
      {
        Lcd_cursor(&lcd, 3, 5);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------20 times
      if (press_counter == 20)
      {
        Lcd_cursor(&lcd, 3, 5);
        Lcd_int(&lcd, D1_nghin);
        Lcd_cursor(&lcd, 3, 6);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------21 times
      if (press_counter == 21)
      {
        Lcd_cursor(&lcd, 3, 6);
        Lcd_int(&lcd, D1_tram);
        Lcd_cursor(&lcd, 3, 7);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------22 times
      if (press_counter == 22)
      {
        Lcd_cursor(&lcd, 3, 7);
        Lcd_int(&lcd, D1_chuc);
        Lcd_cursor(&lcd, 3, 8);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------23 times
      if (press_counter == 23)
      {
        Lcd_cursor(&lcd, 3, 8);
        Lcd_int(&lcd, D1_donvi);
        Lcd_cursor(&lcd, 3, 16);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------24 times
      if (press_counter == 24)
      {
        Lcd_cursor(&lcd, 3, 16);
        Lcd_int(&lcd, E_chucnghin);
        Lcd_cursor(&lcd, 3, 17);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------25 times
      if (press_counter == 25)
      {
        Lcd_cursor(&lcd, 3, 17);
        Lcd_int(&lcd, E_nghin);
        Lcd_cursor(&lcd, 3, 18);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------26 times
      if (press_counter == 26)
      {
        Lcd_cursor(&lcd, 3, 18);
        Lcd_int(&lcd, E_tram);
        Lcd_cursor(&lcd, 3, 19);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------27 times
      if (press_counter == 27)
      {
        Lcd_cursor(&lcd, 3, 19);
        Lcd_int(&lcd, E_chuc);
        Lcd_cursor(&lcd, 3, 20);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------28 times
      if (press_counter == 28)
      {
        Lcd_cursor(&lcd, 3, 20);
        Lcd_int(&lcd, E_donvi);
        Lcd_cursor(&lcd, 4, 5);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------29 times
      if (press_counter == 29)
      {
        Lcd_cursor(&lcd, 4, 5);
        Lcd_int(&lcd, D2_nghin);
        Lcd_cursor(&lcd, 4, 6);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------30 times
      if (press_counter == 30)
      {
        Lcd_cursor(&lcd, 4, 6);
        Lcd_int(&lcd, D2_tram);
        Lcd_cursor(&lcd, 4, 7);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------31 times
      if (press_counter == 31)
      {
        Lcd_cursor(&lcd, 4, 7);
        Lcd_int(&lcd, D2_chuc);
        Lcd_cursor(&lcd, 4, 8);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------32 times
      if (press_counter == 32)
      {
        Lcd_cursor(&lcd, 4, 8);
        Lcd_int(&lcd, D2_donvi);
        Lcd_cursor(&lcd, 4, 16);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------33 times
      if (press_counter == 33)
      {
        Lcd_cursor(&lcd, 4, 16);
        Lcd_int(&lcd, C2_nghin);
        Lcd_cursor(&lcd, 4, 17);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------34 times
      if (press_counter == 34)
      {
        Lcd_cursor(&lcd, 4, 17);
        Lcd_int(&lcd, C2_tram);
        Lcd_cursor(&lcd, 4, 18);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------35 times
      if (press_counter == 35)
      {
        Lcd_cursor(&lcd, 4, 18);
        Lcd_int(&lcd, C2_chuc);
        Lcd_cursor(&lcd, 4, 19);
        if (timer_int)
        {
          Lcd_int(&lcd, rotary_value);
        }
        else
        {
          Lcd_string(&lcd, "_");
        }
      }
      //----------------------------------------------------------------36 times
      if (press_counter == 36)
      {
        Lcd_cursor(&lcd, 4, 19);
        Lcd_int(&lcd, C2_donvi);
				press_counter++;
      }
    }
    //----------------------------------------------------------------37 times
    if (press_counter == 37)
    {
      //package 1
      n1 = 10 * n1_chuc + n1_donvi;
      n2 = 10 * n2_chuc + n2_donvi;
      B  = 1000 * B_nghin + 100 * B_tram + 10 * B_chuc + B_donvi;
      C  = 1000 * C_nghin + 100 * C_tram + 10 * C_chuc + C_donvi;
      D  = 1000 * D_nghin + 100 * D_tram + 10 * D_chuc + D_donvi;

      B_H = B >> 8;
      B_L = B;

      C_H = C >> 8;
      C_L = C;

      D_H = D >> 8;
      D_L = D;

      //package 2

      B1 = 1000 * B1_nghin + 100 * B1_tram + 10 * B1_chuc + B1_donvi;
      C1 = 1000 * C1_nghin + 100 * C1_tram + 10 * C1_chuc + C1_donvi;
      B2 = 1000 * B2_nghin + 100 * B2_tram + 10 * B2_chuc + B2_donvi;

      B1_H = B1 >> 8;
      B1_L = B1;

      C1_H = C1 >> 8;
      C1_L = C1;

      B2_H = B2 >> 8;
      B2_L = B2;

      //package 3

      D1 = 1000 * D1_nghin + 100 * D1_tram + 10 * D1_chuc + D1_donvi;
      E  = 10000 * E_chucnghin + 1000 * E_nghin + 100 * E_tram + 10 * E_chuc + E_donvi;

      D1_H = D1 >> 8;
      D1_L = D1;

      E_HH = E >> 16;
      E_H = E >> 8;
      E_L = E;

      //package 4

      D2 = 1000 * D2_nghin + 100 * D2_tram + 10 * D2_chuc + D2_donvi;
      C2 = 1000 * C2_nghin + 100 * C2_tram + 10 * C2_chuc + C2_donvi;

      D2_H = D2 >> 8;
      D2_L = D2;

      C2_H = C2 >> 8;
      C2_L = C2;
     
		 
			__HAL_GPIO_EXTI_CLEAR_IT(send_data_Pin);
      HAL_NVIC_EnableIRQ(send_data_EXTI_IRQn);
			flag_enable_send_data = 1;
    }
    //----------------------------------------------------------------38 times
    if (can_tx_int == 1 && flag_enable_send_data >= 1)
    {
      flag_enable_send_data = 2;
			
      choose_mode = flag_choose_mode;
      can_tx_int = 0;
      if (choose_mode == pattern_a || (choose_mode == pattern_b && D1 + E < B1 && D2 + C2 < B2))
      {
        //send package 1:8bytes
        CanTx.StdId = 0x101;
        CanTx.DLC = 8;

        CanTx.Data[0] = n1;
        CanTx.Data[1] = n2;
        CanTx.Data[2] = B_H;
        CanTx.Data[3] = B_L;
        CanTx.Data[4] = C_H;
        CanTx.Data[5] = C_L;
        CanTx.Data[6] = D_H;
        CanTx.Data[7] = D_L;
        HAL_CAN_Transmit(&hcan, 10);
        HAL_Delay(10);

        //send package 2:6bytes
        CanTx.StdId = 0x102;
        CanTx.DLC = 6;

        CanTx.Data[0] = B1_H;
        CanTx.Data[1] = B1_L;
        CanTx.Data[2] = C1_H;
        CanTx.Data[3] = C1_L;
        CanTx.Data[4] = B2_H;
        CanTx.Data[5] = B2_L;
        HAL_CAN_Transmit(&hcan, 10);
        HAL_Delay(10);

        //send package 3:5bytes
        CanTx.StdId = 0x103;
        CanTx.DLC = 5;

        CanTx.Data[0] = D1_H;
        CanTx.Data[1] = D1_L;
        CanTx.Data[2] = E_HH;
        CanTx.Data[3] = E_H;
        CanTx.Data[4] = E_L;
        HAL_CAN_Transmit(&hcan, 10);
        HAL_Delay(10);

        //send package 5:5bytes
        CanTx.StdId = 0x104;
        CanTx.DLC = 5;

        CanTx.Data[0] = D2_H;
        CanTx.Data[1] = D2_L;
        CanTx.Data[2] = C2_H;
        CanTx.Data[3] = C2_L;
        CanTx.Data[4] = choose_mode;
        HAL_CAN_Transmit(&hcan, 10);
      }
    }
    //if (flag_enable_send_data == 1)
		if(flag_enable_send_data == 2)
    {
			Lcd_clear(&lcd);
			Lcd_cursor(&lcd, 1, 1);
			Lcd_string(&lcd, "---CONTROLLER BOX---");
			Lcd_cursor(&lcd,2,2);
			if(choose_mode == 1)
			{
				Lcd_string(&lcd,"Pattern: a");
			}
			else
				Lcd_string(&lcd,"Pattern: b");
			
			flag_enable_send_data++;
			
		}
		if (flag_enable_send_data == 3)	
		{
      __HAL_GPIO_EXTI_CLEAR_IT(review_data_Pin);
      HAL_NVIC_EnableIRQ(review_data_EXTI_IRQn);
      if (choose_mode == pattern_a || (choose_mode == pattern_b && D1 + E < B1 && D2 + C2 < B2))
      {
        Lcd_cursor(&lcd, 3, 7);
        if (timer_int)
        {
          Lcd_string(&lcd, "Sent Data");
        }
        else
        {
          Lcd_string(&lcd, "         ");
        }
      }
      else
      {
        Lcd_cursor(&lcd, 3, 1);
        if (timer_int)
        {
          Lcd_string(&lcd, "   Wrong Condition  ");
        }
        else
        {
          Lcd_string(&lcd, "                    ");
        }
      }
    }
    if (review_data_int == 1)
    {
			
      review_data_int = 0;
      switch (flag_enable_send_data % 2)
      {
				case 0: lcd_form1_viewdata(); break;
        case 1: lcd_form0_viewdata(); break;
      }

    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
    @brief System Clock Configuration
    @retval None
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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
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
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

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

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7199;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
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
          Analog
          Input
          Output
          EVENT_OUT
          EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D7_Pin | D6_Pin | D5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, D4_Pin | EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RW_Pin | RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, led1_Pin | led2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : send_data_Pin */
  GPIO_InitStruct.Pin = send_data_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(send_data_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : review_data_Pin */
  GPIO_InitStruct.Pin = review_data_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(review_data_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : channel_b_Pin */
  GPIO_InitStruct.Pin = channel_b_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(channel_b_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : channel_a_Pin */
  GPIO_InitStruct.Pin = channel_a_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(channel_a_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : press_encoder_Pin */
  GPIO_InitStruct.Pin = press_encoder_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(press_encoder_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : D7_Pin D6_Pin D5_Pin */
  GPIO_InitStruct.Pin = D7_Pin | D6_Pin | D5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D4_Pin EN_Pin */
  GPIO_InitStruct.Pin = D4_Pin | EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RW_Pin RS_Pin led1_Pin led2_Pin */
  GPIO_InitStruct.Pin = RW_Pin | RS_Pin | led1_Pin | led2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : choose_mode_Pin */
  GPIO_InitStruct.Pin = choose_mode_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(choose_mode_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_TSC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/* USER CODE BEGIN 4 */
//-----------------------------------------------------------------------------------------------External interrupt
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == send_data_Pin)
  {
    can_tx_int = 1;
  }
  if (GPIO_Pin == channel_a_Pin)
  {
    if (HAL_GPIO_ReadPin(channel_b_GPIO_Port, channel_b_Pin) == 1)
      rotary_value++;
    else
      rotary_value--;
    if (rotary_value == 255)
      rotary_value = 9;
    if (rotary_value == 10)
      rotary_value = 0;
  }
  if (GPIO_Pin == press_encoder_Pin)
  {
    press_counter++;
    switch (press_counter)
    {
      case 1:
        {
          if (HAL_GPIO_ReadPin(choose_mode_GPIO_Port, choose_mode_Pin) == GPIO_PIN_SET)
            flag_choose_mode = 1;
          else
            flag_choose_mode = 0;
          break;
        }
      case 2: n1_chuc = rotary_value; break;
      case 3: n1_donvi = rotary_value; break;
      case 4: n2_chuc = rotary_value; break;
      case 5: n2_donvi = rotary_value; break;
    }
    if (flag_choose_mode == 1)
    {
      switch (press_counter)
      {
        case 6: B_nghin = rotary_value; break;
        case 7: B_tram = rotary_value; break;
        case 8: B_chuc = rotary_value; break;
        case 9: B_donvi = rotary_value; break;
        case 10: C_nghin = rotary_value; break;
        case 11: C_tram = rotary_value; break;
        case 12: C_chuc = rotary_value; break;
        case 13: C_donvi = rotary_value; break;
        case 14: D_nghin = rotary_value; break;
        case 15: D_tram = rotary_value; break;
        case 16: D_chuc = rotary_value; break;
        case 17: D_donvi = rotary_value; break;
				case 37: HAL_NVIC_DisableIRQ(press_encoder_EXTI_IRQn); break;
      }
    }
    else
    {
      switch (press_counter)
      {
        case 6: B1_nghin = rotary_value; break;
        case 7: B1_tram = rotary_value; break;
        case 8: B1_chuc = rotary_value; break;
        case 9: B1_donvi = rotary_value; break;
        case 10: C1_nghin = rotary_value; break;
        case 11: C1_tram = rotary_value; break;
        case 12: C1_chuc = rotary_value; break;
        case 13: C1_donvi = rotary_value; break;
        case 14: B2_nghin = rotary_value; break;
        case 15: B2_tram = rotary_value; break;
        case 16: B2_chuc = rotary_value; break;
        case 17: B2_donvi = rotary_value; break;

        case 20: D1_nghin = rotary_value; break;
        case 21: D1_tram = rotary_value; break;
        case 22: D1_chuc = rotary_value; break;
        case 23: D1_donvi = rotary_value; break;
        case 24: E_chucnghin = rotary_value; break;
        case 25: E_nghin = rotary_value; break;
        case 26: E_tram = rotary_value; break;
        case 27: E_chuc = rotary_value; break;
        case 28: E_donvi = rotary_value; break;
        case 29: D2_nghin = rotary_value; break;
        case 30: D2_tram = rotary_value; break;
        case 31: D2_chuc = rotary_value; break;
        case 32: D2_donvi = rotary_value; break;
        case 33: C2_nghin = rotary_value; break;
        case 34: C2_tram = rotary_value; break;
        case 35: C2_chuc = rotary_value; break;
        case 36: C2_donvi = rotary_value; break;
        case 37: HAL_NVIC_DisableIRQ(press_encoder_EXTI_IRQn); break;
      }
    }
    rotary_value = 0;
  }
  if (GPIO_Pin == review_data_Pin)
  {
    flag_enable_send_data++;
    if (flag_enable_send_data == 254)
    {
      flag_enable_send_data = 4;
    }
    review_data_int = 1;
  }
}
//-----------------------------------------------------------------------------------------------Timer
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == htim2.Instance)
  {
    timer_counter++;
    if (timer_counter == 300)
    {
      timer_int = !timer_int;
      timer_counter = 0;
      HAL_GPIO_TogglePin(led2_GPIO_Port, led2_Pin);
    }
  }
}

//-----------------------------------------------------------------------------------------------Implement Function
void lcd_form_init(void)
{
  Lcd_cursor(&lcd, 1, 1);
  Lcd_string(&lcd, "---CONTROLLER BOX---");
  Lcd_cursor(&lcd, 2, 2);
  Lcd_string(&lcd, "Pattern:");
}
void lcd_form1_pattern_a(void)
{
  Lcd_cursor(&lcd, 2, 13);
  Lcd_string(&lcd, "n1=__   ");

  Lcd_cursor(&lcd, 3, 1);
  Lcd_string(&lcd, " n2=__      B =____ ");

  Lcd_cursor(&lcd, 4, 1);
  Lcd_string(&lcd, " C =____    D =____ ");
}
void lcd_form1_pattern_b(void)
{
  Lcd_cursor(&lcd, 2, 13);
  Lcd_string(&lcd, "n1=__   ");

  Lcd_cursor(&lcd, 3, 1);
  Lcd_string(&lcd, " n2=__      B1=____ ");

  Lcd_cursor(&lcd, 4, 1);
  Lcd_string(&lcd, " C1=____    B2=____ ");
}
void lcd_form2_pattern_b(void)
{
  Lcd_cursor(&lcd, 2, 13);
  Lcd_string(&lcd, "     ");

  Lcd_cursor(&lcd, 3, 1);
  Lcd_string(&lcd, " D1=____    E =_____");

  Lcd_cursor(&lcd, 4, 1);
  Lcd_string(&lcd, " D2=____    C2=____ ");
}

//----------------------------viewdata
void lcd_form0_viewdata(void)
{
	if(flag_choose_mode == pattern_a)
	{
		Lcd_cursor(&lcd, 1, 1);
		Lcd_string(&lcd, "---CONTROLLER BOX---");
		Lcd_cursor(&lcd, 2, 1);
		Lcd_string(&lcd, " Pattern: a n1=     ");
		Lcd_cursor(&lcd, 3, 1);
		Lcd_string(&lcd, " n2=        B =     ");
		Lcd_cursor(&lcd, 4, 1);
		Lcd_string(&lcd, " C =        D =     ");
		Lcd_cursor(&lcd, 2, 16);
		Lcd_int(&lcd, n1);
		Lcd_cursor(&lcd, 3, 5);
		Lcd_int(&lcd, n2);
		Lcd_cursor(&lcd, 3, 16);
		Lcd_int(&lcd, B);
		Lcd_cursor(&lcd, 4, 5);
		Lcd_int(&lcd, C);
		Lcd_cursor(&lcd, 4, 16);
		Lcd_int(&lcd, D);
	}
	else
	{
		Lcd_cursor(&lcd, 1, 1);
		Lcd_string(&lcd, "---CONTROLLER BOX---");
		Lcd_cursor(&lcd, 2, 1);
		Lcd_string(&lcd, " Pattern: b n1=     ");
		Lcd_cursor(&lcd, 3, 1);
		Lcd_string(&lcd, " n2=        B1=     ");
		Lcd_cursor(&lcd, 4, 1);
		Lcd_string(&lcd, " C1=        B2=     ");
		Lcd_cursor(&lcd, 2, 16);
		Lcd_int(&lcd, n1);
		Lcd_cursor(&lcd, 3, 5);
		Lcd_int(&lcd, n2);
		Lcd_cursor(&lcd, 3, 16);
		Lcd_int(&lcd, B1);
		Lcd_cursor(&lcd, 4, 5);
		Lcd_int(&lcd, C1);
		Lcd_cursor(&lcd, 4, 16);
		Lcd_int(&lcd, B2);
	}
}
void lcd_form1_viewdata(void)
{
	if(flag_choose_mode == pattern_a)
  {
		Lcd_cursor(&lcd, 1, 1);
		Lcd_string(&lcd, "---CONTROLLER BOX---");
		Lcd_cursor(&lcd, 2, 1);
		Lcd_string(&lcd, " Pattern: a n1=     ");
		Lcd_cursor(&lcd, 3, 1);
		Lcd_string(&lcd, " n2=        B =     ");
		Lcd_cursor(&lcd, 4, 1);
		Lcd_string(&lcd, " C =        D =     ");
		Lcd_cursor(&lcd, 2, 16);
		Lcd_int(&lcd, n1);
		Lcd_cursor(&lcd, 3, 5);
		Lcd_int(&lcd, n2);
		Lcd_cursor(&lcd, 3, 16);
		Lcd_int(&lcd, B);
		Lcd_cursor(&lcd, 4, 5);
		Lcd_int(&lcd, C);
		Lcd_cursor(&lcd, 4, 16);
		Lcd_int(&lcd, D);
	}
	else
	{
		Lcd_cursor(&lcd, 1, 1);
		Lcd_string(&lcd, "---CONTROLLER BOX---");
		Lcd_cursor(&lcd, 2, 1);
		Lcd_string(&lcd, " Pattern: b         ");
		Lcd_cursor(&lcd, 3, 1);
		Lcd_string(&lcd, " D1=        E =     ");
		Lcd_cursor(&lcd, 4, 1);
		Lcd_string(&lcd, " D2=        C2=     ");
		Lcd_cursor(&lcd, 3, 5);
		Lcd_int(&lcd, D1);
		Lcd_cursor(&lcd, 3, 16);
		Lcd_int(&lcd, E);
		Lcd_cursor(&lcd, 4, 5);
		Lcd_int(&lcd, D2);
		Lcd_cursor(&lcd, 4, 16);
		Lcd_int(&lcd, C2);
	}
}

/* USER CODE END 4 */

/**
    @brief  This function is executed in case of error occurrence.
    @param  file: The file name as string.
    @param  line: The line in file as a number.
    @retval None
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
    @brief  Reports the name of the source file and the source line number
            where the assert_param error has occurred.
    @param  file: pointer to the source file name
    @param  line: assert_param error line source number
    @retval None
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
    @}
*/

/**
    @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
