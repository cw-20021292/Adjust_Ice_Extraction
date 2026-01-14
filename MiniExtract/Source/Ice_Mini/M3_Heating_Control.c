/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Display.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M3_Heating_Control.h"

void Heating_Control(void);

void flow_valve_control(void);
void init_flow_valve(void);
void control_flow_valve(void);
void preheating_flow_control(void);
void preheating_variable_flow_control(void);
void mainheating_flow_control(void);
void Water_Heater_Control(void);
void set_target_temperature(void);
void normal_heater_watt_check(void);
void Cal_HotFlowHz(void);
void Cal_HeaterWatt(void);
void heating_control(void);
void pre_heating_control( U8 mu8_target );
void main_heating_control( U8 mu8_target );
void calc_heater_out( U8 mu8_target );
void update_max_flow(void);

void sort_hot_temp(void);

void SetTargetTempUnder_15(void);
void SetTargetTempUnder_25(void);
void SetTargetTempExtra(void);

U16 gu16HeaterOffTemp;
U16 gu16HeaterOnTemp;
U16 gu16HeaterSaveOnTemp;
U16 gu16HeaterNoUseOnTemp;
U8 gu8HeaterOffDelay;


U8 gu8HeaterControlCnt;

//function control_flow_valve
U8 gu8_flow_control_timer;

//fucntion preheating_flow_control
U16 u16Heater_Power_Save;

//function Mainheating_flow_control
U8 u8Target_Hz_Hot;     //占쏙옙표 占쏙옙占쏙옙
U8 gu8_adjust_pulse_test;

//function set_target_temperature
U8 gu8_Hot_Target_Temp;
U8 gu8_Hot_Preheat_Temp;
U8 gu8_min_power;

//function normal_heater_watt_check
U8 gu8HeaterWatt_CheckTime;
U8 gu8_damaged_heater_timer;
bit bit_check_damage;
//bit bit_damaged_heater_error_fixed;
bit bit_damaged_heater_error_once;

//function Cal_HotFlowHz
U8 gu8_heater_increase_cnt;
U16 gu16_flow_inc_timer;
U16 gu16_flow_dec_timer;
S8 gs8_flow_inc;
U16 Target_Flow_Q;
U8 gu8_hot_setting_temperature;

//function heating_control
U8 gu8_heater_full_timer;
U8 gu8_low_flow_timer;

//function main_heating_control
S8 gs8_adjust_heater_power;
U8 gu8_adjust_heater_timer;

//function calc_heater_out
U16 u16TargetHeaterPower;

//function update_max_flow
U8 gu8_max_flow_update_timer;
U8 gu8_max_flow;

//function preheating_flow_control
U8 bit_first_adjust;

//function calc_heater_out
U8 u8Heater_1stepWatt;

//function set_target_temperature
U16 u16Heater_Power;

HOT_TEMP_LEVEL selected_hot_temp[4];
U8 gu8_hot_water_select_index;          /* CH.PARK ADDED */

TYPE_BYTE          U8IceHeaterONB;
#define            u8IceHeaterON                         U8IceHeaterONB.byte
#define            Bit0_Ice_Making_Heater_On_State       U8IceHeaterONB.Bit.b0
#define            Bit1_Over_Ice_Melt_State              U8IceHeaterONB.Bit.b1
#define            Bit2_Ice_Make_Init_On_State           U8IceHeaterONB.Bit.b2



TYPE_BYTE          U8IceHeaterOFFB;
#define            u8IceHeaterOFF                        U8IceHeaterOFFB.byte
#define            Bit0_Ice_Disable_Error_Off_State      U8IceHeaterOFFB.Bit.b0
#define            Bit1_Tray_Dual_Error_Check_State      U8IceHeaterOFFB.Bit.b1
#define            Bit2_Tray_Move_Error_State            U8IceHeaterOFFB.Bit.b2
#define            Bit3_Non_Ice_Make_State               U8IceHeaterOFFB.Bit.b3



TYPE_WORD          U16HotHeaterOnW;
#define            u16HotHeaterOn                            U16HotHeaterOnW.word
#define            u16HotHeater_L                            U16HotHeaterOnW.byte[0]
#define            u16HotHeater_H                            U16HotHeaterOnW.byte[1]
#define            Bit0_Hot_Heating_State                    U16HotHeaterOnW.Bit.b0





TYPE_WORD          U16HotHeaterOffW;
#define            u16HotHeaterOff                           U16HotHeaterOffW.word
#define            u16HotHeaterOff_L                         U16HotHeaterOffW.byte[0]
#define            u16HotHeaterOff_H                         U16HotHeaterOffW.byte[1]
#define            Bit0_First_Low_Water_State                U16HotHeaterOffW.Bit.b0
#define            Bit1_Hot_Setting_Off_State                U16HotHeaterOffW.Bit.b1
#define            Bit2_Hot_Error_State                      U16HotHeaterOffW.Bit.b2
#define            Bit3_Low_Water_Error_State                U16HotHeaterOffW.Bit.b3
#define            Bit4_Room_Over_Heat_State                 U16HotHeaterOffW.Bit.b4
#define            Bit5_Hot_Safety_State                     U16HotHeaterOffW.Bit.b5
#define            Bit6_Hot_Ster_State                       U16HotHeaterOffW.Bit.b6

TYPE_WORD          U16HotTemplSelectW;
#define            U16HotTemplSelect							U16HotTemplSelectW.word
#define            U16HotTemplSelect_L							U16HotTemplSelectW.byte[0]
#define            U16HotTemplSelect_H							U16HotTemplSelectW.byte[1]
#define            Bit0_Temp_Select__45oC						U16HotTemplSelectW.Bit.b0
#define            Bit1_Temp_Select__50oC						U16HotTemplSelectW.Bit.b1
#define            Bit2_Temp_Select__55oC						U16HotTemplSelectW.Bit.b2
#define            Bit3_Temp_Select__60oC						U16HotTemplSelectW.Bit.b3
#define            Bit4_Temp_Select__65oC						U16HotTemplSelectW.Bit.b4
#define            Bit5_Temp_Select__70oC						U16HotTemplSelectW.Bit.b5
#define            Bit6_Temp_Select__75oC						U16HotTemplSelectW.Bit.b6
#define            Bit7_Temp_Select__80oC						U16HotTemplSelectW.Bit.b7
#define            Bit8_Temp_Select__85oC						U16HotTemplSelectW.Bit.b8
#define            Bit9_Temp_Select__90oC						U16HotTemplSelectW.Bit.b9
#define            Bit10_Temp_Select__95oC						U16HotTemplSelectW.Bit.b10
#define            Bit11_Temp_Select__100oC             		U16HotTemplSelectW.Bit.b11

//init flow valve()
bit bit_init_flow_valve;

