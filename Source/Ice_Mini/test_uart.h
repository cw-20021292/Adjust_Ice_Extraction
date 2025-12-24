/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _TEST_UART_H_
#define _TEST_UART_H_

//

extern void UARTest_NO_LOAD_Set(void);
extern void eeprom_initial(void);
extern void AT_UART_Communication(void);
extern void UARTest_RUN(void);
extern void calculate_flow_input(void);

extern void start_drain_pump( U16 u16_data );
extern void stop_drain_pump( void );
extern void start_tray_pump( U16 u16_data );
extern void stop_tray_pump( void );
extern void input_ice_tray_micro_sw(void);
extern void check_error_micro_sw_movement(void);
extern void down_tray_motor(void);
extern void up_tray_motor(void);
extern void control_ice_tray(void);
extern void check_error_micro_sw_movement(void);
extern void inverse_direction_time_check(void);

extern void ControlGasSwitch(void);
extern void GasSwitchIce(void);
extern void GasSwitchInit(void);
extern void GasSwitchCold(void);
extern void GasSwitchHotGas(void);
extern void inverse_direction_time_check(void);
extern void BuzStep(U8 mu8Step);
extern void test_uart_rtc(void);
extern void eeprom_test(void);
//extern void InitRtcTime(void);
extern void led_blink_timer(void);
extern void initial_all_data(void);
extern void fnd_front_test_mode_(void);
extern void fnd_uart_test_mode_(void);
extern void on_all_control_led( void );
extern void off_all_control_led( void );
extern void display_test_error(void);
extern void fnd_left_display_test(void);
extern void fnd_right_display_test(void);

extern void WifiKey ( E_WIFI_KEY_T mu8Key );
extern void fnd_left_uart_test(void);
extern void fnd_right_uart_test(void);
extern void run_open_ro_drain(void);
/*extern void ControlMixFlow(void);*/
/*extern void run_increase_flow( U16 mu16_move );*/
extern void comp_off(void);
extern void comp_on(void);
extern void Bldc_Comp_Communication(void);
extern void clear_bldc_buffer(void);
extern void all_breath_stop(void);

extern void set_duty_percent( U8 mu8_number, U8 mu8_percent );
extern void all_duty_100_percent(void);
extern U8 get_ice_mode_comp_rps(void);
extern U8 get_hotgas_mode_comp_rps(void);
extern U8 get_cold_mode_comp_rps(void);
extern void make_test_mode_rgb_color( U8 mu8_color );
extern void play_melody_select_196( void );
extern void play_melody_warning_197( void );
extern void play_melody_setting_on_198( void );
extern void play_melody_setting_off_199( void );
extern void play_voice_test_mode_151( void );
extern void eeprom_test(void);
//extern void tds_out_control(void);

extern void run_decrease_flow( U16 mu16_move );
extern void run_increase_flow( U16 mu16_move );
extern void InitRtcTime(void);
extern void ControlFlow(void);
extern void ProcessRtc(void);







/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
extern TYPE_BYTE          U8FrontTempHundredB;
#define            gu8_front_temp_fnd_hundred                  U8FrontTempHundredB.byte
#define            Bit0_Front_Temp_Fnd_Hundred_1               U8FrontTempHundredB.Bit.b0
#define            Bit1_Front_Temp_Fnd_Hundred_2               U8FrontTempHundredB.Bit.b1
#define            Bit2_Front_Temp_Fnd_Hundred_3               U8FrontTempHundredB.Bit.b2
#define            Bit3_Front_Temp_Fnd_Hundred_4               U8FrontTempHundredB.Bit.b3
#define            Bit4_Front_Temp_Fnd_Hundred_5               U8FrontTempHundredB.Bit.b4
#define            Bit5_Front_Temp_Fnd_Hundred_6               U8FrontTempHundredB.Bit.b5
#define            Bit6_Front_Temp_Fnd_Hundred_7               U8FrontTempHundredB.Bit.b6

extern TYPE_BYTE          U8FrontTempTenB;
#define            gu8_front_temp_fnd_ten                      U8FrontTempTenB.byte
#define            Bit0_Front_Temp_Fnd_Ten_1                   U8FrontTempTenB.Bit.b0
#define            Bit1_Front_Temp_Fnd_Ten_2                   U8FrontTempTenB.Bit.b1
#define            Bit2_Front_Temp_Fnd_Ten_3                   U8FrontTempTenB.Bit.b2
#define            Bit3_Front_Temp_Fnd_Ten_4                   U8FrontTempTenB.Bit.b3
#define            Bit4_Front_Temp_Fnd_Ten_5                   U8FrontTempTenB.Bit.b4
#define            Bit5_Front_Temp_Fnd_Ten_6                   U8FrontTempTenB.Bit.b5
#define            Bit6_Front_Temp_Fnd_Ten_7                   U8FrontTempTenB.Bit.b6

extern TYPE_BYTE          U8FrontTempOneB;
#define            gu8_front_temp_fnd_one                      U8FrontTempOneB.byte
#define            Bit0_Front_Temp_Fnd_One_1                   U8FrontTempOneB.Bit.b0
#define            Bit1_Front_Temp_Fnd_One_2                   U8FrontTempOneB.Bit.b1
#define            Bit2_Front_Temp_Fnd_One_3                   U8FrontTempOneB.Bit.b2
#define            Bit3_Front_Temp_Fnd_One_4                   U8FrontTempOneB.Bit.b3
#define            Bit4_Front_Temp_Fnd_One_5                   U8FrontTempOneB.Bit.b4
#define            Bit5_Front_Temp_Fnd_One_6                   U8FrontTempOneB.Bit.b5
#define            Bit6_Front_Temp_Fnd_One_7                   U8FrontTempOneB.Bit.b6

