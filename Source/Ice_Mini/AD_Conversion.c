/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : System_init.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "AD_Conversion.h"
#include    "Temp_Table.h"

/***********************************************************************************************************************/

void AD_Conversion(void);
U16 get_adc_value( U8 ad_channel, U8 resolution);
void filtering_dc_current_24V_adc( U16 mu16ad_result );
void filtering_dc_current_12V_adc( U16 mu16ad_result );
void filtering_drain_pump_current_adc( U16 mu16ad_result );
void filtering_hot_tank_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_HotTankWater(U16 mu16Adc);
void filtering_hot_pump_current_adc( U16 mu16ad_result );

void filtering_uv_water_faucet_current_feed_adc( U16 mu16ad_result );
void filtering_uv_ice_faucet_one_current_feed_adc( U16 mu16ad_result );
void filtering_uv_ice_tray_1_2_current_feed_adc( U16 mu16ad_result );
void filtering_uv_ice_tank_1_2_current_feed_adc( U16 mu16ad_result );
void FILTERING_UV_ICE_TANK3_CURRENT_FEED_ADC( U16 mu16ad_result );

void filtering_uv_water_tank_current_feed_adc( U16 mu16ad_result );         /* 미사용 */

void filtering_ice_full_adc( U16 mu16ad_result );
void filtering_ice_Low_adc( U16 mu16ad_result );
void filtering_leakage_adc( U16 mu16ad_result );
void filtering_eva_1_temp_adc( U16 mu16ad_result );
//void filtering_eva_2_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_Eva(U16 mu16Adc);
void filtering_cold_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_ColdWater(U16 mu16Adc);
void filtering_room_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_RoomWater(U16 mu16Adc);
///void filtering_mixing_temp_adc( U16 mu16ad_result );
///U16 ConvAdc2Temp_MixingOutWater(U16 mu16Adc);
void filtering_amb_temp_adc( U16 mu16ad_result );
void filtering_amb_side_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_Ambient(U16 mu16Adc);
void filtering_fan_current_adc( U16 mu16ad_result );
void filtering_heater_ice_door_current_adc( U16 mu16ad_result );
//void filtering_uv_ice_tray_1_2_current_feed_adc( U16 mu16ad_result );
//void filtering_tray_temp_adc( U16 mu16ad_result );
//U16 ConvAdc2Temp_HotOutWater(U16 mu16Adc);

//void filtering_tds_in_temp_adc( U16 mu16ad_result );
//U16 ConvAdc2Temp_TDS_In_Water(U16 mu16Adc);
void filtering_uv_ice_faucet_two_current_adc( U16 mu16ad_result );
void filtering_heater_current_feed_adc( U16 mu16ad_result );

void filtering_hot_heater_adc( U16 mu16ad_result );
void filtering_hot_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_HotOutWater(U16 mu16Adc);
void filtering_hot_in_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_HotInWater(U16 mu16Adc);

/***********************************************************************************************************************/
/*..hui [17-11-24오후 1:47:00] 드레인펌프 피드백 전류..*/
U16 gu16_AD_Result_Cold;
U16 gu16ADIceFull;
U16 gu16ADCds;
U16 gu16ADLeakage;
//U8 gu8_AD_Result_Eva_First;
U16 gu16_AD_Result_Amb;
U16 gu16_AD_Result_Room;


U8 u8AdCount;

U16 gu16_AD_Drain_Pump_Current;
U16 u16Max_Drain_Pump_Current_AD;
U16 u16Min_Drain_Pump_Current_AD;
U32 u32AD_Drain_Pump_Current_Sum;
U8 u8Cnt_Drain_Pump_Current;




U16 gu16_AD_Tray_Pump_Current;
U16 u16Max_Hot_Pump_Current_AD;
U16 u16Min_Hot_Pump_Current_AD;
U32 u32AD_Hot_Pump_Current_Sum;
U8 u8Cnt_Hot_Pump_Current;


U16 u16Max_Cold_Temp_AD;
U16 u16Min_Cold_Temp_AD;
U32 u32AD_Cold_Temp_Sum;
U8 u8Cnt_Cold_Temp;
U16 gu16_Cold_Temperature;
U8 gu8_Cold_Temperature_One_Degree;


U16 u16Max_Amb_Temp_AD;
U16 u16Min_Amb_Temp_AD;
U32 u32AD_Amb_Temp_Sum;
U8 u8Cnt_Amb_Temp;
U16 gu16_Amb_Front_Temperature;
U8 gu8_Amb_Front_Temperature_One_Degree;

U8 gu8_Amb_Temperature_One_Degree;


U16 gu16_AD_Result_Eva_First;
U16 u16Max_Eva_1_Temp_AD;
U16 u16Min_Eva_1_Temp_AD;
U32 u32AD_Eva_1_Temp_Sum;
U8 u8Cnt_Eva_1_Temp;
U16 gu16_Eva_First_Temperature;
U8 gu8_Eva_Cold_Temperature_One_Degree;

U16 u16Max_Room_Temp_AD;
U16 u16Min_Room_Temp_AD;
U32 u32AD_Room_Temp_Sum;
U8 u8Cnt_Room_Temp;
U16 gu16_Room_Temperature;
U8 gu8_Room_Temperature_One_Degree;


U16 gu16_AD_Result_Hot_Out;
U16 u16Max_Hot_Temp_AD;
U16 u16Min_Hot_Temp_AD;
U32 u32AD_Hot_Temp_Sum;
U8 u8Cnt_Hot_Temp;
U16 gu16_Hot_Out_Temperature;
U8 gu8_Hot_Out_Temperature_One_Degree;

U16 u16Max_Ice_Full_Temp_AD;
U16 u16Min_Ice_Full_Temp_AD;
U32 u32AD_Ice_Full_Temp_Sum;
U8 u8Cnt_Ice_Full_Temp;

U16 u16Max_Leakage_AD;
U16 u16Min_Leakage_AD;
U32 u32AD_Leakage_Sum;
U8 u8Cnt_Leakage;

U16 u16Max_CDS_AD;
U16 u16Min_CDS_AD;
U32 u32AD_CDS_Sum;
U8 u8Cnt_CDS;


U16 gu16_AD_Result_TDS_In_Temp;
U16 gu16Max_TDS_In_Temp_AD;
U16 gu16Min_TDS_In_Temp_AD;
U16 gu16AD_TDS_In_Temp_Sum;
U8 u8Cnt_TDS_In_Temp;

U16 gu16_AD_Result_Fan_Current;
U16 gu16Max_Fan_Current_Data_AD;
U16 u16Min_Fan_Current_Data_AD;
U32 u32AD_Fan_Current_Sum;
U8 u8Cnt_Fan_Current_Data;

U16 gu16_AD_Result_UV_Ice_Tank_1_2_Current;
U16 gu16Max_UV_Ice_Tank_1_2_Current_Feed_AD;
U16 gu16Min_UV_Ice_Tank_1_2_Current_Feed_AD;
U32 u32AD_UV_Ice_Tank_1_2_Current_Feed_Sum;
U8 u8Cnt_UV_Ice_Tank_1_2_Current_Feed;

U16 gu16_AD_Result_UV_Ice_Faucet_One_Current;
U16 gu16Max_UV_Ice_Faucet_One_Current_Feed_AD;
U16 gu16Min_UV_Ice_Faucet_One_Current_Feed_AD;
U32 u32AD_UV_Ice_Faucet_One_Current_Feed_Sum;
U8 u8Cnt_UV_Ice_Faucet_One_Current_Feed;

U16 gu16_AD_Result_Hot_Tank_Temp;
U16 u16Max_Hot_Tank_Temp_AD;
U16 u16Min_Hot_Tank_Temp_AD;
U32 u32AD_Hot_Tank_Temp_Sum;
U8 u8Cnt_Hot_Tank_Temp;
U8 gu8_Hot_Tank_Temperature_One_Degree;
U16 gu16_Hot_Tank_Temperature;

