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
#include    "cds.h"

#if 0
void input_cds(void);
void power_saving_init(void);
void check_ice_stop(void);
void delay_button_wakeup(void);
void detect_front_cds(void);
#endif

bit F_Sleep;                      // 취침선택

U16 gu16IceStopTime;
//----------------------------------------------------// CDS
U16 gu16Lux;
U16 gu16LuxNoUse;
bit F_IceStop;                        // 취침모드시 제빙정지


bit bit_wakeup_button;
U16 gu16_wakeup_delay_timer;

bit bit_illumi_State;
U16 gu16_led_sleep_timer;


bit bit_wake_up;


#if 0
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_cds(void)
{
    /*..hui [20-2-20오후 4:14:16] 버튼에 의한 절전 해지 시 5분 후에 동작하도록 개선..*/
    /*..hui [20-2-20오후 4:14:34] 야간에 물 먹을때 버튼 누르자마자 컴프 가동하여 소음 발생..*/
    delay_button_wakeup();

    if( F_Sleep != SET )
    {
        if( SLEEP_IN > gu16ADCds )                            // 절전진입
        {
            gu16Lux++;

            if(gu16Lux >= 6000)     // 10분경과시 절전진입
            {
                F_Sleep = SET;
                gu16Lux = 0;
            }
            else{}
        }
        else
        {
            gu16Lux = 0;
        }
    }
    else
    {
        if(gu16ADCds > SLEEP_OUT)                           // 절전해제
        {
            gu16Lux++;

            if(gu16Lux >= 6000)
            {
                F_Sleep = CLEAR;
                gu16Lux = 0;
            }
            else{}
        }
        else
        {
            gu16Lux = 0;
        }
    }

    if(F_Save != SET)
    {
        F_Sleep = 0;
        gu16Lux = 0;
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void power_saving_init(void)
{
    /*F_Sleep = 0;*/
    /*gu16Lux = 0;*/
    bit_wake_up = SET;

    /*..hui [20-2-20오후 4:15:27] 절전중일때만..*/
    if( F_Sleep == SET )
    {
        bit_wakeup_button = SET;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void delay_button_wakeup(void)
{
    if( bit_wakeup_button == SET && F_Sleep == SET )
    {
        gu16_wakeup_delay_timer++;

        if( gu16_wakeup_delay_timer >= POWER_SAVING_WAKEUP_DELAY_TIME )
        {
            gu16_wakeup_delay_timer = 0;
            bit_wakeup_button = CLEAR;
            F_Sleep = 0;
            gu16Lux = 0;
        }
        else{}
    }
    else
    {
        bit_wakeup_button = CLEAR;
        gu16_wakeup_delay_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_ice_stop(void)
{
    //===================================================// 취침모드시 6시간 제빙정지
    if( F_Sleep == SET && F_IceFull == SET && F_IceStop != SET )
    {
        F_IceStop = SET;

        if( gu8_Amb_Temperature_One_Degree >= 25 )
        {
            gu16IceStopTime = ICESTOP_TIME_FIVE_HOURS;
        }
        else
        {
            gu16IceStopTime = ICESTOP_TIME_SIX_HOURS;
        }
    }
    else if( F_Sleep != SET )
    {
        F_IceStop = CLEAR;
    }
    else if( gu16IceStopTime == 0 )
    {
        /*..hui [20-1-20오후 2:50:57] 6시간 지난 후 만빙상태 유지시 다시 카운트 시작함..*/
        /*..hui [20-1-20오후 2:51:14] 6시간 지난 후 만빙상태 확인하여 초기화하도록 변경..*/
        if( F_IceFull == CLEAR )
        {
            F_IceStop = CLEAR;
        }
        else{}
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void detect_front_cds(void)
{
    #if 0
    bit_illumi_State = F_Save;
    Bit5_illumi_State = bit_illumi_State;
    return;
    #endif

    /*..hui [19-12-19오후 9:51:01] 0이면 낮 // 1이면 밤(절전상태)..*/
    /*Bit5_illumi_State = F_Sleep;*/


    if( bit_wake_up == SET )
    {
        bit_wake_up = CLEAR;
        bit_illumi_State = CLEAR;
        gu16_led_sleep_timer = 0;
    }
    else{}

    /*..hui [19-12-19오후 9:56:55] 절전 모드와 따로 제어하도록..*/
    /*..hui [19-12-19오후 10:23:52] LED 제어용 조도센서는 항상 읽도록..*/
    if( bit_illumi_State != SET )
    {
        if( SLEEP_IN > gu16ADCds )
        {
            gu16_led_sleep_timer++;

            if(gu16_led_sleep_timer >= LED_SLEEP_ENTER_TIME)
            {
                bit_illumi_State = SET;
                gu16_led_sleep_timer = 0;
            }
            else{}
        }
        else
        {
            gu16_led_sleep_timer = 0;
        }
    }
    else
    {
        if(gu16ADCds > SLEEP_OUT)
        {
            gu16_led_sleep_timer++;

            if(gu16_led_sleep_timer >= LED_SLEEP_WAKEUP_TIME)
            {
                bit_illumi_State = CLEAR;
                gu16_led_sleep_timer = 0;
            }
            else{}
        }
        else
        {
            gu16_led_sleep_timer = 0;
        }
    }
}

#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


