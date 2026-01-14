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
#include    "motor_ice_select.h"
#include    "model_select.h"
#include    "extract_control.h"

void motor_ice_select_output(void);
void iceSelectMotor_Control(U16 gu16_p_step);
void IceStuckProcess(void);

bit F_SelectCW;                    // 살균 후 ICE Door Reset
U16 gu16_IceSelect_StepMotor;

U16 gu16IceSelectDoorCloseTimer_Min = 0; /* 60s x 60min x 24h = 86400 24Hour */
U16 gu16IceSelectDoorCloseTimer_Hour = 0; /* 60s x 60min x 24h = 86400 24Hour */
U16 gu16IceSelectDoorCloseResetTimer = 0;
bit F_IceSelectDoorClose;        /* 아이스 도어 닫힘 */

bit F_IceSelect;

bit F_IceSelectClose;           /* 조각얼음 이너도어 강제닫힘 동작플래그 */

extern MODEL model;
extern bit bit_ice_stuck_back_state;
extern bit bit_ice_out_back_1s_state;
extern bit bit_ice_out_back_state;
extern U16 gu16_Ice_Door_StepMotor;
extern void Play_Voice(U16 mu16MemoryAddress);

extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2

// [2025-11-17] CH.PARK 얼음걸림 제어를 위한 구조체 추가
ICE_STUCK_1 IceStuck;
ICE_DOOR_REED IceDoorReed;
U16 gu16DoorOpenPulse = 0;
U16 u16OpenTimming = 0;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : StepMotor
// 개요       : 스텝모터 구동 Door 3msec cycle
//----------------------------------------------------------------------------
// 기능       :
//              ICE Door 열림 닫힘
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
void motor_ice_select_output(void)
{
    /* 2025-10-13 CH.PARK 조각얼음 추출 시작 시 100% 밀 때는 최우선 순위로 동작시키고 이후 동작하도록 수정 (사양충돌 개선) */
    if(F_IceSelectClose == SET)
    {
        if(gu16_IceSelect_StepMotor > 0)
        {
            /* 이너도어 CLOSE 지연 시간 적용 */
            if(gu8IceInnerClose == 0)
            {
                gu16_IceSelect_StepMotor--;
            }
            else{}
        }
        else
        {
            gu16_IceSelect_StepMotor = 0;

            pSTEP_MOTOR_ICE_SELECT_1 = 0;
            pSTEP_MOTOR_ICE_SELECT_2 = 0;
            pSTEP_MOTOR_ICE_SELECT_3 = 0;
            pSTEP_MOTOR_ICE_SELECT_4 = 0;

            F_IceSelectClose = CLEAR;
        }

        iceSelectMotor_Control(gu16_IceSelect_StepMotor);
        return;
    }

    if(F_IceSelect == SET)                                       // 열림
    {
        if(F_SelectCW != SET)
        {
            F_SelectCW = SET;
        }
        else{}

        if(GetIceFrontPercent() >= 0.3)
        {
            // 1단계 열림
            if(gu16_IceSelect_StepMotor < INNER_DOOR_OPEN_1_STEP)
            {
                gu16_IceSelect_StepMotor++;
                u16OpenTimming = 667;         // 3ms 베이스임 2초 대기
            }
            else if(gu16_IceSelect_StepMotor < STEP_ANGLE_SELECT)
            {
                if(u16OpenTimming > 0)
                {
                    u16OpenTimming--;
                    return;
                }

                gu16_IceSelect_StepMotor++;
            }
            else
            {
                gu16_IceSelect_StepMotor = STEP_ANGLE_SELECT;

                pSTEP_MOTOR_ICE_SELECT_1 = 0;
                pSTEP_MOTOR_ICE_SELECT_2 = 0;
                pSTEP_MOTOR_ICE_SELECT_3 = 0;
                pSTEP_MOTOR_ICE_SELECT_4 = 0;

                /* 얼음 추출중이 아니고 얼음 걸림 제어도 안하고 있을 때에만 클리어 */
                if((F_IceOut == CLEAR)
                && (IceStuck.u8IceJamResolveStep == PROCESS_ICE_JAM_INIT)
                )
                {
                    F_IceSelect = CLEAR;              // Door 열림 완료 후 Off
                }
                else{}
            }
        }
        else
        {
            // 기존처럼 그냥 Full Open
            if(gu16_IceSelect_StepMotor < STEP_ANGLE_SELECT)
            {
                gu16_IceSelect_StepMotor++;
            }
            else
            {
                gu16_IceSelect_StepMotor = STEP_ANGLE_SELECT;

                pSTEP_MOTOR_ICE_SELECT_1 = 0;
                pSTEP_MOTOR_ICE_SELECT_2 = 0;
                pSTEP_MOTOR_ICE_SELECT_3 = 0;
                pSTEP_MOTOR_ICE_SELECT_4 = 0;

                /* 얼음 추출중이 아니고 얼음 걸림 제어도 안하고 있을 때에만 클리어 */
                if((F_IceOut == CLEAR)
                && (IceStuck.u8IceJamResolveStep == PROCESS_ICE_JAM_INIT)
                )
                {
                    F_IceSelect = CLEAR;              // Door 열림 완료 후 Off
                }
                else{}
            }
        }


    }
    else                                                  // 닫힘
    {
        if(F_SelectCW == SET)
        {
            gu16_IceSelect_StepMotor = STEP_ANGLE_SELECT;
            F_SelectCW = 0;
        }
        else{}

        if(gu16_IceSelect_StepMotor > 0)
        {
            /* 이너도어 CLOSE 지연 시간 적용 */
            if(gu8IceInnerClose == 0)
            {
                gu16_IceSelect_StepMotor--;
            }
            else{}
        }
        else
        {
            gu16_IceSelect_StepMotor = 0;

            pSTEP_MOTOR_ICE_SELECT_1 = 0;
            pSTEP_MOTOR_ICE_SELECT_2 = 0;
            pSTEP_MOTOR_ICE_SELECT_3 = 0;
            pSTEP_MOTOR_ICE_SELECT_4 = 0;
        }
    }

    iceSelectMotor_Control(gu16_IceSelect_StepMotor);
    /* 2025-10-28 CH.PARK 얼음 걸림 해제 제어사양 적용 */
    IceStuckProcess();
}

