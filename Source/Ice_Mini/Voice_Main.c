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
#include    "Voice_Main.h"

//void VoiceIC_Type_Check(void);
void Voice_Initialize(void);
void ProcessVoice_Main(void);
void Play_Voice(U16 mu16MemoryAddress);
U8 IsLevel_Mute(U16 addr);
U8 IsLevel_Melody(U16 addr);
/*U8 IsLevel_Voice(U16 addr);*/
U8 IsCriticalVoice(U16 addr);



U16 gu16_voice_address;
U16 gu16_voice_command;

U8 gu8VoiceVolumeLevel;
U8 gu8Sound_Type;                       // 음성안내 모드 (기존 gu8VoiceLevel)

U8 gu8_voice_language_type;


bit F_OneMoreSound;
bit F_Beep_Sound;
bit F_PlayVoice;     /*Sound Level에 따른 Address 받으면 SET 하여 음성 출력*/


bit bit_power_on_voice;

U8 gu8Voice_IC_Type;

U8 gu8_voice_land_select_timer;
U8 gu8_nyquest_select_timer;
U8 gu8_voice_sel_finish;

U8 gu8_power_on_timer;




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Voice_Initialize(void)
{
    /*..hui [21-9-8오후 3:18:10] 포타 진행중 부팅음 안나게..*/
    if( gu8_fota_start == SET )
    {
        bit_power_on_voice = SET;
        gu8_fota_start = CLEAR;

        /*..hui [24-1-18오후 5:30:03] FOTA 완료 후 BLE 활성화..*/
        WifiKey(WIFI_KEY_BLE);
    }
    else
    {
        bit_power_on_voice = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ProcessVoice_Main(void)
{
    if( bit_power_on_voice == CLEAR )
    {
        gu8_power_on_timer++;

        if( gu8_power_on_timer >= 10 )
        {
            gu8_power_on_timer = 0;
            bit_power_on_voice = SET;

    		Play_Voice(VOICE_191_MELODY_PLUG_IN_COWAY);
        }
        else{}
    }
    else{}

    gu16_voice_command = 0;   /*..모두 전송하고 나면 Command 초기화..*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Play_Voice(U16 mu16MemoryAddress)
{
    if( (mu16MemoryAddress == VOICE_151_SPECIAL_FUNCTION)
    || (mu16MemoryAddress == VOICE_196_WIFI_SELECT)
    || (mu16MemoryAddress == VOICE_197_WIFI_WARNING)
    || (mu16MemoryAddress == VOICE_198_WIFI_SET_ON)
    || (mu16MemoryAddress == VOICE_199_WIFI_SET_OFF)
    || (mu16MemoryAddress == VOICE_151_INFORM_MY2_RECIPE)
    )
    {
        gu16_voice_address = mu16MemoryAddress;
    }
    else
    {
        gu16_voice_address = mu16MemoryAddress + KR_25;
    }

    if( gu8Sound_Type == SOUND_TYPE_MUTE )
    {
        if( IsLevel_Mute( mu16MemoryAddress ) == TRUE )
        {
            F_PlayVoice = SET;
        }
        else{}
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        if( IsLevel_Mute( mu16MemoryAddress ) == TRUE
        || IsLevel_Melody( mu16MemoryAddress ) == TRUE )
        {
            F_PlayVoice = SET;
        }
        else{}
    }
    else if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        /*..hui [24-5-30오후 2:19:32] 롬사이즈 다이어트.. 음성출력은 전부 다 출력..*/
        F_PlayVoice = SET;
    }
    else{}

    /////Voice_Stop_Next_Lab();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 음성안내를 [음소거]로 설정한 상태에서도 나와야 하는 음성들 정의
***********************************************************************************************************************/
U8 IsLevel_Mute(U16 addr)
{
    switch( addr )
    {
        /* Errors */
        case VOICE_4_CALL_AS_COLD_WATER_ERROR:
        case VOICE_5_CALL_AS_HOT_WATER_ERROR:
        case VOICE_6_CALL_AS_ICE_ERROR:
        case VOICE_7_CALL_AS_WATER_SUPPLY_ERROR:
        case VOICE_8_CALL_AS_WATER_LEAKAGE_ERROR:

        /* Wifi,BLE,IoCare */
        case VOICE_16_START_SMART_TESTING_MODE:
        case VOICE_17_FINISH_SMART_TESTING_MODE_NO_ERROR:
        case VOICE_18_FINISH_SMART_TESTING_MODE_WITH_ERROR:
        case VOICE_19_START_BLE_PAIRNG:
        case VOICE_20_INFORM_APP_PAIRING_SUCCESS_WITH_BLE:
        case VOICE_21_INFORM_APP_PAIRING_FAIL_WITH_BLE:
        case VOICE_22_START_WIFI_PAIRNG:
        case VOICE_23_INFORM_APP_PAIRING_SUCCESS_WITH_WIFI:
        case VOICE_24_INFORM_APP_PAIRING_FAIL_WITH_WIFI:
        case VOICE_25_INFORM_WIFI_MODE_DEACTIVATED:
        case VOICE_26_APPLY_WIFI_AFTER_DEACTIVATING:
        case VOICE_27_INFORM_WIFI_ON:
        case VOICE_28_INFORM_WIFI_OFF:
        case VOICE_29_APPLY_PRODUCT_CERT_OCCUPATION:
        case VOICE_30_INFORM_APP_PAIRING_SUCCESS_WITH_WIFI:
        case VOICE_31_INFORM_APP_PAIRING_FAIL_WITH_WIFI:
        case VOICE_32_INFORM_APP_PAIRING_FAIL_WITH_WIFI:
        case VOICE_34_INFORM_WIFI_BEFORE_FLUSHING:
        case VOICE_196_WIFI_SELECT:
        case VOICE_197_WIFI_WARNING:
        case VOICE_198_WIFI_SET_ON:
        case VOICE_199_WIFI_SET_OFF:

        /* 설치 및 필터교체 */
        case VOICE_35_INFORM_FLUSHING_START:
        case VOICE_36_INFORM_FLUSHING_FINISH:
        case VOICE_33_INFORM_PROEDUCT_BEFORE_FLUSHING:

        /* 음성, 효과음 */
        case VOICE_65_VOICE_MODE:
        case VOICE_66_MELODY_MODE:
        case VOICE_67_MUTE_MODE:
        case VOICE_68_MODE_SET_VOICE:
        case VOICE_69_MODE_SET_MELODY:
        case VOICE_70_MODE_SET_MUTE:

        /* 부팅음 */
        case VOICE_191_MELODY_PLUG_IN_COWAY:

        // [2025-12-04] CH.PARK 얼음걸림 음성안내는 음소거 하더라도 나와야 함 (상품기획)
        case VOICE_1365_ICE_STUCK_DETECTED:
            return TRUE;

        default :
            return FALSE;
    }

    return FALSE;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 음성안내를 [멜로디]로 설정한 상태에서도 나와야 하는 음성들 정의
***********************************************************************************************************************/
U8 IsLevel_Melody(U16 addr)
{
    switch( addr )
    {
        case VOICE_4_CALL_AS_COLD_WATER_ERROR:
        case VOICE_5_CALL_AS_HOT_WATER_ERROR:
        case VOICE_6_CALL_AS_ICE_ERROR:
        case VOICE_7_CALL_AS_WATER_SUPPLY_ERROR:
        case VOICE_8_CALL_AS_WATER_LEAKAGE_ERROR:

        case VOICE_16_START_SMART_TESTING_MODE:
        case VOICE_17_FINISH_SMART_TESTING_MODE_NO_ERROR:
        case VOICE_18_FINISH_SMART_TESTING_MODE_WITH_ERROR:
        case VOICE_19_START_BLE_PAIRNG:
        case VOICE_20_INFORM_APP_PAIRING_SUCCESS_WITH_BLE:
        case VOICE_21_INFORM_APP_PAIRING_FAIL_WITH_BLE:
        case VOICE_22_START_WIFI_PAIRNG:
        case VOICE_23_INFORM_APP_PAIRING_SUCCESS_WITH_WIFI:
        case VOICE_24_INFORM_APP_PAIRING_FAIL_WITH_WIFI:
        case VOICE_25_INFORM_WIFI_MODE_DEACTIVATED:
        case VOICE_26_APPLY_WIFI_AFTER_DEACTIVATING:
        case VOICE_27_INFORM_WIFI_ON:
        case VOICE_28_INFORM_WIFI_OFF:
        case VOICE_29_APPLY_PRODUCT_CERT_OCCUPATION:
        case VOICE_30_INFORM_APP_PAIRING_SUCCESS_WITH_WIFI:
        case VOICE_31_INFORM_APP_PAIRING_FAIL_WITH_WIFI:
        case VOICE_32_INFORM_APP_PAIRING_FAIL_WITH_WIFI:
        case VOICE_34_INFORM_WIFI_BEFORE_FLUSHING:
        case VOICE_196_WIFI_SELECT:
        case VOICE_197_WIFI_WARNING:
        case VOICE_198_WIFI_SET_ON:
        case VOICE_199_WIFI_SET_OFF:

        case VOICE_33_INFORM_PROEDUCT_BEFORE_FLUSHING:
        case VOICE_35_INFORM_FLUSHING_START:
        case VOICE_36_INFORM_FLUSHING_FINISH:

        case VOICE_65_VOICE_MODE:
        case VOICE_66_MELODY_MODE:
        case VOICE_67_MUTE_MODE:
        case VOICE_68_MODE_SET_VOICE:
        case VOICE_69_MODE_SET_MELODY:
        case VOICE_70_MODE_SET_MUTE:

        case VOICE_191_MELODY_PLUG_IN_COWAY:

        case VOICE_192_MELODY_DISPENSE_CONTINUOUS:
        case VOICE_193_MELODY_DISPENSE_START:
        case VOICE_194_MELODY_DISPENSE_FINISH:
        case VOICE_196_MELODY_SELECT:
        case VOICE_197_MELODY_WARNING:
        case VOICE_198_MELODY_SET_ON:
        case VOICE_199_MELODY_SET_OFF:

        // [2025-12-04] CH.PARK 얼음걸림 음성안내는 음소거 하더라도 나와야 함 (상품기획)
        case VOICE_1365_ICE_STUCK_DETECTED:
            return TRUE;

        default :
            return FALSE;
    }

    return FALSE;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
U8 IsLevel_Voice(U16 addr)
{
    switch( addr )
    {
        case VOICE_1_SHUTOFF_WATER_FILTER_COVER:
        case VOICE_2_STOP_ICE_ICETANK_COVER:
        case VOICE_3_SHUTOFF_WATER_SIDE_COVER:
        case VOICE_4_SHUTOFF_WATER_TOP_COVER:
        case VOICE_5_SHUTOFF_WATER_FRONT_COVER:
        case VOICE_6_RESTART_ICE_COVER_OK:
        case VOICE_7_CALL_AS_COLD_WATER_ERROR:
        case VOICE_8_CLEAN_DUST_FILTER_COLD_WATER_ERROR:
        case VOICE_9_CALL_AS_HOT_WATER_ERROR:
        case VOICE_10_CALL_AS_ICE_ERROR:
        case VOICE_11_CALL_AS_WATER_SUPPLY_ERROR:
        case VOICE_12_CALL_AS_WATER_LEAKAGE_ERROR:
        case VOICE_13_REPLACE_ONLY_FILTER_NO1_NO3:
        case VOICE_14_PRESS_RESET_BUTTON_AFTER_NEW_FILTER:
        case VOICE_15_REPLACE_ADD_FILTER_NO3_PLEASE:
        case VOICE_16_REPLACE_AFTER_CHECK_FILTER_NO1_NO3:
        case VOICE_17_REPLACE_ADD_FILTER_NO1_PLEASE:
        case VOICE_18_CLOSE_COVER_AFTER_FILTER_NO1_NO3:
        case VOICE_19_PRESS_YES_OR_NO_AFTER_FILTER_NO1_NO3:
        case VOICE_20_REPLACE_AFTER_CHECK_FILTER_NO1_NO3_V2:
        case VOICE_21_PRESS_YES_OR_NO_AFTER_FILTER_NO1_NO3_WELL:
        case VOICE_22_REPLACE_ONLY_FILTER_NO1_NO3_NOT_YET_NO2:
        case VOICE_23_START_FILTER_FLUSHING:
        case VOICE_24_FINISH_FILTER_FLUSHING:
        case VOICE_25_CHECK_FILTER_FLUSHING_MANUAL:
        case VOICE_26_REPLACE_FILTER_NO1_NO3:
        case VOICE_27_INFORM_ACTIVATED_FILTER_NO1_ADD_NO3:
        case VOICE_28_INFORM_ACTIVATED_FILTER_NO3_ADD_NO1:
        case VOICE_29_CLOSE_COVER_FOR_FILTER_FLUSHING:
        case VOICE_30_START_FILTER_FLUSHING_NO1_NO3:
        case VOICE_31_PRESS_RESET_BUTTON_AFTER_NEW_FILTER:
        case VOICE_32_PRESS_RESET_BUTTON_FILTER_NO1:
        case VOICE_33_PRESS_RESET_BUTTON_FILTER_NO3:
        case VOICE_34_REPLACE_ADD_FILTER_NO3:
        case VOICE_35_REPLACE_ADD_FILTER_NO1:
        case VOICE_36_CANCEL_RESET_FILTER_NO1:
        case VOICE_37_CANCEL_RESET_FILTER_NO2:
        case VOICE_38_CANCEL_RESET_FILTER_NO3:
        case VOICE_39_CANCEL_FILTER_FLUSHING:
        case VOICE_40_PRESS_RESET_BUTTON_NO1:
        case VOICE_41_PRESS_RESET_BUTTON_NO2:
        case VOICE_42_PRESS_RESET_BUTTON_NO3:
        case VOICE_43_REPLACE_ADD_FILTER_NO2_NO3_FOR_ALL:
        case VOICE_44_REPLACE_ADD_FILTER_NO1_NO3_FOR_ALL:
        case VOICE_45_REPLACE_ADD_FILTER_NO1_NO2_FOR_ALL:
        case VOICE_46_PRESS_YES_OR_NO_AFTER_ALL_FILTERS:
        case VOICE_47_CHECK_REPLACE_ALL_FILTERS:
        case VOICE_48_NOT_SELECTED_FILTER_FLUSHING:
        case VOICE_49_REPLACE_FILTER_ALL:
        case VOICE_50_INFORM_ACTIVATION_ADD_OTHER_FILTER:
        case VOICE_51_CLOSE_COVER_FOR_FILTER_FLUSHING_V2:
        case VOICE_52_PRESS_RESET_BUTTON_AFTER_REPLACE_FILTER:
        case VOICE_53_PRESS_RESET_BUTTON_DEACTIVATED:
        case VOICE_54_REPLACE_ADD_FILTER_NO3_FOR_ALL:
        case VOICE_55_REPLACE_ADD_FILTER_NO1_FOR_ALL:
        case VOICE_56_REPLACE_ADD_FILTER_NO2_FOR_ALL:
        case VOICE_57_PRESS_DISPENSE_BUTTON_AFTER_WATER_VALVE_OPEN:
        case VOICE_58_PRESS_YES_OR_NO_AFTER_FAUCET:
        case VOICE_59_PRESS_YES_OR_NO_AFTER_FILTER_FAUCET:
        case VOICE_60_WAIT_ICE_TANK_CLEANING:
        case VOICE_61_START_SMART_TESTING_MODE:
        case VOICE_62_FINISH_SMART_TESTING_MODE_NO_ERROR:
        case VOICE_63_FINISH_SMART_TESTING_MODE_WITH_ERROR:
        case VOICE_64_INFORM_BLE_MODE_ACTIVATED:
        case VOICE_65_INFORM_BLE_MODE_DEACTIVATED:
        case VOICE_66_INFORM_WIFI_MODE_ACTIVATED:
        case VOICE_67_INFORM_WIFI_MODE_DEACTIVATED:
        case VOICE_68_INFORM_WIFI_ON:
        case VOICE_69_INFORM_WIFI_OFF:
        case VOICE_70_PRESS_BUTTON_ACCORDING_TO_APP_GUIDE:
        case VOICE_71_INFORM_APP_PAIRING_SUCCESS:
        case VOICE_72_INFORM_APP_PAIRING_FAIL:
        case VOICE_73_INFORM_APP_DISCONNECTED:
        case VOICE_74_INFORM_WIFI_OFF:
        case VOICE_75_PRESS_INSTALL_BUTTON:
        case VOICE_76_START_WIFI_AUTOMATIC_CONNECTION:
        case VOICE_77_WAIT_WATER_PIPE_DRAIN:
        case VOICE_78_DISCARD_FIRST_CUP:
        case VOICE_79_WATCHOUT_HOT_WATER_CUP:
        case VOICE_80_WATCHOUT_HOT_WATER_CONTINUOUS:
        case VOICE_81_SETTING_MODE_CLEAN_CARE:
        case VOICE_82_START_CLEAN_CARE_WATCHOUT_FAUCET:
        case VOICE_83_PRESS_BUTTON_MANUAL_CLEAN_CARE:
        case VOICE_84_START_CLEAN_CARE_WATCHOUT_HOT:
        case VOICE_85_FINISH_CLEAN_CARE:
        case VOICE_86_PRESS_BUTTON_MORE_SETTING_MODE:
        case VOICE_87_SETTING_MODE:
        case VOICE_88_CLOSE_FRONT_COVER:
        case VOICE_89_CLOSE_SIDE_COVER:
        case VOICE_90_CLOSE_TOP_COVER:
        case VOICE_91_CLOSE_FILTER_COVER:
        case VOICE_92_PRESS_BUTTON_HOT_LOCK_OFF:
        case VOICE_93_PRESS_SETTING_MODE_HOT_LOCK_OFF:
        case VOICE_94_PRESS_BUTTON_HOT_FUNCTION_ON:
        case VOICE_95_CHECK_SETTING_HOT_FUNCTION:
        case VOICE_96_CHECK_SETTING_COLD_FUNCTION:
        case VOICE_97_DISPENSE_ICE_WHILE_PRESS:
        case VOICE_98_INFORM_ICE_LOCK_ON:
        case VOICE_99_PRESS_BUTTON_ICE_FUNCTION_ON:
        case VOICE_100_SET_CLOCK_ECO_MODE:
        case VOICE_101_NO_GUARANTEE_ICE_ECO_MODE:
        case VOICE_102_PRESS_BUTTON_ALL_LOCK_OFF_A:
        case VOICE_103_PRESS_SETTING_MODE_ALL_LOCK_OFF:
        case VOICE_104_PRESS_BUTTON_ALL_LOCK_OFF_B:
        case VOICE_105_WAIT_CLEAN_CARE:
        case VOICE_106_SET_APP_AUTO_LOCK_OFF:
        case VOICE_107_NO_GUARANTEE_LOW_WATER:
        case VOICE_108_WAIT_LOW_WATER:
        case VOICE_109_INFORM_NOT_ENOUGH_HOT:
        case VOICE_110_INFORM_DISPENSE_NOT_ENOUGH_HOT:
        case VOICE_111_INFORM_NOT_ENOUGH_COLD:
        case VOICE_112_INFORM_HOT_LOCK_ON:
        case VOICE_113_INFORM_HOT_LOCK_OFF:
        case VOICE_114_SETTING_MODE_JOG_DAIL:
        case VOICE_115_SETTING_HOT_TANK_CONTROL_MODE:
        case VOICE_116_START_HEATING_HOT_TANK:
        case VOICE_117_START_CONTROL_HOT_TANK:
        case VOICE_118_INFORM_ENOUGH_HOT:
        case VOICE_119_INFORM_TOO_HIGH_HOT:
        case VOICE_120_SETTING_MODE_HOT_TANK:
        case VOICE_121_INFORM_HOT_FUNCTION_ON:
        case VOICE_122_INFORM_HOT_FUNCTION_OFF:
        case VOICE_123_SETTING_MODE_COLD_TANK:
        case VOICE_124_INFORM_COLD_FUNCTION_ON:
        case VOICE_125_INFORM_COLD_FUNCTION_OFF:
        case VOICE_126_SETTING_MODE_ALL_LOCK:
        case VOICE_127_INFORM_ALL_LOCK_ON:
        case VOICE_128_INFORM_ALL_LOCK_OFF:
        case VOICE_129_VOICE_MODE:
        case VOICE_130_MELODY_MODE:
        case VOICE_131_MUTE_MODE:
        case VOICE_132_SETTING_MODE_SOUND:
        case VOICE_133_MODE_SET_VOICE:
        case VOICE_134_MODE_SET_MELODY:
        case VOICE_135_MODE_SET_MUTE:
        case VOICE_136_MODE_SET_COLD_ON:
        case VOICE_137_MODE_SET_COLD_OFF:
        case VOICE_138_SETTING_MODE_CLEAN_CARE_TIME:
        case VOICE_139_MODE_SET_CLEAN_CARE_TIME:
        case VOICE_140_SETTING_MODE_DEFAULT_AMOUNT:
        case VOICE_141_MODE_SET_DEFAULT_AMOUNT:
        case VOICE_142_NOT_TIME_REPLACE_FILTER_YET:
        case VOICE_143_CHECK_TIME_REPLACE_FILTER:
        case VOICE_144_SETTING_MODE_CLOCK:
        case VOICE_145_MODE_SET_CLOCK:
        case VOICE_146_FINISH_SETTING:
        case VOICE_147_INFORM_ICE_LOCK_ON:
        case VOICE_148_INFORM_ICE_LOCK_OFF:
        case VOICE_149_INFORM_ICE_FUNCTION_ON:
        case VOICE_150_INFORM_ICE_FUNCTION_OFF:
        case VOICE_151_SPECIAL_FUNCTION:

        case VOICE_192_MELODY_DISPENSE_CONTINUOUS:
        case VOICE_193_MELODY_DISPENSE_START:
        case VOICE_194_MELODY_DISPENSE_FINISH:
        case VOICE_195_MELODY_PLUG_IN:
        case VOICE_196_MELODY_SELECT:
        case VOICE_197_MELODY_WARNING:
        case VOICE_198_MELODY_SET_ON:
        case VOICE_199_MELODY_SET_OFF:



            return TRUE;

        default :
            return FALSE;
    }

    return FALSE;
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 IsCriticalVoice(U16 addr)
{
    switch( addr )
    {
        return TRUE;

        default :
            return FALSE;
    }

    return FALSE;
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

