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
#include    "hot_ster_tray.h"
#include    "uv_ice_off.h"
/***********************************************************************************************************************/
static void ice_off_uv_operation_timer(void);
static U8 ice_off_uv_standby_timer(void);
static void start_ice_off_uv(void);
static void initial_ice_off_uv_timer(void);
/***********************************************************************************************************************/
extern TYPE_BYTE          U8IceTrayUvOFFB;
#define            u8IceTrayUvOFF                                         U8IceTrayUvOFFB.byte
#define            Bit0_Ice_Tray_UV_Tank_Open_Off_State                   U8IceTrayUvOFFB.Bit.b0        /* 탱크커버가 열렸을 때 */
#define            Bit1_Ice_Tray_UV_Ice_Off_State                         U8IceTrayUvOFFB.Bit.b1        /* [2025-12-19] CH.PARK 얼음 OFF 시 UV OFF (미사용) */
#define            Bit2_Ice_Tray_UV_Ice_Extract_State                     U8IceTrayUvOFFB.Bit.b2        /* 얼음 추출 시 */
#define            Bit3_Ice_Tray_UV_Retry_3S_Off_State                    U8IceTrayUvOFFB.Bit.b3        /* 에러상태 RETRY */
extern TYPE_BYTE       U8OperationB;
#define         u8Operation                                       U8OperationB.byte
#define         Bit0_Cold_Operation_Disable_State                 U8OperationB.Bit.b0
#define         Bit1_Hot_Operation_Disable_State                  U8OperationB.Bit.b1
#define         Bit2_Ice_Operation_Disable_State                  U8OperationB.Bit.b2
#define         Bit3_Ice_Tank_Ster_Operation_Disable_State        U8OperationB.Bit.b3

extern bit F_TrayMotorUP;
extern bit F_TrayMotorDOWN;
/***********************************************************************************************************************/
U16 gu16_ice_off_uv_standby_timer_sec;
U16 gu16_ice_off_uv_standby_timer_min;
U16 gu16_ice_off_uv_standby_timer_hour;

U16 gu16_ice_off_uv_operation_timer_sec;
U8 gu8_ice_off_uv_operation_timer_min;

/* [2025-12-19] CH.PARK 얼음OFF 시 동작되는 트레이 UV 살균 제어 단계는 enum으로 선언해서 디버깅 및 사양 파악이 용이하게 함. */
UV_Ice_Off_Step_t gu8_uv_ice_off_step;
bit bit_ice_off_uv_start;