U16 gu16_AD_Result_DC_Current_24V;
U16 gu16Max_DC_Current_24V_AD;
U16 gu16Min_DC_Current_24V_AD;
U32 gu32AD_DC_Current_24V_Sum;
U8 u8Cnt_DC_Current_24V;

U16 gu16_AD_Result_DC_Current_12V;
U16 gu16Max_DC_Current_12V_AD;
U16 u16Min_DC_Current_12V_AD;
U32 u32AD_DC_Current_12V_Sum;
U8 u8Cnt_DC_Current_12V;

U16 gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed;
U16 gu16Max_UV_Ice_Tray_1_2_Current_Feed_AD;
U16 gu16Min_UV_Ice_Tray_1_2_Current_Feed_AD;
U32 u32AD_UV_Ice_Tray_1_2_Current_Feed_Sum;
U8 u8Cnt_UV_Ice_Tray_1_2_Current_Feed;


U16 gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed;
U16 gu16Max_UV_Water_Tank_Current_Feed_AD;
U16 gu16Min_UV_Water_Tank_Current_Feed_AD;
U32 u32AD_UV_Water_Tank_Current_Feed_Sum;
U8 u8Cnt_UV_Water_Tank_Current_Feed;

U16 gu16_AD_Result_Amb_Side;
U16 u16Max_Amb_Side_Temp_AD;
U16 u16Min_Amb_Side_Temp_AD;
U32 u32AD_Amb_Side_Temp_Sum;
U8 u8Cnt_Amb_Side_Temp;
U16 gu16_Amb_Side_Temperature;
U8 gu8_Amb_Side_Temperature_One_Degree;

U16 gu16_AD_Result_UV_Ice_Faucet_Two_Current;
U16 gu16Max_UV_Ice_Faucet_Two_Current_AD;
U16 gu16Min_UV_Ice_Faucet_Two_Current_AD;
U32 u32AD_UV_Ice_Faucet_Two_Current_Sum;
U8 u8Cnt_UV_Ice_Faucet_Two_Current;

U16 gu16_AD_Result_Heater_Current_Feed;
U16 gu16Max_Heater_Current_Feed_AD;
U16 gu16Min_Heater_Current_Feed_AD;
U32 u32AD_Heater_Current_Feed_Sum;
U8 u8Cnt_Heater_Current_Feed;

U16 gu16_AD_Result_Hot_Heater;
U16 u16Max_Hot_Heater_Temp_AD;
U16 u16Min_Hot_Heater_Temp_AD;
U32 u32AD_Hot_Heater_Temp_Sum;
U8 u8Cnt_Hot_Heater_Temp;
U16 gu16_Hot_Heater_Temperature;
U8 gu8_Hot_Heater_Temperature_One_Degree;

U16 gu16_AD_Result_Hot_In;
U16 gu16Max_Hot_In_Temp_AD;
U16 gu16Min_Hot_In_Temp_AD;
U32 gu32AD_Hot_In_Temp_Sum;
U8 gu8Cnt_Hot_In_Temp;
U16 gu16_Hot_In_Temperature;
U8 gu8_Hot_In_Temperature_One_Degree;

U16 gu16_AD_Result_UV_Water_Faucet_Current_Feed;
U16 gu16Max_UV_Water_Faucet_Current_Feed_AD;
U16 gu16Min_UV_Water_Faucet_Current_Feed_AD;
U32 u32AD_UV_Water_Faucet_Current_Feed_Sum;
U8 u8Cnt_UV_Water_Faucet_Current_Feed;

U16 u16Max_Ice_Low_Temp_AD;
U16 u16Min_Ice_Low_Temp_AD;
U32 u32AD_Ice_Low_Temp_Sum;
U8 u8Cnt_Ice_Low_Temp;
U16 gu16ADIceLow;

U16 gu16Max_UV_Ice_Tank_3_Current_Feed_AD;
U16 gu16Min_UV_Ice_Tank_3_Current_Feed_AD;
U32 u32AD_UV_Ice_Tank_3_Current_Feed_Sum;
U8 u8Cnt_UV_Ice_Tank_3_Current_Feed;
U16 gu16_AD_Result_UV_Ice_Tank_3_Current_Feed;

U16 gu16Max_UV_Ice_Tray_1_2_Current_Feed_AD;
U16 gu16Min_UV_Ice_Tray_1_2_Current_Feed_AD;
U32 u32AD_UV_Ice_Tray_1_2_Current_Feed_Sum;
U8 u8Cnt_UV_Ice_Tray_1_2_Current_Feed;
U16 gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed;

// [25-02-20 13:36:42] yspark
U16 Testgu16ADHeaterMax = 0;

/* Ice Door Heater ADC Values 250228 CH.PARK */
U16 gu16_AD_Result_IceDoor_Heater_Current;
U16 gu16Max_IceDoor_Heater_Current_Data_AD;
U16 u16Min_IceDoor_Heater_Current_Data_AD;
U32 u32AD_IceDoor_Heater_Current_Sum;
U8 u8Cnt_IceDoor_Heater_Current_Data;

#if 0
U16 gu16_TDS_Out_Temperature;
U8 gu8_TDS_Out_Temperature_One_Degree;
U16 gu16_AD_Result_TDS_Out_Org_Temp;

U16 gu16_AD_Result_TDS_Out_Data;
U16 gu16Max_TDS_Out_Data_AD;
U16 u16Min_TDS_Out_Data_AD;
U16 u16AD_TDS_Out_Data_Sum;
U8 u8Cnt_TDS_Out_Data;
U16 gu16AD_TDS_Out_Temp_Sum;
#endif