// ★2025-06-11 Phil after PM
extern TYPE_WORD          U16HotInFeed9ValveONB;
#define            u16HotInFeed9ValveONs                        U16HotInFeed9ValveONB.word
#define            u8HotInFeed9ValveONs_L                       U16HotInFeed9ValveONB.byte[0]
#define            u8HotInFeed9ValveONs_H                       U16HotInFeed9ValveONB.byte[1]
#define            Bit0_HIF9_Water_Filling_State                U16HotInFeed9ValveONB.Bit.b0
#define            Bit1_HIF9_Hot_Out_State                      U16HotInFeed9ValveONB.Bit.b1
#define            Bit2_HIF9_Ice_Tray_Ster_State                U16HotInFeed9ValveONB.Bit.b2
// ★2025-06-11 Phil after PM


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Heating_Control(void)
{
	if(gu8_hot_drain_cold == SET)
	{
        /* do nothing */
	}
	else
	{
		flow_valve_control();
		Water_Heater_Control();
	}
    update_max_flow();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flow_valve_control(void)
{
    init_flow_valve();
    control_flow_valve();
    /*..hui [25-4-10오후 1:45:11] 트레이 살균할때는 따로 제어..*/
    control_tray_ster_flow_valve();

    ControlFlow();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_flow_valve(void)
{
    if( F_WaterOut == SET )
    {
        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            if( gu8_Water_Out_Step >= STATE_31_WATER_EXTRACT_STATE )
            /*if( gu8_Water_Out_Step >= STATE_20_HOT_PRE_HEATING_STATE )*/
            {
            	/*sean [25-05-08] 초기화 안시키고 보기위해서 처음만 초기화 하도록 변경*/
                //bit_init_flow_valve = SET;
            }
            else{}
        }
        else{}
    }
    else if( bit_ice_tank_ster_start == SET && gu8_ice_ster_mode >= STER_MODE_HOT_PREHEAT )
    {
        /*..hui [25-4-10오후 1:50:37] 트레이 세척 끝나고 초기화..*/
        bit_init_flow_valve = SET;
    }
    else
    {
        if( bit_init_flow_valve == SET )
        {
            bit_init_flow_valve = CLEAR;
            run_init_flow();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void control_flow_valve(void)
{
    U16 mu16_adjust = 0;
    U8 mu8_target = 0;

    if( F_WaterOut == SET
        && u8WaterOutState == HOT_WATER_SELECT
        /*&& F_First_Hot_Effluent == CLEAR*/ )
    {
//// ★2025-06-11 Phil after PM
        if(( gu8_Water_Out_Step == STATE_20_HOT_PRE_HEATING_STATE
			&& Bit1_HIF9_Hot_Out_State == F_WaterOut	)									// 예열중에도 온수 입수밸브가 개방되면 유량 조절
            && gu8_Preheat_Step >= STATE_2_PREHEAT_DRAIN_STATE)         //2025-07-14 cbr 최초 출수 유량 increase 과한 조건 개선
        {
			preheating_variable_flow_control();
        }
//// ★2025-06-11 Phil after PM

        //if( gu8_Water_Out_Step == STATE_20_HOT_PRE_HEATING_STATE )
        //if( gu8_Water_Out_Step >= STATE_20_HOT_PRE_HEATING_STATE
        if( gu8_Water_Out_Step >= STATE_21_HOT_PRE_HEATING_BUFFER_DRAIN_STATE       // ★ 2025-06-11 Phil
			&& gu8_Water_Out_Step < STATE_30_EXTRACT_VALVE_ON_STATE)
        {
            //preheating_flow_control();
			preheating_variable_flow_control();
        }
        else if( gu8_Water_Out_Step >= STATE_30_EXTRACT_VALVE_ON_STATE
                 && gu8_Water_Out_Step < STATE_40_EXTRACT_VALVE_OFF_STATE )
        {
            mainheating_flow_control();
        }
        else{}
    }
    // ★2025-06-20 phil    //2025-07-11 cbr
    else if(gu8_flushing_mode == FLUSHING_FILL_HOT_TANK_STATE && gu8_Hot_Filling_Step == 6)
    {
			preheating_variable_flow_control();
    }
    // ★2025-06-20 phil
    else
    {
        bit_first_adjust = CLEAR;
        gu8_flow_control_timer = 0;
    }
}

U16 gu16_preheat_adjust_val;
U8 gu8_dbg_flow_skip;
void preheating_flow_control(void)
{
    U16 mu16_adjust = 0;
    U8 mu8_target = 0;

	//gu8_hot_filling_max_hz = 52;

    if( gu8_Preheat_Step < STATE_2_PREHEAT_DRAIN_STATE || bit_first_adjust == SET )
    {
    	gu8_dbg_flow_skip = SET;
        return;
    }
    else
	{
		gu8_dbg_flow_skip = CLEAR;
	}

    /*..hui [21-8-31오후 4:48:33] 20psi == 47..*/
    /*..hui [21-9-1오후 4:04:28] 40psi == 73..*/
    /*..hui [21-9-1오후 4:17:39] 60psi == 90..*/
    //if(0)
    if(u16Heater_Power_Save <= HEATER_POWER_LOW)
    {
        if( gu8_drain_max_flow <= 11 ) //gu8_drain_max_flow 수압세팅시 필요.
        {
            gu16_preheat_adjust_val = 250;
        }
        else if( gu8_hot_filling_max_hz <= 60 )
        {
            if( gu8_Hot_In_Temperature_One_Degree >= 25 )
            {
                gu16_preheat_adjust_val = 250;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 15 )
            {
                // mu16_adjust = 350;
                // [25-02-21 08:24:07] yspark, 조정값 변경
                //gu16_preheat_adjust_val = 550;
                // [25-04-15] sean, 조정값 변경
                gu16_preheat_adjust_val = 1210;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 10 )
            {
                // mu16_adjust = 350;
                // [25-03-27 ] sean, 10도 추가 조정값 변경
                gu16_preheat_adjust_val = 1410;
            }
            else
            {
                // [25-03-27 ] sean, 10도 추가 조정값 변경
                gu16_preheat_adjust_val = 1510;
            }
        }
        else if( gu8_hot_filling_max_hz <= 80 )
        {
            if( gu8_Hot_In_Temperature_One_Degree >= 25 )
            {
                gu16_preheat_adjust_val = 950;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 15 )
            {
                // [25-02-21 08:24:07] yspark, 조정값 변경
                // mu16_adjust = 550;
                // [25-03-27 ] sean, 10도 추가 조정값 변경
                gu16_preheat_adjust_val = 1370;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 10 )
            {
                // mu16_adjust = 350;
                // [25-03-27 ] sean, 10도 추가 조정값 변경
                gu16_preheat_adjust_val = 1470;
            }
            else
            {
                gu16_preheat_adjust_val = 1570;
            }
        }
        else // ( gu8_hot_filling_max_hz > 80 )
        {
            if( gu8_Hot_In_Temperature_One_Degree >= 25 )
            {
                gu16_preheat_adjust_val = 650;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 15 )
            {
                // mu16_adjust = 750;
                // [25-02-21 08:25:10] yspark, 조정값 변경
                gu16_preheat_adjust_val = 1380;
                // [25-03-27 ] sean, 10도 추가 조정값 변경
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 10 )
            {
                // mu16_adjust = 350;
                // [25-03-27 ] sean, 10도 추가 조정값 변경
                gu16_preheat_adjust_val = 1530;
                // [25-03-27 ] sean, 10도 추가 조정값 변경
            }
            else
            {
                gu16_preheat_adjust_val = 1580;
                // [25-03-27 ] sean, 10도 추가 조정값 변경
            }
        }
    }
    else if(u16Heater_Power_Save < HEATER_POWER_HIGH)
    {
        if( gu8_hot_filling_max_hz <= 60 )
        {
            if( gu8_Hot_In_Temperature_One_Degree >= 25 )
            {
                //mu16_adjust = 50;
  			    gu16_preheat_adjust_val = 720;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 15 )
            {
                //mu16_adjust = 70;
  			    // mu16_adjust = 650;
                // [25-02-21 08:25:48] yspark, 조정값 변경
  			    //gu16_preheat_adjust_val = 800;
                // [25-04-10 08:25:48] sean, 조정값 변경
  			    //gu16_preheat_adjust_val = 1120;
  			    gu16_preheat_adjust_val = 920;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 10 )
            {
                // mu16_adjust = 350;
                // [25-03-27 ] sean, 10도 추가 조정값 변경
                //gu16_preheat_adjust_val = 1220;
                gu16_preheat_adjust_val = 1120;
            }
            else
            {
                //mu16_adjust = 90;
  			    gu16_preheat_adjust_val = 920;
            }
        }
        else if( gu8_hot_filling_max_hz <= 80 )
        {
            if( gu8_Hot_In_Temperature_One_Degree >= 25 )
            {
                gu16_preheat_adjust_val = 100;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 15 )
            {
                // mu16_adjust = 250;
                // [25-02-21 08:26:10] yspark, 조정값 변경
  			    //gu16_preheat_adjust_val = 800;
                // [25-04-10 08:25:48] sean, 조정값 변경
  			    gu16_preheat_adjust_val = 830;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 10 )
            {
                // mu16_adjust = 250;
                // [25-02-21 08:26:10] yspark, 조정값 변경
                gu16_preheat_adjust_val = 930;
            }
            else
            {
                gu16_preheat_adjust_val = 1030;
            }

        }
        else // if( gu8_hot_filling_max_hz > 80 )
        {
            if( gu8_Hot_In_Temperature_One_Degree >= 25 )
            {
                gu16_preheat_adjust_val = 300;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 15 )
            {
                // mu16_adjust = 350;
                // [25-02-21 08:26:34] yspark, 조정값 변경
  			    //gu16_preheat_adjust_val = 800;
                // [25-04-10 08:25:48] sean, 조정값 변경
  			    gu16_preheat_adjust_val = 840;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 10 )
            {
                // mu16_adjust = 250;
                // [25-02-21 08:26:10] yspark, 조정값 변경
                // [25-04-10 08:25:48] sean, 조정값 변경
                gu16_preheat_adjust_val = 940;
            }
            else
            {
                gu16_preheat_adjust_val = 1040;
            }
        }
    }
    else // (u16Heater_Power_Save > HEATER_POWER_HIGH)
    {
        if( gu8_hot_filling_max_hz <= 60 )
        {
            if( gu8_Hot_In_Temperature_One_Degree >= 25 )
            {
                //mu16_adjust = 50;
  			    //gu16_preheat_adjust_val = 150;
  			    gu16_preheat_adjust_val = 550;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 15 )
            {
                //mu16_adjust = 70;
  			    // mu16_adjust = 650;
                // [25-02-21 08:25:48] yspark, 조정값 변경
  			    //gu16_preheat_adjust_val = 800;
                // [25-04-10 08:25:48] sean, 조정값 변경
  			    //gu16_preheat_adjust_val = 1120;
  			    //gu16_preheat_adjust_val = 220;
  			    gu16_preheat_adjust_val = 620;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 10 )
            {
                // mu16_adjust = 350;
                // [25-03-27 ] sean, 10도 추가 조정값 변경
                //gu16_preheat_adjust_val = 1220;
                //gu16_preheat_adjust_val = 320;
  			    gu16_preheat_adjust_val = 650;
            }
            else
            {
                //mu16_adjust = 90;
  			    //gu16_preheat_adjust_val = 420;
  			    gu16_preheat_adjust_val = 750;
            }
        }
        else if( gu8_hot_filling_max_hz <= 80 )
        {
            if( gu8_Hot_In_Temperature_One_Degree >= 25 )
            {
                //gu16_preheat_adjust_val = 250;
  			    gu16_preheat_adjust_val = 650;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 15 )
            {
                // mu16_adjust = 250;
                // [25-02-21 08:26:10] yspark, 조정값 변경
  			    //gu16_preheat_adjust_val = 800;
                // [25-04-10 08:25:48] sean, 조정값 변경
  			    //gu16_preheat_adjust_val = 430;
  			    gu16_preheat_adjust_val = 630;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 10 )
            {
                // mu16_adjust = 250;
                // [25-02-21 08:26:10] yspark, 조정값 변경
                //gu16_preheat_adjust_val = 530;
  			    gu16_preheat_adjust_val = 680;
            }
            else
            {
                //gu16_preheat_adjust_val = 630;
  			    gu16_preheat_adjust_val = 730;
            }

        }
        else // if( gu8_hot_filling_max_hz > 80 )
        {
            if( gu8_Hot_In_Temperature_One_Degree >= 25 )
            {
                //gu16_preheat_adjust_val = 350;
  			    gu16_preheat_adjust_val = 750;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 15 )
            {
                // mu16_adjust = 350;
                // [25-02-21 08:26:34] yspark, 조정값 변경
  			    //gu16_preheat_adjust_val = 800;
                // [25-04-10 08:25:48] sean, 조정값 변경
  			    gu16_preheat_adjust_val = 540;
            }
            else if( gu8_Hot_In_Temperature_One_Degree >= 10 )
            {
                // mu16_adjust = 250;
                // [25-02-21 08:26:10] yspark, 조정값 변경
                // [25-04-10 08:25:48] sean, 조정값 변경
                gu16_preheat_adjust_val = 640;
            }
            else
            {
                gu16_preheat_adjust_val = 740;
            }
        }
    }

    run_decrease_flow( gu16_preheat_adjust_val );

    bit_first_adjust = SET;
}

U8 gu8_PreHeat_Flow_target;
void preheating_variable_flow_control(void)
{
    U16 mu16_adjust = 0;
    //U8 mu8_target = 0;
    U8 mu8_stable_timr = 0;

    if(u16Heater_Power_Save <= HEATER_POWER_HIGH)
    {
    	/*..sean [25-05-12] 90/95도 해당 제어 동일하게 적용..*/
        if( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )  )
        {
            //gu8_MainHeat_Flow_target = u8Target_Hz_Hot;
            gu8_PreHeat_Flow_target = u8Target_Hz_Hot - 3;
        }
        else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
        {
            //gu8_MainHeat_Flow_target = u8Target_Hz_Hot;
// ★2025-06-02 Phil
            //gu8_PreHeat_Flow_target = u8Target_Hz_Hot - 1;// ★2025-06-02 Phil

            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {
                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    gu8_PreHeat_Flow_target = u8Target_Hz_Hot - 1;
                }
                else
                { // 첫째 잔
                    gu8_PreHeat_Flow_target = u8Target_Hz_Hot - 3;
                }
            }
            else
            {
            	gu8_PreHeat_Flow_target = u8Target_Hz_Hot - 1;
            }
// ★2025-06-02 Phil
        }
        else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
        {
            gu8_PreHeat_Flow_target = u8Target_Hz_Hot;
        }
        else
        {
            gu8_PreHeat_Flow_target = u8Target_Hz_Hot;
        }
    }
    else
    {
#if 1
		if( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )  )
        {
            gu8_PreHeat_Flow_target = u8Target_Hz_Hot - 2;
        }
		else
		{
        	gu8_PreHeat_Flow_target = u8Target_Hz_Hot;
		}
#endif
		//gu8_MainHeat_Flow_target = u8Target_Hz_Hot;
    }
    // [25-05-27 14:54:03] 유량 protection 추가
    if(u8Target_Hz_Hot <= C_033_LPM)
    {
        u8Target_Hz_Hot = C_033_LPM;
    }
    else if( u8Target_Hz_Hot >= C_07_LPM)
    {
        u8Target_Hz_Hot = C_07_LPM;
    }
    else{}


    /*..hui [21-8-31占쏙옙占쏙옙 4:48:33] 20psi == 47..*/
    if( gu8_hot_filling_max_hz <= 60 )
    {
        if( u8Target_Hz_Hot >= C_05_LPM )
        {
            if(gu8_Flow_1sec >= u8Target_Hz_Hot + 10
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 10)
            {
                mu16_adjust = 100;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 8
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 8)
            {
                mu16_adjust = 80;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 6
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 6)
            {
                mu16_adjust = 40;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 4
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 4)
            {
                mu16_adjust = 20;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 2
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 2)
            {
                mu16_adjust = 15;
            }
            else
            {
                mu16_adjust = 5;
            }
        }
        else // ( u8Target_Hz_Hot < C_05_LPM )
        {
            if(gu8_Flow_1sec >= u8Target_Hz_Hot + 10
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 10)
            {
                mu16_adjust = 100;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 8
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 8)
            {
                mu16_adjust = 80;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 6
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 6)
            {
                mu16_adjust = 60;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 4
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 4)
            {
                mu16_adjust = 40;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 2
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 2)
            {
                mu16_adjust = 20;
            }
            else
            {
                mu16_adjust = 5;
            }
        }
    }
    else // ( gu8_hot_filling_max_hz > 60 )
    {
        if(gu8_Flow_1sec >= u8Target_Hz_Hot + 10
           || gu8_Flow_1sec <= u8Target_Hz_Hot - 10)
        {
            mu16_adjust = 100;
        }
        else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 8
           || gu8_Flow_1sec <= u8Target_Hz_Hot - 8)
        {
            mu16_adjust = 80;
        }
        else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 6
           || gu8_Flow_1sec <= u8Target_Hz_Hot - 6)
        {
            mu16_adjust = 60;
        }
        else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 4
           || gu8_Flow_1sec <= u8Target_Hz_Hot - 4)
        {
            mu16_adjust = 40;
        }
        else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 2
           || gu8_Flow_1sec <= u8Target_Hz_Hot - 2)
        {
            mu16_adjust = 20;
        }
        else
        {
            mu16_adjust = 5;
        }
    }
    //2025-07-14 cbr_test   첫 추출 시 유량0일때 펄스 100 들어가서 과하게 increase됨.
    if((!F_firstEffluent_hotWater && gu8_Flow_1sec < 18)
        && (F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT))
    {
        mu16_adjust = (mu16_adjust / 3);
    }
    else{}  //2025-07-14 cbr_test

    if( gu8_Hot_Heater_Temperature_One_Degree >= 95 )
    {
        mu8_stable_timr = 1;
    }
    else if( gu8_Flow_1sec <= 12 )
    {
        mu8_stable_timr = 1;
    }
    else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
    {
        /*mu8_stable_timr = 7;*/
        /*mu8_stable_timr = 5;*/
        mu8_stable_timr = 2;
    }
    else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____55oC)
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____50oC )
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC ) )
    {
        /*mu8_stable_timr = 7;*/
        /*mu8_stable_timr = 5;*/
        mu8_stable_timr = 4;
    }
    else
    {
        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {
            mu8_stable_timr = 1;
        }
        else
        {
            mu8_stable_timr = 2;   //FLOW_STABLE_TIME;
        }
    }

    if( gu8_hot_flow_mode == FLOW_MODE_NONE  )
    {
        gu8_flow_control_timer++;

        if( gu8_flow_control_timer >= mu8_stable_timr )
        {
            /*gu8_flow_control_timer = FLOW_STABLE_TIME;*/
            gu8_flow_control_timer = mu8_stable_timr;
        }
        else
        {
            return;
        }
    }
    else
    {
        gu8_flow_control_timer = 0;
        return;
    }


    if( gu8_Flow_1sec > gu8_PreHeat_Flow_target + 1 )
    {
    	if(gu8_Flow_1sec > C_03_LPM)
    	{
        	run_decrease_flow( mu16_adjust );
    	}
		else {}
    }
    else if( (gu8_Flow_1sec < gu8_PreHeat_Flow_target - 1) && (gu8_Flow_1sec >= 10))    //2025-07-17 cbr decrease 후 16에서 멈추는 현상
    {
        run_increase_flow( mu16_adjust );
    }
    else{}
}

U8 gu8_MainHeat_Flow_target;
void mainheating_flow_control(void)
{
    U16 mu16_adjust = 0;
    //U8 mu8_target = 0;
    U8 mu8_stable_timr = 0;

    if(u16Heater_Power_Save <= HEATER_POWER_HIGH)
    {
        if (u16Heater_Power_Save < HEATER_POWER_LOW)
        {
            if( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )  )
            {
                //gu8_MainHeat_Flow_target = u8Target_Hz_Hot;
                gu8_MainHeat_Flow_target = u8Target_Hz_Hot - 1;
            }
            else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
                || ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
            {
                //gu8_MainHeat_Flow_target = u8Target_Hz_Hot;
                gu8_MainHeat_Flow_target = u8Target_Hz_Hot - 1;
            }
            else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
            {
                gu8_MainHeat_Flow_target = u8Target_Hz_Hot;
            }
            else
            {
                gu8_MainHeat_Flow_target = u8Target_Hz_Hot;
            }
        }
        else
        {
            if( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )  )
            {
                //cbr
                if(gu8_Hot_In_Temperature_One_Degree <= 15)
                {
                    gu8_MainHeat_Flow_target = u8Target_Hz_Hot + 0;
                    //gu8_MainHeat_Flow_target = u8Target_Hz_Hot - 1;
                }else
                {
                    gu8_MainHeat_Flow_target = u8Target_Hz_Hot - 2;
                }
            }
            else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
                || ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
            {
                //gu8_MainHeat_Flow_target = u8Target_Hz_Hot;
                gu8_MainHeat_Flow_target = u8Target_Hz_Hot - 1;
            }
            else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
            {
                gu8_MainHeat_Flow_target = u8Target_Hz_Hot;
            }
            else
            {
                gu8_MainHeat_Flow_target = u8Target_Hz_Hot;
            }
        }
    }
    else
    {
#if 1
		if( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )  )
        {
            gu8_MainHeat_Flow_target = u8Target_Hz_Hot - 2;
        }
		else
		{
        	gu8_MainHeat_Flow_target = u8Target_Hz_Hot;
		}