/////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_BYTE          U8FrontAmountHundredB;
#define            gu8_front_amount_fnd_hundred                U8FrontAmountHundredB.byte
#define            Bit0_Front_Amount_Fnd_Hundred_1             U8FrontAmountHundredB.Bit.b0
#define            Bit1_Front_Amount_Fnd_Hundred_2             U8FrontAmountHundredB.Bit.b1
#define            Bit2_Front_Amount_Fnd_Hundred_3             U8FrontAmountHundredB.Bit.b2
#define            Bit3_Front_Amount_Fnd_Hundred_4             U8FrontAmountHundredB.Bit.b3
#define            Bit4_Front_Amount_Fnd_Hundred_5             U8FrontAmountHundredB.Bit.b4
#define            Bit5_Front_Amount_Fnd_Hundred_6             U8FrontAmountHundredB.Bit.b5
#define            Bit6_Front_Amount_Fnd_Hundred_7             U8FrontAmountHundredB.Bit.b6

extern TYPE_BYTE          U8FrontAmountTenB;
#define            gu8_front_amount_fnd_ten                    U8FrontAmountTenB.byte
#define            Bit0_Front_Amount_Fnd_Ten_1                 U8FrontAmountTenB.Bit.b0
#define            Bit1_Front_Amount_Fnd_Ten_2                 U8FrontAmountTenB.Bit.b1
#define            Bit2_Front_Amount_Fnd_Ten_3                 U8FrontAmountTenB.Bit.b2
#define            Bit3_Front_Amount_Fnd_Ten_4                 U8FrontAmountTenB.Bit.b3
#define            Bit4_Front_Amount_Fnd_Ten_5                 U8FrontAmountTenB.Bit.b4
#define            Bit5_Front_Amount_Fnd_Ten_6                 U8FrontAmountTenB.Bit.b5
#define            Bit6_Front_Amount_Fnd_Ten_7                 U8FrontAmountTenB.Bit.b6

extern TYPE_BYTE          U8FrontAmountOneB;
#define            gu8_front_amount_fnd_one                    U8FrontAmountOneB.byte
#define            Bit0_Front_Amount_Fnd_One_1                 U8FrontAmountOneB.Bit.b0
#define            Bit1_Front_Amount_Fnd_One_2                 U8FrontAmountOneB.Bit.b1
#define            Bit2_Front_Amount_Fnd_One_3                 U8FrontAmountOneB.Bit.b2
#define            Bit3_Front_Amount_Fnd_One_4                 U8FrontAmountOneB.Bit.b3
#define            Bit4_Front_Amount_Fnd_One_5                 U8FrontAmountOneB.Bit.b4
#define            Bit5_Front_Amount_Fnd_One_6                 U8FrontAmountOneB.Bit.b5
#define            Bit6_Front_Amount_Fnd_One_7                 U8FrontAmountOneB.Bit.b6

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

///////////
extern TYPE_BYTE          U8FrontLeftLEDB;
#define            gu8_front_left_led                          U8FrontLeftLEDB.byte
#define            Bit0_Front_Left_Led_Ice_Full_Text           U8FrontLeftLEDB.Bit.b0
#define            Bit1_Front_Left_Led_Ice_Shortae_Text        U8FrontLeftLEDB.Bit.b1
#define            Bit2_Front_Left_Led_UV_Ster_Text            U8FrontLeftLEDB.Bit.b2
#define            Bit3_Front_Left_Led_Hot_Ster_Text           U8FrontLeftLEDB.Bit.b3
#define            Bit4_Front_Left_Led_Sleep_Icon              U8FrontLeftLEDB.Bit.b4
#define            Bit5_Front_Left_Led_Step_Text               U8FrontLeftLEDB.Bit.b5
#define            Bit6_Front_Left_Led_Clock_Colon_Icon        U8FrontLeftLEDB.Bit.b6
#define            Bit7_Front_Left_Led_Celcius_oC_Icon         U8FrontLeftLEDB.Bit.b7

/* LED 제어 BIT 추가 250203 CH.PARK */
extern TYPE_BYTE          U8FrontTextLEDB;
#define            gu8_front_left_led_2                         U8FrontTextLEDB.byte
#define            Bit0_Front_Left_Led_Eff_Faucet_Text          U8FrontTextLEDB.Bit.b0
#define            Bit1_Front_Left_Led_Ice_Faucet_Text          U8FrontTextLEDB.Bit.b1
#define            Bit2_Front_Left_Led_Ice_Tray_Text            U8FrontTextLEDB.Bit.b2
#define            Bit3_Front_Left_Led_Ice_Storage_Box_Text     U8FrontTextLEDB.Bit.b3
#define            Bit4_Front_Right_Led_Filter_Clean_Text       U8FrontTextLEDB.Bit.b4
#define            Bit5_Front_Right_Seg_Dot_Text                U8FrontTextLEDB.Bit.b5

extern TYPE_BYTE          U8FrontRightLEDB;
#define            gu8_front_right_led                         U8FrontRightLEDB.byte
#define            Bit0_Front_Right_Led_Wifi_Icon_White        U8FrontRightLEDB.Bit.b0
#define            Bit1_Front_Right_Led_Wifi_Icon_Blue         U8FrontRightLEDB.Bit.b1
#define            Bit2_Front_Right_Led_Sunny_Icon             U8FrontRightLEDB.Bit.b2
#define            Bit3_Front_Right_Led_Cloud_Icon             U8FrontRightLEDB.Bit.b3
#define            Bit4_Front_Right_Led_Rain_Icon              U8FrontRightLEDB.Bit.b4
#define            Bit5_Front_Right_Led_Percent_Icon           U8FrontRightLEDB.Bit.b5
#define            Bit6_Front_Right_Led_Liter_L_Icon           U8FrontRightLEDB.Bit.b6
#define            Bit7_Front_Right_Led_ml_Icon                U8FrontRightLEDB.Bit.b7


extern TYPE_BYTE          U8FrontTempSettingLEDB;
#define            gu8_front_temp_setting_bar_led              U8FrontTempSettingLEDB.byte
#define            Bit0_Front_Led_Temp_Setting_Bar_1_1         U8FrontTempSettingLEDB.Bit.b0
#define            Bit1_Front_Led_Temp_Setting_Bar_1_2         U8FrontTempSettingLEDB.Bit.b1
#define            Bit2_Front_Led_Temp_Setting_Bar_1_3         U8FrontTempSettingLEDB.Bit.b2
#define            Bit3_Front_Led_Temp_Setting_Bar_1_4         U8FrontTempSettingLEDB.Bit.b3
#define            Bit4_Front_Led_Temp_Setting_Bar_1_5         U8FrontTempSettingLEDB.Bit.b4        // [좌측 BAR 5 아이콘]

