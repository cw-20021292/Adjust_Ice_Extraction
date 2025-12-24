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
#include    "test_pcb.h"



void Main_PBA_Test_Mode_Start(void);
void Pcb_Test_Main(void);
void pcb_test_job(void);
void thermistor_test(void);
void hot_out_temp(void);
void hot_heater_temp(void);
void hot_in_temp(void);
void cold_temp(void);
void outdoor_1_temp(void);
void outdoor_2_temp(void);

void room_temp(void);
void mixing_temp(void);
void eva1_temp(void);
/////void tds_in_temp(void);
/////void tds_out_temp(void);

void sensor_test(void);
void watertank_low_water(void);
void watertank_high_water(void);
void draintank_low_water(void);
void draintank_high_water(void);
void ice_full(void);
void ice_lack(void);
void water_leak(void);
void boost_in(void);

void switch_test(void);
void output_test(void);
void heater_output(void);
void door_heater_output(void);
void comp_fan_output(void);
void step_motor_teest_output(void);
void ac_motor_output(void);

/**
 * @brief 얼음 분쇄모터 출력 테스트
 *
 */
void ICE_BREAK_DC_MOTOR_OUTPUT(void);

void valve_output_one(void);
void valve_output_two(void);
void uv_output(void);
void pump_output(void);
void flow_sensor(void);
/////void tds_sensor(void);

void fault_ad_test(void);

void uart_test(void);
void bldc_comm_test(void);

void pcb_test_mode_uart_test(void);
void uart_error_display(void);
void PCB_Test_Mode_Key_Short_Input( U32 u32key_input_value);
void PCB_Test_Mode_Extract_Key_Short_Input(void);
void PCB_Test_Mode_Ice_Key_Short_Input(void);
void test_mode_eeprom_initial(void);
void wifi_test(void);
void flow_valve_test_output(void);
void swingbar_output();
void tray_stepmotor_test_output();



void start_tray_pump( U16 u16_data );
void stop_tray_pump( void );

U8 gu8_redo_test_input;
U8 gu8_left_test_input;

U8 gu8_user_test_input;
U8 gu8_hot_test_input;
U8 gu8_hot_test_input_old;
U8 gu8_room_test_input;
U8 gu8_cold_test_input;
U8 gu8_cup_test_input;
U8 gu8_ice_water_test_input;


U8 gu8_user_test_input_led;
U8 gu8_hot_test_input_led;
U8 gu8_room_test_input_led;
U8 gu8_cold_test_input_led;
U8 gu8_cup_test_input_led;





U8 gu8_right_test_input;



U8 gu8_eeprom_initial_test_input;

U8 gu8_eeprom_initial_step;


U8 u8PcbTestEnableFlag;
U8 u8PcbTestEnableTimer;
bit F_PcbTestStart;
U16 u16TestModeEnableTimer;
U8 u8leakcnt;

bit F_step_test1;
bit F_step_test2;


U8 gu8_EAD_Pcb_Test_On_Time;
U8 gu8_EAD_Pcb_Test_Off_Time;

U8 gu8UARTest_Mode;


U8 gu8_fix_direction;
U8 gu8_EAD_Off;

bit F_Pcb_Test_Ice_Click;

U8 u8icefullcnt;
U8 u8leakcnt;
bit F_water_ext_step_motor_out_state;

U8 delay_ice_full;
U8 u8icelackcnt;
U8 delay_ice_lack;

bit F_pcbtest_stepmotor_on_state;

bit bit_step_out_state;


U8 u8_drain_cnt;
U8 u8_hot_p_cnt;

bit F_flow_detect;
bit F_mc_sw1;
bit F_mc_sw2;

U8 gu8_hot_heater_on_timer;
U8 gu8_ice_heater_on_timer;


//U8 u8_rtc_test_proc;
//U8 u8_rtc_test_timer;
//U8 u8_rtc_test_fail;

U8 gu8_valve_timer_one;
U8 gu8_valve_timer_two;
U8 gu8_valve_timer_three;

U8 gu8_flow_test_timer;
U8 gu8_filter_flow_test_timer;


U8 gu8_user_acc1;
U8 gu8_user_acc2;
U8 gu8_user_acc3;
U8 gu8_user_acc4;


U8 gu8_ice_test_input;
U8 gu8_icewater_test_input;
U8 gu8_hot_test_input;
U8 gu8_ambient_test_input;
U8 gu8_cold_test_input;
U8 gu8_amount_test_input;
U8 gu8_cold_off_input;
U8 gu8_my_test_input;       /* MY키 테스트 키 추가 250212 CH.PARK */

U8 gu8_setting_ice_size_test_input;
U8 gu8_setting_ice_off_test_input;
U8 gu8_setting_hot_lock_test_input;
U8 gu8_setting_ice_first_test_input;
U8 gu8_setting_cold_temp_test_input;
U8 gu8_setting_eco_mode_test_input;
U8 gu8_setting_ice_lock_test_input;
U8 gu8_setting_all_lock_test_input;

U8 gu8_heater_test_timer_100ms = CLEAR;
U8 gu8_door_heater_test_timer_100ms = CLEAR;

U8 gu8_water_ext_test_input;
U8 gu8_ice_ext_test_input;


bit bit_setting_test_finish;
bit bit_ice_test_finish;
bit bit_hot_test_finish;
bit bit_ambient_test_finish;
bit bit_cold_tst_finish;
bit bit_amount_test_finish;
bit bit_ice_first_test_finish;
bit bit_ice_lock_test_finish;
bit bit_hot_lock_test_finish;
bit bit_touch_lock_test_finish;
bit bit_steam_off_test_finish;
bit bit_eco_test_finish;

bit bit_water_extract_test_finish;
bit bit_ice_extract_test_finish;

bit bit_bldc_rx_pba_test_ok;

bit bit_comp_test;

bit bit_pcb_test_finish;

U16 gu16_current_tray_pwm;

U8 bldc_test_ok_flag = 0;
U8 bldc_test_ok_cnt = 0;


extern U8 gu8_Amb_Front_Temperature_One_Degree;
extern U8 gu8_Amb_Side_Temperature_One_Degree;
extern U8 gu8_front_rcv_filter_reed_data;

extern tsSTEPMOTOR sStepMotor;
extern U8 Init_Flow(void);
extern U8 Increase_Flow(void);
extern U8 Decrease_flow(void);
extern void run_increase_flow(U16 mu16_move);
extern void run_decrease_flow(U16 mu16_move);
extern void run_init_flow(void);
extern void check_error_micro_sw_movement(void);
extern void inverse_direction_time_check(void);
extern void control_ice_tray(void);
extern void input_ice_tray_micro_sw(void);
extern void run_down_ice_tray(void);
extern void run_up_ice_tray(void);
extern void run_stop_ice_tray(void);
/***************************************************************************************************/
/**
 * @brief MAIN PBA 검사모드 시작 함수
 *
 */
