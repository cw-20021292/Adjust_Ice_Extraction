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
#include    "model_select.h"
#include    "motor_ice_select.h"

void ModelSelect(void);

MODEL model;

#define MODEL_JUDGE_DONE_TIME       10  // 1초

extern U16 gu16_IceSelect_StepMotor;

/************************************************************************************************************************
/**
 * @brief 리드스위치 추가여부 판단 관련 변수 초기화
 * @date 2025-10-28
 */
void ModelInit(void)
{
    model.u8model = MODEL_REED_NONE;
    model.u8IsModelChecked = FALSE;
    model.u8ModelCheckTimer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ModelSelect(void)
{
    if(GetIsSelectModel() == SET)
    {
        model.u8ModelCheckTimer = 0;
        return;
    }
    else{}

    /* 초기 전원 인가 후 이너도어 동작완료 시 (펄스값 0) */
    if(gu16_IceSelect_StepMotor == 0)
    {
        // 1초 후 모델 판단
        model.u8ModelCheckTimer++;
        if(model.u8ModelCheckTimer >= MODEL_JUDGE_DONE_TIME)
        {
            model.u8ModelCheckTimer = MODEL_JUDGE_DONE_TIME;

            /* LOW ACTIVE (감지) */
            if(GET_INNER_DOOR_REED_SW() == ACTIVE_LOW_DETECTED)
            {
                SetModel(MODEL_REED_USE);
            }
            else
            {
                SetModel(MODEL_REED_NONE);
            }

            SetIsSelectModel(SET);
            IceJamVoicePlayCountInit();
        }
    }
    else
    {
        model.u8ModelCheckTimer = 0;
    }
}

void SetIsSelectModel(U8 mu8_is_model_checked)
{
    model.u8IsModelChecked = mu8_is_model_checked;
}

U8 GetIsSelectModel(void)
{
    return model.u8IsModelChecked;
}

void SetModel(MODEL_DATA mu8_model)
{
    model.u8model = mu8_model;
}

MODEL_DATA GetModel(void)
{
    return model.u8model;
}

