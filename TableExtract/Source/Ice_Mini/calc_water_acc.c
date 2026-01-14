/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : AT+CONNECT=74F07DB01010
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "calc_water_acc.h"

void calc_water_usage(void);
void clac_effluent_water_acc(void);
void calc_ice_tray_input_water(void);
void calc_auto_drain_water(void);
/////void calc_hot_ster_water(void);
void calc_flushing_water(void);

void acc_user_water( U16 mu16_water_acc );

TYPE_BYTE          U8IceTankSterACCB;
#define            u8IceTankSterAcc                       U8IceTankSterACCB.byte
#define            Bit0_Ster_Prepare_Acc_State            U8IceTankSterACCB.Bit.b0
#define            Bit1_Hot_Spray_Acc_State               U8IceTankSterACCB.Bit.b1
#define            Bit2_Lukewarm_Spray_Acc_State          U8IceTankSterACCB.Bit.b2
#define            Bit3_Final_Clean_Acc_State             U8IceTankSterACCB.Bit.b3
#define            Bit4_Ice_Tray_Clean_Acc_State          U8IceTankSterACCB.Bit.b4
#define            Bit5_Melt_Ice_Acc_State                U8IceTankSterACCB.Bit.b5


U16 u16_user_effluent_time;
U16 u16_user_effluent_total_time;
U16 u16_user_effluent_cup_size;

//U32 gu32_total_usage_water_ml;
//U32 gu32_total_usage_water_ml_old;
//U32 gu32_total_usage_water_ml_save;


//U16 u16_display_usage_water_gal;
//U16 gu16_total_usage_water_gal_save;
//U16 u16_display_usage_water_gal_old;

bit bit_tray_water_acc;

bit bit_drain_water_acc;
U8 gu8_ster_water_acc_step;



U16 gu16_temporary_save_usage;

U16 gu16_water_usage_neo_filter;
U16 gu16_water_usage_ro_filter;
U16 gu16_water_usage_ino_filter;



