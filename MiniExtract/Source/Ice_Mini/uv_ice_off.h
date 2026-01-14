/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _UV_ICE_OFF_H_
#define _UV_ICE_OFF_H_

U8 uv_ice_off_control(void);

typedef enum UV_Ice_Off_Step_t
{
    UV_ICE_OFF_STEP_STANDBY = 0,
    UV_ICE_OFF_STEP_TRAY_DOWN_1,
    UV_ICE_OFF_STEP_TRAY_DOWN_CHECK_1,
    UV_ICE_OFF_STEP_UV_ON_TRAY_DOWN_2H,
    UV_ICE_OFF_STEP_UV_OFF_10H,
    UV_ICE_OFF_STEP_TRAY_UP,
    UV_ICE_OFF_STEP_TRAY_UP_CHECK,
    UV_ICE_OFF_STEP_UV_ON_TRAY_UP_2H,
    UV_ICE_OFF_STEP_TRAY_DOWN_2,
    UV_ICE_OFF_STEP_TRAY_DOWN_CHECK_2,
    UV_ICE_OFF_STEP_FINISH,
} UV_Ice_Off_Step_t;

extern void down_tray_motor(void);
extern void up_tray_motor(void);

extern TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                                    U32ControlErrorsD.dward
#define         Bit0_Hot_Tank_Temp_Open_Short_Error__E45            U32ControlErrorsD.Bit.b0    //E45
#define         Bit1_Room_OverHeat_Error__E49                       U32ControlErrorsD.Bit.b1    //E49
#define         Bit2_Room_Temp_Open_Short_Error__E42                U32ControlErrorsD.Bit.b2    //E42
#define         Bit3_Leakage_Sensor_Error__E01                      U32ControlErrorsD.Bit.b3    //E01
#define         Bit4_Room_Low_Water_Level_Error__E21                U32ControlErrorsD.Bit.b4    //E21
#define         Bit5_Hot_Heater_OverHeat_Error__E40_Not_Use         U32ControlErrorsD.Bit.b5    //E40
#define         Bit6_Main_Water_Flow_Block_Error__E09               U32ControlErrorsD.Bit.b6    //E09
#define         Bit7_BLDC_Communication_Error__E27                  U32ControlErrorsD.Bit.b7    //E27
#define         Bit8_BLDC_Operation_Error_Current_Sensing__E81      U32ControlErrorsD.Bit.b8    //E81
#define         Bit9_BLDC_Operation_Error_Starting_Fail__E82        U32ControlErrorsD.Bit.b9    //E82
#define         Bit10_BLDC_Operation_Error_Over_Current__E83        U32ControlErrorsD.Bit.b10   //E83
#define         Bit11_BLDC_Operation_Error_Overheat__E84            U32ControlErrorsD.Bit.b11   //E84
#define         Bit12_BLDC_Operation_Error_Disconnection_Comm__E85  U32ControlErrorsD.Bit.b12   //E85
#define         Bit13_BLDC_Operation_Error_Abnormal_Voltage__E86    U32ControlErrorsD.Bit.b13   //E86
#define         Bit14_Cold_Temp_Open_Short_Error__E44               U32ControlErrorsD.Bit.b14   //E44
#define         Bit15_Amb_Temp_Open_Short_Error__E43                U32ControlErrorsD.Bit.b15   //E43
#define         Bit16_Drain_Pump_Error__E60                         U32ControlErrorsD.Bit.b16   //E60
#define         Bit17_Tray_Micro_SW_Dual_Detect_Error__E61          U32ControlErrorsD.Bit.b17   //E61
#define         Bit18_Tray_Micro_SW_Up_Move_Error__E62              U32ControlErrorsD.Bit.b18   //E62
#define         Bit19_Tray_Micro_SW_Down_Move_Error__E63            U32ControlErrorsD.Bit.b19   //E63
#define         Bit20_Mixing_Out_Temp_Open_Short_Error__E52         U32ControlErrorsD.Bit.b20   //E52
#define         Bit21_Amb_Side_Temp_Open_Short_Error__E53           U32ControlErrorsD.Bit.b21   //E53
#define         Bit22_Tray_In_Temp_Open_Short_Error__E41_Not_Use    U32ControlErrorsD.Bit.b22   //E56
#define         Bit23_Water_Tank_1_2_UV_Error__E74                  U32ControlErrorsD.Bit.b23   //E74
#define         Bit24_Ice_Tank_1_2_Back_UV_Error__E75               U32ControlErrorsD.Bit.b24   //E75
#define         Bit25_Ice_Tray_1_2_UV_Error__E76                    U32ControlErrorsD.Bit.b25   //E76
#define         Bit26_Ice_Tank_3_Front_UV_Error__E79                U32ControlErrorsD.Bit.b26   //E79
#define         Bit27_Tds_In_Temp_Open_Short_Error__E90             U32ControlErrorsD.Bit.b27   //E90
#define         Bit28_Tds_Out_Temp_Open_Short_Error__E91            U32ControlErrorsD.Bit.b28   //E91
#define         Bit29_Tds_In_Data_Error__E92                        U32ControlErrorsD.Bit.b29   //E92
#define         Bit30_Tds_Out_Data_Error__E93                       U32ControlErrorsD.Bit.b30   //E93