extern TYPE_BYTE          U8FrontAmountSettingLEDB;
#define            gu8_front_amount_setting_bar_led            U8FrontAmountSettingLEDB.byte
#define            Bit0_Front_Led_Amount_Setting_Bar_2_1       U8FrontAmountSettingLEDB.Bit.b0
#define            Bit1_Front_Led_Amount_Setting_Bar_2_2       U8FrontAmountSettingLEDB.Bit.b1
#define            Bit2_Front_Led_Amount_Setting_Bar_2_3       U8FrontAmountSettingLEDB.Bit.b2
#define            Bit3_Front_Led_Amount_Setting_Bar_2_4       U8FrontAmountSettingLEDB.Bit.b3        // [좌측 BAR 4 아이콘]
#define            Bit4_Front_Led_Amount_Setting_Bar_Continue  U8FrontAmountSettingLEDB.Bit.b4

extern TYPE_BYTE          U8FrontCenterRecipeLEDB;
#define            gu8_front_center_recipe_led                 U8FrontCenterRecipeLEDB.byte
#define            Bit0_Front_Center_Recipe_Ramen_Text         U8FrontCenterRecipeLEDB.Bit.b0
#define            Bit1_Front_Center_Tea_Text                  U8FrontCenterRecipeLEDB.Bit.b1   // '차' 추가 CH.PARK      // ADDED CH.PARK   // '차' 추가 CH.PARK      // ADDED CH.PARK
#define            Bit2_Front_Center_Recipe_Drip_Coffee_Text   U8FrontCenterRecipeLEDB.Bit.b2
#define            Bit3_Front_Center_MY_1_Text                 U8FrontCenterRecipeLEDB.Bit.b3
#define            Bit4_Front_Center_MY_2_Text                 U8FrontCenterRecipeLEDB.Bit.b4
#define            Bit5_Front_Center_MY_3_Text                 U8FrontCenterRecipeLEDB.Bit.b5

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_BYTE          U8FrontSelectLEDB;
#define            gu8_front_select_led                        U8FrontSelectLEDB.byte
#define            Bit0_Front_Led_Ice_Select                   U8FrontSelectLEDB.Bit.b0
#define            Bit1_Front_Led_Ice_Water_Select             U8FrontSelectLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Select                   U8FrontSelectLEDB.Bit.b2
#define            Bit3_Front_Led_Ambient_Select               U8FrontSelectLEDB.Bit.b3
#define            Bit4_Front_Led_Cold_Select                  U8FrontSelectLEDB.Bit.b4
#define            Bit5_Front_Led_Amount_Select                U8FrontSelectLEDB.Bit.b5
#define            Bit6_Front_Led_My_Select                    U8FrontSelectLEDB.Bit.b6     // [MY] 터치 선택 아이콘

extern TYPE_BYTE          U8FrontSettingLEDB;
#define            gu8_front_setting_led                       U8FrontSettingLEDB.byte
#define            Bit0_Front_Led_Ice_Size                     U8FrontSettingLEDB.Bit.b0
#define            Bit1_Front_Led_Ice_Off                      U8FrontSettingLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Lock_Text                     U8FrontSettingLEDB.Bit.b2
#define            Bit3_Front_Led_Ice_First                    U8FrontSettingLEDB.Bit.b3
#define            Bit4_Front_Led_Cold_Temp                    U8FrontSettingLEDB.Bit.b4
#define            Bit5_Front_Led_Sleep_Mode_Text                   U8FrontSettingLEDB.Bit.b5
#define            Bit6_Front_Led_Cold_Off                     U8FrontSettingLEDB.Bit.b6    // [냉수OFF] 터치 선택 아이콘



/* LED 제어 BIT 추가 250203 CH.PARK */
extern TYPE_BYTE          U8FrontSettingLEDB_2;
#define            gu8_front_setting_led_2                     U8FrontSettingLEDB_2.byte
#define            Bit0_Front_Led_Ice_Lock                     U8FrontSettingLEDB_2.Bit.b0
#define            Bit1_Front_Led_All_Lock                     U8FrontSettingLEDB_2.Bit.b1
#define            Bit2_Front_Led_Icon_Led_Ice_Locker          U8FrontSettingLEDB_2.Bit.b2      // [얼음 자물쇠 아이콘]
#define            Bit3_Front_Led_Icon_Led_Hot_Locker          U8FrontSettingLEDB_2.Bit.b3      // [온수 자물쇠 아이콘]
#define            Bit4_Front_Led_Icon_Fast_Ice                U8FrontSettingLEDB_2.Bit.b4      // LPP 추가 : 빠른제빙 설정 아이콘
#define            Bit5_Front_Led_Icon_Comp_Blue               U8FrontSettingLEDB_2.Bit.b5      // LPP 추가 : COMP 블루 LED
#define            Bit6_Front_Led_Icon_Comp_White              U8FrontSettingLEDB_2.Bit.b6      // COMP 화이트 LED

extern TYPE_BYTE          U8FrontUnderTextLEDB;
#define            gu8_front_under_text_led                    U8FrontUnderTextLEDB.byte
#define            Bit0_Front_Under_Txt_Led_Ice_Large          U8FrontUnderTextLEDB.Bit.b0
#define            Bit1_Front_Under_Txt_Led_Ice_Center_bar     U8FrontUnderTextLEDB.Bit.b1
#define            Bit2_Front_Under_Txt_Led_Ice_Small          U8FrontUnderTextLEDB.Bit.b2
#define            Bit3_Front_Under_Txt_Led_Cold_High          U8FrontUnderTextLEDB.Bit.b3
#define            Bit4_Front_Under_Txt_Led_Cold_Center_Bar    U8FrontUnderTextLEDB.Bit.b4
#define            Bit5_Front_Under_Txt_Led_Cold_Low           U8FrontUnderTextLEDB.Bit.b5
#define            Bit6_Front_Under_Txt_Led_Ice_Normal         U8FrontUnderTextLEDB.Bit.b6    // X
#define            Bit7_Front_Under_Txt_Led_Ice_Piece          U8FrontUnderTextLEDB.Bit.b7    // X