U16 gu16_uv_ice_off_timer;
/***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: uv_ice_off_control
* Description  : 얼음OFF 시 얼음 트레이 UV 살균 제어 함수
***********************************************************************************************************************/
U8 uv_ice_off_control(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;

    /*..hui [24-2-8오전 10:23:35] 더미탈빙 완료 전에도 미진행..*/
    /*..hui [24-2-8오전 10:42:29] 제빙 대기중이 아닐 경우에도..*/
    if((F_IceOn == SET && Bit2_Ice_Operation_Disable_State == CLEAR)
    || (F_IceInit == SET)
    || (gu8IceStep > STATE_0_STANDBY)
    || (bit_install_flushing_state == SET)
    || (bit_ice_tank_ster_start == SET)
    || (Bit2_Ice_Tray_Test_Start == SET)
    || (gu8_cody_take_off_ice_start == SET)
    /*|| F_Tank_Cover_Input == CLEAR )*/
    || (bit_uv_tank_input == CLEAR)
    )
    {
        /*..hui [24-2-8오전 10:59:29] 끝낸(취소된) 시점이 트레이가 올라가있는 상태이면 내리고 종료..*/
        if((gu8_uv_ice_off_step >= UV_ICE_OFF_STEP_TRAY_UP)
        && (gu8_uv_ice_off_step <= UV_ICE_OFF_STEP_TRAY_DOWN_2)
        )
        {
            if((gu8_ice_system_ok == SET)
            && (F_TrayMotorDOWN == CLEAR)
            && (gu8IceTrayLEV != ICE_TRAY_POSITION_ICE_THROW)
            )
            {
                down_tray_motor();
            }
            else{}
        }
        else{}

        initial_ice_off_uv_timer();
        gu8_uv_ice_off_step = UV_ICE_OFF_STEP_STANDBY;
        bit_ice_off_uv_start = CLEAR;
        return CLEAR;
    }
    else{}

/********************************************************************************************/
/********************************************************************************************/
    switch( gu8_uv_ice_off_step )
    {
        case UV_ICE_OFF_STEP_STANDBY :

            mu8_finish = ice_off_uv_standby_timer();

            if(mu8_finish == SET)
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step++;
                start_ice_off_uv();
            }
            else{}

        break;

        case UV_ICE_OFF_STEP_TRAY_DOWN_1 :

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                // [2025-12-19] CH.PARK, MAX는 sStepMotor.state이거 안씀.
                if( F_TrayMotorDOWN == CLEAR )
                {
                    /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
                    down_tray_motor();
                    gu16_uv_ice_off_timer = 0;
                    gu8_uv_ice_off_step++;
                }
                else
                {
                    gu16_uv_ice_off_timer++;

                    if( gu16_uv_ice_off_timer >= 600 )
                    {
                        gu16_uv_ice_off_timer = 0;
                        gu8_uv_ice_off_step = UV_ICE_OFF_STEP_UV_ON_TRAY_DOWN_2H;
                    }
                    else{}
                }
            }
            else
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step = UV_ICE_OFF_STEP_UV_ON_TRAY_DOWN_2H;
            }

        break;

        case UV_ICE_OFF_STEP_TRAY_DOWN_CHECK_1 :

            /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW )
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step++;
            }
            else
            {
                gu16_uv_ice_off_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_uv_ice_off_timer >= 600 )
                {
                    gu16_uv_ice_off_timer = 0;
                    gu8_uv_ice_off_step++;
                }
                else{}
            }

        break;

        case UV_ICE_OFF_STEP_UV_ON_TRAY_DOWN_2H :

            /*..hui [24-2-7오후 5:48:06] 탈빙 방향 2시간 가동..*/
            if( bit_ice_off_uv_start == SET )
            {
                /*..hui [19-10-25오전 9:41:56] 추출 또는 뚜껑열렸을 경우에는 정지..*/
                /*if( u8IceTankUvOFF == 0 )*/
                if( (Bit0_Ice_Tray_UV_Tank_Open_Off_State == CLEAR)
                && (Bit2_Ice_Tray_UV_Ice_Extract_State == CLEAR)
                )
                {
                    ice_off_uv_operation_timer();
                    mu8_return = SET;
                }
                else{}
            }
            else
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step++;
            }

        break;

        case UV_ICE_OFF_STEP_UV_OFF_10H :

            mu8_finish = ice_off_uv_standby_timer();

            if(mu8_finish == SET)
            {
                gu8_uv_ice_off_step++;
                start_ice_off_uv();
            }
            else{}

        break;

        case UV_ICE_OFF_STEP_TRAY_UP :

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                // [2025-12-19] CH.PARK, MAX는 sStepMotor.state이거 안씀.
                if( F_TrayMotorUP == CLEAR )
                {
                    /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
                    up_tray_motor();
                    gu16_uv_ice_off_timer = 0;
                    gu8_uv_ice_off_step++;
                }
                else
                {
                    gu16_uv_ice_off_timer++;

                    if( gu16_uv_ice_off_timer >= 600 )
                    {
                        gu16_uv_ice_off_timer = 0;
                        gu8_uv_ice_off_step = UV_ICE_OFF_STEP_UV_ON_TRAY_UP_2H;
                    }
                    else{}
                }
            }
            else
            {
                // [2025-12-19] CH.PARK 해빙제어 중이었으면 그대로 UV 살균 진행함.
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step = UV_ICE_OFF_STEP_UV_ON_TRAY_UP_2H;
            }

        break;

        case UV_ICE_OFF_STEP_TRAY_UP_CHECK :

            /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING )
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step++;
            }
            else
            {
                gu16_uv_ice_off_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_uv_ice_off_timer >= 600 )
                {
                    gu16_uv_ice_off_timer = 0;
                    gu8_uv_ice_off_step++;
                }
                else{}
            }

        break;

        case UV_ICE_OFF_STEP_UV_ON_TRAY_UP_2H :

            /*..hui [24-2-7오후 5:52:12] 제빙 방향 2시간 가동..*/
            if( bit_ice_off_uv_start == SET )
            {
                /*..hui [19-10-25오전 9:41:56] 추출 또는 뚜껑열렸을 경우에는 정지..*/
                /*if( u8IceTankUvOFF == 0 )*/
                if((Bit0_Ice_Tray_UV_Tank_Open_Off_State == CLEAR)
                && (Bit2_Ice_Tray_UV_Ice_Extract_State == CLEAR)
                )
                {
                    ice_off_uv_operation_timer();
                    mu8_return = SET;
                }
                else{}
            }
            else
            {
                gu16_uv_ice_off_timer = 0;
                /*gu8_uv_ice_off_step = 0;*/
                gu8_uv_ice_off_step++;
            }

        break;

        case UV_ICE_OFF_STEP_TRAY_DOWN_2 :

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                // [2025-12-19] CH.PARK, MAX는 sStepMotor.state이거 안씀.
                if( F_TrayMotorDOWN == CLEAR )
                {
                    /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
                    down_tray_motor();
                    gu16_uv_ice_off_timer = 0;
                    gu8_uv_ice_off_step++;
                }
                else
                {
                    gu16_uv_ice_off_timer++;

                    if( gu16_uv_ice_off_timer >= 600 )
                    {
                        gu16_uv_ice_off_timer = 0;
                        gu8_uv_ice_off_step = UV_ICE_OFF_STEP_FINISH;
                    }
                    else{}
                }
            }
            else
            {
                // [2025-12-19] CH.PARK 해빙제어 중이었으면 그대로 UV 살균 진행함.
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step = UV_ICE_OFF_STEP_FINISH;
            }

        break;

        case UV_ICE_OFF_STEP_TRAY_DOWN_CHECK_2 :

            /* [2025-12-19] CH.PARK 트레이 탈빙 방향 이동완료 체크 */
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW )
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step++;
            }
            else
            {
                gu16_uv_ice_off_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_uv_ice_off_timer >= 600 )
                {
                    gu16_uv_ice_off_timer = 0;
                    gu8_uv_ice_off_step++;
                }
                else{}
            }

        break;

        case UV_ICE_OFF_STEP_FINISH :

            /*..hui [24-2-8오전 10:27:18] 종료.. 다시 처음부터..*/
            gu16_uv_ice_off_timer = 0;
            gu8_uv_ice_off_step = 0;
            initial_ice_off_uv_timer();

        break;


        default :

            gu16_uv_ice_off_timer = 0;
            gu8_uv_ice_off_step = 0;

        break;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: ice_off_uv_operation_timer