U8 gu8_test_hot_heater_value;           // 히터 내부온도 ok
U8 gu8_test_hot_out_value;              // 온수 출수온도 ok
U8 gu8_test_hot_in_value;               // 온수 입수온도 ok
U8 gu8_test_room_temp_value;            // 정수 온도 ok
U8 gu8_test_cold_temp_value;            // 냉수 온도 ok
U8 gu8_test_amb_front_value;            // 외기온도 1 ok
U8 gu8_test_amb_side_value;             // 외기온도 2 ok
U8 gu8_test_eva_cold_temp_value;        // 증발기 온도 ok
U16 gu16_test_leakage_valve;            // 누수 ok
U16 gu16_test_pump_drain_valve;         // 드레인펌프 전류 adc ok
U16 gu16_test_uv_extract_faucet_value;  // 출수파우셋 uv adc ok
U16 gu16_test_uv_ice_faucet_1_value;    // 얼음파우셋 1 uv adc ok
U16 gu16_test_uv_ice_faucet_2_value;    // 얼음파우셋 2 uv adc ok
U16 gu16_test_uv_ice_tray_value;        // 얼음트레이 uv adc ok
U16 gu16_test_uv_ice_tank_1_2_value;    // 얼음탱크 1,2 uv adc ok
U16 gu16_test_uv_ice_tank_3_value;      // 얼음탱크 3 uv adc ok
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void AD_Conversion(void)
{
    U16 ad_result = 0;
    U8 mu8_ad_channel;

    u8AdCount++;

    switch(u8AdCount)
    {
        case AD_Count_1:
                /* 24V 전압 입력 피드백 */
               ad_result = get_adc_value( (U8)AD_Channel_DC_Current_24V,
                                           AD_CONV_10BIT);

               filtering_dc_current_24V_adc(ad_result);
               break;

        case AD_Count_2:
                /* 12V 전압 입력 피드백 */
               ad_result = get_adc_value( (U8)AD_Channel_DC_Current_12V,
                                           AD_CONV_10BIT);

               filtering_dc_current_12V_adc(ad_result);

               break;

        case AD_Count_3:
               /*..hui [17-11-24오후 2:38:16] 누수..*/
               ad_result = get_adc_value( (U8)AD_Channel_Water_Leakage,
                                           AD_CONV_10BIT);

               filtering_leakage_adc(ad_result);
               break;

        case AD_Count_4:
                /*..hui [24-12-16오후 1:10:52] 온수 히터 온도센서..*/
                ad_result = get_adc_value( (U8)AD_Channel_Hot_Heater_Temp,
                                            AD_CONV_10BIT);

                filtering_hot_heater_adc(ad_result);

                gu16_Hot_Heater_Temperature = ConvAdc2Temp_HotOutWater(gu16_AD_Result_Hot_Heater);
                
                /* 신뢰성팀 디버깅용 */
                if(gu8_test_hot_heater_value > 0)
                {
                    gu8_Hot_Heater_Temperature_One_Degree = gu8_test_hot_heater_value;
                }
                else
                {
                    gu8_Hot_Heater_Temperature_One_Degree = (U8)((gu16_Hot_Heater_Temperature + 5) / 10);
                }
               
               break;

        case AD_Count_5:
               /*..hui [24-12-16오후 1:10:59] 온수 추출 온도센서..*/
                ad_result = get_adc_value( (U8)AD_Channel_Hot_Out_Temp,
                                            AD_CONV_10BIT );

                filtering_hot_temp_adc(ad_result);

                gu16_Hot_Out_Temperature = ConvAdc2Temp_HotOutWater(gu16_AD_Result_Hot_Out);
                if(bit_ice_tank_ster_start == CLEAR)
                {
                    if(gu8_test_hot_out_value > 0)
                    {
                        gu8_Hot_Out_Temperature_One_Degree = gu8_test_hot_out_value;
                    }
                    else
                    {
                        gu8_Hot_Out_Temperature_One_Degree = (U8)((gu16_Hot_Out_Temperature + 5) / 10);
                    }
                }
                else {  }
            break;

        case AD_Count_6:
               /*..hui [24-12-16오후 1:11:06] 온수 입수 온도센서..*/
               ad_result = get_adc_value( (U8)AD_Channel_Hot_In_Temp,
                                           AD_CONV_10BIT );

               filtering_hot_in_temp_adc(ad_result);

               gu16_Hot_In_Temperature = ConvAdc2Temp_HotInWater(gu16_AD_Result_Hot_In);

               if(gu8_test_hot_in_value > 0)
               {
                    gu8_Hot_In_Temperature_One_Degree = gu8_test_hot_in_value;
               }
               else
               {
                    gu8_Hot_In_Temperature_One_Degree = (U8)((gu16_Hot_In_Temperature + 5) / 10);
               }
               break;

        case AD_Count_7:
               /*..hui [17-11-24오후 2:37:48] 외기 온도센서 1..*/
               ad_result = get_adc_value( (U8)AD_Channel_Amb_Temp,
                                           AD_CONV_10BIT );


               filtering_amb_temp_adc(ad_result);

               gu16_Amb_Front_Temperature = ConvAdc2Temp_Ambient(gu16_AD_Result_Amb);
               if(gu8_test_amb_front_value > 0)
               {
                    gu8_Amb_Front_Temperature_One_Degree = gu8_test_amb_front_value;
               }
               else
               {
                    gu8_Amb_Front_Temperature_One_Degree = (U8)((gu16_Amb_Front_Temperature + 5) / 10);
               }
               break;

        case AD_Count_8:
               /*..hui [17-11-24오후 2:37:56] 에바 온도센서..*/
               ad_result = get_adc_value( (U8)AD_Channel_EVA_1_TEMP,
                                           AD_CONV_10BIT );

               filtering_eva_1_temp_adc(ad_result);

               /*..hui [23-6-30오후 5:45:47] 웨스턴은 EVA 온도 1개.. 얼음임..*/
               gu16_Eva_First_Temperature = ConvAdc2Temp_Eva(gu16_AD_Result_Eva_First);
               
                if(gu8_test_eva_cold_temp_value > 0)
                {
                    gu8_Eva_Cold_Temperature_One_Degree = gu8_test_eva_cold_temp_value;
                }
                else
                {
                    gu8_Eva_Cold_Temperature_One_Degree = (U8)((gu16_Eva_First_Temperature + 5) / 10);
                }
               break;

        case AD_Count_9:
               /*..hui [17-11-24오후 2:38:01] 정수 온도센서..*/
               ad_result = get_adc_value( (U8)AD_Channel_Room_Temp,
                                           AD_CONV_10BIT );

               if( bit_adc_room_start == SET && pROOM_TH_POWER == SET)
               {
                   filtering_room_temp_adc(ad_result);

                   gu16_Room_Temperature = ConvAdc2Temp_RoomWater(gu16_AD_Result_Room);
                   
                    
                    if(gu8_test_room_temp_value > 0)
                    {
                        gu8_Room_Temperature_One_Degree = gu8_test_room_temp_value;
                    }
                    else
                    {
                        gu8_Room_Temperature_One_Degree = (U8)((gu16_Room_Temperature + 5) / 10);
                    }

                    if(bit_ice_tank_ster_start == SET)
                    {
                        if(gu8_test_hot_out_value > 0)
                        {
                            gu8_Hot_Out_Temperature_One_Degree = gu8_test_hot_out_value;
                        }
                        else
                        {
                            gu8_Hot_Out_Temperature_One_Degree = gu8_Room_Temperature_One_Degree;                        
                        }
                    }
               }
               else{}

               break;

        case AD_Count_10:
               /*..hui [17-11-24오후 2:37:41] 냉수 온도센서..*/
               ad_result = get_adc_value( (U8)AD_Channel_Cold_Temp,
                                           AD_CONV_10BIT );

               if( bit_adc_cold_start == SET && pCOLD_TH_POWER == SET )
               {
                   filtering_cold_temp_adc(ad_result);

                   if(gu8_test_cold_temp_value > 0)
                   {
                        gu16_Cold_Temperature = (gu8_test_cold_temp_value * 10);
                        gu8_Cold_Temperature_One_Degree = gu8_test_cold_temp_value;
                   }
                   else
                   {
                        gu16_Cold_Temperature = ConvAdc2Temp_ColdWater(gu16_AD_Result_Cold);
                        gu8_Cold_Temperature_One_Degree = (U8)((gu16_Cold_Temperature + 5) / 10);
                   }
               }
               else{}

               break;

        case AD_Count_11:
               /*..hui [24-12-16오후 1:11:28] 드레인 펌프 전류..*/
               ad_result = get_adc_value( (U8)AD_Channel_Drain_Pump_Current,
                                           AD_CONV_10BIT );

               filtering_drain_pump_current_adc(ad_result);

               break;

        case AD_Count_12:
               /*..hui [25-1-24오후 5:29:03] 출수 파우셋 UV..*/
               ad_result = get_adc_value( (U8)AD_Channel_UV_Water_Faucet_Current,
                                           AD_CONV_10BIT);

               filtering_uv_water_faucet_current_feed_adc(ad_result);

               break;

        case AD_Count_13:
               /*..hui [25-1-24오후 5:29:12] 얼음 파우셋 UV 1..*/
               ad_result = get_adc_value( (U8)AD_Channel_UV_Ice_Faucet_1_Current,
                                           AD_CONV_10BIT);

               filtering_uv_ice_faucet_one_current_feed_adc(ad_result);

               break;

        case AD_Count_14:
               /*..hui [25-1-24오후 5:29:20] 얼음 파우셋 UV2..*/
               ad_result = get_adc_value( (U8)AD_Channel_UV_Ice_Faucet_2_Current,
                                           AD_CONV_10BIT);

               filtering_uv_ice_faucet_two_current_adc(ad_result);

               break;

        case AD_Count_15:
               /*..hui [25-1-24오후 5:29:30] 얼음탱크 UV 1,2..*/
               ad_result = get_adc_value( (U8)AD_Channel_UV_Ice_Tank_1_2_Current,
                                           AD_CONV_10BIT);

               filtering_uv_ice_tank_1_2_current_feed_adc(ad_result);

               break;

        case AD_Count_16:
               /*..hui [17-11-24오후 2:38:10] 만빙 수신..*/
               ad_result = get_adc_value( (U8)AD_Channel_Ice_Full_Receive_1,
                                           AD_CONV_10BIT);

               filtering_ice_full_adc(ad_result);

               break;

        case AD_Count_17:
               /*..hui [25-1-24오후 5:30:27] 아이스트레이 UV1,2..*/
               ad_result = get_adc_value( (U8)AD_Channel_UV_Ice_Tray_1_2_Current,
                                           AD_CONV_10BIT);

               filtering_uv_ice_tray_1_2_current_feed_adc(ad_result);

               break;


        case AD_Count_18:
               /*..hui [24-12-16오후 1:12:15] 히터 전류 피드백..*/
               ad_result = get_adc_value( (U8)AD_Channel_Hot_Heater_Current,
                                           AD_CONV_10BIT);

               filtering_heater_current_feed_adc(ad_result);
               break;

        case AD_Count_19:
               /*..hui [24-12-16오후 1:12:25] 외기 온도센서 2 ..*/
               ad_result = get_adc_value( (U8)AD_Channel_Amb_2_Temp,
                                           AD_CONV_10BIT );

               filtering_amb_side_temp_adc(ad_result);

               gu16_Amb_Side_Temperature = ConvAdc2Temp_Ambient(gu16_AD_Result_Amb_Side);
               if(gu8_test_amb_side_value > 0)
               {
                  gu8_Amb_Side_Temperature_One_Degree = gu8_test_amb_side_value;
               
               }
               else
               {
                  gu8_Amb_Side_Temperature_One_Degree = (U8)((gu16_Amb_Side_Temperature + 5) / 10);   
               }

               break;

        case AD_Count_20:
               /*..hui [24-12-16오후 1:12:31] 팬 피드백 전류..*/
               ad_result = get_adc_value( (U8)AD_Channel_FAN_Current,
                                           AD_CONV_10BIT );

               filtering_fan_current_adc(ad_result);
               
               break;

        case AD_Count_21:
                /* 얼음탱크 저빙센서 추가 250210 @CH.PARK */
                ad_result = get_adc_value( (U8)AD_Channel_Ice_Full_Receive_2,
                                           AD_CONV_10BIT );

                filtering_ice_Low_adc(ad_result);

                break;

        case AD_Count_22:
                /* 얼음탱크 도어 히터 전류 피드백 추가 250210 @CH.PARK */
                ad_result = get_adc_value( (U8)AD_Channel_Ice_Door_Heater_IAD,
                                           AD_CONV_10BIT );
                
                filtering_heater_ice_door_current_adc(ad_result);
                break;

        case AD_Count_23:
                /* 얼음저장고 UV LED 전류피드백 250225 CH.PARK */
                ad_result = get_adc_value( (U8)AD_Channel_UV_Ice_Tank_3_Current,
                                            AD_CONV_10BIT);

                FILTERING_UV_ICE_TANK3_CURRENT_FEED_ADC(ad_result);
                u8AdCount = 0;
            break;

        default:

               ADS = AD_Channel_DC_Current_24V;
               u8AdCount = 0;

               break;
    }
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 get_adc_value( U8 ad_channel, U8 resolution)
{
    U16 mu16_ad_result = 0;
    U16 mu16_final_ad_value = 0;

    ADC_Stop();

    ADS = ad_channel;
    ADCE = 1U;  /* enable AD comparator */

    ADC_Start();

    while(ADIF != SET){}

    ADC_Stop();
    ADCE = 0U;  /* disable AD comparator */

    mu16_ad_result = (U16)(ADCR >> resolution);

    /*..hui [17-11-24오후 2:11:20] ACD값 필터링....*/
    /*mu16_final_ad_value = filtering_adc_value( ad_old_value,
                                          mu16_ad_result );  */

    /*return mu16_final_ad_value;*/

    return mu16_ad_result;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_dc_current_24V_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_DC_Current_24V_AD)    //Max Save
    {
        gu16Max_DC_Current_24V_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_DC_Current_24V_AD)  //Min   Save
    {
        gu16Min_DC_Current_24V_AD = mu16ad_result;
    }

    gu32AD_DC_Current_24V_Sum += mu16ad_result;

    if(++u8Cnt_DC_Current_24V >= 12)                   // Sum = count +   Max +   Min
    {
        u8Cnt_DC_Current_24V = 0;
        gu16_AD_Result_DC_Current_24V
            = (U16)(gu32AD_DC_Current_24V_Sum - gu16Max_DC_Current_24V_AD - gu16Min_DC_Current_24V_AD) / 10;

        gu32AD_DC_Current_24V_Sum  = 0;
        gu16Max_DC_Current_24V_AD = 0;
        gu16Min_DC_Current_24V_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_dc_current_12V_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_DC_Current_12V_AD)    //Max Save
    {
        gu16Max_DC_Current_12V_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_DC_Current_12V_AD)  //Min   Save
    {
        u16Min_DC_Current_12V_AD = mu16ad_result;
    }

    u32AD_DC_Current_12V_Sum += mu16ad_result;

    if(++u8Cnt_DC_Current_12V >= 12)                   // Sum = count +   Max +   Min
    {
        u8Cnt_DC_Current_12V = 0;
        gu16_AD_Result_DC_Current_12V
            = (U16)(u32AD_DC_Current_12V_Sum - gu16Max_DC_Current_12V_AD - u16Min_DC_Current_12V_AD) / 10;

        /*gu16_AD_Result_DC_Current_12V = 1024 - gu16_AD_Result_DC_Current_12V;*/

        u32AD_DC_Current_12V_Sum  = 0;
        gu16Max_DC_Current_12V_AD = 0;
        u16Min_DC_Current_12V_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_drain_pump_current_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Drain_Pump_Current_AD)    //Max Save
    {
        u16Max_Drain_Pump_Current_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Drain_Pump_Current_AD)  //Min   Save
    {
        u16Min_Drain_Pump_Current_AD = mu16ad_result;
    }

    u32AD_Drain_Pump_Current_Sum += mu16ad_result;

    if(++u8Cnt_Drain_Pump_Current >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Drain_Pump_Current = 0;

        if(gu16_test_pump_drain_valve > 0)
        {
            gu16_AD_Drain_Pump_Current = gu16_test_pump_drain_valve;
        }
        else
        {
            gu16_AD_Drain_Pump_Current = (U16)(u32AD_Drain_Pump_Current_Sum - u16Max_Drain_Pump_Current_AD - u16Min_Drain_Pump_Current_AD) / 50;
        }

        u32AD_Drain_Pump_Current_Sum  = 0;
        u16Max_Drain_Pump_Current_AD = 0;
        u16Min_Drain_Pump_Current_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_hot_tank_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Hot_Tank_Temp_AD)    //Max Save
    {
        u16Max_Hot_Tank_Temp_AD = (U16)mu16ad_result;
    }

    if(mu16ad_result < u16Min_Hot_Tank_Temp_AD)  //Min   Save
    {
        u16Min_Hot_Tank_Temp_AD = (U16)mu16ad_result;
    }

    u32AD_Hot_Tank_Temp_Sum += (U16)mu16ad_result;

    if(++u8Cnt_Hot_Tank_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Hot_Tank_Temp = 0;
        gu16_AD_Result_Hot_Tank_Temp = (U16)(u32AD_Hot_Tank_Temp_Sum - u16Max_Hot_Tank_Temp_AD - u16Min_Hot_Tank_Temp_AD) / 50;
        /*..hui [23-2-8오후 4:07:44] 풀다운을 풀업으로 변경...*/
        gu16_AD_Result_Hot_Tank_Temp = 1024 - gu16_AD_Result_Hot_Tank_Temp;

        u32AD_Hot_Tank_Temp_Sum  = 0;
        u16Max_Hot_Tank_Temp_AD = 0;
        u16Min_Hot_Tank_Temp_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_HotTankWater(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_HOT_WATER )
    {
        return 0;  // min temperture..
    }

    if( mu16Adc > MAX_ADC_HOT_WATER )
    {
        return 1000;  // max temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_HOT_WATER;
    return temp_hot_tank_water_table[ mu16Index ];
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_hot_pump_current_adc( U16 mu16ad_result )
{

    if(mu16ad_result > u16Max_Hot_Pump_Current_AD)    //Max Save
    {
        u16Max_Hot_Pump_Current_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Hot_Pump_Current_AD)  //Min   Save
    {
        u16Min_Hot_Pump_Current_AD = mu16ad_result;
    }

    u32AD_Hot_Pump_Current_Sum += mu16ad_result;

    if(++u8Cnt_Hot_Pump_Current >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Hot_Pump_Current = 0;
        gu16_AD_Tray_Pump_Current = (U16)(u32AD_Hot_Pump_Current_Sum - u16Max_Hot_Pump_Current_AD - u16Min_Hot_Pump_Current_AD) / 50;

        u32AD_Hot_Pump_Current_Sum  = 0;
        u16Max_Hot_Pump_Current_AD = 0;
        u16Min_Hot_Pump_Current_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void  filtering_uv_water_tank_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Water_Tank_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Water_Tank_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Water_Tank_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Water_Tank_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Water_Tank_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Water_Tank_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Water_Tank_Current_Feed = 0;
        gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed
            = (U16)(u32AD_UV_Water_Tank_Current_Feed_Sum - gu16Max_UV_Water_Tank_Current_Feed_AD - gu16Min_UV_Water_Tank_Current_Feed_AD) / 50;

        u32AD_UV_Water_Tank_Current_Feed_Sum  = 0;
        gu16Max_UV_Water_Tank_Current_Feed_AD = 0;
        gu16Min_UV_Water_Tank_Current_Feed_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_uv_water_faucet_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Water_Faucet_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Water_Faucet_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Water_Faucet_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Water_Faucet_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Water_Faucet_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Water_Faucet_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Water_Faucet_Current_Feed = 0;
        
        if(gu16_test_uv_extract_faucet_value > 0)
        {
            gu16_AD_Result_UV_Water_Faucet_Current_Feed = gu16_test_uv_extract_faucet_value;
        }
        else
        {
            gu16_AD_Result_UV_Water_Faucet_Current_Feed
            = (U16)(u32AD_UV_Water_Faucet_Current_Feed_Sum - gu16Max_UV_Water_Faucet_Current_Feed_AD - gu16Min_UV_Water_Faucet_Current_Feed_AD) / 50;
        }

        u32AD_UV_Water_Faucet_Current_Feed_Sum  = 0;
        gu16Max_UV_Water_Faucet_Current_Feed_AD = 0;
        gu16Min_UV_Water_Faucet_Current_Feed_AD = 1024;
    }

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_uv_ice_faucet_one_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Ice_Faucet_One_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Ice_Faucet_One_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Ice_Faucet_One_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Ice_Faucet_One_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Ice_Faucet_One_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Ice_Faucet_One_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Ice_Faucet_One_Current_Feed = 0;

        if(gu16_test_uv_ice_faucet_1_value > 0)
        {
            gu16_AD_Result_UV_Ice_Faucet_One_Current = gu16_test_uv_ice_faucet_1_value;
        }
        else
        {
            gu16_AD_Result_UV_Ice_Faucet_One_Current
                = (U16)(u32AD_UV_Ice_Faucet_One_Current_Feed_Sum - gu16Max_UV_Ice_Faucet_One_Current_Feed_AD - gu16Min_UV_Ice_Faucet_One_Current_Feed_AD) / 50;
        }

        u32AD_UV_Ice_Faucet_One_Current_Feed_Sum  = 0;
        gu16Max_UV_Ice_Faucet_One_Current_Feed_AD = 0;
        gu16Min_UV_Ice_Faucet_One_Current_Feed_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_uv_ice_tank_1_2_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Ice_Tank_1_2_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Ice_Tank_1_2_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Ice_Tank_1_2_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Ice_Tank_1_2_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Ice_Tank_1_2_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Ice_Tank_1_2_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Ice_Tank_1_2_Current_Feed = 0;

        if(gu16_test_uv_ice_tank_1_2_value > 0)
        {
            gu16_AD_Result_UV_Ice_Tank_1_2_Current = gu16_test_uv_ice_tank_1_2_value;
        }
        else
        {
            gu16_AD_Result_UV_Ice_Tank_1_2_Current
                = (U16)(u32AD_UV_Ice_Tank_1_2_Current_Feed_Sum - gu16Max_UV_Ice_Tank_1_2_Current_Feed_AD - gu16Min_UV_Ice_Tank_1_2_Current_Feed_AD) / 50;
        }

        u32AD_UV_Ice_Tank_1_2_Current_Feed_Sum  = 0;
        gu16Max_UV_Ice_Tank_1_2_Current_Feed_AD = 0;
        gu16Min_UV_Ice_Tank_1_2_Current_Feed_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_uv_ice_tray_1_2_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Ice_Tray_1_2_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Ice_Tray_1_2_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Ice_Tray_1_2_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Ice_Tray_1_2_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Ice_Tray_1_2_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Ice_Tray_1_2_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Ice_Tray_1_2_Current_Feed = 0;

        if(gu16_test_uv_ice_tray_value > 0)
        {
            gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed = gu16_test_uv_ice_tray_value;
        }
        else
        {
            gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed
                = (U16)(u32AD_UV_Ice_Tray_1_2_Current_Feed_Sum - gu16Max_UV_Ice_Tray_1_2_Current_Feed_AD - gu16Min_UV_Ice_Tray_1_2_Current_Feed_AD) / 50;
        }

        u32AD_UV_Ice_Tray_1_2_Current_Feed_Sum  = 0;
        gu16Max_UV_Ice_Tray_1_2_Current_Feed_AD = 0;
        gu16Min_UV_Ice_Tray_1_2_Current_Feed_AD = 1024;
    }

}

/**
 * @brief UV TANK3 전류 피드백
 * 
 * @param mu16ad_result 
 */
void FILTERING_UV_ICE_TANK3_CURRENT_FEED_ADC( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Ice_Tank_3_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Ice_Tank_3_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Ice_Tank_3_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Ice_Tank_3_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Ice_Tank_3_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Ice_Tank_3_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Ice_Tank_3_Current_Feed = 0;

        if(gu16_test_uv_ice_tank_3_value > 0)
        {
            gu16_AD_Result_UV_Ice_Tank_3_Current_Feed = gu16_test_uv_ice_tank_3_value;
        }
        else
        {
            gu16_AD_Result_UV_Ice_Tank_3_Current_Feed
                = (U16)(u32AD_UV_Ice_Tank_3_Current_Feed_Sum - gu16Max_UV_Ice_Tank_3_Current_Feed_AD - gu16Min_UV_Ice_Tank_3_Current_Feed_AD) / 50;
        }

        u32AD_UV_Ice_Tank_3_Current_Feed_Sum  = 0;
        gu16Max_UV_Ice_Tank_3_Current_Feed_AD = 0;
        gu16Min_UV_Ice_Tank_3_Current_Feed_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_ice_full_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Ice_Full_Temp_AD)    //Max Save
    {
        u16Max_Ice_Full_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Ice_Full_Temp_AD)  //Min   Save
    {
        u16Min_Ice_Full_Temp_AD = mu16ad_result;
    }

    u32AD_Ice_Full_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Ice_Full_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Ice_Full_Temp = 0;
        gu16ADIceFull = (U16)(u32AD_Ice_Full_Temp_Sum - u16Max_Ice_Full_Temp_AD - u16Min_Ice_Full_Temp_AD) / 50;

        u32AD_Ice_Full_Temp_Sum  = 0;
        u16Max_Ice_Full_Temp_AD = 0;
        u16Min_Ice_Full_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_ice_Low_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Ice_Low_Temp_AD)    //Max Save
    {
        u16Max_Ice_Low_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Ice_Low_Temp_AD)  //Min   Save
    {
        u16Min_Ice_Low_Temp_AD = mu16ad_result;
    }

    u32AD_Ice_Low_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Ice_Low_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Ice_Low_Temp = 0;
        gu16ADIceLow = (U16)(u32AD_Ice_Low_Temp_Sum - u16Max_Ice_Low_Temp_AD - u16Min_Ice_Low_Temp_AD) / 50;

        u32AD_Ice_Low_Temp_Sum  = 0;
        u16Max_Ice_Low_Temp_AD = 0;
        u16Min_Ice_Low_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_leakage_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Leakage_AD)    //Max Save
    {
        u16Max_Leakage_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Leakage_AD)  //Min   Save
    {
        u16Min_Leakage_AD = mu16ad_result;
    }

    u32AD_Leakage_Sum += mu16ad_result;

    if(++u8Cnt_Leakage >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Leakage = 0;

        if(gu16_test_leakage_valve > 0)
        {
            gu16ADLeakage = gu16_test_leakage_valve;
        }
        else
        {
            gu16ADLeakage = (U16)((u32AD_Leakage_Sum - u16Max_Leakage_AD - u16Min_Leakage_AD) / 50);
        }

        u32AD_Leakage_Sum  = 0;
        u16Max_Leakage_AD = 0;
        u16Min_Leakage_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_eva_1_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Eva_1_Temp_AD)    //Max Save
    {
        u16Max_Eva_1_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Eva_1_Temp_AD)  //Min   Save
    {
        u16Min_Eva_1_Temp_AD = mu16ad_result;
    }

    u32AD_Eva_1_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Eva_1_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Eva_1_Temp = 0;
        gu16_AD_Result_Eva_First = (U16)((u32AD_Eva_1_Temp_Sum - u16Max_Eva_1_Temp_AD - u16Min_Eva_1_Temp_AD) / 50);
        /*..hui [23-2-8오후 4:07:44] 풀다운을 풀업으로 변경...*/
        gu16_AD_Result_Eva_First = 1024 - gu16_AD_Result_Eva_First;

        u32AD_Eva_1_Temp_Sum  = 0;
        u16Max_Eva_1_Temp_AD = 0;
        u16Min_Eva_1_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void filtering_eva_2_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Eva_2_Temp_AD)    //Max Save
    {
        u16Max_Eva_2_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Eva_2_Temp_AD)  //Min   Save
    {
        u16Min_Eva_2_Temp_AD = mu16ad_result;
    }

    u32AD_Eva_2_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Eva_2_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Eva_2_Temp = 0;
        gu16_AD_Result_Eva_Second = (U16)((u32AD_Eva_2_Temp_Sum - u16Max_Eva_2_Temp_AD - u16Min_Eva_2_Temp_AD) / 50);
        /*..hui [23-2-8오후 4:07:44] 풀다운을 풀업으로 변경...*/
        gu16_AD_Result_Eva_Second = 1024 - gu16_AD_Result_Eva_Second;

        u32AD_Eva_2_Temp_Sum  = 0;
        u16Max_Eva_2_Temp_AD = 0;
        u16Min_Eva_2_Temp_AD = 1024;
    }

}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_Eva(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_EVA_TEMP )
    {
        return 0;  // min temperture..
    }

    if( mu16Adc > MAX_ADC_EVA_TEMP )
    {
        return 1000;  // max temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_EVA_TEMP;
    return temp_eva_table[ mu16Index ];
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_cold_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Cold_Temp_AD)    //Max Save
    {
        u16Max_Cold_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Cold_Temp_AD)  //Min   Save
    {
        u16Min_Cold_Temp_AD = mu16ad_result;
    }

    u32AD_Cold_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Cold_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Cold_Temp = 0;
        gu16_AD_Result_Cold = (U16)((u32AD_Cold_Temp_Sum - u16Max_Cold_Temp_AD - u16Min_Cold_Temp_AD) / 50);

        u32AD_Cold_Temp_Sum  = 0;
        u16Max_Cold_Temp_AD = 0;
        u16Min_Cold_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_ColdWater(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_COLD_WATER )
    {
        return 900;  // max temperture..
    }

    if( mu16Adc > MAX_ADC_COLD_WATER )
    {
        return 0;  // min temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_COLD_WATER;
    return temp_cold_water_table[ mu16Index ];
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_room_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Room_Temp_AD)    //Max Save
    {
        u16Max_Room_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Room_Temp_AD)  //Min   Save
    {
        u16Min_Room_Temp_AD = mu16ad_result;
    }

    u32AD_Room_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Room_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Room_Temp = 0;
        gu16_AD_Result_Room = (U16)((u32AD_Room_Temp_Sum - u16Max_Room_Temp_AD - u16Min_Room_Temp_AD) / 50);

        u32AD_Room_Temp_Sum  = 0;
        u16Max_Room_Temp_AD = 0;
        u16Min_Room_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_RoomWater(U16 mu16Adc)
{
    /*return ConvAdc2Temp_ColdWater( mu16Adc );*/
    return ConvAdc2Temp_HotInWater( mu16Adc );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
U16 ConvAdc2Temp_HotInWater(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_HOT_IN_WATER )
    {
        return 900;  // max temperture..
    }

    if( mu16Adc > MAX_ADC_HOT_IN_WATER )
    {
        return 0;  // min temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_HOT_IN_WATER;
    return temp_hot_in_water_table[ mu16Index ];
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void filtering_mixing_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Mixing_Temp_AD)    //Max Save
    {
        u16Max_Mixing_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Mixing_Temp_AD)  //Min   Save
    {
        u16Min_Mixing_Temp_AD = mu16ad_result;
    }

    u32AD_Mixing_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Mixing_Temp >= 22)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Mixing_Temp = 0;
        gu16_AD_Result_Mixing_Out = (U16)((u32AD_Mixing_Temp_Sum - u16Max_Mixing_Temp_AD - u16Min_Mixing_Temp_AD) / 20);

        u32AD_Mixing_Temp_Sum  = 0;
        u16Max_Mixing_Temp_AD = 0;
        u16Min_Mixing_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_MixingOutWater(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_HOT_OUT_WATER )
    {
        return 1200;  // max temperture..
    }

    if( mu16Adc > MAX_ADC_HOT_OUT_WATER )
    {
        return 0;  // min temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_HOT_OUT_WATER;
    return temp_hot_out_water_table[ mu16Index ];
}
#endif


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_amb_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Amb_Temp_AD)    //Max Save
    {
        u16Max_Amb_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Amb_Temp_AD)  //Min   Save
    {
        u16Min_Amb_Temp_AD = mu16ad_result;
    }

    u32AD_Amb_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Amb_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Amb_Temp = 0;
        gu16_AD_Result_Amb = (U16)((u32AD_Amb_Temp_Sum - u16Max_Amb_Temp_AD - u16Min_Amb_Temp_AD) / 50);
        /*..hui [23-2-8오후 4:07:44] 풀다운을 풀업으로 변경...*/
        gu16_AD_Result_Amb = 1024 - gu16_AD_Result_Amb;

        u32AD_Amb_Temp_Sum  = 0;
        u16Max_Amb_Temp_AD = 0;
        u16Min_Amb_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_amb_side_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Amb_Side_Temp_AD)    //Max Save
    {
        u16Max_Amb_Side_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Amb_Side_Temp_AD)  //Min   Save
    {
        u16Min_Amb_Side_Temp_AD = mu16ad_result;
    }

    u32AD_Amb_Side_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Amb_Side_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Amb_Side_Temp = 0;
        gu16_AD_Result_Amb_Side = (U16)((u32AD_Amb_Side_Temp_Sum - u16Max_Amb_Side_Temp_AD - u16Min_Amb_Side_Temp_AD) / 50);
        /*..hui [23-2-8오후 4:07:44] 풀다운을 풀업으로 변경...*/
        gu16_AD_Result_Amb_Side = 1024 - gu16_AD_Result_Amb_Side;

        u32AD_Amb_Side_Temp_Sum  = 0;
        u16Max_Amb_Side_Temp_AD = 0;
        u16Min_Amb_Side_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_Ambient(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_AMBIENT_TEMP )
    {
        return 0;  // min temperture..
    }

    if( mu16Adc > MAX_ADC_AMBIENT_TEMP )
    {
        return 1000;  // max temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_AMBIENT_TEMP;
    return temp_ambient_table[ mu16Index ];
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_fan_current_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_Fan_Current_Data_AD)    //Max Save
    {
        gu16Max_Fan_Current_Data_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Fan_Current_Data_AD)  //Min   Save
    {
        u16Min_Fan_Current_Data_AD = mu16ad_result;
    }

    u32AD_Fan_Current_Sum += mu16ad_result;

    if(++u8Cnt_Fan_Current_Data >= 22)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Fan_Current_Data = 0;
        gu16_AD_Result_Fan_Current = (U16)(u32AD_Fan_Current_Sum - gu16Max_Fan_Current_Data_AD - u16Min_Fan_Current_Data_AD) / 20;

        u32AD_Fan_Current_Sum  = 0;
        gu16Max_Fan_Current_Data_AD = 0;
        u16Min_Fan_Current_Data_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : Ice Door Heater current feedback