extern TYPE_BYTE          U8FrontUnderIconLEDB;
#define            gu8_front_under_icon_led                         U8FrontUnderIconLEDB.byte
#define            Bit1_Front_Under_Ice_Inner_Blue_Extract          U8FrontUnderIconLEDB.Bit.b0     // 얼음추출부 안쪽 블루 LED
#define            Bit1_Front_Under_Ice_Inner_White_Extract         U8FrontUnderIconLEDB.Bit.b1     // 얼음추출부 안쪽 화이트 LED
#define            Bit2_Front_Under_Ice_Outer_Blue_Extract          U8FrontUnderIconLEDB.Bit.b2     // 얼음추출부 바깥쪽 블루 LED
#define            Bit3_Front_Under_Ice_Outer_White_Extract         U8FrontUnderIconLEDB.Bit.b3     // 얼음추출부 바깥쪽 화이트 LED
#define            Bit4_Front_Under_Water_White_Extract             U8FrontUnderIconLEDB.Bit.b4     // 냉온정추출부 화이트 LED
#define            Bit5_Front_Under_Led_Welcome                     U8FrontUnderIconLEDB.Bit.b5     // WELCOME 1 LED
#define            Bit6_Front_Under_Led_Welcome_2                   U8FrontUnderIconLEDB.Bit.b6     // WELCOME 2 LED CH.PARK ADDED 250204

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
extern TYPE_DIMMING       U8DimmingPercentNo1;
#define            gu8_dimming_set_one                         U8DimmingPercentNo1.byte
#define            bit_0_3_ice_select                          U8DimmingPercentNo1.nibble.b0_3
#define            bit_4_7_ice_water_select                    U8DimmingPercentNo1.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo2;
#define            gu8_dimming_set_two                         U8DimmingPercentNo2.byte
#define            bit_0_3_hot_select                          U8DimmingPercentNo2.nibble.b0_3
#define            bit_4_7_ambient_select                      U8DimmingPercentNo2.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo3;
#define            gu8_dimming_set_three                       U8DimmingPercentNo3.byte
#define            bit_0_3_cold_select                         U8DimmingPercentNo3.nibble.b0_3
#define            bit_4_7_amount_select                       U8DimmingPercentNo3.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo4;
#define            gu8_dimming_set_four                        U8DimmingPercentNo4.byte
#define            bit_0_3_setting_ice_size                    U8DimmingPercentNo4.nibble.b0_3
#define            bit_4_7_setting_ice_off                     U8DimmingPercentNo4.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo5;
#define            gu8_dimming_set_five                        U8DimmingPercentNo5.byte
#define            bit_0_3_setting_ice_first                   U8DimmingPercentNo5.nibble.b0_3
#define            bit_4_7_setting_cold_temp                   U8DimmingPercentNo5.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo6;
#define            gu8_dimming_set_six                         U8DimmingPercentNo6.byte
#define            bit_0_3_setting_sleep_mode                  U8DimmingPercentNo6.nibble.b0_3
#define            bit_4_7_setting_ice_lock                    U8DimmingPercentNo6.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo7;
#define            gu8_dimming_set_seven                       U8DimmingPercentNo7.byte
#define            bit_0_3_all_lock                            U8DimmingPercentNo7.nibble.b0_3
#define            bit_4_7_hot_lock                            U8DimmingPercentNo7.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo8;
#define            gu8_dimming_set_eight                       U8DimmingPercentNo8.byte
#define            bit_0_3_ice_full_txt                        U8DimmingPercentNo8.nibble.b0_3
#define            bit_4_7_UV_ster_txt                         U8DimmingPercentNo8.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo9;
#define            gu8_dimming_set_nine                        U8DimmingPercentNo9.byte
#define            bit_0_3_hot_ster_txt                        U8DimmingPercentNo9.nibble.b0_3
#define            bit_4_7_sleep_icon                          U8DimmingPercentNo9.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo10;
#define            gu8_dimming_set_ten                         U8DimmingPercentNo10.byte
#define            bit_0_3_step_txt                            U8DimmingPercentNo10.nibble.b0_3
#define            bit_4_7_clock_colon_icon                    U8DimmingPercentNo10.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo11;
#define            gu8_dimming_set_eleven                      U8DimmingPercentNo11.byte
#define            bit_0_3_oC_icon                             U8DimmingPercentNo11.nibble.b0_3
#define            bit_4_7_fast_ice_icon                       U8DimmingPercentNo11.nibble.b4_7
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo12;
#define            gu8_dimming_set_twelve                      U8DimmingPercentNo12.byte
#define            bit_0_3_wifi_white_icon                     U8DimmingPercentNo12.nibble.b0_3
#define            bit_4_7_my_select                      U8DimmingPercentNo12.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo13;
#define            gu8_dimming_set_thirteen                    U8DimmingPercentNo13.byte
#define            bit_0_3_sunny_icon                          U8DimmingPercentNo13.nibble.b0_3
#define            bit_4_7_cloud_icon                          U8DimmingPercentNo13.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo14;
#define            gu8_dimming_set_fourteen                    U8DimmingPercentNo14.byte
#define            bit_0_3_rain_icon                           U8DimmingPercentNo14.nibble.b0_3
#define            bit_4_7_percent_icon                        U8DimmingPercentNo14.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo15;
#define            gu8_dimming_set_fifteen                     U8DimmingPercentNo15.byte
#define            bit_0_3_liter_txt                           U8DimmingPercentNo15.nibble.b0_3
#define            bit_4_7_ml_txt                              U8DimmingPercentNo15.nibble.b4_7
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo16;
#define            gu8_dimming_set_sixteen                     U8DimmingPercentNo16.byte
#define            bit_0_3_temp_bar_1_1                        U8DimmingPercentNo16.nibble.b0_3
#define            bit_4_7_temp_bar_1_2                        U8DimmingPercentNo16.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo17;
#define            gu8_dimming_set_seventeen                   U8DimmingPercentNo17.byte
#define            bit_0_3_temp_bar_1_3                        U8DimmingPercentNo17.nibble.b0_3
#define            bit_4_7_temp_bar_1_4                        U8DimmingPercentNo17.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo18;
#define            gu8_dimming_set_eighteen                    U8DimmingPercentNo18.byte
#define            bit_0_3_amount_bar_2_1                      U8DimmingPercentNo18.nibble.b0_3
#define            bit_4_7_amount_bar_2_2                      U8DimmingPercentNo18.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo19;
#define            gu8_dimming_set_nineteen                    U8DimmingPercentNo19.byte
#define            bit_0_3_amount_bar_2_3                      U8DimmingPercentNo19.nibble.b0_3
#define            bit_4_7_amount_bar_continue                 U8DimmingPercentNo19.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo20;
#define            gu8_dimming_set_twenty                      U8DimmingPercentNo20.byte
#define            bit_0_3_recipe_ramen_txt                    U8DimmingPercentNo20.nibble.b0_3
#define            bit_4_7_recipe_drip_coffee_txt              U8DimmingPercentNo20.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo21;
#define            gu8_dimming_set_twenty_one                  U8DimmingPercentNo21.byte
#define            bit_0_3_MY_1_txt                            U8DimmingPercentNo21.nibble.b0_3
#define            bit_4_7_MY_2_txt                            U8DimmingPercentNo21.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo22;
#define            gu8_dimming_set_twenty_two                  U8DimmingPercentNo22.byte
#define            bit_0_3_ice_large_txt                       U8DimmingPercentNo22.nibble.b0_3
#define            bit_4_7_ice_center_bar                      U8DimmingPercentNo22.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo23;
#define            gu8_dimming_set_twenty_three                U8DimmingPercentNo23.byte
#define            bit_0_3_ice_small_txt                       U8DimmingPercentNo23.nibble.b0_3
#define            bit_4_7_ice_normal_txt                       U8DimmingPercentNo23.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo24;
#define            gu8_dimming_set_twenty_four                 U8DimmingPercentNo24.byte
#define            bit_0_3_cold_high_txt                       U8DimmingPercentNo24.nibble.b0_3
#define            bit_4_7_cold_center_bar                     U8DimmingPercentNo24.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo25;
#define            gu8_dimming_set_twenty_five                 U8DimmingPercentNo25.byte
#define            bit_0_3_cold_low_txt                        U8DimmingPercentNo25.nibble.b0_3
#define            bit_4_7_ice_piece_txt                       U8DimmingPercentNo25.nibble.b4_7
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo26;
#define            gu8_dimming_set_twenty_six                  U8DimmingPercentNo26.byte
#define            bit_0_3_ice_lock_icon                       U8DimmingPercentNo26.nibble.b0_3
#define            bit_4_7_hot_lock_icon                       U8DimmingPercentNo26.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo27;
#define            gu8_dimming_set_twenty_seven                U8DimmingPercentNo27.byte
#define            bit_0_3_comp_operation_dot                  U8DimmingPercentNo27.nibble.b0_3
#define            bit_4_7_comp_blue_dot                       U8DimmingPercentNo27.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo28;
#define            gu8_dimming_set_twenty_eight                U8DimmingPercentNo28.byte
#define            bit_0_3_ice_extract                         U8DimmingPercentNo28.nibble.b0_3
#define            bit_4_7_water_extract                       U8DimmingPercentNo28.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo29;
#define            gu8_dimming_set_twenty_nine                 U8DimmingPercentNo29.byte
#define            bit_0_3_welcome_led                         U8DimmingPercentNo29.nibble.b0_3
#define            bit_4_7_ice_blue_inner                      U8DimmingPercentNo29.nibble.b4_7
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo30;
#define            gu8_dimming_set_thirty                      U8DimmingPercentNo30.byte
#define            bit_0_3_amount_bar_2_4                      U8DimmingPercentNo30.nibble.b0_3
#define            bit_4_7_temp_bar_1_5                        U8DimmingPercentNo30.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo31;
#define            gu8_dimming_set_thirty_one                 U8DimmingPercentNo31.byte
#define            bit_0_3_Ice_Shortage                       U8DimmingPercentNo31.nibble.b0_3
#define            bit_4_7_eff_Faucet_Text                    U8DimmingPercentNo31.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo32;
#define            gu8_dimming_set_thirty_two                  U8DimmingPercentNo32.byte
#define            bit_0_3_Ice_Faucet                          U8DimmingPercentNo32.nibble.b0_3
#define            bit_4_7_Ice_Tray                            U8DimmingPercentNo32.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo33;
#define            gu8_dimming_set_thirty_three                  U8DimmingPercentNo33.byte
#define            bit_0_3_Ice_Storage_Box                       U8DimmingPercentNo33.nibble.b0_3
#define            bit_4_7_Filter_Clean                       U8DimmingPercentNo33.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo34;
#define            gu8_dimming_set_thirty_four                  U8DimmingPercentNo34.byte
#define            bit_0_3_Right_Seg_Dot                       U8DimmingPercentNo34.nibble.b0_3
#define            bit_4_7_Tea_Text                       U8DimmingPercentNo34.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo35;
#define            gu8_dimming_set_thirty_five                  U8DimmingPercentNo35.byte
#define            bit_0_3_My_3_txt                       U8DimmingPercentNo35.nibble.b0_3
#define            bit_4_7_Cold_Off                       U8DimmingPercentNo35.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo36;
#define            gu8_dimming_set_thirty_six                  U8DimmingPercentNo36.byte
#define            bit_0_3_Ice_Water_Extract                   U8DimmingPercentNo36.nibble.b0_3
#define            bit_4_7_Welcome_2                        U8DimmingPercentNo36.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo37;
#define            gu8_dimming_set_thirty_seven                  U8DimmingPercentNo37.byte
#define            bit_0_3_ice_extract_inner                     U8DimmingPercentNo37.nibble.b0_3
#define            bit_4_7_Ice_Water_Inner_Extract                         U8DimmingPercentNo37.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo38;
#define            gu8_dimming_set_thirty_eight                  U8DimmingPercentNo38.byte
#define            bit_0_3_Seg_Left_Hundred                       U8DimmingPercentNo38.nibble.b0_3
#define            bit_4_7_Seg_Left_Ten                       U8DimmingPercentNo38.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo39;
#define            gu8_dimming_set_thirty_nine                  U8DimmingPercentNo39.byte
#define            bit_0_3_Seg_Left_One                       U8DimmingPercentNo39.nibble.b0_3
#define            bit_4_7_Seg_Right_Hundred                       U8DimmingPercentNo39.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo40;
#define            gu8_dimming_set_fourty                       U8DimmingPercentNo40.byte
#define            bit_0_3_Seg_Right_Ten                       U8DimmingPercentNo40.nibble.b0_3
#define            bit_4_7_Seg_Right_One                       U8DimmingPercentNo40.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////