U8 gu8_teeeeeeeeeeeeeeeest;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_water_usage(void)
{
    /*..hui [23-5-10오전 9:58:52] 처음 만수위 도달하고나서 시작..*/
    if( F_FW_Version_Display_Mode == CLEAR )
    {
        return;
    }
    else{}

    /*..hui [23-5-10오전 9:54:16] 추출 유량 계산..*/
    clac_effluent_water_acc();

    /*..hui [23-5-10오전 9:54:44] 트레이 입수 유량 계산..*/
    calc_ice_tray_input_water();

    /*..hui [23-7-28오후 2:49:08] 순환배수 유량 계산..*/
    calc_auto_drain_water();

    /*..hui [23-7-28오후 2:54:23] 얼음 탱크 살균 시 유량 계산..*/
    /////calc_hot_ster_water();

    /*..hui [23-12-18오후 3:34:07] 플러싱시 유량 계산..*/
    /*..hui [23-12-18오후 7:04:34] flushing_finish로 이동 종료 후 한번만....*/
    /*calc_flushing_water();*/

    #if 0
    if( gu8_teeeeeeeeeeeeeeeest == 1 )
    {
        gu8_teeeeeeeeeeeeeeeest = 0;
        acc_user_water( 500 );
    }
    else if( gu8_teeeeeeeeeeeeeeeest == 2 )
    {
        gu8_teeeeeeeeeeeeeeeest = 0;
        acc_user_water( 1230 );
    }
    else if( gu8_teeeeeeeeeeeeeeeest == 3 )
    {
        gu8_teeeeeeeeeeeeeeeest = 0;
        acc_user_water( 2690 );
    }
    else if( gu8_teeeeeeeeeeeeeeeest == 4 )
    {
        gu8_teeeeeeeeeeeeeeeest = 0;
        acc_user_water( 3510 );
    }
    else if( gu8_teeeeeeeeeeeeeeeest == 5 )
    {
        gu8_teeeeeeeeeeeeeeeest = 0;
        acc_user_water( 4920 );
    }
    else if( gu8_teeeeeeeeeeeeeeeest == 6 )
    {
        gu8_teeeeeeeeeeeeeeeest = 0;
        acc_user_water( 5940 );
    }
    else{}
    #endif

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void clac_effluent_water_acc(void)
{
    U16 mu16_water_acc = 0;

    #if 1
    if( F_WaterOut == SET )
    {
        u16_user_effluent_time++;
        u16_user_effluent_total_time = u16Efluent_Time;

        if( u8Extract_Continue == SET )
        {
            if( u8WaterOutState == PURE_WATER_SELECT )
            {
                u16_user_effluent_cup_size = 2100;
            }
            else if( u8WaterOutState == COLD_WATER_SELECT )
            {
                u16_user_effluent_cup_size = 2200;
            }
            else /*if(u8WaterOutState == HOT_WATER_SELECT)*/
            {
                u16_user_effluent_cup_size = 2000;
            }
        }
        else
        {
            if( gu8Cup_level == CUP_LEVEL_1_120ML )
            {
                u16_user_effluent_cup_size = 120;
            }
            else if( gu8Cup_level == CUP_LEVEL_2_250ML )
            {
                u16_user_effluent_cup_size = 250;
            }
            else if( gu8Cup_level == CUP_LEVEL_3_500ML )
            {
                u16_user_effluent_cup_size = 500;
            }
            else if( gu8Cup_level == CUP_LEVEL_4_1000ML )
            {
                u16_user_effluent_cup_size = 1000;
            }
           
        }
    }
    else
    {
        if(u16_user_effluent_time != 0)
        {
            u16_user_effluent_time = u16_user_effluent_time + 1;

            /*..hui [23-8-2오후 4:43:13] 5ml 단위도 있기 때문에 ..*/
            mu16_water_acc =
                (U16)(((U32)u16_user_effluent_time * (U32)u16_user_effluent_cup_size) / u16_user_effluent_total_time);

            /*mu16_water_acc = mu16_water_acc * 10;*/
            acc_user_water( mu16_water_acc );

            /*..hui [21-8-3오후 3:53:17] 와이파이 적산용 물량..*/
            gu16_wifi_water_acc = (gu16_extract_display_cnt*10);

            u16_user_effluent_time = 0;
        }
        else
        {
            u16_user_effluent_time = 0;
            u16_user_effluent_total_time = 0;
            u16_user_effluent_cup_size = 0;
        }
    }
    #endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_ice_tray_input_water(void)
{
    U16 mu16_water_acc = 0;

    if( gu8IceStep >= STATE_21_ICE_SWITCH_MOVE )
    {
        if( bit_tray_water_acc == CLEAR )
        {
            bit_tray_water_acc = SET;
            /*..hui [23-5-9오후 2:45:56] 아이스트레이 입수 용량 300cc..*/
            mu16_water_acc = ICE_TRAY_INPUT_USING_WATER;
            acc_user_water( mu16_water_acc );
        }
        else{}
    }
    else
    {
        bit_tray_water_acc = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_auto_drain_water(void)
{
    U16 mu16_water_acc = 0;

    if( F_DrainStatus == SET )
    {
        if( bit_drain_water_acc == CLEAR )
        {
            bit_drain_water_acc = SET;

            /*..hui [23-7-28오후 2:50:12] 자동배수 물량 500cc.. 확인해봐야 함 ..*/
            mu16_water_acc = AUTO_DRAIN_USING_WATER;
            acc_user_water( mu16_water_acc );
        }
        else{}
    }
    else
    {
        bit_drain_water_acc = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void calc_hot_ster_water(void)
{
    U16 mu16_water_acc = 0;

    if( bit_ice_tank_ster_start == SET )
    {
        if( gu8_ice_ster_mode == STER_MODE_PREPARE )
        {
            if( Bit0_Ster_Prepare_Acc_State == CLEAR )
            {
                Bit0_Ster_Prepare_Acc_State = SET;
                mu16_water_acc = PREPARE_STER_USING_WATER;
                acc_user_water( mu16_water_acc );
            }
            else{}
        }
        else if( gu8_ice_ster_mode == STER_MODE_HOT_SPRAY_STATE )
        {
            if( Bit1_Hot_Spray_Acc_State == CLEAR )
            {
                Bit1_Hot_Spray_Acc_State = SET;
                mu16_water_acc = HOT_SPRAY_USING_WATER;
                acc_user_water( mu16_water_acc );
            }
            else{}
        }
        else if( gu8_ice_ster_mode == STER_MODE_LUKEWARM_SPRAY_STATE )
        {
            if( Bit2_Lukewarm_Spray_Acc_State == CLEAR )
            {
                Bit2_Lukewarm_Spray_Acc_State = SET;
                mu16_water_acc = LUKEWARM_SPRAY_USING_WATER;
                acc_user_water( mu16_water_acc );
            }
            else{}
        }
        else if( gu8_ice_ster_mode == STER_MODE_FINAL_CLEAN_STATE )
        {
            if( Bit3_Final_Clean_Acc_State == CLEAR )
            {
                Bit3_Final_Clean_Acc_State = SET;
                mu16_water_acc = FINAL_CLEAN_USING_WATER;
                acc_user_water( mu16_water_acc );
            }
            else{}
        }
        else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN_PREPARE )
        {
            Bit4_Ice_Tray_Clean_Acc_State = CLEAR;
        }
        else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN )
        {
            if( Bit4_Ice_Tray_Clean_Acc_State == CLEAR )
            {
                Bit4_Ice_Tray_Clean_Acc_State = SET;
                mu16_water_acc = ICE_TRAY_CLEAN_USING_WATER;
                acc_user_water( mu16_water_acc );
            }
            else{}
        }
        else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE )
        {
            Bit5_Melt_Ice_Acc_State = CLEAR;
        }
        else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE )
        {
            if( Bit5_Melt_Ice_Acc_State == CLEAR )
            {
                Bit5_Melt_Ice_Acc_State = SET;
                mu16_water_acc = MELT_ICE_USING_WATER;
                acc_user_water( mu16_water_acc );
            }
            else{}
        }
        else{}
    }
    else
    {
        u8IceTankSterAcc = 0;
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_flushing_water(void)
{
    U16 mu16_water_acc = 0;

    if( bit_install_flushing_state == SET )
    {
        mu16_water_acc = INSTALL_FLUSHING_USING_WATER;
        acc_user_water( mu16_water_acc );
    }
    else
    {
        if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
        {
            mu16_water_acc = NEO_INO_FILTER_FLUSHING_USING_WATER;
            acc_user_water( mu16_water_acc );
        }
        else /*if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL )*/
        {
            mu16_water_acc = NEO_RO_INO_FILTER_FLUSHING_USING_WATER;
            acc_user_water( mu16_water_acc );
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void acc_user_water( U16 mu16_water_acc )
{
    U16 mu16_a = 0;

    gu16_temporary_save_usage += mu16_water_acc;

    /*..hui [23-12-5오후 5:22:02] 1리터마다 EEPROM에 저장..*/
    if( gu16_temporary_save_usage >= 1000 )
    {
        mu16_a = (U16)(gu16_temporary_save_usage / 1000);

        gu16_temporary_save_usage = (gu16_temporary_save_usage - (mu16_a * 1000));

        /*..hui [23-12-5오후 5:23:39] 1리터 증가..*/
        /*gu16_water_usage_neo_filter = gu16_water_usage_neo_filter + 1;*/
        gu16_water_usage_neo_filter = gu16_water_usage_neo_filter + mu16_a;

        if(gu16_water_usage_neo_filter >= NEO_TOTAL_USAGE_MAX_WATER)
        {
            gu16_water_usage_neo_filter = NEO_TOTAL_USAGE_MAX_WATER;
        }
        else{}


        /*..hui [23-12-5오후 5:23:39] 1리터 증가..*/
        /*gu16_water_usage_ro_filter = gu16_water_usage_ro_filter + 1;*/
        gu16_water_usage_ro_filter = gu16_water_usage_ro_filter + mu16_a;

        if(gu16_water_usage_ro_filter >= RO_TOTAL_USAGE_MAX_WATER)
        {
            gu16_water_usage_ro_filter = RO_TOTAL_USAGE_MAX_WATER;
        }
        else{}

        /*..hui [23-12-5오후 5:23:39] 1리터 증가..*/
        /*gu16_water_usage_ino_filter = gu16_water_usage_ino_filter + 1;*/
        gu16_water_usage_ino_filter = gu16_water_usage_ino_filter + mu16_a;

        if(gu16_water_usage_ino_filter >= INO_TOTAL_USAGE_MAX_WATER)
        {
            gu16_water_usage_ino_filter = INO_TOTAL_USAGE_MAX_WATER;
        }
        else{}

    }
    else{}


    #if 0
    gu32_total_usage_water_ml += mu16_water_acc;

    if(gu32_total_usage_water_ml >= TOTAL_USAGE_MAX_WATER)
    {
        gu32_total_usage_water_ml = TOTAL_USAGE_MAX_WATER;
    }
    else{}

    gu16_wifi_total_usage_water = (U16)(gu32_total_usage_water_ml / 1000);

    /*..hui [23-6-7오후 5:32:58] 1이면 0.1gal..*/
    u16_display_usage_water_gal = (U16)(gu32_total_usage_water_ml / ML_PER_GAL);

    if( u16_display_usage_water_gal >= MAX_GAL )
    {
        u16_display_usage_water_gal = MAX_GAL;
    }
    else{}

    #if 0
    if( gu32_total_usage_water_ml <= 1000 )
    {
        mu8_diff = 1;
    }
    else
    {
        /*..hui [23-6-7오후 5:44:26] 1000gal 이상(100gal)은 1gal마다 저장..*/
        mu8_diff = 10;
    }
    #endif

    mu8_diff = 120;


    if( gu32_total_usage_water_ml >= gu32_total_usage_water_ml_old + mu8_diff
        || gu32_total_usage_water_ml < gu32_total_usage_water_ml_old )
    {
        gu32_total_usage_water_ml_old = gu32_total_usage_water_ml;

        gu32_total_usage_water_ml_save = gu32_total_usage_water_ml;

        if( gu32_total_usage_water_ml_save >= TOTAL_USAGE_MAX_WATER )
        {
            gu32_total_usage_water_ml_save = TOTAL_USAGE_MAX_WATER;
        }
        else{}
    }
    else{}
    #endif




    #if 0
    /*..hui [23-6-7오후 5:44:03] 99.9gal 이하는 0.1gal마다 저장..*/
    /*if( u16_display_usage_water_gal <= 999 )*/
    if( u16_display_usage_water_gal <= 1000 )
    {
        mu8_diff = 1;
    }
    else
    {
        /*..hui [23-6-7오후 5:44:26] 1000gal 이상(100gal)은 1gal마다 저장..*/
        mu8_diff = 10;
    }

    if( u16_display_usage_water_gal >= u16_display_usage_water_gal_old + mu8_diff
        || u16_display_usage_water_gal < u16_display_usage_water_gal_old )
    {
        u16_display_usage_water_gal_old = u16_display_usage_water_gal;

        gu16_total_usage_water_gal_save = u16_display_usage_water_gal;

        if( gu16_total_usage_water_gal_save >= MAX_GAL )
        {
            gu16_total_usage_water_gal_save = MAX_GAL;
        }
        else{}
    }
    else{}
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


