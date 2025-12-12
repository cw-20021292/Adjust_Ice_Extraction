
#include "WIFI_Config.h"

/******************************************************************************/
/***** User Header ************************************************************/
/******************************************************************************/
/* Start user code for include (User heders). */
/******************************************************************************/
// #include "Voice_NXD1005.h"
#include "macrodriver.h"
#include "Global_Variable.h"
#include "Port_Define.h"
/******************************************************************************/
extern bit F_Wifi_Power;
extern bit F_Wifi_First_Paring;
extern bit F_Wifi_Fota_MODULE;
extern bit F_Wifi_Fota_MCU;

extern bit F_ExtractKeySet;
extern bit F_WaterOut;
extern bit bit_self_test_start;
extern bit F_Tank_Cover_Input;
extern bit bit_self_test_start;

extern bit bit_ice_tank_ster_start;
extern bit bit_filter_all;
extern FLUSHING_STEP gu8_flushing_mode;
extern bit F_First_Hot_Effluent;
extern void play_melody_setting_on_198(void);
extern void Play_Voice(U16 mu16MemoryAddress);
extern void get_wifi_time ( U16 mYear, U16 mMonth, U16 mDate, U16 mHour, U16 mMin, U16 mSec );
extern void start_fota(void);

extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2

/******************************************************************************/

/* End user code.*/


/******************************************************************************/
/***** EEPROM Setting *********************************************************/
/******************************************************************************/
/* User eeprom write settings */
void UserWriteEep ( U16 mu16Addr, U8 mu8Val )
{
    if(u8FactoryTestMode != NONE_TEST_MODE)
    {
        return;
    }
    else{}

    if( mu16Addr == EEPROM_ADDR_WIFI_POWER )
    {
        /* Start user code.*/

        // Ex)
        // WiFi.mUonOff = mu8Val;
        F_Wifi_Power = mu8Val;

        /* End user code. */
    }
    else if( mu16Addr == EEPROM_ADDR_FIRST_PARING )
    {
        /* Start user code.*/

        // WiFi.mUfirstParing = mu8Val;
        F_Wifi_First_Paring = mu8Val;

        /* End user code. */
    }
    else if( mu16Addr == EEPROM_ADDR_FOTA_MODULE )
    {
        /* Start user code.*/

        // WiFi.mUfotaModule = mu8Val;
        F_Wifi_Fota_MODULE = mu8Val;

        /* End user code. */
    }
    else if( mu16Addr == EEPROM_ADDR_FOTA_MCU )
    {
        /* Start user code.*/

        // WiFi.mUfotaMain = mu8Val;
        F_Wifi_Fota_MCU = mu8Val;

        /* End user code. */
    }
}

/* User eeprom read settings */
U8 UserReadEep ( U16 mu16Addr )
{
    U8 mu8Data = 0U;

    if( mu16Addr == EEPROM_ADDR_WIFI_POWER )
    {
        /* Start user code.*/

        // return WiFi.mUonOff;
        // mu8Data = WiFi.mUonOff;
        mu8Data = (U8)F_Wifi_Power;

        /* End user code. */
    }
    else if( mu16Addr == EEPROM_ADDR_FIRST_PARING )
    {
        /* Start user code.*/

        // return WiFi.mUfirstParing;
        mu8Data = (U8)F_Wifi_First_Paring;

        /* End user code. */
    }
    else if( mu16Addr == EEPROM_ADDR_FOTA_MODULE )
    {
        /* Start user code.*/

        // return WiFi.mUfotaModule;
        mu8Data = (U8)F_Wifi_Fota_MODULE;

        /* End user code. */
    }
    else if( mu16Addr == EEPROM_ADDR_FOTA_MCU )
    {
        /* Start user code.*/

        // return WiFi.mUfotaMain;
        mu8Data = (U8)F_Wifi_Fota_MCU;

        /* End user code. */
    }

    return mu8Data;
}
/* User buzzsound/voice settings */

