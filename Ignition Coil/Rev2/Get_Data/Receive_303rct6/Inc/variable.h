#include "stdint.h"
#include "stm32f3xx_hal.h"
uint8_t can_rx_int0 = 0;
uint8_t can_rx_int1 = 0;
uint8_t can_rx_int2 = 0;
uint8_t can_rx_int3 = 0;
uint8_t can_rx_int4 = 0;


uint8_t n1_pa = 0, n2_pa = 0;
uint8_t n1_pb = 0, n2_pb = 0;


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
uint8_t flag_choose_mode;

uint8_t flag_in1_falling_a_tim1 = 0;
uint8_t flag_in1_falling_b_tim1 = 0;
uint8_t flag_in1_rising_a_tim1 = 0;
uint8_t flag_in1_rising_b_tim1 = 0;
uint8_t flag_in1_falling_a_tim2 = 0;
uint8_t flag_in1_falling_b_tim2 = 0;
uint8_t flag_in1_rising_a_tim2 = 0;
uint8_t flag_in1_rising_b_tim2 = 0;

uint8_t flag_in2_falling_a_tim1 = 0;
uint8_t flag_in2_falling_b_tim1 = 0;
uint8_t flag_in2_rising_a_tim1 = 0;
uint8_t flag_in2_rising_b_tim1 = 0;
uint8_t flag_in2_falling_a_tim2 = 0;
uint8_t flag_in2_falling_b_tim2 = 0;
uint8_t flag_in2_rising_a_tim2 = 0;
uint8_t flag_in2_rising_b_tim2 = 0;

uint8_t flag_in3_falling_a_tim1 = 0;
uint8_t flag_in3_falling_b_tim1 = 0;
uint8_t flag_in3_rising_a_tim1 = 0;
uint8_t flag_in3_rising_b_tim1 = 0;
uint8_t flag_in3_falling_a_tim2 = 0;
uint8_t flag_in3_falling_b_tim2 = 0;
uint8_t flag_in3_rising_a_tim2 = 0;
uint8_t flag_in3_rising_b_tim2 = 0;

uint8_t flag_in4_falling_a_tim1 = 0;
uint8_t flag_in4_falling_b_tim1 = 0;
uint8_t flag_in4_rising_a_tim1 = 0;
uint8_t flag_in4_rising_b_tim1 = 0;
uint8_t flag_in4_falling_a_tim2 = 0;
uint8_t flag_in4_falling_b_tim2 = 0;
uint8_t flag_in4_rising_a_tim2 = 0;
uint8_t flag_in4_rising_b_tim2 = 0;



uint16_t counter_out1a_tim1 = 0;
uint16_t counter_out1b_tim1_before = 0;
uint16_t counter_out1b_tim1_after = 0;
uint16_t counter_out1a_tim2 = 0;
uint16_t counter_out1b_tim2 = 0;

uint16_t counter_out2a_tim1 = 0;
uint16_t counter_out2b_tim1_before = 0;
uint16_t counter_out2b_tim1_after = 0;
uint16_t counter_out2a_tim2 = 0;
uint16_t counter_out2b_tim2 = 0;

uint16_t counter_out3a_tim1 = 0;
uint16_t counter_out3b_tim1_before = 0;
uint16_t counter_out3b_tim1_after = 0;
uint16_t counter_out3a_tim2 = 0;
uint16_t counter_out3b_tim2 = 0;

uint16_t counter_out4a_tim1 = 0;
uint16_t counter_out4b_tim1_before = 0;
uint16_t counter_out4b_tim1_after = 0;
uint16_t counter_out4a_tim2 = 0;
uint16_t counter_out4b_tim2 = 0;

uint8_t n1_times_tim1_in1 = 0;
uint8_t n2_times_tim1_in1 = 0;
uint8_t n1_times_tim2_in1 = 0;
uint8_t n2_times_tim2_in1 = 0;

uint8_t n1_times_tim1_in2 = 0;
uint8_t n2_times_tim1_in2 = 0;
uint8_t n1_times_tim2_in2 = 0;
uint8_t n2_times_tim2_in2 = 0;

uint8_t n1_times_tim1_in3 = 0;
uint8_t n2_times_tim1_in3 = 0;
uint8_t n1_times_tim2_in3 = 0;
uint8_t n2_times_tim2_in3 = 0;

uint8_t n1_times_tim1_in4 = 0;
uint8_t n2_times_tim1_in4 = 0;
uint8_t n1_times_tim2_in4 = 0;
uint8_t n2_times_tim2_in4 = 0;

volatile uint8_t flag_request_data = 0;
//variable for eeprom

CanTxMsgTypeDef CanTx;
CanRxMsgTypeDef CanRx;
CAN_FilterConfTypeDef sFilterConfig;

//Variable for eeprom
uint8_t buffer_read1[8];
uint8_t buffer_read2[8];
uint8_t buffer_read3[5];
uint8_t buffer_read4[4];

uint8_t buffer_write1[8];
uint8_t buffer_write2[8];
uint8_t buffer_write3[5];
uint8_t buffer_write4[4];
