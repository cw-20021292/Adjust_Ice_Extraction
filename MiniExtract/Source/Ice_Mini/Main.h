/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

extern void System_ini(void);
extern void Mode_Control(void);
extern void Heating_Control(void);
extern void Input(void);
extern void Output(void);
extern void Error_Control(void);
extern void FactoryMode_Control(void);
extern void Pc_Communication(void);
extern void Display_Control(void);

extern U8  u8CountSync;
extern void Save_Eeprom_Data(void);
extern void Pcb_Test_Main(void);
extern void TestUart(void);
extern void Ice_Make_Process(void);
extern void factory_display_test_main(void);
extern void factory_test_main(void);
extern void Front_Communication(void);
extern void lcd_test(void);
extern void Make_Mode_Decision(void);
extern void lcd_init(void);
extern void Save_Eeprom_Data(void);
extern void Uart_Test_Main(void);
extern void Pcb_Test_Main(void);
extern void Display_Test_Main(void);
extern void AD_Conversion(void);
extern void flushing_main(void);
extern void WifiControlProcess ( E_WIFI_TIME_T mu8Time );
extern void get_final_small_amb_temp(void);
extern void ProcessVoice_Main(void);
extern void self_test(void);



extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2








extern U8  u8CountSync_50Ms;


extern bit F_50ms;
extern bit F_ADC_Check;
extern U8 gu8_uart_test_mode;


#endif