***********************************************************************************************************************/
void filtering_heater_ice_door_current_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_IceDoor_Heater_Current_Data_AD)    //Max Save
    {
        gu16Max_IceDoor_Heater_Current_Data_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_IceDoor_Heater_Current_Data_AD)  //Min   Save
    {
        u16Min_IceDoor_Heater_Current_Data_AD = mu16ad_result;
    }

    u32AD_IceDoor_Heater_Current_Sum += mu16ad_result;

    if(++u8Cnt_IceDoor_Heater_Current_Data >= 22)                   // Sum = count +   Max +   Min
    {
        u8Cnt_IceDoor_Heater_Current_Data = 0;
        gu16_AD_Result_IceDoor_Heater_Current = (U16)(u32AD_IceDoor_Heater_Current_Sum - gu16Max_IceDoor_Heater_Current_Data_AD - u16Min_IceDoor_Heater_Current_Data_AD) / 20;

        u32AD_IceDoor_Heater_Current_Sum  = 0;
        gu16Max_IceDoor_Heater_Current_Data_AD = 0;
        u16Min_IceDoor_Heater_Current_Data_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void filtering_uv_ice_tray_1_2_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Ice_Tray_1_2_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Ice_Tray_1_2_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Ice_Tray_1_2_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Ice_Tray_1_2_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Ice_Tray_1_2_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Ice_Tray_1_2_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Ice_Tray_1_2_Current_Feed = 0;
        gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed
            = (U16)(u32AD_UV_Ice_Tray_1_2_Current_Feed_Sum - gu16Max_UV_Ice_Tray_1_2_Current_Feed_AD - gu16Min_UV_Ice_Tray_1_2_Current_Feed_AD) / 50;

        u32AD_UV_Ice_Tray_1_2_Current_Feed_Sum  = 0;
        gu16Max_UV_Ice_Tray_1_2_Current_Feed_AD = 0;
        gu16Min_UV_Ice_Tray_1_2_Current_Feed_AD = 1024;
    }
}
#endif


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0

