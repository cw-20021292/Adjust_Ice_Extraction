/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "test_display_factory.h"

void diplay_test_start(void);
void Display_Test_Main(void);
void display_test_factory_input(void);
void display_test_error(void);
void display_test_factory_job(void);
void Display_Test_Mode_Key_Short_Input(U32 u32key_input_value);
void initial_ice_tray(void);
void make_test_mode_rgb_color( U8 mu8_color );
void make_test_mode_ice_inner_rgb_color( U8 mu8_color );
void make_test_mode_ice_outer_rgb_color( U8 mu8_color );

//void Set_Display_Test_KeyInput(DISPLAY_TEST_KEY_INPUT input);

#define SETTING_LED_ICE_SIZE 0x01
#define SETTING_LED_ICE_OFF  0x02
#define SETTING_LED_HOT_LOCK 0x04
#define SETTING_LED_FAST_ICE 0x08
#define SETTING_LED_COLD_TMP 0x10
#define SETTING_LED_SLEEPMOD 0x20
#define SETTING_LED_ICE_LOCK 0x40
#define SETTING_LED_ALL_LOCK 0x80
#define SETTING_LED_COLD_OFF 0x100

U8 key_press_ice;
U8 key_press_icewater;
U8 key_press_hot;
U8 key_press_pure;
U8 key_press_cold;
U8 key_press_amount;
U8 key_press_hidden_1;
U8 key_press_hidden_2;
U8 key_press_hidden_3;
U8 key_press_hidden_4;
U8 key_press_hidden_5;
U8 key_press_hidden_6;
U8 key_press_hidden_7;
U8 key_press_hidden_8;
U8 key_press_extract;

U8 display_test_flick_timer_100ms = 0;
U8 is_display_test_flick = 0;
U8 display_flick_state = 0;
U8 display_test_rgb_color = 0;

bit F_cds_detect;
U8 gu8_user_lcd_output;
U8 gu8_hot_lcd_output;
U8 gu8_room_lcd_output;
U8 gu8_cold_lcd_output;
U8 gu8_cup_lcd_output;

U8 gu8_initial_all_data;
U8 u8_water_select_testmode;
U8 u8_cup_select_testmode;

U8 gu8_hot_temp_off_timer;
U8 gu8_cup_level_off_timer;
U8 gu8_left_fnd_off_timer;
U8 gu8_right_fnd_off_timer;

U8 gu8_display_test_error;
bit bit_display_error_state;

bit bit_tank_cover_first_read;
bit bit_tank_cover_error;

bit bit_side_cover_first_read;
bit bit_side_cover_error;
U8 gu8_reed_first_read_timer;

U8 gu8_ice_feeder_test_on_timer;
U8 gu8_ice_feeder_test_off_timer;

U8 gu8_display_reed_test_step;
U8 gu8_display_reed_test_timer;

bit bit_display_test_neo_filter;
bit bit_display_test_ro_filter;
bit bit_display_test_ino_filter;


bit bit_display_test_neo_filter_old;
bit bit_display_test_ro_filter_old;
bit bit_display_test_ino_filter_old;


bit bit_display_test_filter_reed_error;


U8 gu8_water_color_change_timer;
U8 gu8_ice_color_change_timer;

U16 gu16_display_tds_in_max;
U16 gu16_display_tds_out_max;

U16 gu16_tds_test_timer;

DISPLAY_TEST_STEP Disp_test_step;

bit bit_uart_ice_test_finish;
bit bit_uart_ice_water_test_finish;
bit bit_uart_hot_test_finish;
bit bit_uart_ambient_test_finish;
bit bit_uart_cold_tst_finish;
bit bit_uart_amount_test_finish;
bit bit_uart_ice_size_test_finish;
bit bit_uart_ice_off_test_finish;
bit bit_uart_hot_lock_test_finish;
bit bit_uart_fast_ice_test_finish;
bit bit_uart_cold_temp_test_finish;
bit bit_uart_sleep_mode_test_finish;
bit bit_uart_ice_lock_test_finish;
bit bit_uart_all_lock_test_finish;
bit bit_uart_my_test_finish;        /* MY 세팅키 추가 250213 @CH.PARK */
bit bit_uart_cold_off_finish;       /* 냉수OFF 세팅키 추가 250213 @CH.PARK */

bit bit_uart_water_extract_test_finish;
bit bit_uart_ice_extract_test_finish;

bit bit_filter_cover_old;

U8 gu8_left_segment_off_timer;
U8 gu8_right_segment_off_timer;
U8 gu8_left_bar_off_timer;
U8 gu8_right_bar_off_timer;

bit bit_touch_test_finish;
bit bit_display_test_tank_cover_old;
bit bit_test_tank_cover_flag;
bit bit_display_test_tank_cover_error;
bit bit_display_test_filter_cover_old;
bit bit_test_filter_cover_flag;
bit bit_display_test_filter_cover_error;
bit bit_is_cover_checked;

U8 gu8_ice_water_select_display_timer;
U8 gu8_ice_select_display_timer;
U8 gu8_hot_select_display_timer;
U8 gu8_pure_select_display_timer;
U8 gu8_cold_select_display_timer;
U8 gu8_amount_select_display_timer;
U8 gu8_my_select_display_timer;
U8 gu8_ice_off_display_timer;
U8 gu8_ice_size_display_timer;
U8 gu8_hot_lock_display_timer;
U8 gu8_fast_ice_display_timer;
U8 gu8_cold_off_display_timer;