#endif
		//gu8_MainHeat_Flow_target = u8Target_Hz_Hot;
    }


    /*..hui [21-8-31占쏙옙占쏙옙 4:48:33] 20psi == 47..*/
    if( gu8_hot_filling_max_hz <= 60 )
    {
        if( u8Target_Hz_Hot >= C_05_LPM )
        {
            if(gu8_Flow_1sec >= u8Target_Hz_Hot + 10
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 10)
            {
                mu16_adjust = 100;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 8
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 8)
            {
                mu16_adjust = 80;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 6
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 6)
            {
                mu16_adjust = 40;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 4
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 4)
            {
                mu16_adjust = 20;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 2
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 2)
            {
                mu16_adjust = 15;
            }
            else
            {
                mu16_adjust = 5;
            }
        }
        else // ( u8Target_Hz_Hot < C_05_LPM )
        {
            if(gu8_Flow_1sec >= u8Target_Hz_Hot + 10
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 10)
            {
                mu16_adjust = 100;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 8
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 8)
            {
                mu16_adjust = 80;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 6
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 6)
            {
                mu16_adjust = 60;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 4
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 4)
            {
                mu16_adjust = 40;
            }
            else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 2
               || gu8_Flow_1sec <= u8Target_Hz_Hot - 2)
            {
                mu16_adjust = 20;
            }
            else
            {
                mu16_adjust = 5;
            }
        }
    }
    else // ( gu8_hot_filling_max_hz > 60 )
    {
        if(gu8_Flow_1sec >= u8Target_Hz_Hot + 10
           || gu8_Flow_1sec <= u8Target_Hz_Hot - 10)
        {
            mu16_adjust = 100;
        }
        else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 8
           || gu8_Flow_1sec <= u8Target_Hz_Hot - 8)
        {
            mu16_adjust = 80;
        }
        else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 6
           || gu8_Flow_1sec <= u8Target_Hz_Hot - 6)
        {
            mu16_adjust = 60;
        }
        else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 4
           || gu8_Flow_1sec <= u8Target_Hz_Hot - 4)
        {
            mu16_adjust = 40;
        }
        else if(gu8_Flow_1sec >= u8Target_Hz_Hot + 2
           || gu8_Flow_1sec <= u8Target_Hz_Hot - 2)
        {
            mu16_adjust = 20;
        }
        else
        {
            mu16_adjust = 5;
        }
    }


    //if( u16Heater_Power_Save <= HEATER_POWER_LOW
    //    && gu8_Hot_Heater_Temperature_One_Degree >= 95 )
    //{
    //    mu8_stable_timr = 5;
    //}

    if( gu8_Hot_Heater_Temperature_One_Degree >= 95 )
    {
        #if 0
        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {
            mu8_stable_timr = 1;
        }
        else
        {
            mu8_stable_timr = 2;
        }
        #endif

        mu8_stable_timr = 1;
    }
    else if( gu8_Flow_1sec <= 12 )
    {
        mu8_stable_timr = 1;
    }
    else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
    {
        /*mu8_stable_timr = 7;*/
        /*mu8_stable_timr = 5;*/
        mu8_stable_timr = 4;
    }
    else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____55oC)
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____50oC )
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC ) )
    {
        /*mu8_stable_timr = 7;*/
        /*mu8_stable_timr = 5;*/
        mu8_stable_timr = 4;
    }
    else
    {
        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {
            mu8_stable_timr = 1;
        }
        else
        {
            mu8_stable_timr = 2;   //FLOW_STABLE_TIME;
        }
    }

    if( gu8_hot_flow_mode == FLOW_MODE_NONE  )
    {
        gu8_flow_control_timer++;

        if( gu8_flow_control_timer >= mu8_stable_timr )
        {
            /*gu8_flow_control_timer = FLOW_STABLE_TIME;*/
            gu8_flow_control_timer = mu8_stable_timr;
        }
        else
        {
            return;
        }
    }
    else
    {
        gu8_flow_control_timer = 0;
        return;
    }


    if( gu8_Flow_1sec > gu8_MainHeat_Flow_target + 1 )
    {
    	if(gu8_Flow_1sec > C_03_LPM)
    	{
        	run_decrease_flow( mu16_adjust );
    	}
		else {}
    }
    else if( (gu8_Flow_1sec < gu8_MainHeat_Flow_target - 1 ) && (gu8_Flow_1sec >= 10))  //2025-07-17 cbr decrease 후 16에서 멈추는 현상
    {
        run_increase_flow( mu16_adjust );
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Water_Heater_Control(void)
{
    if( bit_ice_tank_ster_start == CLEAR )
    {
        set_target_temperature();
        normal_heater_watt_check();
        Cal_HotFlowHz();
        heating_control();
    }
    else
    {
        heating_control_tray_ster();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void set_target_temperature(void)
{
    if (gu8_Hot_In_Temperature_One_Degree <= 15)
    {  // 15도
        SetTargetTempUnder_15();
    }
    else if (gu8_Hot_In_Temperature_One_Degree <= 25)
    {  // 상시
        SetTargetTempUnder_25();
    }
    else
    {  // 25도 이상
        SetTargetTempExtra();
    }

    //gu8_min_power = 45;

    if( (gu8_hot_setting_temperature == HOT_SET_TEMP____55oC)
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____50oC )
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC ) )
    {
        gu8_min_power = 40;
    }
    else
    {
        //gu8_min_power = 45;
        /*.. sean [25-5-8] 최소 히터 출력을 45에서 60으로 변경..*/
        gu8_min_power = 60;
    }
}
// [25-02-20 13:27:42] yspark, 테스트 변수 생성
U16 Testgu16PowerMaxValue = 0;

void Cal_HeaterWatt(void)
{
    U32 a = 0;
    U32 b = 0;
    U32 c = 0;

    #if 0
    /*..hui [21-2-19占쏙옙占쏙옙 3:05:51] AIS3.0 - 占쏙옙占쏙옙占쏙옙占쏙옙 2720W..*/
    if(gu16_AD_Result_Heater_Current_Feed >= 100)
    {
        a = (U32)gu16_AD_Result_Heater_Current_Feed;
        b = (U32)((455 * a) / 100);
        c = (U32)(b - 1510);
    }
    else{}
    #endif

    #if 0
    if(gu16_AD_Result_Heater_Current_Feed >= 450)
    {
        a = (U32)gu16_AD_Result_Heater_Current_Feed;
        b = (U32)((780 * a) / 100);
        c = (U32)(b - 1341);
    }
    else{}
    #endif

    // if(gu16_AD_Result_Heater_Current_Feed >= 400)
    // {
    //     a = (U32)gu16_AD_Result_Heater_Current_Feed;
    //     b = (U32)((830 * a) / 100);
    //     /*c = (U32)(b - 1419);*/
    //     /*c = (U32)(b - 1400);*/
    //     /*c = (U32)(b - 1300);*/
    //     /*c = (U32)(b - 1419);*/
    //     /*c = (U32)(b - 1500);*/
    //     c = (U32)(b - 1520);
    // }
    // else{}

    // [25-02-20 14:06:19] yspark 실험 값
    a = (U32)gu16_AD_Result_Heater_Current_Feed;
    b = (U32)((6937 * a) / 1000);
    c = (U32) (b - 685 + 50);

    u16Heater_Power = (U16)c;

    // [25-02-20 13:28:05] yspark, 최대 전력값 저장
    if (u16Heater_Power >= Testgu16PowerMaxValue)
    {
        Testgu16PowerMaxValue = u16Heater_Power;
    }

    if( u16Heater_Power >= C_Heater_Min_Power )
    {
        u16Heater_Power_Save = u16Heater_Power;
    }
    else
    {
        /*..hui [20-4-22占쏙옙占쏙옙 4:22:00] 占쏙옙占쏙옙 占쏙옙占쏘날占쌤울옙 占쌍소뤄옙 占쏙옙占쏙옙..*/
        u16Heater_Power_Save = C_Heater_Min_Power;
    }

    /*..hui [19-1-24占쏙옙占쏙옙 1:42:36] AD占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占싫될곤옙占?Default 占쏙옙 占쏙옙占쏙옙..*/
    if(u16Heater_Power_Save <= C_Heater_Min_Power)
    {
        u16Heater_Power_Save = C_Heater_Min_Power;
    }
    else
    {
        if(u16Heater_Power_Save >= C_Heater_Max_Power)
        {
            u16Heater_Power_Save = C_Heater_Max_Power;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void normal_heater_watt_check(void)
{
    U8 mu8_disable = CLEAR;

	//u16Heater_Power_Save = 2800;

    if(F_WaterOut != SET)
    {
        mu8_disable = SET;
    }
    else{}

    if(u8WaterOutState != HOT_WATER_SELECT)
    {
        mu8_disable = SET;
    }
    else{}

    if( mu8_disable == CLEAR )
    {
        if(pHEATER_HOT_H_RELAY == SET && pHEATER_HOT_TRIAC_L == SET && gu8TriacLevelMax == STEP_TRIAC)
        {
            gu8HeaterWatt_CheckTime++;

            if(gu8HeaterWatt_CheckTime >= 10)
            {
                gu8HeaterWatt_CheckTime = 10;
                Cal_HeaterWatt();
            }
            else{}
        }
        else
        {
            gu8HeaterWatt_CheckTime = 0;
        }
    }
    else
    {
        gu8HeaterWatt_CheckTime = 0;
        bit_check_damage = CLEAR;
        gu8_damaged_heater_timer = 0;
        bit_damaged_heater_error_once = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/*------------------------------------------------------------------------------
                            Cal_HotFlowHz()
//占승쇽옙 占쏙옙占썩에 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙究占쏙옙占??
//占쏙옙표: 0.29LPM -> 290ml/min
--------------------------------------------------------------------------------*/
U16 gu16_effluent_hot;      //2025-07-31 cbr
void Cal_HotFlowHz(void)
{
    U32 a = 0;
    U32 b = 0;
    U32 c = 0;
    U32 d = 0;
    U32 e = 0;
    U8 mu8_target = 0;
    U8 mu8_flow_inc_time = 0;
    U8 mu8_flow_dec_time = 0;

    if(F_WaterOut != SET)
    {
        //u8HeaterCompensation = 0;
        gu8_heater_increase_cnt = 0;

        gu16_flow_dec_timer = 0;
        gu16_flow_inc_timer = 0;
        gs8_flow_inc = 0;

        return;
    }
    else{}

    if(u8WaterOutState != HOT_WATER_SELECT)
    {
        return;
    }
    else{}
#if 0
    // [25-02-20 14:35:26] yspark, 풀 출력일 때만 계산
    if ((pHEATER_HOT_H_RELAY == SET && pHEATER_HOT_TRIAC_L == SET && gu8TriacLevelMax == STEP_TRIAC) == 0)
    {
        return;
    }
#endif
// [25-05-23 16:01:05] yspark, 수정
// Target 유량을 통일화 하기 위해서 수정
    // if( gu8_Water_Out_Step == STATE_20_HOT_PRE_HEATING_STATE )
    // {
    //     mu8_target = gu8_Hot_Preheat_Temp;
    // }
    // else
    // {
    //     mu8_target = gu8_Hot_Target_Temp;
    // }

    mu8_target = gu8_Hot_Target_Temp;

    if( mu8_target > gu8_Hot_In_Temperature_One_Degree )
    {
        a = (U32)(Heater_Efficiency * 860 * u16Heater_Power_Save)/(U32)1000;
        b = (U32)(mu8_target - gu8_Hot_In_Temperature_One_Degree);
        c = (U32)(a/b);
        d = (U32)(c*1000/60);
    }
    else{}

    Target_Flow_Q = (U16)d;

    // 占쌍쇽옙 占쏙옙占쏙옙치
    if(Target_Flow_Q <= C_Flow_Min_Q)
    {
        Target_Flow_Q = C_Flow_Min_Q;  //占쌍쇽옙 占쏙옙占쏙옙占쏙옙 260占쏙옙占쏙옙 占쏙옙占쏙옙占쌌니댐옙.
    }
    else{}

    /*..hui [19-12-11占쏙옙占쏙옙 3:20:02] 1.0lpm占쏙옙占쏙옙 占쌍댐옙 占쏙옙占쏙옙.. 占쏙옙占쏙옙占시뤄옙 占쏙옙占쏙옙..*/
    if(Target_Flow_Q >= 1044)
    {
        Target_Flow_Q = 1044;
    }
    else{}

    u8Target_Hz_Hot = (U8)(Target_Flow_Q / 18); //20170417
    //u8Target_Hz_Hot = (U8)(Target_Flow_Q / 20); //20250326
    //2025-07-31 cbr
    if(gu8_hot_setting_temperature == HOT_SET_TEMP____45oC)
    {
        // u8Target_Hz_Hot = u8Target_Hz_Hot + 3;
        u8Target_Hz_Hot = u8Target_Hz_Hot + 0;
    }
    else
    {
        if(u8Extract_Continue == SET )
        {
            // u8Target_Hz_Hot = u8Target_Hz_Hot + 5;
            u8Target_Hz_Hot = u8Target_Hz_Hot + 3;
        }
        else if(gu16_effluent_hot >= (U16)(500 * C_CUP_MY_HOT))
        {
            // u8Target_Hz_Hot = u8Target_Hz_Hot + 5;
            u8Target_Hz_Hot = u8Target_Hz_Hot + 3;
        }
        else
        {
            // u8Target_Hz_Hot = u8Target_Hz_Hot + 3;
            u8Target_Hz_Hot = u8Target_Hz_Hot + 0;
        }
    }
    //2025-07-31 cbr

	if(u16Heater_Power_Save <= HEATER_POWER_LOW)
	{
	    if(u8Target_Hz_Hot <= C_033_LPM)
	    {
	        u8Target_Hz_Hot = C_033_LPM;
	    }
	    else if( u8Target_Hz_Hot >= C_07_LPM)
	    {
	        u8Target_Hz_Hot = C_07_LPM;
	    }
	    else{}
	}
	else
	{
	    if(u8Target_Hz_Hot <= C_03_LPM)
	    {
	        u8Target_Hz_Hot = C_03_LPM;
	    }
	    else if( u8Target_Hz_Hot >= C_07_LPM)
	    {
	        u8Target_Hz_Hot = C_07_LPM;
	    }
	    else{}
	}

    /*..hui [19-2-13占쏙옙占쏙옙 10:11:07] 占쌈쏙옙 占쌓쏙옙트占쏙옙..*/
    /*..hui [20-4-8占쏙옙占쏙옙 11:39:11] 占쏙옙占쏙옙占쏙옙占싹뗰옙 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占??占쌩곤옙..*/
    if(u16Heater_Power_Save <= HEATER_POWER_LOW)
    {
        // [25-05-26 17:21:13] yspark, 유량이 너무 작아 수정
        u8Target_Hz_Hot = u8Target_Hz_Hot - 0;

        //2025-07-15 cbr    저전압 20도 고유량 85도 첫잔 미달
        if( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
            || ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
        {
            if(gu8_Hot_In_Temperature_One_Degree <= 25)
            {
                u8Target_Hz_Hot = u8Target_Hz_Hot - 2;
            }
            else{}
        }
        else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
            || ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
            || ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
            || ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
        {
            if( u8Target_Hz_Hot >= C_05_LPM )
            {
                u8Target_Hz_Hot = C_05_LPM;
            }
            else{}
        }
        else if(( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )  )
                && ( gu8_Hot_In_Temperature_One_Degree <= 15 ))
        {
            u8Target_Hz_Hot = u8Target_Hz_Hot + 2;      //2025-07-22 cbr 100도 물끊김
        }
        else{}        //2025-07-15 cbr
    }
    else
    {
        if(u16Heater_Power_Save <= HEATER_POWER_HIGH)
        {
            if( gu8_Hot_In_Temperature_One_Degree <= 15 )
            {
                if( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
                {
                    /*..hui [21-2-26占쏙옙占쏙옙 4:16:47] 占십깍옙 占쏙옙占쏙옙占시곤옙占쏙옙 占쌜곤옙 70占쏙옙占싸곤옙占?占쏙옙占실댐옙 占쏙옙占쏙옙占쏙옙 커占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占싫듸옙..*/
                    /*..hui [21-2-26占쏙옙占쏙옙 4:17:12] 占쏙옙占쏙옙 占쏙옙占쏙옙占쌀쇽옙占쌍듸옙占쏙옙 AIS35占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쌍댐옙 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙..*/
                    if( u8Target_Hz_Hot >= C_05_LPM )
                    {
                        u8Target_Hz_Hot = C_05_LPM;
                    }
                    else{}
                }
                else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
                {
                    u8Target_Hz_Hot = u8Target_Hz_Hot - 1;
                }
                else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC ) )
                // && (u16Heater_Power_Save > HEATER_POWER_LOW) )              //2025-07-28 cbr
                {
                    //u8Target_Hz_Hot = u8Target_Hz_Hot - 1;
                    // u8Target_Hz_Hot = u8Target_Hz_Hot - 4;
                    u8Target_Hz_Hot = u8Target_Hz_Hot - 0;      //2025-07-22 cbr 정격 10도 끊김
                }
                else
                {
                    //u8Target_Hz_Hot = u8Target_Hz_Hot - 1;
                    u8Target_Hz_Hot = u8Target_Hz_Hot;

                }
            }
            else
            {
                //u8Target_Hz_Hot = u8Target_Hz_Hot - 1;
                // u8Target_Hz_Hot = u8Target_Hz_Hot + 2;
// ★2025-06-02 Phil
                //u8Target_Hz_Hot = u8Target_Hz_Hot+1;

                if( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
							|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
							|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )  )
                {
                    //u8Target_Hz_Hot = u8Target_Hz_Hot - 1;
                    u8Target_Hz_Hot = u8Target_Hz_Hot - 2;
                }
                else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
                    || ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC )
                    )
                {       //2025-07-16 cbr    정격 20도(30도?확인필요) 조건 70도 미달(타겟 40hz 측정됨. 28hz로 제한)
                    if( u8Target_Hz_Hot >= C_05_LPM )
                    {
                        u8Target_Hz_Hot = C_05_LPM;
                    }
                    else{}
                }
                //2025-07-29 cbr 80도 정격 20도 고유량 미달 : 유량 조절 필요
                else if((gu8_hot_setting_temperature == HOT_SET_TEMP____80oC)
                    && (gu8_hot_filling_max_hz > u8Target_Hz_Hot)
                    && (gu8_Hot_In_Temperature_One_Degree <= 25))
                {
                    u8Target_Hz_Hot = u8Target_Hz_Hot - 4;
                }
                else
                {
                		u8Target_Hz_Hot = u8Target_Hz_Hot+1;
                }
// ★2025-06-02 Phil
            }
        }
        else// if(u16Heater_Power_Save > HEATER_POWER_HIGH)
    	{
            if( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )  )
            {
                //u8Target_Hz_Hot = u8Target_Hz_Hot - 1;
                //u8Target_Hz_Hot = u8Target_Hz_Hot + 2 ;
                // u8Target_Hz_Hot = u8Target_Hz_Hot;
                if(gu8_Hot_In_Temperature_One_Degree <= 15)
                {
                    u8Target_Hz_Hot = u8Target_Hz_Hot;          //2025-07-18 cbr    10도 고전압 물끊김(유량 적음)
                }
                else if(gu8_Hot_In_Temperature_One_Degree <= 25)
                {
                    u8Target_Hz_Hot = u8Target_Hz_Hot - 4;      //2025-07-15 cbr   고전압 20도 30~33hz 측정, 과함.
                }
                else
                {
                    u8Target_Hz_Hot = u8Target_Hz_Hot - 2;      //2025-07-23 cbr 고전압 30도 물끊김
                }
            }
            else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
            {
                u8Target_Hz_Hot = u8Target_Hz_Hot - 1;
            }
			else
            {
	            if( u8Target_Hz_Hot >= C_05_LPM )
	            {
	                u8Target_Hz_Hot = C_05_LPM;
	            }
	            else{}
        	}
        }
    }

    if( Bit1_Main_Heating_State == SET )
    {
        //if( gu8_Hot_Out_Temperature_One_Degree >= gu8_Hot_Target_Temp - 1 )
        if( gu8_Hot_Out_Temperature_One_Degree >= gu8_Hot_Target_Temp + 2 )
        {
            gu16_flow_inc_timer++;
            gu16_flow_dec_timer = 0;

            if( gu8_Hot_Out_Temperature_One_Degree <= gu8_Hot_Target_Temp + 3 )
            {
                if( gs8_flow_inc < 0 )
                {
                    if( gu8_Hot_In_Temperature_One_Degree <= 15
						&&( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
						|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
						|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )  )
					)
                    {
                        mu8_flow_inc_time = 2;
                    }
                    else if( gu8_Hot_In_Temperature_One_Degree <= 15
						&& ( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
							|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
					)
                    {
                        mu8_flow_inc_time = 5;
                    }
                    else
                    {
                        mu8_flow_inc_time = 10;
                    }
                }
                else
                {
                    mu8_flow_inc_time = 15;
                }
            }
            else
            {
                if( gu8_Hot_In_Temperature_One_Degree <= 15
					&& ( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
						|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
						|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC ) )
					)
                {
                    mu8_flow_inc_time = 1;
                }
                else if( gu8_Hot_In_Temperature_One_Degree <= 15
						&& ( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
							|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
						)
                {
                    mu8_flow_inc_time = 3;
                }
                else
                {
                    //mu8_flow_inc_time = 7;

                    if( u16Heater_Power_Save > HEATER_POWER_LOW
                        && gu8_hot_setting_temperature == HOT_SET_TEMP____45oC )
                    {
                        mu8_flow_dec_time = 3;
                    }
                    else if( u16Heater_Power_Save > HEATER_POWER_LOW
                        && gu8_hot_setting_temperature == HOT_SET_TEMP____50oC )
                    {
                        mu8_flow_dec_time = 3;
                    }
                    else if( u16Heater_Power_Save > HEATER_POWER_LOW
                        && gu8_hot_setting_temperature == HOT_SET_TEMP____55oC )
                    {
                        mu8_flow_dec_time = 3;
                    }
                    else if( u16Heater_Power_Save > HEATER_POWER_LOW
                        && gu8_hot_setting_temperature == HOT_SET_TEMP____60oC )
                    {
                        mu8_flow_dec_time = 3;
                    }
                    else if( u16Heater_Power_Save > HEATER_POWER_LOW
                        && gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
                    {
                        mu8_flow_dec_time = 3;
                    }
                    else if( u16Heater_Power_Save > HEATER_POWER_LOW
                        && gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
                    {
                        mu8_flow_dec_time = 3;
                    }
                    else if( u16Heater_Power_Save > HEATER_POWER_LOW
                        && gu8_hot_setting_temperature == HOT_SET_TEMP____75oC )
                    {
                        mu8_flow_dec_time = 3;
                    }
                    else
                    {
                        mu8_flow_inc_time = 7;
                    }
                }
            }

            if( gu16_flow_inc_timer >= mu8_flow_inc_time )
            {
                gu16_flow_inc_timer = 0;

                gs8_flow_inc = gs8_flow_inc + 1;

                if( gs8_flow_inc >= 4 )
                {
                    gs8_flow_inc = 4;
                }
                else{}
            }
            else{}
        }
        else if( gu8_Hot_Out_Temperature_One_Degree <= gu8_Hot_Target_Temp - 3 )
        {
            if( u16Heater_Power_Save > HEATER_POWER_LOW
                && ( (gu8_hot_setting_temperature == HOT_SET_TEMP____55oC)
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____50oC )
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC ) ) )
            {
                mu8_flow_dec_time = 3;
            }
            else if( u16Heater_Power_Save > HEATER_POWER_LOW
                && ( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) ) )
            {
                mu8_flow_dec_time = 3;
            }
            else
            {
                if( gu8_Hot_Out_Temperature_One_Degree <= gu8_Hot_Target_Temp - 7 )
                {
                    mu8_flow_dec_time = 8;
                }
                else
                {
                    mu8_flow_inc_time = 13;
                }
            }

            gu16_flow_dec_timer++;
            gu16_flow_inc_timer = 0;

            if( gu16_flow_dec_timer >= mu8_flow_inc_time )
            {
                gu16_flow_dec_timer = 0;

                gs8_flow_inc = gs8_flow_inc - 1;

                if( u16Heater_Power_Save <= HEATER_POWER_HIGH
                    && ( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
						|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
						|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )  )
				)
                {
                    if( gs8_flow_inc <= -3 )
                    {
                        gs8_flow_inc = -3;
                    }
                    else{}
                }
				else if( u16Heater_Power_Save <= HEATER_POWER_HIGH
				&& ( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
							|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
						)
				{
					if( gs8_flow_inc <= -3 )
				{
				    gs8_flow_inc = -3;
				}
					else{}
				}
                else
                {
                    if( gs8_flow_inc <= -2 )
                    {
                        gs8_flow_inc = -2;
                    }
                    else{}
                }
            }
            else{}
        }
        else
        {
            gu16_flow_dec_timer = 0;
            gu16_flow_inc_timer = 0;
        }
       u8Target_Hz_Hot = u8Target_Hz_Hot + gs8_flow_inc;
    }
    else{}

		/* sean [25-5-08] Heater 온도가 높아졌을때에는 유량조절하는 부분 Skip	*/
#if 0
        if( gu8_Hot_Out_Temperature_One_Degree >= HOT_TRIAC_OFF_TEMP
            || gu8_Hot_Heater_Temperature_One_Degree >= HOT_TRIAC_OFF_TEMP )
        {
            u8Target_Hz_Hot = C_07_LPM;
        }
        // else if( gu8_Hot_Out_Temperature_One_Degree >= 96
        //     || gu8_Hot_Heater_Temperature_One_Degree >= 96 )
        // {
        //     u8Target_Hz_Hot = C_07_LPM;
        // }
        else
        {
            u8Target_Hz_Hot = u8Target_Hz_Hot + gs8_flow_inc;
        }
    }
    else{}
