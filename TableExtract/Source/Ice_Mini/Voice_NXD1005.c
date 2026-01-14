/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "Voice_NXD1005.h"


/////void Initial_Voice_Next_Lab(void);
/////void Voice_Stop_Next_Lab(void);
void ProcessVoice_next_lab(void);
//void voice_stop_next_lab(void);
//void send_volume_next_lab(void);
//void send_data_next_lab(void);

//void SEND_SPI_COMMAND_NEXT_LAB(void);
//void Delay_Next_Lab(U16 time);




U8 gu8PlayVoice_Count;

U8 gu8_play_step_next_lab;

U8 u8test_nextlab;

U16 gu16_voice_delay_timer;

const U16 gu16VoiceVolumeRegList[5] =
{
    VOICE_COMMAND_VOLUME_1,
    VOICE_COMMAND_VOLUME_2,
    VOICE_COMMAND_VOLUME_3,
    VOICE_COMMAND_VOLUME_4,
    VOICE_COMMAND_VOLUME_5
};

const U16 gu16BeepVolumeRegList[5] =
{
    BEEP_COMMAND_VOLUME_1,
    BEEP_COMMAND_VOLUME_2,
    BEEP_COMMAND_VOLUME_3,
    BEEP_COMMAND_VOLUME_4,
    BEEP_COMMAND_VOLUME_5
};