* Description  : 얼음OFF UV 살균 중 동작 타이머 (2시간)
***********************************************************************************************************************/
static void ice_off_uv_operation_timer(void)
{
    gu16_ice_off_uv_operation_timer_sec++;

    if(gu16_ice_off_uv_operation_timer_sec >= 600)
    {
        gu16_ice_off_uv_operation_timer_sec = 0;
        gu8_ice_off_uv_operation_timer_min++;
    }
    else{}

    if(gu8_ice_off_uv_operation_timer_min >= UV_ICE_OFF_OPERATION_TIME_MIN)
    {
        bit_ice_off_uv_start = CLEAR;
        initial_ice_off_uv_timer();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: ice_off_uv_standby_timer
* Description  : 얼음OFF UV 살균 전 대기 타이머 (10시간)
***********************************************************************************************************************/
static U8 ice_off_uv_standby_timer(void)
{
    U8 mu8_return = 0;

    gu16_ice_off_uv_standby_timer_sec++;

    if(gu16_ice_off_uv_standby_timer_sec >= 600)
    {
        gu16_ice_off_uv_standby_timer_sec = 0;
        gu16_ice_off_uv_standby_timer_min++;
    }
    else{}

    if(gu16_ice_off_uv_standby_timer_min >= 60)
    {
        gu16_ice_off_uv_standby_timer_min = 0;
        gu16_ice_off_uv_standby_timer_hour++;
    }
    else{}

    if( gu16_ice_off_uv_standby_timer_hour >= 10 )
    {
        initial_ice_off_uv_timer();
        mu8_return = SET;
    }
    else{}

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: start_ice_off_uv
* Description  : 얼음OFF UV 살균 시작
***********************************************************************************************************************/
static void start_ice_off_uv(void)
{
    bit_ice_off_uv_start = SET;
    initial_ice_off_uv_timer();
}

/***********************************************************************************************************************
* Function Name: initial_ice_off_uv_timer
* Description  : 얼음OFF UV 살균 관련된 타이머 변수 모두 초기화
***********************************************************************************************************************/
static void initial_ice_off_uv_timer(void)
{
    gu16_ice_off_uv_operation_timer_sec = 0;
    gu8_ice_off_uv_operation_timer_min = 0;

    gu16_ice_off_uv_standby_timer_sec = 0;
    gu16_ice_off_uv_standby_timer_min = 0;
    gu16_ice_off_uv_standby_timer_hour = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