#endif
#if 0
    /*..hui [21-3-18占쏙옙占쏙옙 5:50:45] 커占쏙옙 占쌉쇽옙 15占쏙옙 占쏙옙占쏙옙 첫占쏙옙占싹띰옙 占십반울옙 占승듸옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙..*/
    /*..hui [21-3-18占쏙옙占쏙옙 5:50:57] 占쏙옙占싶곤옙 占쏙옙占쏙옙 占식억옙占쏙옙占쏙옙 占승듸옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙 占쏙옙占쏙옙..*/
    if( u16Heater_Power_Save <= HEATER_POWER_HIGH
        && gu8_hot_setting_temperature == HOT_SET_TEMP_3__COFFEE__85_oC
        /*&& gu8_Hot_In_Temperature_One_Degree <= 15*/
        && gu8_Hot_In_Temperature_One_Degree <= 20
        && gu8_Hot_Heater_Temperature_One_Degree <= 65
        && gu8_pre_heater_temp <= 20 )
    {
        u8Target_Hz_Hot = u8Target_Hz_Hot - 5;
    }
    else if( u16Heater_Power_Save <= HEATER_POWER_HIGH
        && gu8_hot_setting_temperature == HOT_SET_TEMP_3__COFFEE__85_oC
        /*&& gu8_Hot_In_Temperature_One_Degree <= 15*/
        && gu8_Hot_In_Temperature_One_Degree <= 27
        && gu8_Hot_Heater_Temperature_One_Degree <= 75
        && gu8_pre_heater_temp <= 30 )
    {
        u8Target_Hz_Hot = u8Target_Hz_Hot - 4;
    }
    else{}