/***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void Initial_Voice_Next_Lab(void)
{
    Port_VOICE_RESET = SET;

    Delay_Next_Lab(400);

    //set E2, E3 control Register
    gu16_voice_command = VOICE_COMMAND_CONTROL2; //set Reg. E2 = 0x60
    SEND_SPI_COMMAND_NEXT_LAB();

    Delay_Next_Lab(400);

    gu16_voice_command = VOICE_COMMAND_CONTROL3; //set Reg. E3 = 0x05
    SEND_SPI_COMMAND_NEXT_LAB();

    Delay_Next_Lab(400);

    gu8_play_step_next_lab = NEXT_LAB_FIRST_PLAY;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Voice_Stop_Next_Lab(void)
{
    gu8_play_step_next_lab = NEXT_LAB_FIRST_PLAY;
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ProcessVoice_next_lab(void)
{
    #if 0
    if( F_PlayVoice == SET )
    {
        if( ( gu16_voice_address >= (VOICE_192_MELODY_DISPENSE_CONTINUOUS)
              && gu16_voice_address <= (VOICE_199_MELODY_SET_OFF) )
            || ( gu16_voice_address >= (VOICE_192_MELODY_DISPENSE_CONTINUOUS + US)
              && gu16_voice_address <= (VOICE_199_MELODY_SET_OFF + US) )
            || ( gu16_voice_address >= (VOICE_192_MELODY_DISPENSE_CONTINUOUS + ES)
              && gu16_voice_address <= (VOICE_199_MELODY_SET_OFF + ES) )
            || ( gu16_voice_address >= (VOICE_192_MELODY_DISPENSE_CONTINUOUS + CN)
              && gu16_voice_address <= (VOICE_199_MELODY_SET_OFF + CN) )
            || ( gu16_voice_address >= (VOICE_192_MELODY_DISPENSE_CONTINUOUS + FR)
              && gu16_voice_address <= (VOICE_199_MELODY_SET_OFF + FR) )
            || (u8FactoryTestMode > 0) )
        {
            //voice_stop_next_lab();
            //send_volume_next_lab();
            //send_data_next_lab();
            F_PlayVoice = CLEAR;
            gu16_voice_delay_timer = 0;

            u8test_nextlab++;
        }
        else
        {
            gu16_voice_delay_timer++;

            if( gu16_voice_delay_timer >= 5 )
            {
                gu16_voice_delay_timer = 0;

                //voice_stop_next_lab();
                //send_volume_next_lab();
                //send_data_next_lab();
                F_PlayVoice = CLEAR;

                u8test_nextlab++;
            }
            else{}
        }
    }
    else
    {
        gu16_voice_delay_timer = 0;
    }

    F_Beep_Sound = 0;
    gu16_voice_command = 0;
    #endif
}



#if 0
/****************************************************************************
                Output One Word Command to the Voice IC
 ***************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void voice_stop_next_lab(void)
{
    gu16_voice_command = VOICE_COMMAND_STOP;
    SEND_SPI_COMMAND_NEXT_LAB();
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void send_volume_next_lab(void)
{
    if ( gu16_voice_address == VOICE_192_MELODY_DISPENSE_CONTINUOUS
        || gu16_voice_address == VOICE_193_MELODY_DISPENSE_START
        || gu16_voice_address == VOICE_194_MELODY_DISPENSE_FINISH
        || gu16_voice_address == VOICE_195_MELODY_PLUG_IN
        || gu16_voice_address == VOICE_196_MELODY_SELECT
        || gu16_voice_address == VOICE_197_MELODY_WARNING
        || gu16_voice_address == VOICE_198_MELODY_SET_ON
        || gu16_voice_address == VOICE_199_MELODY_SET_OFF )
    {
        F_Beep_Sound = 1;
    }
    else{}

    /*볼륨 설정*/
    /* 주요 보이스 항목들에 대해서는 볼륨을 최대로 한다. */
    if( IsCriticalVoice( gu16_voice_address ) == TRUE )
    {
        /*..hui [21-10-13오후 7:29:19] 5단계로 변경..*/
        gu16_voice_command = 0xE100 + VOICE_COMMAND_VOLUME_5;
    }
    else
    {
        if( bit_sleep_mode_start == SET )
        {
            /*..hui [24-2-20오후 2:00:21] 취침모드일 경우 볼륨 1로 낮춤..*/
            gu16_voice_command = 0xE100 + gu16BeepVolumeRegList[ SOUND_VOLUME_LEVEL_1 ];
        }
        else
        {
            if( F_Beep_Sound == SET )
            {
                gu16_voice_command = 0xE100 + gu16BeepVolumeRegList[ gu8VoiceVolumeLevel];
            }
            else
            {
                gu16_voice_command = 0xE100 + gu16VoiceVolumeRegList[ gu8VoiceVolumeLevel];
            }
        }
    }

    Delay_Next_Lab(400);   // 약25us
    SEND_SPI_COMMAND_NEXT_LAB();
    Delay_Next_Lab(400);   // 약25us
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void send_data_next_lab(void)
{
      //set $E4 register = 00 if address is < 256
      if (gu16_voice_address < 256)
      {                                       //set phrase group & higher 3 bit address on $E4 register
          gu16_voice_command = VOICE_COMMAND_ADDRESS_256; //phase group=0, high address = 000
          SEND_SPI_COMMAND_NEXT_LAB();
          //set lower 8 bit address on $E0 register
          Delay_Next_Lab(400);   // 약25us
          gu16_voice_command = VOICE_COMMAND_ADDRESS_0 + gu16_voice_address; //set lower 8 bit address on $E0 register
          SEND_SPI_COMMAND_NEXT_LAB();
      }
      //set $E4 register = 0x01 if address is 256~511
      else if ( gu16_voice_address < 512)
      {                                       //set phrase group & higher 3 bit address on $E4 register
          gu16_voice_command = VOICE_COMMAND_ADDRESS_512; //phrase group = 1, high address = 1
          SEND_SPI_COMMAND_NEXT_LAB();
          //set lower 8 bit address on $E0 register
          Delay_Next_Lab(400);   // 약25us
          gu16_voice_command = VOICE_COMMAND_ADDRESS_0 + (gu16_voice_address - 256); //set lower 8 bit address on $E0 register
          SEND_SPI_COMMAND_NEXT_LAB();
      }
      //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      /*..추가 (확장)..*/
      //set $E4 register = 0x02 if address is 512~767
      else if ( gu16_voice_address < 768)
      {                                       //set phrase group & higher 3 bit address on $E4 register
          gu16_voice_command = VOICE_COMMAND_ADDRESS_768; //phrase group = 2, high address = 010
          SEND_SPI_COMMAND_NEXT_LAB();
          //set lower 8 bit address on $E0 register
          Delay_Next_Lab(400);   // 약25us
          gu16_voice_command = VOICE_COMMAND_ADDRESS_0 + (gu16_voice_address - 512); //set lower 8 bit address on $E0 register
          SEND_SPI_COMMAND_NEXT_LAB();
      }
      //set $E4 register = 0x03 if address is 768~1023
      else if ( gu16_voice_address < 1024)
      {                                       //set phrase group & higher 3 bit address on $E4 register
          gu16_voice_command = VOICE_COMMAND_ADDRESS_1024; //phrase group = 3, high address = 011
          SEND_SPI_COMMAND_NEXT_LAB();
          //set lower 8 bit address on $E0 register
          Delay_Next_Lab(400);   // 약25us
          gu16_voice_command = VOICE_COMMAND_ADDRESS_0 + (gu16_voice_address - 768); //set lower 8 bit address on $E0 register
          SEND_SPI_COMMAND_NEXT_LAB();
      }
      //set $E4 register = 0x04 if address is 1024~1279
      else if ( gu16_voice_address < 1280)
      {                                       //set phrase group & higher 3 bit address on $E4 register
          gu16_voice_command = VOICE_COMMAND_ADDRESS_1280; //phrase group = 4, high address = 100
          SEND_SPI_COMMAND_NEXT_LAB();
          //set lower 8 bit address on $E0 register
          Delay_Next_Lab(400);   // 약25us
          gu16_voice_command = VOICE_COMMAND_ADDRESS_0 + (gu16_voice_address - 1024); //set lower 8 bit address on $E0 register
          SEND_SPI_COMMAND_NEXT_LAB();
      }
      //set $E4 register = 0x05 if address is 1280~1535
      else if ( gu16_voice_address < 1536)
      {                                       //set phrase group & higher 3 bit address on $E4 register
          gu16_voice_command = VOICE_COMMAND_ADDRESS_1536; //phrase group = 5, high address = 101
          SEND_SPI_COMMAND_NEXT_LAB();
          //set lower 8 bit address on $E0 register
          Delay_Next_Lab(400);   // 약25us
          gu16_voice_command = VOICE_COMMAND_ADDRESS_0 + (gu16_voice_address - 1280); //set lower 8 bit address on $E0 register
          SEND_SPI_COMMAND_NEXT_LAB();
      }
      //set $E4 register = 0x06 if address is 1536~1791
      else if ( gu16_voice_address < 1792)
      {                                       //set phrase group & higher 3 bit address on $E4 register
          gu16_voice_command = VOICE_COMMAND_ADDRESS_1792; //phrase group = 6, high address = 110
          SEND_SPI_COMMAND_NEXT_LAB();
          //set lower 8 bit address on $E0 register
          Delay_Next_Lab(400);   // 약25us
          gu16_voice_command = VOICE_COMMAND_ADDRESS_0 + (gu16_voice_address - 1536); //set lower 8 bit address on $E0 register
          SEND_SPI_COMMAND_NEXT_LAB();
      }
      //set $E4 register = 0x07 if address is 1792~2047
      else if ( gu16_voice_address < 2048)
      {                                       //set phrase group & higher 3 bit address on $E4 register
          gu16_voice_command = VOICE_COMMAND_ADDRESS_2048; //phrase group = 7, high address = 111
          SEND_SPI_COMMAND_NEXT_LAB();
          //set lower 8 bit address on $E0 register
          Delay_Next_Lab(400);   // 약25us
          gu16_voice_command = VOICE_COMMAND_ADDRESS_0 + (gu16_voice_address - 1792); //set lower 8 bit address on $E0 register
          SEND_SPI_COMMAND_NEXT_LAB();
      }
      else
      {
         /*..출력 안함..*/
      }
}

