/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _MODEL_SELECT_H_
#define _MODEL_SELECT_H_

void ModelInit(void);

void SetIsSelectModel(U8 mu8_is_model_checked);
U8 GetIsSelectModel(void);
void SetModel(MODEL_DATA mu8_model);
MODEL_DATA GetModel(void);

#endif
