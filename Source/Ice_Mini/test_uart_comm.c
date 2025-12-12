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
#include    "test_uart_comm.h"


void AT_UART_Communication(void);
void AT_UART_Rx_Process(void);
void AT_UART_Tx_Process(void);
void int_UART3_AT_TX(void);
void int_UART3_AT_RX(void);




bit AT_F_TxStart;             //
bit AT_F_RxComplete;          //
bit AT_F_Rx_NG;               //
bit AT_F_Uart_Open_Short_ERROR;

U8 AT_gu8RxdMaxCNT;
U8 AT_gu8TX_ERROR;
U8 AT_gu8TxData[70];
U8 AT_gu8RxData[70];
U8 AT_gu8TxdCounter;
U8 AT_UART_TXD_LENGTH;
U8 AT_gu8UARTStateMode;
U8 AT_gu8RxdCounter;

U16 AT_gu16_CMD_Mode;
U8 AT_gu8_CMD_MATHODE;
U8 gu8UART_DataLength;
bit F_AT_TX_Finish;
bit F_AT_TX_Make;
bit F_Uart_Final;
bit F_Entry_UARTest;
bit F_UARTest;
U8 gu8RxdBufferData;

U8 gu8_uart_test_mode;

U8 gu8_uart_comp_start;
U8 gu8_uart_comp_rps;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                    (1) UART 통신 데이터 처리
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void AT_UART_Communication(void)
{
    AT_UART_Rx_Process();         // 1-1 수신부 데이터 변환
    AT_UART_Tx_Process();         // 1-2 송신부 데이터 변환
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
///""SUBR COMMENT""************************************************************
// ID         : ATUO TEST_Rx_Process
// 개요         : 자동화 테스트 수신부
//----------------------------------------------------------------------------
// 기능       : 자동화 테스트 수신부 처리
//
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
//------------------------
// 1-1 수신부 데이터 변환
//------------------------
void AT_UART_Rx_Process(void)
{
    static U8 AT_mu8Temp_Data1;
    static U8 AT_mu8Temp_Data2;
    static U8 AT_mu8Temp_Data3;
    static U8 AT_mu8Temp_Data4;
    static U8 AT_mu8Temp_Data5;

    static U16 AT_mu16Temp_Data;

    if(AT_F_RxComplete != SET)
    {
        return;
    }
    else
    {
        AT_F_RxComplete = 0;
    }

    AT_F_Uart_Open_Short_ERROR = 0;

    AT_mu8Temp_Data1 = AT_mu8Temp_Data2 = AT_mu8Temp_Data3 = 0;

    //========================================================// CHK 확인
    AT_mu8Temp_Data3 = AT_gu8RxdMaxCNT - 2;

    for(AT_mu8Temp_Data1=0; AT_mu8Temp_Data1<AT_mu8Temp_Data3 ; AT_mu8Temp_Data1++)
    {
        AT_mu8Temp_Data2 ^= AT_gu8RxData[AT_mu8Temp_Data1];                   // 수신한 데이터를 계산한 C/S
    }

    AT_mu8Temp_Data3 = AscToHex(AT_gu8RxData[AT_gu8RxdMaxCNT-2], AT_gu8RxData[AT_gu8RxdMaxCNT-1]);    // 수신된 C/S

    AT_mu8Temp_Data1 = 0;
    AT_mu8Temp_Data1 = AscToHex(AT_gu8RxData[1], AT_gu8RxData[2]);    //CMD

    AT_mu8Temp_Data4 = 0;
    AT_mu8Temp_Data4 = AscToHex(AT_gu8RxData[3], AT_gu8RxData[4]);    //모르는 데이타

    AT_mu8Temp_Data5 = 0;
    AT_mu8Temp_Data5 = AscToHex(AT_gu8RxData[5], AT_gu8RxData[6]);

    if(AT_mu8Temp_Data2 == AT_mu8Temp_Data3)
    {
        AT_gu8TX_ERROR = 0;
        AT_F_Rx_NG = 0;
    }
    else
    {
        AT_gu8TX_ERROR++;
        AT_F_Rx_NG = 1;
    }

    /*AT_gu16_CMD_Mode = AT_mu8Temp_Data1;*/
    /*AT_gu8_CMD_MATHODE = AT_mu8Temp_Data4;*/

    if( AT_F_Rx_NG == SET )                            //수신 데이터의 CS불일치할경우 바로 No Ack 송부, No Ack시 다음스텝 수행불가
    {
        #if 0
        AT_gu16_CMD_Mode = 0xFF00;
        gu8UARTData[1]= AT_RS232_NAK;
        gu8UARTData[2]= AT_mu8Temp_Data1;
        gu8UARTData[3]= AT_mu8Temp_Data4;
        #endif

        AT_gu16_CMD_Mode = AT_UART_No_CMD;
    }
    else
    {
        AT_gu16_CMD_Mode = AT_mu8Temp_Data1;
        AT_gu16_CMD_Mode = AT_gu16_CMD_Mode << 8;
        AT_gu16_CMD_Mode |= AT_mu8Temp_Data4;

        if( AT_gu16_CMD_Mode == AT_UART_CMD_START )
        {
            gu8_uart_test_mode = AT_mu8Temp_Data5;
        }
        else if( AT_gu16_CMD_Mode == AT_UART_CMD_COMP_ON )
        {
            /*gu8_uart_comp_start = AT_mu8Temp_Data5;*/
            /*gu8_uart_comp_rps = AT_mu8Temp_Data6;*/
            gu8_uart_comp_rps = AT_mu8Temp_Data5;
        }
        else{}
    }

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//------------------------
// 1-2 송신부 데이터 변환
//------------------------
void AT_UART_Tx_Process(void)
{
    static U8  AT_mu8Temp_Data1, AT_mu8Temp_Data2, AT_mu8Temp_Data3, gu8UARTAddr;
    static U16 AT_mu16Temp_Data;

    if(AT_F_TxStart != SET)
    {
        return;
    }
    else
    {
        AT_F_TxStart = 0;
    }

    AT_gu8TxData[0] = AT_RS232_STX;

    for(gu8UARTAddr=1; gu8UARTAddr < (gu8UART_DataLength + 1); gu8UARTAddr++)
    {
        AT_mu16Temp_Data = 0;

        if( gu8UARTData[2] == (U8)(AT_UART_CMD_SENSOR_TH / 256) && gu8UARTData[3] == (U8)(AT_UART_CMD_SENSOR_TH % 256) )
        {
            if( gu8UARTAddr == 4 || gu8UARTAddr == 5
                || gu8UARTAddr == 8 || gu8UARTAddr == 9
                || gu8UARTAddr == 12 || gu8UARTAddr == 13
                || gu8UARTAddr == 16 || gu8UARTAddr == 17
                || gu8UARTAddr == 20 || gu8UARTAddr == 21
                || gu8UARTAddr == 24 || gu8UARTAddr == 25
                || gu8UARTAddr == 28 || gu8UARTAddr == 29
                || gu8UARTAddr == 32 || gu8UARTAddr == 33 )
                /*|| gu8UARTAddr == 36 || gu8UARTAddr == 37 )*/
            {
                AT_mu16Temp_Data = DecToAsc(gu8UARTData[gu8UARTAddr]);
            }
            else
            {
                AT_mu16Temp_Data = HexToAsc(gu8UARTData[gu8UARTAddr]);
            }
        }
        else if( gu8UARTData[2] == (U8)(AT_UART_CMD_CURRENT_CALC / 256) && gu8UARTData[3] == (U8)(AT_UART_CMD_CURRENT_CALC % 256) )
        {
            /*..hui [21-7-20오전 10:36:16] 전류 측정값도 dec를 아스키로 변환..*/
            if(gu8UARTAddr >= 4 && gu8UARTAddr <= 9)
            {
                AT_mu16Temp_Data = DecToAsc(gu8UARTData[gu8UARTAddr]);
            }
            else
            {
                AT_mu16Temp_Data = HexToAsc(gu8UARTData[gu8UARTAddr]);
            }
        }
        else
        {
            AT_mu16Temp_Data = HexToAsc(gu8UARTData[gu8UARTAddr]);
        }

        /*AT_mu16Temp_Data = HexToAsc(gu8UARTData[gu8UARTAddr]);*/                //DATA : 1..2..3..4
        AT_gu8TxData[(gu8UARTAddr*2)-1] = (U8)(AT_mu16Temp_Data>>8);          //ASC  : 1..3..5..7
        AT_gu8TxData[(gu8UARTAddr*2)]   = (U8)AT_mu16Temp_Data;               //ASC  : 2..4..6..8
    }                                                                         //[0]STX..[1]~(8]DATA(ASC)..[9]~[10]CS(ASC)..[11]ETX..

    AT_mu8Temp_Data1 = 0;
    AT_mu8Temp_Data2 = 0;

    for(AT_mu8Temp_Data2=0; AT_mu8Temp_Data2 < ((gu8UART_DataLength*2)+1); AT_mu8Temp_Data2++)
    {
        AT_mu8Temp_Data1 ^= AT_gu8TxData[AT_mu8Temp_Data2];
    }

    AT_mu16Temp_Data = HexToAsc(AT_mu8Temp_Data1);

    AT_gu8TxData[(gu8UART_DataLength * 2) + 1] = (U8)(AT_mu16Temp_Data>>8);
    AT_gu8TxData[(gu8UART_DataLength * 2) + 2] = (U8)AT_mu16Temp_Data;
    AT_gu8TxData[(gu8UART_DataLength * 2) + 3] = AT_RS232_ETX;


    AT_UART_TXD_LENGTH = ((gu8UART_DataLength * 2) + 4);


    AT_gu8TxdCounter = 0;

    TXD3 = AT_gu8TxData[AT_gu8TxdCounter];               // 첫번째 바이트 보내기

    AT_gu8TxdCounter++;

    F_AT_TX_Finish = 1;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//------------------------------------------------------------------------------
//                      UART RXD (INTST1) - AutoTest
//------------------------------------------------------------------------------
void int_UART3_AT_TX(void)
{
//  TXD1=0x20;

    NOP();
    NOP();
    NOP();
    NOP();

    if(F_AT_TX_Finish == SET)
    {
        // 수신 인터럽 후에 바로 보냄
        TXD3 = AT_gu8TxData[AT_gu8TxdCounter];

        if(AT_gu8TxData[AT_gu8TxdCounter] == 0x04)        // 송신완료
        {
            AT_gu8TxdCounter = 0;                          // ETX 수신 후 전송 카운트 초기화
            F_AT_TX_Finish = 0;
        }
        else
        {
            AT_gu8TxdCounter++;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//------------------------------------------------------------------------------
//                      UART RXD (INTSR1) - AutoTest
//------------------------------------------------------------------------------
void int_UART3_AT_RX(void)
{
    U8 err_type03;

    err_type03 = (U8)(SSR13 & 0x0007);
    SIR13 = (U16)err_type03;

    gu8RxdBufferData = RXD3;

    switch(AT_gu8UARTStateMode)
    {
        // 대기
        case UART_MODE_IDLE:

             if(gu8RxdBufferData == AT_RS232_STX)
             {                 // STX check 0x01
                 AT_gu8RxdCounter = 0;
                 AT_gu8UARTStateMode = UART_MODE_RECEIVE;            // 0x01이 들어오면 '수신중'으로
                 AT_gu8RxData[AT_gu8RxdCounter++] = gu8RxdBufferData;// Stx 카운트 0
             }
             else
             {
                 AT_gu8RxdCounter = 0;
             }

             break;

         // 수신중
        case UART_MODE_RECEIVE:

             if(gu8RxdBufferData == AT_RS232_ETX)
             {                 // ETX check 0x04
                 AT_gu8RxData[AT_gu8RxdCounter] = gu8RxdBufferData;
                 AT_F_RxComplete = 1;                                // 수신완료

                 // Rx data initialize //
                 AT_gu8RxdMaxCNT = AT_gu8RxdCounter;                 // Except byte of stx, etx
                 AT_gu8RxdCounter = 0;
                 AT_gu8UARTStateMode = UART_MODE_IDLE;
             }
             else
             {
                 AT_gu8RxData[AT_gu8RxdCounter++] = gu8RxdBufferData;// 수신 데이터 저장
             }

             break;

        // Error
        case UART_MODE_ERROR:

             AT_gu8RxdCounter = 0;
             AT_gu8UARTStateMode = UART_MODE_IDLE;

             break;


        default:  // Rx data initialize //

             AT_gu8RxdCounter = 0;
             AT_gu8UARTStateMode = UART_MODE_IDLE;

             break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