void filtering_cds_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_CDS_AD)    //Max Save
    {
        u16Max_CDS_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_CDS_AD)  //Min   Save
    {
        u16Min_CDS_AD = mu16ad_result;
    }

    u32AD_CDS_Sum += mu16ad_result;

    if(++u8Cnt_CDS >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_CDS = 0;
        gu16ADCds = (U16)((u32AD_CDS_Sum - u16Max_CDS_AD - u16Min_CDS_AD) / 50);

        u32AD_CDS_Sum  = 0;
        u16Max_CDS_AD = 0;
        u16Min_CDS_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_tray_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Tray_Temp_AD)    //Max Save
    {
        u16Max_Tray_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Tray_Temp_AD)  //Min   Save
    {
        u16Min_Tray_Temp_AD = mu16ad_result;
    }

    u32AD_Tray_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Tray_Temp >= 22)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Tray_Temp = 0;
        gu16_AD_Result_Tray_Temp = (U16)((u32AD_Tray_Temp_Sum - u16Max_Tray_Temp_AD - u16Min_Tray_Temp_AD) / 20);
        /*..hui [23-2-8오후 4:07:44] 풀다운을 풀업으로 변경...*/
        /*gu16_AD_Result_Tray_Temp = 1024 - gu16_AD_Result_Tray_Temp;*/

        u32AD_Tray_Temp_Sum  = 0;
        u16Max_Tray_Temp_AD = 0;
        u16Min_Tray_Temp_AD = 1024;
    }

}