#endif
    if(u8Target_Hz_Hot <= C_033_LPM)
    {
        u8Target_Hz_Hot = C_033_LPM;
    }
    else if( u8Target_Hz_Hot >= C_07_LPM)
    {
        u8Target_Hz_Hot = C_07_LPM;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void heating_control(void)
{
    U8 mu8_target = 0;
    U8 mu8_max_limit = 0;
    U8 mu8_up_ref = 0;

    U8 mu8_overheat = 0;
    U8 mu8_overheat_clear = 0;

    if(F_WaterOut != SET)
    {
        u8HeaterMaxLimit = 0;

        return;
    }
    else{}

    if(u8WaterOutState != HOT_WATER_SELECT)
    {
        return;
    }
    else{}

    if( gu8_Water_Out_Step == STATE_30_EXTRACT_VALVE_ON_STATE
        || gu8_Water_Out_Step == STATE_31_WATER_EXTRACT_STATE )
    {
        mu8_target = gu8_Hot_Target_Temp;
    }
    else if(gu8_Water_Out_Step == STATE_20_HOT_PRE_HEATING_STATE
        && gu8_Preheat_Step >= STATE_3_PREHEAT_CHECK_TIME)
    {
        mu8_target = gu8_Hot_Preheat_Temp;
    }
    else
    {
    	//step 추가로 NG로 빠짐
        //return;
    }

/////////////////////////////////////////////////////////////////////////////////
    calc_heater_out( mu8_target );

    /*..hui [19-10-2오후 7:27:34] 예열시에도 히터 출력은 추출 온도 기준으로 계산..*/
    /*..hui [19-10-2오후 7:27:51] 15도 미만일경우 20% 추가..*/
    if(Bit0_Pre_Heating_State == SET)
    {
        pre_heating_control( mu8_target );

        gu8_heater_full_timer = 0;
        gu8_low_flow_timer = 0;
    }
    else if( Bit1_Main_Heating_State == SET)// && gu8_hot_setting_temperature == HOT_SETTING_TEMP_COFFEE )
    {
        main_heating_control( mu8_target );
#if 0
        if( gu8_hot_setting_temperature != HOT_SET_TEMP_1__MILK__43_oC
            && u16Heater_Power_Save <= HEATER_POWER_HIGH
            && ( gu8_Hot_Out_Temperature_One_Degree <= 85 && gu8_Hot_Heater_Temperature_One_Degree <= 85 ) )
        {
            gu8_heater_full_timer++;

            if( gu8_heater_full_timer >= 10 )
            {
                gu8_heater_full_timer = 10;
            }
            else
            {
                u8Delta_Power_Level = 100;
            }
        }
        else{}

        /*..hui [21-3-18오전 10:53:04] 커피 설정일때 입수 17도 미만일경우 추출후에도 80도 미만이면 풀 가동..*/
        /*..hui [21-3-18오전 10:53:32] 이게 없으면 예열시간이 적어서 온도가 안올라갔는데도 계산상 히터 전력을 내릴수있음..*/
        if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__COFFEE__85_oC
            && gu8_Hot_In_Temperature_One_Degree <= 27
            && u16Heater_Power_Save <= HEATER_POWER_HIGH
            && gu8_pre_heater_temp <= 30 )
        {
            if( gu8_Hot_Out_Temperature_One_Degree <= 80 )
            {
                u8Delta_Power_Level = 100;
            }
            else{}
        }
        else{}
#endif
        // [25-02-20 15:18:19] yspark 튜닝
        // [25-05-23 17:05:57] ysaprk 2차 튜닝
        //cbr
        if( gu8_Hot_Out_Temperature_One_Degree >= 99
            || gu8_Hot_Heater_Temperature_One_Degree >= 99 )
        {
            if(u8Delta_Power_Level > gu8_min_power)
            {
				//유량 변화에 따라 Delta power값 조절
                if(gu8_MainHeat_Flow_target > 27)
                {
                    u8Delta_Power_Level = u8Delta_Power_Level - 20;
                }
                else
                {
                    u8Delta_Power_Level = u8Delta_Power_Level - 25;
                }
            }
            else{}
        }
        else if( gu8_Hot_Out_Temperature_One_Degree >= 98
            || gu8_Hot_Heater_Temperature_One_Degree >= 98 )
        {
            if(u8Delta_Power_Level > gu8_min_power)
            {
                if(gu8_MainHeat_Flow_target > 27)
                {
                    u8Delta_Power_Level = u8Delta_Power_Level - 15;
                }
                else
                {
                    u8Delta_Power_Level = u8Delta_Power_Level - 20;
                }
            }
            else{}
        }
        else if( gu8_Hot_Out_Temperature_One_Degree >= 97
            || gu8_Hot_Heater_Temperature_One_Degree >= 97 )
        {
            if(u8Delta_Power_Level > gu8_min_power)
            {
                u8Delta_Power_Level = u8Delta_Power_Level - 15;
            }
            else{}
        }
        else if( gu8_Hot_Out_Temperature_One_Degree >= 96
            || gu8_Hot_Heater_Temperature_One_Degree >= 96 )
        {
            if(u8Delta_Power_Level > gu8_min_power)
            {
                u8Delta_Power_Level = u8Delta_Power_Level - 10;
            }
            else{}
        }
        else if( gu8_Hot_Out_Temperature_One_Degree >= 95
            || gu8_Hot_Heater_Temperature_One_Degree >= 95 )
        {
            if(u8Delta_Power_Level > gu8_min_power)
            {
                u8Delta_Power_Level = u8Delta_Power_Level - 5;
            }
            else{}
        }
        else if( gu8_Hot_Out_Temperature_One_Degree >= mu8_target + 5 )
        {
            if(u8Delta_Power_Level > gu8_min_power)
            {
                u8Delta_Power_Level = u8Delta_Power_Level - 10;
//                // ★2025-06-02 Phil
//                  if( (gu8_hot_setting_temperature == HOT_SET_TEMP____55oC)
//			          || ( gu8_hot_setting_temperature == HOT_SET_TEMP____50oC )
//			          || ( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC ) )
//                {
//                		u8Delta_Power_Level = u8Delta_Power_Level - 0;
//                }
//                else
//                {
//                		u8Delta_Power_Level = u8Delta_Power_Level - 10;
//                }
//                // ★2025-06-02 Phil
            }
            else{}
        }
        else if( gu8_Hot_Out_Temperature_One_Degree <= mu8_target - 5 )
        {
            if(u8Delta_Power_Level > gu8_min_power)
            {
                //u8Delta_Power_Level = u8Delta_Power_Level - 10;
                // ★2025-06-02 Phil
                  if( (gu8_hot_setting_temperature == HOT_SET_TEMP____55oC)
			          || ( gu8_hot_setting_temperature == HOT_SET_TEMP____50oC )
			          || ( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC ) )
                {
                		u8Delta_Power_Level = 100;
                }
                else
                {
                		u8Delta_Power_Level = u8Delta_Power_Level - 0;
                }
                // ★2025-06-02 Phil
            }
            else{}
        }
        else{}
#if 0
        if( (gu8_Hot_Out_Temperature_One_Degree >= mu8_target + 8)
             && (gu8_hot_setting_temperature == HOT_SET_TEMP_1__MILK__43_oC)
             && (u16Heater_Power_Save > HEATER_POWER_LOW) )
        {
            if(u8Delta_Power_Level > gu8_min_power)
            {
                u8Delta_Power_Level = u8Delta_Power_Level - 5;
            }
            else{}
        }
        else{}
#endif
        /*if( gu8_Flow_1sec <= C_025_LPM )*/    //kdh
        //if( gu8_Flow_1sec <= C_03_LPM )
        //sean [25-05-13] 유량값이 부족하여 0.25LPM으로 세팅
        if( gu8_Flow_1sec <= C_025_LPM )
        {
            gu8_low_flow_timer++;

            if( gu8_low_flow_timer >= 10 )
            {
                gu8_low_flow_timer = 10;
                u8Delta_Power_Level = gu8_min_power;
            }
            else{}
        }
        else
        {
            gu8_low_flow_timer = 0;
        }
    }
    else
    {
        gu8_adjust_heater_timer = 0;
        gs8_adjust_heater_power = 0;
        gu8_low_flow_timer = 0;
        gu8_heater_full_timer = 0;
    }

    if(u8Delta_Power_Level >= 100)
    {
        u8Delta_Power_Level = 100;
    }
    else
    {
        if(u8Delta_Power_Level <= gu8_min_power)
        {
            u8Delta_Power_Level = gu8_min_power;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void pre_heating_control( U8 mu8_target )
{
    /*..sean [25-05-12] 90/95도 해당 제어 동일하게 적용..*/
    if ( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
		|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
		|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )
        || (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
        || ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ))
    {
        if (u16Heater_Power_Save <= HEATER_POWER_LOW)
        {
            u8Delta_Power_Level = 110;
        }
        else if( gu8_Hot_Heater_Temperature_One_Degree <= (mu8_target - 5) )
        {
            u8Delta_Power_Level = 100;
        }
        else
        {
            u8Delta_Power_Level = 100;
        }
    }
    else
    {
        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {
            u8Delta_Power_Level = 100;
        }
        else
        {
            if(u16Heater_Power_Save <= HEATER_POWER_HIGH)
            {
                u8Delta_Power_Level = 85;
            }
            else
            {
                u8Delta_Power_Level = 70;
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void main_heating_control( U8 mu8_target )
{
    U8 mu8_up_ref = 0;

    if( gu8_Hot_Out_Temperature_One_Degree >= mu8_target + 3 )
    {
        if( (gu8_hot_setting_temperature == HOT_SET_TEMP____55oC)
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____50oC )
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC ) )
        {
            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {
                if( gs8_adjust_heater_power > 0 )
                {
                    mu8_up_ref = 3;
                }
                else
                {
                    mu8_up_ref = 5;
                }
            }
            else
            {
                mu8_up_ref = 2;
            }
        }
        else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
        {
            if(u16Heater_Power_Save > HEATER_POWER_LOW && u16Heater_Power_Save <= HEATER_POWER_HIGH )
            {
                if( gs8_adjust_heater_power > 0 )
                {
                    mu8_up_ref = 2;
                }
                else
                {
                    mu8_up_ref = 5;
                }
            }
            else
            {
                if( gs8_adjust_heater_power > 0 )
                {
                    mu8_up_ref = 5;
                }
                else
                {
                    mu8_up_ref = 15;
                }
            }
        }
        else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
		|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
        {
            if( gs8_adjust_heater_power > 0 )
            {
                mu8_up_ref = 5;
            }
            else
            {
                if(gu8_Hot_Out_Temperature_One_Degree >= mu8_target + 5)
                {
                    mu8_up_ref = 7;
                }
                else if(gu8_Hot_Out_Temperature_One_Degree >= mu8_target + 4)
                {
                    mu8_up_ref = 9;
                }
                else if(gu8_Hot_Out_Temperature_One_Degree >= mu8_target + 3)
                {
                    mu8_up_ref = 12;
                }
                else
                {
                    mu8_up_ref = 15;
                }
            }
        }
		//85도 그대로 여서 수정해야함 *--*
        else //if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__MAX__100_oC )
        {
            if( gs8_adjust_heater_power > 0 )
            {
                mu8_up_ref = 5;
            }
            else
            {
                if(gu8_Hot_Out_Temperature_One_Degree >= mu8_target + 5)
                {
                    mu8_up_ref = 7;
                }
                else if(gu8_Hot_Out_Temperature_One_Degree >= mu8_target + 4)
                {
                    mu8_up_ref = 9;
                }
                else if(gu8_Hot_Out_Temperature_One_Degree >= mu8_target + 3)
                {
                    mu8_up_ref = 12;
                }
                else
                {
                    mu8_up_ref = 15;
                }
            }
        }

        gu8_adjust_heater_timer++;

        if( gu8_adjust_heater_timer >= mu8_up_ref )
        {
            gu8_adjust_heater_timer = 0;
            gs8_adjust_heater_power = gs8_adjust_heater_power - 1;

            if( gs8_adjust_heater_power <= -20 )
            {
                gs8_adjust_heater_power = -20;
            }
            else{}
        }
        else{}
    }
    //else if(gu8_Hot_Out_Temperature_One_Degree <= mu8_target - 2)
    else if(gu8_Hot_Out_Temperature_One_Degree <= mu8_target - 1)
    {
        if( (gu8_hot_setting_temperature == HOT_SET_TEMP____55oC)
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____50oC )
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC ) )
        {
            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {
                if( gs8_adjust_heater_power < 0 )
                {
                    mu8_up_ref = 8;
                }
                else
                {
                    mu8_up_ref = 15;
                }
            }
            else
            {
                 mu8_up_ref = 2;
            }
        }
        else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
        {
            if( gs8_adjust_heater_power < 0 )
            {
                mu8_up_ref = 8;
            }
            else
            {
                mu8_up_ref = 9;
            }
        }
        else
        {
            if( gs8_adjust_heater_power < 0 )
            {
                mu8_up_ref = 3;
            }
            else if(gu8_Hot_Out_Temperature_One_Degree <= mu8_target - 8)
            {
                if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                {
                    mu8_up_ref = 4;
                }
                else if(u16Heater_Power_Save <= HEATER_POWER_HIGH)
                {
                    mu8_up_ref = 8;
                }
                else
                {
                    mu8_up_ref = 10;
                }
            }
            else
            {
                mu8_up_ref = 8;
            }
        }

        gu8_adjust_heater_timer++;

        if( gu8_adjust_heater_timer >= mu8_up_ref )
        {
            gu8_adjust_heater_timer = 0;
            gs8_adjust_heater_power = gs8_adjust_heater_power + 1;

            if( gs8_adjust_heater_power >= 20 )
            {
                gs8_adjust_heater_power = 20;
            }
            else{}
        }
        else{}
    }
    else
    {
        gu8_adjust_heater_timer = 0;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    // [25-02-20 16:37:27] yspark, 히터 조정 값 변경
#if 0
    if( u8Delta_Power_Level >= gu8_min_power )
    {
        if (gu8_hot_setting_temperature == HOT_SET_TEMP_1__MILK__43_oC)
        {
            u8Delta_Power_Level = u8Delta_Power_Level + gs8_adjust_heater_power;
        }
        else
        {}
    }
    else{}
#endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/*------------------------------------------------------------------------------
Triac_Decent_Cal()
: 현재 조건에 맞는 적정 전력 제어 단계 계산

현재 유량에 알맞은 히터 전력 계산 - 계산된 전력만큼만 가열하여 과열을 방지하고자 함
--------------------------------------------------------------------------------*/
//20170614 목표 유량과 현재 실제 유량을 비교해서 최대 트라이악 제어 단계를 상한 제한둠(레벨확정)

// 목표전력 = 측정유량 *60 * (목표온도-입수온도)*1000 /(히터효율*860)
//2. 목표전력=측정유량*60(목표온도-입수온도)/히터효율/860*1000
//측정유량은LPM//히터효율*860=817
void calc_heater_out( U8 mu8_target )
{
    U32 mu32_conv_flow = 0;
    U32 a = 0;
    U32 b = 0;
    U32 c = 0;
    U32 d = 0;
    U32 e = 0;

    mu32_conv_flow = (U32)conv_hot_hz( gu8_Flow_1sec );

    /*a = (F32)gu8_Flow_1sec * C_FLOW_METER_Hz * 60;*/

    a = (U32)(mu32_conv_flow * 60);

    if( mu8_target > gu8_Hot_In_Temperature_One_Degree )
    {
        b = (U32)(mu8_target - gu8_Hot_In_Temperature_One_Degree);
        c = (U32)(a * b);
        d = (U32)(c / 860);
        e = (U32)(d / Heater_Efficiency);
    }
    else{}

    // [25-02-21 14:23:07] yspark, 43도에서는 전력 변환 확인 이외 온도는 풀로 히팅
    if ( (gu8_hot_setting_temperature == HOT_SET_TEMP____55oC)
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____50oC )
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC ) )
    {
        u16TargetHeaterPower = (U16)e;
    }
    else
    {
        u16TargetHeaterPower = (U16)u16Heater_Power_Save;                                      //占십울옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙
    }

    if(u16TargetHeaterPower >= C_Heater_Max_Power)
    {
        u16TargetHeaterPower = C_Heater_Max_Power;
    }
    else{}

    /*..hui [19-1-21占쏙옙占쏙옙 3:54:11] 50 占쌤곤옙占??占쏙옙占쏙옙..*/
    u8Heater_1stepWatt = (U8)((u16Heater_Power_Save / 2) / STEP_TRIAC);

    /*..hui [19-1-18占쏙옙占쏙옙 4:41:29] 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙표 占쏙옙占승븝옙占쏙옙 클 占쏙옙占??.*/
    /*..hui [19-1-18占쏙옙占쏙옙 5:25:53] 占쏙옙占쏙옙 占쏙옙占쏙옙 占쌍댐옙 占쏙옙쨘占쏙옙占??占쏙옙占쏙옙 타占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占??占쏙옙占쏙옙 占쏙옙占??.*/
    if(u16TargetHeaterPower < u16Heater_Power_Save)
    {
        u8Delta_Power_Level = (U8)((F32)((F32)u16TargetHeaterPower / (F32)u16Heater_Power_Save) * (F32)100);

        if(u8Delta_Power_Level >= 100)
        {
            u8Delta_Power_Level = 100;
        }
        else
        {
            if(u8Delta_Power_Level <= gu8_min_power)
            {
                u8Delta_Power_Level = gu8_min_power;
            }
            else{}
        }
    }
    else
    {
        /*..hui [19-1-18占쏙옙占쏙옙 5:24:21] 占쏙옙占쏙옙 占쏙옙占쏙옙 占쌍댐옙 占쏙옙占쏙옙占??타占쏙옙 占쏙옙占쏙옙 占쏙옙째占쏙옙占쏙옙占??占쏙옙占쏙옙占쏙옙占??占쌍댐옙 占쏙옙占??.*/
        u8Delta_Power_Level = 100;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void update_max_flow(void)
{
    if( F_WaterOut == SET && F_First_Hot_Effluent == CLEAR)
    {
        if( u8WaterOutState != HOT_WATER_SELECT  && gu8_Flow_1sec >= 10 )
        {
            if( gu8_max_flow >= 10
                && gu8_max_flow <= gu8_Flow_1sec + 2
                && gu8_max_flow >= gu8_Flow_1sec - 2 )
            {
                gu8_max_flow_update_timer++;

                if( gu8_max_flow_update_timer >= 20 )
                {
                    gu8_max_flow_update_timer = 20;
                    gu8_hot_filling_max_hz = gu8_max_flow - 6;
                }
                else{}
            }
            else
            {
                gu8_max_flow = gu8_Flow_1sec;
                gu8_max_flow_update_timer = 0;
            }
        }
        else
        {
            gu8_max_flow_update_timer = 0;
            gu8_max_flow = 0;
        }
    }
    else
    {
        gu8_max_flow_update_timer = 0;
        gu8_max_flow = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


void sort_hot_temp(void)
{
	U8 i = 0;
	U8 selected_ok;

	//memset(selected_hot_temp,0,sizeof(selected_hot_temp));

	selected_hot_temp[0] = 0;
	selected_hot_temp[1] = 0;
	selected_hot_temp[2] = 0;
	selected_hot_temp[3] = 0;

	if(i == 0)
	{
		if(Bit11_Temp_Select__100oC == SET)
		{
			selected_hot_temp[0] = HOT_SET_TEMP____100oC;
		}
		else if(Bit10_Temp_Select__95oC == SET)
		{
			selected_hot_temp[0] = HOT_SET_TEMP____95oC;
		}
		else if(Bit9_Temp_Select__90oC == SET)
		{
			selected_hot_temp[0] = HOT_SET_TEMP____90oC;
		}
		else if(Bit8_Temp_Select__85oC == SET)
		{
			selected_hot_temp[0] = HOT_SET_TEMP____85oC;
		}
		else if(Bit7_Temp_Select__80oC == SET)
		{
			selected_hot_temp[0] = HOT_SET_TEMP____80oC;
		}
		else if(Bit6_Temp_Select__75oC == SET)
		{
			selected_hot_temp[0] = HOT_SET_TEMP____75oC;
		}
		else if(Bit5_Temp_Select__70oC == SET)
		{
			selected_hot_temp[0] = HOT_SET_TEMP____70oC;
		}
		else if(Bit4_Temp_Select__65oC == SET)
		{
			selected_hot_temp[0] = HOT_SET_TEMP____65oC;
		}
		else if(Bit3_Temp_Select__60oC == SET)
		{
			selected_hot_temp[0] = HOT_SET_TEMP____60oC;
		}
		else if(Bit2_Temp_Select__55oC == SET)
		{
			selected_hot_temp[0] = HOT_SET_TEMP____55oC;
		}
		else if(Bit1_Temp_Select__50oC == SET)
		{
			selected_hot_temp[0] = HOT_SET_TEMP____50oC;
		}
		else if(Bit0_Temp_Select__45oC == SET)
		{
			selected_hot_temp[0] = HOT_SET_TEMP____45oC;
		}
	}

	for( i = 1; i < 4; i++ )
	{
		if(Bit11_Temp_Select__100oC == SET && (selected_hot_temp[i-1] > HOT_SET_TEMP____100oC))
		{
			selected_hot_temp[i] = HOT_SET_TEMP____100oC;
		}
		else if(Bit10_Temp_Select__95oC == SET && (selected_hot_temp[i-1] > HOT_SET_TEMP____95oC))
		{
			selected_hot_temp[i] = HOT_SET_TEMP____95oC;
		}
		else if(Bit9_Temp_Select__90oC == SET && (selected_hot_temp[i-1] > HOT_SET_TEMP____90oC))
		{
			selected_hot_temp[i] = HOT_SET_TEMP____90oC;
		}
		else if(Bit8_Temp_Select__85oC == SET && (selected_hot_temp[i-1] > HOT_SET_TEMP____85oC))
		{
			selected_hot_temp[i] = HOT_SET_TEMP____85oC;
		}
		else if(Bit7_Temp_Select__80oC == SET && (selected_hot_temp[i-1] > HOT_SET_TEMP____80oC))
		{
			selected_hot_temp[i] = HOT_SET_TEMP____80oC;
		}
		else if(Bit6_Temp_Select__75oC == SET && (selected_hot_temp[i-1] > HOT_SET_TEMP____75oC))
		{
			selected_hot_temp[i] = HOT_SET_TEMP____75oC;
		}
		else if(Bit5_Temp_Select__70oC == SET && (selected_hot_temp[i-1] > HOT_SET_TEMP____70oC))
		{
			selected_hot_temp[i] = HOT_SET_TEMP____70oC;
		}
		else if(Bit4_Temp_Select__65oC == SET && (selected_hot_temp[i-1] > HOT_SET_TEMP____65oC))
		{
			selected_hot_temp[i] = HOT_SET_TEMP____65oC;
		}
		else if(Bit3_Temp_Select__60oC == SET && (selected_hot_temp[i-1] > HOT_SET_TEMP____60oC))
		{
			selected_hot_temp[i] = HOT_SET_TEMP____60oC;
		}
		else if(Bit2_Temp_Select__55oC == SET && (selected_hot_temp[i-1] > HOT_SET_TEMP____55oC))
		{
			selected_hot_temp[i] = HOT_SET_TEMP____55oC;
		}
		else if(Bit1_Temp_Select__50oC == SET && (selected_hot_temp[i-1] > HOT_SET_TEMP____50oC))
		{
			selected_hot_temp[i] = HOT_SET_TEMP____50oC;
		}
		else if(Bit0_Temp_Select__45oC == SET && (selected_hot_temp[i-1] > HOT_SET_TEMP____45oC))
		{
			selected_hot_temp[i] = HOT_SET_TEMP____45oC;
		}
	}

	//selected_hot_temp[0] -= 1;
	//selected_hot_temp[1] -= 1;
	//selected_hot_temp[2] -= 1;
	//selected_hot_temp[3] -= 1;
}

void SetTargetTempUnder_15(void)
{
    switch( gu8_hot_setting_temperature )
    {

        case HOT_SET_TEMP____45oC:

// ★2025-06-11 Phil after PM
	        if(bit_Hot_InLowTemp_SetHighTemp == 1)
	        {  // 고온 →저온
	            gu8_Hot_Preheat_Temp = 45;
	            gu8_Hot_Target_Temp = 40;
	        }
	        //if(u16Heater_Power_Save <= HEATER_POWER_LOW)
	        else if(u16Heater_Power_Save <= HEATER_POWER_LOW)
// ★2025-06-11 Phil after PM
            {  // 저전력
                //gu8_Hot_Preheat_Temp = 50;
                //gu8_Hot_Target_Temp = 45;
                gu8_Hot_Preheat_Temp = 50;		// ★2025-06-02 Phil
                gu8_Hot_Target_Temp = 48;			// ★2025-06-02 Phil
            }
            else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
            {  // 고전력
                gu8_Hot_Preheat_Temp = 45;
                gu8_Hot_Target_Temp = 40;
            }
            else
            {  // 상시
//                gu8_Hot_Preheat_Temp = 50;
//                gu8_Hot_Target_Temp = 45;
                // gu8_Hot_Preheat_Temp = 50;		// ★2025-06-02 Phil
                gu8_Hot_Preheat_Temp = 43;      //2025-07-18 cbr    overflow 수정 후
                // gu8_Hot_Target_Temp = 50;			// ★2025-06-02 Phil
                gu8_Hot_Target_Temp = 45;       //2025-07-17 cbr
            }

            break;

        case HOT_SET_TEMP____50oC:

            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {  // 저전력
                // gu8_Hot_Preheat_Temp = 60;
                // gu8_Hot_Target_Temp = 60;
                //2025-07-30 cbr
                gu8_Hot_Preheat_Temp = 55;
                gu8_Hot_Target_Temp = 55;
            }
            else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
            {  // 고전력
                // gu8_Hot_Preheat_Temp = 55;
                // gu8_Hot_Target_Temp = 45;
                //2025-07-30 cbr
                gu8_Hot_Preheat_Temp = 50;
                gu8_Hot_Target_Temp = 47;
            }
            else
            {  // 상시
                // gu8_Hot_Preheat_Temp = 55;
                // gu8_Hot_Target_Temp = 55;
                gu8_Hot_Preheat_Temp = 50;      //2025-07-28 cbr
                gu8_Hot_Target_Temp = 50;       //2025-07-28 cbr
            }

            break;

        case HOT_SET_TEMP____55oC:

            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {  // 저전력
                // gu8_Hot_Preheat_Temp = 62;
                // gu8_Hot_Target_Temp = 62;
                //2025-07-30 cbr
                gu8_Hot_Preheat_Temp = 58;
                gu8_Hot_Target_Temp = 58;
            }
            else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
            {  // 고전력
                // gu8_Hot_Preheat_Temp = 60;
                // gu8_Hot_Target_Temp = 55;
                //2025-07-30 cbr
                gu8_Hot_Preheat_Temp = 50;
                gu8_Hot_Target_Temp = 53;
            }
            else
            {  // 상시
                // gu8_Hot_Preheat_Temp = 60;
                // gu8_Hot_Target_Temp = 60;
                gu8_Hot_Preheat_Temp = 53;      //2025-07-28 cbr
                gu8_Hot_Target_Temp = 53;       //2025-07-28 cbr
            }

            break;

        case HOT_SET_TEMP____60oC:

            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {  // 저전력
                gu8_Hot_Preheat_Temp = 75;
                gu8_Hot_Target_Temp = 65;
            }
            else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
            {  // 고전력
                // gu8_Hot_Preheat_Temp = 75;
                // gu8_Hot_Target_Temp = 60;
                //2025-07-30 cbr
                gu8_Hot_Preheat_Temp = 65;
                gu8_Hot_Target_Temp = 60;
            }
            else
            {  // 상시
                // gu8_Hot_Preheat_Temp = 75;
                // gu8_Hot_Target_Temp = 65;
                gu8_Hot_Preheat_Temp = 70;      //2025-07-28 cbr
                gu8_Hot_Target_Temp = 60;       //2025-07-28 cbr
            }

            break;

        case HOT_SET_TEMP____65oC:

            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {  // 저전력
                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    gu8_Hot_Preheat_Temp = 85;
                    gu8_Hot_Target_Temp = 73;
                }
                else
                {  // 첫잔
                    gu8_Hot_Preheat_Temp = 90;
                    gu8_Hot_Target_Temp = 85;
                }
            }
            else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
            {  // 고전력
                gu8_Hot_Preheat_Temp = 85;
                gu8_Hot_Target_Temp = 65;
            }
            else
            {  // 상시
                // gu8_Hot_Preheat_Temp = 85;
                // gu8_Hot_Target_Temp = 73;
                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    gu8_Hot_Preheat_Temp = 80;
                    gu8_Hot_Target_Temp = 65;
                }
                else
                {  // 첫잔
                    gu8_Hot_Preheat_Temp = 85;
                    gu8_Hot_Target_Temp = 75;
                }
            }
            break;

        case HOT_SET_TEMP____70oC:

            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {  // 저전력
                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    gu8_Hot_Preheat_Temp = 90;
                    gu8_Hot_Target_Temp = 78;
                }
                else
                {  // 첫잔
                    gu8_Hot_Preheat_Temp = 95;    //2025-07-11 cbr
                    // gu8_Hot_Target_Temp = 85;//82; // ★2025-06-02 Phil
                    gu8_Hot_Target_Temp = 88;   //2025-07-22 cbr
                }
            }
            else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
            {  // 고전력
// ★2025-06-02 Phil
//                gu8_Hot_Preheat_Temp = 90;
//                gu8_Hot_Target_Temp = 73;
                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    gu8_Hot_Preheat_Temp = 90;
                    //gu8_Hot_Target_Temp = 68;
                    gu8_Hot_Target_Temp = 70;
                }
                else
                {  // 첫잔
                    gu8_Hot_Preheat_Temp = 90;
                    //gu8_Hot_Target_Temp = 73;
                    gu8_Hot_Target_Temp = 82;      //2025-07-11 cbr
                }

            }
            else
            {  // 상시
//                gu8_Hot_Preheat_Temp = 90;
//                gu8_Hot_Target_Temp = 85;

                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    gu8_Hot_Preheat_Temp = 85;
                    //gu8_Hot_Target_Temp = 85;
                    gu8_Hot_Target_Temp = 70;// ★2025-06-08 Phil
                }
                else
                {  // 첫잔
                    gu8_Hot_Preheat_Temp = 90;
                    gu8_Hot_Target_Temp = 83;// ★2025-06-08 Phil
                }
            }
// ★2025-06-02 Phil
            break;

        case HOT_SET_TEMP____75oC:

            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {  // 저전력
                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    gu8_Hot_Preheat_Temp = 95;
                    gu8_Hot_Target_Temp = 90;
                }
                else
                {  // 첫잔
                    gu8_Hot_Preheat_Temp = 98;
                    gu8_Hot_Target_Temp = 100;
                }
            }
            else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
            {  // 고전력
                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    // gu8_Hot_Preheat_Temp = 98;
                    // gu8_Hot_Target_Temp = 85;
                    //2025-07-30 cbr
                    gu8_Hot_Preheat_Temp = 82;
                    gu8_Hot_Target_Temp = 75;
                }
                else
                {  // 첫잔
                    // gu8_Hot_Preheat_Temp = 98;
                    // gu8_Hot_Target_Temp = 95;
                    //2025-07-30 cbr
                    gu8_Hot_Preheat_Temp = 90;
                    gu8_Hot_Target_Temp = 90;
                }
            }
            else
            {  // 상시
                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    // gu8_Hot_Preheat_Temp = 98;
                    // gu8_Hot_Target_Temp = 88;
                    gu8_Hot_Preheat_Temp = 85;      //2025-07-28 cbr
                    gu8_Hot_Target_Temp = 78;       //2025-07-28 cbr
                }
                else
                {  // 첫잔
                    gu8_Hot_Preheat_Temp = 95;
                    gu8_Hot_Target_Temp = 95;
                }
            }

            break;

        case HOT_SET_TEMP____80oC:

            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {  // 저전력
                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    gu8_Hot_Preheat_Temp = 98;
                    gu8_Hot_Target_Temp = 90;
                }
                else
                {  // 첫잔
                    gu8_Hot_Preheat_Temp = 98;
                    gu8_Hot_Target_Temp = 100;
                }
            }
            else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
            {  // 고전력
                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    // gu8_Hot_Preheat_Temp = 98;
                    // gu8_Hot_Target_Temp = 88;
                    //2025-07-30 cbr
                    gu8_Hot_Preheat_Temp = 90;
                    gu8_Hot_Target_Temp = 80;
                }
                else
                {  // 첫잔
                    // gu8_Hot_Preheat_Temp = 98;
                    // gu8_Hot_Target_Temp = 95;
                    //2025-07-30 cbr
                    gu8_Hot_Preheat_Temp = 90;
                    gu8_Hot_Target_Temp = 90;
                }
            }
            else
            {  // 상시
                // gu8_Hot_Preheat_Temp = 98;
                // gu8_Hot_Target_Temp = 95;
                //2025-07-28 cbr
                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    gu8_Hot_Preheat_Temp = 95;
                    gu8_Hot_Target_Temp = 85;
                }
                else
                {  // 첫잔
                    gu8_Hot_Preheat_Temp = 95;
                    gu8_Hot_Target_Temp = 90;
                }
            }
            break;

        case HOT_SET_TEMP____85oC:
            // [25-02-21 13:25:54] yspark, 85도 100도와 동일하게 온도 설정
            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {  // 저전력
                //gu8_Hot_Preheat_Temp = 98;
                // gu8_Hot_Target_Temp = 100;
                //2025-07-22 cbr
                if (F_firstEffluent_hotWater)
                {  // 둘째 잔
                    gu8_Hot_Preheat_Temp = 98;
                    gu8_Hot_Target_Temp = 95;
                }
                else
                {  // 첫잔
                    gu8_Hot_Preheat_Temp = 100;
                    gu8_Hot_Target_Temp = 100;
                }
            }
            else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
            {  // 고전력
                // gu8_Hot_Preheat_Temp = 98;
                gu8_Hot_Preheat_Temp = 95;      //2025-07-18 cbr
                //gu8_Hot_Target_Temp = 100;
                // gu8_Hot_Target_Temp = 96;		// ★2025-06-02 Phil
                gu8_Hot_Target_Temp = 90;       //2025-07-18 cbr
            }
            else
            {  // 상시
                gu8_Hot_Preheat_Temp = 98;
                //gu8_Hot_Target_Temp = 100;
                // gu8_Hot_Target_Temp = 97;		// ★2025-06-02 Phil
                gu8_Hot_Target_Temp = 90;       //2025-07-18 cbr
            }

            break;

        case HOT_SET_TEMP____90oC:
            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {
                // 저전력
                if(F_Airvent_TargetTempDown == SET)
                {
                    gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
                }
                else
                {
                    gu8_Hot_Preheat_Temp = 96;  //98;   //2025-06-24 cbr
                }

                // gu8_Hot_Preheat_Temp = 98;
                gu8_Hot_Target_Temp = 100;
            }
            else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
            {
                // 고전력
                if(F_Airvent_TargetTempDown == SET)
                {
                    gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
                }
                else
                {
                    gu8_Hot_Preheat_Temp = 88;  //98;   //2025-06-24 cbr
                }

                // gu8_Hot_Preheat_Temp = 88;      //2025-07-18 cbr
                gu8_Hot_Target_Temp = 96;       //2025-07-18 cbr
            }
            else
            {
                // 상시
                if(F_Airvent_TargetTempDown == SET)
                {
                    gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
                }
                else
                {
                    gu8_Hot_Preheat_Temp = 95;
                }
                // gu8_Hot_Preheat_Temp = 95;      //2025-07-22 cbr
                gu8_Hot_Target_Temp = 98;       //2025-07-22 cbr
            }
            break;

        case HOT_SET_TEMP____95oC:
            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {
                // 저전력
                if(F_Airvent_TargetTempDown == SET)
                {
                    gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
                }
                else
                {
                    gu8_Hot_Preheat_Temp = 98;  //98;   //2025-06-24 cbr
                }

                // gu8_Hot_Preheat_Temp = 98;
                gu8_Hot_Target_Temp = 100;
            }
            else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
            {
                // 고전력
                if(F_Airvent_TargetTempDown == SET)
                {
                    gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
                }
                else
                {
                    gu8_Hot_Preheat_Temp = 88;  //98;   //2025-06-24 cbr
                }

                // gu8_Hot_Preheat_Temp = 88;      //2025-07-18 cbr
                gu8_Hot_Target_Temp = 96;       //2025-07-18 cbr
            }
            else
            {
                // 상시
                if(F_Airvent_TargetTempDown == SET)
                {
                    gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
                }
                else
                {
                    gu8_Hot_Preheat_Temp = 95;  //98;   //2025-06-24 cbr
                }

                // gu8_Hot_Preheat_Temp = 95;      //2025-07-22 cbr
                gu8_Hot_Target_Temp = 98;       //2025-07-22 cbr
            }
            break;

        case HOT_SET_TEMP____100oC:
            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {
                // 저전력
                if(F_Airvent_TargetTempDown == SET)
                {
                    gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
                }
                else
                {
                    gu8_Hot_Preheat_Temp = 98;  //2025-06-24 cbr
                }

                // gu8_Hot_Preheat_Temp = 98;
                gu8_Hot_Target_Temp = 100;
            }
            else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
            {
                // 고전력
                if(F_Airvent_TargetTempDown == SET)
                {
                    gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
                }
                else
                {
                    gu8_Hot_Preheat_Temp = 88;  //2025-06-24 cbr
                }

                // gu8_Hot_Preheat_Temp = 88;      //2025-07-18 cbr
                gu8_Hot_Target_Temp = 96;       //2025-07-18 cbr
            }
            else
            {
                // 상시
                if(F_Airvent_TargetTempDown == SET)
                {
                    gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
                }
                else
                {
                    gu8_Hot_Preheat_Temp = 95;  //98;   //2025-06-24 cbr
                }

                // gu8_Hot_Preheat_Temp = 95;      //2025-07-22 cbr
                gu8_Hot_Target_Temp = 98;       //2025-07-22 cbr
            }
            break;

        default:

            gu8_Hot_Preheat_Temp = 0;
            gu8_Hot_Target_Temp = 0;

            break;
    }
}