/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_WORD          U16AnimationDimmingW;
#define            gu16_animation_dimming                                     U16AnimationDimmingW.word
#define            u8AnimationDimming_L                                       U16AnimationDimmingW.byte[0]
#define            u8AnimationDimming_H                                       U16AnimationDimmingW.byte[1]
#define            Bit0_Animation_Dimming_Ice_Select_State                    U16AnimationDimmingW.Bit.b0
#define            Bit1_Animation_Dimming_Ice_Water_Select_State              U16AnimationDimmingW.Bit.b1
#define            Bit2_Animation_Dimming_Hot_Select_State                    U16AnimationDimmingW.Bit.b2
#define            Bit3_Animation_Dimming_Ambient_Select_State                U16AnimationDimmingW.Bit.b3
#define            Bit4_Animation_Dimming_Cold_Select_State                   U16AnimationDimmingW.Bit.b4
#define            Bit5_Animation_Dimming_Amount_Select_State                 U16AnimationDimmingW.Bit.b5
#define            Bit6_Animation_Dimming_My_Select_State                     U16AnimationDimmingW.Bit.b6
#define            Bit7_Animation_Dimming_Cold_Off_State                      U16AnimationDimmingW.Bit.b7
#define            Bit8_Animation_Dimming_Setting_Ice_Size_State              U16AnimationDimmingW.Bit.b8
#define            Bit9_Animation_Dimming_Setting_Ice_Off_State               U16AnimationDimmingW.Bit.b9
#define            Bit10_Animation_Dimming_Setting_Hot_Lock_State              U16AnimationDimmingW.Bit.b10
#define            Bit11_Animation_Dimming_Setting_Ice_First_State            U16AnimationDimmingW.Bit.b11
#define            Bit12_Animation_Dimming_Setting_Cold_Temp_State            U16AnimationDimmingW.Bit.b12
#define            Bit13_Animation_Dimming_Setting_Sleep_Mode_Text_State      U16AnimationDimmingW.Bit.b13
#define            Bit14_Animation_Dimming_Ice_Lock_State                     U16AnimationDimmingW.Bit.b14
#define            Bit15_Animation_Dimming_Setting_All_Lock_State             U16AnimationDimmingW.Bit.b15



