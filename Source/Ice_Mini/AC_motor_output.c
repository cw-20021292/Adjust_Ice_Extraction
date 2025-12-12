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
#include    "AC_motor_output.h"

void output_ac_motor(void);
void check_error_micro_sw_detect_at_once(void);
void check_error_micro_sw_movement(void);
void output_ice_feeder_motor(void);
void output_ice_tray_motor(void);
void check_error_tray_motor_up_operation(void);
void check_error_tray_motor_down_retry_operation(void);
void ice_make_system_up_move_reset(void);
void ice_make_system_down_move_reset(void);

void over_ice_making_check(void);
void over_ice_making_melt_proc(void);
void ice_system_reset(void);
void ice_stuck_reset(void);
void ice_system_stop(void);

void inverse_direction_time_check(void);
void reset_micro_sw_move_err_check_state(void);
void down_tray_motor(void);
void up_tray_motor(void);
void stop_tray_motor(void);
void check_ice_system_ok(void);

////

//----------------------------------------------------// Motor
U8 gu8Reverse;
U8 gu8TrayCWInterval;
U8 gu8TrayCCWInterval;
U8 gu8DualTrayStep;
U8 gu8DualTrayCheckCNT;
U16 gu16DualCheckDelay;
U8 gu8_Err_Tray_Up_Count;
U8 gu8_Err_Tray_Down_Count;

/*..hui [19-12-13오후 7:12:16] 트레이 탈빙 이동 누적 에러 카운트..*/
U8 gu8_err_tray_down_acc_count;


U8 gu8_Tray_Interval_Timer;


U8 gu8_Tray_CW_Interval_Timer;
bit F_Tray_CW_delay_finish;




U8 gu8_Tray_CCW_Interval_Timer;
bit F_Tray_CCW_delay_finish;


U8 u8_Tray_up_moving_retry_timer;


U16 gu16_Tray_down_moving_retry_timer;




U8 u8Trayretry1;


bit F_ErrTrayMotor_DualInital;
U16 gu16ErrTrayMotor;


U16 gu16_Err_Tray_Motor_Down_Total_Tmr;
U16 gu16_Err_Tray_Motor_Up_Total_Tmr;



U16 gu16_Ice_Tray_Up_Reset_Delay_Tmr;

U16 gu16_Ice_Tray_Down_Reset_Delay_Tmr;

U8 gu8_Tray_Motor_Direction;

U8 gu8_Pre_Tray_Motor_Direction;
bit F_Ice_Tray_Up_Move_Reset;

bit F_Ice_Tray_Down_Move_Reset;

bit F_over_ice_check_enable;


U16 gu16_over_ice_melt_timer;

U8 gu8_over_ice_melt_proc;

U8 gu8_over_ice_melt_operation_count;


bit F_Over_Ice_Heater_State;

bit bit_ice_out_back_1s_state;
U8 gu8_ice_out_reverse_1s_timer;

bit bit_ice_out_back_state;
U8 gu8_ice_out_reverse_timer;

U8 gu8_ice_out_operation_timer;
bit bit_ice_full_state;

U8 gu8_ice_system_ok;

/* 얼음걸림 이상 관련 변수 */
bit bit_ice_stuck_back_state;
U8 gu8_ice_stuck_reverse_timer;

/* 얼음 저빙,만빙 감지 이상 관련 변수 */
bit bit_ice_detection_abnormal_state;   /* 저빙미감지, 만빙감지 시 */
U8 gu8_ice_detect_abnormal_timer_100ms; /* 동작 타이머 */
U8 gu8_ice_detect_abnormal_op_count;    /* 동작 횟수 */

/* 얼음 추출 후 얼음 위치 후진 동작 관련 변수  */
bit bit_ice_mix_back_state;
U8 gu8_ice_mix_reverse_timer;

U8 gu8_tray_up_contiunue_timer;

U16 gu16_screw_back_and_forth_timer;
U8 gu8_screw_back_and_forth_step;

U8 gu8_ice_break_acc_count_100ms = CLEAR;
U8 gu8_ice_continue_acc_count_100ms = CLEAR;

// Endurance Here!
U8 gu8_ice_out_endurance_timer;
U32 gu32_feeder_screw_ccw_count;

bit bit_ice_shake_state;
U16 gu16_ice_full_shake_timer_100ms;
U8  gu8_ice_full_shaking_op_timer_100ms;

/* 정량추출 직전 앞뒤로 섞는 제어를 위한 변수 */
U8 gu8_ice_feeder_shake;
U8 gu8_ice_feeder_shake_time;

/* 일반얼음 추출 관련 변수 */
U8 gu8_normal_ice_acc_cur_count_100ms = CLEAR;      // 동작 현재시간
U8 gu8_normal_ice_acc_set_count_100ms = CLEAR;      // 동작 타겟시간
U8 gu8_normal_ice_stay_count = CLEAR;               // 중간 멈춤 횟수
bit bit_normal_ice_out_start;                       // 일반얼음 추출 동작 시작플래그

U16 gu16_ice_extract_timer_100ms;

extern MODEL model;
extern ICE_STUCK_1 IceStuck;