void SetTargetTempExtra(void)
{
    switch (gu8_hot_setting_temperature)
    {
        case HOT_SET_TEMP____45oC:

// ★2025-06-11 Phil after PM
        if(bit_Hot_InLowTemp_SetHighTemp == 1)
        {  // 고온 →저온
            gu8_Hot_Preheat_Temp = 40;
            gu8_Hot_Target_Temp = 40;
        }
        //if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        else if(u16Heater_Power_Save <= HEATER_POWER_LOW)
// ★2025-06-11 Phil after PM
        {  // 저전력
//            gu8_Hot_Preheat_Temp = 52;
//            gu8_Hot_Target_Temp = 52;
            // gu8_Hot_Preheat_Temp = 45;//52; //2025-06-05 18:57:56 cbr        // ★2025-06-02 Phil
            // gu8_Hot_Target_Temp = 43;//49;  //2025-06-05 18:58:05 cbr        // ★2025-06-02 Phil
            //2025-07-24 cbr
            if (F_firstEffluent_hotWater)
            {  // 둘째 잔
                gu8_Hot_Preheat_Temp = 40;
                gu8_Hot_Target_Temp = 43;
            }
            else
            {  // 첫잔
                gu8_Hot_Preheat_Temp = 38;
                gu8_Hot_Target_Temp = 38;
            }
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            //gu8_Hot_Preheat_Temp = 52;
            //gu8_Hot_Target_Temp = 52;
            gu8_Hot_Preheat_Temp = 40;  //47;   //2025-06-05 19:36:20 cbr       // ★2025-06-02 Phil
            gu8_Hot_Target_Temp = 40;   //43;   //2025-06-05 19:40:02 cbr       // ★2025-06-02 Phil
        }
        else
        {  // 상시
            //gu8_Hot_Preheat_Temp = 52;
            //gu8_Hot_Target_Temp = 52;
            // gu8_Hot_Preheat_Temp = 43; //2025-06-05 19:45:02    cbr
            gu8_Hot_Preheat_Temp = 40; //2025-07-23 cbr
            // gu8_Hot_Target_Temp = 43;  //2025-06-05 19:44:55    cbr
            gu8_Hot_Target_Temp = 40;  //2025-06-05 19:44:55    cbr
        }

        break;

    case HOT_SET_TEMP____50oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            // gu8_Hot_Preheat_Temp = 60;
            // gu8_Hot_Target_Temp = 55;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 50;
            gu8_Hot_Target_Temp = 55;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            // gu8_Hot_Preheat_Temp = 60;
            // gu8_Hot_Target_Temp = 55;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 45;
            gu8_Hot_Target_Temp = 48;
        }
        else
        {  // 상시
            // gu8_Hot_Preheat_Temp = 60;
            // gu8_Hot_Target_Temp = 55;
            gu8_Hot_Preheat_Temp = 45;      //2025-07-25 cbr
            gu8_Hot_Target_Temp = 50;       //2025-07-25 cbr
        }

        break;

    case HOT_SET_TEMP____55oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            // gu8_Hot_Preheat_Temp = 60;
            // gu8_Hot_Target_Temp = 53;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 60;
            gu8_Hot_Target_Temp = 55;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            // gu8_Hot_Preheat_Temp = 65;
            // gu8_Hot_Target_Temp = 60;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 58;
            gu8_Hot_Target_Temp = 53;
        }
        else
        {  // 상시
            gu8_Hot_Preheat_Temp = 60;
            gu8_Hot_Target_Temp = 53;
        }

        break;

    case HOT_SET_TEMP____60oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            gu8_Hot_Preheat_Temp = 65;
            gu8_Hot_Target_Temp = 63;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            // gu8_Hot_Preheat_Temp = 75;
            // gu8_Hot_Target_Temp = 70;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 58;
            gu8_Hot_Target_Temp = 58;
        }
        else
        {  // 상시
            // gu8_Hot_Preheat_Temp = 65;
            // gu8_Hot_Target_Temp = 63;
            gu8_Hot_Preheat_Temp = 60;      //2025-07-25 cbr
            gu8_Hot_Target_Temp = 60;       //2025-07-25 cbr
        }

        break;

    case HOT_SET_TEMP____65oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            gu8_Hot_Preheat_Temp = 75;
            gu8_Hot_Target_Temp = 70;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            // gu8_Hot_Preheat_Temp = 80;
            // gu8_Hot_Target_Temp = 78;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 65;
            gu8_Hot_Target_Temp = 63;
        }
        else
        {  // 상시
            // gu8_Hot_Preheat_Temp = 75;
            // gu8_Hot_Target_Temp = 70;
            gu8_Hot_Preheat_Temp = 65;      //2025-07-25 cbr
            gu8_Hot_Target_Temp = 65;       //2025-07-25 cbr
        }
        break;

    case HOT_SET_TEMP____70oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            gu8_Hot_Preheat_Temp = 65;  //80;       //2025-06-05 19:00:31 cbr
            gu8_Hot_Target_Temp = 70;   //78;       //2025-06-05 19:00:27 cbr
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            gu8_Hot_Preheat_Temp = 60;  //75;   //2025-06-05 19:34:27 cbr
            gu8_Hot_Target_Temp = 63;   //72;   //2025-06-05 19:34:31 cbr
        }
        else
        {  // 상시
            gu8_Hot_Preheat_Temp = 60; //80; //2025-06-05 17:55:39 //cbr
            gu8_Hot_Target_Temp = 68; //78;  //2025-06-05 13:50:38 //cbr
        }

        break;

    case HOT_SET_TEMP____75oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            // gu8_Hot_Preheat_Temp = 90;
            // gu8_Hot_Target_Temp = 85;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 75;
            gu8_Hot_Target_Temp = 75;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            // gu8_Hot_Preheat_Temp = 85;
            // gu8_Hot_Target_Temp = 80;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 70;
            gu8_Hot_Target_Temp = 72;
        }
        else
        {  // 상시
            // gu8_Hot_Preheat_Temp = 90;
            // gu8_Hot_Target_Temp = 85;
            gu8_Hot_Preheat_Temp = 70;      //2025-07-25 cbr
            gu8_Hot_Target_Temp = 75;       //2025-07-25 cbr
        }

        break;

    case HOT_SET_TEMP____80oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            // gu8_Hot_Preheat_Temp = 90;
            // gu8_Hot_Target_Temp = 93;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 85;
            gu8_Hot_Target_Temp = 85;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            // gu8_Hot_Preheat_Temp = 88;
            // gu8_Hot_Target_Temp = 87;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 80;
            gu8_Hot_Target_Temp = 80;
        }
        else
        {  // 상시
            // gu8_Hot_Preheat_Temp = 90;
            // gu8_Hot_Target_Temp = 93;
            gu8_Hot_Preheat_Temp = 80;      //2025-07-25 cbr
            gu8_Hot_Target_Temp = 85;       //2025-07-25 cbr
        }
        break;

    case HOT_SET_TEMP____85oC:
        // [25-02-21 13:25:54] yspark, 85도 100도와 동일하게 온도 설정
        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            //gu8_Hot_Preheat_Temp = 98;
		    gu8_Hot_Preheat_Temp = 85;	//100;		//2025-06-05 21:07:44 cbr	// ★2025-06-02 Phil
            // gu8_Hot_Target_Temp = 100;
            gu8_Hot_Target_Temp = 95;  //2025-07-24 cbr

        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            gu8_Hot_Preheat_Temp = 78;      //96;//98;    //2025-06-05 21:07:09 cbr //스팀 발생
            //gu8_Hot_Target_Temp = 100;
            // gu8_Hot_Target_Temp = 96;		// ★2025-06-02 Phil
            gu8_Hot_Target_Temp = 92;       //2025-07-23 cbr
        }
        else
        {  // 상시
            gu8_Hot_Preheat_Temp = 82;  //96; //98;    //2025-06-05 21:07:50    cbr
            //gu8_Hot_Target_Temp = 100;
            // gu8_Hot_Target_Temp = 95;  //97;	//cbr	// ★2025-06-02 Phil
            gu8_Hot_Target_Temp = 90;       //2025-07-23 cbr
        }

        break;

    case HOT_SET_TEMP____90oC:
        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            gu8_Hot_Preheat_Temp = 88;//98;     //2025-06-05 21:01:54   cbr
            gu8_Hot_Target_Temp = 100;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            gu8_Hot_Preheat_Temp = 82;  //98;   //2025-06-05 20:47:16   cbr
            gu8_Hot_Target_Temp = 100;
        }
        else
        {  // 상시
            gu8_Hot_Preheat_Temp = 85;  //98;      //2025-06-05 21:02:00    cbr
            gu8_Hot_Target_Temp = 100;
        }
        break;

    case HOT_SET_TEMP____95oC:
        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            gu8_Hot_Preheat_Temp = 88;//98;     //2025-06-05 21:01:54   cbr
            gu8_Hot_Target_Temp = 100;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            gu8_Hot_Preheat_Temp = 82;  //98;   //2025-06-05 20:47:16   cbr
            gu8_Hot_Target_Temp = 100;
        }
        else
        {  // 상시
            gu8_Hot_Preheat_Temp = 85;  //98;      //2025-06-05 21:02:00    cbr
            gu8_Hot_Target_Temp = 100;
        }
        break;

    case HOT_SET_TEMP____100oC:
        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            gu8_Hot_Preheat_Temp = 88;//98;     //2025-06-05 21:01:54   cbr
            gu8_Hot_Target_Temp = 100;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            gu8_Hot_Preheat_Temp = 82;  //98;   //2025-06-05 20:47:16   cbr
            gu8_Hot_Target_Temp = 100;
        }
        else
        {  // 상시
            gu8_Hot_Preheat_Temp = 85;  //98;      //2025-06-05 21:02:00    cbr
            gu8_Hot_Target_Temp = 100;
        }
        break;

    default:

        gu8_Hot_Preheat_Temp = 0;
        gu8_Hot_Target_Temp = 0;

        break;
    }
}

