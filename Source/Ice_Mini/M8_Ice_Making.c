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
#include    "M8_Ice_making.h"
#include    "Temp_Table.h"
#include    "Ice_Make_Time_Table.h"


void Ice_Make_Process(void);
void normal_mode_ice_init_operation(void);
U16 calc_ice_make_time(U8 mu8AmbTemp, U8 mu8RoomTemp);
//U16 calc_ice_heater_time(void);
U8 Ice_Tray_Sensing(void);
void ice_make_operation(void);
void ice_init_select_bar_test(void);
U8 hot_gas_operation(void);
void recovery_ice_tray(void);
void reduce_hot_gas_noise(void);

U8 get_ice_mode_comp_rps(void);
U8 get_hotgas_mode_comp_rps(void);
U8 get_preheat_mode_comp_rps(void);
U16 get_hotgas_time(void);
U16 get_preheat_time(void);
void get_average_tray_temp(void);


bit F_IceHeater;
bit F_Hotgas_Time;
U8 gu8InitStep;


ICE_STEP gu8IceStep;

bit F_IceVV;

//----------------------------------------------------// ICE Heater
U16 gu16IceHeaterTime;                                // 탈빙 Heater 동작 시간
bit F_ColdWaterInit;
bit F_WaterInit;                      // 최초 정수완료
/*bit F_HotWaterInit;*/                   // 최초 정수완료 - 온수
bit F_WaterInitSet;
bit F_ColdVV;

bit F_TrayMotorUP;
bit F_TrayMotorPreUP;
bit F_TrayMotorDOWN;
bit F_TrayMotorPreDOWN;

//bit F_ColdIn;
//bit F_ColdDIR;               // 냉수쪽 얼음주입
bit F_IceOpen;
bit F_IceTray;
U8 gu8IceOut;
bit F_IceOutCCW;
U8 gu8IceOutCCWInterval;
U16 gu16IceOutTest;
//U16 gu16StepMotor1;
U8 gu8IceClose;
U8 gu8IceInnerClose;
U8 gu8SBTest;                // SB Error 관련
bit F_NoColdBar;
bit F_NoIceBar;
//U16 gu16CompOffDelay;
U16 gu16IceMakeTime;
U8 gu8_IceHeaterControl;
U16 gu16IceVVTimeSetDelay;
U16 gu16ErrPuriDelay;



U16 gu16IceVVTime;
//U8 gu8IceCount;
U8 gu8ICETrayRoomDelay;
//U8 Tray_Comp_Delay;

/*..hui [18-3-8오전 11:23:33] 제빙 중 50초 누적 추출 시 냉수 탈빙 동작..*/
bit F_Ext_cold;

U8 gu8AmbTemp;
U8 gu8RoomTemp;

bit F_CompOn;                     // 냉수 콤프 동작
bit F_IceCompOn;                  // 얼음 콤프 동작
bit F_CompHeater;                 // 콤프,히터 동시기동방지


U8 gu8_ice_make_1sec_timer;
bit F_ice_make_one_more_time;

U8 gu8_ice_tray_reovery_time;

U16 gu16_Ice_Tray_Fill_Hz;
U16 gu16_cody_ice_make_time;


U16 gu16_preheat_time;


U16 gu16_averge_count;
U32 gu32_averge_temp_sum;
U8 gu8_averge_temp_min;
U8 gu8_average_temp_max;

U8 gu8_average_tray_temp;
U8 gu8_average_timer;

U8 gu8_ice_mix_timer;