U8 gu8_water_rgb_test_step;
U8 gu8_ice_rgb_test_step;
extern void output_ice_tray_motor(void);
extern void play_melody_warning_197( void );
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void diplay_test_start(void)
{
    gu8_test_mode_timeout_1s = 0;

    play_voice_test_mode_151();

    off_all_control_led();
    UARTest_NO_LOAD_Set();
    // F_TrayMotorUP = 0;
    //F_TrayMotorDOWN = 0;

    /*..hui [17-12-28오후 10:54:12] 버전만 표시..*/
    F_FW_Version_Display_Mode = CLEAR;
    gu8_led_version_step = 2;
    gu8_version_display_Timer = 0;

    u8FactoryTestMode = DISPLAY_TEST_MODE;

    /*..hui [19-11-5오후 5:57:28] EEPROM / RTC 시간 초기화..*/
    gu8_initial_all_data = 1;

    /*..hui [19-12-19오후 1:26:46] 정수 온도센서 전원 ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19오후 1:27:21] 냉수 온도센서 전원 ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;

    /*..hui [20-1-14오후 8:15:16] 12V 전원 ON..*/
    Bit2_Uart_Test_Mode_State = SET;

    bit_uart_ice_test_finish = CLEAR;
    bit_uart_ice_water_test_finish = CLEAR;
    bit_uart_hot_test_finish = CLEAR;
    bit_uart_ambient_test_finish = CLEAR;
    bit_uart_cold_tst_finish = CLEAR;
    bit_uart_amount_test_finish = CLEAR;
    bit_uart_ice_size_test_finish = CLEAR;
    bit_uart_ice_off_test_finish = CLEAR;
    bit_uart_hot_lock_test_finish = CLEAR;
    bit_uart_fast_ice_test_finish = CLEAR;
    bit_uart_cold_temp_test_finish = CLEAR;
    bit_uart_sleep_mode_test_finish = CLEAR;
    bit_uart_my_test_finish = CLEAR;
    bit_uart_cold_off_finish = CLEAR;

    bit_uart_water_extract_test_finish = CLEAR;
    bit_uart_ice_lock_test_finish = CLEAR;
    bit_uart_all_lock_test_finish = CLEAR;

    bit_manual_test_start = CLEAR;

    ///all_breath_stop();

    bit_tank_cover_first_read = CLEAR;
    bit_side_cover_first_read = CLEAR;
    gu8_reed_first_read_timer = 0;

    bit_filter_reed_old = SET;
    bit_filter_cover_old = bit_filter_cover;

    gu8_display_reed_test_step = 0;
    bit_display_test_filter_reed_error = CLEAR;

    gu16_IceSelect_StepMotor = STEP_ANGLE_SELECT;
    gu16_Ice_Door_StepMotor = STEP_ANGLE_DOOR;

    bit_display_test_filter_cover_old = pREED_FILTER_COVER;
    bit_display_test_tank_cover_old = pREED_TANK_COVER_2;

    gu8_water_rgb_test_step = 0;
    gu8_ice_rgb_test_step = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 1
void Display_test_step_Handler(void)
{
	led_blink_timer();
	//all_breath_stop();
	all_duty_100_percent();

    if((Disp_test_step != DISPLAY_TEST_FINISH)
    && (Disp_test_step > DISPLAY_TEST_START)
    )
    {
        fnd_left_display_test();
        fnd_right_display_test();
    }
    else {  }


	switch(Disp_test_step)
	{
		case DISPLAY_TEST_NONE:
			if(F_FW_Version_Display_Mode != SET)
			{
				display_version();
			}
			else
			{
                Disp_test_step = DISPLAY_TEST_START;
                play_voice_test_mode_151();
			}
			break;

		case DISPLAY_TEST_START:
			fnd_left_out( FIXED_DISPLAY, DISPLAY_NUM_8, DISPLAY_NUM_8, DISPLAY_NUM_8);
			fnd_right_out( FIXED_DISPLAY, DISPLAY_NUM_8, DISPLAY_NUM_8, DISPLAY_NUM_8);

            gu8_front_left_led = 0xFF;
            gu8_front_left_led_2 = 0x3F;
			gu8_front_right_led = 0xFF;
			gu8_front_temp_setting_bar_led = 0x1F;
			gu8_front_amount_setting_bar_led = 0x1F;
			gu8_front_center_recipe_led = 0x3F;
			gu8_front_select_led = 0x7F;

			gu8_front_setting_led = 0x7F;
            gu8_front_setting_led_2 = 0x7F;
			gu8_front_under_text_led = 0xFF;
			gu8_front_under_icon_led = 0x7A;        // BLUE 안씀
			break;

		case DISPLAY_TEST_BTN1: // [얼음물] 클릭 후
			gu8_ice_water_select_display_timer++;

            if(gu8_ice_water_select_display_timer <= 2)
            {
                // 얼음물
                Bit1_Front_Led_Ice_Water_Select = CLEAR;

                // MY 1,2,3
                Bit3_Front_Center_MY_1_Text = SET;
                Bit4_Front_Center_MY_2_Text = SET;
                Bit5_Front_Center_MY_3_Text = SET;

                // 출수파우셋
                Bit0_Front_Left_Led_Eff_Faucet_Text = SET;
            }
            else if(gu8_ice_water_select_display_timer <= 4)
            {
                // 얼음물
                Bit1_Front_Led_Ice_Water_Select = (CLEAR);

                // MY 1,2,3
                Bit3_Front_Center_MY_1_Text = (CLEAR);
                Bit4_Front_Center_MY_2_Text = SET;
                Bit5_Front_Center_MY_3_Text = SET;

                // 출수파우셋
                Bit0_Front_Left_Led_Eff_Faucet_Text = SET;
            }
            else if(gu8_ice_water_select_display_timer <= 6)
            {
                // 얼음물
                Bit1_Front_Led_Ice_Water_Select = CLEAR;

                // MY 1,2,3
                Bit3_Front_Center_MY_1_Text = CLEAR;
                Bit4_Front_Center_MY_2_Text = CLEAR;
                Bit5_Front_Center_MY_3_Text = SET;

                // 출수파우셋
                Bit0_Front_Left_Led_Eff_Faucet_Text = SET;
            }
            else if(gu8_ice_water_select_display_timer <= 8)
            {
                // 얼음물
                Bit1_Front_Led_Ice_Water_Select = CLEAR;

                // MY 1,2,3
                Bit3_Front_Center_MY_1_Text = CLEAR;
                Bit4_Front_Center_MY_2_Text = CLEAR;
                Bit5_Front_Center_MY_3_Text = CLEAR;

                // 출수파우셋
                Bit0_Front_Left_Led_Eff_Faucet_Text = SET;
            }
            else if(gu8_ice_water_select_display_timer <= 10)
            {
                // 얼음물
                Bit1_Front_Led_Ice_Water_Select = CLEAR;

                // MY 1,2,3
                Bit3_Front_Center_MY_1_Text = CLEAR;
                Bit4_Front_Center_MY_2_Text = CLEAR;
                Bit5_Front_Center_MY_3_Text = CLEAR;

                // 출수파우셋
                Bit0_Front_Left_Led_Eff_Faucet_Text = CLEAR;
            }
            else
            {
                gu8_ice_water_select_display_timer = 10;

                // 얼음물
                Bit1_Front_Led_Ice_Water_Select = CLEAR;

                // MY 1,2,3
                Bit3_Front_Center_MY_1_Text = CLEAR;
                Bit4_Front_Center_MY_2_Text = CLEAR;
                Bit5_Front_Center_MY_3_Text = CLEAR;
                // 출수파우셋
                Bit0_Front_Left_Led_Eff_Faucet_Text = CLEAR;
            }
			break;

		case DISPLAY_TEST_BTN2: // [얼음] 클릭 후
            gu8_ice_select_display_timer++;
            if(gu8_ice_select_display_timer <= 2)
            {
                // 얼음
                Bit0_Front_Led_Ice_Select = CLEAR;

                // 라면, 드립커피, 차
                Bit0_Front_Center_Recipe_Ramen_Text = SET;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = SET;
                Bit1_Front_Center_Tea_Text = SET;

                // 얼음부족
                Bit1_Front_Left_Led_Ice_Shortae_Text = SET;

                // 얼음 일반/조각
                Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
                Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
            }
            else if(gu8_ice_select_display_timer <= 4)
            {
                // 얼음
                Bit0_Front_Led_Ice_Select = CLEAR;

                // 라면, 드립커피, 차
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = SET;
                Bit1_Front_Center_Tea_Text = SET;

                // 얼음부족
                Bit1_Front_Left_Led_Ice_Shortae_Text = SET;

                // 얼음 일반/조각
                Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
                Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
            }
            else if(gu8_ice_select_display_timer <= 6)
            {
                // 얼음
                Bit0_Front_Led_Ice_Select = CLEAR;

                // 라면, 드립커피, 차
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                Bit1_Front_Center_Tea_Text = SET;

                // 얼음부족
                Bit1_Front_Left_Led_Ice_Shortae_Text = SET;

                // 얼음 일반/조각
                Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
                Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
            }
            else if(gu8_ice_select_display_timer <= 8)
            {
                // 얼음
                Bit0_Front_Led_Ice_Select = CLEAR;

                // 라면, 드립커피, 차
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                Bit1_Front_Center_Tea_Text = CLEAR;

                // 얼음부족
                Bit1_Front_Left_Led_Ice_Shortae_Text = SET;

                // 얼음 일반/조각
                Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
                Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
            }
            else if(gu8_ice_select_display_timer <= 10)
            {
                // 얼음
                Bit0_Front_Led_Ice_Select = CLEAR;

                // 라면, 드립커피, 차
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                Bit1_Front_Center_Tea_Text = CLEAR;

                // 얼음부족
                Bit1_Front_Left_Led_Ice_Shortae_Text = CLEAR;

                // 얼음 일반/조각
                Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
                Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
            }
            else if(gu8_ice_select_display_timer <= 12)
            {
                // 얼음
                Bit0_Front_Led_Ice_Select = CLEAR;

                // 라면, 드립커피, 차
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                Bit1_Front_Center_Tea_Text = CLEAR;

                // 얼음부족
                Bit1_Front_Left_Led_Ice_Shortae_Text = CLEAR;

                // 얼음 일반/조각
                Bit6_Front_Under_Txt_Led_Ice_Normal = CLEAR;
                Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
            }
            else if(gu8_ice_select_display_timer <= 14)
            {
                // 얼음
                Bit0_Front_Led_Ice_Select = CLEAR;

                // 라면, 드립커피, 차
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                Bit1_Front_Center_Tea_Text = CLEAR;

                // 얼음부족
                Bit1_Front_Left_Led_Ice_Shortae_Text = CLEAR;

                // 얼음 일반/조각
                Bit6_Front_Under_Txt_Led_Ice_Normal = CLEAR;
                Bit7_Front_Under_Txt_Led_Ice_Piece = CLEAR;
            }
            else
            {
                gu8_ice_select_display_timer = 14;
                // 얼음
                Bit0_Front_Led_Ice_Select = CLEAR;

                // 라면, 드립커피, 차
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                Bit1_Front_Center_Tea_Text = CLEAR;

                // 얼음부족
                Bit1_Front_Left_Led_Ice_Shortae_Text = CLEAR;

                // 얼음 일반/조각
                Bit6_Front_Under_Txt_Led_Ice_Normal = CLEAR;
                Bit7_Front_Under_Txt_Led_Ice_Piece = CLEAR;
            }
			break;

		case DISPLAY_TEST_BTN3: // [온수] 클릭 후
            gu8_hot_select_display_timer++;
            if(gu8_hot_select_display_timer <= 2)
            {
                // 온수
                Bit2_Front_Led_Hot_Select = CLEAR;

                // 얼음가득, 절전아이콘
                Bit0_Front_Left_Led_Ice_Full_Text = SET;
                Bit4_Front_Left_Led_Sleep_Icon = SET;

                // 얼음파우셋
                Bit1_Front_Left_Led_Ice_Faucet_Text = SET;
            }
            else if(gu8_hot_select_display_timer <= 4)
            {
                // 온수
                Bit2_Front_Led_Hot_Select = CLEAR;

                // 얼음가득, 절전아이콘
                Bit0_Front_Left_Led_Ice_Full_Text = CLEAR;
                Bit4_Front_Left_Led_Sleep_Icon = SET;

                // 얼음파우셋
                Bit1_Front_Left_Led_Ice_Faucet_Text = SET;
            }
            else if(gu8_hot_select_display_timer <= 6)
            {
                // 온수
                Bit2_Front_Led_Hot_Select = CLEAR;

                // 얼음가득, 절전아이콘
                Bit0_Front_Left_Led_Ice_Full_Text = CLEAR;
                Bit4_Front_Left_Led_Sleep_Icon = CLEAR;

                // 얼음파우셋
                Bit1_Front_Left_Led_Ice_Faucet_Text = SET;
            }
            else if(gu8_hot_select_display_timer <= 8)
            {
                // 온수
                Bit2_Front_Led_Hot_Select = CLEAR;

                // 얼음가득, 절전아이콘
                Bit0_Front_Left_Led_Ice_Full_Text = CLEAR;
                Bit4_Front_Left_Led_Sleep_Icon = CLEAR;

                // 얼음파우셋
                Bit1_Front_Left_Led_Ice_Faucet_Text = CLEAR;
            }
            else
            {
                gu8_hot_select_display_timer = 8;
                // 온수
                Bit2_Front_Led_Hot_Select = CLEAR;

                // 얼음가득, 절전아이콘
                Bit0_Front_Left_Led_Ice_Full_Text = CLEAR;
                Bit4_Front_Left_Led_Sleep_Icon = CLEAR;

                // 얼음파우셋
                Bit1_Front_Left_Led_Ice_Faucet_Text = CLEAR;
            }

            break;

		case DISPLAY_TEST_BTN4: // [정수] 클릭 후
            gu8_pure_select_display_timer++;
            if(gu8_pure_select_display_timer <= 2)
            {
                // 정수
                Bit3_Front_Led_Ambient_Select = CLEAR;

                // UV살균, 고온살균
                Bit2_Front_Left_Led_UV_Ster_Text = SET;
                Bit3_Front_Left_Led_Hot_Ster_Text = SET;

                // :
                Bit6_Front_Left_Led_Clock_Colon_Icon = SET;

                // 얼음트레이
                Bit2_Front_Left_Led_Ice_Tray_Text = SET;
            }
            else if(gu8_pure_select_display_timer <= 4)
            {
                // 정수
                Bit3_Front_Led_Ambient_Select = CLEAR;

                // UV살균, 고온살균
                Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
                Bit3_Front_Left_Led_Hot_Ster_Text = SET;

                // :
                Bit6_Front_Left_Led_Clock_Colon_Icon = SET;

                // 얼음트레이
                Bit2_Front_Left_Led_Ice_Tray_Text = SET;
            }
            else if(gu8_pure_select_display_timer <= 6)
            {
                // 정수
                Bit3_Front_Led_Ambient_Select = CLEAR;

                // UV살균, 고온살균
                Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
                Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;

                // :
                Bit6_Front_Left_Led_Clock_Colon_Icon = SET;

                // 얼음트레이
                Bit2_Front_Left_Led_Ice_Tray_Text = SET;
            }
            else if(gu8_pure_select_display_timer <= 8)
            {
                // 정수
                Bit3_Front_Led_Ambient_Select = CLEAR;

                // UV살균, 고온살균
                Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
                Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;

                // :
                Bit6_Front_Left_Led_Clock_Colon_Icon = CLEAR;

                // 얼음트레이
                Bit2_Front_Left_Led_Ice_Tray_Text = SET;
            }
            else if(gu8_pure_select_display_timer <= 10)
            {
                // 정수
                Bit3_Front_Led_Ambient_Select = CLEAR;

                // UV살균, 고온살균
                Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
                Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;

                // :
                Bit6_Front_Left_Led_Clock_Colon_Icon = CLEAR;

                // 얼음트레이
                Bit2_Front_Left_Led_Ice_Tray_Text = CLEAR;
            }
            else
            {
                gu8_pure_select_display_timer = 10;

                // 정수
                Bit3_Front_Led_Ambient_Select = CLEAR;

                // UV살균, 고온살균
                Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
                Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;

                // :
                Bit6_Front_Left_Led_Clock_Colon_Icon = CLEAR;

                // 얼음트레이
                Bit2_Front_Left_Led_Ice_Tray_Text = CLEAR;
            }

			break;

		case DISPLAY_TEST_BTN5: // [냉수] 클릭 후
            gu8_cold_select_display_timer++;
            if(gu8_cold_select_display_timer <= 2)
            {
                // 냉수
                Bit4_Front_Led_Cold_Select = CLEAR;

                // 빠른제빙 아이콘
                Bit4_Front_Led_Icon_Fast_Ice = SET;

                // 'C
                Bit7_Front_Left_Led_Celcius_oC_Icon = SET;
            }
            else if(gu8_cold_select_display_timer <= 4)
            {
                // 냉수
                Bit4_Front_Led_Cold_Select = CLEAR;

                // 빠른제빙 아이콘
                Bit4_Front_Led_Icon_Fast_Ice = CLEAR;

                // 'C
                Bit7_Front_Left_Led_Celcius_oC_Icon = SET;
            }
            else if(gu8_cold_select_display_timer <= 6)
            {
                // 냉수
                Bit4_Front_Led_Cold_Select = CLEAR;

                // 빠른제빙 아이콘
                Bit4_Front_Led_Icon_Fast_Ice = CLEAR;

                // 'C
                Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
            }
            else
            {
                gu8_cold_select_display_timer = 6;
                // 냉수
                Bit4_Front_Led_Cold_Select = CLEAR;

                // 빠른제빙 아이콘
                Bit4_Front_Led_Icon_Fast_Ice = CLEAR;

                // 'C
                Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
            }
			break;

		case DISPLAY_TEST_BTN6: // [용량] 클릭 후
            gu8_amount_select_display_timer++;
            if(gu8_amount_select_display_timer <= 2)
            {
                // 용량
                Bit5_Front_Led_Amount_Select = CLEAR;

                // 해,구름,우산
                Bit2_Front_Right_Led_Sunny_Icon = SET;
                Bit3_Front_Right_Led_Cloud_Icon = SET;
                Bit4_Front_Right_Led_Rain_Icon = SET;
            }
            else if(gu8_amount_select_display_timer <= 4)
            {
                // 용량
                Bit5_Front_Led_Amount_Select = CLEAR;

                // 해,구름,우산
                Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
                Bit3_Front_Right_Led_Cloud_Icon = SET;
                Bit4_Front_Right_Led_Rain_Icon = SET;
            }
            else if(gu8_amount_select_display_timer <= 6)
            {
                // 용량
                Bit5_Front_Led_Amount_Select = CLEAR;

                // 해,구름,우산
                Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
                Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
                Bit4_Front_Right_Led_Rain_Icon = SET;
            }
            else if(gu8_amount_select_display_timer <= 8)
            {
                // 용량
                Bit5_Front_Led_Amount_Select = CLEAR;

                // 해,구름,우산
                Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
                Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
                Bit4_Front_Right_Led_Rain_Icon = CLEAR;
            }
            else
            {
                gu8_amount_select_display_timer = 8;
                // 용량
                Bit5_Front_Led_Amount_Select = CLEAR;

                // 해,구름,우산
                Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
                Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
                Bit4_Front_Right_Led_Rain_Icon = CLEAR;
            }
			break;

        case DISPLAY_TEST_BTN6_2: // [MY] 클릭 후
            gu8_my_select_display_timer++;
            if(gu8_my_select_display_timer <= 2)
            {
                // MY
                Bit6_Front_Led_My_Select = CLEAR;

                // 얼음저장고
                Bit3_Front_Left_Led_Ice_Storage_Box_Text = SET;

                // 필터세척
                Bit4_Front_Right_Led_Filter_Clean_Text = SET;

                // .
                Bit5_Front_Right_Seg_Dot_Text = SET;
            }
            else if(gu8_my_select_display_timer <= 4)
            {
                // MY
                Bit6_Front_Led_My_Select = CLEAR;

                // 얼음저장고
                Bit3_Front_Left_Led_Ice_Storage_Box_Text = CLEAR;

                // 필터세척
                Bit4_Front_Right_Led_Filter_Clean_Text = SET;

                // .
                Bit5_Front_Right_Seg_Dot_Text = SET;
            }
            else if(gu8_my_select_display_timer <= 6)
            {
                // MY
                Bit6_Front_Led_My_Select = CLEAR;

                // 얼음저장고
                Bit3_Front_Left_Led_Ice_Storage_Box_Text = CLEAR;

                // 필터세척
                Bit4_Front_Right_Led_Filter_Clean_Text = CLEAR;

                // .
                Bit5_Front_Right_Seg_Dot_Text = SET;
            }
            else if(gu8_my_select_display_timer <= 8)
            {
                // MY
                Bit6_Front_Led_My_Select = CLEAR;

                // 얼음저장고
                Bit3_Front_Left_Led_Ice_Storage_Box_Text = CLEAR;

                // 필터세척
                Bit4_Front_Right_Led_Filter_Clean_Text = CLEAR;

                // .
                Bit5_Front_Right_Seg_Dot_Text = CLEAR;
            }
            else
            {
                gu8_my_select_display_timer = 8;
                // MY
                Bit6_Front_Led_My_Select = CLEAR;

                // 얼음저장고
                Bit3_Front_Left_Led_Ice_Storage_Box_Text = CLEAR;

                // 필터세척
                Bit4_Front_Right_Led_Filter_Clean_Text = CLEAR;

                // .
                Bit5_Front_Right_Seg_Dot_Text = CLEAR;
            }

			break;

		case DISPLAY_TEST_BTN7: // [얼음OFF] 클릭 후
            gu8_ice_off_display_timer++;
            if(gu8_ice_off_display_timer <= 2)
            {
                // 얼음OFF
                Bit1_Front_Led_Ice_Off = CLEAR;

                // WIFI ICON
                Bit0_Front_Right_Led_Wifi_Icon_White = SET;
                Bit1_Front_Right_Led_Wifi_Icon_Blue = SET;
            }
            else if(gu8_ice_off_display_timer <= 4)
            {
                // 얼음OFF
                Bit1_Front_Led_Ice_Off = CLEAR;

                // WIFI ICON
                Bit0_Front_Right_Led_Wifi_Icon_White = CLEAR;
                Bit1_Front_Right_Led_Wifi_Icon_Blue = SET;
            }
            else if(gu8_ice_off_display_timer <= 6)
            {
                // 얼음OFF
                Bit1_Front_Led_Ice_Off = CLEAR;

                // WIFI ICON
                Bit0_Front_Right_Led_Wifi_Icon_White = CLEAR;
                Bit1_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
            }
            else
            {
                gu8_ice_off_display_timer = 6;
                // 얼음OFF
                Bit1_Front_Led_Ice_Off = CLEAR;

                // WIFI ICON
                Bit0_Front_Right_Led_Wifi_Icon_White = CLEAR;
                Bit1_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
            }

            /* OUTLINE RED */
            Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_RED );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
			break;

		case DISPLAY_TEST_BTN8: // [얼음대소] 클릭 후
            gu8_ice_size_display_timer++;
            if(gu8_ice_size_display_timer <= 2)
            {
                // 얼음크기
                Bit0_Front_Led_Ice_Size = CLEAR;

                // L, ml
                Bit7_Front_Right_Led_ml_Icon = SET;
                Bit6_Front_Right_Led_Liter_L_Icon = SET;
            }
            else if(gu8_ice_size_display_timer <= 4)
            {
                // 얼음크기
                Bit0_Front_Led_Ice_Size = CLEAR;

                // L, ml
                Bit7_Front_Right_Led_ml_Icon = CLEAR;
                Bit6_Front_Right_Led_Liter_L_Icon = SET;

            }
            else if(gu8_ice_size_display_timer <= 6)
            {
                // 얼음크기
                Bit0_Front_Led_Ice_Size = CLEAR;

                // L, ml
                Bit7_Front_Right_Led_ml_Icon = CLEAR;
                Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
            }
            else
            {
                gu8_ice_size_display_timer = 6;
                // 얼음크기
                Bit0_Front_Led_Ice_Size = CLEAR;

                // L, ml
                Bit7_Front_Right_Led_ml_Icon = CLEAR;
                Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
            }

            /* OUTLINE GREEN */
            Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            break;

		case DISPLAY_TEST_BTN9: // [온수잠금] 클릭 후
            gu8_hot_lock_display_timer++;
            if(gu8_hot_lock_display_timer <= 2)
            {
                // 온수잠금
                Bit2_Front_Led_Hot_Lock_Text = CLEAR;

                // 온수잠금 아이콘
                Bit3_Front_Led_Icon_Led_Hot_Locker = SET;

                // %
                Bit5_Front_Right_Led_Percent_Icon = SET;

                // 냉수 DOT WHITE
                Bit5_Front_Led_Icon_Comp_Blue = SET;
            }
            else if(gu8_hot_lock_display_timer <= 4)
            {
                // 온수잠금
                Bit2_Front_Led_Hot_Lock_Text = CLEAR;

                // 온수잠금 아이콘
                Bit3_Front_Led_Icon_Led_Hot_Locker = CLEAR;

                // %
                Bit5_Front_Right_Led_Percent_Icon = SET;

                // 냉수 DOT WHITE
                Bit5_Front_Led_Icon_Comp_Blue = SET;
            }
            else if(gu8_hot_lock_display_timer <= 6)
            {
                // 온수잠금
                Bit2_Front_Led_Hot_Lock_Text = CLEAR;

                // 온수잠금 아이콘
                Bit3_Front_Led_Icon_Led_Hot_Locker = CLEAR;

                // %
                Bit5_Front_Right_Led_Percent_Icon = CLEAR;

                // 냉수 DOT WHITE
                Bit5_Front_Led_Icon_Comp_Blue = SET;
            }
            else if(gu8_hot_lock_display_timer <= 8)
            {
                // 온수잠금
                Bit2_Front_Led_Hot_Lock_Text = CLEAR;

                // 온수잠금 아이콘
                Bit3_Front_Led_Icon_Led_Hot_Locker = CLEAR;

                // %
                Bit5_Front_Right_Led_Percent_Icon = CLEAR;

                // 냉수 DOT WHITE
                Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
            }
            else
            {
                gu8_hot_lock_display_timer = 8;
                // 온수잠금
                Bit2_Front_Led_Hot_Lock_Text = CLEAR;

                // 온수잠금 아이콘
                Bit3_Front_Led_Icon_Led_Hot_Locker = CLEAR;

                // %
                Bit5_Front_Right_Led_Percent_Icon = CLEAR;

                // 냉수 DOT WHITE
                Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
            }

            /* OUTLINE BLUE */
            Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
			break;

		case DISPLAY_TEST_BTN10: // [빠른제빙] 클릭 후
			gu8_fast_ice_display_timer++;
            if(gu8_fast_ice_display_timer <= 2)
            {
                // 빠른제빙
                Bit3_Front_Led_Ice_First = CLEAR;

                // 냉수 DOT BLUE
                Bit6_Front_Led_Icon_Comp_White = SET;

                // 단계
                Bit5_Front_Left_Led_Step_Text = SET;

                // WELCOME LED (좌측)
                Bit6_Front_Under_Led_Welcome_2 = SET;
            }
            else if(gu8_fast_ice_display_timer <= 4)
            {
                // 빠른제빙
                Bit3_Front_Led_Ice_First = CLEAR;

                // 냉수 DOT BLUE
                Bit6_Front_Led_Icon_Comp_White = CLEAR;

                // 단계
                Bit5_Front_Left_Led_Step_Text = SET;

                // WELCOME LED (좌측)
                Bit6_Front_Under_Led_Welcome_2 = SET;
            }
            else if(gu8_fast_ice_display_timer <= 6)
            {
                // 빠른제빙
                Bit3_Front_Led_Ice_First = CLEAR;

                // 냉수 DOT BLUE
                Bit6_Front_Led_Icon_Comp_White = CLEAR;

                // 단계
                Bit5_Front_Left_Led_Step_Text = CLEAR;

                // WELCOME LED (좌측)
                Bit6_Front_Under_Led_Welcome_2 = SET;
            }
            else if(gu8_fast_ice_display_timer <= 8)
            {
                // 빠른제빙
                Bit3_Front_Led_Ice_First = CLEAR;

                // 냉수 DOT BLUE
                Bit6_Front_Led_Icon_Comp_White = CLEAR;

                // 단계
                Bit5_Front_Left_Led_Step_Text = CLEAR;

                // WELCOME LED (좌측)
                Bit6_Front_Under_Led_Welcome_2 = CLEAR;
            }
            else
            {
                gu8_fast_ice_display_timer = 8;
                // 빠른제빙
                Bit3_Front_Led_Ice_First = CLEAR;

                // 냉수 DOT BLUE
                Bit6_Front_Led_Icon_Comp_White = CLEAR;

                // 단계
                Bit5_Front_Left_Led_Step_Text = CLEAR;

                // WELCOME LED (좌측)
                Bit6_Front_Under_Led_Welcome_2 = CLEAR;
            }

            /* INLINE RED */
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_RED );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
			break;

		case DISPLAY_TEST_BTN11: // [냉수강약] 클릭 후
            gu8_left_bar_off_timer++;
            if(gu8_left_bar_off_timer <= 2)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = SET;
            }
            else if(gu8_left_bar_off_timer <= 4)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = SET;

            }
            else if(gu8_left_bar_off_timer <= 6)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = SET;

            }
            else if(gu8_left_bar_off_timer <= 8)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = SET;

            }
            else if(gu8_left_bar_off_timer <= 10)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
            }
            else if(gu8_left_bar_off_timer <= 12)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

                Bit3_Front_Under_Txt_Led_Cold_High = CLEAR;
            }
            else if(gu8_left_bar_off_timer <= 14)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

                Bit4_Front_Under_Txt_Led_Cold_Center_Bar = CLEAR;
            }
            else if(gu8_left_bar_off_timer <= 16)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

                Bit5_Front_Under_Txt_Led_Cold_Low = CLEAR;
            }
            else if(gu8_left_bar_off_timer <= 18)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

                Bit4_Front_Led_Cold_Temp = CLEAR;
            }
            else if(gu8_left_bar_off_timer <= 20)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

                Bit5_Front_Under_Led_Welcome = CLEAR;
            }
            else
            {
                gu8_left_bar_off_timer = 20;

                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

                // 냉수온도
                Bit4_Front_Led_Cold_Temp = CLEAR;

                // 강 | 약
                Bit3_Front_Under_Txt_Led_Cold_High = CLEAR;
                Bit4_Front_Under_Txt_Led_Cold_Center_Bar = CLEAR;
                Bit5_Front_Under_Txt_Led_Cold_Low = CLEAR;

                // WELCOME LED (우측)
                Bit5_Front_Under_Led_Welcome = CLEAR;
            }

            /* INLINE GREEN */
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
			break;

		case DISPLAY_TEST_BTN12: // [냉수OFF] 클릭 후
            gu8_cold_off_display_timer++;
            if(gu8_cold_off_display_timer <= 2)
            {
                // 냉수OFF
                Bit6_Front_Led_Cold_Off = CLEAR;

                // 얼음잠금 아이콘
                Bit2_Front_Led_Icon_Led_Ice_Locker = SET;

                // 대 | 소
                Bit0_Front_Under_Txt_Led_Ice_Large = SET;
                Bit1_Front_Under_Txt_Led_Ice_Center_bar = SET;
                Bit2_Front_Under_Txt_Led_Ice_Small = SET;
            }
            else if(gu8_cold_off_display_timer <= 4)
            {
                // 냉수OFF
                Bit6_Front_Led_Cold_Off = CLEAR;

                // 얼음잠금 아이콘
                Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;

                // 대 | 소
                Bit0_Front_Under_Txt_Led_Ice_Large = SET;
                Bit1_Front_Under_Txt_Led_Ice_Center_bar = SET;
                Bit2_Front_Under_Txt_Led_Ice_Small = SET;
            }
            else if(gu8_cold_off_display_timer <= 6)
            {
                // 냉수OFF
                Bit6_Front_Led_Cold_Off = CLEAR;

                // 얼음잠금 아이콘
                Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;

                // 대 | 소
                Bit0_Front_Under_Txt_Led_Ice_Large = CLEAR;
                Bit1_Front_Under_Txt_Led_Ice_Center_bar = SET;
                Bit2_Front_Under_Txt_Led_Ice_Small = SET;
            }
            else if(gu8_cold_off_display_timer <= 8)
            {
                // 냉수OFF
                Bit6_Front_Led_Cold_Off = CLEAR;

                // 얼음잠금 아이콘
                Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;

                // 대 | 소
                Bit0_Front_Under_Txt_Led_Ice_Large = CLEAR;
                Bit1_Front_Under_Txt_Led_Ice_Center_bar = CLEAR;
                Bit2_Front_Under_Txt_Led_Ice_Small = SET;

            }
            else if(gu8_cold_off_display_timer <= 10)
            {
                // 냉수OFF
                Bit6_Front_Led_Cold_Off = CLEAR;

                // 얼음잠금 아이콘
                Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;

                // 대 | 소
                Bit0_Front_Under_Txt_Led_Ice_Large = CLEAR;
                Bit1_Front_Under_Txt_Led_Ice_Center_bar = CLEAR;
                Bit2_Front_Under_Txt_Led_Ice_Small = CLEAR;
            }
            else
            {
                gu8_cold_off_display_timer = 10;
                // 냉수OFF
                Bit6_Front_Led_Cold_Off = CLEAR;

                // 얼음잠금 아이콘
                Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;

                // 대 | 소
                Bit0_Front_Under_Txt_Led_Ice_Large = CLEAR;
                Bit1_Front_Under_Txt_Led_Ice_Center_bar = CLEAR;
                Bit2_Front_Under_Txt_Led_Ice_Small = CLEAR;
            }

            /* INLINE BLUE */
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
			break;

		case DISPLAY_TEST_BTN13: // [취침모드] 클릭 후
            // 용량바 5개
            gu8_right_bar_off_timer++;
            if(gu8_right_bar_off_timer <= 2)
            {
                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            }
            else if(gu8_right_bar_off_timer <= 4)
            {
                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;

            }
            else if(gu8_right_bar_off_timer <= 6)
            {
                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;

            }
            else if(gu8_right_bar_off_timer <= 8)
            {
                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;

            }
            else if(gu8_right_bar_off_timer <= 10)
            {
                Bit5_Front_Led_Sleep_Mode_Text = SET;

                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
            }
            else if(gu8_right_bar_off_timer <= 12)
            {
                Bit5_Front_Led_Sleep_Mode_Text = CLEAR;

                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
            }
            else
            {
                gu8_right_bar_off_timer = 12;

                // 취침모드
                Bit5_Front_Led_Sleep_Mode_Text = CLEAR;

                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
            }

            /* INLINE BLUE */
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );

            /* RED */
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_RED );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
			break;

		case DISPLAY_TEST_BTN14: // [얼음잠금] 클릭 후
            gu8_uart_setting_ice_lock_test_input = 1;
			Bit0_Front_Led_Ice_Lock = CLEAR;

            /* INLINE BLUE */
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );

            /* GREEN */
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
			break;

        case DISPLAY_TEST_BTN15: // [전체잠금] 클릭 후
			Bit1_Front_Led_All_Lock = CLEAR;
            gu8_uart_setting_all_lock_test_input = 1;

            /* INLINE BLUE */
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );

            /* BLUE */
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
			break;

        case DISPLAY_TEST_BTN_ICE_EXTRACT: // [얼음 추출 버튼] 클릭 후
            display_test_flick_timer_100ms++;

            Bit1_Front_Under_Ice_Inner_Blue_Extract = CLEAR;
            Bit2_Front_Under_Ice_Outer_Blue_Extract = CLEAR;

            if( display_test_flick_timer_100ms <= 3 )
            {
                // 내부 외부 white LED only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, EXTRACT__DIMMING__40_PERCETN );
            }
            else if( display_test_flick_timer_100ms <= 6 )
            {
                // 얼음 추출 외부 RED only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_RED );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            }
            else if( display_test_flick_timer_100ms <= 9 )
            {
                // 얼음 추출 외부 GREEN only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            }
            else if( display_test_flick_timer_100ms <= 12 )
            {
                // 얼음 추출 외부 BLUE only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            }
            else if( display_test_flick_timer_100ms <= 15 )
            {
                // 얼음 추출 내부 RED only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_RED );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            }
            else if( display_test_flick_timer_100ms <= 18 )
            {
                // 얼음 추출 내부 GREEN only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            }
            else if( display_test_flick_timer_100ms <= 21 )
            {
                // 얼음 추출 내부 BLUE only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            }
            else if( display_test_flick_timer_100ms <= 24 )
            {
                Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
                Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, EXTRACT__DIMMING__40_PERCETN );
            }
            else
            {
                display_test_flick_timer_100ms = 24;
                Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
                Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, EXTRACT__DIMMING__40_PERCETN );
            }

            /* WHITE */
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
            break;

		case DISPLAY_TEST_BTN_EXTRACT: // [물 추출버튼] 클릭 후
            display_test_flick_timer_100ms++;
			if(display_test_flick_timer_100ms <= 3) /* 0.1 ~ 1초 구간 */
			{
                /* WHITE */
                Bit4_Front_Under_Water_White_Extract = SET;
                make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
			}
            else if(display_test_flick_timer_100ms <= 6) /* 1 ~ 2초 구간 */
			{
                /* RED */
				Bit4_Front_Under_Water_White_Extract = SET;
                make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_RED );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
			}
            else if(display_test_flick_timer_100ms <= 9)  /* 2 ~ 3초 구간 */
			{
                /* GREEN */
				Bit4_Front_Under_Water_White_Extract = SET;
                make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
			}
            else if(display_test_flick_timer_100ms <= 12)
            {
                /* BLUE */
				Bit4_Front_Under_Water_White_Extract = SET;
                make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
            }
            else if(display_test_flick_timer_100ms <= 15)
            {
                Bit4_Front_Under_Water_White_Extract = CLEAR;
                make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );

                display_test_flick_timer_100ms = 0;
                Disp_test_step = DISPLAY_TEST_FINISH;
            }
            else
            {
                display_test_flick_timer_100ms = 0;
                Disp_test_step = DISPLAY_TEST_FINISH;

                /* 마무리하기 직전에 필터커버 체결여부 캡쳐 [박용우님 요청] 250722 CH.PARK */
                bit_filter_cover = pREED_FILTER_COVER;
                bit_filter_cover_old = bit_filter_cover;
                bit_is_cover_checked = (bit)CLEAR;
            }
			break;

		case DISPLAY_TEST_FINISH: // 검사완료 -> 점멸

            bit_filter_cover = pREED_FILTER_COVER;

            /* 필터커버 리드스위치 [감지 <-> 미감지] 조건으로 판단 250314 CH.PARK */
            if(bit_filter_cover != bit_filter_cover_old)
            {
                bit_filter_cover_old = bit_filter_cover;
                play_voice_test_mode_151();
                bit_is_cover_checked = (bit)TRUE;
            }
            else {  }

			if( (gu8_front_left_led == 0x00)
            && (gu8_front_left_led_2 == 0x00)
			&& (gu8_front_right_led == 0x00)
			&& (gu8_front_temp_setting_bar_led == 0x00)
			&& (gu8_front_amount_setting_bar_led == 0x00)
			&& (gu8_front_center_recipe_led == 0x00)
			&& (gu8_front_select_led == 0x00)
			&& (gu8_front_setting_led == 0x00)
            && (gu8_front_setting_led_2 == 0x00)
			&& (gu8_front_under_text_led == 0x00)
			&& (gu8_front_under_icon_led == 0x00)
			&& (is_display_test_flick == CLEAR)
            && (bit_is_cover_checked != (bit)CLEAR)
            )
			{
				is_display_test_flick = SET;
				display_test_rgb_color = TEST_MODE_RGB_OFF;
				gu8_rgb_red_on_time = 0;
				gu8_rgb_green_on_time = 0;
				gu8_rgb_blue_on_time = 0;
				gu8_rgb_pwm_period = 0;
			}

			if(is_display_test_flick == SET)
			{
                display_test_flick_timer_100ms++;
				if(display_test_flick_timer_100ms >= 5)
				{
					display_test_flick_timer_100ms = 0;
					display_flick_state ^= SET;

					if(display_flick_state == SET)
					{
						on_all_control_led();
                        make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                        make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                        make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
                    }
					else
					{
						off_all_control_led();
                        make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                        make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                        make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
					}
				}

			}

			break;

		default:
			break;


	}
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Display_Test_Main(void)
{
    /////all_breath_stop();
    all_duty_100_percent();

    if( F_FW_Version_Display_Mode != SET )
    {
        display_version();
    }
    else
    {
        display_test_error();           // 에러검출
        display_test_factory_input();
        display_test_factory_job();

        fnd_left_display_test();
        fnd_right_display_test();

        /*..hui [23-6-30오후 1:22:01] 디스플레이 검사할때도 DC FAN은 항시 ON하도록..*/
        pDC_FAN = SET;
    }

    initial_all_data();
    initial_ice_tray();
    motor_ice_door_output();
    motor_ice_select_output();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_test_factory_input(void)
{
    if( gu8_front_temp_fnd_hundred == 0
    && gu8_front_temp_fnd_ten == 0
    && gu8_front_temp_fnd_one == 0

    && gu8_front_amount_fnd_hundred == 0
    && gu8_front_amount_fnd_ten == 0
    && gu8_front_amount_fnd_one == 0

    && gu8_front_left_led == 0
    && gu8_front_right_led == 0
    && gu8_front_temp_setting_bar_led == 0
    && gu8_front_amount_setting_bar_led == 0
    && gu8_front_center_recipe_led == 0
    && gu8_front_select_led == 0
    && gu8_front_setting_led == 0
    && gu8_front_under_text_led == 0
    && gu8_front_under_icon_led == 0

    // && gu8_front_rcv_filter_reed_data == 1
    && gu8_uart_tray_initial_step == 3
    && gu8_display_test_error == 0 )
    {
        F_cds_detect = 1;
    }
    else{}

    if( bit_uart_ice_water_test_finish == SET
    && bit_uart_ice_test_finish == SET
    && bit_uart_hot_test_finish == SET
    && bit_uart_ambient_test_finish == SET
    && bit_uart_cold_tst_finish == SET
    && bit_uart_amount_test_finish == SET
    && bit_uart_ice_off_test_finish == SET
    && bit_uart_ice_size_test_finish == SET
    && bit_uart_hot_lock_test_finish == SET
    && bit_uart_fast_ice_test_finish == SET
    && bit_uart_cold_temp_test_finish == SET
    && bit_uart_sleep_mode_test_finish == SET
    && bit_uart_ice_lock_test_finish == SET
    && bit_uart_all_lock_test_finish == SET
    && bit_uart_my_test_finish == SET
    && bit_uart_cold_off_finish == SET
    && bit_uart_water_extract_test_finish == SET
    && bit_uart_ice_extract_test_finish == SET )
    {
        bit_touch_test_finish = SET;

        /* 추출버튼 먼저 눌렀을 때 검사 이상해지는 버그 개선 250718 CH.PARK */
        gu8_ice_color_change_timer = 23;
        gu8_water_color_change_timer = 14;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_test_error(void)
{
    if(gu16_AD_Result_Cold <= TEMP_SENSOR_SHORT || gu16_AD_Result_Cold >= TEMP_SENSOR_OPEN)                     /* 냉수 온도센서 에러 */
    {
        gu8_display_test_error = 1;
    }
    else if(gu16_AD_Result_Hot_Heater <= TEMP_SENSOR_SHORT || gu16_AD_Result_Hot_Heater >= TEMP_SENSOR_OPEN)    /* 온수 히터 온도센서 에러 */
    {
        gu8_display_test_error = 2;
    }
    else if(gu16_AD_Result_Hot_Out <= TEMP_SENSOR_SHORT || gu16_AD_Result_Hot_Out >= TEMP_SENSOR_OPEN)          /* 온수 추출 온도센서 에러 */
    {
        gu8_display_test_error = 3;
    }
    else if(gu16_AD_Result_Hot_In <= TEMP_SENSOR_SHORT || gu16_AD_Result_Hot_In >= TEMP_SENSOR_OPEN)            /* 온수 입수 온도센서 에러 */
    {
        gu8_display_test_error = 4;
    }
    else if(gu16_AD_Result_Room <= TEMP_SENSOR_SHORT || gu16_AD_Result_Room >= TEMP_SENSOR_OPEN)                /* 정수 온도센서 에러 */
    {
        gu8_display_test_error = 5;
    }
    else if(gu16_AD_Result_Amb <= TEMP_SENSOR_SHORT || gu16_AD_Result_Amb >= TEMP_SENSOR_OPEN)                  /* 외기 온도센서 에러 */
    {
        gu8_display_test_error = 6;
    }
    else if(gu16_AD_Result_Amb_Side <= TEMP_SENSOR_SHORT || gu16_AD_Result_Amb_Side >= TEMP_SENSOR_OPEN)
    {
       gu8_display_test_error = 7;
    }
    else if(gu16_AD_Result_Eva_First <= TEMP_SENSOR_SHORT || gu16_AD_Result_Eva_First >= TEMP_SENSOR_OPEN)
    {
       gu8_display_test_error = 8;
    }
    else if(pLEVEL_ICE_DRAIN_LOW == SET)  /* 드레인 저수위 감지 에러 */
    {
        gu8_display_test_error = 9;
    }
    else if(pLEVEL_ICE_DRAIN_HIGH == SET) /* 드레인 만수위 감지 에러 */
    {
        gu8_display_test_error = 10;
    }
    else if(gu16ADLeakage > 615)          /* 누수센서 에러 */
    {
        gu8_display_test_error = 11;
    }
    else if(pREED_FILTER == SET )         /* 필터 미체결 */
    {
        gu8_display_test_error = 14;
    }
    else if(GET_INNER_DOOR_REED_SW() == ACTIVE_LOW_NO_DETECTED)    // [2025-11-17] CH.PARK 아이스도어 리드 미감지
    {
        gu8_display_test_error = 15;
    }
    else
    {
        if( bit_touch_test_finish == SET )
        {
            if( bit_display_test_filter_cover_error == SET )     // 필터커버
            {
                gu8_display_test_error = 12;
            }
            else if( bit_display_test_tank_cover_error == SET )            // 얼음탱크 커버
            {
                gu8_display_test_error = 13;
            }
            else
            {
                gu8_display_test_error = 0;
            }
        }
        else
        {
            gu8_display_test_error = 0;
        }
    }

    if( gu8_display_test_error != 0 )
    {
        if( bit_display_error_state == CLEAR )
        {
            bit_display_error_state = SET;
            play_melody_warning_197();
        }
        else{}
    }
    else
    {
        bit_display_error_state = CLEAR;

    }

    gu8_reed_first_read_timer++;

    if( gu8_reed_first_read_timer >= 30 )
    {
        gu8_reed_first_read_timer = 30;
        bit_tank_cover_first_read = SET;
        bit_side_cover_first_read = SET;
    }
    else{}

    // 미체결 -> 체결 상태가 되어야만 에러 해제
    if(bit_display_test_filter_cover_old != pREED_FILTER_COVER)
    {
        bit_display_test_filter_cover_old = pREED_FILTER_COVER;
        bit_test_filter_cover_flag = SET;

        if(pREED_FILTER_COVER == CLEAR)
        {
            bit_display_test_filter_cover_error = CLEAR;
        }
        else
        {
            bit_display_test_filter_cover_error = SET;
        }
    }
    else
    {
        if(bit_test_filter_cover_flag == CLEAR)
        {
            bit_display_test_filter_cover_error = SET;
        }
        else {  }
    }

    if(bit_display_test_tank_cover_old != pREED_TANK_COVER_2)
    {
        bit_display_test_tank_cover_old = pREED_TANK_COVER_2;
        bit_test_tank_cover_flag = SET;

        if(pREED_TANK_COVER_2 == CLEAR)
        {
            bit_display_test_tank_cover_error = CLEAR;
        }
        else
        {
            bit_display_test_tank_cover_error = SET;
        }
    }
    else
    {
        if(bit_test_tank_cover_flag == CLEAR)
        {
            bit_display_test_tank_cover_error = SET;
        }
        else {  }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_test_factory_job(void)
{
    led_blink_timer();

    if( gu8_display_test_error != 0 )
    {
        gu8_front_amount_fnd_hundred = 0;
        gu8_front_amount_fnd_ten = 0;
        gu8_front_amount_fnd_one = 0;

        gu8_front_left_led = 0;
        gu8_front_left_led_2 = 0;
        gu8_front_right_led = 0;
        gu8_front_temp_setting_bar_led = 0;
        gu8_front_amount_setting_bar_led = 0;
        gu8_front_center_recipe_led = 0;

        gu8_front_select_led = 0;
        gu8_front_setting_led = 0;
        gu8_front_setting_led_2 = 0;
        gu8_front_under_text_led = 0;
        gu8_front_under_icon_led = 0;

        return;
    }
    else{}

    /* [얼음물] 키 입력 */
    if(gu8_uart_ice_water_test_input == 1)
    {
        // 얼음물
        Bit1_Front_Led_Ice_Water_Select = (F_cds_detect & F_Wink_500ms);

        // MY 1,2,3
        Bit3_Front_Center_MY_1_Text = (F_cds_detect & F_Wink_500ms);
        Bit4_Front_Center_MY_2_Text = (F_cds_detect & F_Wink_500ms);
        Bit5_Front_Center_MY_3_Text = (F_cds_detect & F_Wink_500ms);

        // 출수파우셋
        Bit0_Front_Left_Led_Eff_Faucet_Text = (F_cds_detect & F_Wink_500ms);
        bit_uart_ice_water_test_finish = SET;
    }
    else
    {
        if( bit_uart_ice_water_test_finish == CLEAR )
        {
            // 얼음물
            Bit1_Front_Led_Ice_Water_Select = SET;

            // MY 1,2,3
			Bit3_Front_Center_MY_1_Text = SET;
            Bit4_Front_Center_MY_2_Text = SET;
            Bit5_Front_Center_MY_3_Text = SET;

            // 출수파우셋
            Bit0_Front_Left_Led_Eff_Faucet_Text = SET;
        }
        else
        {
            gu8_uart_ice_water_test_input = 1;
        }
    }

    /* [얼음] 키 입력 */
    if(gu8_uart_ice_test_input == 1)
    {
        // 얼음
        Bit0_Front_Led_Ice_Select = (F_cds_detect & F_Wink_500ms);

        // 라면, 드립커피, 차
        Bit0_Front_Center_Recipe_Ramen_Text = (F_cds_detect & F_Wink_500ms);
        Bit2_Front_Center_Recipe_Drip_Coffee_Text = (F_cds_detect & F_Wink_500ms);
        Bit1_Front_Center_Tea_Text = (F_cds_detect & F_Wink_500ms);

        // 얼음부족
        Bit1_Front_Left_Led_Ice_Shortae_Text = (F_cds_detect & F_Wink_500ms);

        // 얼음 일반/조각
        Bit6_Front_Under_Txt_Led_Ice_Normal = (F_cds_detect & F_Wink_500ms);
        Bit7_Front_Under_Txt_Led_Ice_Piece = (F_cds_detect & F_Wink_500ms);
        bit_uart_ice_test_finish = SET;
    }
    else
    {
        if( bit_uart_ice_test_finish == CLEAR )
        {
            // 얼음
            Bit0_Front_Led_Ice_Select = SET;

            // 라면, 드립커피, 차
            Bit0_Front_Center_Recipe_Ramen_Text = SET;
            Bit2_Front_Center_Recipe_Drip_Coffee_Text = SET;
            Bit1_Front_Center_Tea_Text = SET;

            // 얼음부족
            Bit1_Front_Left_Led_Ice_Shortae_Text = SET;

            // 얼음 일반/조각
            Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
            Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
        }
        else
        {
            gu8_uart_ice_test_input = 1;
        }
    }

    /* [온수] 키 입력 */
    if(gu8_uart_hot_test_input == 1)
    {
        // 온수
        Bit2_Front_Led_Hot_Select = (F_cds_detect & F_Wink_500ms);

        // 얼음가득, 절전아이콘
        Bit0_Front_Left_Led_Ice_Full_Text = (F_cds_detect & F_Wink_500ms);
        Bit4_Front_Left_Led_Sleep_Icon = (F_cds_detect & F_Wink_500ms);

        // 얼음파우셋
        Bit1_Front_Left_Led_Ice_Faucet_Text = (F_cds_detect & F_Wink_500ms);
        bit_uart_hot_test_finish = SET;
    }
    else
    {
        if( bit_uart_hot_test_finish == CLEAR )
        {
            // 온수
			Bit2_Front_Led_Hot_Select = SET;

            // 얼음가득, 절전아이콘
            Bit0_Front_Left_Led_Ice_Full_Text = SET;
            Bit4_Front_Left_Led_Sleep_Icon = SET;

            // 얼음파우셋
            Bit1_Front_Left_Led_Ice_Faucet_Text = SET;
        }
        else
        {
            gu8_uart_hot_test_input = 1;
        }
    }

    /* [정수] 키 입력 */
    if(gu8_uart_purify_test_input == 1)
    {
        // 정수
        Bit3_Front_Led_Ambient_Select = (F_cds_detect & F_Wink_500ms);

        // UV살균, 고온살균
        Bit2_Front_Left_Led_UV_Ster_Text = (F_cds_detect & F_Wink_500ms);
        Bit3_Front_Left_Led_Hot_Ster_Text = (F_cds_detect & F_Wink_500ms);

        // :
        Bit6_Front_Left_Led_Clock_Colon_Icon = (F_cds_detect & F_Wink_500ms);

        // 얼음트레이
        Bit2_Front_Left_Led_Ice_Tray_Text = (F_cds_detect & F_Wink_500ms);

        bit_uart_ambient_test_finish = SET;
    }
    else
    {
        if( bit_uart_ambient_test_finish == CLEAR )
        {
            // 정수
			Bit3_Front_Led_Ambient_Select = SET;

            // UV살균, 고온살균
            Bit2_Front_Left_Led_UV_Ster_Text = SET;
            Bit3_Front_Left_Led_Hot_Ster_Text = SET;

            // :
            Bit6_Front_Left_Led_Clock_Colon_Icon = SET;

            // 얼음트레이
            Bit2_Front_Left_Led_Ice_Tray_Text = SET;
        }
        else
        {
            gu8_uart_purify_test_input = 1;
        }
    }

    /* [냉수] 키 입력 */
    if(gu8_uart_cold_test_input == 1)
    {
        // 냉수
        Bit4_Front_Led_Cold_Select = (F_cds_detect & F_Wink_500ms);

        // 빠른제빙 아이콘
        Bit4_Front_Led_Icon_Fast_Ice = (F_cds_detect & F_Wink_500ms);

        // 'C
        Bit7_Front_Left_Led_Celcius_oC_Icon = (F_cds_detect & F_Wink_500ms);
        bit_uart_cold_tst_finish = SET;
    }
    else
    {
        if( bit_uart_cold_tst_finish == CLEAR )
        {
            // 냉수
			Bit4_Front_Led_Cold_Select = SET;

            // 빠른제빙 아이콘
            Bit4_Front_Led_Icon_Fast_Ice = SET;

            // 'C
            Bit7_Front_Left_Led_Celcius_oC_Icon = SET;
        }
        else
        {
            gu8_uart_cold_test_input = 1;
        }
    }

    /* [용량] 키 입력 */
    if(gu8_uart_amount_test_input == 1)
    {
        // 용량
        Bit5_Front_Led_Amount_Select = (F_cds_detect & F_Wink_500ms);

        // 해,구름,우산
        Bit2_Front_Right_Led_Sunny_Icon = (F_cds_detect & F_Wink_500ms);
        Bit3_Front_Right_Led_Cloud_Icon = (F_cds_detect & F_Wink_500ms);
        Bit4_Front_Right_Led_Rain_Icon = (F_cds_detect & F_Wink_500ms);
        bit_uart_amount_test_finish = SET;
    }
    else
    {
        if( bit_uart_amount_test_finish == CLEAR )
        {
            // 용량
			Bit5_Front_Led_Amount_Select = SET;

            // 해,구름,우산
            Bit2_Front_Right_Led_Sunny_Icon = SET;
            Bit3_Front_Right_Led_Cloud_Icon = SET;
            Bit4_Front_Right_Led_Rain_Icon = SET;
        }
        else
        {

            gu8_uart_amount_test_input = 1;
        }
    }

    /* [MY] 입력 시  */
    if(gu8_uart_setting_my_test_input == 1)
    {
        // MY
        Bit6_Front_Led_My_Select = (F_cds_detect & F_Wink_500ms);

        // 얼음저장고
        Bit3_Front_Left_Led_Ice_Storage_Box_Text = (F_cds_detect & F_Wink_500ms);

        // 필터세척
        Bit4_Front_Right_Led_Filter_Clean_Text = (F_cds_detect & F_Wink_500ms);

        // .
        Bit5_Front_Right_Seg_Dot_Text = (F_cds_detect & F_Wink_500ms);

        bit_uart_my_test_finish = SET;
    }
    else
    {
        if(bit_uart_my_test_finish == CLEAR)
        {
            // MY
			Bit6_Front_Led_My_Select = SET;

            // 얼음저장고
            Bit3_Front_Left_Led_Ice_Storage_Box_Text = SET;

            // 필터세척
            Bit4_Front_Right_Led_Filter_Clean_Text = SET;

            // .
            Bit5_Front_Right_Seg_Dot_Text = SET;
        }
        else
        {
            gu8_uart_setting_my_test_input = 1;
        }
    }

    /* [얼음OFF] 키 입력 */
    if(gu8_uart_setting_ice_off_test_input == 1)
    {
        // 얼음OFF
        Bit1_Front_Led_Ice_Off = (F_cds_detect & F_Wink_500ms);

        // WIFI ICON
        Bit0_Front_Right_Led_Wifi_Icon_White = (F_cds_detect & F_Wink_500ms);
        Bit1_Front_Right_Led_Wifi_Icon_Blue = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_ice_off_test_finish == CLEAR)
        {
            gu8_ice_rgb_test_step = 1;
            bit_uart_ice_off_test_finish = SET;
        }
    }
    else
    {
        if( bit_uart_ice_off_test_finish == CLEAR )
        {
            // 얼음OFF
            Bit1_Front_Led_Ice_Off = SET;

            // WIFI ICON
            Bit0_Front_Right_Led_Wifi_Icon_White = SET;
            Bit1_Front_Right_Led_Wifi_Icon_Blue = SET;
        }
        else
        {
            gu8_uart_setting_ice_off_test_input = 1;
        }
    }

    /* [얼음대소] 키입력 */
    if(gu8_uart_setting_ice_size_test_input == 1)
    {
        // 얼음크기
        Bit0_Front_Led_Ice_Size = (F_cds_detect & F_Wink_500ms);

        // L, ml
        Bit7_Front_Right_Led_ml_Icon = (F_cds_detect & F_Wink_500ms);
        Bit6_Front_Right_Led_Liter_L_Icon = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_ice_size_test_finish == CLEAR)
        {
            gu8_ice_rgb_test_step = 2;
            bit_uart_ice_size_test_finish = SET;
        }
    }
    else
    {
        if( bit_uart_ice_size_test_finish == CLEAR )
        {
            // 얼음크기
			Bit0_Front_Led_Ice_Size = SET;

            // L, ml
            Bit7_Front_Right_Led_ml_Icon = SET;
            Bit6_Front_Right_Led_Liter_L_Icon = SET;
        }
        else
        {
            gu8_uart_setting_ice_size_test_input = 1;
        }
    }

    /* [온수잠금] 키 입력 */
    if(gu8_uart_setting_hot_lock_test_input == 1)
    {
        // 온수잠금
        Bit2_Front_Led_Hot_Lock_Text = (F_cds_detect & F_Wink_500ms);

        // 온수잠금 아이콘
        Bit3_Front_Led_Icon_Led_Hot_Locker = (F_cds_detect & F_Wink_500ms);

        // %
        Bit5_Front_Right_Led_Percent_Icon = (F_cds_detect & F_Wink_500ms);

        // 냉수 DOT WHITE
        Bit5_Front_Led_Icon_Comp_Blue = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_hot_lock_test_finish == CLEAR)
        {
            gu8_ice_rgb_test_step = 3;
            bit_uart_hot_lock_test_finish = SET;
        }
    }
    else
    {
        if( bit_uart_hot_lock_test_finish == CLEAR )
        {
            // 온수잠금
            Bit2_Front_Led_Hot_Lock_Text = SET;

            // 온수잠금 아이콘
            Bit3_Front_Led_Icon_Led_Hot_Locker = SET;

            // %
            Bit5_Front_Right_Led_Percent_Icon = SET;

            // 냉수 DOT WHITE
            Bit5_Front_Led_Icon_Comp_Blue = SET;
        }
        else
        {
            gu8_uart_setting_hot_lock_test_input = 1;
        }
    }

    /* [빠른제빙] 키 입력 */
    if(gu8_uart_setting_fast_ice_test_input == 1)
    {
        // 빠른제빙
        Bit3_Front_Led_Ice_First = (F_cds_detect & F_Wink_500ms);

        // 냉수 DOT BLUE
        Bit6_Front_Led_Icon_Comp_White = (F_cds_detect & F_Wink_500ms);

        // 단계
        Bit5_Front_Left_Led_Step_Text = (F_cds_detect & F_Wink_500ms);

        // WELCOME LED (좌측)
        Bit6_Front_Under_Led_Welcome_2 = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_fast_ice_test_finish == CLEAR)
        {
            gu8_ice_rgb_test_step = 4;
            bit_uart_fast_ice_test_finish = SET;
        }
    }
    else
    {
        if( bit_uart_fast_ice_test_finish == CLEAR )
        {
            // 빠른제빙
			Bit3_Front_Led_Ice_First = SET;

            // 냉수 DOT BLUE
            Bit6_Front_Led_Icon_Comp_White = SET;

            // 단계
            Bit5_Front_Left_Led_Step_Text = SET;

            // WELCOME LED (좌측)
            Bit6_Front_Under_Led_Welcome_2 = SET;
        }
        else
        {
            gu8_uart_setting_fast_ice_test_input = 1;
        }
    }

    /* [냉수강약] 키 입력 */
    if(gu8_uart_setting_cold_temp_test_input == 1)
    {
        // 온도바 5개
        gu8_hot_temp_off_timer++;
        if(gu8_hot_temp_off_timer <= 3)
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
        }
        else if(gu8_hot_temp_off_timer <= 6)
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
        }
        else if(gu8_hot_temp_off_timer <= 9)
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
        }
        else if(gu8_hot_temp_off_timer <= 12)
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
        }
        else
        {
            gu8_hot_temp_off_timer = 13;
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = (F_cds_detect & F_Wink_500ms);
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = (F_cds_detect & F_Wink_500ms);
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = (F_cds_detect & F_Wink_500ms);
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = (F_cds_detect & F_Wink_500ms);
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = (F_cds_detect & F_Wink_500ms);
        }

        // 냉수온도
        Bit4_Front_Led_Cold_Temp = (F_cds_detect & F_Wink_500ms);

        // 강 | 약
        Bit3_Front_Under_Txt_Led_Cold_High = (F_cds_detect & F_Wink_500ms);
        Bit4_Front_Under_Txt_Led_Cold_Center_Bar = (F_cds_detect & F_Wink_500ms);
        Bit5_Front_Under_Txt_Led_Cold_Low = (F_cds_detect & F_Wink_500ms);

        // WELCOME LED (우측)
        Bit5_Front_Under_Led_Welcome = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_cold_temp_test_finish == CLEAR)
        {
            gu8_ice_rgb_test_step = 5;
            bit_uart_cold_temp_test_finish = SET;
        }
    }
    else
    {
        if( bit_uart_cold_temp_test_finish == CLEAR )
        {
            // 냉수온도
			Bit4_Front_Led_Cold_Temp = SET;

            // 강 | 약
			Bit3_Front_Under_Txt_Led_Cold_High = SET;
			Bit4_Front_Under_Txt_Led_Cold_Center_Bar = SET;
			Bit5_Front_Under_Txt_Led_Cold_Low = SET;

            // 온도바 5개
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = SET;

            // WELCOME LED (우측)
            Bit5_Front_Under_Led_Welcome = SET;

            gu8_hot_temp_off_timer = 0;
        }
        else
        {
            gu8_uart_setting_cold_temp_test_input = 1;
        }
    }

    /* [냉수OFF] 키 입력 */
    if(gu8_uart_setting_cold_off_input == 1)
    {
        // 냉수OFF
        Bit6_Front_Led_Cold_Off = (F_cds_detect & F_Wink_500ms);

        // 얼음잠금 아이콘
        Bit2_Front_Led_Icon_Led_Ice_Locker = (F_cds_detect & F_Wink_500ms);

        // 대 | 소
        Bit0_Front_Under_Txt_Led_Ice_Large = (F_cds_detect & F_Wink_500ms);
        Bit1_Front_Under_Txt_Led_Ice_Center_bar = (F_cds_detect & F_Wink_500ms);
        Bit2_Front_Under_Txt_Led_Ice_Small = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_cold_off_finish == CLEAR)
        {
            bit_uart_cold_off_finish = SET;
            gu8_ice_rgb_test_step = 6;
        }
    }
    else
    {
        if(bit_uart_cold_off_finish == CLEAR)
        {
            // 냉수OFF
            Bit6_Front_Led_Cold_Off = SET;

            // 얼음잠금 아이콘
            Bit2_Front_Led_Icon_Led_Ice_Locker = SET;

            // 대 | 소
            Bit0_Front_Under_Txt_Led_Ice_Large = SET;
            Bit1_Front_Under_Txt_Led_Ice_Center_bar = SET;
            Bit2_Front_Under_Txt_Led_Ice_Small = SET;
        }
        else
        {
            gu8_uart_setting_cold_off_input = 1;
        }
    }

    /* [취침모드] 키 입력 */
    if(gu8_uart_setting_sleep_mode_test_input == 1)
    {
        // 취침모드
        Bit5_Front_Led_Sleep_Mode_Text = (F_cds_detect & F_Wink_500ms);

        gu8_cup_level_off_timer++;
        if(gu8_cup_level_off_timer <= 3)
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
        }
        else if(gu8_cup_level_off_timer <= 6)
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
        }
        else if(gu8_cup_level_off_timer <= 9)
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
        }
        else if(gu8_cup_level_off_timer <= 12)
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
        }
        else
        {
            gu8_cup_level_off_timer = 13;
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = (F_cds_detect & F_Wink_500ms);
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = (F_cds_detect & F_Wink_500ms);
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = (F_cds_detect & F_Wink_500ms);
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = (F_cds_detect & F_Wink_500ms);
            Bit4_Front_Led_Amount_Setting_Bar_Continue = (F_cds_detect & F_Wink_500ms);
        }

        if(bit_uart_sleep_mode_test_finish == CLEAR)
        {
            bit_uart_sleep_mode_test_finish = SET;
            gu8_water_rgb_test_step = 1;
        }
    }
    else
    {
        if( bit_uart_sleep_mode_test_finish == CLEAR )
        {
            // 취침모드
			Bit5_Front_Led_Sleep_Mode_Text = SET;

            // 용량바 5개
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;

            gu8_cup_level_off_timer = 0;

        }
        else
        {
            gu8_uart_setting_sleep_mode_test_input = 1;
        }
    }

    /* [얼음잠금] 키 입력 */
    if(gu8_uart_setting_ice_lock_test_input == 1)
    {
        Bit0_Front_Led_Ice_Lock = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_ice_lock_test_finish == CLEAR)
        {
            bit_uart_ice_lock_test_finish = SET;
            gu8_water_rgb_test_step = 2;
        }
    }
    else
    {
        if( bit_uart_ice_lock_test_finish == CLEAR )
        {
            Bit0_Front_Led_Ice_Lock = SET;
        }
        else
        {
            gu8_uart_setting_ice_lock_test_input = 1;
        }
    }

    /* [전체잠금] 키 입력 */
    if(gu8_uart_setting_all_lock_test_input == 1)
    {
        Bit1_Front_Led_All_Lock = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_all_lock_test_finish == CLEAR)
        {
            bit_uart_all_lock_test_finish = SET;
            gu8_water_rgb_test_step = 3;
        }
    }
    else
    {
        if( bit_uart_all_lock_test_finish == CLEAR )
        {
            Bit1_Front_Led_All_Lock = SET;
        }
        else
        {
            gu8_uart_setting_all_lock_test_input = 1;
        }
    }

    /* [냉온정 추출] 키 */
    if(gu8_water_ext_test_input == 1)
    {
        gu8_water_color_change_timer++;

        if( gu8_water_color_change_timer <= 3 )
        {
            gu8_water_rgb_test_step = 0;
        }
        else if( gu8_water_color_change_timer <= 6 )
        {
            gu8_water_rgb_test_step = 1;
        }
        else if( gu8_water_color_change_timer <= 9 )
        {
            gu8_water_rgb_test_step = 2;
        }
        else if( gu8_water_color_change_timer <= 12 )
        {
            gu8_water_rgb_test_step = 3;
        }
        else if( gu8_water_color_change_timer <= 15 )
        {
            // gu8_water_color_change_timer = 15;
            gu8_water_rgb_test_step = 4;
        }
        else
        {
            // gu8_water_color_change_timer = 15;
            // gu8_water_rgb_test_step = 0;
        }
    }
    else
    {
        gu8_water_color_change_timer = 0;
    }

    /* [얼음 추출] 키 입력 */
    if(gu8_ice_ext_test_input == 1)
    {
        gu8_ice_color_change_timer++;

        if( gu8_ice_color_change_timer <= 3 )
        {
            gu8_ice_rgb_test_step = 0;
        }
        else if( gu8_ice_color_change_timer <= 6 )
        {
            gu8_ice_rgb_test_step = 1;
        }
        else if( gu8_ice_color_change_timer <= 9 )
        {
            gu8_ice_rgb_test_step = 2;
        }
        else if( gu8_ice_color_change_timer <= 12 )
        {
            gu8_ice_rgb_test_step = 3;
        }
        else if( gu8_ice_color_change_timer <= 15 )
        {
            gu8_ice_rgb_test_step = 4;
        }
        else if( gu8_ice_color_change_timer <= 18 )
        {
            gu8_ice_rgb_test_step = 5;
        }
        else if( gu8_ice_color_change_timer <= 21 )
        {
            gu8_ice_rgb_test_step = 6;
        }
        else if( gu8_ice_color_change_timer <= 24 )
        {
            // gu8_ice_color_change_timer = 24;
            gu8_ice_rgb_test_step = 7;
        }
        else
        {
            // gu8_ice_color_change_timer = 24;
            // gu8_ice_rgb_test_step = 0;
        }
    }
    else
    {
        gu8_ice_color_change_timer = 0;
    }

    switch (gu8_ice_rgb_test_step)
    {
        case 0:
            // 내부 외부 white LED only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__40_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__40_PERCENT );
            break;

        case 1:
            // 얼음 추출 외부 RED only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_RED );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            break;

        case 2:
            // 얼음 추출 외부 GREEN only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            break;

        case 3:
            // 얼음 추출 외부 BLUE only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            break;

        case 4:
            // 얼음 추출 내부 RED only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_RED );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            break;

        case 5:
            // 얼음 추출 내부 GREEN only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            break;

        case 6:
            // 얼음 추출 내부 BLUE only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );

            break;

        case 7:
            // 완료
            bit_uart_ice_extract_test_finish = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = (F_cds_detect & F_Wink_500ms);
            Bit1_Front_Under_Ice_Inner_White_Extract = (F_cds_detect & F_Wink_500ms);
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__40_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__40_PERCENT );
            break;

        default:

            break;
    }

    switch (gu8_water_rgb_test_step)
    {
        case 0:
            // white LED only
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__40_PERCENT );

            break;

        case 1:
            // 냉온정 추출 RED only
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_RED );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
            break;

        case 2:
            // 냉온정 추출 GREEN only
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
            break;

        case 3:
            // 냉온정 추출 BLUE only
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
            break;

        case 4:
            // 완료
            bit_uart_water_extract_test_finish = SET;

            Bit4_Front_Under_Water_White_Extract = (F_cds_detect & F_Wink_500ms);
            make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
            break;

        default:

            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