void SetTargetTempUnder_25(void)
{
    switch (gu8_hot_setting_temperature)
    {
        case HOT_SET_TEMP____45oC:

// ★2025-06-11 Phil after PM
        if(bit_Hot_InLowTemp_SetHighTemp == 1)
        {  // 고온 →저온
            gu8_Hot_Preheat_Temp = 45;
            gu8_Hot_Target_Temp = 37;
        }
        //if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        else if(u16Heater_Power_Save <= HEATER_POWER_LOW)
// ★2025-06-11 Phil after PM
        {  // 저전력
            // gu8_Hot_Preheat_Temp = 50;// ★2025-06-09 Phil
            gu8_Hot_Preheat_Temp = 40;      //2025-07-15 cbr
            gu8_Hot_Target_Temp = 46;// ★2025-06-09 Phil
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            // gu8_Hot_Preheat_Temp = 40;// ★2025-06-02 Phil
            // gu8_Hot_Target_Temp = 39;// ★2025-06-02 Phil
            gu8_Hot_Preheat_Temp = 36;      //2025-07-16 cbr
            gu8_Hot_Target_Temp = 40;       //2025-07-16 cbr
        }
        else
        {  // 상시
            // gu8_Hot_Preheat_Temp = 43;// ★2025-06-02 Phil
            gu8_Hot_Preheat_Temp = 36;      //2025-07-16 cbr
            gu8_Hot_Target_Temp = 43;// ★2025-06-02 Phil
        }

        break;

    case HOT_SET_TEMP____50oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            // gu8_Hot_Preheat_Temp = 45; //2025-06-04 cbr
            // gu8_Hot_Target_Temp = 45;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 53;
            gu8_Hot_Target_Temp = 53;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            // gu8_Hot_Preheat_Temp = 60;
            // gu8_Hot_Target_Temp = 55;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 48;
            gu8_Hot_Target_Temp = 48;
        }
        else
        {  // 상시
            // gu8_Hot_Preheat_Temp = 60;
            // gu8_Hot_Target_Temp = 55;
            gu8_Hot_Preheat_Temp = 50;      //2025-07-29 cbr
            gu8_Hot_Target_Temp = 50;       //2025-07-29 cbr
        }

        break;

    case HOT_SET_TEMP____55oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            // gu8_Hot_Preheat_Temp = 56;  //60; //cbr
            // gu8_Hot_Target_Temp = 53;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 60;
            gu8_Hot_Target_Temp = 60;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            // gu8_Hot_Preheat_Temp = 65;
            // gu8_Hot_Target_Temp = 60;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 57;
            gu8_Hot_Target_Temp = 55;
        }
        else
        {  // 상시
            // gu8_Hot_Preheat_Temp = 56;  //62; //cbr
            // gu8_Hot_Target_Temp = 53;
            gu8_Hot_Preheat_Temp = 60;      //2025-07-29 cbr
            gu8_Hot_Target_Temp = 57;       //2025-07-29 cbr
        }

        break;

    case HOT_SET_TEMP____60oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            // gu8_Hot_Preheat_Temp = 65;
            // gu8_Hot_Target_Temp = 63;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 60;
            gu8_Hot_Target_Temp = 63;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            // gu8_Hot_Preheat_Temp = 75;
            // gu8_Hot_Target_Temp = 70;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 55;
            gu8_Hot_Target_Temp = 56;
        }
        else
        {  // 상시
            // gu8_Hot_Preheat_Temp = 67;
            // gu8_Hot_Target_Temp = 60;
            gu8_Hot_Preheat_Temp = 55;      //2025-07-29 cbr
            gu8_Hot_Target_Temp = 58;       //2025-07-29 cbr
        }

        break;

    case HOT_SET_TEMP____65oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            // gu8_Hot_Preheat_Temp = 75;
            // gu8_Hot_Target_Temp = 72;  //70;//2025-06-04 16:33:01 cbr
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 68;
            gu8_Hot_Target_Temp = 68;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            // gu8_Hot_Preheat_Temp = 80;
            // gu8_Hot_Target_Temp = 78;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 60;
            gu8_Hot_Target_Temp = 62;
        }
        else
        {  // 상시
            // gu8_Hot_Preheat_Temp = 75;
            // gu8_Hot_Target_Temp = 67;
            gu8_Hot_Preheat_Temp = 65;      //2025-07-29 cbr
            gu8_Hot_Target_Temp = 63;       //2025-07-29 cbr
        }
        break;

    case HOT_SET_TEMP____70oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            // gu8_Hot_Preheat_Temp = 80;
            // //gu8_Hot_Target_Temp = 75;
            // //gu8_Hot_Target_Temp = 79;// ★2025-06-02 Phil
            // gu8_Hot_Target_Temp = 73;// ★2025-06-02 Phil
            //2025-07-16 cbr
            if (F_firstEffluent_hotWater)
            {  // 둘째 잔
                gu8_Hot_Preheat_Temp = 80;
                gu8_Hot_Target_Temp = 75;
            }
            else
            {  // 첫잔
                gu8_Hot_Preheat_Temp = 80;
                gu8_Hot_Target_Temp = 80;
            }
            //2025-07-16 cbr
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
//            //gu8_Hot_Preheat_Temp = 72;
//            //gu8_Hot_Target_Temp = 68;
//            gu8_Hot_Preheat_Temp = 70;		// ★2025-06-02 Phil
//            gu8_Hot_Target_Temp = 70;			// ★2025-06-02 Phil
// ★2025-06-09 Phil
            if (F_firstEffluent_hotWater)
            {  // 둘째 잔
                // gu8_Hot_Preheat_Temp = 70;
                // gu8_Hot_Target_Temp = 70;
                gu8_Hot_Preheat_Temp = 68;      //2025-07-22 cbr
                gu8_Hot_Target_Temp = 68;       //2025-07-22 cbr
            }
            else
            {  // 첫잔
                gu8_Hot_Preheat_Temp = 70;
                gu8_Hot_Target_Temp = 70;   //75;   //2025-07-30 cbr 45도 후 즉시 추출 시 첫잔 높음
            }