void Main_PBA_Test_Mode_Start(void)
{
    gu8_test_mode_timeout_1s = 0;
    off_all_control_led();
    play_melody_setting_on_198();

    u8FactoryTestMode = PCB_TEST_MODE;
    UARTest_NO_LOAD_Set();
    F_FW_Version_Display_Mode = CLEAR;

    /*..hui [19-12-19쩔?횊횆 1:26:46] 횁짚쩌철 쩔횂쨉쨉쩌쩐쩌짯 ?체쩔첩 ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19쩔?횊횆 1:27:21] 쨀횄쩌철 쩔횂쨉쨉쩌쩐쩌짯 ?체쩔첩 ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;

    /*..hui [20-1-14쩔?횊횆 8:15:16] 12V ?체쩔첩 ON..*/
    Bit2_Uart_Test_Mode_State = SET;

    gu8_flow_test_timer = 0;
    gu8_filter_flow_test_timer = 0;
    bit_bldc_rx_pba_test_ok = CLEAR;

    /*..hui [21-2-18쩔?횊횆 5:08:19] WIFI 째첩?책 째횏쨩챌 횄횩째징..*/
    // WifiKey(WIFI_KEY_TEST);
    SetWifiSystemStatus(WIFI_FACTORY_STATUS, SET);

    gu8_eeprom_initial_test_input = 1;

    bit_manual_test_start = CLEAR;

    //////all_breath_stop();

    bit_pcb_test_finish = CLEAR;

    flow_sensor_start();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Pcb_Test_Main(void)
{
	//all_breath_stop();
	//all_dimming_full_on();
	all_duty_100_percent();

	led_blink_timer();

	if(F_FW_Version_Display_Mode != SET)
	 {
        display_version();
	 }
	 else
	 {
        pcb_test_job();
        fnd_left_pba_test();
        fnd_right_pba_test();
	 }

}

void pcb_test_job(void)
{
    /* MainPBA 테스트모드 ICON ICE 2KG WORD 문서 확인 */
	eeprom_test();              /* 테스트 항목 1번 : EEPROM 테스트 */
	thermistor_test();          /* 테스트 항목 2번 : 온도센서 */
	sensor_test();	            /* 테스트 항목 3번 : 수위센서류 */
	switch_test();              /* 테스트 항목 4번 : REED / SWITCH */
	flow_sensor();              /* 테스트 항목 5번 : 유량센서 - [빠른제빙] LED 점등 (확인) */
	output_test();              /* 테스트 항목 6,7,8,9번 : 출력 */
	wifi_test();                /* 테스트 항목 10번 : WIFI */
	fault_ad_test();            /* 테스트 항목 11번 : 전류 피드백 IAD 확인 */
	uart_test();                /* 테스트 항목 12번 : UART 통신 */
	bldc_comm_test();           /* 테스트 항목 13번 : BLDC UART 통신 */
	test_mode_eeprom_initial(); /* 테스트 항목 14번 : EEPROM 초기화 */

    if(bit_eeprom_err == 0)
    {
        Bit0_Front_Left_Led_Ice_Full_Text = SET;
        Bit1_Front_Left_Led_Ice_Shortae_Text = SET;     /* 2KG 추가 250211 CH.PARK */
    }
    else
    {
        Bit0_Front_Left_Led_Ice_Full_Text = CLEAR;
        Bit1_Front_Left_Led_Ice_Shortae_Text = CLEAR;   /* 2KG 추가 250211 CH.PARK */
    }

    /* PBA 테스트 정상완료 조건 */
    if((gu8_front_temp_fnd_hundred == 0x7F)
    && (gu8_front_temp_fnd_ten == 0x7F)
    && (gu8_front_temp_fnd_one == 0x7F)

    && (gu8_front_amount_fnd_hundred == 0x7F)
    && (gu8_front_amount_fnd_ten == 0x7F)
    && (gu8_front_amount_fnd_one == 0x7F)

    && (gu8_front_left_led == 0xFF)
    && (gu8_front_left_led_2 == 0x3F)
    && (gu8_front_right_led == 0xFF)
    && (gu8_front_temp_setting_bar_led == 0x1F)
    && (gu8_front_amount_setting_bar_led == 0x1F)

    && (gu8_front_center_recipe_led == 0x3F)
    && (gu8_front_select_led == 0x7F)
    && (gu8_front_setting_led == 0x7F)
    && (gu8_front_setting_led_2 == 0x7D)        //
    && (gu8_front_under_text_led == 0xFF)
    && (gu8_front_under_icon_led == 0x7A)

    && (bldc_test_ok_flag == SET)
    && (GetWifiStatusValue(WIFI_STATUS_TEST) == SET)
    )
    {
        /*Bit4_Front_Led_Eco_Mode ^= SET;*/
        //Bit7_Front_Left_Led_Gal_Icon ^= SET;

        bit_pcb_test_finish = SET;
    }
    else
    {
        /*Bit5_Front_Led_Eco_Mode = CLEAR;*/
    }

    /* 모든 테스트가 정상적으로 완료되면 [전체잠금] LED 빠르게 점멸함 */
    if( bit_pcb_test_finish == SET )
    {
        Bit1_Front_Led_All_Lock ^= SET;
    }
    else
    {
        Bit1_Front_Led_All_Lock = CLEAR;
    }

    // input_ice_tray_micro_sw();
    // inverse_direction_time_check();
    // check_error_micro_sw_movement();
    // control_ice_tray();
}

void test_mode_eeprom_initial(void)
{
    /*..hui [19-10-31?ㅼ쟾 11:05:54] 寃????꾨즺?쒗썑??吏꾩엯 媛??ν븯?꾨줉..*/
    if(gu8_eeprom_initial_test_input == 1)
    {
        eeprom_initial();
        gu8_eeprom_initial_test_input = 0;
        /*FactoryResetRtc();*/
        InitRtcTime();
    }
    else{}
}

void thermistor_test(void)
{
	hot_out_temp();     /* 온수 출수 온도센서 - UV살균, 출수파우셋, 얼음파우셋 LED 점등 (확인) */       //
	hot_heater_temp();  /* 히터 온도센서 - 고온살균, 얼음트레이, 얼음저장고 LED 점등 (확인) */          //
	hot_in_temp();      /* 온수 입수 온도센서 - 슬립, 단계, :, 'C LED 점등 (확인) */                   //
	cold_temp();        /* 냉수 온도센서 - 해, 우산, 구름, WIFI(블루) LED 점등 (확인) */
	room_temp();        /* 정수 온도센서 - 필터세척, L, ml, % LED 점등 (확인) */
	outdoor_1_temp();   /* 외기 온도센서 1 - 왼쪽 세팅바 5개 LED 점등 (확인) */
	outdoor_2_temp();   /* 외기 온도센서 2 - 미사용 */
	eva1_temp();        /* EVA(증발기) 온도센서 - 라면, 드립커피, 차 LED 점등 (확인) */                 //
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_out_temp(void)
{
    if(gu16_AD_Result_Hot_Out <= TEMP_SENSOR_SHORT || gu16_AD_Result_Hot_Out >= TEMP_SENSOR_OPEN)
    {
        Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;

        /* 2KG 추가 250211 CH.PARK */
        Bit0_Front_Left_Led_Eff_Faucet_Text = CLEAR;
        Bit1_Front_Left_Led_Ice_Faucet_Text = CLEAR;
    }
    else if(gu16_AD_Result_Hot_Out >= (512 - GAP) && gu16_AD_Result_Hot_Out <= (512 + GAP))         // 정상
    {
        Bit2_Front_Left_Led_UV_Ster_Text = SET;

        /* 2KG 추가 250211 CH.PARK */
        Bit0_Front_Left_Led_Eff_Faucet_Text = SET;
        Bit1_Front_Left_Led_Ice_Faucet_Text = SET;
    }
    else
    {
        Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;

        /* 2KG 추가 250211 CH.PARK */
        Bit0_Front_Left_Led_Eff_Faucet_Text = CLEAR;
        Bit1_Front_Left_Led_Ice_Faucet_Text = CLEAR;
    }
}

void hot_heater_temp(void)
{
    if( gu16_AD_Result_Hot_Heater <= TEMP_SENSOR_SHORT || gu16_AD_Result_Hot_Heater >= TEMP_SENSOR_OPEN)
    {
        Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;

        /* 2KG 추가 250211 CH.PARK */
        Bit2_Front_Left_Led_Ice_Tray_Text = CLEAR;
        Bit3_Front_Left_Led_Ice_Storage_Box_Text = CLEAR;
    }
    else if(gu16_AD_Result_Hot_Heater >= (512 - GAP) && gu16_AD_Result_Hot_Heater <= (512 + GAP))
    {
        Bit3_Front_Left_Led_Hot_Ster_Text = SET;

        /* 2KG 추가 250211 CH.PARK */
        Bit2_Front_Left_Led_Ice_Tray_Text = SET;
        Bit3_Front_Left_Led_Ice_Storage_Box_Text = SET;
    }
    else
    {
        Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;

        /* 2KG 추가 250211 CH.PARK */
        Bit2_Front_Left_Led_Ice_Tray_Text = CLEAR;
        Bit3_Front_Left_Led_Ice_Storage_Box_Text = CLEAR;
    }

}

void hot_in_temp(void)
{
	if( gu16_AD_Result_Hot_In <= TEMP_SENSOR_SHORT || gu16_AD_Result_Hot_In >= TEMP_SENSOR_OPEN)
	{
        //?먮윭
        Bit4_Front_Left_Led_Sleep_Icon = CLEAR;
        Bit5_Front_Left_Led_Step_Text = CLEAR;
        Bit6_Front_Left_Led_Clock_Colon_Icon = CLEAR;
        Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
        Bit4_Front_Led_Icon_Fast_Ice = CLEAR;
	}
	else if(gu16_AD_Result_Hot_In >= (512 - GAP) && gu16_AD_Result_Hot_In <= (512 + GAP))
	{
        //1??
        Bit4_Front_Left_Led_Sleep_Icon = SET;
        Bit5_Front_Left_Led_Step_Text = SET;
        Bit6_Front_Left_Led_Clock_Colon_Icon = SET;
        Bit7_Front_Left_Led_Celcius_oC_Icon = SET;
        Bit4_Front_Led_Icon_Fast_Ice = SET;
	}
	else
	{
        Bit4_Front_Left_Led_Sleep_Icon = CLEAR;
        Bit5_Front_Left_Led_Step_Text = CLEAR;
        Bit6_Front_Left_Led_Clock_Colon_Icon = CLEAR;
        Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
        Bit4_Front_Led_Icon_Fast_Ice = CLEAR;
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_temp(void)
{
    if(gu16_AD_Result_Cold <= TEMP_SENSOR_SHORT || gu16_AD_Result_Cold >= TEMP_SENSOR_OPEN)
    {
        Bit1_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
        Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
        Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
        Bit4_Front_Right_Led_Rain_Icon = CLEAR;
    }
    else if(gu16_AD_Result_Cold >= (512 - GAP) && gu16_AD_Result_Cold <= (512 + GAP))
    {
        //1??
        Bit1_Front_Right_Led_Wifi_Icon_Blue = SET;
        Bit2_Front_Right_Led_Sunny_Icon = SET;
        Bit3_Front_Right_Led_Cloud_Icon = SET;
        Bit4_Front_Right_Led_Rain_Icon = SET;
    }
    else
    {
        Bit1_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
        Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
        Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
        Bit4_Front_Right_Led_Rain_Icon = CLEAR;
    }
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void room_temp(void)
{
    if(gu16_AD_Result_Room <= TEMP_SENSOR_SHORT || gu16_AD_Result_Room >= TEMP_SENSOR_OPEN)
    {
        Bit5_Front_Right_Led_Percent_Icon = CLEAR;
        Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
        Bit7_Front_Right_Led_ml_Icon = CLEAR;
    }
    else if(gu16_AD_Result_Room >= (512 - GAP) && gu16_AD_Result_Room <= (512 + GAP))
    {
        Bit5_Front_Right_Led_Percent_Icon = SET;
        Bit6_Front_Right_Led_Liter_L_Icon = SET;
        Bit7_Front_Right_Led_ml_Icon = SET;
    }
    else
    {
        Bit5_Front_Right_Led_Percent_Icon = CLEAR;
        Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
        Bit7_Front_Right_Led_ml_Icon = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void outdoor_1_temp(void)
{
    if(gu16_AD_Result_Amb <= TEMP_SENSOR_SHORT || gu16_AD_Result_Amb >= TEMP_SENSOR_OPEN)
    {
        //?먮윭
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;    /* 2KG 추가 250211 CH.PARK */
    }
    else if(gu16_AD_Result_Amb >= (512 - GAP) && gu16_AD_Result_Amb <= (512 + GAP))
    {
        //1??
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
        Bit4_Front_Led_Temp_Setting_Bar_1_5 = SET;    /* 2KG 추가 250211 CH.PARK */
    }
    else
    {
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;    /* 2KG 추가 250211 CH.PARK */
    }
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void outdoor_2_temp(void)
{
#if 0
    if(gu16_AD_Result_Amb_Side <= TEMP_SENSOR_SHORT || gu16_AD_Result_Amb_Side >= TEMP_SENSOR_OPEN)
    {
        //?먮윭
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
				Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
				Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
				Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
    }
    else if(gu16_AD_Result_Amb_Side >= (512 - GAP) && gu16_AD_Result_Amb_Side <= (512 + GAP))
    {
        //1??
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
				Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
				Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
				Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
    }
    else
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
				Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
				Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
				Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
    }

		#endif
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void eva1_temp(void)
{
    if( gu16_AD_Result_Eva_First <= TEMP_SENSOR_SHORT || gu16_AD_Result_Eva_First >= TEMP_SENSOR_OPEN )
    {
        Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
        Bit1_Front_Center_Tea_Text = CLEAR;                     /* 2KG 추가 250211 CH.PARK */
        Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
    }
    else if(gu16_AD_Result_Eva_First >= (512 - GAP) && gu16_AD_Result_Eva_First <= (512 + GAP))
    {
        Bit0_Front_Center_Recipe_Ramen_Text = SET;
        Bit1_Front_Center_Tea_Text = SET;                       /* 2KG 추가 250211 CH.PARK */
        Bit2_Front_Center_Recipe_Drip_Coffee_Text = SET;
    }
    else
    {
        Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
        Bit1_Front_Center_Tea_Text = CLEAR;                     /* 2KG 추가 250211 CH.PARK */
        Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
    }
}

void sensor_test(void)
{
	draintank_low_water();      /* [얼음] 버튼 LED 점등 (확인) */
	draintank_high_water();     /* [얼음물] 버튼 LED 점등 (확인) */
	ice_full();                 /* [온수] 버튼 LED 점등 (확인) */
    ice_lack();                 /* [MY] 버튼 LED 점등 (확인) */ /* 얼음탱크 저빙 추가 250226 CH.PARK  */
	water_leak();               /* [정수] 버튼 LED 점등 (확인) */
}

void draintank_low_water(void)
{
    if(pLEVEL_ICE_DRAIN_LOW == CLEAR)
    {
        Bit0_Front_Led_Ice_Select = SET;
    }
    else
    {
        Bit0_Front_Led_Ice_Select = CLEAR;
    }

}
void draintank_high_water(void)
{
    if(pLEVEL_ICE_DRAIN_HIGH == CLEAR)
    {
        Bit1_Front_Led_Ice_Water_Select = SET;
    }
    else
    {
        Bit1_Front_Led_Ice_Water_Select = CLEAR;
    }
}

void ice_full(void)
{
    /*ICE_IR_POW = 1;*/ /*留뚮튃?쇱꽌 諛쒖떊遺?*/
    pIR_POWER = SET;

    delay_ice_full++;
    if(delay_ice_full >= 20) //2초 딜레이
    {
        delay_ice_full = 20;
    }
    else
    {
        return;
    }

    if (gu16ADIceFull <= 230)
    {
        u8icefullcnt++;

        if(u8icefullcnt >= 3)
        {
            u8icefullcnt = 3;
            Bit2_Front_Led_Hot_Select = SET;
        }
        else{}
    }
    else
    {
        if(u8icefullcnt != 3)
        {
            u8icefullcnt = 0;
            Bit2_Front_Led_Hot_Select = CLEAR;
        }
    }
}

void ice_lack(void)
{
    pIR_POWER2 = SET;

    delay_ice_lack++;
    if(delay_ice_lack >= 20) //2AE μo·¹AI
    {
        delay_ice_lack = 20;
    }
    else
    {
        return;
    }

    if (gu16ADIceLow <= 230)
    {
        u8icelackcnt++;

        if(u8icelackcnt >= 3)
        {
            u8icelackcnt = 3;
            Bit6_Front_Led_My_Select = SET;
        }
        else{}
    }
    else
    {
        if(u8icelackcnt != 3)
        {
            u8icelackcnt = 0;
            Bit6_Front_Led_My_Select = CLEAR;
    	}
    }
}
void water_leak(void)
{
    if (gu16ADLeakage > 750)
    {
        u8leakcnt++;

        if(u8leakcnt >= 3)
        {
            Bit3_Front_Led_Ambient_Select = SET;
        }
        else{}
    }
    else
    {
        if(u8leakcnt != 3)
        {
            u8leakcnt = 0;
            Bit3_Front_Led_Ambient_Select = CLEAR;
        }
    }
}

void switch_test(void)
{
	if(pICE_MICRO_SW_LOW == CLEAR)
    {
        Bit5_Front_Led_Amount_Select = SET;
    }
    else
    {
        Bit5_Front_Led_Amount_Select = CLEAR;
    }

    if(pICE_MICRO_SW_HIGH == CLEAR)
    {
        Bit0_Front_Led_Ice_Size = SET;
    }
    else
    {
        Bit0_Front_Led_Ice_Size = CLEAR;
    }

    /* 탱크커버 2 */
    if(pREED_TANK_COVER_2 == CLEAR)
    {
        Bit4_Front_Led_Cold_Select = SET;
        Bit1_Front_Led_Ice_Off = SET;
        Bit6_Front_Led_Cold_Off = SET;  /* 2KG 추가 250211 CH.PARK */
    }
    else
    {
        Bit4_Front_Led_Cold_Select = CLEAR;
        Bit1_Front_Led_Ice_Off = CLEAR;
        Bit6_Front_Led_Cold_Off = CLEAR; /* 2KG 추가 250211 CH.PARK */
    }

    /* 필터 1 */
    if(pREED_FILTER == CLEAR)
    {
        Bit2_Front_Led_Hot_Lock_Text = SET;
        Bit0_Front_Led_Ice_Lock = SET;
    }
    else
    {
        Bit2_Front_Led_Hot_Lock_Text = CLEAR;
        Bit0_Front_Led_Ice_Lock = CLEAR;
    }

    // /* 필터커버 */
    // if(pREED_FILTER_COVER == CLEAR)
    // {
    //     Bit0_Front_Led_Ice_Lock = SET;
    // }
    // else
    // {
    //     Bit0_Front_Led_Ice_Lock = CLEAR;
    // }
}

void flow_sensor(void)
{
    #if 0
    if(gu8_Tray_Flow_1sec > 5)
    {
        F_flow_detect = SET;
    }
    else{}
    #endif

    /*..hui [23-6-28?ㅽ썑 5:28:06] ?몃젅???좊웾?쇱꽌..*/
    if(gu8_Flow_1sec >= 30  && gu8_Flow_1sec <= 70)
    {
        gu8_flow_test_timer++;

        if( gu8_flow_test_timer >= 10 )
        {
            gu8_flow_test_timer = 10;
            Bit3_Front_Led_Ice_First = SET;
        }
        else{}
    }
    else
    {
        gu8_flow_test_timer = 0;
    }
}

void output_test(void)
{
    /* 모터류 테스트 */
    ICE_BREAK_DC_MOTOR_OUTPUT();        /* 얼음 분쇄 AC모터 검사 추가 250212 CH.PARK - [MY] 버튼으로 검사 (확인) */
	step_motor_teest_output();          /* 스테핑모터 검사 - [냉수] 버튼으로 검사 (확인) */
	tray_stepmotor_test_output();       /* 아이스트레이 스테핑모터 검사 - [온수] 버튼으로 검사 (확인) */
	ac_motor_output();                  /* 얼음토출 AC모터 - [용량] 버튼으로 검사 (확인) */
    /* STEP) 온수 유량조절밸브 ? */
    /* STEP) ICE DOOR 1 ? */
    /* STEP) ICE DOOR SELECT ? */

    /* 밸브류 테스트 */
	valve_output_one();                 /* 밸브, UV램프 같이 테스트 - 키 입력으로 on/off (확인) */
	//valve_output_two();

    /* 기타 테스트 */
	heater_output();                    /* 히터 릴레이, 트라이악 2초 제어 [얼음물 버튼] (확인) */
	swingbar_output();                  /* 스윙바 제어 [얼음물 버튼] (확인) */
	comp_fan_output();                  /* 얼음 컴프레셔, DC쿨링팬 제어 [얼음 버튼] (확인)  */
	door_heater_output();               /* 아이스도어 히터 제어 [얼음 추출버튼] (확인) */
    flow_valve_test_output();           /* 유량조절밸브 [정수 버튼] (확인) */
	uv_output();                        /* UV 램프 전류피드백에 따라 LED 제어 (확인) */
	pump_output();                      /* 드레인펌프 동작 및 전류피대븍에 따른 LED 제어 (확인) */
}

void heater_output(void)
{
#if 0
    if( gu8_icewater_test_input == 1 )
    {
        gu8_hot_heater_on_timer++;

        /*..hui [20-2-26?ㅽ썑 8:25:38] ?쒗뭹?쇰줈???뚯뒪?명븷?섏엳?꾨줉 2珥덈줈 ?쒗븳..*/
        if( gu8_hot_heater_on_timer >= 20 )
        {
            gu8_hot_heater_on_timer = 20;
            pHEATER_HOT_H_RELAY = 0;
						pHEATER_HOT_TRIAC_L = 0;
        }
        else
        {
            pHEATER_HOT_H_RELAY = 1;
						pHEATER_HOT_TRIAC_L = 1;
        }
    }
    else
    {
        gu8_hot_heater_on_timer = 0;
        pHEATER_HOT_H_RELAY = 0;
				pHEATER_HOT_TRIAC_L = 0;
    }
		#endif
	if( gu8_icewater_test_input == 1 )
	{
        gu8_heater_test_timer_100ms++;
        if(gu8_heater_test_timer_100ms >= 20)   /* 히터는 2초 간 on 이후 off */
		{
            gu8_heater_test_timer_100ms = 20;
            pHEATER_HOT_H_RELAY = 0;
    		pHEATER_HOT_TRIAC_L = 0;
        }
        else
        {
            pHEATER_HOT_H_RELAY = 1;
    		pHEATER_HOT_TRIAC_L = 1;
        }
	}
	else
	{
        gu8_heater_test_timer_100ms = 0;

		pHEATER_HOT_H_RELAY = 0;
		pHEATER_HOT_TRIAC_L = 0;
	}
}

/************************************************************************************************/
/**
 * @brief 아이스도어 히터 제어 및 전류피드백 검출 추가 250313 CH.PARK
 *
 */
void door_heater_output(void)
{
    if( gu8_ice_ext_test_input == 1 )
	{
        // gu8_door_heater_test_timer_100ms++;
        // if(gu8_door_heater_test_timer_100ms >= 20)   /* 히터는 2초 간 on 이후 off */
		// {
        //     gu8_door_heater_test_timer_100ms = 20;
        //     pHEATER_ICE_DOOR = 0;
        // }
        // else
        // {
    	// 	pHEATER_ICE_DOOR = 1;
        // }

        pHEATER_ICE_DOOR = 1;
	}
	else
	{
        gu8_door_heater_test_timer_100ms = 0;

		pHEATER_ICE_DOOR = 0;
	}

    if(gu8_ice_ext_test_input != 0)
    {
        //諛곗닔?뚰봽 IAD
        if(gu16_AD_Result_IceDoor_Heater_Current >= 100) // (임시)
        {
            Bit4_Front_Right_Led_Filter_Clean_Text = SET;
        }
        else
        {
            Bit4_Front_Right_Led_Filter_Clean_Text = CLEAR;
        }
    }
    else
    {
        Bit4_Front_Right_Led_Filter_Clean_Text = CLEAR;
    }
}

void comp_fan_output(void)
{
    if(gu8_ice_test_input == 1)
    {
        //pCOMP = 1;
        gu8_bldc_target_hz = BLDC_COMP_65Hz;
        comp_on();
        pDC_FAN = 1;
        bit_comp_test = SET;

    }
    else
    {
        //pCOMP = 0;
        comp_off();
        pDC_FAN = 0;
        bit_comp_test = CLEAR;
    }
}

void swingbar_output(void)
{
	if(gu8_icewater_test_input == 1)
	{
		pSWING_BAR = 1;

	}
	else
	{
		pSWING_BAR = 0;
	}
}

U8 gasswitch_init_cnt = 0;
void step_motor_teest_output()
{
    ControlGasSwitch();

    #if 0       /* 냉수버튼으로 냉매전환밸브까지 검사 */
    if(gu8_cold_test_input == 0)
    {
        /* Timer Interrupt Service에 구현되어 있어서 제어 가능함 */
        F_IceOpen = CLEAR;
        F_IceSelect = CLEAR;        /* 아이스 셀렉트 제어 추가 250311 CH.PARK */

        F_water_ext_step_motor_out_state = CLEAR;

        gasswitch_init_cnt = 0;
        F_pcbtest_stepmotor_on_state = CLEAR;
    }
    else
    {
        if(F_water_ext_step_motor_out_state == CLEAR)
        {
            F_water_ext_step_motor_out_state = SET;

            /* Timer Interrupt Service에 구현되어 있어서 제어 가능함 */
            F_IceOpen = SET;
            F_IceSelect = SET;      /* 아이스 셀렉트 제어 추가 250311 CH.PARK */
        }

        if(F_pcbtest_stepmotor_on_state == CLEAR)
        {
            F_pcbtest_stepmotor_on_state = SET;

            F_GasSwitch_Initial = CLEAR;
            GasSwitchInit();
            gasswitch_init_cnt++;;

        }
        else
        {
            if((gu8_GasSwitch_Mode != 0x01)//GAS_SWITCH_MODE_INIT
            && (gasswitch_init_cnt != 0)
            )
            {
                GasSwitchInit();
                gasswitch_init_cnt = 0;
            }
            else {  }
        }
    }
    #endif

    if(gu8_cold_test_input == 0)
    {
        /* Timer Interrupt Service에 구현되어 있어서 제어 가능함 */
        F_IceOpen = CLEAR;
        F_IceSelect = CLEAR;        /* 아이스 셀렉트 제어 추가 250311 CH.PARK */

        F_water_ext_step_motor_out_state = CLEAR;
        // gasswitch_init_cnt = 0;
    }
    else
    {
        if(F_water_ext_step_motor_out_state == CLEAR)
        {
            F_water_ext_step_motor_out_state = SET;

            /* Timer Interrupt Service에 구현되어 있어서 제어 가능함 */
            F_IceOpen = SET;
            F_IceSelect = SET;      /* 아이스 셀렉트 제어 추가 250311 CH.PARK */
        }
    }

    /* 1KG 따라서 추가 250226 CH.PARK */
    if(gu8_my_test_input == 0)
    {
        gasswitch_init_cnt = 0;
        F_pcbtest_stepmotor_on_state = CLEAR;
    }
    else
    {
        if(F_pcbtest_stepmotor_on_state == CLEAR)
        {
            F_pcbtest_stepmotor_on_state = SET;

            F_GasSwitch_Initial = CLEAR;
            GasSwitchInit();
            gasswitch_init_cnt++;
        }
        else
        {
            if((gu8_GasSwitch_Mode != 0x01)//GAS_SWITCH_MODE_INIT
            && (gasswitch_init_cnt != 0)
            )
            {
                GasSwitchInit();
                gasswitch_init_cnt = 0;
            }
            else {  }
        }
    }

}

void tray_stepmotor_test_output()
{
#if 0
	if(sStepMotor.state == STEP_STATE_DEACTIVE)
	{
		pSTEP_MOTOR_ICE_TRAY_1 = 0;
		pSTEP_MOTOR_ICE_TRAY_2 = 0;
		pSTEP_MOTOR_ICE_TRAY_3 = 0;
		pSTEP_MOTOR_ICE_TRAY_4 = 0;
		return;
	}
#endif

    if(gu8_hot_test_input == 1)
    {
        run_up_ice_tray();   // 트레이제어 함수변경
    }
    else if(gu8_hot_test_input == 2)
    {
        run_down_ice_tray();   // 트레이제어 함수변경
    }
    else
    {
        run_stop_ice_tray();   // 트레이제어 함수변경
        // pSTEP_MOTOR_ICE_TRAY_1 = 0;
        // pSTEP_MOTOR_ICE_TRAY_2 = 0;
        // pSTEP_MOTOR_ICE_TRAY_3 = 0;
        // pSTEP_MOTOR_ICE_TRAY_4 = 0;
    }

    control_ice_tray();
}


U8 flow_cnt = 0;
U8 flow_step = 0;
void flow_valve_test_output()
{
	if(gu8_ambient_test_input == 0)
	{
		//flow_sensor_stop();

	}
	else
	{
		calculate_flow_input();

		switch(gu8_ambient_test_input)
		{

			case 1:
            run_increase_flow(1000);
            Increase_Flow();

            break;

			case 2:
            run_decrease_flow(1000);
            Decrease_flow();

            break;

		}
	}
}

void pump_output(void)
{
    if(gu8_water_ext_test_input == 0)
    {
        stop_drain_pump();
        Bit4_Front_Led_Cold_Temp = CLEAR;

        /* 2KG 추가 250211 CH.PARK */
        Bit6_Front_Under_Txt_Led_Ice_Normal = CLEAR;
        Bit7_Front_Under_Txt_Led_Ice_Piece = CLEAR;
   }
    else
    {
        start_drain_pump( PUMP_PWM_MAX );
        Bit4_Front_Led_Cold_Temp = SET;

        /* 2KG 추가 250211 CH.PARK */
        Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
        Bit7_Front_Under_Txt_Led_Ice_Piece = SET;

        //bit_comp_test = SET;
    }

    if(gu8_water_ext_test_input != 0)
    {
        //諛곗닔?뚰봽 IAD
        if(gu16_AD_Drain_Pump_Current >= 5 && gu16_AD_Drain_Pump_Current <= 900) //795
        {
            u8_drain_cnt = 0;
            Bit5_Front_Led_Sleep_Mode_Text = SET;
        }
        else
        {
            u8_drain_cnt++;
            if(u8_drain_cnt >= 10)
            {
                u8_drain_cnt = 10;
                Bit5_Front_Led_Sleep_Mode_Text = CLEAR;
            }
            else{}
        }
    }
    else
    {
        u8_drain_cnt = 0;
        Bit5_Front_Led_Sleep_Mode_Text = CLEAR;
    }

#if 0
    if(gu8_setting_all_lock_test_input == 0)
    {
        stop_tray_pump();



        /*..hui [24-7-30?ㅽ썑 2:11:51] ?쒕젅???섏쐞?쇱꽌 ON..*/
        //pPower_Drain_Level = CLEAR;
    }
    else
    {
        start_tray_pump( PUMP_PWM_MAX );



        /*..hui [24-7-30?ㅽ썑 2:11:44] ?쒕젅???섏쐞?쇱꽌 OFF..*/
        //pPower_Drain_Level = SET;
    }

    if(gu8_setting_all_lock_test_input != 0)
    {
        if(gu16_AD_Tray_Pump_Current >= 5 && gu16_AD_Tray_Pump_Current <= 900) //795
        {
            u8_hot_p_cnt = 0;
            Bit0_Front_Led_Ice_Lock = SET;
        }
        else
        {
            u8_hot_p_cnt++;
            if(u8_hot_p_cnt >= 10)
            {
                u8_hot_p_cnt = 10;
                Bit0_Front_Led_Ice_Lock = CLEAR;
            }
            else{}
        }
    }
    else
    {
        u8_hot_p_cnt = 0;
        Bit0_Front_Led_Ice_Lock = CLEAR;
    }
#endif
}

void ac_motor_output(void)
{
    if(gu8_amount_test_input == 1)
    {
        pMOTOR_ICE_OUT_CW = SET;
        pMOTOR_ICE_OUT_CCW = CLEAR;
    }
    else if(gu8_amount_test_input == 2)
    {
        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = SET;
    }
    else
    {
        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = CLEAR;
    }
}

/***************************************************************************************/
/**
 * @brief 얼음 분쇄모터 출력 테스트
 *
 */
void    ICE_BREAK_DC_MOTOR_OUTPUT(void)
{
    /* MY 버튼 입력 시 분쇄모터 동작/정지 250311 CH.PARK */
    if(gu8_my_test_input == 1)
    {
        P_OUT_ICE_CRUSH = SET;
    }
    else
    {
        P_OUT_ICE_CRUSH = CLEAR;
    }
}

void valve_output_one(void)
{
    if(gu8_setting_ice_size_test_input == 1)
	{
        pVALVE_HOT_IN = 1;
        pUV_LED_ICE_TANK_1_2 = 1;
	}
	else
	{
        pVALVE_HOT_IN = 0;
        pUV_LED_ICE_TANK_1_2 = 0;
	}

    if(gu8_setting_ice_off_test_input == 1)
	{
        pVALVE_ROOM_IN = 1;
        pUV_LED_ICE_FAUCET_1 = 1;
	}
	else
	{
        pVALVE_ROOM_IN = 0;
        pUV_LED_ICE_FAUCET_1 = 0;
	}

    if(gu8_setting_hot_lock_test_input == 1)
    {
        pVALVE_COLD_DRAIN = 1;
        pVALVE_NOS = 1;
        pUV_LED_ICE_TRAY_1_2 = SET;
    }
    else
    {
        pVALVE_COLD_DRAIN = 0;
        pVALVE_NOS = 0;
        pUV_LED_ICE_TRAY_1_2 = 0;
    }

    if(gu8_setting_ice_first_test_input == 0)
    {
        pVALVE_HOT_DRAIN = CLEAR;
        pUV_LED_ICE_FAUCET_2 = 0;
    }
    else
    {
        pVALVE_HOT_DRAIN = SET;
        pUV_LED_ICE_FAUCET_2 = 1;
    }

    if(gu8_setting_cold_temp_test_input == 1)
	{
        pVALVE_COLD_IN = 1;
        //pVALVE_HOT_OUT = 1;
        pUV_LED_ICE_TANK_3 = SET;     /* ICE TANK3 UV LED 제어 추가 250311 CH.PARK */
	}
	else
	{
        pVALVE_COLD_IN = 0;
        //pVALVE_HOT_OUT = 0;
        pUV_LED_ICE_TANK_3 = CLEAR;   /* ICE TANK3 UV LED 제어 추가 250311 CH.PARK */
	}

    /* [냉수OFF] 버튼 선택 */
    if(gu8_cold_off_input == 1)
    {
        pVALVE_ICE_WATER_EXTRACT = SET;      /* 얼음물 추출밸브 일단 추가 */
    }
    else
    {
        pVALVE_ICE_WATER_EXTRACT = CLEAR;    /* 얼음물 추출밸브 일단 추가 */
    }

    if(gu8_setting_eco_mode_test_input == 1)
	{
        pVALVE_HOT_COLD_OVERFLOW = 1;
        pVALVE_ROOM_COLD_EXTRACT = 1;
	}
	else
	{
        pVALVE_HOT_COLD_OVERFLOW = 0;
        pVALVE_ROOM_COLD_EXTRACT = 0;
	}

    if(gu8_setting_ice_lock_test_input == 1)
    {
        pVALVE_ICE_TRAY_IN = 1;
        pUV_LED_WATER_FAUCET = 1;
    }
    else
    {
        pVALVE_ICE_TRAY_IN = 0;
        pUV_LED_WATER_FAUCET = 0;
    }

    if(gu8_setting_all_lock_test_input == 1)
    {
        pVALVE_HOT_OUT = 1;
    }
    else
    {
        pVALVE_HOT_OUT = 0;
    }
}

void uv_output(void)
{
    if(gu8_setting_ice_first_test_input != 0)
    {
        if( gu16_AD_Result_UV_Ice_Faucet_Two_Current >= UV_SOLO__ERROR_CHECK_OVER_AD
        || gu16_AD_Result_UV_Ice_Faucet_Two_Current <= UV_SOLO__ERROR_CHECK_UNDER_AD )
        {
            Bit0_Front_Under_Txt_Led_Ice_Large = CLEAR;
            Bit1_Front_Under_Txt_Led_Ice_Center_bar = CLEAR;
            Bit2_Front_Under_Txt_Led_Ice_Small = CLEAR;
        }
        else
        {
            Bit0_Front_Under_Txt_Led_Ice_Large = SET;
            Bit1_Front_Under_Txt_Led_Ice_Center_bar = SET;
            Bit2_Front_Under_Txt_Led_Ice_Small = SET;
        }

    }
    else
    {
        Bit0_Front_Under_Txt_Led_Ice_Large = CLEAR;
        Bit1_Front_Under_Txt_Led_Ice_Center_bar = CLEAR;
        Bit2_Front_Under_Txt_Led_Ice_Small = CLEAR;
    }

    if(gu8_setting_ice_lock_test_input != 0)
    {
        if( gu16_AD_Result_UV_Water_Faucet_Current_Feed >= UV_SOLO__ERROR_CHECK_OVER_AD
        || gu16_AD_Result_UV_Water_Faucet_Current_Feed <= UV_SOLO__ERROR_CHECK_UNDER_AD )
        {
            Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;
        }
        else
        {
            Bit2_Front_Led_Icon_Led_Ice_Locker = SET;
        }

    }
    else
    {
        Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;
    }

    if(gu8_setting_ice_size_test_input != 0)
    {
        if( gu16_AD_Result_UV_Ice_Tank_1_2_Current >= UV_COUPLE__ERROR_CHECT_OVER_AD
        || gu16_AD_Result_UV_Ice_Tank_1_2_Current <= UV_COUPLE__ERROR_CHECK_UNDER_AD )
        {
            Bit3_Front_Under_Txt_Led_Cold_High = CLEAR;
            Bit4_Front_Under_Txt_Led_Cold_Center_Bar = CLEAR;
            Bit5_Front_Under_Txt_Led_Cold_Low = CLEAR;
        }
        else
        {

            Bit3_Front_Under_Txt_Led_Cold_High = SET;
            Bit4_Front_Under_Txt_Led_Cold_Center_Bar = SET;
            Bit5_Front_Under_Txt_Led_Cold_Low = SET;
        }

    }
    else
    {
        Bit3_Front_Under_Txt_Led_Cold_High = CLEAR;
        Bit4_Front_Under_Txt_Led_Cold_Center_Bar = CLEAR;
        Bit5_Front_Under_Txt_Led_Cold_Low = CLEAR;
    }

    if(gu8_setting_ice_off_test_input != 0)
    {
        if( gu16_AD_Result_UV_Ice_Faucet_One_Current >= UV_SOLO__ERROR_CHECK_OVER_AD
        || gu16_AD_Result_UV_Ice_Faucet_One_Current <= UV_SOLO__ERROR_CHECK_UNDER_AD )
        {
            Bit3_Front_Led_Icon_Led_Hot_Locker = CLEAR;
        }
        else
        {
            Bit3_Front_Led_Icon_Led_Hot_Locker = SET;
        }

    }
    else
    {
        Bit3_Front_Led_Icon_Led_Hot_Locker = CLEAR;
    }


    if(gu8_setting_hot_lock_test_input != 0)
    {
        if( gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed >= UV_COUPLE__ERROR_CHECT_OVER_AD
        || gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed <= UV_COUPLE__ERROR_CHECK_UNDER_AD )
        {

            Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
        }
        else
        {

            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
        }

    }
    else
    {

        Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
    }

    if(gu8_setting_cold_temp_test_input != 0)
    {
        if( gu16_AD_Result_UV_Ice_Tank_3_Current_Feed >= UV_SOLO__ERROR_CHECK_OVER_AD
        || gu16_AD_Result_UV_Ice_Tank_3_Current_Feed <= UV_SOLO__ERROR_CHECK_UNDER_AD )
        {
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;      /* 2KG 추가 250226 CH.PARK */
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        }
        else
        {
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;      /* 2KG 추가 250226 CH.PARK */
            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
        }
    }
    else
    {
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;      /* 2KG 추가 250226 CH.PARK */
        Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
    }

    if( gu8_ice_test_input != 0 )
    {
        if( gu16_AD_Result_Fan_Current >= 10 )
        {
            Bit6_Front_Led_Icon_Comp_White = SET;
            Bit5_Front_Led_Icon_Comp_Blue = SET;
            Bit5_Front_Right_Seg_Dot_Text = SET;    /* 2KG 추가 250211 CH.PARK */

        }
        else
        {
            Bit6_Front_Led_Icon_Comp_White = CLEAR;
            Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
            Bit5_Front_Right_Seg_Dot_Text = CLEAR;  /* 2KG 추가 250211 CH.PARK */
        }
    }
    else
    {
        Bit6_Front_Led_Icon_Comp_White = CLEAR;
        Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
        Bit5_Front_Right_Seg_Dot_Text = CLEAR;      /* 2KG 추가 250211 CH.PARK */
    }

}

void fault_ad_test(void)
{
    if( gu16_AD_Result_DC_Current_12V >= 15 )
    {
        Bit3_Front_Under_Ice_Outer_White_Extract = SET;
        Bit1_Front_Under_Ice_Inner_White_Extract = SET;
        Bit5_Front_Under_Led_Welcome = SET;
    }
    else
    {

    }

    if( gu16_AD_Result_DC_Current_24V >= 15 )
    {
        Bit4_Front_Under_Water_White_Extract = SET;
        Bit6_Front_Under_Led_Welcome_2 = SET;
    }
    else
    {

    }
}

void uart_test(void)
{
    pcb_test_mode_uart_test();
    uart_error_display();

    AT_UART_Communication();
}

void pcb_test_mode_uart_test(void)
{
    if( gu8UARTest_Mode == 0 )
    {
         gu8UARTData[1]= AT_PCB_UART_TEST;

         gu8UART_DataLength = 1;
         AT_F_TxStart = 1;

         gu8UARTest_Mode++;
    }
    else if( gu8UARTest_Mode == 1 )
    {
        //if(AT_F_RxComplete == SET)
        //{

            gu8UARTest_Mode = 0;
        //}
        //else{}
    }
    else{}
}


void uart_error_display(void)
{
    if( AT_gu8TX_ERROR >= 2)
    {
        /* 2025-10-02 CH.PARK MY쪽 점멸 타이밍 맞추기 어려워서
        모든 MY LED는 1KG와 동일하게 0.5s로 느리게 대신 같은 타이밍에 점멸되도록 수정 */
        Bit3_Front_Center_MY_1_Text = F_Wink_500ms;
    }
    else
    {
        Bit3_Front_Center_MY_1_Text = AT_F_RxComplete;
    }
}




void bldc_comm_test(void)
{
    /*Bldc_Comp_Communication();*/

    if( bit_comp_test == SET )
    {
        gu8_bldc_target_hz = BLDC_COMP_65Hz;
    }
    else
    {
        gu8_bldc_target_hz = 0;
        bit_bldc_rx_pba_test_ok = CLEAR;
    }

    //////Bldc_Comp_Communication();

    if( gu8_bldc_target_hz == 0 )
    {
        comp_off();
    }
    else
    {
        comp_on();
    }

    if( pCOMP == SET )
    {
        Bldc_Comp_Communication();
    }
    else
    {
        clear_bldc_buffer();
    }

    if( bit_bldc_rx_pba_test_ok == SET )
    {
        // Bit4_Front_Center_MY_2_Text ^= SET;
        // Bit5_Front_Center_MY_3_Text ^= SET;     /* 2KG 추가 250211 CH.PARK */

        /* 2025-10-02 CH.PARK 메인 PCB 검사쪽 개선 */
        Bit4_Front_Center_MY_2_Text = F_Wink_500ms;
        Bit5_Front_Center_MY_3_Text = F_Wink_500ms;

        bldc_test_ok_cnt ++;
        if(bldc_test_ok_cnt > 30)
        {
            bldc_test_ok_cnt = 30;
            bldc_test_ok_flag = SET;
        }
    }
    else
    {
        Bit4_Front_Center_MY_2_Text = CLEAR;
        Bit5_Front_Center_MY_3_Text = CLEAR;     /* 2KG 추가 250211 CH.PARK */
        bldc_test_ok_cnt = 0;
        bldc_test_ok_flag = CLEAR;
    }
}

void wifi_test(void)
{
    if(GetWifiStatusValue(WIFI_STATUS_TEST) == SET)
    {
        Bit0_Front_Right_Led_Wifi_Icon_White = SET;
    }
    else
    {
        Bit0_Front_Right_Led_Wifi_Icon_White ^= SET;
    }
}


void PCB_Test_Mode_Key_Short_Input( U32 u32key_input_value)
{
    U8 mu8_return = 0;

    switch(u32key_input_value)
    {
        case KEY_ICE_SELECT:
            gu8_ice_test_input++;

            if(gu8_ice_test_input > 1)
            {
                gu8_ice_test_input = 0;
            }
            else{}
            play_melody_select_196();
        break;

        case KEY_ICE_WATER_SELECT:
            //
            gu8_icewater_test_input++;

            if(gu8_icewater_test_input > 1)
            {
                gu8_icewater_test_input = 0;
            }
            else{}
            play_melody_select_196();
        break;

        case KEY_HOT_SELECT:
            gu8_hot_test_input++;

            if(gu8_hot_test_input >= 3)
            {
                gu8_hot_test_input = 0;
            }
            else{}
            play_melody_select_196();
        break;

        case KEY_AMBIENT_SELECT:
            gu8_ambient_test_input++;

            if(gu8_ambient_test_input >= 3)
            {
                gu8_ambient_test_input = 0;
            }
            else{}
            play_melody_select_196();
        break;

        case KEY_COLD_SELECT:
            gu8_cold_test_input++;

            if(u8FactoryTestMode == PCB_TEST_MODE)
            {
                if(gu8_cold_test_input >= 2)
                {
                    gu8_cold_test_input = 0;
                }
                else{}
            }
            else
            {
                if(gu8_cold_test_input >= 2)
                {
                    gu8_cold_test_input = 0;
                }
                else{}
            }
            play_melody_select_196();
        break;

        case KEY_AMOUNT_SELECT:
            gu8_amount_test_input++;

            if(u8FactoryTestMode == PCB_TEST_MODE)
            {
                if(gu8_amount_test_input >= 3)
                {
                    gu8_amount_test_input = 0;
                }
                else{}
            }
            else
            {
                if(gu8_amount_test_input >= 2)
                {
                    gu8_amount_test_input = 0;
                }
                else{}
            }
            play_melody_select_196();
        break;


        case KEY_SETTING_ICE_FIRST:
            gu8_setting_ice_first_test_input++;

            if(gu8_setting_ice_first_test_input >= 2)
            {
                gu8_setting_ice_first_test_input = 0;
            }
            else{}
            play_melody_select_196();
        break;


        case KEY_SETTING_ICE_LOCK:
            gu8_setting_ice_lock_test_input++;

            if(gu8_setting_ice_lock_test_input >= 2)
            {
                gu8_setting_ice_lock_test_input = 0;
            }
            else{}
            play_melody_select_196();
        break;

        case KEY_SETTING_HOT_LOCK:
            //
            gu8_setting_hot_lock_test_input++;

            if(gu8_setting_hot_lock_test_input >= 2)
            {
                gu8_setting_hot_lock_test_input = 0;
            }
            else{}
            play_melody_select_196();
        break;

        case KEY_SETTING_ICE_SIZE:
            //
            gu8_setting_ice_size_test_input++;

            if(gu8_setting_ice_size_test_input >= 2)
            {
                gu8_setting_ice_size_test_input = 0;
            }
            else{}
						play_melody_select_196();

        break;

        case KEY_SETTING_ICE_OFF:
            gu8_setting_ice_off_test_input++;

            if(gu8_setting_ice_off_test_input >= 2)
            {
                gu8_setting_ice_off_test_input = 0;
            }
            else{}
            play_melody_select_196();

        break;

        case KEY_SETTING_COLD_TEMP:
            //
            gu8_setting_cold_temp_test_input++;

            if(gu8_setting_cold_temp_test_input >= 2)
            {
                gu8_setting_cold_temp_test_input = 0;
            }
            else{}
            play_melody_select_196();

        break;

        case KEY_SETTING_ALL_LOCK:
            gu8_setting_all_lock_test_input++;

            if(gu8_setting_all_lock_test_input >= 2)
            {
                gu8_setting_all_lock_test_input = 0;
            }
            else{}
            play_melody_select_196();

        break;

        case KEY_SETTING_SLEEP_MODE:
            gu8_setting_eco_mode_test_input++;

            if(gu8_setting_eco_mode_test_input >= 2)
            {
                gu8_setting_eco_mode_test_input = 0;
            }
            else{}
            play_melody_select_196();
        break;

        case KEY_MY_SELECT:
        gu8_my_test_input++;

        if(gu8_my_test_input > 1)
        {
            gu8_my_test_input = 0;
        }
        else { /* DO NOTHING */ }
        play_melody_select_196();
        break;

        case KEY_COLD_WATER_OFF:
        gu8_cold_off_input++;

        if(gu8_cold_off_input > 1)
        {
            gu8_cold_off_input = 0;
        }
        else { /* DO NOTHING */ }
        play_melody_select_196();
        break;

        default:
            NOP();
        break;
    }

}

void PCB_Test_Mode_Extract_Key_Short_Input(void)
{
	gu8_water_ext_test_input++;

  if(gu8_water_ext_test_input>= 2)
  {
      gu8_water_ext_test_input = 0;
  }
  else{}
	play_melody_select_196();
}


void PCB_Test_Mode_Ice_Extract_Key_Short_Input(void)
{
	gu8_ice_ext_test_input++;

    if(gu8_ice_ext_test_input >= 2)
    {
        gu8_ice_ext_test_input = 0;
    }
    else{}
    play_melody_select_196();
}