// 1. bit_ice_out_back_1s_state   (1초 역회전)
// 2. bit_ice_out_back_state      (3초 역회전)
// 3. gu8_ice_feeder_shake        (추출 전 섞기)
// 4. bit_ice_stuck_back_state    (얼음 걸림 해제)
// 5. bit_ice_mix_back_state      (제빙 후 섞기)
// 6. bit_ice_shake_state         (만빙 시 주기적 섞기)
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_ac_motor(void)
{
    /*ac_motor_time_check();*/
    output_ice_feeder_motor();
    output_ice_tray_motor();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_ice_feeder_motor(void)
{
    if(gu8IceOutCCWInterval > 0)
    {
        gu8IceOutCCWInterval--;    // 토출모터 대기3->2초
    }
    else{}

    if(gu16ErrIceOut > 0)
    {
        gu16ErrIceOut--;                // 얼음토출 모터에러 120초
    }
    else{}

/*..hui [20-4-17오후 3:04:49] 피더 역회전 넣을때 ice_extraction_finish에 F_IR 지워줘야함..꼭~~~..*/
/*..hui [20-4-17오후 3:04:59] 만빙 감지를 2초 역회전 완료 후 하도록 하기 위해..*/
    //===========================================// 얼음토출 모터 동작
    if(F_IceOutCCW == SET)                      // 토출회전(역회전)
    {
        if( F_IceBreak == CLEAR )
        {
            /*..hui [20-4-14오후 12:42:38] 3초 후 피더 추출 동작..*/
            if(pMOTOR_ICE_OUT_CCW != SET && gu8IceOutCCWInterval == 0)
            {
                gu16ErrIceOut = 1200; 						 //에러대기 120초
                bit_normal_ice_out_start = SET;
            }
            else{}

            /*..hui [20-4-14오후 12:45:16] 추출 2분 이상 지속시 강제 정지..*/
            if(pMOTOR_ICE_OUT_CCW == SET && gu16ErrIceOut == 0)
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                /* 누름추출 시 추출완료되지 않는 현상 개선 250808 CH.PARK */
                ice_extraction_finish();
                F_IceOutCCW = CLEAR;
                bit_normal_ice_out_start = CLEAR;
            }
            else{}

            if( pMOTOR_ICE_OUT_CCW == SET )
            {
                /* 2025-09-18 @CH.PARK 실제 피더가 정회전 하는 시간으로 판단 (추출 오차 개선) */
                gu16_ice_extract_timer_100ms++;

                gu8_ice_out_operation_timer++;
                if( gu8_ice_out_operation_timer >= 30 && gu8_ice_out_operation_timer < 60 )
                {
                    bit_ice_out_back_1s_state = SET;
                    bit_ice_out_back_state = CLEAR;
                }
                else if( gu8_ice_out_operation_timer >= 60 )
                {
                    gu8_ice_out_operation_timer = 60;
                    bit_ice_out_back_1s_state = CLEAR;
                    bit_ice_out_back_state = SET;
                }
                else{}
            }
            else
            {
                /*..hui [20-4-22오전 10:27:26] 추출 직전에 만빙일 경우에만 감지하도록..*/
                if( F_IceFull == SET )
                {
                    bit_ice_full_state = SET;
                }
                else
                {
                    #ifndef __AC_MOTOR_TEST_MODE__
                    bit_ice_full_state = CLEAR;
                    #endif
                }
            }

            if(bit_normal_ice_out_start != CLEAR)
            {
                gu8_normal_ice_acc_cur_count_100ms++;

                if(gu8_ice_out_continue == SET)
                {
                    /* [V1.0.0.2] 일반얼음 연속 추출 시 3초 전진, 1초 휴지 반복 */
                    gu8_ice_continue_acc_count_100ms++;
                    if(pMOTOR_ICE_OUT_CCW == SET)
                    {
                        if(gu8_ice_continue_acc_count_100ms >= 30)      /* 3초 동작 */
                        {
                            gu8_ice_continue_acc_count_100ms = 0;
                            pMOTOR_ICE_OUT_CCW = CLEAR;
                        }
                        else {  }
                    }
                    else
                    {
                        if(gu8_ice_continue_acc_count_100ms >= 10)      /* 1초 정지 */
                        {
                            gu8_ice_continue_acc_count_100ms = 0;
                            pMOTOR_ICE_OUT_CCW = SET;
                        }
                        else {  }
                    }
                }
                else if(gu8_ice_amount_step == ICE_LEVEL_1_STEP)            // 1단계
                {
                    gu8_normal_ice_stay_count = 0;
                    gu8_normal_ice_acc_set_count_100ms = ICE_OUT_1_STEP_TIME;
                    if(gu8_normal_ice_acc_cur_count_100ms <= gu8_normal_ice_acc_set_count_100ms)
                    {
                        pMOTOR_ICE_OUT_CCW = SET;
                    }
                    else
                    {
                        gu8_normal_ice_acc_cur_count_100ms = 0;
                    }
                }
                else if(gu8_ice_amount_step == ICE_LEVEL_2_STEP)
                {
                    if(gu8_normal_ice_stay_count >= 1)
                    {
                        gu8_normal_ice_acc_set_count_100ms = 30;
                        if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms - 10))      // 2초 전진
                        {
                            pMOTOR_ICE_OUT_CCW = SET;
                        }
                        else if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms + 1))  // 1초 정지
                        {
                            pMOTOR_ICE_OUT_CCW = CLEAR;
                        }
                        else
                        {
                            gu8_normal_ice_acc_cur_count_100ms = 0;
                        }
                    }
                    else
                    {
                        gu8_normal_ice_acc_set_count_100ms = 50;
                        if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms - 10))      // 4초 전진
                        {
                            pMOTOR_ICE_OUT_CCW = SET;
                        }
                        else if(gu8_normal_ice_acc_cur_count_100ms <= gu8_normal_ice_acc_set_count_100ms)        // 1초 정지
                        {
                            pMOTOR_ICE_OUT_CCW = CLEAR;
                        }
                        else
                        {
                            gu8_normal_ice_acc_cur_count_100ms = 0;
                            gu8_normal_ice_stay_count++;
                        }
                    }
                }
                else if(gu8_ice_amount_step == ICE_LEVEL_3_STEP)
                {
                    if(gu8_normal_ice_stay_count >= 1)
                    {
                        gu8_normal_ice_acc_set_count_100ms = 30;
                        if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms - 10))      // 2초 전진
                        {
                            pMOTOR_ICE_OUT_CCW = SET;
                        }
                        else if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms))      // 1초 정지
                        {
                            pMOTOR_ICE_OUT_CCW = CLEAR;
                        }
                        else
                        {
                            gu8_normal_ice_acc_cur_count_100ms = 0;
                        }
                    }
                    else
                    {
                        gu8_normal_ice_acc_set_count_100ms = 50;
                        if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms - 10))      // 4초 전진
                        {
                            pMOTOR_ICE_OUT_CCW = SET;
                        }
                        else if(gu8_normal_ice_acc_cur_count_100ms <= gu8_normal_ice_acc_set_count_100ms)        // 1초 정지
                        {
                            pMOTOR_ICE_OUT_CCW = CLEAR;
                        }
                        else
                        {
                            gu8_normal_ice_acc_cur_count_100ms = 0;
                            gu8_normal_ice_stay_count++;
                        }
                    }
                }
                else if(gu8_ice_amount_step == ICE_LEVEL_4_STEP)
                {
                    gu8_normal_ice_acc_set_count_100ms = 50;
                    if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms - 10))      // 4초 전진
                    {
                        pMOTOR_ICE_OUT_CCW = SET;
                    }
                    else if(gu8_normal_ice_acc_cur_count_100ms <= gu8_normal_ice_acc_set_count_100ms)        // 1초 정지
                    {
                        pMOTOR_ICE_OUT_CCW = CLEAR;
                    }
                    else
                    {
                        gu8_normal_ice_acc_cur_count_100ms = 0;
                    }
                }
                else {  }
            }
            else
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
            }
        }
        else
        {
            bit_normal_ice_out_start = SET;

            /* 조각얼음도 6초 이상 추출하면 후진 */
            gu8_ice_out_operation_timer++;
            if( gu8_ice_out_operation_timer >= 30 && gu8_ice_out_operation_timer < 60 )
            {
                bit_ice_out_back_1s_state = SET;
                bit_ice_out_back_state = CLEAR;
            }
            else if( gu8_ice_out_operation_timer >= 60 )
            {
                gu8_ice_out_operation_timer = 60;
                bit_ice_out_back_1s_state = CLEAR;
                bit_ice_out_back_state = SET;
            }
            else{}

            /* 조각얼음 시 2초 전진, 1초 정지 반복 (최신) 임채희님 naverworks 요청 250704 ch.park */
            gu8_ice_break_acc_count_100ms++;
            if(pMOTOR_ICE_OUT_CCW == SET)
            {
                /* 2025-09-18 @CH.PARK 실제 피더가 정회전 하는 시간으로 판단 (추출 오차 개선) */
                gu16_ice_extract_timer_100ms++;

                if(gu8_ice_break_acc_count_100ms >= 20)     /* 2초동작 */
                {
                    gu8_ice_break_acc_count_100ms = 0;
                    pMOTOR_ICE_OUT_CCW = CLEAR;
                }
                else {  }
            }
            else
            {
                if(gu8_ice_break_acc_count_100ms >= 10)     /* 1초정지 */
                {
                    gu8_ice_break_acc_count_100ms = 0;
                    pMOTOR_ICE_OUT_CCW = SET;
                }
                else {  }
            }
        }

        /*..hui [20-4-14오후 1:09:53] 추출시 역회전 정지..*/
        pMOTOR_ICE_OUT_CW = CLEAR;
        gu8_ice_out_reverse_timer = 0;
        gu8_ice_stuck_reverse_timer = 0;
    }
    else
    {
        gu8_normal_ice_acc_cur_count_100ms = CLEAR;
        gu8_normal_ice_acc_set_count_100ms = CLEAR;
        gu8_normal_ice_stay_count = CLEAR;
        bit_normal_ice_out_start = CLEAR;

        /* 양산프로그램 */
        /* pMOTOR_ICE_OUT_CCW = CLEAR; */
        bit_ice_full_state = CLEAR;
        gu8_ice_out_operation_timer = 0;
        gu8_ice_break_acc_count_100ms = 0;
        gu8_ice_continue_acc_count_100ms = 0;

        /*..hui [20-4-14오후 12:38:42] 피더스크류가 추출 방향으로 동작을 했으면..*/
        if(bit_ice_out_back_1s_state == SET)
        {
            /* 리드스위치 사용하는 모델이고 얼음 걸림 확인중이거나 동작중일 때는 추출 역회전동작은 대기 */
            if(model.u8model == MODEL_REED_USE)
            {
                if((IceStuck.u8IceJamCheck == SET)
                || (IceStuck.u8IceJamResolveStep > 0)
                )
                {
                    pMOTOR_ICE_OUT_CCW = CLEAR;
                    pMOTOR_ICE_OUT_CW = CLEAR;
                    return;
                }
            }

            pMOTOR_ICE_OUT_CCW = CLEAR;

            gu8_ice_out_reverse_1s_timer++;

            /* 3초 이상 추출완료 시 5초 대기 (멈춤) 후 1초 후진 */
            if( gu8_ice_out_reverse_1s_timer < ICE_OUT_BACK_1S_DELAY_TIME )
            {
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if( gu8_ice_out_reverse_1s_timer < (U8)(ICE_OUT_BACK_1S_DELAY_TIME + ICE_OUT_BACK_1S_GO_TIME))
            {
                pMOTOR_ICE_OUT_CW = SET;
            }
            else
            {
                bit_ice_out_back_1s_state = CLEAR;
                gu8_ice_out_reverse_1s_timer = 0;
                /*..hui [20-4-22오전 10:35:40] 역회전 완료 후 만빙감지..*/
                F_IR = SET;
                F_Low_IR = SET;
            }

            gu8_ice_out_reverse_timer = 0;
            gu8_ice_stuck_reverse_timer = 0;
            gu8_ice_mix_reverse_timer = 0;
        }
        else if( bit_ice_out_back_state == SET )
        {
            /* 리드스위치 사용하는 모델이고 얼음 걸림 확인중이거나 동작중일 때는 추출 역회전동작은 대기 */
            if(model.u8model == MODEL_REED_USE)
            {
                if((IceStuck.u8IceJamCheck == SET)
                || (IceStuck.u8IceJamResolveStep > 0)
                )
                {
                    pMOTOR_ICE_OUT_CCW = CLEAR;
                    pMOTOR_ICE_OUT_CW = CLEAR;
                    return;
                }
            }

            pMOTOR_ICE_OUT_CCW = CLEAR;

            gu8_ice_out_reverse_timer++;

            /* 6초 이상 추출완료 시 5초 대기 (멈춤) 후 3초 후진 */
            if( gu8_ice_out_reverse_timer < ICE_OUT_BACK_2S_DELAY_TIME )
            {
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if( gu8_ice_out_reverse_timer < (U8)(ICE_OUT_BACK_2S_DELAY_TIME + ICE_OUT_BACK_2S_GO_TIME))
            {
                pMOTOR_ICE_OUT_CW = SET;
            }
            else
            {
                bit_ice_out_back_state = CLEAR;
                gu8_ice_out_reverse_timer = 0;
                /*..hui [20-4-22오전 10:35:40] 역회전 완료 후 만빙감지..*/
                F_IR = SET;
                F_Low_IR = SET;

                /* 2025-09-18 CH.PARK 3초 역회전 이후 반드시 1초 대기 후 정회전되도록 함.
                바로 회전 방향을 돌리면 안됨 */
                gu8IceOutCCWInterval = 10;
            }

            gu8_ice_stuck_reverse_timer = 0;
            gu8_ice_mix_reverse_timer = 0;
            gu8_ice_out_reverse_1s_timer = 0;
        }
        else if(gu8_ice_feeder_shake == SET)
        {
            /* 2025-10-13 CH.PARK 조각얼음 추출 시작 시 100% 밀 때는 일시적으로 섞지 않음 */
            if(F_IceSelectClose == SET)
            {
                return;
            }

            gu8_ice_feeder_shake_time++;
            if(gu8_ice_feeder_shake_time <= ICE_SHAKE_DELAY_TIME)             // 4초 대기
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if(gu8_ice_feeder_shake_time <= (ICE_SHAKE_DELAY_TIME + 10))        // 1초 전진
            {
                pMOTOR_ICE_OUT_CCW = SET;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if(gu8_ice_feeder_shake_time <= (ICE_SHAKE_DELAY_TIME + 15))        // 0.5초 대기
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if(gu8_ice_feeder_shake_time <= (ICE_SHAKE_DELAY_TIME + 25))        // 1초 후진
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = SET;
            }
            else
            {
                gu8_ice_feeder_shake = CLEAR;
                gu8_ice_feeder_shake_time = 0;
            }
        }
        else if( bit_ice_stuck_back_state == SET )
        {
            pMOTOR_ICE_OUT_CCW = CLEAR;

            gu8_ice_stuck_reverse_timer++;

            /*..hui [25-3-17오후 4:16:14] 얼음 걸림 해제 동작 2초..*/
            if( gu8_ice_stuck_reverse_timer >= 20 )
            {
                gu8_ice_stuck_reverse_timer = 0;
                bit_ice_stuck_back_state = CLEAR;
            }
            else
            {
                pMOTOR_ICE_OUT_CW = SET;
            }

            gu8_ice_mix_reverse_timer = 0;
            gu8_ice_out_reverse_1s_timer = 0;
            gu8_ice_out_reverse_timer = 0;
        }
        else if( bit_ice_mix_back_state == SET )              /* 제빙완료 후 뒤섞는 제어 */
        {
            /* 리드스위치 사용하는 모델이고 얼음 걸림 확인중이거나 동작중일 때는 추출 역회전동작은 대기 */
            if(model.u8model == MODEL_REED_USE)
            {
                if((IceStuck.u8IceJamCheck == SET)
                || (IceStuck.u8IceJamResolveStep > 0)
                )
                {
                    pMOTOR_ICE_OUT_CCW = CLEAR;
                    pMOTOR_ICE_OUT_CW = CLEAR;
                    return;
                }
            }

            gu8_ice_mix_reverse_timer++;
            // if( gu8_ice_mix_reverse_timer <= 2 )           /* 0.2초 전진 */
            if( gu8_ice_mix_reverse_timer <= 5 )              /* 0.5초 전진 (변경) 250828 CH.PARK */
            {
                pMOTOR_ICE_OUT_CCW = SET;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            // else if( gu8_ice_mix_reverse_timer <= 12 )      /* 1초 대기 */
            else if( gu8_ice_mix_reverse_timer <= 15 )         /* 1초 대기 */
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            // else if( gu8_ice_mix_reverse_timer <= 15 )      /* 0.3초 후진 */
            else if( gu8_ice_mix_reverse_timer <= 20 )         /* 0.5초 후진 (변경) 250828 CH.PARK */
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = SET;
            }
            else
            {
                bit_ice_mix_back_state = CLEAR;
                gu8_ice_mix_reverse_timer = 0;
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }

            gu8_ice_stuck_reverse_timer = 0;
            gu8_ice_out_reverse_1s_timer = 0;
            gu8_ice_out_reverse_timer = 0;
        }
        else if(bit_ice_shake_state == SET)
        {
            /* 리드스위치 사용하는 모델이고 얼음 걸림 확인중이거나 동작중일 때는 추출 역회전동작은 대기 */
            if(model.u8model == MODEL_REED_USE)
            {
                if((IceStuck.u8IceJamCheck == SET)
                || (IceStuck.u8IceJamResolveStep > 0)
                )
                {
                    pMOTOR_ICE_OUT_CCW = CLEAR;
                    pMOTOR_ICE_OUT_CW = CLEAR;
                    return;
                }
            }

            gu8_ice_full_shaking_op_timer_100ms++;

            if( gu8_ice_full_shaking_op_timer_100ms <= 5 )              /* 0.5초 전진 */
            {
                pMOTOR_ICE_OUT_CCW = SET;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if( gu8_ice_full_shaking_op_timer_100ms <= 15 )         /* 1초 대기 */
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if( gu8_ice_full_shaking_op_timer_100ms <= 20 )         /* 0.5초 후진 */
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = SET;
            }
            else
            {
                bit_ice_shake_state = CLEAR;
                gu16_ice_full_shake_timer_100ms = 0;
                gu8_ice_full_shaking_op_timer_100ms = 0;
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
        }
        else
        {
            pMOTOR_ICE_OUT_CCW = CLEAR;
            pMOTOR_ICE_OUT_CW = CLEAR;

            gu8_ice_out_reverse_1s_timer = 0;
            gu8_ice_out_reverse_timer = 0;
            gu8_ice_stuck_reverse_timer = 0;
            gu8_ice_mix_reverse_timer = 0;

            if( F_IceFull == SET )
            {
                gu16_ice_full_shake_timer_100ms++;
                if(gu16_ice_full_shake_timer_100ms >= 18000)
                {
                    gu16_ice_full_shake_timer_100ms = 0;
                    gu8_ice_full_shaking_op_timer_100ms = 0;
                    bit_ice_shake_state = SET;
                }
                else {  }
            }
            else
            {
                gu16_ice_full_shake_timer_100ms = 0;
                gu8_ice_full_shaking_op_timer_100ms = 0;
                bit_ice_shake_state = CLEAR;
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_ice_tray_motor(void)
{
    /*..hui [18-2-9오후 1:09:49] CW CCW 방향 변경 시 5초 대기 후 전환..*/
    inverse_direction_time_check();

    if( Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
        || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET
        || Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET )
    {
        /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
        /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
        run_stop_ice_tray();
    }
    else if(F_ErrTrayMotor_DualInital == SET)
    {
        check_error_micro_sw_detect_at_once();
        /*..hui [18-2-13오후 3:16:13] move 에러 확인 중 동시감지 에러 체크로 전환시 모두 클리어..*/
        /*..hui [18-2-13오후 3:16:29] 다시 move조건이되면 처음부터 시작하도록....*/
        reset_micro_sw_move_err_check_state();
    }
    else
    {
        check_error_micro_sw_movement();
        gu8DualTrayStep = 0;
    }

    check_ice_system_ok();

    if( Bit18_Tray_Micro_SW_Up_Move_Error__E62 == CLEAR
        && Bit19_Tray_Micro_SW_Down_Move_Error__E63 == CLEAR
        && Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == CLEAR )
    {
        /*..hui [25-3-17오후 3:16:46] 아이스트레이 모터 출력..*/
        /*..hui [25-3-17오후 3:17:56] 에러 아닐때만 출력되도록..*/
        control_ice_tray();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void reset_micro_sw_move_err_check_state(void)
{
    F_Ice_Tray_Up_Move_Reset = 0;
    F_Ice_Tray_Down_Move_Reset = 0;
    F_Safety_Routine = 0;
    gu16_Err_Tray_Motor_Up_Total_Tmr = 0;
    gu16_Err_Tray_Motor_Down_Total_Tmr = 0;
    u8_Tray_up_moving_retry_timer = 0;
    gu16_Tray_down_moving_retry_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void inverse_direction_time_check(void)
{
    /*if( pMOTOR_ICE_TRAY_CW == SET )*/
    if( gu8_ice_tray_mode == ICE_TRAY_MODE_UP )
    {
        gu8_Tray_CW_Interval_Timer = 0;
        F_Tray_CW_delay_finish = CLEAR;
    }
    else
    {
        gu8_Tray_CW_Interval_Timer++;

        if(gu8_Tray_CW_Interval_Timer >= 50)
        {
            gu8_Tray_CW_Interval_Timer = 50;
            F_Tray_CW_delay_finish = SET;
        }
        else{}
    }

    /*if(pMOTOR_ICE_TRAY_CCW == SET)*/
    if( gu8_ice_tray_mode == ICE_TRAY_MODE_DOWN )
    {
        gu8_Tray_CCW_Interval_Timer = 0;
        F_Tray_CCW_delay_finish = CLEAR;
    }
    else
    {
        gu8_Tray_CCW_Interval_Timer++;

        if(gu8_Tray_CCW_Interval_Timer >= 50)
        {
            gu8_Tray_CCW_Interval_Timer = 50;
            F_Tray_CCW_delay_finish = SET;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_micro_sw_detect_at_once(void)
{
    /*..hui [18-2-1오전 10:43:34] 트레이 동시 감지시 재시도 ..*/
    if(gu16DualCheckDelay > 0)
    {
        gu16DualCheckDelay--;
    }
    else{}


    if(F_TrayMotorPreUP == SET)
    {
        gu8DualTrayStep = 1;
        F_TrayMotorPreUP = 0;
    }
    else{}

    switch(gu8DualTrayStep)
    {
        case 0 :

            /*..hui [18-2-1오전 11:19:07] 트레이 제빙 방향 이동..*/
            /*pMOTOR_ICE_TRAY_CW = 1;*/
            /*pMOTOR_ICE_TRAY_CCW = 0;*/
            run_up_ice_tray();

            /*gu16DualCheckDelay = 150;*/     // 제빙 15초 이동
            gu16DualCheckDelay = 100;     // 제빙 15초 이동
            gu8DualTrayStep++;     // 1.CW
            break;

        case 1 :

            if(gu16DualCheckDelay == 0)
            {
                /*pMOTOR_ICE_TRAY_CW = 0;*/
                /*pMOTOR_ICE_TRAY_CCW = 0;*/
                run_stop_ice_tray();
                gu16DualCheckDelay = 20;    // 2초 지연
                gu8DualTrayStep++;     // 2.제빙위치에서 정지
            }
            /*else if(gu16DualCheckDelay <= 130 && gu16DualCheckDelay >= 50)*/
            /*else if(gu16DualCheckDelay <= 130 && gu16DualCheckDelay >= 50)*/
            else if(gu16DualCheckDelay <= 90 && gu16DualCheckDelay >= 70)
            {
                if(gu8IceLEV == 2)              // 이동중 Dual Open 해제
                {
                    gu8DualTrayStep = 0;
                    gu16DualCheckDelay = 0;
                    gu8DualTrayCheckCNT = 0;
                    F_ErrTrayMotor_DualInital = 0;    // Tray 인식 이동중이면 Tray M/S Error 초기발생 해제
                    gu8IceStep = STATE_0_STANDBY;
                    gu8InitStep = 0;
                    F_IceInit = 1;
                }
                else{}
            }

            break;

        case 2 :

            if(gu16DualCheckDelay == 0)
            {
                /*..hui [18-2-1오전 11:19:15] 트레이 탈빙 방향 이동..*/
                /*pMOTOR_ICE_TRAY_CW = 0;*/
                /*pMOTOR_ICE_TRAY_CCW = 1;*/
                run_down_ice_tray();
                /*gu16DualCheckDelay = 150;*/   // 탈빙 15초 이동
                gu16DualCheckDelay = 250;   // 탈빙 15초 이동
                gu8DualTrayStep++;          // 3.CCW
            }
            else{}

            break;

        case 3 :

            if(gu16DualCheckDelay == 0)
            {
                /*pMOTOR_ICE_TRAY_CW = 0;*/
                /*pMOTOR_ICE_TRAY_CCW = 0;*/
                run_stop_ice_tray();
                gu16DualCheckDelay = 3000;     // 5분 지연
                gu8DualTrayStep++;              // 4.탈빙위치에서 정지
            }
            /*else if(gu16DualCheckDelay <= 130 && gu16DualCheckDelay >= 50)*/
            else if(gu16DualCheckDelay <= 220 && gu16DualCheckDelay >= 80)
            {
                if(gu8IceLEV == 2)              // 이동중 Dual Open 해제
                {
                    gu8DualTrayStep = 0;
                    gu16DualCheckDelay = 0;
                    gu8DualTrayCheckCNT = 0;
                    F_ErrTrayMotor_DualInital = 0;  // Tray 인식 이동중이면 Tray M/S Error 초기발생 해제
                    gu8IceStep = STATE_0_STANDBY;
                    gu8InitStep = 0;
                    F_IceInit = 1;
                }
            }
            else{}

            break;

        case 4 :

            if(gu16DualCheckDelay == 0)
            {
                gu8DualTrayStep = 0;
                if(++gu8DualTrayCheckCNT >= 3)
                {
                    Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 = SET;          // 3회 시도후 Error
                    F_ErrTrayMotor_DualInital = 0;
                }
                else{}
            }
            else{}

            break;

        default :

            /*pMOTOR_ICE_TRAY_CW = 0;*/
            /*pMOTOR_ICE_TRAY_CCW = 0;*/
            run_stop_ice_tray();

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_micro_sw_movement(void)
{
    //------------------------------------------------- 얼음받이 회전
    /*..hui [18-1-26오후 8:22:52] F_TrayMotorUP 가 제빙 F_TrayMotorCCW가 탈빙위치.. ..*/
    /*..hui [18-1-26오후 8:23:08] F_TrayMotorUP 가 실제로는 CCW로 돈다..*/
    gu8_Tray_Motor_Direction = (U8)(((F_TrayMotorDOWN << 1) & 0x02) |
                                     (F_TrayMotorUP));

    switch(gu8_Tray_Motor_Direction)
    {
        case TRAY_MOTOR_STOP:

            /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
            /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
            run_stop_ice_tray();
            gu16_Err_Tray_Motor_Up_Total_Tmr = 0;
            gu16_Err_Tray_Motor_Down_Total_Tmr = 0;
            u8_Tray_up_moving_retry_timer = 0;
            gu16_Tray_down_moving_retry_timer = 0;

            break;

        case TRAY_MOTOR_CW_DIRECTION:

            /*..hui [18-2-6오후 1:32:40] CCW로 돌고 5초가 아직 안지난 상태면 대기..*/
            if(F_Tray_CCW_delay_finish == SET)
            {
                /*..hui [18-2-2오후 3:11:59] 제빙방향 이동중 에러 감지..*/
                /*..hui [18-2-6오후 7:02:16] CW가 SET되는 시점은 gu8IceStep이 1일때밖에 없음, 제빙 시작할때..*/
                check_error_tray_motor_up_operation();
            }
            else
            {
                /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
                /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
                run_stop_ice_tray();
            }

            break;

        case TRAY_MOTOR_CCW_DIRECTION:

            /*..hui [18-2-6오후 1:32:40] CCW로 돌고 5초가 아직 안지난 상태면 대기..*/
            /*..hui [18-2-6오후 8:18:30] CCW가 SET되는 시점은 더미탈빙/제빙탈빙시....*/
            if(F_Tray_CW_delay_finish == SET)
            {
                /*..hui [18-2-2오후 3:12:05] 탈빙 방향 이동중 에러 감지..*/
                check_error_tray_motor_down_retry_operation();
            }
            else
            {
                /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
                /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
                run_stop_ice_tray();
            }

            break;


        default:

            /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
            /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
            run_stop_ice_tray();

            break;
    }

    ice_make_system_up_move_reset();        // 제빙방향 해빙제어
    ice_make_system_down_move_reset();      // 탈빙방향 해빙제어

    /*..hui [18-2-9오후 1:55:07] SW적으로 동시에 SET될 경우 대비용..*/
    if(F_TrayMotorUP == SET && F_TrayMotorDOWN == SET)
    {
        Bit18_Tray_Micro_SW_Up_Move_Error__E62 = SET;
    }
    else{}

    /*..hui [19-12-13오후 7:25:08] 트레이 내린 후 정상적으로 탈빙 모드까지 진입 시 누적 카운트 초기화..*/
    if( gu8IceStep >= STATE_43_ICE_TAKE_OFF )
    {
        gu8_err_tray_down_acc_count = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_tray_motor_up_operation(void)
{
    /*..hui [18-2-6오후 5:25:47] 탈빙에서 제빙 방향으로 이동 및 에러감지..*/
    switch( gu8IceTrayLEV )
    {
        case ICE_TRAY_POSITION_ICE_MAKING:

            /*..hui [18-2-6오후 2:14:43] 제빙 방향으로 감지시 정지..*/
            /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
            run_stop_ice_tray();

            F_TrayMotorUP = CLEAR;
            gu16_Err_Tray_Motor_Up_Total_Tmr = 0;
            gu8_Err_Tray_Up_Count = 0;
            u8_Tray_up_moving_retry_timer = 0;
            gu8_tray_up_contiunue_timer = 0;

            break;

        case ICE_TRAY_POSITION_MOVING:

            u8_Tray_up_moving_retry_timer = 0;
            /*pMOTOR_ICE_TRAY_CW = SET;*/
            if( gu8_ice_tray_mode == ICE_TRAY_MODE_NONE )
            {
                gu8_tray_up_contiunue_timer++;

                if( gu8_tray_up_contiunue_timer >= 10 )
                {
                    gu8_tray_up_contiunue_timer = 0;
                    run_up_ice_tray();
                }
                else{}
            }
            else
            {
                gu8_tray_up_contiunue_timer = 0;
            }

            break;

        case ICE_TRAY_POSITION_ICE_THROW:

            u8_Tray_up_moving_retry_timer++;

            if( u8_Tray_up_moving_retry_timer <= 50 )
            {
                /*pMOTOR_ICE_TRAY_CW = SET;*/
                run_up_ice_tray();
            }
            else if((u8_Tray_up_moving_retry_timer > 50) && (u8_Tray_up_moving_retry_timer <= 100))
            {
                /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
                run_stop_ice_tray();
            }
            else if((u8_Tray_up_moving_retry_timer > 100) && (u8_Tray_up_moving_retry_timer <= 150))
            {
                /*pMOTOR_ICE_TRAY_CW = SET;*/
                run_up_ice_tray();
            }
            /*else if((u8_Tray_up_moving_retry_timer > 150) && (u8_Tray_up_moving_retry_timer <= 200))
            {
                pMOTOR_ICE_TRAY_CW = CLEAR;
            }
            else if((u8_Tray_up_moving_retry_timer > 200) && (u8_Tray_up_moving_retry_timer <= 250))
            {
                pMOTOR_ICE_TRAY_CW = SET;
            }*/
            else
            {
                /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
                run_stop_ice_tray();

                F_TrayMotorUP = CLEAR;
                u8_Tray_up_moving_retry_timer = 0;
                gu8_tray_up_contiunue_timer = 0;

                gu8_Err_Tray_Up_Count++;

                /*if(gu8_Err_Tray_Up_Count >= 3)*/
                if(gu8_Err_Tray_Up_Count >= TRAY_UP_RETRY_COUNT)
                {
                    Bit18_Tray_Micro_SW_Up_Move_Error__E62 = SET;
                }
                else
                {
                    /*gu8_Err_Tray_Up_Count++;*/
                    F_Ice_Tray_Up_Move_Reset = SET;
                    ice_system_stop();

                    if( gu8_Err_Tray_Up_Count <= TRAY_UP_ICE_STUCK_COUNT )
                    {
                        /*..hui [25-3-17오후 4:18:38] 첫 2회만 얼음걸림 역회전 제어 추가..*/
                        bit_ice_stuck_back_state = SET;
                    }
                    else{}
                }
            }

            break;

        case ICE_TRAY_POSITION_ERROR:

            /*..hui [18-2-6오후 4:49:15] 트레이 동시 감지시 즉시 정지..*/
            /*..hui [18-2-6오후 4:51:07] 이쪽으로 들어올일은 없음 윗부분 동시감지 에러 부분에서 처리..*/
            /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
            run_stop_ice_tray();
            F_TrayMotorUP = CLEAR;
            u8_Tray_up_moving_retry_timer = 0;
            gu8_tray_up_contiunue_timer = 0;

            break;


        default:

            /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
            run_stop_ice_tray();
            F_TrayMotorUP = CLEAR;
            u8_Tray_up_moving_retry_timer = 0;
            gu8_tray_up_contiunue_timer = 0;

            break;
    }


    /*if( pMOTOR_ICE_TRAY_CW == SET )*/
    if( gu8_ice_tray_mode == ICE_TRAY_MODE_UP )
    {
        gu16_Err_Tray_Motor_Up_Total_Tmr++;

        if( gu16_Err_Tray_Motor_Up_Total_Tmr >= ICETRAY_CW_TIME )
        {
            /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
            run_stop_ice_tray();

            F_TrayMotorUP = CLEAR;
            gu16_Err_Tray_Motor_Up_Total_Tmr = 0;

            gu8_Err_Tray_Up_Count++;

            /*if(gu8_Err_Tray_Up_Count >= 3)*/
            if(gu8_Err_Tray_Up_Count >= TRAY_UP_RETRY_COUNT)
            {
                Bit18_Tray_Micro_SW_Up_Move_Error__E62 = SET;
            }
            else
            {
                /*gu8_Err_Tray_Up_Count++;*/
                F_Ice_Tray_Up_Move_Reset = SET;
                ice_system_stop();

                if( gu8_Err_Tray_Up_Count <= TRAY_UP_ICE_STUCK_COUNT )
                {
                    /*..hui [25-3-17오후 4:18:38] 첫 2회만 얼음걸림 역회전 제어 추가..*/
                    bit_ice_stuck_back_state = SET;
                }
                else{}
            }
        }
        else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_tray_motor_down_retry_operation(void)
{
    /*..hui [18-2-6오후 8:26:55] 제빙에서 탈빙으로 이동 및 에러감지....*/
    switch(gu8IceTrayLEV)
    {
        case ICE_TRAY_POSITION_ICE_MAKING:

            #if 0
            /*..hui [18-2-6오후 8:27:13] 5초 이상 제빙 유지시 재 시도 기능 수행..*/
            gu16_Tray_down_moving_retry_timer++;

            if(gu16_Tray_down_moving_retry_timer <= 50)
            {
                /*pMOTOR_ICE_TRAY_CCW = SET;*/
                run_down_ice_tray();
            }
            else if((gu16_Tray_down_moving_retry_timer > 50) && (gu16_Tray_down_moving_retry_timer <= 100))
            {
                /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
                run_stop_ice_tray();
            }
            else if((gu16_Tray_down_moving_retry_timer > 100) && (gu16_Tray_down_moving_retry_timer <= 150))
            {
                /*pMOTOR_ICE_TRAY_CCW = SET;*/
                run_down_ice_tray();
            }
            else
            {
                /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
                run_stop_ice_tray();
                F_TrayMotorDOWN = CLEAR;
                gu16_Tray_down_moving_retry_timer = 0;

                gu8_Err_Tray_Down_Count++;
                gu8_err_tray_down_acc_count++;

                if(gu8_Err_Tray_Down_Count >= 3 || gu8_err_tray_down_acc_count >= 10)
                {
                    /*Bit18_Tray_Micro_SW_Up_Move_Error__E62 = SET;*/
                    Bit19_Tray_Micro_SW_Down_Move_Error__E63 = SET;
                }
                else
                {
                    /*gu8_Err_Tray_Down_Count++;*/
                    F_Ice_Tray_Down_Move_Reset = SET;
                    ice_system_stop();
                }
            }
            #endif

            /*..hui [18-2-6오후 8:27:13] 5초 이상 제빙 유지시 재 시도 기능 수행..*/
            gu16_Tray_down_moving_retry_timer++;

            if(gu16_Tray_down_moving_retry_timer <= 250)
            {
                run_down_ice_tray();
            }
            else if((gu16_Tray_down_moving_retry_timer > 250) && (gu16_Tray_down_moving_retry_timer <= 300))
            {
                /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
                run_stop_ice_tray();
            }
            else if((gu16_Tray_down_moving_retry_timer > 300) && (gu16_Tray_down_moving_retry_timer <= 550))
            {
                /*pMOTOR_ICE_TRAY_CCW = SET;*/
                run_down_ice_tray();
            }
            else
            {
                /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
                run_stop_ice_tray();
                F_TrayMotorDOWN = CLEAR;
                gu16_Tray_down_moving_retry_timer = 0;

                gu8_Err_Tray_Down_Count++;
                gu8_err_tray_down_acc_count++;

                if(gu8_Err_Tray_Down_Count >= 3 || gu8_err_tray_down_acc_count >= 10)
                {
                    /*Bit18_Tray_Micro_SW_Up_Move_Error__E62 = SET;*/
                    Bit19_Tray_Micro_SW_Down_Move_Error__E63 = SET;
                }
                else
                {
                    /*gu8_Err_Tray_Down_Count++;*/
                    F_Ice_Tray_Down_Move_Reset = SET;
                    ice_system_stop();
                }
            }

            break;

        case ICE_TRAY_POSITION_MOVING:

            gu16_Tray_down_moving_retry_timer = 0;
            /*pMOTOR_ICE_TRAY_CCW = SET;*/
            run_down_ice_tray();

            break;

        case ICE_TRAY_POSITION_ICE_THROW:

            /*..hui [18-2-6오후 2:14:43] 제빙 방향으로 감지시 정지..*/
            /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
            run_stop_ice_tray();
            F_TrayMotorDOWN = CLEAR;
            gu16_Err_Tray_Motor_Down_Total_Tmr = 0;
            gu8_Err_Tray_Down_Count = 0;
            gu16_Tray_down_moving_retry_timer = 0;

            break;

        case ICE_TRAY_POSITION_ERROR:

            /*..hui [18-2-6오후 4:49:15] 트레이 동시 감지시 즉시 정지..*/
            /*..hui [18-2-6오후 4:51:07] 이쪽으로 들어올일은 없음 윗부분 동시감지 에러 부분에서 처리..*/
            /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
            run_stop_ice_tray();
            F_TrayMotorDOWN = CLEAR;
            gu16_Tray_down_moving_retry_timer = 0;

            break;


        default:

            /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
            run_stop_ice_tray();
            F_TrayMotorDOWN = CLEAR;
            gu16_Tray_down_moving_retry_timer = 0;

            break;
    }


    /*if(pMOTOR_ICE_TRAY_CCW == SET)*/
    if( gu8_ice_tray_mode == ICE_TRAY_MODE_DOWN )
    {
        gu16_Err_Tray_Motor_Down_Total_Tmr++;

        if(gu16_Err_Tray_Motor_Down_Total_Tmr >= ICETRAY_CCW_TIME)
        {
            /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
            run_stop_ice_tray();
            F_TrayMotorDOWN = CLEAR;
            gu16_Err_Tray_Motor_Down_Total_Tmr = 0;

            gu8_Err_Tray_Down_Count++;
            gu8_err_tray_down_acc_count++;

            if(gu8_Err_Tray_Down_Count >= 3 || gu8_err_tray_down_acc_count >= 10)
            {
                /*Bit18_Tray_Micro_SW_Up_Move_Error__E62 = SET;*/
                Bit19_Tray_Micro_SW_Down_Move_Error__E63 = SET;
            }
            else
            {
                /*gu8_Err_Tray_Down_Count++;*/
                F_Ice_Tray_Down_Move_Reset = SET;
                ice_system_stop();
            }
        }
        else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_make_system_up_move_reset(void)
{
    U16 mu16_delay_time = 0;

    if( gu8_Err_Tray_Up_Count <= TRAY_UP_ICE_STUCK_COUNT )
    {
        /*..hui [25-3-17오후 3:59:26] 첫 5회는 1분으로..*/
        mu16_delay_time = TRAY_UP_ICE_STUCK_DELAY_TIME;     // 1분 대기
    }
    else
    {
        mu16_delay_time = TRAY_UP_RESET_DELAY_TIME;         // 90분
    }

    if(F_Ice_Tray_Up_Move_Reset == SET)
    {
        gu16_Ice_Tray_Up_Reset_Delay_Tmr++;

        /*if(gu16_Ice_Tray_Up_Reset_Delay_Tmr >= TRAY_UP_RESET_DELAY_TIME)*/
        if(gu16_Ice_Tray_Up_Reset_Delay_Tmr >= mu16_delay_time)
        {
            if( gu8_Err_Tray_Up_Count <= 2 )
            {
                ice_stuck_reset();
                F_Ice_Tray_Up_Move_Reset = CLEAR;
                /*..hui [25-3-17오후 4:20:05] 트레이 내리고 다시 시작..*/
                /*run_down_ice_tray();*/
                down_tray_motor();
            }
            else
            {
                ice_system_reset();
                F_Ice_Tray_Up_Move_Reset = CLEAR;
            }
        }
        else
        {
            /*..hui [18-2-13오후 3:24:13] 10분 대기중에 정상 복귀시 하던거 중지....*/
            if(gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
            {
                ice_system_reset();
                F_Ice_Tray_Up_Move_Reset = CLEAR;
            }
            else{}
        }
    }
    else
    {
        gu16_Ice_Tray_Up_Reset_Delay_Tmr = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_make_system_down_move_reset(void)
{
    over_ice_making_check();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void over_ice_making_check(void)
{
    F_over_ice_check_enable = F_Ice_Tray_Down_Move_Reset;

    if(F_over_ice_check_enable != SET || Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET)
    {
        gu16_Ice_Tray_Down_Reset_Delay_Tmr = 0;
        gu16_over_ice_melt_timer = 0;
        gu8_over_ice_melt_proc = 0;
        gu8_over_ice_melt_operation_count = 0;
        //F_over_ice_melt_mode_cold_water_valve_out = CLEAR;
        F_Over_Ice_Heater_State = CLEAR;
    }
    else
    {
        gu16_Ice_Tray_Down_Reset_Delay_Tmr++;

        if(gu16_Ice_Tray_Down_Reset_Delay_Tmr >= TRAY_ERROR_STANDBY_TIME)   //10min
        {
            gu16_Ice_Tray_Down_Reset_Delay_Tmr = TRAY_ERROR_STANDBY_TIME;

            over_ice_making_melt_proc();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void over_ice_making_melt_proc(void)
{
    /*..hui [18-2-6오후 9:42:36] 과제빙된거 녹이는중에 언제든 트레이 정상 복귀되면 하던거 중지..*/
    if(gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW)
    {
        ice_system_reset();
        F_Ice_Tray_Down_Move_Reset = CLEAR;
    }
    else{}


    switch(gu8_over_ice_melt_proc)
    {
        case 0:

            gu16_over_ice_melt_timer = 0;
            gu8_over_ice_melt_proc++;

            break;

        case 1:

            /*..hui [18-2-6오후 9:16:17] 먼저 10초동안 냉수 급수밸브 ON한다..*/
            gu16_over_ice_melt_timer++;

            /*if(gu16_over_ice_melt_timer >= 100)*/
            /*..hui [23-9-22오전 11:26:29] 15초로 늘림.. 아이콘아이스 사양..*/
            if(gu16_over_ice_melt_timer >= 150)
            {
                F_IceVV = CLEAR;
                gu16_over_ice_melt_timer = 0;
                gu8_over_ice_melt_proc++;
            }
            else
            {
                F_IceVV = SET;
            }

            F_Over_Ice_Heater_State = CLEAR;

            break;

        case 2:

            /*..hui [18-2-6오후 9:21:25] 냉수 입수하고 20초동안 탈빙히터를 가동한당..*/
            gu16_over_ice_melt_timer++;

            /*..hui [20-4-21오후 7:15:57] 안전을 위해 10초로 변경..*/
            /*..hui [20-4-21오후 7:22:24] AIS30은 탈빙시 초기 OFF 부터 시작하므로 다시 15초로....*/
            /*if(gu16_over_ice_melt_timer >= 150)*/
            /*if(gu16_over_ice_melt_timer >= 6000)*/
            /*..hui [23-9-22오전 11:26:49] 탈빙히터 동작 삭제.. 20분동안 대기..*/
            if(gu16_over_ice_melt_timer >= 12000)
            {
                F_Over_Ice_Heater_State = CLEAR;
                gu16_over_ice_melt_timer = 0;
                gu8_over_ice_melt_proc++;
            }
            else
            {
                F_Over_Ice_Heater_State = SET;
            }

            break;


        case 3:

            gu16_over_ice_melt_timer = 0;
            gu8_over_ice_melt_proc++;

            F_Over_Ice_Heater_State = CLEAR;

            break;

        case 4:

            /*..hui [18-2-6오후 9:23:11] 5초동안 냉수 급수밸브 ON..*/
            gu16_over_ice_melt_timer++;

            if(gu16_over_ice_melt_timer >= 50)
            {
                F_IceVV = CLEAR;
                gu16_over_ice_melt_timer = 0;
                gu8_over_ice_melt_proc++;
            }
            else
            {
                F_IceVV = SET;
            }

            F_Over_Ice_Heater_State = CLEAR;

            break;

        case 5:

            /*..hui [18-2-6오후 9:23:58] 10분동안 대기..*/
            gu16_over_ice_melt_timer++;

            if(gu16_over_ice_melt_timer >= 6000)
            {
                /*..hui [18-2-6오후 9:25:47] 10분동안 대기후에 다시 급수밸브 5초 ON한다..*/
                gu16_over_ice_melt_timer = 0;
                gu8_over_ice_melt_proc = 3;

                /*..hui [18-2-6오후 9:29:04] 총 9번 대략 90분동안 수행..*/
                gu8_over_ice_melt_operation_count++;

                /*..hui [18-2-6오후 9:30:30] 90분 동안 수행 후 CCW 동작 한번 더 수행..*/
                if(gu8_over_ice_melt_operation_count >= 10)
                {
                    ice_system_reset();
                    F_Ice_Tray_Down_Move_Reset = CLEAR;

                    if(gu8IceTrayLEV != ICE_TRAY_POSITION_ICE_THROW)
                    {
                        F_TrayMotorUP = CLEAR;
                        F_TrayMotorDOWN = SET;
                    }
                    else{}
                }
                else{}
            }
            else{}

            F_Over_Ice_Heater_State = CLEAR;

            break;

        default:

            gu8_over_ice_melt_proc = 0;
            gu8_over_ice_melt_operation_count = 0;
            gu16_over_ice_melt_timer = 0;

            break;

    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_system_reset(void)
{
    F_Safety_Routine = CLEAR;
    gu8IceStep = STATE_0_STANDBY;
    gu8InitStep = 0;

    F_IceHeater = CLEAR;
    F_IceVV = CLEAR;

    /*..hui [18-3-22오전 10:04:37] CCW 방향 이동중에도 얼음이 있을수있음.. 더미탈빙 진행..생각이 짧았다....*/
    F_IceInit = SET;

#if 0
    /*..hui [18-2-9오후 2:34:20] CCW 방향으로 이동 재시도중에는 굳이 더미탈빙 할 필요 없음..*/
    if(F_Ice_Tray_Up_Move_Reset == SET)
    {
        F_IceInit = CLEAR;
    }
    else
    {
        F_IceInit = SET;
    }
#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_stuck_reset(void)
{
    F_Safety_Routine = CLEAR;
    gu8IceStep = STATE_0_STANDBY;
    gu8InitStep = 0;

    F_IceHeater = CLEAR;
    F_IceVV = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_system_stop(void)
{
    F_Safety_Routine = SET;
    //F_IceMakeGo = CLEAR;
    //F_IceInit = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void down_tray_motor(void)
{
    F_TrayMotorUP = CLEAR;
    F_TrayMotorPreUP = CLEAR;
    F_TrayMotorDOWN = SET;
    F_TrayMotorPreDOWN = SET;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void up_tray_motor(void)
{
    F_TrayMotorUP = SET;
    F_TrayMotorPreUP = SET;
    F_TrayMotorDOWN = CLEAR;
    F_TrayMotorPreDOWN = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_ice_system_ok(void)
{
    if( Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == CLEAR
        && Bit18_Tray_Micro_SW_Up_Move_Error__E62 == CLEAR
        && Bit19_Tray_Micro_SW_Down_Move_Error__E63 == CLEAR
        && F_Ice_Tray_Up_Move_Reset == CLEAR
        && F_Ice_Tray_Down_Move_Reset == CLEAR
        && F_Safety_Routine == CLEAR
        && gu8_Err_Tray_Down_Count == 0
        && gu8_Err_Tray_Up_Count == 0 )
    {
        gu8_ice_system_ok = SET;
    }
    else
    {
        gu8_ice_system_ok = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_tray_motor(void)
{
    F_TrayMotorUP = CLEAR;
    F_TrayMotorPreUP = CLEAR;
    F_TrayMotorDOWN = CLEAR;
    F_TrayMotorPreDOWN = CLEAR;
}



