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
#include    "boost_pump.h"


void output_boost_pump(void);
U8 pump_retry_proc( void );
void start_boost_pump( U16 u16_data );
void stop_boost_pump( void );
void boost_pump_input(void);


/***********************************************************************************************************************/
TYPE_BYTE          U8PumpONB;
#define            u8PumpON                               U8PumpONB.byte
#define            Bit0_Pump_Feed_Operation_State         U8PumpONB.Bit.b0




TYPE_BYTE          U8PumpOFFB;
#define            u8PumpOFF                              U8PumpOFFB.byte
#define            Bit0_Pump_Not_Connect_Off_State        U8PumpOFFB.Bit.b0



bit bit_pump_output;
U8 gu8_pump_delay_timer;

PUMP_RETRY_STEP gu8_pump_retry_step;
U32 gu32_pump_retry_timer;

U16 gu16_current_pump_pwm;

U8 gu8_boost_on_decision_timer;
U8 gu8_boost_off_decision_timer;

bit bit_boost_pump_connect;
bit bit_boost_init_check;
/***********************************************************************************************************************/



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_boost_pump(void)
{
    #if 0
    boost_pump_input();

    if( bit_boost_pump_connect == SET )
    {
        /*..hui [20-9-25오후 5:39:12] 피드밸브 동작중에 같이 동작..*/
        if( bit_feed_output == SET )
        {
            gu8_pump_delay_timer++;

            if( gu8_pump_delay_timer >= PUMP_DELAY_TIME )
            {
                gu8_pump_delay_timer = PUMP_DELAY_TIME;

                Bit0_Pump_Feed_Operation_State = pump_retry_proc();
            }
            else{}
        }
        else
        {
            gu8_pump_delay_timer = 0;
            gu32_pump_retry_timer = 0;
            Bit0_Pump_Feed_Operation_State = CLEAR;
            gu8_pump_retry_step = STEP0_STANDBY;
        }
    }
    else
    {
        gu8_pump_delay_timer = 0;
        gu32_pump_retry_timer = 0;
        Bit0_Pump_Feed_Operation_State = CLEAR;
        gu8_pump_retry_step = STEP0_STANDBY;
    }

    /***********************************************************************************************/

    if( bit_boost_pump_connect == CLEAR )
    {
        Bit0_Pump_Not_Connect_Off_State = SET;
    }
    else
    {
        Bit0_Pump_Not_Connect_Off_State = CLEAR;
    }


/***********************************************************************************************/
    if (u8PumpOFF > 0)
    {
        pBOOST_PUMP_ON = CLEAR;      /*off*/
        bit_pump_output = CLEAR;
    }
    else
    {
        if (u8PumpON > 0)
        {
            pBOOST_PUMP_ON = SET;    /*on*/
            bit_pump_output = SET;
        }
        else
        {
            pBOOST_PUMP_ON = CLEAR;  /*off*/
            bit_pump_output = CLEAR;
        }
    }
/***********************************************************************************************/
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 pump_retry_proc( void )
{
    U8 mu8_return = 0;

    #if 0
    if( Bit3_Leakage_Sensor_Error__E01 == SET
        || Bit4_Room_Low_Water_Level_Error__E21 == SET )
    {
        gu8_pump_retry_step = STEP0_STANDBY;
        gu32_pump_retry_timer = 0;

        return mu8_return;
    }
    else{}

    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        bit_boost_init_check = SET;
    }
    else
    {
        if( bit_boost_init_check == SET )
        {
            /*..hui [23-3-24오전 11:31:08] 정수탱크 수위가 저수위->중수위/만수위로 변경된경우 청므부터 다시..*/
            bit_boost_init_check = CLEAR;
            gu8_pump_retry_step = STEP0_STANDBY;
        }
        else{}
    }

    switch( gu8_pump_retry_step )
    {
        case STEP0_STANDBY:

            gu32_pump_retry_timer = 0;
            gu8_pump_retry_step = STEP1_40MIN_ON;
            mu8_return = SET;

        break;

        case STEP1_40MIN_ON:

            gu32_pump_retry_timer++;

            if( gu32_pump_retry_timer >= PUMP_ON_40MIN )
            {
                gu32_pump_retry_timer = 0;
                gu8_pump_retry_step = STEP2_20MIN_OFF;
            }
            else
            {
                mu8_return = SET;
            }

        break;

        case STEP2_20MIN_OFF:

            gu32_pump_retry_timer++;

            if( gu32_pump_retry_timer >= PUMP_OFF_20MIN )
            {
                gu32_pump_retry_timer = 0;
                gu8_pump_retry_step = STEP3_40MIN_ON;
            }
            else{}

        break;

        case STEP3_40MIN_ON:

            gu32_pump_retry_timer++;

            if( gu32_pump_retry_timer >= PUMP_ON_40MIN )
            {
                gu32_pump_retry_timer = 0;
                gu8_pump_retry_step = STEP4_120MIN_OFF;
            }
            else
            {
                mu8_return = SET;
            }

        break;

        case STEP4_120MIN_OFF:

            gu32_pump_retry_timer++;

            if( gu32_pump_retry_timer >= PUMP_OFF_120MIN )
            {
                gu32_pump_retry_timer = 0;
                gu8_pump_retry_step = STEP3_40MIN_ON;
            }
            else{}

        break;

        default:

            gu32_pump_retry_timer = 0;
            gu8_pump_retry_step = 0;

        break;
    }
    #endif

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_boost_pump( U16 u16_data )
{
    //R_TAU0_Channel0_Start();
    //TDR01 = u16_data;
    //gu16_current_pump_pwm = u16_data;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_boost_pump( void )
{
    //R_TAU0_Channel0_Stop();
    //TDR01 = 0;
    //gu16_current_pump_pwm = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void boost_pump_input(void)
{
    #if 0
    if( pOUT_PUMP_IN == CLEAR )
    {
        gu8_boost_off_decision_timer = 0;
        gu8_boost_on_decision_timer++;

        if( gu8_boost_on_decision_timer >= BOOST_PUMP_ON_DETECT_TIME )
        {
            gu8_boost_on_decision_timer = BOOST_PUMP_ON_DETECT_TIME;
            bit_boost_pump_connect = SET;
        }
        else{}
    }
    else
    {
        gu8_boost_on_decision_timer = 0;
        gu8_boost_off_decision_timer++;

        if( gu8_boost_off_decision_timer >= BOOST_PUMP_OFF_DETECT_TIME )
        {
            gu8_boost_off_decision_timer = BOOST_PUMP_OFF_DETECT_TIME;
            bit_boost_pump_connect = CLEAR;
        }
        else{}
    }
    #endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