void iceSelectMotor_Control(U16 gu16_p_step)
{
    if(gu16_p_step == 0 || gu16_p_step == STEP_ANGLE_SELECT)
    {
        pSTEP_MOTOR_ICE_SELECT_1 = 0;
        pSTEP_MOTOR_ICE_SELECT_2 = 0;
        pSTEP_MOTOR_ICE_SELECT_3 = 0;
        pSTEP_MOTOR_ICE_SELECT_4 = 0;
    }
    else
    {
        switch(gu16_p_step % 8)
        {
            case 0 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 1;
                    pSTEP_MOTOR_ICE_SELECT_2 = 0;
                    pSTEP_MOTOR_ICE_SELECT_3 = 0;
                    pSTEP_MOTOR_ICE_SELECT_4 = 0;

                    break;

            case 1 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 1;
                    pSTEP_MOTOR_ICE_SELECT_2 = 0;
                    pSTEP_MOTOR_ICE_SELECT_3 = 0;
                    pSTEP_MOTOR_ICE_SELECT_4 = 1;

                    break;

            case 2 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 0;
                    pSTEP_MOTOR_ICE_SELECT_2 = 0;
                    pSTEP_MOTOR_ICE_SELECT_3 = 0;
                    pSTEP_MOTOR_ICE_SELECT_4 = 1;

                    break;

            case 3 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 0;
                    pSTEP_MOTOR_ICE_SELECT_2 = 0;
                    pSTEP_MOTOR_ICE_SELECT_3 = 1;
                    pSTEP_MOTOR_ICE_SELECT_4 = 1;

                    break;

            case 4 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 0;
                    pSTEP_MOTOR_ICE_SELECT_2 = 0;
                    pSTEP_MOTOR_ICE_SELECT_3 = 1;
                    pSTEP_MOTOR_ICE_SELECT_4 = 0;

                    break;

            case 5 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 0;
                    pSTEP_MOTOR_ICE_SELECT_2 = 1;
                    pSTEP_MOTOR_ICE_SELECT_3 = 1;
                    pSTEP_MOTOR_ICE_SELECT_4 = 0;

                    break;

            case 6 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 0;
                    pSTEP_MOTOR_ICE_SELECT_2 = 1;
                    pSTEP_MOTOR_ICE_SELECT_3 = 0;
                    pSTEP_MOTOR_ICE_SELECT_4 = 0;

                    break;

            case 7 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 1;
                    pSTEP_MOTOR_ICE_SELECT_2 = 1;
                    pSTEP_MOTOR_ICE_SELECT_3 = 0;
                    pSTEP_MOTOR_ICE_SELECT_4 = 0;

                    break;

            default:

                break;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_select_door_close_24_hour(void)
{
    U16 mu16_forced_close_time_min = 0;
    U16 mu16_forced_close_time_hour = 0;
    U8 mu8_return = 0;

    //====================================================
    /* 아이스 도어 주기적으로 닫는 로직( 24시간 기준으로 반복 )
     * 아이스 도어가 강제로 열린 경우를 가정해서 24시간 기준으로 닫아 준다.*/

    if( F_LineTest == SET )
    {
        /*..hui [18-1-23오후 2:29:46] 테스트 모드시 60초..*/
        mu16_forced_close_time_min = 600;
        /*..hui [18-1-23오후 2:29:52] 테스트 모드시 1분..*/
        mu16_forced_close_time_hour = 5;
    }
    else
    {
        /*..hui [18-1-23오후 2:29:03] 일반 모드시 60분..*/
        mu16_forced_close_time_min = 36000;
        /*..hui [18-1-23오후 2:29:09] 일반 모드시 24시간..*/
        mu16_forced_close_time_hour = 24;
    }

    mu8_return = finish_ice_setting();

    if( mu8_return == SET )
    {
        F_IceSelectDoorClose = SET;
    }
    else{}

    if( F_IceOut == SET )
    {
        gu16IceSelectDoorCloseTimer_Min = 0;
        gu16IceSelectDoorCloseTimer_Hour = 0;
    }
    else{}

    /*..hui [18-1-23오후 2:12:10] 60분 타이머..*/
    gu16IceSelectDoorCloseTimer_Min++;

    if(gu16IceSelectDoorCloseTimer_Min >= mu16_forced_close_time_min)
    {
        gu16IceSelectDoorCloseTimer_Min = 0;
        gu16IceSelectDoorCloseTimer_Hour++;
    }
    else{}

    /*..hui [18-1-23오후 2:12:15] 24시간 타이머..*/
    if(gu16IceSelectDoorCloseTimer_Hour >= mu16_forced_close_time_hour)
    {
        F_IceSelectDoorClose = SET;
        gu16IceSelectDoorCloseTimer_Hour = 0;
    }
    else{}

    if( F_IceSelectDoorClose == SET )
    {
        F_IceSelectDoorClose = CLEAR;

        gu16IceSelectDoorCloseTimer_Min = 0;
        gu16IceSelectDoorCloseTimer_Hour = 0;

        gu16IceSelectDoorCloseResetTimer = 70;
        gu16_IceSelect_StepMotor = STEP_ANGLE_SELECT;
    }
    else{}

    /*..hui [18-1-23오후 2:44:04] 아이스도어 강제 CLOSE중에 얼음 추출할경우 FULL OPEN..*/
    if(gu16IceSelectDoorCloseResetTimer > 0)
    {
        gu16IceSelectDoorCloseResetTimer--;
    }
    else{}
}

/***********************************************************************************************************************/
/**
 * @brief 얼음 걸림 제어 관련 변수 초기화
 *
 */
void IceStuckInit(void)
{
    IceStuck.u8IceJamCheck = CLEAR;
    IceStuck.u8IceJamResolveStep = PROCESS_ICE_JAM_INIT;
    IceStuck.u8IceJamProcessTimer = 0;
    IceStuck.u8IceJamProcessCount = 0;
}

/***********************************************************************************************************************/
/**
 * @brief 얼음걸림 동작 시퀀스 모드 설정
 *
 * @param mu8_ice_jam_resolve_step
 */
void SetIceStuckStatus(ICE_JAM_RESV_STEP mu8_ice_jam_resolve_step)
{
    IceStuck.u8IceJamResolveStep = mu8_ice_jam_resolve_step;
}

/***********************************************************************************************************************/
/**
 * @brief 리드 스위치 추가된 모델의 얼음 걸림 동작
 *
 */
void IceStuckProcess(void)
{
    // [2025-11-17] CH.PARK 검사모드 시 얼음걸림 제어 미가동
    if( u8FactoryTestMode != NONE_TEST_MODE)
    {
        IceStuckInit();
        return;
    }

    /* 2025-10-28 CH.PARK 모델 판단 미완료 시 */
    if(model.u8IsModelChecked == CLEAR)
    {
        IceStuckInit();
        return;
    }

    /* 2025-10-28 CH.PARK 리드스위치 사용안하는 모델(기존모델)일 시 */
    if(model.u8model != MODEL_REED_USE)
    {
        IceStuckInit();
        return;
    }

    /* 2025-10-28 CH.PARK 얼음 추출중일 시 얼음 걸림 동작 미가동 및 데이터 초기화 */
    if(F_IceOut == SET)
    {
        IceStuckInit();
        return;
    }

    // 얼음걸림 상황 발생
    if(IceStuck.u8IceJamCheck == SET)
    {
        if(gu16_IceSelect_StepMotor == 0)
        {
            /* 2025-10-28 CH.PARK 닫았지만 감지 안됐으면 즉시 얼음 걸림 해제동작 수행 */
            if(GET_INNER_DOOR_REED_SW() == ACTIVE_LOW_NO_DETECTED)
            {
                SetIceStuckStatus(PROCESS_ICE_JAM_DOOR_OPEN);
            }
            else
            {
                SetIceStuckStatus(PROCESS_ICE_JAM_INIT);
            }

            IceStuck.u8IceJamCheck = CLEAR;
            IceStuck.u8IceJamProcessTimer = 0;
        }
    }

    IceStuck.u8IceJamProcessTimer++;
    if(IceStuck.u8IceJamProcessTimer >= ICE_JAM_PROCESS_TIME_MAX)      // 1초 마다
    {
        IceStuck.u8IceJamProcessTimer = 0;
        switch (IceStuck.u8IceJamResolveStep)
        {
            case PROCESS_ICE_JAM_INIT:
                // 대기
                break;

            case PROCESS_ICE_JAM_DOOR_OPEN:
                if(IceStuck.u8IceJamProcessCount < ICE_JAM_RESV_COUNT_MAX)
                {
                    IceStuck.u8IceJamProcessCount++;
                }

                // 이너도어 OPEN
                F_IceSelect = SET;
                F_IceOpen = SET;

                /* 두 도어 모두 이동 완료 시 FEEDER 제어 */
                if((gu16_IceSelect_StepMotor == STEP_ANGLE_SELECT)
                && (gu16_Ice_Door_StepMotor == STEP_ANGLE_DOOR)
                )
                {
                    SetIceStuckStatus(PROCESS_ICE_JAM_FEEDER_BACK);
                }
                break;

            case PROCESS_ICE_JAM_FEEDER_BACK:
                // 이너도어 OPEN
                F_IceSelect = SET;
                F_IceOpen = SET;

                // 피더 2초 역회전 (나머지 추출 역회전은 수행 취소)
                bit_ice_stuck_back_state = SET;
                bit_ice_out_back_1s_state = CLEAR;
                bit_ice_out_back_state = CLEAR;

                SetIceStuckStatus(PROCESS_ICE_JAM_FEEDER_CHECK);
                break;

            case PROCESS_ICE_JAM_FEEDER_CHECK:
                // 이너도어 CLOSE
                F_IceSelect = SET;
                F_IceOpen = SET;

                /* 역회전제어 완료 시 */
                if(bit_ice_stuck_back_state == CLEAR)
                {
                    SetIceStuckStatus(PROCESS_ICE_JAM_DOOR_CLOSE);
                }
                break;

            case PROCESS_ICE_JAM_DOOR_CLOSE:
                F_IceSelect = CLEAR;
                F_IceOpen = SET;

                SetIceStuckStatus(PROCESS_ICE_JAM_DOOR_CLOSE_CHECK);

                break;

            case PROCESS_ICE_JAM_DOOR_CLOSE_CHECK:
                if(gu16_IceSelect_StepMotor == 0)
                {
                    /* 2025-10-28 CH.PARK 최대 1회 얼음 걸림 해제 동작 넘을 시 그냥 동작 해제 */
                    /* 2025-10-29 CH.PARK 확장성을 생각해서 그냥 횟수만 단발성 1회로 수정 */
                    if(IceStuck.u8IceJamProcessCount >= ICE_JAM_RESV_COUNT_MAX)
                    {
                        /* LOW : 감지 */
                        if(GET_INNER_DOOR_REED_SW() == ACTIVE_LOW_DETECTED)
                        {
                            // IceDoor ClOSE
                            SetIceStuckStatus(PROCESS_ICE_JAM_DONE);
                        }
                        else
                        {
                            // 미감지 시 음성안내 후 해제 제어 종료
                            SetIceStuckStatus(PROCESS_ICE_JAM_ERROR);
                        }
                    }
                    else
                    {
                        /* LOW : 감지 */
                        if(GET_INNER_DOOR_REED_SW() == ACTIVE_LOW_DETECTED)
                        {
                            // IceDoor ClOSE
                            SetIceStuckStatus(PROCESS_ICE_JAM_DONE);
                        }
                        else
                        {
                            // 미감지 시 처음부터 다시
                            SetIceStuckStatus(PROCESS_ICE_JAM_DOOR_OPEN);
                        }
                    }
                }
                break;

            case PROCESS_ICE_JAM_DONE:
                SetIceStuckStatus(PROCESS_ICE_JAM_INIT);

                /* 2025-10-28 CH.PARK 걸림 해제 완료 시 아이스도어 닫음 */
                F_IceOpen = CLEAR;
                break;

            case PROCESS_ICE_JAM_ERROR:
                SetIceStuckStatus(PROCESS_ICE_JAM_VOICE_INFO_PLAY);

                /* 2025-10-28 CH.PARK 걸림 해제 완료 시 아이스도어 닫음 */
                F_IceOpen = CLEAR;
                break;

            case PROCESS_ICE_JAM_VOICE_INFO_PLAY:       // [2025-11-17] CH.PARK 얼음걸림 해제 안내음성 안내
                /* [2025-11-17] CH.PARK 아이스도어 닫힘 시 음성안내 송출 */
                if(gu16_Ice_Door_StepMotor == CLEAR)
                {
                    // 얼음걸림 해제 안내음성 안내
                    SetIceStuckStatus(PROCESS_ICE_JAM_INIT);

                    // 부팅 후 최대 2회까지만 음성안내 송출
                    if(IceStuck.u8IceJamVoicePlayCount < ICE_JAM_VOICE_INFO_PLAY_COUNT_MAX)
                    {
                        Play_Voice(VOICE_1365_ICE_STUCK_DETECTED);
                        IceStuck.u8IceJamVoicePlayCount++;
                    }
                }
                break;


            default:
                SetIceStuckStatus(PROCESS_ICE_JAM_INIT);
                break;
        }
    }
}

/***********************************************************************************************************************/
/**
 * @brief 아이스도어 리드 상태 초기화
 *
 */
 void IceDoorReedInit(void)
 {
    IceDoorReed.u8IceDoorPreStatus = ACTIVE_LOW_NO_DETECTED;
    IceDoorReed.u8IceDoorCurStatus = ACTIVE_LOW_NO_DETECTED;
    IceDoorReed.u8IceDoorInputTimer = 0;
    IceDoorReed.u8IceDoorStatus = CLEAR;
 }

/***********************************************************************************************************************/
/**
 * @brief 얼음문 리드 상태 조회 (1초이상 미감지/감지 시 확정)
 *
 * @return U8
 */
void CheckIceDoorReedStatus(void)
{
    /* 2025-10-28 CH.PARK 리드스위치 사용안하는 모델(기존모델)일 시 */
    if(GetModel() != MODEL_REED_USE)
    {
        return;
    }

    IceDoorReed.u8IceDoorCurStatus = GET_INNER_DOOR_REED_SW();

    if(IceDoorReed.u8IceDoorPreStatus != IceDoorReed.u8IceDoorCurStatus)
    {
        IceDoorReed.u8IceDoorPreStatus = IceDoorReed.u8IceDoorCurStatus;
        IceDoorReed.u8IceDoorInputTimer = 0;
    }
    else
    {
        IceDoorReed.u8IceDoorInputTimer++;
        if(IceDoorReed.u8IceDoorInputTimer >= ICE_DOOR_REED_INPUT_TIME_MAX)
        {
            IceDoorReed.u8IceDoorInputTimer = ICE_DOOR_REED_INPUT_TIME_MAX;

            if(IceDoorReed.u8IceDoorCurStatus == ACTIVE_LOW_DETECTED)
            {
                SetIceDoorReedStatus(REED_DETECTED);
            }
            else
            {
                SetIceDoorReedStatus(REED_NO_DETECTED);
            }
        }
    }
}

/***********************************************************************************************************************/
/**
 * @brief 아이스도어 리드 상태 설정
 *
 * @param mu8_reed_status
 */
void SetIceDoorReedStatus(REED_INFO mu8_reed_status)
{
    IceDoorReed.u8IceDoorStatus = mu8_reed_status;
}

/***********************************************************************************************************************/
/**
 * @brief 아이스도어 리드 상태 리턴
 *
 * @return REED_INFO
 */
REED_INFO GetIceDoorReedStatus(void)
{
    return IceDoorReed.u8IceDoorStatus;
}

/**
 * @brief 얼음걸림 음성안내 횟수 카운트 초기화
 *
 */
void IceJamVoicePlayCountInit(void)
{
    IceStuck.u8IceJamVoicePlayCount = 0;
}