extern TYPE_WORD          U16AnimationDimmingTwoW;
#define            gu16_animation_dimming_two                                 U16AnimationDimmingTwoW.word
#define            u8AnimationDimmingTwo_L                                    U16AnimationDimmingTwoW.byte[0]
#define            u8AnimationDimmingTwo_H                                    U16AnimationDimmingTwoW.byte[1]
#define            Bit0_Animation_Dimming_Ice_Full_Txt_State                  U16AnimationDimmingTwoW.Bit.b0
#define            Bit1_Animation_Dimming_UV_Ster_Txt_State                   U16AnimationDimmingTwoW.Bit.b1
#define            Bit2_Animation_Dimming_Hot_Ster_Txt_State                  U16AnimationDimmingTwoW.Bit.b2
#define            Bit3_Animation_Dimming_Sleep_Icon_State                    U16AnimationDimmingTwoW.Bit.b3
#define            Bit4_Animation_Dimming_Step_Txt_State                      U16AnimationDimmingTwoW.Bit.b4
#define            Bit5_Animation_Dimming_Clock_Colon_Icon_State              U16AnimationDimmingTwoW.Bit.b5
#define            Bit6_Animation_Dimming_oC_Icon_State                       U16AnimationDimmingTwoW.Bit.b6
#define            Bit7_Animation_Dimming_Wifi_Icon_State                     U16AnimationDimmingTwoW.Bit.b7
#define            Bit8_Animation_Dimming_Sunny_Icon_State                    U16AnimationDimmingTwoW.Bit.b8
#define            Bit9_Animation_Dimming_Cloud_Icon_State                    U16AnimationDimmingTwoW.Bit.b9
#define            Bit10_Animation_Dimming_Rain_Icon_State                    U16AnimationDimmingTwoW.Bit.b10
#define            Bit11_Animation_Dimming_Percent_Icon_State                 U16AnimationDimmingTwoW.Bit.b11
#define            Bit12_Animation_Dimming_Liter_Txt_State                    U16AnimationDimmingTwoW.Bit.b12
#define            Bit13_Animation_Dimming_ml_txt_State                       U16AnimationDimmingTwoW.Bit.b13
#define            Bit14_Animation_Dimming_right_dot_txt_State                U16AnimationDimmingTwoW.Bit.b14
#define            Bit15_Animation_Dimming_Hot_Locker_State                   U16AnimationDimmingTwoW.Bit.b15



extern TYPE_BYTE          U8AnimationDimmingThreeB;
#define            gu8_animation_dimming_three                                U8AnimationDimmingThreeB.byte
#define            Bit0_Animation_Dimming_Temp_bar_1_1_State                  U8AnimationDimmingThreeB.Bit.b0
#define            Bit1_Animation_Dimming_Temp_bar_1_2_State                  U8AnimationDimmingThreeB.Bit.b1
#define            Bit2_Animation_Dimming_Temp_bar_1_3_State                  U8AnimationDimmingThreeB.Bit.b2
#define            Bit3_Animation_Dimming_Temp_bar_1_4_State                  U8AnimationDimmingThreeB.Bit.b3
#define            Bit4_Animation_Dimming_Amount_bar_2_1_State                U8AnimationDimmingThreeB.Bit.b4
#define            Bit5_Animation_Dimming_Amount_bar_2_2_State                U8AnimationDimmingThreeB.Bit.b5
#define            Bit6_Animation_Dimming_Amount_bar_2_3_State                U8AnimationDimmingThreeB.Bit.b6
#define            Bit7_Animation_Dimming_Amount_bar_Continue_State           U8AnimationDimmingThreeB.Bit.b7