void UserBuzzSound ( U16 mu16Buzz )
{
    U16 Sound = 0;
    switch( mu16Buzz )
    {
        case WIFI_BUZZER_SELECT :       // 페어링 (선택음 "띵")
            /* Start user code.*/
            // ex) Sound = 1196;
            Play_Voice(VOICE_196_MELODY_SELECT);

            /* End user code. */
            break;

        case WIFI_BUZZER_AP_CONNECT :   // AP연결 (진입음 "띠리링" / Wi-Fi 연결모드가 활성화 되었습니다.)
            /* Start user code.*/
            // ex) Sound = 1001;
            Play_Voice(VOICE_23_INFORM_APP_PAIRING_SUCCESS_WITH_WIFI);

            /* End user code. */
            break;

        case WIFI_BUZZER_BLE_CONNECT :  // AP연결 (진입음 "띠리링" / BLE연결모드가 활성화 되었습니다.)
            /* Start user code.*/
            // ex) Sound = 1001;
            Play_Voice(VOICE_19_START_BLE_PAIRNG);

            /* End user code. */
            break;

        case WIFI_BUZZER_SETUP :        // WIFI ON (설정음 "띵동↗" / 제품의 Wi-Fi가 켜졌습니다.)
            /* Start user code.*/
            // ex) Sound = 1198;
            Play_Voice(VOICE_27_INFORM_WIFI_ON);

            /* End user code. */
            break;

        case WIFI_BUZZER_SERVER_CONNECT :   // 서버연결 (연결음 "띠리링↗" / 제품과 앱이 성공적으로 연결되었습니다.)
            /* Start user code.*/
            // ex) Sound = 0xFFFF;
            Play_Voice(VOICE_23_INFORM_APP_PAIRING_SUCCESS_WITH_WIFI);

            /* End user code. */
            break;

        case WIFI_BUZZER_CANCEL :           // WIFI OFF (해제음 "동띵" / 제품의 Wi-Fi가 꺼졌습니다.)
            /* Start user code.*/
            // ex) Sound = 1199;
            Play_Voice(VOICE_28_INFORM_WIFI_OFF);

            /* End user code. */
            break;

        case WIFI_BUZZER_AP_START :         // AP시작음 (설정음 "띵동 ↗")
            /* Start user code.*/
            // ex) Sound = 1198;
            Play_Voice(VOICE_198_MELODY_SET_ON);

            /* End user code. */
            break;

        case WIFI_BUZZER_ERROR :            // 불가음 (에러음 "띵깡띵깡")
            /* Start user code.*/
            // ex) Sound = 1197;
            Play_Voice(VOICE_197_MELODY_WARNING);

            /* End user code. */
            break;

        case WIFI_BUZZER_WiFi_OFF :         // Wi-Fi 페어링 해제음(동띵) / Wi-Fi 연결 모드가 비활성화 되었습니다.
            /* Start user code.*/
            // ex) Sound = 1199;
            Play_Voice(VOICE_25_INFORM_WIFI_MODE_DEACTIVATED);

            /* End user code. */
            break;

        case WIFI_BUZZER_BLE_OFF :          // 블루투스 페어링 해제음(동띵) / 블루투스 연결 모드가 비활성화 되었습니다.
            /* Start user code.*/
            // ex) Sound = 1199;
            Play_Voice(VOICE_21_INFORM_APP_PAIRING_FAIL_WITH_BLE);

            /* End user code. */
            break;

        case WIFI_BUZZER_BLE_CERT :         // (선택음 "띵") / 블루투스 점유인증 활성화 상태 / 제품인증을 진행 중입니다. 앱에서 가이드하는 버튼을 눌러주세요.
            /* Start user code.*/
            // ex) Sound = 1196;
            Play_Voice(VOICE_29_APPLY_PRODUCT_CERT_OCCUPATION);

            /* End user code. */
            break;

        case WIFI_BUZZER_SERVER_FIRST :     // 페어링 완료 후 서버연결 (연결음 "띠리링↗" / 제품과 앱이 성공적으로 연결되었습니다.
            /* Start user code.*/
            // ex) Sound = 0xFFFF;
            Play_Voice(VOICE_30_INFORM_APP_PAIRING_SUCCESS_WITH_WIFI);

            /* End user code. */
            break;

        case WIFI_BUZZER_SMART_CHECK_OK :       // (설정음 "띵동 ↗") / 스마트 진단이 완료 되어 제품을 사용하실 수 있습니다.
            /* Start user code.*/
            // ex) Sound = 1198;
            Play_Voice(VOICE_17_FINISH_SMART_TESTING_MODE_NO_ERROR);

            /* End user code. */
            break;

        case WIFI_BUZZER_SMART_CHECK_ERROR :    // 불가음 (에러음 "띵깡띵깡") / 스마트 진단이 완료 되었습니다.
            /* Start user code.*/
            // ex) Sound = 1197;
            Play_Voice(VOICE_18_FINISH_SMART_TESTING_MODE_WITH_ERROR);

            /* End user code. */
            break;

        default :
            break;
    }

    if (Sound != 0xFFFFU)
	{
        /* Start user code.*/

		// Ex) Play_Voice(Sound);

        /* End user code. */
	}
}

/* Time Setting Option (When using A2010 Time) - Called when time data is received*/
void SetUserSystemTime ( U16 mYear, U16 mMonth, U16 mDate, U16 mHour, U16 mMin, U16 mSec, U16 mDay )
{   /* Start user code.*/
    /* 와이파이 시간 데이터 업데이트 */
    get_wifi_time( mYear, mMonth, mDate, mHour, mMin, mSec);


}   /* End user code. */


