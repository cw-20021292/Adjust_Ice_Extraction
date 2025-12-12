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
#include    "display_fnd.h"


void fnd_left_out( U8 mu8_direct, U8 mu8_hundred, U8 mu8_ten, U8 mu8_one  );
void fnd_right_out( U8 mu8_direct, U8 mu8_hundred, U8 mu8_ten, U8 mu8_one  );
void fnd_right_uart_test(void);


const U8 Fnd_Display_Data[]
= { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,                                              /*..0 ~ 9..*/
    0x77, 0x71, 0x1C, 0x54, 0x5C, 0x73, 0x50, 0x78, 0x40, 0x79, 0x3F, 0x39, 0x76, 0x38, 0x5E, 0x7C, 0x37, 0x0C,  /*..A, F, u, n, o, P, r, t, -, E, O, C, H, L, d, b, N, v..*/
    0x39, 0x09, 0x0f, 0x63, 0x5C,                                                                            /*..continue..square up, square down*/
    0x08, 0x48, 0x49,                                                                                        /* 예열표시 ≡ */
    0x00 };


U8 gu8_temporary_thousand;
U8 gu8_temporary_hundred;
U8 gu8_temporary_ten;
U8 gu8_temporary_one;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/






/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_out( U8 mu8_direct, U8 mu8_hundred, U8 mu8_ten, U8 mu8_one  )
{
    if( mu8_direct == DIRECT_DISPLAY )
    {
        gu8_front_temp_fnd_hundred = mu8_hundred;
        gu8_front_temp_fnd_ten = mu8_ten;
        gu8_front_temp_fnd_one = mu8_one;
    }
    else
    {
        gu8_front_temp_fnd_hundred = Fnd_Display_Data[ mu8_hundred ];
        gu8_front_temp_fnd_ten = Fnd_Display_Data[ mu8_ten ];
        gu8_front_temp_fnd_one = Fnd_Display_Data[ mu8_one ];
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_out( U8 mu8_direct, U8 mu8_hundred, U8 mu8_ten, U8 mu8_one  )
{
    if( mu8_direct == DIRECT_DISPLAY )
    {
        gu8_front_amount_fnd_hundred = mu8_hundred;
        gu8_front_amount_fnd_ten = mu8_ten;
        gu8_front_amount_fnd_one = mu8_one;
    }
    else
    {
        gu8_front_amount_fnd_hundred = Fnd_Display_Data[ mu8_hundred ];
        gu8_front_amount_fnd_ten = Fnd_Display_Data[ mu8_ten ];
        gu8_front_amount_fnd_one = Fnd_Display_Data[ mu8_one ];
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_uart_test(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    if( gu8_uart_test_mode == NOT_INCLUDE_FRONT_UART_TEST )
    {
        mu8_temporary_hundred = (U8)((gu8_Flow_1sec / 100) % 10);
        mu8_temporary_ten = (U8)((gu8_Flow_1sec / 10) % 10);
        mu8_temporary_one = (U8)(gu8_Flow_1sec % 10);
    }
    else
    {
        if( bit_manual_test_start == SET )
        {
            if( gu8_GasSwitch_Status == GAS_SWITCH_ICE )
            {
                mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
                mu8_temporary_ten = (U8)((gu8_Eva_Cold_Temperature_One_Degree / 10) % 10);
                mu8_temporary_one = (U8)(gu8_Eva_Cold_Temperature_One_Degree % 10);
            }
            else if( gu8_GasSwitch_Status == GAS_SWITCH_COLD )
            {
                mu8_temporary_hundred = DISPLAY_NUM_LARGE_C;
                mu8_temporary_ten = (U8)((gu8_Cold_Temperature_One_Degree / 10) % 10);
                mu8_temporary_one = (U8)(gu8_Cold_Temperature_One_Degree % 10);
            }
            else /*if( gu8_GasSwitch_Status == GAS_SWITCH_HOTGAS )*/
            {
                mu8_temporary_hundred = DISPLAY_NUM_LARGE_H;
                mu8_temporary_ten = (U8)((gu8_Amb_Temperature_One_Degree / 10) % 10);
                mu8_temporary_one = (U8)(gu8_Amb_Temperature_One_Degree % 10);
            }
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;
        }
    }

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}






/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