//----------------------------------------------------------------------------
// send 16 bits SPI command serially from bit15 to bit0.
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void SEND_SPI_COMMAND_NEXT_LAB(void)
{
   int i = 0;

   Port_VOICE_CSB = 0; //start SPI
   //Delay_us(5);        /*CSB Low 후 5ns~20ns delay*/
   //Delay_Next_Lab(8);
   //Delay_Next_Lab(640);                    // 약40us
   //Delay_Next_Lab(1000);                    // 약40us   //?????????????????????????????????????
   Delay_Next_Lab(24000);                    // CSB Low 후 약 1.4ms   //?????????????????????????????????????
   Port_VOICE_clk = 0; //stand-by status,

   /*16bit 처리*/
   while (i < 16)
   {
      Port_VOICE_clk = 0;
      //Delay_us(5); /*mimium 500ns*/
      //Delay_Next_Lab(8);
      Delay_Next_Lab(160);                 // 약10us

      if(gu16_voice_command & MK_COMMAND)
      {
         Port_VOICE_data = 1;
      }
      else
      {
         Port_VOICE_data = 0;
      }

      gu16_voice_command <<= 1; //shift left
      //Delay_us(5);   /*mimium 500ns*/
      //Delay_Next_Lab(8);
      Delay_Next_Lab(160);                 // 약10us

      Port_VOICE_clk = 1;
      i++;
      //Delay_us(10);
      //Delay_Next_Lab(12);

       if(i == 8)
       {
           Delay_Next_Lab(640);               // 약40us (1Byte-1byte 패킷구분)
       }
       else
       {
           Delay_Next_Lab(320);              // 약20us
       }
   }

   Port_VOICE_data = 0;
   //Delay_us(5);
   Delay_Next_Lab(8);                    // 0.5us
   Port_VOICE_CSB = 1; //stand-by status
   //Delay_us(10);       /*KMH next command를 위해 5us delay*/
   //Delay_Next_Lab(12);
   Delay_Next_Lab(320);                  // 20us
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//------------------------------------------------------------------------------
//                      System Delay Time
//------------------------------------------------------------------------------
void Delay_Next_Lab(U16 time)
{
   while(--time) NOP();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#endif