/* User FOTA Display Setting */
void SetUserSystemDisplay ( U8 mu8Display )
{
    if ( mu8Display == USER_DISPLAY_FOTA ) // FOTA
    {
        /* Start user code.*/
        start_fota();
        /* End user code. */
    }
}

/* Product Status Information Settings */
void SetUserSystemStatusData ( U8 mu8StatusType )
{
    switch ( mu8StatusType )
    {
        case USER_MODEL_TYPE:   // 모델 타입 설정
        /*
            SetUserSystemStatus(mu8StatusType, 0U);       // e.g. CHP
            SetUserSystemStatus(USER_MODEL_TYPE, 1U);    // e.g. CP
        */
        SetUserSystemStatus(mu8StatusType, 0U); // CHPI (Model 0)

        break;

        case USER_FACTORY_STATUS:       // Wi-Fi 검사모드 진입 설정
        /*
            SetUserSystemStatus(mu8StatusType, 0U);       // e.g. 검사모드 아님
            SetUserSystemStatus(mu8StatusType, 1U);       // e.g. 검사모드 진입
        */

        break;

        case USER_RX_STATUS:    // 일반제어 불가상태 설정
        /*
            SetUserSystemStatus(mu8StatusType, 0U);       // e.g. 제어가능
            SetUserSystemStatus(mu8StatusType, 1U);       // e.g. 제어불가
        */

        if((F_ExtractKeySet == SET)
        || (bit_ice_tank_ster_start == SET)
        || (F_WaterOut == SET)
        || (bit_self_test_start == SET)
        || (F_Tank_Cover_Input == CLEAR)
        || (Bit1_Uart_Test_Mode == SET)
        || (Bit0_Pcb_Test_Mode == SET)
        || (bit_filter_all == CLEAR)
        )
        {
            SetUserSystemStatus(mu8StatusType, 1U);     // 불가
        }
        else
        {
            SetUserSystemStatus(mu8StatusType, 0U);     // 가능
        }
        break;

        case USER_SMART_POSSIBLE_STATUS:    // 스마트진단 불가상태 설정
        /*
            SetUserSystemStatus(mu8StatusType, 0U);       // e.g. 진단가능
            SetUserSystemStatus(mu8StatusType, 1U);       // e.g. 진단불가
        */

        if((F_ExtractKeySet == SET)
        || (bit_ice_tank_ster_start == SET)
        || (F_WaterOut == SET)
        || (F_Tank_Cover_Input == CLEAR)
        || (Bit1_Uart_Test_Mode == SET)
        || (Bit0_Pcb_Test_Mode == SET)
        || (bit_filter_all == CLEAR)
        || (F_First_Hot_Effluent == SET)        // 히터에 물이 채워진 상태일 때에만 가능 물없으면 안됨 (플러싱 스킵도 안됨)
        )
        {
            SetUserSystemStatus(mu8StatusType, 1U);
        }
        else
        {
            SetUserSystemStatus(mu8StatusType, 0U);
        }

        break;

        case USER_FOTA_POSSIBLE_STATUS:     // FOTA 불가 상태 설정
        /*
            SetUserSystemStatus(mu8StatusType, 0U);       // e.g. FOTA가능
            SetUserSystemStatus(mu8StatusType, 1U);       // e.g. FOTA불가
        */

        if ((F_ExtractKeySet == SET)
        || (bit_ice_tank_ster_start == SET)
        || (F_WaterOut == SET)
        )
        {
            SetUserSystemStatus(mu8StatusType, 1U);
        }
        else
        {
            SetUserSystemStatus(mu8StatusType, 0U);
        }

        break;

        case USER_SMART_SENSING_STATUS:     // 스마트진단 중 상태 설정
        /*
            SetUserSystemStatus(mu8StatusType, 0U);       // e.g. 일반 상태 (스마트진단 중 상태 아님)
            SetUserSystemStatus(mu8StatusType, 1U);       // e.g. 스마트 진단 진행 중
        */

        if ((bit_self_test_start == SET))
        {
            SetUserSystemStatus(mu8StatusType, 1U);
        }
        else
        {
            SetUserSystemStatus(mu8StatusType, 0U);
        }
        break;

        case USER_FACTORY_DIRECTFOTA_STATUS:    // 다이렉트 포타 진입 설정
        /*
            SetUserSystemStatus(mu8StatusType, 0U);       // e.g. 다이렉트 FOTA 모드 아님
            SetUserSystemStatus(mu8StatusType, 1U);       // e.g. 다이렉트 FOTA 모드
        */
        default:

        break;
    }

}