U8 gu8_ice_take_off_tray_delay = CLEAR;
U8 gu8_ice_take_off_count = CLEAR;
U8 gu8_ice_take_off_stop_time = CLEAR;
U8 gu8_ice_take_off_op_time = CLEAR;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Ice_Make_Process(void)
{
    /*..hui [17-12-26오전 9:51:20] 버전 표시 완료 후 시작..*/
    if(F_FW_Version_Display_Mode != SET)
    {
        return;
    }
    else{}

    /*..hui [17-12-19오후 7:07:33] 누수일때 제빙 및 컴프 정지 추가....*/
    /*..hui [17-12-19오후 7:07:54] 나중에 냉수 입수밸브 OFF시키는것도 추가해야함....*/
    /* 유로살균 진행 시 제빙 중지 및 제빙 불가 250721 CH.PARK */
    if( Bit2_Ice_Operation_Disable_State == SET
    || F_Safety_Routine == SET
    || F_ErrTrayMotor_DualInital == SET
    || cody_water_line.gu8_start == SET)
    {
        F_IceHeater = CLEAR;
        gu8InitStep = 0;
        gu8IceStep = STATE_0_STANDBY;
        return;
    }
    else{}

    //=======================================================//제빙유닛 초기화
    if(F_IceInit == SET)
    {
        ice_init_operation();
        return;
    }
    else
    {
        gu8InitStep = 0;
    }

    //======================================================// 제빙종료시
    if(Bit1_Ice_Make_Go != SET)
    {
        gu8IceStep = STATE_0_STANDBY;
        F_IceHeater = 0;
        return;
    }
    else{}

    //=======================================================// 제빙 시퀸스
    ice_make_operation();

    /*..hui [23-9-19오후 3:37:57] 트레이 입수온도 평균값 확인..*/
    /*get_average_tray_temp();*/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_make_operation(void)
{
    U8 mu8_return_value = 0;
    U8 mu8_comp_rps = 0;

    //=======================================================// 제빙 시퀸스
    switch(gu8IceStep)
    {
        //----------------------------------------------// 얼음받이 제빙회전
        case STATE_0_STANDBY :
            if( (gu16CompOffDelay == 0)
            || (F_Comp_Output == SET)
            )
            {
                /*..hui [19-10-23오후 12:47:20] 얼음 추출중에는 트레이 올리지 않도록..*/
                /*..hui [19-10-23오후 12:47:34] 추출중에 얼음이 밀려서 트레이가 걸린다..*/
                /*..hui [19-10-23오후 12:47:46] 기구적으로 수정이 필욯마..*/
                if( F_IceOut == CLEAR && bit_tray_in_error_temporary == CLEAR )
                {
                    /*if( bit_start_preheat == SET )*/

                    /* 외기 온도 25도 미만인 상태에서 압축기 휴지 시간이 30분 초과한 경우 */
                    if( bit_start_preheat == SET && gu8_Amb_Temperature_One_Degree < PREHEAT_AMB_TEMP )
                    {
                        gu8IceStep = STATE_5_PREHEAT_HOTGAS_MOVE;
                    }
                    else
                    {
                        gu8IceStep = STATE_10_ICE_TRAY_MOVE_UP;
                    }
                }
                else{}
            }
            else{}

            break;

        case STATE_5_PREHEAT_HOTGAS_MOVE :

            /*..hui [23-4-7오후 5:10:11] 냉매전환밸브 핫가스 이동..*/
            GasSwitchHotGas();
            gu8IceStep = STATE_6_CALC_PREHEAT_TIME;

            break;

        case STATE_6_CALC_PREHEAT_TIME :

            if( gu8_GasSwitch_Status == GAS_SWITCH_HOTGAS )
            {
                /*..hui [23-4-7오후 5:10:03] 냉매전환밸브 핫가스 이동 완료 후, COMP 가동, 60HZ..*/
                mu8_comp_rps = get_preheat_mode_comp_rps();
                set_comp_rps( mu8_comp_rps );

                gu16_preheat_time = get_preheat_time();

                gu8IceStep = STATE_7_PREHEAT_OPERATION;
            }
            else
            {
                GasSwitchHotGas();
            }

            break;

        case STATE_7_PREHEAT_OPERATION :

            if(gu16_preheat_time > 0 && pCOMP == SET)
            {
                gu16_preheat_time--;
            }
            else{}

            if(gu16_preheat_time == 0)
            {
                GasSwitchIce();
                gu8IceStep = STATE_10_ICE_TRAY_MOVE_UP;
            }
            else{}

            break;

        //----------------------------------------------// 얼음받이 제빙회전
        case STATE_10_ICE_TRAY_MOVE_UP :
            if(F_TrayMotorDOWN != SET)
            {
                up_tray_motor();    // 제빙시작 시 상승
                gu8IceStep = STATE_11_WAIT_ROOM_WATER_FULL;

                F_CristalIce = SET;
            }
            else{}

            break;

        //----------------------------------------------// 제빙회전후 물받이VV ON
        case STATE_11_WAIT_ROOM_WATER_FULL :

            //if( /*F_TrayMotorUP != SET && */gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING )
            //if( (sStepMotor.state == STEP_STATE_DEACTIVE) && ( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING ) )
            /*if ( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING )*/
            if( F_TrayMotorUP != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING )
            {
                F_TrayMotorUP = CLEAR;

                gu8_E62_dummy_iceheat_flag = CLEAR;
                tray_error_flag_E62 = CLEAR;
                tray_abnormal_E62_timer = 0;
                tray_abnormal_E62_step = 0;
                abnormal_2_repeat_cnt = 0;

                /*..hui [23-4-7오후 5:52:57] 연속 제빙 조건일경우..*/
                /*..hui [23-8-14오후 1:56:47] 수위 확인은 트레이 입수쪽에서.. ..*/
                /*..hui [23-8-14오후 1:57:10] 여기까지 오는 사이에 물 다 빼버리면 COMP 켜진상태로 이쪽에서 대기하게됨..*/
                if( F_Comp_Output == SET )
                {
                    gu8IceStep = STATE_12_CONT_ICE_SWITCH_MOVE;
                }
                else
                {
                    gu8IceStep = STATE_14_CHECK_ICE_TRAY_HZ;
                }
            }
            else
            {
                /*..hui [18-3-20오후 7:21:54] 정수탱크 만수위 채우는중에 트레이 쳐지면 제빙 정지됨..*/
                if(F_TrayMotorUP != SET)
                {
                    gu8IceStep = STATE_10_ICE_TRAY_MOVE_UP;
                }
                else{}

            }

            break;

        case STATE_12_CONT_ICE_SWITCH_MOVE :

            GasSwitchIce();
            gu8IceStep = STATE_13_CONT_RPS_SETTING;

            break;

        case STATE_13_CONT_RPS_SETTING :

            /*..hui [19-7-24오후 4:35:37] 냉매전환밸브 이동 완료 후..*/
            if(gu8_GasSwitch_Status == GAS_SWITCH_ICE)
            {
                mu8_comp_rps = get_ice_mode_comp_rps();
                set_comp_rps( mu8_comp_rps );

                gu8IceStep = STATE_14_CHECK_ICE_TRAY_HZ;
            }
            else
            {
                GasSwitchIce();
            }

            break;

        //----------------------------------------------// 제빙회전후 물받이VV ON
        case STATE_14_CHECK_ICE_TRAY_HZ :

            /*..hui [19-7-23오후 2:08:21] 트레이입수 수배관 변경에 따른 사양 변경(유량센서 후단)..*/
            /*..hui [19-7-23오후 2:08:26] 온수 사용중에는 트레이 입수 금지..*/
            /*if(u8WaterOutState == HOT_WATER_SELECT && F_WaterOut == SET)*/
            /*..hui [19-8-28오전 9:54:48] 온수 뿐만아니라 물 추출중에도 트레이 입수 대기..*/
            #if 1
            if(F_WaterOut == SET)
            {
                /* 트레이 입수 하려는데 냉온정 상관없이 추출하면 대기해야 됨 */
            }
            else
            {
                gu16_Ice_Tray_Fill_Hz = C_ICE_TRAY_FILL_200CC;
                gu8IceStep = STATE_20_WATER_IN_ICE_TRAY;
            }
            #endif

            break;

        //-----------------------------------------------// 물받이VV Off
        case STATE_20_WATER_IN_ICE_TRAY :

            if( gu16_Ice_Tray_Fill_Hz <= 0 )
            {
                gu8IceStep = STATE_21_ICE_SWITCH_MOVE;

                gu16_wifi_tray_in_flow = 260;
                /*..hui [24-11-13오후 2:57:55] TDS 삭제..*/
                /*gu16_tds_water_acc = gu16_tds_water_acc + 200;*/
            }
            else
            {
                gu16_wifi_tray_in_time++;
                /* 트레이 입수중인데 트레이 입수에 문제가 생기면
                즉시 트레이 내리고 탈빙 후 나중에 다시 시도 250423 CH.PARK */
                if( bit_tray_in_error_temporary == SET )
                {
                    down_tray_motor();      // 트레이 입수중 에러
                    if( F_Comp_Output == SET )
                    {
                        gu8IceStep = STATE_40_ICE_TRAY_MOVE_DOWN;
                    }
                    else
                    {
                        gu8IceStep = STATE_51_FINISH_ICE_MAKE;
                    }
                }
                else {  }
            }

            break;

        //-----------------------------------------------// 물받이VV Off
        case STATE_21_ICE_SWITCH_MOVE :

            GasSwitchIce();

            gu8IceStep = STATE_30_CALC_ICE_MAKING_TIME;

            break;

        //-----------------------------------------------// 제빙 시작
        case STATE_30_CALC_ICE_MAKING_TIME :

            /*..hui [19-7-24오후 4:35:37] 냉매전환밸브 이동 완료 후..*/
            if(gu8_GasSwitch_Status == GAS_SWITCH_ICE)
            {
                if(gu16CompOffDelay == 0 ||  F_Comp_Output == SET)
                {
                    /* 얼음사이즈 [대/소]는 냉동에서 테이블 주면 그에 맞게 설정하면 됨 250224 CH.PARK */
                    gu16IceMakeTime
                        = (U16)calc_ice_make_time( gu8_Amb_Front_Temperature_One_Degree, gu8_Room_Temperature_One_Degree);

                    /*gu16IceMakeTime
                        = (U16)calc_ice_make_time( gu8_Amb_Temperature_One_Degree, gu8_average_tray_temp);*/

                    /*..hui [19-7-5오후 2:08:13] 100ms 카운트 조건 변경..*/
                    gu16IceMakeTime = (U16)(gu16IceMakeTime  * 10);

                    /*..hui [25-3-27오후 1:34:22] 얼음 대소 기능 추가..*/
                    if( bit_ice_size == ICE_SIZE_SMALL )
                    {
                        gu16IceMakeTime = (U16)((F32)gu16IceMakeTime * 0.9f);   // 냉동요청 80% -> 90%
                    }
                    else{}

                    gu16_cody_ice_make_time  = gu16IceMakeTime;

                    /*..hui [24-2-14오후 4:28:53] UV 남은시간 계산용..*/
                    gu16_uv_ice_make_time = gu16IceMakeTime;

                    mu8_comp_rps = get_ice_mode_comp_rps();
                    set_comp_rps( mu8_comp_rps );

                    gu8IceStep = STATE_31_MAIN_ICE_MAKING;
                    gu8_ice_tray_reovery_time = 0;
                }
                else{}
            }
            else
            {
                GasSwitchIce();
            }

            break;
        //-----------------------------------------------// 제빙완료후 모터회전
        case STATE_31_MAIN_ICE_MAKING :

            if(gu16IceMakeTime > 0 && pCOMP == SET)
            {
                gu16IceMakeTime--;    // 제빙 13분

                gu32_wifi_ice_make_time++;
            }
            else{}

            if(gu16IceMakeTime == 0)
            {
                /*gu16IceHeaterTime = calc_ice_heater_time();*/
                down_tray_motor();      // 제빙완료 → 탈빙

                gu8IceStep = STATE_40_ICE_TRAY_MOVE_DOWN;
                gu8_ice_take_off_tray_delay = CLEAR;
                gu8_ice_take_off_count = CLEAR;
                F_CristalIce = CLEAR;
            }
            else
            {
                /* 제빙중인데 트레이가 아래로 쳐질 때 복원 */
                recovery_ice_tray();

                if( gu16IceMakeTime <= HOT_GAS_NOISE_REDUCE_TIME )
                {
                    reduce_hot_gas_noise();
                }
                else{}
            }

            break;

        //-----------------------------------------------// 모터회전완료
        case STATE_40_ICE_TRAY_MOVE_DOWN :
			if(F_TrayMotorDOWN != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW)
            {
				F_TrayMotorDOWN = 0;
                gu8IceStep = STATE_41_GAS_SWITCH_HOT_GAS;
            }
            else {}
            break;

        case STATE_41_GAS_SWITCH_HOT_GAS :

            mu8_comp_rps = get_hotgas_mode_comp_rps();
            set_comp_rps( mu8_comp_rps );

            GasSwitchHotGas();

            gu8IceStep = STATE_42_CALC_HOT_GAS_TIME;
            break;

        case STATE_42_CALC_HOT_GAS_TIME :

            if(gu8_GasSwitch_Status == GAS_SWITCH_HOTGAS)
            {
                gu16IceHeaterTime = get_hotgas_time();
                gu8IceStep = STATE_43_ICE_TAKE_OFF;
            }
            else
            {
                GasSwitchHotGas();
            }

            break;


            case STATE_43_ICE_TAKE_OFF :
            gu32_wifi_ice_heater_timer++;

            mu8_return_value = hot_gas_operation();

            if(mu8_return_value == SET)
            {
                F_IR = SET;              // 만빙센서 동작
                F_Low_IR = SET;
                F_IceHeater = CLEAR;
                gu8_ice_mix_timer = 0;
                gu8IceStep = STATE_44_FEEDER_OPERATION;
                bit_ice_mix_back_state = SET;       // 제빙완료 후 2초 정역
            }
            else{}

            break;

            case STATE_44_FEEDER_OPERATION:

            gu8_ice_mix_timer++;
            if( gu8_ice_mix_timer >= ICE_FEDDER_MIX_MAX_TIME )
            {
                gu8_ice_mix_timer = 0;
                F_IR = SET;              // ¸¸ºu¼¾¼­ μ¿AU
                F_Low_IR = SET;
                gu8IceStep = STATE_50_ICE_FULL_IR_CHECK;
            }
            else{}

            break;
        //-------------------------------------------------// SB 냉수 회전완료
        case STATE_50_ICE_FULL_IR_CHECK :

            if(F_IR != SET)
            {
                gu8IceStep = STATE_51_FINISH_ICE_MAKE;
            }
            else{}

            break;

        case STATE_51_FINISH_ICE_MAKE :
            // gu8IceStep = STATE_52_TRAY_UP_POSITION;
            gu8IceStep = STATE_0_STANDBY;
            /*..hui [23-7-21오후 4:52:04] 추가..*/
            F_CristalIce = CLEAR;
            break;

        default :

            gu8IceStep = STATE_0_STANDBY;
            gu8InitStep = 0;
            F_IceHeater = CLEAR;
            F_IceInit = SET;

            break;
      }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 calc_ice_make_time(U8 mu8AmbTemp, U8 mu8RoomTemp)
{
    U8 mu8_amb_temp = 0;
    U8 mu8_room_temp = 0;

    if(mu8AmbTemp >= 45)
    {
        mu8_amb_temp = 45;
    }
    else
    {
        mu8_amb_temp = mu8AmbTemp;
    }

    if(mu8RoomTemp >= 45)
    {
        mu8_room_temp = 45;
    }
    else
    {
        mu8_room_temp = mu8RoomTemp;
    }

    return Temp_MakeTime[ mu8_room_temp ][ mu8_amb_temp ];
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 hot_gas_operation(void)
{
    U8 mu8_return_value = 0;

    if(gu16IceHeaterTime > 0)
    {
        gu16IceHeaterTime--;

        gu32_wifi_hot_gas_time++;
    }
    else{}

    if(gu16IceHeaterTime == 0)
    {
        F_IceHeater = CLEAR;
        mu8_return_value = SET;
    }
    else{}

    return mu8_return_value;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void recovery_ice_tray(void)
{
    /*..hui [18-3-22오전 9:39:58] 기구적인 문제로 제빙중 아에스트레이가 쳐지는 현상 발생할수있음..*/
    /*..hui [18-3-22오전 9:40:16] 아이스트레이가 쳐지면 10초에 한번씩 다시 올려준다..*/
    if(gu8IceTrayLEV != ICE_TRAY_POSITION_ICE_MAKING)
    {
        /*..hui [18-3-22오전 10:00:09] 트레이 재시도기능 중에는 동작안함..*/
        if(F_Safety_Routine != SET)
        {
            gu8_ice_tray_reovery_time++;
        }
        else
        {
            gu8_ice_tray_reovery_time = 0;
        }

        if(gu8_ice_tray_reovery_time >= 200)
        {
            gu8_ice_tray_reovery_time = 0;
            up_tray_motor();    // 제빙중 트레이 처짐 시 상승
        }
        else{}
    }
    else
    {
        gu8_ice_tray_reovery_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void reduce_hot_gas_noise(void)
{
    U8 mu8_comp_rps = 0;

    mu8_comp_rps = get_hotgas_mode_comp_rps();
    set_comp_rps( mu8_comp_rps );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 get_ice_mode_comp_rps(void)
{
    U8 mu8_return = 0;

	/*.. sean [25-02-04] gu8_Amb_Temperature_One_Degree으로 처리되어 front로 변경..*/
    if( gu8_Amb_Front_Temperature_One_Degree <= 10 )
    {
        /*..hui [23-4-7오전 11:15:58] 10도 이하..*/
        mu8_return = BLDC_COMP_65Hz;
    }
    else if( gu8_Amb_Front_Temperature_One_Degree <= 20 )
    {
        /*..hui [23-4-7오전 11:16:02] 20도 이하..*/
        mu8_return = BLDC_COMP_66Hz;
    }
    else if( gu8_Amb_Front_Temperature_One_Degree <= 25 )
    {
        /*..hui [23-4-7오전 11:16:06] 25도 이하..*/
        mu8_return = BLDC_COMP_66Hz;
    }
    else if( gu8_Amb_Front_Temperature_One_Degree <= 30 )
    {
        /*..hui [23-4-7오전 11:16:10] 30도 이하..*/
        mu8_return = BLDC_COMP_66Hz;
    }
    else
    {
        /*..hui [23-4-7오전 11:16:14] 30도 초과..*/
        mu8_return = BLDC_COMP_65Hz;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 get_hotgas_mode_comp_rps(void)
{
    U8 mu8_return = 0;

    if( gu8_Amb_Temperature_One_Degree < HOT_GAS_AMB_TEMP_9_DIGREE )
    {
        /*..hui [23-4-7오후 1:17:04] 9도 미만..*/
        mu8_return = BLDC_COMP_50Hz;
    }
    else if( gu8_Amb_Temperature_One_Degree <= HOT_GAS_AMB_TEMP_13_DIGREE )
    {
        /*..hui [23-4-7오후 1:23:42] 9도 ~ 13도..*/
        mu8_return = BLDC_COMP_50Hz;
    }
    else if( gu8_Amb_Temperature_One_Degree <= HOT_GAS_AMB_TEMP_19_DIGREE )
    {
        /*..hui [23-4-7오후 1:23:55] 14도 ~ 19도..*/
        mu8_return = BLDC_COMP_50Hz;
    }
    else if( gu8_Amb_Temperature_One_Degree <= HOT_GAS_AMB_TEMP_24_DIGREE )
    {
        /*..hui [23-4-7오후 1:24:08] 20도 ~ 24도..*/
        mu8_return = BLDC_COMP_47Hz;
    }
    else if( gu8_Amb_Temperature_One_Degree <= HOT_GAS_AMB_TEMP_29_DIGREE )
    {
        /*..hui [23-4-7오후 1:24:18] 25도 ~ 29도..*/
        mu8_return = BLDC_COMP_47Hz;
    }
    else
    {
        /*..hui [23-4-7오후 1:24:23] 30도 이상..*/
        /*mu8_return = BLDC_COMP_43Hz;*/
        /*..hui [23-5-24오전 10:59:56] 청래 변경..*/
        /*mu8_return = BLDC_COMP_51Hz;*/
        mu8_return = BLDC_COMP_43Hz;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 get_preheat_mode_comp_rps(void)
{
    /*..hui [23-4-7오후 5:00:06] 예열 모드 RPS 60HZ..*/
    return BLDC_COMP_60Hz;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 get_hotgas_time(void)
{
    U16 mu16_return = 0;

	/*.. sean [25-02-04] gu8_Amb_Temperature_One_Degree으로 처리되어 front로 변경..*/
    if( gu8_Amb_Front_Temperature_One_Degree < HOT_GAS_AMB_TEMP_9_DIGREE )
    {
        /*..hui [23-4-7오후 1:17:04] 9도 미만..*/
        mu16_return = HOT_GAS_TIME_9_UNDER_765S;
    }
    else if( gu8_Amb_Front_Temperature_One_Degree <= HOT_GAS_AMB_TEMP_13_DIGREE )
    {
        /*..hui [23-4-7오후 1:23:42] 9도 ~ 13도..*/
        mu16_return = HOT_GAS_TIME_13_UNDER_600S;
    }
    else if( gu8_Amb_Front_Temperature_One_Degree <= HOT_GAS_AMB_TEMP_19_DIGREE )
    {
        /*..hui [23-4-7오후 1:23:55] 14도 ~ 19도..*/
        mu16_return = HOT_GAS_TIME_19_UNDER_180S;
    }
    else if( gu8_Amb_Front_Temperature_One_Degree <= HOT_GAS_AMB_TEMP_24_DIGREE )
    {
        /*..hui [23-4-7오후 1:24:08] 20도 ~ 24도..*/
        mu16_return = HOT_GAS_TIME_24_UNDER_30S;
    }
    else if( gu8_Amb_Front_Temperature_One_Degree <= HOT_GAS_AMB_TEMP_29_DIGREE )
    {
        /*..hui [23-4-7오후 1:24:18] 25도 ~ 29도..*/
        mu16_return = HOT_GAS_TIME_29_UNDER_20S;
    }
    else
    {
        /*..hui [23-4-7오후 1:24:23] 30도 이상..*/
        mu16_return = HOT_GAS_TIME_30_OVER_15S;
    }

    return mu16_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 get_preheat_time(void)
{
    U16 mu16_return = 0;

    if( gu8_Amb_Temperature_One_Degree < 14 )
    {
        /*..hui [23-4-7오후 5:05:22] 14도 미만..*/
        mu16_return = PREHEAT_TIME_14_UNDER_600S;
    }
    else if( gu8_Amb_Temperature_One_Degree < 20 )
    {
        /*..hui [23-4-7오후 5:05:35] 14도 ~ 19도..*/
        mu16_return = PREHEAT_TIME_20_UNDER_360S;
    }
    else
    {
        /*..hui [23-4-7오후 5:05:45] 20도 ~ 24도..*/
        mu16_return = PREHEAT_TIME_25_UNDER_360S;
    }

    return mu16_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_average_tray_temp(void)
{
    #if 0
    if( Bit18_Tray_In_Temp_Open_Short_Error__E41 == SET )
    {
        gu8_average_timer = 0;
        gu16_averge_count = 0;
        gu32_averge_temp_sum = 0;
        gu8_average_temp_max = 0;
        gu8_averge_temp_min = 100;

        /*..hui [23-9-19오후 3:35:54] 트레이 입수센서 에러시 정수온도로..*/
        gu8_average_tray_temp = gu8_Room_Temperature_One_Degree;

        return;
    }
    else{}

    if( gu8IceStep == STATE_20_WATER_IN_ICE_TRAY )
    {
        gu8_average_timer++;

        /*..hui [23-9-19오후 3:29:56] 1초 단위 적산..*/
        if( gu8_average_timer >= 10 )
        {
            gu8_average_timer = 0;
        }
        else
        {
            return;
        }

        /*..hui [23-9-19오후 1:28:26] 트레이 입수 50hz 전까지만 평균..*/
        /*..hui [23-9-19오후 1:31:21] 트레이 펌프 가동중에만 적산..*/
        if( bit_tray_pump_output == CLEAR )
        {
            return;
        }
        else{}

        /*if( gu16_Ice_Tray_Fill_Hz >= (C_ICE_TRAY_FILL_200CC - 20) )*/
        if( gu16_Ice_Tray_Fill_Hz >= 20 )
        {
            gu16_averge_count++;

            gu32_averge_temp_sum = gu32_averge_temp_sum + gu8_Tray_Temperature_One_Degree;

            if (gu8_Tray_Temperature_One_Degree > gu8_average_temp_max)
            {
                gu8_average_temp_max = gu8_Tray_Temperature_One_Degree;
            }
            else{}

            if (gu8_Tray_Temperature_One_Degree < gu8_averge_temp_min)
            {
                gu8_averge_temp_min = gu8_Tray_Temperature_One_Degree;
            }
            else{}

            if( gu16_averge_count >= 3 )
            {
                gu8_average_tray_temp = (U8)( (gu32_averge_temp_sum - (gu8_average_temp_max + gu8_averge_temp_min)) / (gu16_averge_count - 2) );
            }
            else{}
        }
        else{}
    }
    else
    {
        gu8_average_timer = 0;
        gu16_averge_count = 0;
        gu32_averge_temp_sum = 0;
        gu8_average_temp_max = 0;
        gu8_averge_temp_min = 100;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

