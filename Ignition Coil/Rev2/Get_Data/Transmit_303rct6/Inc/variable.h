


#include "stm32f3xx_hal_can.h"
#include "stdint.h"

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

CanTxMsgTypeDef CanTx;
CanRxMsgTypeDef CanRx;
CAN_FilterConfTypeDef sFilterCongif;

volatile uint8_t can_tx_int = 0;
volatile uint8_t rotary_value = 0;
volatile uint16_t timer_counter = 0;
volatile uint8_t timer_int = 0;
volatile uint8_t review_data_int = 0;

volatile static uint8_t n1_chuc_pa = 0, n1_donvi_pa = 0;
volatile static uint8_t n2_chuc_pa = 0, n2_donvi_pa = 0;

volatile static uint8_t n1_chuc_pb = 0, n1_donvi_pb = 0;
volatile static uint8_t n2_chuc_pb = 0, n2_donvi_pb = 0;

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


uint8_t flag_enable_send_data = 0;

uint8_t n1_pa = 0, n2_pa = 0;
uint8_t n1_pb = 0, n2_pb = 0;

uint16_t B = 0, C = 0, D = 0;
uint8_t B_H = 0, B_L = 0, C_H = 0, C_L = 0, D_H = 0, D_L = 0;

uint16_t B1 = 0, C1 = 0, B2 = 0;
uint8_t B1_H = 0, B1_L = 0, C1_H = 0, C1_L = 0, B2_H = 0, B2_L = 0;


uint16_t D1 = 0;
uint32_t E = 0;
uint8_t D1_H = 0, D1_L = 0, E_HH = 0, E_H = 0, E_L = 0;


uint16_t D2 = 0, C2 = 0;
uint8_t D2_H = 0, D2_L = 0, C2_H = 0, C2_L = 0;

uint8_t designator_position = 1;

typedef enum
{
	not_yet_press_encoder_position,
	n1_position,
	n1_chuc_position,
	n1_donvi_position,
	n2_position,
	n2_chuc_position,
	n2_donvi_position,
	B_position,B1_position = 7,
	B_nghin_position,B1_nghin_position = 8,
	B_tram_position,B1_tram_position = 9,
	B_chuc_position,B1_chuc_position = 10,
	B_donvi_position,B1_donvi_position = 11,
	C_position,C1_position = 12,
	C_nghin_position,C1_nghin_position = 13,
	C_tram_position,C1_tram_position = 14,
	C_chuc_position,C1_chuc_position = 15,
	C_donvi_position,C1_donvi_position = 16,
	D_position,B2_position = 17,
	D_nghin_position,B2_nghin_position = 18,
	D_tram_position,B2_tram_position = 19,
	D_chuc_position,B2_chuc_position = 20,
	D_donvi_position,B2_donvi_position = 21,
	D1_position,Finish_input_pattern_a_position = 22,
	D1_nghin_position,
	D1_tram_position,
	D1_chuc_position,
	D1_donvi_position,
	E_position,
	E_chucnghin_position,
	E_nghin_position,
	E_tram_position,
	E_chuc_position,
	E_donvi_position,
	D2_position,
	D2_nghin_position,
	D2_tram_position,
	D2_chuc_position,
	D2_donvi_position,
	C2_position,
	C2_nghin_position,
	C2_tram_position,
	C2_chuc_position,
	C2_donvi_position,
	Finish_input_pattern_b_position
}positionTypeDef;

positionTypeDef point_lcd_value = not_yet_press_encoder_position;

uint8_t flag_B2_to_D1_press = 0;
uint8_t flag_C2_to_n1_press = 0;

volatile uint8_t flag_get_data = 0;

volatile uint8_t flag_B2_to_D1 = 0;
volatile uint8_t flag_D1_to_B2 = 0;
volatile uint8_t flag_n1_to_C2 = 0;
volatile uint8_t flag_C2_to_n1 = 0;
typedef enum
{
	pattern_b,
	pattern_a,
}patternTypeDef;

patternTypeDef flag_choose_mode;