extern TYPE_BYTE          U8AnimationDimmingFourB;
#define            gu8_animation_dimming_four                                 U8AnimationDimmingFourB.byte
#define            Bit0_Animation_Dimming_Recipe_Ramen_txt_State              U8AnimationDimmingFourB.Bit.b0
#define            Bit1_Animation_Dimming_Recipe_Drip_Coffee_txt_State        U8AnimationDimmingFourB.Bit.b1
#define            Bit2_Animation_Dimming_Tea_txt_State                       U8AnimationDimmingFourB.Bit.b2
#define            Bit3_Animation_Dimming_MY_1_txt_State                      U8AnimationDimmingFourB.Bit.b3
#define            Bit4_Animation_Dimming_MY_2_txt_State                      U8AnimationDimmingFourB.Bit.b4
#define            Bit5_Animation_Dimming_Ice_Lock_Icon_State                 U8AnimationDimmingFourB.Bit.b5
#define            Bit6_Animation_Dimming_Hot_Lock_Icon_State                 U8AnimationDimmingFourB.Bit.b6
#define            Bit7_Animation_Dimming_Comp_Operation_Dot_State            U8AnimationDimmingFourB.Bit.b7


extern TYPE_BYTE          U8AnimationDimmingFiveB;
#define            gu8_animation_dimming_five                                 U8AnimationDimmingFiveB.byte
#define            Bit0_Animation_Dimming_Ice_Large_txt_State                 U8AnimationDimmingFiveB.Bit.b0
#define            Bit1_Animation_Dimming_Ice_Center_Bar_State                U8AnimationDimmingFiveB.Bit.b1
#define            Bit2_Animation_Dimming_Ice_Small_txt_State                 U8AnimationDimmingFiveB.Bit.b2
#define            Bit3_Animation_Dimming_Cold_High_txt_State                 U8AnimationDimmingFiveB.Bit.b3
#define            Bit4_Animation_Dimming_Cold_Center_Bar_State               U8AnimationDimmingFiveB.Bit.b4
#define            Bit5_Animation_Dimming_Cold_Low_txt_State                  U8AnimationDimmingFiveB.Bit.b5
#define            Bit6_Animation_Dimming_Welcome_2_Led_State                 U8AnimationDimmingFiveB.Bit.b6    // CH.PARK ADDED 250204
#define            Bit7_Animation_Dimming_My_3_txt_State                      U8AnimationDimmingFiveB.Bit.b7


extern TYPE_BYTE          U8AnimationDimmingSixB;
#define            gu8_animation_dimming_six                                  U8AnimationDimmingSixB.byte
#define            Bit0_Animation_Dimming_Ice_Extract_Outer_State                   U8AnimationDimmingSixB.Bit.b0
#define            Bit1_Animation_Dimming_Water_Extract_State                 U8AnimationDimmingSixB.Bit.b1
#define            Bit2_Animation_Dimming_Welcome_Led_State                   U8AnimationDimmingSixB.Bit.b2
#define            Bit3_Animation_Dimming_Eff_Faucet_Text_State               U8AnimationDimmingSixB.Bit.b3
#define            Bit4_Animation_Dimming_Ice_Faucet_Text_State               U8AnimationDimmingSixB.Bit.b4
#define            Bit5_Animation_Dimming_Ice_Tray_Text_State               U8AnimationDimmingSixB.Bit.b5
#define            Bit6_Animation_Dimming_Ice_Box_Text_State               U8AnimationDimmingSixB.Bit.b6
#define            Bit7_Animation_Dimming_Filter_Clean_Text_State             U8AnimationDimmingSixB.Bit.b7

extern TYPE_BYTE          U8AnimationDimmingSevenB;
#define            gu8_animation_dimming_seven                                U8AnimationDimmingSevenB.byte
#define            Bit0_Animation_Dimming_Temp_bar_1_5_State                  U8AnimationDimmingSevenB.Bit.b0
#define            Bit1_Animation_Dimming_Amount_bar_2_4_State                U8AnimationDimmingSevenB.Bit.b1
#define            Bit2_Animation_Dimming_Ice_Shortage_Text_State             U8AnimationDimmingSevenB.Bit.b2
#define            Bit3_Animation_Dimming_Ice_Water_Text_State                U8AnimationDimmingSevenB.Bit.b3
#define            Bit4_Animation_Dimming_Ice_Water_Extract_State             U8AnimationDimmingSevenB.Bit.b4
#define            Bit5_Animation_Dimming_Ice_Normal_State                    U8AnimationDimmingSevenB.Bit.b5
#define            Bit6_Animation_Dimming_Ice_Piece_State                     U8AnimationDimmingSevenB.Bit.b6
#define            Bit7_Animation_Dimming_Ice_Extract_Inner_State             U8AnimationDimmingSevenB.Bit.b7

/* LPP 추가 */
extern TYPE_BYTE          U8AnimationDimmingEightB;
#define            gu8_animation_dimming_eight                                U8AnimationDimmingEightB.byte
#define            Bit0_Animation_Dimming_Ice_Inner_Blue_state                U8AnimationDimmingEightB.Bit.b0
#define            Bit1_Animation_Dimming_Fast_Ice_State                      U8AnimationDimmingEightB.Bit.b1
#define            Bit2_Animation_Dimming_Comp_Blue_State                     U8AnimationDimmingEightB.Bit.b2
#define            Bit3_Animation_Dimming_Ice_Locker_State                    U8AnimationDimmingEightB.Bit.b3

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


extern TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3



extern TYPE_BYTE          U812VPowerControl;
#define            u8PowerControl12V                                    U812VPowerControl.byte
#define            Bit0_Gas_Switch_12V_Out_State                        U812VPowerControl.Bit.b0
#define            Bit1_Ice_Tank_UV_12V_Out_State                       U812VPowerControl.Bit.b1
#define            Bit2_Uart_Test_Mode_State                            U812VPowerControl.Bit.b2
#define            Bit3_Water_Tank_UV_12V_Out_State                     U812VPowerControl.Bit.b3
#define            Bit4_Ice_Tray_UV_12V_Out_State                       U812VPowerControl.Bit.b4
#define            Bit5_Ice_Tank_Front_UV_12V_Out_State                 U812VPowerControl.Bit.b5
#define            Bit6_Drain_Pump_FeedBack_12V_Out_State               U812VPowerControl.Bit.b6