#ifdef _DISPLAY_FCT_SUB_LINE_
void Display_Test_Mode_Key_Short_Input(U32 u32key_input_value)
{
	switch(u32key_input_value)
	{
        case KEY_ICE_WATER_SELECT:
			if(Disp_test_step == DISPLAY_TEST_START)
			{
				Disp_test_step++;
				play_voice_test_mode_151();
			}
			break;

        case KEY_ICE_SELECT:
            if(Disp_test_step == DISPLAY_TEST_BTN1)
			{
                if(gu8_ice_water_select_display_timer  >= 10)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_HOT_SELECT:
			if(Disp_test_step == DISPLAY_TEST_BTN2)
			{
                if(gu8_ice_select_display_timer >= 14)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_AMBIENT_SELECT:
			if(Disp_test_step == DISPLAY_TEST_BTN3)
			{
                if(gu8_hot_select_display_timer >= 8)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_COLD_SELECT:
			if(Disp_test_step == DISPLAY_TEST_BTN4)
			{
                if(gu8_pure_select_display_timer >= 10)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_AMOUNT_SELECT:
			if(Disp_test_step == DISPLAY_TEST_BTN5)
			{
                if(gu8_cold_select_display_timer >= 6)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_MY_SELECT:
			if(Disp_test_step == DISPLAY_TEST_BTN6)
			{
                if(gu8_amount_select_display_timer >= 8)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;


		case KEY_SETTING_ICE_OFF:
			if(Disp_test_step == DISPLAY_TEST_BTN6_2)
			{
                if(gu8_my_select_display_timer >= 8)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
            break;

		case KEY_SETTING_ICE_SIZE:
			if(Disp_test_step == DISPLAY_TEST_BTN7)
			{
                if(gu8_ice_off_display_timer >= 6)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_SETTING_HOT_LOCK:
			if(Disp_test_step == DISPLAY_TEST_BTN8)
			{
				if(gu8_ice_size_display_timer >= 6)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_SETTING_ICE_FIRST:
			if(Disp_test_step == DISPLAY_TEST_BTN9)
			{
                if(gu8_hot_lock_display_timer >= 8)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_SETTING_COLD_TEMP:
			if(Disp_test_step == DISPLAY_TEST_BTN10)
			{
                if(gu8_fast_ice_display_timer >= 8)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_COLD_WATER_OFF:
			if(Disp_test_step == DISPLAY_TEST_BTN11)
			{
                if(gu8_left_bar_off_timer >= 20)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_SETTING_SLEEP_MODE:
			if(Disp_test_step == DISPLAY_TEST_BTN12)
			{
				if(gu8_cold_off_display_timer >= 10)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_SETTING_ICE_LOCK:
			if(Disp_test_step == DISPLAY_TEST_BTN13)
			{
                if(gu8_right_bar_off_timer >= 12)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_SETTING_ALL_LOCK:
			if(Disp_test_step == DISPLAY_TEST_BTN14)
			{
				Disp_test_step++;
				play_voice_test_mode_151();
			}
			break;
	}
}
#else
void Display_Test_Mode_Key_Short_Input(U32 u32key_input_value)
{
    play_voice_test_mode_151();

    /* 에러걸렸을 때는 입력값 처리 무시 250320 CH.PARK */
    if( gu8_display_test_error == 0 )
    {
        switch(u32key_input_value)
        {
            case KEY_ICE_SELECT:                        /* [얼음] 키 */
                gu8_uart_ice_test_input++;

                if(gu8_uart_ice_test_input >= 2)
                {
                    gu8_uart_ice_test_input = 0;
                }
                else{}

                break;

            case KEY_ICE_WATER_SELECT:                  /* [얼음물] 키 */
                gu8_uart_ice_water_test_input++;

                if(gu8_uart_ice_water_test_input >= 2)
                {
                    gu8_uart_ice_water_test_input = 0;
                }
                else{}

                break;

            case KEY_HOT_SELECT:                        /* [온수] 키 */

                if( u8FactoryTestMode == UART_TEST_MODE  )
                {
                    if( gu8_water_ext_test_input == 0 )
                    {
                        #if 1
                        gu8_uart_hot_test_input++;

                        if(gu8_uart_hot_test_input >= 2)
                        {
                            gu8_uart_hot_test_input = 0;
                        }
                        else{}
                        #endif

                        gu8_test_water_out = HOT_WATER_SELECT;
                        bit_uart_hot_extract_finish = CLEAR;
                    }
                    else
                    {
                        ///play_voice_beep_warning();
                    }
                }
                else
                {
                    gu8_uart_hot_test_input++;

                    if(gu8_uart_hot_test_input >= 2)
                    {
                        gu8_uart_hot_test_input = 0;
                    }
                    else{}
                }

                break;

            case KEY_AMBIENT_SELECT:                        /* [정수] 키 */

                if( u8FactoryTestMode == UART_TEST_MODE  )
                {
                    if( gu8_water_ext_test_input == 0 )
                    {
                        #if 1
                        gu8_uart_purify_test_input++;

                        if(gu8_uart_purify_test_input >= 2)
                        {
                            gu8_uart_purify_test_input = 0;
                        }
                        else{}
                        #endif

                        gu8_test_water_out = PURE_WATER_SELECT;
                        bit_uart_purify_extract_finish = CLEAR;
                    }
                    else
                    {
                        ///play_voice_beep_warning();
                    }
                }
                else
                {
                    gu8_uart_purify_test_input++;

                    if(gu8_uart_purify_test_input >= 2)
                    {
                        gu8_uart_purify_test_input = 0;
                    }
                    else{}
                }

                break;

            case KEY_COLD_SELECT:                           /* [냉수] 키 */

                if( u8FactoryTestMode == UART_TEST_MODE  )
                {
                    if( gu8_water_ext_test_input == 0 )
                    {
                        #if 1
                        gu8_uart_cold_test_input++;

                        if(gu8_uart_cold_test_input >= 2)
                        {
                            gu8_uart_cold_test_input = 0;
                        }
                        else{}
                        #endif

                        gu8_test_water_out = COLD_WATER_SELECT;
                        bit_uart_cold_extract_finish = CLEAR;
                    }
                    else
                    {
                        ///play_voice_beep_warning();
                    }
                }
                else
                {
                    gu8_uart_cold_test_input++;

                    if(gu8_uart_cold_test_input >= 2)
                    {
                        gu8_uart_cold_test_input = 0;
                    }
                    else{}
                }


                break;

            case KEY_AMOUNT_SELECT:                         /* [용량] 키 */

                gu8_uart_amount_test_input++;

                if(gu8_uart_amount_test_input >= 2)
                {
                    gu8_uart_amount_test_input = 0;
                }
                else{}

                break;

            case KEY_MY_SELECT:                                    /* [MY] 키 */
                gu8_uart_setting_my_test_input++;

                if(gu8_uart_setting_my_test_input >= 2)
                {
                    gu8_uart_setting_my_test_input = 0;
                }
                else {  }
                break;

            case KEY_SETTING_ICE_SIZE:                      /* [얼음대소] 키 */
                gu8_uart_setting_ice_size_test_input++;

                if(gu8_uart_setting_ice_size_test_input >= 2)
                {
                    gu8_uart_setting_ice_size_test_input = 0;
                }
                else{}

                break;

            case KEY_SETTING_ICE_OFF:                       /* [얼음OFF] 키 */

                gu8_uart_setting_ice_off_test_input++;

                if(gu8_uart_setting_ice_off_test_input >= 2)
                {
                    gu8_uart_setting_ice_off_test_input = 0;
                }
                else{}

                break;

            case KEY_SETTING_HOT_LOCK:                      /* [온수잠금] 키 */

                gu8_uart_setting_hot_lock_test_input++;

                if(gu8_uart_setting_hot_lock_test_input >= 2)
                {
                    gu8_uart_setting_hot_lock_test_input = 0;
                }
                else{}

                break;

            case KEY_SETTING_ICE_FIRST:                     /* [빠른제빙] 키 */

                gu8_uart_setting_fast_ice_test_input++;

                if(gu8_uart_setting_fast_ice_test_input >= 2)
                {
                    gu8_uart_setting_fast_ice_test_input = 0;
                }
                else{}

                break;

            case KEY_SETTING_COLD_TEMP:                    /* [냉수강약] 키 */

                gu8_uart_setting_cold_temp_test_input++;

                if(gu8_uart_setting_cold_temp_test_input >= 2)
                {
                    gu8_uart_setting_cold_temp_test_input = 0;
                }
                else{}

                break;

            case KEY_COLD_WATER_OFF:                        /* [냉수OFF] 키 */
                gu8_uart_setting_cold_off_input++;

                if(gu8_uart_setting_cold_off_input >= 2)
                {
                    gu8_uart_setting_cold_off_input = 0;
                }
                else {  }
                break;

            case KEY_SETTING_SLEEP_MODE:                    /* [취침모드] */

                gu8_uart_setting_sleep_mode_test_input++;

                if(gu8_uart_setting_sleep_mode_test_input >= 2)
                {
                    gu8_uart_setting_sleep_mode_test_input = 0;
                }
                else{}

                break;

            case KEY_SETTING_ICE_LOCK:                      /* [얼음잠금] 키 */

                gu8_uart_setting_ice_lock_test_input++;

                if(gu8_uart_setting_ice_lock_test_input >= 2)
                {
                    gu8_uart_setting_ice_lock_test_input = 0;
                }
                else{}

                break;

            case KEY_SETTING_ALL_LOCK:                      /* [전체잠금] 키 */

                gu8_uart_setting_all_lock_test_input++;

                if(gu8_uart_setting_all_lock_test_input >= 2)
                {
                    gu8_uart_setting_all_lock_test_input = 0;
                }
                else{}

                break;
        }
    }
    else
    {

    }
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_tray(void)
{
    /*..hui [25-4-22오후 4:28:51] 탑커버 열려있는동안 지속감지..*/
    if( pREED_TANK_COVER_2 == SET )
    {
        gu8_ice_feeder_test_on_timer++;
        gu8_ice_feeder_test_off_timer = 0;

        if( gu8_ice_feeder_test_on_timer >= 20 )
        {
            gu8_ice_feeder_test_on_timer = 20;
            /*..hui [23-6-30오전 11:10:15] 역회전 -> 정회전으로 변경.. 설차장님..*/
            pMOTOR_ICE_OUT_CW = CLEAR;
            pMOTOR_ICE_OUT_CCW = SET;
        }
        else{}
    }
    else
    {
        gu8_ice_feeder_test_off_timer++;
        gu8_ice_feeder_test_on_timer = 0;

        if( gu8_ice_feeder_test_off_timer >= 20 )
        {
            gu8_ice_feeder_test_off_timer = 20;
            pMOTOR_ICE_OUT_CW = CLEAR;
            pMOTOR_ICE_OUT_CCW = CLEAR;
        }
        else{}
    }

    input_ice_tray_micro_sw();

    /*..hui [19-11-8오후 4:58:12] 아이스트레이 검사 완료시까지 대기..*/
    if( gu8_uart_tray_initial_step >= 3 )
    {
        F_TrayMotorUP = 0;
        F_TrayMotorDOWN = 0;
        return;
    }
    else{}

    if( gu8_uart_tray_initial_step > 0 )
    {
        gu16_uart_tray_initial_max_timer++;

        if(gu16_uart_tray_initial_max_timer >= 900)
        {
            gu16_uart_tray_initial_max_timer = 0;
            F_TrayMotorUP = 0;
            F_TrayMotorDOWN = 0;
            gu8_uart_tray_initial_step = 3;
        }
        else{}
    }
    else{}

    output_ice_tray_motor();

    switch( gu8_uart_tray_initial_step )
    {
        case 0:

            gu16_uart_tray_initial_timer++;

            if(gu16_uart_tray_initial_timer >= 10)
            {
                gu16_uart_tray_initial_timer = 0;
                gu8_uart_tray_initial_step++;
            }
            else{}

            break;

        case 1:

            up_tray_motor();    // 메인라인검사
            gu8_uart_tray_initial_step++;

            break;

        case 2:

            if(F_TrayMotorUP != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
            {
                gu8_uart_tray_initial_step++;
            }
            else{}

            break;

        case 3:

            /*..hui [19-10-28오후 2:40:33] 여기서 대기..*/
            F_TrayMotorUP = 0;
            F_TrayMotorDOWN = 0;
            gu8_uart_tray_initial = 0;
            //gu8_uart_tray_finish = 1;

            break;

        default:

            gu8_uart_tray_initial_step = 0;

            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_test_mode_rgb_color( U8 mu8_color )
{
    /*..hui [24-1-10오후 1:09:30] 주기 10ms로 변경.. 제호 RO CT 기준..*/
    gu8_rgb_pwm_period = 40;

    if( mu8_color == TEST_MODE_RGB_COLOR_RED )
    {
        /*..hui [24-2-22오후 5:01:06] 레드만 40%..*/
        gu8_rgb_red_on_time = 16;
        gu8_rgb_green_on_time = 0;
        gu8_rgb_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_GREEN )
    {
        gu8_rgb_red_on_time = 0;
        gu8_rgb_green_on_time = 40;
        gu8_rgb_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_BLUE )
    {
        /*..hui [24-2-22오후 5:02:02] 그린 40%, 블루 80%..*/
        gu8_rgb_red_on_time = 0;
        gu8_rgb_green_on_time = 16;
        gu8_rgb_blue_on_time = 32;
    }
    else
    {
        gu8_rgb_red_on_time = 0;
        gu8_rgb_green_on_time = 0;
        gu8_rgb_blue_on_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_test_mode_ice_inner_rgb_color( U8 mu8_color )
{
    /*..hui [24-1-10오후 1:09:30] 주기 10ms로 변경.. 제호 RO CT 기준..*/
    gu8_rgb_pwm_period = 40;

    if( mu8_color == TEST_MODE_RGB_COLOR_RED )
    {
        /*..hui [24-2-22오후 5:01:06] 레드만 40%..*/
        gu8_rgb_ice_inner_red_on_time = 16;
        gu8_rgb_ice_inner_green_on_time = 0;
        gu8_rgb_ice_inner_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_GREEN )
    {
        gu8_rgb_ice_inner_red_on_time = 0;
        gu8_rgb_ice_inner_green_on_time = 40;
        gu8_rgb_ice_inner_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_BLUE )
    {
        /*..hui [24-2-22오후 5:02:02] 그린 40%, 블루 80%..*/
        gu8_rgb_ice_inner_red_on_time = 0;
        gu8_rgb_ice_inner_green_on_time = 16;
        gu8_rgb_ice_inner_blue_on_time = 32;
    }
    else
    {
        gu8_rgb_ice_inner_red_on_time = 0;
        gu8_rgb_ice_inner_green_on_time = 0;
        gu8_rgb_ice_inner_blue_on_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_test_mode_ice_outer_rgb_color( U8 mu8_color )
{
    /*..hui [24-1-10오후 1:09:30] 주기 10ms로 변경.. 제호 RO CT 기준..*/
    gu8_rgb_pwm_period = 40;

    if( mu8_color == TEST_MODE_RGB_COLOR_RED )
    {
        /*..hui [24-2-22오후 5:01:06] 레드만 40%..*/
        gu8_rgb_ice_outer_red_on_time = 16;
        gu8_rgb_ice_outer_green_on_time = 0;
        gu8_rgb_ice_outer_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_GREEN )
    {
        gu8_rgb_ice_outer_red_on_time = 0;
        gu8_rgb_ice_outer_green_on_time = 40;
        gu8_rgb_ice_outer_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_BLUE )
    {
        /*..hui [24-2-22오후 5:02:02] 그린 40%, 블루 80%..*/
        gu8_rgb_ice_outer_red_on_time = 0;
        gu8_rgb_ice_outer_green_on_time = 16;
        gu8_rgb_ice_outer_blue_on_time = 32;
    }
    else
    {
        gu8_rgb_ice_outer_red_on_time = 0;
        gu8_rgb_ice_outer_green_on_time = 0;
        gu8_rgb_ice_outer_blue_on_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_door(void)
{

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_select(void)
{

}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