// ★2025-06-09 Phil
        }
        else
        {  // 상시
//            //gu8_Hot_Preheat_Temp = 80;
//            //gu8_Hot_Target_Temp = 78;
//            gu8_Hot_Preheat_Temp = 70;		// ★2025-06-02 Phil
//            //gu8_Hot_Target_Temp = 70;			// ★2025-06-02 Phil
//            //gu8_Hot_Target_Temp = 73;			// ★2025-06-02 Phil
//            gu8_Hot_Target_Temp = 75;			// ★2025-06-09 Phil
// ★2025-06-09 Phil
            if (F_firstEffluent_hotWater)
            {  // 둘째 잔
                gu8_Hot_Preheat_Temp = 70;
                gu8_Hot_Target_Temp = 70;
            }
            else
            {  // 첫잔
                gu8_Hot_Preheat_Temp = 70;
                gu8_Hot_Target_Temp = 73;   //75;   //2025-07-30 cbr 45도 후 즉시 추출 시 첫잔 높음
            }
// ★2025-06-09 Phil
        }

        break;

    case HOT_SET_TEMP____75oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            // gu8_Hot_Preheat_Temp = 90;
            // gu8_Hot_Target_Temp = 85;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 90;
            gu8_Hot_Target_Temp = 80;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            gu8_Hot_Preheat_Temp = 82;
            gu8_Hot_Target_Temp = 75;
        }
        else
        {  // 상시
            // gu8_Hot_Preheat_Temp = 90;
            // gu8_Hot_Target_Temp = 85;
            gu8_Hot_Preheat_Temp = 85;      //2025-07-29 cbr
            gu8_Hot_Target_Temp = 77;       //2025-07-29 cbr
        }

        break;

    case HOT_SET_TEMP____80oC:

        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            // gu8_Hot_Preheat_Temp = 90;
            // gu8_Hot_Target_Temp = 90;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 85;
            gu8_Hot_Target_Temp = 85;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            // gu8_Hot_Preheat_Temp = 88;
            // gu8_Hot_Target_Temp = 84;
            //2025-07-30 cbr
            gu8_Hot_Preheat_Temp = 80;
            gu8_Hot_Target_Temp = 78;
        }
        else
        {  // 상시
            // gu8_Hot_Preheat_Temp = 90;
            // gu8_Hot_Target_Temp = 90;
            gu8_Hot_Preheat_Temp = 85;      //2025-07-29 cbr
            gu8_Hot_Target_Temp = 80;       //2025-07-29 cbr
        }
        break;

    case HOT_SET_TEMP____85oC:
        // [25-02-21 13:25:54] yspark, 85도 100도와 동일하게 온도 설정
        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {  // 저전력
            //gu8_Hot_Preheat_Temp = 98;
            // gu8_Hot_Preheat_Temp = 100;			// ★2025-06-02 Phil
            // gu8_Hot_Target_Temp = 98;//100;     //2025-07-15 cbr
            if (F_firstEffluent_hotWater)
            {  // 둘째 잔
                gu8_Hot_Preheat_Temp = 100;
                gu8_Hot_Target_Temp = 95;
            }
            else
            {  // 첫잔
                gu8_Hot_Preheat_Temp = 100;
                gu8_Hot_Target_Temp = 100;
            }
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {  // 고전력
            gu8_Hot_Preheat_Temp = 91;//98;     //2025-07-15 cbr
            //gu8_Hot_Target_Temp = 100;
            gu8_Hot_Target_Temp = 93;//96;		//2025-07-15 cbr
        }
        else
        {  // 상시
            gu8_Hot_Preheat_Temp = 98;
            //gu8_Hot_Target_Temp = 100;
            gu8_Hot_Target_Temp = 97;		// ★2025-06-02 Phil
        }

        break;

    case HOT_SET_TEMP____90oC:
        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {
            // 저전력
            if(F_Airvent_TargetTempDown == SET)
            {
                gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
            }
            else
            {
                gu8_Hot_Preheat_Temp = 98;
            }
            // gu8_Hot_Preheat_Temp = 98;
            gu8_Hot_Target_Temp = 100;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {
            // 고전력
            gu8_Hot_Preheat_Temp = 85;          //2025-07-14 cbr
            gu8_Hot_Target_Temp = 97;//100;     //2025-07-14 cbr
        }
        else
        {
            // 상시
            if(F_Airvent_TargetTempDown == SET)
            {
                gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
            }
            else
            {
                gu8_Hot_Preheat_Temp = 85;// ??2025-06-18 Phil
            }

            // gu8_Hot_Preheat_Temp = 85;// ★2025-06-02 Phil
            gu8_Hot_Target_Temp = 98;//100;     //2025-07-14 cbr
        }
        break;

    case HOT_SET_TEMP____95oC:
        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {
            // 저전력
            if(F_Airvent_TargetTempDown == SET)
            {
                gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
            }
            else
            {
                gu8_Hot_Preheat_Temp = 98;
            }

            // gu8_Hot_Preheat_Temp = 98;
            gu8_Hot_Target_Temp = 100;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {
            // 고전력
            gu8_Hot_Preheat_Temp = 85;          //2025-07-14 cbr
            gu8_Hot_Target_Temp = 97;//100;     //2025-07-14 cbr
        }
        else
        {
            // 상시
            if(F_Airvent_TargetTempDown == SET)
            {
                gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
            }
            else
            {
                gu8_Hot_Preheat_Temp = 85;
            }

            // gu8_Hot_Preheat_Temp = 85;// ★2025-06-02 Phil
            gu8_Hot_Target_Temp = 98;//100;     //2025-07-14 cbr
        }
        break;

    case HOT_SET_TEMP____100oC:
        if(u16Heater_Power_Save <= HEATER_POWER_LOW)
        {
            // 저전력
            if(F_Airvent_TargetTempDown == SET)
            {
                gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
            }
            else
            {
                gu8_Hot_Preheat_Temp = 98;
            }

            // gu8_Hot_Preheat_Temp = 98;
            gu8_Hot_Target_Temp = 100;
        }
        else if (u16Heater_Power_Save >= HEATER_POWER_HIGH)
        {
            // 고전력
            gu8_Hot_Preheat_Temp = 85;          //2025-07-14 cbr
            gu8_Hot_Target_Temp = 97;//100;     //2025-07-14 cbr
        }
        else
        {
            // 상시
            if(F_Airvent_TargetTempDown == SET)
            {
                gu8_Hot_Preheat_Temp = 82;  //cbr 2025-12-18
            }
            else
            {
                gu8_Hot_Preheat_Temp = 85;
            }

            // gu8_Hot_Preheat_Temp = 85; // ★2025-06-02 Phil
            gu8_Hot_Target_Temp = 98;//100;     //2025-07-14 cbr
        }
        break;

    default:

        gu8_Hot_Preheat_Temp = 0;
        gu8_Hot_Target_Temp = 0;

        break;
    }
}
