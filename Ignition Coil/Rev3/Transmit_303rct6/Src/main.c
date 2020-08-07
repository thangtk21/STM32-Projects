
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
#include "lcd.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/


Lcd_PortType ports[] = {D4_GPIO_Port, D5_GPIO_Port, D6_GPIO_Port, D7_GPIO_Port};
Lcd_PinType pins[] = {D4_Pin, D5_Pin, D6_Pin, D7_Pin};
Lcd_HandleTypeDef lcd;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_TIM2_Init(void);
static void MX_I2C2_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void Lcd_goto(uint8_t x,uint8_t y)
{
	Lcd_cursor(&lcd,x,y);
}
void Lcd_write_int(int i)
{
	Lcd_int(&lcd,i);
}

void Lcd_write_string(char * string)
{
	Lcd_string(&lcd,string);
}

void Blink_value()
{
	if (timer_int)
		Lcd_write_int(rotary_value);
  else    
		Lcd_write_string(" ");
}

void lcd_form_init(void)
{
  Lcd_goto(1, 1);
  Lcd_write_string( "---CONTROLLER BOX---");
  Lcd_goto( 2, 2);
  Lcd_write_string( "Pattern:");
}
void lcd_show_pattern_a(void)
{
  Lcd_goto(2,12);
  Lcd_write_string(" n1=");
	Lcd_write_int(n1_chuc_pa);
	Lcd_write_int(n1_donvi_pa);
	
  Lcd_goto(3,1);
  Lcd_write_string(" n2=");
	Lcd_write_int(n2_chuc_pa);
	Lcd_write_int(n2_donvi_pa);
	
	Lcd_goto(3,12);
	Lcd_write_string(" B =");
	Lcd_write_int(B_nghin);
	Lcd_write_int(B_tram);
	Lcd_write_int(B_chuc);
	Lcd_write_int(B_donvi);
	
  Lcd_goto(4,1);
  Lcd_write_string(" C =");
	Lcd_write_int(C_nghin);
	Lcd_write_int(C_tram);
	Lcd_write_int(C_chuc);
	Lcd_write_int(C_donvi);
	
	Lcd_goto(4,12);
	Lcd_write_string(" D =");
	Lcd_write_int(D_nghin);
	Lcd_write_int(D_tram);
	Lcd_write_int(D_chuc);
	Lcd_write_int(D_donvi);
}
void lcd_show_form1_pattern_b(void)
{
  Lcd_goto(2,12);
	Lcd_write_string(" n1=");
	Lcd_write_int(n1_chuc_pb);
	Lcd_write_int(n1_donvi_pb);
	
	Lcd_goto(3,1);
	Lcd_write_string(" n2=");
	Lcd_write_int(n2_chuc_pb);
	Lcd_write_int(n2_donvi_pb);
	Lcd_write_string("  ");
	
	Lcd_goto(3,12);
	Lcd_write_string(" B1=");
	Lcd_write_int(B1_nghin);
	Lcd_write_int(B1_tram);
	Lcd_write_int(B1_chuc);
	Lcd_write_int(B1_donvi);
	Lcd_write_string(" ");
	
	
  Lcd_goto(4,1);
  Lcd_write_string(" C1=");
	Lcd_write_int(C1_nghin);
	Lcd_write_int(C1_tram);
	Lcd_write_int(C1_chuc);
	Lcd_write_int(C1_donvi);
	
	Lcd_goto(4,12);
	Lcd_write_string(" B2=");
	Lcd_write_int(B2_nghin);
	Lcd_write_int(B2_tram);
	Lcd_write_int(B2_chuc);
	Lcd_write_int(B2_donvi);
	Lcd_write_string(" ");
}
void lcd_show_form2_pattern_b(void)
{
  Lcd_goto(2,12);
  Lcd_write_string("      ");
	
  Lcd_goto(3,1);
	Lcd_write_string(" D1=");
	Lcd_write_int(D1_nghin);
	Lcd_write_int(D1_tram);
	Lcd_write_int(D1_chuc);
	Lcd_write_int(D1_donvi);
	
	Lcd_goto(3,13);
	Lcd_write_string("E =");
	Lcd_write_int(E_chucnghin);
	Lcd_write_int(E_nghin);
	Lcd_write_int(E_tram);
	Lcd_write_int(E_chuc);
	Lcd_write_int(E_donvi);
	
	Lcd_goto(4,1);
	Lcd_write_string(" D2=");
	Lcd_write_int(D2_nghin);
	Lcd_write_int(D2_tram);
	Lcd_write_int(D2_chuc);
	Lcd_write_int(D2_donvi);
	
	Lcd_goto(4,12);
	Lcd_write_string(" C2=");
	Lcd_write_int(C2_nghin);
	Lcd_write_int(C2_tram);
	Lcd_write_int(C2_chuc);
	Lcd_write_int(C2_donvi);
	Lcd_write_string(" ");
}


void enable_send()
{
	__HAL_GPIO_EXTI_CLEAR_IT(send_data_Pin);
	HAL_NVIC_EnableIRQ(send_data_EXTI_IRQn);
}
void disable_send()
{
	HAL_NVIC_DisableIRQ(send_data_EXTI_IRQn);
}

void send_pattern_a(uint8_t delay)
{
	CanTx.Data[0] = (uint8_t)1; //XXX
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = (uint8_t)1; // PATTERN
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = n1_pa;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = n2_pa;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = B_H;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = B_L;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = C_H;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = C_L;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = D_H;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = D_L;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = (uint8_t)1; // PATTERN
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = n1_pa;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = n2_pa;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = B_H;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = B_L;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = C_H;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = C_L;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = D_H;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = D_L;
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
}
void send_pattern_b(uint8_t delay)
{
	CanTx.Data[0] = (uint8_t)1; //XXX
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = (uint8_t)0; // PATTERN
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = n1_pb;			
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = n2_pb;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = B1_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = B1_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = C1_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = C1_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);

	CanTx.Data[0] = B2_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = B2_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = D1_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = D1_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = E_HH;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = E_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = E_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = D2_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = D2_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = C2_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = C2_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = (uint8_t)0; // PATTERN
	HAL_CAN_Transmit(&hcan,10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = n1_pb;			
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = n2_pb;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = B1_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = B1_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = C1_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = C1_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);

	CanTx.Data[0] = B2_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = B2_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = D1_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = D1_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = E_HH;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = E_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = E_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = D2_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = D2_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = C2_H;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
	
	CanTx.Data[0] = C2_L;
	HAL_CAN_Transmit(&hcan, 10);
	HAL_Delay(delay);
}