extern TYPE_BYTE          U812VPowerControl;
#define            u8PowerControl12V                                    U812VPowerControl.byte
#define            Bit0_Gas_Switch_12V_Out_State                        U812VPowerControl.Bit.b0
#define            Bit1_Ice_Tank_UV_12V_Out_State                       U812VPowerControl.Bit.b1
#define            Bit2_Uart_Test_Mode_State                            U812VPowerControl.Bit.b2
#define            Bit3_Water_Tank_UV_12V_Out_State                     U812VPowerControl.Bit.b3
#define            Bit4_Ice_Tray_UV_12V_Out_State                       U812VPowerControl.Bit.b4
#define            Bit5_Ice_Tank_Front_UV_12V_Out_State                 U812VPowerControl.Bit.b5
#define            Bit6_Drain_Pump_FeedBack_12V_Out_State               U812VPowerControl.Bit.b6

extern TYPE_BYTE          U8IceTankUvONB;
#define            u8IceTankUvON                                        U8IceTankUvONB.byte
#define            Bit0_Ice_Tank_UV_On_State                            U8IceTankUvONB.Bit.b0
#define            Bit1_Ice_Tank_UV_Ice_Tank_Clean_On_State             U8IceTankUvONB.Bit.b1
#define            Bit2_Ice_Tank_UV_Ice_Off_On_State                    U8IceTankUvONB.Bit.b2
#define            Bit3_Ice_Tank_UV_Fault_Test_On_State                 U8IceTankUvONB.Bit.b3

extern TYPE_BYTE          U8IceTankUvOFFB;
#define            u8IceTankUvOFF                                       U8IceTankUvOFFB.byte
#define            Bit0_Tank_Open_UV_Off_State                          U8IceTankUvOFFB.Bit.b0
#define            Bit1_Ice_Extract_UV_Off_State                        U8IceTankUvOFFB.Bit.b1
#define            Bit2_Ice_Tank_UV_Retry_3S_Off_State                  U8IceTankUvOFFB.Bit.b2
#define            Bit3_Ice_Tank_UV_Error_Off_State                     U8IceTankUvOFFB.Bit.b3

extern TYPE_BYTE          U8CodyInspectOperationB;
#define            u8CodyInspectOperation                      U8CodyInspectOperationB.byte
#define            Bit0_Cody_Service_Kit_Start                 U8CodyInspectOperationB.Bit.b0
#define            Bit1_Empty_Tank_Start                       U8CodyInspectOperationB.Bit.b1
#define            Bit2_Ice_Tray_Test_Start                    U8CodyInspectOperationB.Bit.b2

extern bit F_Tank_Cover_Input;
extern U16 gu16StepMotor2;
extern bit F_IceFull;
extern ICE_STEP gu8IceStep;
extern bit F_IceOn;
extern bit bit_uv_ice_tray_out;
extern U8 gu8_ice_tray_1_2_uv_operation_timer_min;
extern bit bit_install_flushing_state;
extern bit bit_self_test_start;
extern bit bit_uv_tank_input;

extern U8 gu8_ice_system_ok;
extern U8 gu8IceTrayLEV;
extern bit F_IceInit;
extern bit bit_ice_tank_ster_start;
extern U8 gu8_cody_take_off_ice_start;
extern bit F_TrayMotorDOWN;
extern bit F_TrayMotorUP;

extern tsSTEPMOTOR sStepMotor;



#endif