extern U8 AT_gu8TX_ERROR;
extern bit AT_F_Rx_NG;
extern U16 gu16ADLeakage;
extern bit F_Uart_Final;
extern U16 gu16_IceSelect_StepMotor;
extern bit F_IceOpen;
extern U16 gu16_Ice_Door_StepMotor;
extern bit F_IceSelect;


extern U8 gu8_Room_Water_Level;

extern U16 gu16_AD_Result_Hot_Tank_Temp;
extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U16 gu16_AD_Result_Hot_Tank_Temp;
extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U16 gu16_AD_Result_Eva_First;
extern U8 gu8_Eva_Cold_Temperature_One_Degree;
extern U16 gu16_AD_Result_Eva_Second;
extern U16 gu16_AD_Result_Amb;
extern U8 gu8_Amb_Temperature_One_Degree;
extern U16 gu16_AD_Result_Cold;
extern U8 gu8_Cold_Temperature_One_Degree;
extern U16 gu16_AD_Result_Room;
extern U8 gu8_Room_Temperature_One_Degree;
extern U16 gu16ADIceLow;
extern U16 gu16ADIceFull;
extern U16 gu16_AD_Drain_Pump_Current;
extern U16 gu16_AD_Tray_Pump_Current;
extern U16 gu16_AD_Result_UV_Ice_Tank_1_2_Current;
extern U16 gu16_AD_Result_UV_Ice_Faucet_Two_Current;
extern U16 gu16_AD_Result_DC_Current_12V;
extern U16 gu16_AD_Result_DC_Current_24V;
extern U16 gu16_AD_Result_UV_Ice_Faucet_One_Current;
extern U16 gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed;
extern U16 gu16_AD_Result_UV_Water_Faucet_Current_Feed;
extern U16 gu16_AD_Result_UV_Ice_Tank_3_Current_Feed;

extern U8 gu8_Flow_1sec;


extern bit F_ErrTrayMotor_DualInital;
extern U8 gu8_GasSwitch_Status;

extern bit F_GasSwitch_Initial;
extern U8 gu8_GasSwitch_Mode;

extern bit F_Overflow;

extern bit F_FW_Version_Display_Mode;

extern bit bit_adc_cold_start;
extern bit bit_adc_room_start;
extern U8 gu8IceTrayLEV;
extern bit F_TrayMotorDOWN;
extern bit F_TrayMotorUP;


extern U8 gu8_icewater_test_input;
extern U8 gu8_ice_test_input;
extern U8 gu8_hot_test_input;
extern U8 gu8_ambient_test_input;
extern U8 gu8_cold_test_input;
extern U8 gu8_amount_test_input;
extern U8 gu8_my_test_input;

extern U8 gu8_setting_ice_first_test_input;
extern U8 gu8_setting_ice_lock_test_input;
extern U8 gu8_setting_hot_lock_test_input;
extern U8 gu8_setting_touch_lock_test_input;
extern U8 gu8_setting_steam_off_test_input;
extern U8 gu8_setting_eco_mode_test_input;

extern U8 gu8_water_ext_test_input;
extern U8 gu8_ice_ext_test_input;


extern bit bit_uart_ice_test_finish;
extern bit bit_uart_ice_water_test_finish;
extern bit bit_uart_hot_test_finish;
extern bit bit_uart_ambient_test_finish;
extern bit bit_uart_cold_tst_finish;
extern bit bit_uart_amount_test_finish;
extern bit bit_uart_ice_size_test_finish;
extern bit bit_uart_ice_off_test_finish;
extern bit bit_uart_hot_lock_test_finish;
extern bit bit_uart_fast_ice_test_finish;
extern bit bit_uart_cold_temp_test_finish;
extern bit bit_uart_sleep_mode_test_finish;

extern bit bit_uart_water_extract_test_finish;
extern bit bit_uart_ice_lock_test_finish;
extern bit bit_uart_all_lock_test_finish;
extern bit bit_uart_my_test_finish;
extern bit bit_uart_cold_off_finish;


extern bit F_Wink_500ms;
extern bit F_cds_detect;
extern U8 gu8_uart_test_mode;
extern U8 gu8_initial_all_data;
extern U16 gu16_AD_Result_Fan_Current;



extern U8 gu8_display_test_error;
extern U8 gu8_hot_temp_off_timer;
extern U8 gu8_cup_level_off_timer;


extern U8 gu8_ro_drain_status;
extern U8 gu8_hot_flow_status;
extern U8 gu8_uart_comp_start;
extern U8 gu8_uart_comp_rps;
extern U8 gu8_bldc_target_hz;

extern S16 gs16_sm_info_target;
extern S16 gs16_sm_info_current;

extern U16 gu16_drain_pwm_out;
extern U16 gu16_current_tray_pwm;
extern U8 gu8_water_color_change_timer;

extern bit F_TDS_ON;
extern U16 gu16TDS_OUT_Pulse_Time;
extern U16 gu16TDS_IN_Pulse;
extern U16 gu16_AD_Result_TDS_Out_Data;
/////extern bit bit_drain_level_power_output;
extern U8 gu8_rtc_time_Hour;
extern U8 gu8_rtc_time_Min;
extern U8 gu8_rtc_time_Sec;
extern U16 gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed;
extern FLOW_VALVE_MODE  gu8_hot_flow_mode;
extern U16 gu16_flow_info_current;
extern tsSTEPMOTOR sStepMotor;

extern U16 gu16_Door_Heater_IAD_OFF_Data;
extern U16 gu16_Door_Heater_IAD_ON_Data;
extern U8 gu8_Door_Heater_Check_Timer_100ms;
extern U16 gu16_AD_Result_IceDoor_Heater_Current;

#define UART_TEMP_SENSOR_ERROR    0xFF

#define UART_CHECK_COLD_EXTRACT             0
#define UART_CHECK_HOT_EXTRACT              1
#define UART_CHECK_ROOM_EXTRACT             2





#endif
