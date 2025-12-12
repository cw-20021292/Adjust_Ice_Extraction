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
#include    "cody_empty_tank.h"


void cody_empty_tank(void);

U8 gu8_empty_tank_step;
U16 gu16_empty_tank_timer;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cody_empty_tank(void)
{
    #if 0
    /*..hui [20-1-29오후 1:26:45] 탱크비움은 커버 열린상태에서 냉수 연속추출로 가능하기 때문에 메뉴 삭제..*/
    if(Bit1_Empty_Tank_Start == CLEAR)
    {
        gu8_empty_tank_step = 0;
        return;
    }
    else{}

    if(gu8_empty_tank_step >= 1 && gu8_empty_tank_step <= 5)
    {
        ///////delay_disappear_popup();
    }
    else{}

    switch( gu8_empty_tank_step )
    {
        case 0:

            gu8_empty_tank_step++;
            gu16_empty_tank_timer = 0;
            ///Bit2_Empty_Tank_Start_State = SET;

            break;

        case 1:

            /*..hui [20-1-8오후 4:02:11] 냉수 드레인 밸브 ON..*/
            gu16_empty_tank_timer++;

            if( gu16_empty_tank_timer >= 20 )
            {
                gu16_empty_tank_timer = 0;
                gu8_empty_tank_step++;
            }
            else{}

            break;

        case 2:

            /*..hui [20-1-8오후 4:04:07] 드레인 펌프 FULL ON..*/
            gu16_empty_tank_timer = 0;
            gu8_empty_tank_step++;

            break;

        case 3:

            gu16_empty_tank_timer++;

            if( gu16_empty_tank_timer >= EMPTY_TANK_TIME)
            {
                gu16_empty_tank_timer = 0;
                gu8_empty_tank_step++;
            }
            else{}

            break;

        case 4:

            /*..hui [20-1-8오후 4:08:12] 냉수 드레인 밸브 / 드레인 펌프 둘 다 OFF..*/
            /////Bit3_Empty_Tank_Finish_State = SET;
            gu8_empty_tank_step++;

            break;

        case 5:

            Bit1_Empty_Tank_Start = CLEAR;
            gu16_empty_tank_timer = 0;
            gu8_empty_tank_step = 0;

            break;

        default:

            break;
    }
    #endif
}