#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
U16 ConvAdc2Temp_HotOutWater(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_HOT_OUT_WATER )
    {
        return 1200;  // max temperture..
    }

    if( mu16Adc > MAX_ADC_HOT_OUT_WATER )
    {
        return 0;  // min temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_HOT_OUT_WATER;
    return temp_hot_out_water_table[ mu16Index ];
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void filtering_tds_in_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_TDS_In_Temp_AD)    //Max Save
    {
        gu16Max_TDS_In_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_TDS_In_Temp_AD)  //Min   Save
    {
        gu16Min_TDS_In_Temp_AD = mu16ad_result;
    }

    gu16AD_TDS_In_Temp_Sum += mu16ad_result;

    if(++u8Cnt_TDS_In_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_TDS_In_Temp = 0;
        gu16_AD_Result_TDS_In_Temp
            = (gu16AD_TDS_In_Temp_Sum - gu16Max_TDS_In_Temp_AD - gu16Min_TDS_In_Temp_AD) / 50;


        gu16_AD_Result_TDS_In_Org_Temp = gu16_AD_Result_TDS_In_Temp;
        // 센서의 전압에 따른 AD값이 온도가 커질수록 작아지므로,
        // 프로그램 가독성이 좋도록 값이 증가하도록 연산처리
        gu16_AD_Result_TDS_In_Temp = 1024 - gu16_AD_Result_TDS_In_Temp;  // 10bit AD -> 최대값 1024

        gu16AD_TDS_In_Temp_Sum  = 0;
        gu16Max_TDS_In_Temp_AD = 0;
        gu16Min_TDS_In_Temp_AD = 1024;
    }

}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
U16 ConvAdc2Temp_TDS_In_Water(U16 mu16Adc)
{
    return ConvAdc2Temp_HotInWater( mu16Adc );
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_uv_ice_faucet_two_current_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Ice_Faucet_Two_Current_AD)    //Max Save
    {
        gu16Max_UV_Ice_Faucet_Two_Current_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Ice_Faucet_Two_Current_AD)  //Min   Save
    {
        gu16Min_UV_Ice_Faucet_Two_Current_AD = mu16ad_result;
    }

    u32AD_UV_Ice_Faucet_Two_Current_Sum += mu16ad_result;

    if(++u8Cnt_UV_Ice_Faucet_Two_Current >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Ice_Faucet_Two_Current = 0;

        if(gu16_test_uv_ice_faucet_2_value > 0)
        {
            gu16_AD_Result_UV_Ice_Faucet_Two_Current = gu16_test_uv_ice_faucet_2_value;
        }
        else
        {
            gu16_AD_Result_UV_Ice_Faucet_Two_Current
                = (U16)(u32AD_UV_Ice_Faucet_Two_Current_Sum - gu16Max_UV_Ice_Faucet_Two_Current_AD - gu16Min_UV_Ice_Faucet_Two_Current_AD) / 50;
        }

        u32AD_UV_Ice_Faucet_Two_Current_Sum  = 0;
        gu16Max_UV_Ice_Faucet_Two_Current_AD = 0;
        gu16Min_UV_Ice_Faucet_Two_Current_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
U16 filtering_adc_value( U16 ad_old_value, U16 ad_now_value )
{
    U16 mu16_filted_adc_value;

    /*..hui [17-11-24오후 2:11:22] ACD값 필터링....*/
    mu16_filted_adc_value = (U16)(ad_old_value - (U16)(ad_old_value / 2) + (U16)(ad_now_value / 2));

    return mu16_filted_adc_value;



}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void ADC_Start(void)
{
    ADIF = 0;  /* clear INTAD interrupt flag */
    //ADMK = 0;  /* enable INTAD interrupt */
    ADCS = 1;  /* enable AD conversion */
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void ADC_Stop(void)
{
    ADCS = 0;  /* disable AD conversion */
    //ADMK = 1;  /* disable INTAD interrupt */
    ADIF = 0;  /* clear INTAD interrupt flag */
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void filtering_tds_out_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_TDS_Out_Temp_AD)    //Max Save
    {
        gu16Max_TDS_Out_Temp_AD = (U16)mu16ad_result;
    }

    if(mu16ad_result < gu16Min_TDS_Out_Temp_AD)  //Min   Save
    {
        gu16Min_TDS_Out_Temp_AD = (U16)mu16ad_result;
    }

    gu16AD_TDS_Out_Temp_Sum += (U16)mu16ad_result;

    if(++u8Cnt_TDS_Out_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_TDS_Out_Temp = 0;
        gu16_AD_Result_TDS_Out_Temp = (gu16AD_TDS_Out_Temp_Sum - gu16Max_TDS_Out_Temp_AD - gu16Min_TDS_Out_Temp_AD) / 50;

        gu16_AD_Result_TDS_Out_Org_Temp = gu16_AD_Result_TDS_Out_Temp;
        // 센서의 전압에 따른 AD값이 온도가 커질수록 작아지므로,
        // 프로그램 가독성이 좋도록 값이 증가하도록 연산처리
        gu16_AD_Result_TDS_Out_Temp = 1024 - gu16_AD_Result_TDS_Out_Temp;  // 10bit AD -> 최대값 1024

        gu16AD_TDS_Out_Temp_Sum  = 0;
        gu16Max_TDS_Out_Temp_AD = 0;
        gu16Min_TDS_Out_Temp_AD = 1024;
    }

}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
U16 ConvAdc2Temp_TDS_Out_Water(U16 mu16Adc)
{
    return ConvAdc2Temp_HotInWater( mu16Adc );
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void filtering_tds_out_data_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_TDS_Out_Data_AD)    //Max Save
    {
        gu16Max_TDS_Out_Data_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_TDS_Out_Data_AD)  //Min   Save
    {
        u16Min_TDS_Out_Data_AD = mu16ad_result;
    }

    u16AD_TDS_Out_Data_Sum += mu16ad_result;

    if(++u8Cnt_TDS_Out_Data >= 12)                   // Sum = count +   Max +   Min
    {
        u8Cnt_TDS_Out_Data = 0;
        gu16_AD_Result_TDS_Out_Data = (U16)(u16AD_TDS_Out_Data_Sum - gu16Max_TDS_Out_Data_AD - u16Min_TDS_Out_Data_AD) / 10;
        gu16_AD_Result_TDS_Out_Data = 1024 - gu16_AD_Result_TDS_Out_Data;

        u16AD_TDS_Out_Data_Sum  = 0;
        gu16Max_TDS_Out_Data_AD = 0;
        u16Min_TDS_Out_Data_AD = 1024;
    }

}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_heater_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_Heater_Current_Feed_AD)    //Max Save
    {
        gu16Max_Heater_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_Heater_Current_Feed_AD)  //Min   Save
    {
        gu16Min_Heater_Current_Feed_AD = mu16ad_result;
    }

    u32AD_Heater_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_Heater_Current_Feed >= 12)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Heater_Current_Feed = 0;
        gu16_AD_Result_Heater_Current_Feed
            = (U16)(u32AD_Heater_Current_Feed_Sum - gu16Max_Heater_Current_Feed_AD - gu16Min_Heater_Current_Feed_AD) / 10;

        u32AD_Heater_Current_Feed_Sum  = 0;
        gu16Max_Heater_Current_Feed_AD = 0;
        gu16Min_Heater_Current_Feed_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_hot_heater_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Hot_Heater_Temp_AD)    //Max Save
    {
        u16Max_Hot_Heater_Temp_AD = (U16)mu16ad_result;
    }

    if(mu16ad_result < u16Min_Hot_Heater_Temp_AD)  //Min   Save
    {
        u16Min_Hot_Heater_Temp_AD = (U16)mu16ad_result;
    }

    u32AD_Hot_Heater_Temp_Sum += (U16)mu16ad_result;

    if(++u8Cnt_Hot_Heater_Temp >= 22)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Hot_Heater_Temp = 0;
        gu16_AD_Result_Hot_Heater
            = (U16)(u32AD_Hot_Heater_Temp_Sum - u16Max_Hot_Heater_Temp_AD - u16Min_Hot_Heater_Temp_AD) / 20;

        u32AD_Hot_Heater_Temp_Sum  = 0;
        u16Max_Hot_Heater_Temp_AD = 0;
        u16Min_Hot_Heater_Temp_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_hot_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Hot_Temp_AD)    //Max Save
    {
        u16Max_Hot_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Hot_Temp_AD)  //Min   Save
    {
        u16Min_Hot_Temp_AD = mu16ad_result;
    }

    u32AD_Hot_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Hot_Temp >= 22)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Hot_Temp = 0;
        gu16_AD_Result_Hot_Out = (U16)((u32AD_Hot_Temp_Sum - u16Max_Hot_Temp_AD - u16Min_Hot_Temp_AD) / 20);

        u32AD_Hot_Temp_Sum  = 0;
        u16Max_Hot_Temp_AD = 0;
        u16Min_Hot_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_HotOutWater(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_HOT_OUT_WATER )
    {
        return 1200;  // max temperture..
    }

    if( mu16Adc > MAX_ADC_HOT_OUT_WATER )
    {
        return 0;  // min temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_HOT_OUT_WATER;
    return temp_hot_out_water_table[ mu16Index ];
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_hot_in_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_Hot_In_Temp_AD)    //Max Save
    {
        gu16Max_Hot_In_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_Hot_In_Temp_AD)  //Min   Save
    {
        gu16Min_Hot_In_Temp_AD = mu16ad_result;
    }

    gu32AD_Hot_In_Temp_Sum += mu16ad_result;

    if(++gu8Cnt_Hot_In_Temp >= 22)                   // Sum = count +   Max +   Min
    {
        gu8Cnt_Hot_In_Temp = 0;
        gu16_AD_Result_Hot_In = (U16)((gu32AD_Hot_In_Temp_Sum - gu16Max_Hot_In_Temp_AD - gu16Min_Hot_In_Temp_AD) / 20);

        gu32AD_Hot_In_Temp_Sum  = 0;
        gu16Max_Hot_In_Temp_AD = 0;
        gu16Min_Hot_In_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_HotInWater(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_HOT_IN_WATER )
    {
        return 900;  // max temperture..
    }

    if( mu16Adc > MAX_ADC_HOT_IN_WATER )
    {
        return 0;  // min temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_HOT_IN_WATER;
    return temp_hot_in_water_table[ mu16Index ];
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