//-----------------------------------------------------------------------------------------------External interrupt
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == press_encoder_Pin)
	{
		static uint8_t start = 0;
		if(start == 0)
		{
			if (HAL_GPIO_ReadPin(choose_mode_GPIO_Port, choose_mode_Pin) == GPIO_PIN_SET)
				flag_choose_mode = pattern_a;
			else
				flag_choose_mode = pattern_b;
		}
		start = 1;
		
		point_lcd_value++;
		
		if(flag_choose_mode == pattern_a)
		{
			if(point_lcd_value == n1_position) 				{D_donvi = rotary_value;enable_send();}
			if(point_lcd_value == n1_chuc_position)		disable_send();
			if(point_lcd_value == n1_donvi_position) 	n1_chuc_pa = rotary_value;
			if(point_lcd_value == n2_position) 				{n1_donvi_pa = rotary_value;enable_send();}
			if(point_lcd_value == n2_chuc_position)		disable_send();
			if(point_lcd_value == n2_donvi_position) 	n2_chuc_pa = rotary_value;
			if(point_lcd_value == B_position) 				{n2_donvi_pa = rotary_value;enable_send();}
			if(point_lcd_value == B_nghin_position)		disable_send();			
			if(point_lcd_value == B_tram_position) 		B_nghin = rotary_value;
			if(point_lcd_value == B_chuc_position) 		B_tram = rotary_value;
			if(point_lcd_value == B_donvi_position) 	B_chuc = rotary_value;
			if(point_lcd_value == C_position) 				{B_donvi = rotary_value;enable_send();}
			if(point_lcd_value == C_nghin_position)		disable_send();
			if(point_lcd_value == C_tram_position) 		C_nghin = rotary_value;
			if(point_lcd_value == C_chuc_position) 		C_tram = rotary_value;
			if(point_lcd_value == C_donvi_position) 	C_chuc = rotary_value;
			if(point_lcd_value == D_position) 				{C_donvi = rotary_value;enable_send();}
			if(point_lcd_value == D_nghin_position)		disable_send();
			if(point_lcd_value == D_tram_position) 		D_nghin = rotary_value;
			if(point_lcd_value == D_chuc_position) 		D_tram = rotary_value;
			if(point_lcd_value == D_donvi_position) 	D_chuc = rotary_value;
			if(point_lcd_value == Finish_input_pattern_a_position)
			{
				point_lcd_value = n1_position;
				D_donvi = rotary_value;
				enable_send();
			}
			rotary_value = 0;
		}
		
		if(flag_choose_mode == pattern_b)
		{
			if(point_lcd_value == n1_position) 				{C2_donvi = rotary_value;enable_send();}
			if(point_lcd_value == n1_chuc_position)		disable_send();
			if(point_lcd_value == n1_donvi_position) 	n1_chuc_pb = rotary_value;
			if(point_lcd_value == n2_position) 				{n1_donvi_pb = rotary_value;enable_send();}
			if(point_lcd_value == n2_chuc_position) 	disable_send();
			if(point_lcd_value == n2_donvi_position) 	n2_chuc_pb = rotary_value;
			if(point_lcd_value == B1_position) 				{n2_donvi_pb = rotary_value;enable_send();}
			if(point_lcd_value == B1_nghin_position)	disable_send();
			if(point_lcd_value == B1_tram_position) 	B1_nghin = rotary_value;
			if(point_lcd_value == B1_chuc_position) 	B1_tram = rotary_value;
			if(point_lcd_value == B1_donvi_position) 	B1_chuc = rotary_value;
			if(point_lcd_value == C1_position) 				{B1_donvi = rotary_value;enable_send();}
			if(point_lcd_value == C1_nghin_position)	disable_send();
			if(point_lcd_value == C1_tram_position) 	C1_nghin = rotary_value;
			if(point_lcd_value == C1_chuc_position) 	C1_tram = rotary_value;
			if(point_lcd_value == C1_donvi_position) 	C1_chuc = rotary_value;
			if(point_lcd_value == B2_position) 				{C1_donvi = rotary_value;enable_send();}
			if(point_lcd_value == B2_nghin_position)	disable_send();
			if(point_lcd_value == B2_tram_position) 	B2_nghin = rotary_value;
			if(point_lcd_value == B2_chuc_position) 	B2_tram = rotary_value;
			if(point_lcd_value == B2_donvi_position) 	B2_chuc = rotary_value;
			if(point_lcd_value == D1_position)				{B2_donvi = rotary_value;enable_send();}
			if(point_lcd_value == D1_tram_position)		D1_nghin = rotary_value;
			if(point_lcd_value == D1_chuc_position)		D1_tram = rotary_value;
			if(point_lcd_value == D1_donvi_position)	D1_chuc = rotary_value;
			if(point_lcd_value == E_position)					{D1_donvi = rotary_value;enable_send();}
			if(point_lcd_value == E_chucnghin_position)	disable_send();
			if(point_lcd_value == E_nghin_position)		E_chucnghin = rotary_value;
			if(point_lcd_value == E_tram_position)		E_nghin = rotary_value;
			if(point_lcd_value == E_chuc_position)		E_tram = rotary_value;
			if(point_lcd_value == E_donvi_position)		E_chuc = rotary_value;
			if(point_lcd_value == D2_position)				{E_donvi = rotary_value;enable_send();}
			if(point_lcd_value == D2_nghin_position)	disable_send();
			if(point_lcd_value == D2_tram_position)		D2_nghin = rotary_value;
			if(point_lcd_value == D2_chuc_position)		D2_tram = rotary_value;
			if(point_lcd_value == D2_donvi_position)	D2_chuc = rotary_value;
			if(point_lcd_value == C2_position)				{D2_donvi = rotary_value;enable_send();}
			if(point_lcd_value == C2_nghin_position)	disable_send();
			if(point_lcd_value == C2_tram_position)		C2_nghin = rotary_value;
			if(point_lcd_value == C2_chuc_position)		C2_tram = rotary_value;
			if(point_lcd_value == C2_donvi_position)	C2_chuc = rotary_value;
			if(point_lcd_value == Finish_input_pattern_b_position)
			{
				enable_send();
				point_lcd_value = n1_position;
				C2_donvi = rotary_value;
			}
			rotary_value = 0;
		}
	}
	
	
  if (GPIO_Pin == channel_a_Pin)
  {
		if(flag_choose_mode == pattern_a)
		{	
			if(point_lcd_value == n1_position ||	point_lcd_value == n2_position || point_lcd_value ==  B_position || point_lcd_value == C_position || point_lcd_value == D_position)
			{
				if (HAL_GPIO_ReadPin(channel_b_GPIO_Port, channel_b_Pin) == 1)	designator_position++;
				else	designator_position--;
				
				if(designator_position == 0)	designator_position = 5;
				if(designator_position == 6) 	designator_position = 1;
				
				if(designator_position == 1)	point_lcd_value = n1_position;
				if(designator_position == 2)	point_lcd_value = n2_position;	
				if(designator_position == 3)	point_lcd_value = B_position; 
				if(designator_position == 4)	point_lcd_value = C_position;
				if(designator_position == 5)	point_lcd_value = D_position; 
			}
			else
			{
				if(point_lcd_value != not_yet_press_encoder_position)		
				{
					if (HAL_GPIO_ReadPin(channel_b_GPIO_Port, channel_b_Pin) == 1)	rotary_value++;
					else	rotary_value--;
					
					if (rotary_value == 255)	rotary_value = 9;
					if (rotary_value == 10)		rotary_value = 0;
				}
			}
		}
		
		if(flag_choose_mode == pattern_b)
		{	
			if(point_lcd_value == n1_position ||	point_lcd_value == n2_position || point_lcd_value ==  B1_position || point_lcd_value == C1_position || point_lcd_value == B2_position ||
			point_lcd_value == D1_position || point_lcd_value == E_position || point_lcd_value == D2_position || point_lcd_value == C2_position)		
			{
				if (HAL_GPIO_ReadPin(channel_b_GPIO_Port, channel_b_Pin) == 1)	
				{
					designator_position++;
					if(designator_position == 6)	flag_B2_to_D1 = 1;
					if(designator_position == 10) flag_C2_to_n1 = 1;
				}
				else	
				{
					designator_position--;
					if(designator_position == 5) flag_D1_to_B2 = 1;
					if(designator_position == 0) flag_n1_to_C2 = 1;
				}
				
				if(designator_position == 0)	designator_position = 9;
				if(designator_position == 10) designator_position = 1;
				
				if(designator_position == 1)	point_lcd_value = n1_position;
				if(designator_position == 2)	point_lcd_value = n2_position;	
				if(designator_position == 3)	point_lcd_value = B1_position; 
				if(designator_position == 4)	point_lcd_value = C1_position;
				if(designator_position == 5)	point_lcd_value = B2_position; 
				
				if(designator_position == 6)	point_lcd_value = D1_position;
				if(designator_position == 7)	point_lcd_value = E_position;
				if(designator_position == 8)	point_lcd_value = D2_position;
				if(designator_position == 9)	point_lcd_value = C2_position;
			}
			else
			{
				if(point_lcd_value != not_yet_press_encoder_position)		
				{
					if (HAL_GPIO_ReadPin(channel_b_GPIO_Port, channel_b_Pin) == 1)	rotary_value++;
					else	rotary_value--;
					
					if (rotary_value == 255)	rotary_value = 9;
					if (rotary_value == 10)		rotary_value = 0;
				}
			}
		}
  }
	
	if (GPIO_Pin == send_data_Pin)
  {	
		first_send++;
		if(first_send > 1) first_send = 2;
		can_tx_int = 1;
  }
	
	if(GPIO_Pin == get_data_Pin)
	{
		flag_get_data = 1;
	}
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
  MX_CAN_Init();
  MX_TIM2_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
	
  HAL_TIM_Base_Start_IT(&htim2);

  hcan.pTxMsg = &CanTx;
	CanTx.StdId = 0x111;
	CanTx.DLC = 1;
  CanTx.RTR = CAN_RTR_DATA;
  CanTx.IDE = CAN_ID_STD;

  lcd = Lcd_create(ports, pins, RS_GPIO_Port, RS_Pin, EN_GPIO_Port, EN_Pin, LCD_4_BIT_MODE);
  Lcd_clear(&lcd);
  lcd_form_init();
	
	HAL_NVIC_DisableIRQ(send_data_EXTI_IRQn);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	
  while (1)
  {
		//Khi chua an gi
		if (point_lcd_value == not_yet_press_encoder_position)
    {
      if(HAL_GPIO_ReadPin(choose_mode_GPIO_Port, choose_mode_Pin))
      {
				lcd_show_pattern_a();
				Lcd_goto(2, 10);
				Lcd_write_string("A");
      }
      else
      {
        lcd_show_form1_pattern_b();
				Lcd_goto(2,10);
				Lcd_write_string("B");
      }
    }
		
		//choose pattern
		if(point_lcd_value == n1_position)
		{
			designator_position = 1;
			
			Lcd_cursor(&lcd, 2, 10);
      if (flag_choose_mode == pattern_a)
      {
        Lcd_write_string("A");
      }
      else
      {
        Lcd_write_string("B");
      }
		}
		
		//-----------------------------------------------------------------------------------------pattern a
		if(point_lcd_value != not_yet_press_encoder_position && flag_choose_mode == pattern_a)
		{
			
			//---------------------------------------------------n1_position
			if(point_lcd_value == n1_position)
			{
				designator_position = 1;
				
				//write D_donvi
				Lcd_goto_D_donvi;
				Lcd_write_int(D_donvi);
				
				//delete con tro D
				Lcd_gotoContro_D;
				Lcd_write_string(" ");
				
				//delete con tro n2
				Lcd_gotoContro_n2;
				Lcd_write_string(" ");
				
				//dua con tro den n1
				Lcd_gotoContro_n1;
				Lcd_write_string(">");
			}
			//---------------------------------------------------n1_chuc_position
			if(point_lcd_value == n1_chuc_position)
			{
				//blink n1_chuc
				rotary_value = n1_chuc_pa;
				while(point_lcd_value == n1_chuc_position)
				{
					Lcd_goto_n1_chuc;
					Blink_value();
				}
			}
			//---------------------------------------------------n1_donvi_position
			if(point_lcd_value == n1_donvi_position)
			{
				//write n1_chuc
				Lcd_goto_n1_chuc;
				Lcd_write_int(n1_chuc_pa);
				
				//blink n1_donvi
				rotary_value = n1_donvi_pa;
				while(point_lcd_value == n1_donvi_position)
				{
					Lcd_goto_n1_donvi;
					Blink_value();
				}
			}
			//---------------------------------------------------n2_position
			if(point_lcd_value == n2_position)
			{
				designator_position = 2;
				
				//write n1_donvi
				Lcd_goto_n1_donvi;
				Lcd_write_int(n1_donvi_pa);
				
				//delete con tro n1
				Lcd_gotoContro_n1;
				Lcd_write_string(" ");
				
				//delete con tro B
				Lcd_gotoContro_B;
				Lcd_write_string(" ");
				
				//dua con tro den n2
				Lcd_gotoContro_n2;
				Lcd_write_string(">");
			}
			//---------------------------------------------------n2_chuc_position
			if(point_lcd_value == n2_chuc_position)
			{
				//blink n2_chuc
				rotary_value = n2_chuc_pa;
				while(point_lcd_value == n2_chuc_position)
				{
					Lcd_goto_n2_chuc;
					Blink_value();
				}
			}
			//---------------------------------------------------n2_donvi_position
			if(point_lcd_value == n2_donvi_position)
			{
				//write n2_chuc
				Lcd_goto_n2_chuc;
				Lcd_write_int(n2_chuc_pa);
				
				//blinkn2_donvi
				rotary_value = n2_donvi_pa;
				while(point_lcd_value == n2_donvi_position)
				{
					Lcd_goto_n2_donvi;
					Blink_value();
				}
			}
			//---------------------------------------------------B_position
			if(point_lcd_value == B_position)
			{
				designator_position = 3;
				
				//write n2_donvi
				Lcd_goto_n2_donvi;
				Lcd_write_int(n2_donvi_pa);
				
				//delete con tro n2
				Lcd_gotoContro_n2;
				Lcd_write_string(" ");
				
				//delete con tro C
				Lcd_gotoContro_C;
				Lcd_write_string(" ");
				
				//dua con tro den B
				Lcd_gotoContro_B;
				Lcd_write_string(">");
			}
			//---------------------------------------------------B_nghin_position
			if(point_lcd_value == B_nghin_position)
			{
				//blink B_nghin
				rotary_value = B_nghin;
				while(point_lcd_value == B_nghin_position)
				{
					Lcd_goto_B_nghin;
					Blink_value();
				}
			}
			//---------------------------------------------------B_tram_position
			if(point_lcd_value == B_tram_position)
			{
				//write B_nghin
				Lcd_goto_B_nghin;
				Lcd_write_int(B_nghin);
				
				//blink B_tram
				rotary_value = B_tram;
				while(point_lcd_value == B_tram_position)
				{
					Lcd_goto_B_tram;
					Blink_value();
				}
			}
			//---------------------------------------------------B_chuc_position
			if(point_lcd_value == B_chuc_position)
			{
				//write B_tram
				Lcd_goto_B_tram;
				Lcd_write_int(B_tram);
				
				//blink B_chuc
				rotary_value = B_chuc;
				while(point_lcd_value == B_chuc_position)
				{
					Lcd_goto_B_chuc;
					Blink_value();
				}
			}
			//---------------------------------------------------B_donvi_position
			if(point_lcd_value == B_donvi_position)
			{
				//write B_chuc
				Lcd_goto_B_chuc;
				Lcd_write_int(B_chuc);
				
				//blink B_donvi
				rotary_value = B_donvi;
				while(point_lcd_value == B_donvi_position)
				{
					Lcd_goto_B_donvi;
					Blink_value();
				}
			}
			//---------------------------------------------------C_position
			if(point_lcd_value == C_position)
			{
				designator_position = 4;
				
				//write B_donvi
				Lcd_goto_B_donvi;
				Lcd_write_int(B_donvi);
				
				//delete con tro B
				Lcd_gotoContro_B;
				Lcd_write_string(" ");
				
				//delete con tro D
				Lcd_gotoContro_D;
				Lcd_write_string(" ");
				
				//dua con tro den C
				Lcd_gotoContro_C;
				Lcd_write_string(">");
			}
			//---------------------------------------------------C_nghin_position
			if(point_lcd_value == C_nghin_position)
			{
				//blink C_nghin
				rotary_value = C_nghin;
				while(point_lcd_value == C_nghin_position)
				{
					Lcd_goto_C_nghin;
					Blink_value();
				}
			}
			//---------------------------------------------------C_tram_position
			if(point_lcd_value == C_tram_position)
			{
				//write C_nghin
				Lcd_goto_C_nghin;
				Lcd_write_int(C_nghin);
				
				//blink C_tram
				rotary_value = C_tram;
				while(point_lcd_value == C_tram_position)
				{
					Lcd_goto_C_tram;
					Blink_value();
				}
			}
			//---------------------------------------------------C_chuc_position
			if(point_lcd_value == C_chuc_position)
			{
				//write C_tram
				Lcd_goto_C_tram;
				Lcd_write_int(C_tram);
				
				//blink C_chuc
				rotary_value = C_chuc;
				while(point_lcd_value == C_chuc_position)
				{
					Lcd_goto_C_chuc;
					Blink_value();
				}
			}
			//---------------------------------------------------C_donvi_position
			if(point_lcd_value == C_donvi_position)
			{
				//write C_chuc
				Lcd_goto_C_chuc;
				Lcd_write_int(C_chuc);
				
				//blink C_donvi
				rotary_value = C_donvi;
				while(point_lcd_value == C_donvi_position)
				{
					Lcd_goto_C_donvi;
					Blink_value();
				}
			}
			//---------------------------------------------------D_position
			if(point_lcd_value == D_position)
			{
				designator_position = 5;
				 
				//write C_donvi
				Lcd_goto_C_donvi;
				Lcd_write_int(C_donvi);
				
				//delete contro C
				Lcd_gotoContro_C;
				Lcd_write_string(" ");
				
				//delete con tro n1
				Lcd_gotoContro_n1;
				Lcd_write_string(" ");
				 
				//dua con tro den D
				Lcd_gotoContro_D;
				Lcd_write_string(">");
			}
			//---------------------------------------------------D_nghin_position
			if(point_lcd_value == D_nghin_position)
			{
				//blink D_nghin
				rotary_value = D_nghin;
				while(point_lcd_value == D_nghin_position)
				{
					Lcd_goto_D_nghin;
					Blink_value();
				}
				
			}
			//---------------------------------------------------D_tram_position
			if(point_lcd_value == D_tram_position)
			{
				//write D_nghin
				Lcd_goto_D_nghin;
				Lcd_write_int(D_nghin);
				
				//blink D_tram
				rotary_value = D_tram;
				while(point_lcd_value == D_tram_position)
				{
					Lcd_goto_D_tram;
					Blink_value();
				}
				
			}
			//---------------------------------------------------D_chuc_position
			if(point_lcd_value == D_chuc_position)
			{
				//write D_tram
				Lcd_goto_D_tram;
				Lcd_write_int(D_tram);
				
				//blink D_chuc
				rotary_value = D_chuc;
				while(point_lcd_value == D_chuc_position)
				{
					Lcd_goto_D_chuc;
					Blink_value();
				}
				
			}
			//---------------------------------------------------D_donvi_position
			if(point_lcd_value == D_donvi_position)
			{
				//write D_chuc
				Lcd_goto_D_chuc;
				Lcd_write_int(D_chuc);
				
				//blink D_donvi
				rotary_value = D_donvi;
				while(point_lcd_value == D_donvi_position)
				{
					Lcd_goto_D_donvi;
					Blink_value();
				}
				
			}
		}
		
		//-----------------------------------------------------------------------------------------pattern b
		if(point_lcd_value != not_yet_press_encoder_position && flag_choose_mode == pattern_b)
		{
			
			//---------------------------------------------------n1_position
			if(point_lcd_value == n1_position)
			{
				if(flag_C2_to_n1 == 1||flag_C2_to_n1_press == 1)
				{
					flag_C2_to_n1 = 0;
					flag_C2_to_n1_press = 0;
					lcd_show_form1_pattern_b();
				}
				
				//delete con tro n2
				Lcd_gotoContro_n2;
				Lcd_write_string(" ");
				
				//dua con tro den n1
				Lcd_gotoContro_n1;
				Lcd_write_string(">");
				
				designator_position = 1;
			}
			//---------------------------------------------------n1_chuc_position
			if(point_lcd_value == n1_chuc_position)
			{
				//blink n1_chuc
				rotary_value = n1_chuc_pb;
				while(point_lcd_value == n1_chuc_position)
				{
					Lcd_goto_n1_chuc;
					Blink_value();
				}
				
			}
			//---------------------------------------------------n1_donvi_position
			if(point_lcd_value == n1_donvi_position)
			{
				//write n1_chuc
				Lcd_goto_n1_chuc;
				Lcd_write_int(n1_chuc_pb);
				
				//blink n1_donvi
				rotary_value =  n1_donvi_pb;
				while(point_lcd_value == n1_donvi_position)
				{
					Lcd_goto_n1_donvi;
					Blink_value();
				}
				
			}
			//---------------------------------------------------n2_position
			if(point_lcd_value == n2_position)
			{
				//write n1_donvi
				Lcd_goto_n1_donvi;
				Lcd_write_int(n1_donvi_pb);
				
				//delete con tro n1
				Lcd_gotoContro_n1;
				Lcd_write_string(" ");
				
				//delete con tro B
				Lcd_gotoContro_B;
				Lcd_write_string(" ");
				
				//dua con tro den n2
				Lcd_gotoContro_n2;
				Lcd_write_string(">");
				
				designator_position = 2;
			}
			//---------------------------------------------------n2_chuc_position
			if(point_lcd_value == n2_chuc_position)
			{
				//blink n2_chuc
				rotary_value = n2_chuc_pb;
				while(point_lcd_value == n2_chuc_position)
				{
					Lcd_goto_n2_chuc;
					Blink_value();
				}
				
			}
			//---------------------------------------------------n2_donvi_position
			if(point_lcd_value == n2_donvi_position)
			{
				//write n2_chuc
				Lcd_goto_n2_chuc;
				Lcd_write_int(n2_chuc_pb);
				
				//blink n2_donvi
				rotary_value = n2_donvi_pb;
				while(point_lcd_value == n2_donvi_position)
				{
					Lcd_goto_n2_donvi;
					Blink_value();
				}
				
			}
			//---------------------------------------------------B1_position
			if(point_lcd_value == B1_position)
			{
				//write n2_donvi
				Lcd_goto_n2_donvi;
				Lcd_write_int(n2_donvi_pb);
				
				//delete con tro n2
				Lcd_gotoContro_n2;
				Lcd_write_string(" ");
				
				//delete con tro C1
				Lcd_gotoContro_C1;
				Lcd_write_string(" ");
				
				//dua con tro den B1
				Lcd_gotoContro_B1;
				Lcd_write_string(">");
				
				designator_position = 3;
			}
			//---------------------------------------------------B1_nghin_position
			if(point_lcd_value == B1_nghin_position)
			{
				//blink B1_nghin
				rotary_value = B1_nghin;
				while(point_lcd_value == B1_nghin_position)
				{
					Lcd_goto_B1_nghin;
					Blink_value();
				}
			}
			//---------------------------------------------------B1_tram_position
			if(point_lcd_value == B1_tram_position)
			{
				//write B1_nghin
				Lcd_goto_B1_nghin;
				Lcd_write_int(B1_nghin);
				
				//blink B1_tram
				rotary_value = B1_tram;
				while(point_lcd_value == B1_tram_position)
				{
					Lcd_goto_B1_tram;
					Blink_value();
				}
				
			}
			//---------------------------------------------------B1_chuc_position
			if(point_lcd_value == B1_chuc_position)
			{
				//write B1_tram
				Lcd_goto_B1_tram;
				Lcd_write_int(B1_tram);
				
				//blink B1_chuc
				rotary_value = B1_chuc;
				while(point_lcd_value == B1_chuc_position)
				{
					Lcd_goto_B1_chuc;
					Blink_value();
				}
				
			}
			//---------------------------------------------------B1_donvi_position
			if(point_lcd_value == B1_donvi_position)
			{
				//write B1_chuc
				Lcd_goto_B1_chuc;
				Lcd_write_int(B1_chuc);
				
				//blink B1_donvi
				rotary_value = B1_donvi;
				while(point_lcd_value == B1_donvi_position)
				{
					Lcd_goto_B1_donvi;
					Blink_value();
				}
				
			}
			//---------------------------------------------------C1_position
			if(point_lcd_value == C1_position)
			{
				//write B1_donvi
				Lcd_goto_B1_donvi;
				Lcd_write_int(B1_donvi);
				
				//delete con tro B1
				Lcd_gotoContro_B1;
				Lcd_write_string(" ");
				
				//delete con tro B2
				Lcd_gotoContro_B2;
				Lcd_write_string(" ");
				
				//dua con tro den C1
				Lcd_gotoContro_C1;
				Lcd_write_string(">");
				
				designator_position = 4;
			}
			//---------------------------------------------------C1_nghin_position
			if(point_lcd_value == C1_nghin_position)
			{
				//blink C1_nghin
				rotary_value = C1_nghin;
				while(point_lcd_value == C1_nghin_position)
				{
					Lcd_goto_C1_nghin;
					Blink_value();
				}
			}
			//---------------------------------------------------C1_tram_position
			if(point_lcd_value == C1_tram_position)
			{
				//write C1_nghin
				Lcd_goto_C1_nghin;
				Lcd_write_int(C1_nghin);
				
				//blink C1_tram
				rotary_value = C1_tram;
				while(point_lcd_value == C1_tram_position)
				{
					Lcd_goto_C1_tram;
					Blink_value();
				}
			}
			//---------------------------------------------------C1_chuc_position
			if(point_lcd_value == C1_chuc_position)
			{
				//write C1_tram
				Lcd_goto_C1_tram;
				Lcd_write_int(C1_tram);
				
				//blink C1_chuc
				rotary_value = C1_chuc;
				while(point_lcd_value == C1_chuc_position)
				{
					Lcd_goto_C1_chuc;
					Blink_value();
				}
				
			}
			//---------------------------------------------------C1_donvi_position
			if(point_lcd_value == C1_donvi_position)
			{
				//write C1_chuc
				Lcd_goto_C1_chuc;
				Lcd_write_int(C1_chuc);
				
				//blink C1_donvi
				rotary_value = C1_donvi;
				while(point_lcd_value == C1_donvi_position)
				{
					Lcd_goto_C1_donvi;
					Blink_value();
				}
			}
			//---------------------------------------------------B2_position
			if(point_lcd_value == B2_position)
			{
				if(flag_D1_to_B2 == 1)
				{
					flag_D1_to_B2 = 0;
					lcd_show_form1_pattern_b();
				}
				//write C1_donvi
				Lcd_goto_C1_donvi;
				Lcd_write_int(C1_donvi);
				
				//delete con tro C1
				Lcd_gotoContro_C1;
				Lcd_write_string(" ");
				
				//dua con tro den B2
				Lcd_gotoContro_B2;
				Lcd_write_string(">");
				
				designator_position = 5;
			}
			//---------------------------------------------------B2_nghin_position
			if(point_lcd_value == B2_nghin_position)
			{
				//blink B2_nghin
				rotary_value = B2_nghin;
				while(point_lcd_value == B2_nghin_position)
				{
					Lcd_goto_B2_nghin;
					Blink_value();
				}
			}
			//---------------------------------------------------B2_tram_position
			if(point_lcd_value == B2_tram_position)
			{
				//write B2_nghin
				Lcd_goto_B2_nghin;
				Lcd_write_int(B2_nghin);
				
				//blink B2_tram
				rotary_value = B2_tram;
				while(point_lcd_value == B2_tram_position)
				{
					Lcd_goto_B2_tram;
					Blink_value();
				}
			}
			//---------------------------------------------------B2_chuc_position
			if(point_lcd_value == B2_chuc_position)
			{
				//write B2_tram
				Lcd_goto_B2_tram;
				Lcd_write_int(B2_tram);
				
				//blink B2_chuc
				rotary_value = B2_chuc;
				while(point_lcd_value == B2_chuc_position)
				{
					Lcd_goto_B2_chuc;
					Blink_value();
				}
			}
			//---------------------------------------------------B2_donvi_position
			if(point_lcd_value == B2_donvi_position)
			{
				flag_B2_to_D1_press = 1;
				
				//write B2_chuc
				Lcd_goto_B2_chuc;
				Lcd_write_int(B2_chuc);
				
				//blink B2_donvi
				rotary_value = B2_donvi;
				while(point_lcd_value == B2_donvi_position)
				{
					Lcd_goto_B2_donvi;
					Blink_value();
				}
			}
			//---------------------------------------------------D1_position
			if(point_lcd_value == D1_position)
			{
				if(flag_B2_to_D1 == 1||flag_B2_to_D1_press == 1)
				{
					flag_B2_to_D1 = 0;
					flag_B2_to_D1_press = 0;
					lcd_show_form2_pattern_b();
				}
				
				//delete con tro E
				Lcd_gotoContro_E;
				Lcd_write_string(" ");
				
				//dua con tro den D1
				Lcd_gotoContro_D1;
				Lcd_write_string(">");
				
				designator_position = 6;
			}
			//---------------------------------------------------D1_nghin_position
			if(point_lcd_value == D1_nghin_position)
			{
				//blink D1_nghin
				rotary_value = D1_nghin;
				while(point_lcd_value == D1_nghin_position)
				{
					Lcd_goto_D1_nghin;
					Blink_value();
				}
			}
			//---------------------------------------------------D1_tram_position
			if(point_lcd_value == D1_tram_position)
			{
				//write D1_nghin
				Lcd_goto_D1_nghin;
				Lcd_write_int(D1_nghin);
				
				//blink D1_tram
				rotary_value = D1_tram;
				while(point_lcd_value == D1_tram_position)
				{
					Lcd_goto_D1_tram;
					Blink_value();
				}
			}
			//---------------------------------------------------D1_chuc_position
			if(point_lcd_value == D1_chuc_position)
			{
				//write D1_tram
				Lcd_goto_D1_tram;
				Lcd_write_int(D1_tram);
				
				//blink B2_chuc
				rotary_value = D1_chuc;
				while(point_lcd_value == D1_chuc_position)
				{
					Lcd_goto_D1_chuc;
					Blink_value();
				}
			}
			//---------------------------------------------------D1_donvi_position
			if(point_lcd_value == D1_donvi_position)
			{
				//write D1_chuc
				Lcd_goto_D1_chuc;
				Lcd_write_int(D1_chuc);
				
				//blink D1_donvi
				rotary_value = D1_donvi;
				while(point_lcd_value == D1_donvi_position)
				{
					Lcd_goto_D1_donvi;
					Blink_value();
				}
			}
			//---------------------------------------------------E_position
			if(point_lcd_value == E_position)
			{
				//write D1_donvi
				Lcd_goto_D1_donvi;
				Lcd_write_int(D1_donvi);
				
				//delete con tro D1
				Lcd_gotoContro_D1;
				Lcd_write_string(" ");
				
				//delete con tro D2
				Lcd_gotoContro_D2;
				Lcd_write_string(" ");
				
				//dua con tro den E
				Lcd_gotoContro_E;
				Lcd_write_string(">");
				
				designator_position = 7;
			}
			//---------------------------------------------------E_chucnghin_position
			if(point_lcd_value == E_chucnghin_position)
			{
				//blink E_chucnghin
				rotary_value = E_chucnghin;
				while(point_lcd_value == E_chucnghin_position)
				{
					Lcd_goto_E_chucnghin;
					Blink_value();
				}
			}
			//---------------------------------------------------E_nghin_position
			if(point_lcd_value == E_nghin_position)
			{
				//write E_chucnghin
				Lcd_goto_E_chucnghin;
				Lcd_write_int(E_chucnghin);
				
				//blink E_nghin
				rotary_value = E_nghin;
				while(point_lcd_value == E_nghin_position)
				{
					Lcd_goto_E_nghin;
					Blink_value();
				}
			}
			//---------------------------------------------------E_tram_position
			if(point_lcd_value == E_tram_position)
			{
				//write E_nghin
				Lcd_goto_E_nghin;
				Lcd_write_int(E_nghin);
				
				//blink E_tram
				rotary_value = E_tram;
				while(point_lcd_value == E_tram_position)
				{
					Lcd_goto_E_tram;
					Blink_value();
				}
			}
			//---------------------------------------------------E_chuc_position
			if(point_lcd_value == E_chuc_position)
			{
				//write E_tram
				Lcd_goto_E_tram;
				Lcd_write_int(E_tram);
				
				//blink E_chuc
				rotary_value = E_chuc;
				while(point_lcd_value == E_chuc_position)
				{
					Lcd_goto_E_chuc;
					Blink_value();
				}
			}
			//---------------------------------------------------E_donvi_position
			if(point_lcd_value == E_donvi_position)
			{
				//write E_chuc
				Lcd_goto_E_chuc;
				Lcd_write_int(E_chuc);
				
				//blink E_donvi
				rotary_value = E_donvi;
				while(point_lcd_value == E_donvi_position)
				{
					Lcd_goto_E_donvi;
					Blink_value();
				}
				
			}
			//---------------------------------------------------D2_position
			if(point_lcd_value == D2_position)
			{
				//write E_donvi
				Lcd_goto_E_donvi;
				Lcd_write_int(E_donvi);
				
				//delete con tro E
				Lcd_gotoContro_E;
				Lcd_write_string(" ");
				
				//delete con tro C2
				Lcd_gotoContro_C2;
				Lcd_write_string(" ");
				
				//dua con tro den D2
				Lcd_gotoContro_D2;
				Lcd_write_string(">");
				
				designator_position = 8;
			}
			//---------------------------------------------------D2_nghin_position
			if(point_lcd_value == D2_nghin_position)
			{
				//blink D2_nghin
				rotary_value = D2_nghin;
				while(point_lcd_value == D2_nghin_position)
				{
					Lcd_goto_D2_nghin;
					Blink_value();
				}
			}
			//---------------------------------------------------D2_tram_position
			if(point_lcd_value == D2_tram_position)
			{
				//write D2_nghin
				Lcd_goto_D2_nghin;
				Lcd_write_int(D2_nghin);
				
				//blink D2_tram
				rotary_value = D2_tram;
				while(point_lcd_value == D2_tram_position)
				{
					Lcd_goto_D2_tram;
					Blink_value();
				}
			}
			//---------------------------------------------------D2_chuc_position
			if(point_lcd_value == D2_chuc_position)
			{
				//write D2_tram
				Lcd_goto_D2_tram;
				Lcd_write_int(D2_tram);
				
				//blink D2_chuc
				rotary_value = D2_chuc;
				while(point_lcd_value == D2_chuc_position)
				{
					Lcd_goto_D2_chuc;
					Blink_value();
				}
			}
			//---------------------------------------------------D2_donvi_position
			if(point_lcd_value == D2_donvi_position)
			{
				//write D2_chuc
				Lcd_goto_D2_chuc;
				Lcd_write_int(D2_chuc);
				
				//blink D2_donvi
				rotary_value = D2_donvi;
				while(point_lcd_value == D2_donvi_position)
				{
					Lcd_goto_D2_donvi;
					Blink_value();
				}
			}
			//---------------------------------------------------C2_position
			if(point_lcd_value == C2_position)
			{
				if(flag_n1_to_C2 == 1)
				{
					flag_n1_to_C2 = 0;
					lcd_show_form2_pattern_b();
				}
				//write D2_donvi
				Lcd_goto_D2_donvi;
				Lcd_write_int(D2_donvi);
				
				//delete con tro D2
				Lcd_gotoContro_D2;
				Lcd_write_string(" ");
				
				//dua con tro den C2
				Lcd_gotoContro_C2;
				Lcd_write_string(">");
				
				designator_position = 9;
			}
			//---------------------------------------------------C2_nghin_position
			if(point_lcd_value == C2_nghin_position)
			{
				//blink C2_nghin
				rotary_value = C2_nghin;
				while(point_lcd_value == C2_nghin_position)
				{
					Lcd_goto_C2_nghin;
					Blink_value();
				}
			}
			//---------------------------------------------------C2_tram_position
			if(point_lcd_value == C2_tram_position)
			{
				//write C2_nghin
				Lcd_goto_C2_nghin;
				Lcd_write_int(C2_nghin);
				
				//blink C2_tram
				rotary_value = C2_tram;
				while(point_lcd_value == C2_tram_position)
				{
					Lcd_goto_C2_tram;
					Blink_value();
				}
			}
			//---------------------------------------------------C2_chuc_position
			if(point_lcd_value == C2_chuc_position)
			{
				//write C2_tram
				Lcd_goto_C2_tram;
				Lcd_write_int(C2_tram);
				
				//blink C2_chuc
				rotary_value = C2_chuc;
				while(point_lcd_value == C2_chuc_position)
				{
					Lcd_goto_C2_chuc;
					Blink_value();
				}
			}
			//---------------------------------------------------C2_donvi_position
			if(point_lcd_value == C2_donvi_position)
			{
				flag_C2_to_n1_press = 1;
				
				//write C2_chuc
				Lcd_goto_C2_chuc;
				Lcd_write_int(C2_chuc);
				
				//blink C2_donvi
				rotary_value = C2_donvi;
				while(point_lcd_value == C2_donvi_position)
				{
					Lcd_goto_C2_donvi;
					Blink_value();
				}
			}
		}
		//-----------------------------------------------------------------------------------------send data
		// nhan send_data
		if(can_tx_int == 1)
		{
			can_tx_int = 0;
			if(flag_choose_mode == pattern_a)
			{
				// Tinh cac parameter
				n1_pa = 10 * n1_chuc_pa + n1_donvi_pa;
				n2_pa = 10 * n2_chuc_pa + n2_donvi_pa;
				B  = 1000 * B_nghin + 100 * B_tram + 10 * B_chuc + B_donvi;
				C  = 1000 * C_nghin + 100 * C_tram + 10 * C_chuc + C_donvi;
				D  = 1000 * D_nghin + 100 * D_tram + 10 * D_chuc + D_donvi;
				
				// Tach cac parameter thanh cac goi
				B_H = B/100;
				B_L = B%100;
				C_H = C/100;
				C_L = C%100;
				D_H = D/100;
				D_L = D%100;
				
				//ghi vao eeprom
				buf_write_pa[0] = n1_pa;
				buf_write_pa[1] = n2_pa;
				buf_write_pa[2] = B_H;
				buf_write_pa[3] = B_L;
				buf_write_pa[4] = C_H;
				buf_write_pa[5] = C_L;
				buf_write_pa[6] = D_H;
				buf_write_pa[7] = D_L;
				HAL_I2C_Mem_Write(&hi2c2,address_24lc08,0,1,buf_write_pa,8,100);
				HAL_Delay(10);
					
				//send data
				if(first_send == 1)
				{
					send_pattern_a(5);
					HAL_Delay(395);
					send_pattern_a(5);
				}
				else
				{
					send_pattern_a(5);
				}

				//hien thi LCD
				Lcd_goto(1,1);
				Lcd_write_string("                    ");
				Lcd_goto(1,1);
				Lcd_write_string("     Data Sent      ");
				HAL_Delay(200);
				Lcd_goto(1,1);
				Lcd_write_string("                    ");
				HAL_Delay(200);
				Lcd_goto(1,1);
				Lcd_write_string("     Data Sent      ");
				HAL_Delay(200);
				Lcd_goto(1,1);
				Lcd_write_string("                    ");
				HAL_Delay(200);
				Lcd_goto(1,1);
				Lcd_write_string("---CONTROLLER BOX---");
		
			}
			if(flag_choose_mode == pattern_b)
			{
				// Tinh cac parameter
				n1_pb = 10 * n1_chuc_pb + n1_donvi_pb;
				n2_pb = 10 * n2_chuc_pb + n2_donvi_pb;
				B1 = 1000 * B1_nghin + 100 * B1_tram + 10 * B1_chuc + B1_donvi;
				C1 = 1000 * C1_nghin + 100 * C1_tram + 10 * C1_chuc + C1_donvi;
				B2 = 1000 * B2_nghin + 100 * B2_tram + 10 * B2_chuc + B2_donvi;
				D1 = 1000 * D1_nghin + 100 * D1_tram + 10 * D1_chuc + D1_donvi;
				E  = 10000 * E_chucnghin + 1000 * E_nghin + 100 * E_tram + 10 * E_chuc + E_donvi;
				D2 = 1000 * D2_nghin + 100 * D2_tram + 10 * D2_chuc + D2_donvi;
				C2 = 1000 * C2_nghin + 100 * C2_tram + 10 * C2_chuc + C2_donvi;

				// Tach cac parameter thanh nhieu byte
				B1_H = B1/100;
				B1_L = B1%100;
				C1_H = C1/100;
				C1_L = C1%100;
				B2_H = B2/100;
				B2_L = B2%100;
				D1_H = D1/100;
				D1_L = D1%100;
				E_HH = E/10000;
				E_H = E/100%100;
				E_L = E%100;
				D2_H = D2/100;
				D2_L = D2%100;
				C2_H = C2/100;
				C2_L = C2%100;
				
				
				//neu sai dieu kien
				if((D1+E >= B1 || D2+C2 >= B2) && (n1_pb!=0 || n2_pb!=0))
				{
					Lcd_goto(1,1);
					Lcd_write_string("                    ");
					Lcd_goto(1,1);
					Lcd_write_string("   Wrong Condition  ");
					HAL_Delay(200);
					Lcd_goto(1,1);
					Lcd_write_string("                    ");
					HAL_Delay(200);
					Lcd_goto(1,1);
					Lcd_write_string("   Wrong Condition  ");
					HAL_Delay(200);
					Lcd_goto(1,1);
					Lcd_write_string("                    ");
					HAL_Delay(200);
					Lcd_goto(1,1);
					Lcd_write_string("---CONTROLLER BOX---");
				}
				else
				{
					//ghi vao eeprom
					
					buf_write_pb1[0] = n1_pb;
					buf_write_pb1[1] = n2_pb;
					buf_write_pb1[2] = B1_H;
					buf_write_pb1[3] = B1_L;
					buf_write_pb1[4] = C1_H;
					buf_write_pb1[5] = C1_L;
					buf_write_pb1[6] = B2_H;
					buf_write_pb1[7] = B2_L;
					HAL_I2C_Mem_Write(&hi2c2,address_24lc08,50,1,buf_write_pb1,8,100);
					HAL_Delay(10);
					
					buf_write_pb2[0] = D1_H;
					buf_write_pb2[1] = D1_L;
					buf_write_pb2[2] = E_HH;
					buf_write_pb2[3] = E_H;
					buf_write_pb2[4] = E_L;
					HAL_I2C_Mem_Write(&hi2c2,address_24lc08,100,1,buf_write_pb2,5,100);
					HAL_Delay(10);
					
					buf_write_pb3[0] = D2_H;
					buf_write_pb3[1] = D2_L;
					buf_write_pb3[2] = C2_H;
					buf_write_pb3[3] = C2_L;
					HAL_I2C_Mem_Write(&hi2c2,address_24lc08,150,1,buf_write_pb3,4,100);
					HAL_Delay(10);
					
					//send data 
						
					if(first_send == 1)
					{
						send_pattern_b(5);
						HAL_Delay(395);
						send_pattern_b(5);
					}
					else
					{
						send_pattern_b(5);
					}
		
					//Hien thi LCD
					Lcd_goto(1,1);
					Lcd_write_string("                    ");
					Lcd_goto(1,1);
					Lcd_write_string("     Data Sent      ");
					HAL_Delay(200);
					Lcd_goto(1,1);
					Lcd_write_string("                    ");
					HAL_Delay(200);
					Lcd_goto(1,1);
					Lcd_write_string("     Data Sent      ");
					HAL_Delay(200);
					Lcd_goto(1,1);
					Lcd_write_string("                    ");
					HAL_Delay(200);
					Lcd_goto(1,1);
					Lcd_write_string("---CONTROLLER BOX---");
				}
			}
		}
		
		//-----------------------------------------------------------------------------------------request data
		//Nhan nut get data
		//Gui sang ben nhan pattern, ben nhan xac dinh pattern nao thi gui lai, doc tu EEPROM
		if(flag_get_data == 1)
		{
			flag_get_data = 0;
			static uint8_t start_get_mode = 0;
			if(start_get_mode == 0)
			{
				start_get_mode = 1;
				flag_choose_mode = (patternTypeDef)READ_PATTERN;
			}
			if(flag_choose_mode == pattern_a)
			{
				//doc ra gia tri cua pattern a tu eeprom va hien thi len lcd
				HAL_I2C_Mem_Read(&hi2c2,address_24lc08,0,1,buf_read_pa,8,100);
				HAL_Delay(10);
				n1_pa = buf_read_pa[0];
				n2_pa = buf_read_pa[1];
				B_H = buf_read_pa[2];
				B_L = buf_read_pa[3];
				C_H = buf_read_pa[4];
				C_L = buf_read_pa[5];
				D_H = buf_read_pa[6];
				D_L = buf_read_pa[7];
				
				n1_chuc_pa = n1_pa/10;
				n1_donvi_pa = n1_pa%10;
				n2_chuc_pa = n2_pa/10;
				n2_donvi_pa = n2_pa%10;
				
				B_nghin = B_H/10;
				B_tram = B_H%10;
				B_chuc = B_L/10;
				B_donvi = B_L%10;
				B = B_nghin*1000+B_tram*100+B_chuc*10+B_donvi;
				
				C_nghin = C_H/10;
				C_tram = C_H%10;
				C_chuc = C_L/10;
				C_donvi = C_L%10;
				C = C_nghin*1000+C_tram*100+C_chuc*10+C_donvi;
				
				D_nghin = D_H/10;
				D_tram = D_H%10;
				D_chuc = D_L/10;
				D_donvi = D_L%10;
				D = D_nghin*1000+D_tram*100+D_chuc*10+D_donvi;
				
				enable_send();
				lcd_show_pattern_a();
				
				Lcd_goto(1,1);
				Lcd_write_string("                    ");
				Lcd_goto(1,1);
				Lcd_write_string("   Data Recalled    ");
				HAL_Delay(200);
				Lcd_goto(1,1);
				Lcd_write_string("                    ");
				HAL_Delay(200);
				Lcd_goto(1,1);
				Lcd_write_string("   Data Recalled    ");
				HAL_Delay(200);
				Lcd_goto(1,1);
				Lcd_write_string("                    ");
				HAL_Delay(200);
				Lcd_goto(1,1);
				Lcd_write_string("---CONTROLLER BOX---");
				
			}
			if(flag_choose_mode == pattern_b)
			{
				//doc ra gia tri cua pattern b tu eeprom va hien thi len lcd
				HAL_I2C_Mem_Read(&hi2c2,address_24lc08,50,1,buf_read_pb1,8,100);
				HAL_Delay(10);
				n1_pb = buf_read_pb1[0];
				n2_pb = buf_read_pb1[1];
				B1_H = buf_read_pb1[2];
				B1_L = buf_read_pb1[3];
				C1_H = buf_read_pb1[4];
				C1_L = buf_read_pb1[5];
				B2_H = buf_read_pb1[6];
				B2_L = buf_read_pb1[7];
				
				HAL_I2C_Mem_Read(&hi2c2,address_24lc08,100,1,buf_read_pb2,5,100);
				HAL_Delay(10);
				D1_H = buf_read_pb2[0];
				D1_L = buf_read_pb2[1];
				E_HH = buf_read_pb2[2];
				E_H = buf_read_pb2[3];
				E_L = buf_read_pb2[4];
				
				HAL_I2C_Mem_Read(&hi2c2,address_24lc08,150,1,buf_read_pb3,4,100);
				HAL_Delay(10);
				D2_H = buf_read_pb3[0];
				D2_L = buf_read_pb3[1];
				C2_H = buf_read_pb3[2];
				C2_L = buf_read_pb3[3];
				
				n1_chuc_pb = n1_pb/10;
				n1_donvi_pb = n1_pb%10;
				n2_chuc_pb = n2_pb/10;
				n2_donvi_pb = n2_pb%10;
				
				B1_nghin = B1_H/10;
				B1_tram = B1_H%10;
				B1_chuc = B1_L/10;
				B1_donvi = B1_L%10;
				B1 = B1_nghin*1000+B1_tram*100+B1_chuc*10+B1_donvi;
				
				C1_nghin = C1_H/10;
				C1_tram = C1_H%10;
				C1_chuc = C1_L/10;
				C1_donvi = C1_L%10;
				C1 = C1_nghin*1000+C1_tram*100+C1_chuc*10+C1_donvi;
				
				B2_nghin = B2_H/10;
				B2_tram = B2_H%10;
				B2_chuc = B2_L/10;
				B2_donvi = B2_L%10;
				B2 = B2_nghin*1000+B2_tram*100+B2_chuc*10+B2_donvi;
				
				D1_nghin = D1_H/10;
				D1_tram = D1_H%10;
				D1_chuc = D1_L/10;
				D1_donvi = D1_L%10;
				D1 = D1_nghin*1000+D1_tram*100+D1_chuc*10+D1_donvi;
				
				E_chucnghin = E_HH;
				E_nghin = E_H/10;
				E_tram = E_H%10;
				E_chuc = E_L/10;
				E_donvi = E_L%10;
				E =E_chucnghin*10000+E_nghin*1000+E_tram*100+E_chuc*10+E_donvi;
				
				D2_nghin = D2_H/10;
				D2_tram = D2_H%10;
				D2_chuc = D2_L/10;
				D2_donvi = D2_L%10;
				D2 = D2_nghin*1000+D2_tram*100+D2_chuc*10+D2_donvi;
				
				C2_nghin = C2_H/10;
				C2_tram = C2_H%10;
				C2_chuc = C2_L/10;
				C2_donvi = C2_L%10;
				C2 = C2_nghin*1000+C2_tram*100+C2_chuc*10+C2_donvi;
				
				enable_send();
				lcd_show_form1_pattern_b();
				
				Lcd_goto(1,1);
				Lcd_write_string("                    ");
				Lcd_goto(1,1);
				Lcd_write_string("   Data Recalled    ");
				HAL_Delay(200);
				Lcd_goto(1,1);
				Lcd_write_string("                    ");
				HAL_Delay(200);
				Lcd_goto(1,1);
				Lcd_write_string("   Data Recalled    ");
				HAL_Delay(200);
				Lcd_goto(1,1);
				Lcd_write_string("                    ");
				HAL_Delay(200);
				Lcd_goto(1,1);
				Lcd_write_string("---CONTROLLER BOX---");
			}
			
			point_lcd_value = n1_position;
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

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C2;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_HSI;
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
  hcan.Init.Prescaler = 100;
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

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7199;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 2999;
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D7_Pin|D6_Pin|D5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, D4_Pin|EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RW_Pin|RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, led1_Pin|led2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : send_data_Pin get_data_Pin */
  GPIO_InitStruct.Pin = send_data_Pin|get_data_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

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
  GPIO_InitStruct.Pin = D7_Pin|D6_Pin|D5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D4_Pin EN_Pin */
  GPIO_InitStruct.Pin = D4_Pin|EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RW_Pin RS_Pin led1_Pin led2_Pin */
  GPIO_InitStruct.Pin = RW_Pin|RS_Pin|led1_Pin|led2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

//-----------------------------------------------------------------------------------------------Timer
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == htim2.Instance)
  {
      timer_int = !timer_int;  
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
