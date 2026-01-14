/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _MOTOR_ICE_SELECT_OUTPUT_H_
#define _MOTOR_ICE_SELECT_OUTPUT_H_


#define DEFAULT_ICE_DOOR_CLOSE_TIME     86400

/* 시간 카운터 상수 정의 */
#define MAX_100MS_CNT       600     // 1분 = 600 * 100ms
#define MAX_MINUTE_CNT      60      // 1시간 = 60분
#define MAX_HOUR_CNT        24      // 1일 = 24시간
#define MAX_DAY_CNT         30      // 30일 주기

void IceStuckInit(void);
void IceDoorReedInit(void);
void CheckIceDoorReedStatus(void);
void SetIceDoorReedStatus(REED_INFO mu8_reed_status);
REED_INFO GetIceDoorReedStatus(void);
void IceJamVoicePlayCountInit(void);
void IceStuckProcess(void);
void SetIceJamProcessCount(U8 mu8_ice_jam_process_count);
U8 GetIceJamProcessCount(void);
void ProcessIceJamClear(void);

extern U8 finish_ice_setting(void);

extern U8 gu8IceClose;
extern bit F_IceOpen;

extern U8 gu8ErrDoor;
extern bit F_IceOut;
extern bit F_LineTest;
extern bit F_IceBreak;

extern U8 gu8IceInnerClose;
#endif
