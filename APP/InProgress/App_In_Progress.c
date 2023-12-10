/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 10-11-2023            */
/*          Version: 1.0                */
/*          Module: App                 */
/****************************************/

#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>

#include "../../MCAL/DIO/STD_Types.h"
#include "../../MCAL/DIO/Bit_Math.h"
#include "../../MCAL/DIO/DIO_Header.h"
#include "../../MCAL/ADC/ADC_INIT.h"
#include "../../MCAL/ADC/ADC_CONFIG.h"
#include "../../MCAL/INTERRUPT/Interrupt_H.h"
#include "../../MCAL/TIMER/Timer_Init.h"
#include "../../MCAL/UART/UART.h"
#include "../../MCAL/TWI/TWI.h"

#include "../../HAL/Seven_Segment/Seven_Segment.h"
#include "../../HAL/LCD16/LCD_Driver.h"
#include "../../HAL/KEYPAD/KEYPAD.h"
#include "../../HAL/Buttons/Buttons.h"
#include "../../HAL/LEDS/LEDS.h"
#include "../../HAL/SERVO/SERVO.h"
#include "../../HAL/BUZZER/BUZZER.h"
#include "../../HAL/EEPROM/EEPROM.h"


#include "App_In_Progress.h"
#include "../Helper.h"

#include <string.h>

extern uint8 button0_State;
extern uint8 button1_State;
extern uint8 button2_State;












void App_35_LVL_3_Config_From_Bluetooth_Save_EEPROM_Read_EEPROM_Config_UART_START(){
//UART ASK PHONE FOR CONFIG, SAVE IT TO VARIABLE, SAVE IT TO EEPROM, DISABLE UART
//READ EEPROM, INIT UART CONFIG FROM EEPROM, Enable UART
//EEPROM WRITE HERE, READ HERE, UART INIT HERE
	UART_Init();
	EEPROM_Init();
	uint8 CommSize,SyncMode,SyncPolarity,ParityMode,Stopbit,X2Speed;
	sint8 ReadArray[1];
	uint32 UART_BAUD =0;
	
	UART_Send_String_Polling_8("Enter CommSize(5,6,7,8,9):\n");
	UART_Recieve_String_8(ReadArray);
	CommSize = ReadArray[0] - 48;
	UART_Send_String_Polling_8("Enter SyncMode(1-ASYNC,2-SYNC):\n");
	UART_Recieve_String_8(ReadArray);
	SyncMode = ReadArray[0] - 48;
	UART_Send_String_Polling_8("Enter SyncPolarity(0-,1):\n");
	UART_Recieve_String_8(ReadArray);
	SyncPolarity = ReadArray[0] - 48;
	UART_Send_String_Polling_8("Enter Parity(0-off,1-Odd,2-Even):\n");
	UART_Recieve_String_8(ReadArray);
	ParityMode = ReadArray[0] - 48;	
	UART_Send_String_Polling_8("Enter Stopbit(1-Bit,2-Bit):\n");
	UART_Recieve_String_8(ReadArray);
	Stopbit = ReadArray[0] - 48;
	UART_Send_String_Polling_8("Enter X2Speed(0-off,1-on):\n");
	UART_Recieve_String_8(ReadArray);
	X2Speed = ReadArray[0] - 48;
	
	//THIS WHERE ERROR
	UART_Send_String_Polling_8("Enter UART_BAUD(Rate):\n");
	sint8 BaudRateArray[20];
	UART_Recieve_String_8(BaudRateArray);
	uint8 i = 0;
	
	while(BaudRateArray[i] != '\0'){
		//if (BaudRateArray[i] >= '0' && BaudRateArray[i] <= '9')
			UART_BAUD = (UART_BAUD * 10) + ((uint8)BaudRateArray[i] - 48);
		//else if(BaudRateArray[i] == 13) {BUZZER_Init(); BUZZER_On();}
		//Carriage return why?
		//The UART Phone sends "carriage return" then the /n from phone
		i++;
	}
	//UART_Send_String_Polling_8(BaudRateArray);


// 	uint8 
CommSize=8,SyncMode=1,SyncPolarity=0,ParityMode=0,Stopbit=1,X2Speed=0;
// 	uint32 
//	UART_BAUD = 9600;

//ALL BELOW WORK!!
//	WRITE	
	EEPROM_Write_Byte(0x0010,CommSize);			//1 Byte
	EEPROM_Write_Byte(0x0011,SyncMode);			//1 Byte
	EEPROM_Write_Byte(0x0012,SyncPolarity);		//1 Byte
	EEPROM_Write_Byte(0x0013,ParityMode);		//1 Byte
	EEPROM_Write_Byte(0x0014,Stopbit);			//1 Byte
	EEPROM_Write_Byte(0x0015,X2Speed);			//1 Byte
	EEPROM_Write_Number_32(0x0016,UART_BAUD);	//4 Bytes
//	READ
	CommSize	= EEPROM_Read_Byte(0x0010);
	SyncMode	= EEPROM_Read_Byte(0x0011);
	SyncPolarity= EEPROM_Read_Byte(0x0012);
	ParityMode	= EEPROM_Read_Byte(0x0013);
	Stopbit		= EEPROM_Read_Byte(0x0014);
	X2Speed		= EEPROM_Read_Byte(0x0015);
	UART_BAUD	= EEPROM_Read_Number_32(0x0016);
	
	UART_Send_String_Polling_8("Progress: Stop the UART...\n");
	UART_Send_String_Polling_8("Progress: Edit UART Config...\n");
	UART_Send_String_Polling_8("Progress: Turn On UART...\n");
	UART_Disable_TX();
	UART_Disable_RX();
	UART_Dynamic_INIT(CommSize,SyncMode,SyncPolarity,ParityMode,Stopbit,X2Speed,UART_BAUD);
	UART_Enable_TX();
	UART_Enable_RX();

	// Bluetooth Communication HERE!!
	UART_Send_String_Polling_8("Progress: Test UART Works!\n");
	
}

















// WELL DONE!
void App_36_LVL_2_UARTCONF_WRITE_EEPROM(){
	EEPROM_Init();
	uint8 CommSize = 8, SyncMode = 1, SyncPolarity = 0, ParityMode = 0, Stopbit = 2;
	uint8 X2SpeedMode = 0;
	uint32 BudRateX = 9600;		// 2400UL ~~ 250000UL
	EEPROM_Write_Byte(0x00E0,CommSize);//1Byte
	EEPROM_Write_Byte(0x00E1,SyncMode);//1Byte
	EEPROM_Write_Byte(0x00E2,SyncPolarity);//1Byte
	EEPROM_Write_Byte(0x00E3,ParityMode);//1Byte
	EEPROM_Write_Byte(0x00E4,Stopbit);//1Byte
	EEPROM_Write_Byte(0x00E5,X2SpeedMode);//1Byte
	EEPROM_Write_Number_32(0x00E6,BudRateX);//4Byte
}

void App_36_LVL_2_UARTCONF_READ_EEPROM(){
	EEPROM_Init();
	uint8 CommSize     = EEPROM_Read_Byte(0x00E0);
	uint8 SyncMode	   = EEPROM_Read_Byte(0x00E1);
	uint8 SyncPolarity = EEPROM_Read_Byte(0x00E2);
	uint8 ParityMode   = EEPROM_Read_Byte(0x00E3);
	uint8 Stopbit      = EEPROM_Read_Byte(0x00E4);
	uint8 X2SpeedMode  = EEPROM_Read_Byte(0x00E5);
	uint32 BudRateX    = EEPROM_Read_Number_32(0x00E6);
	// 	UART_Disable_TX();
	// 	UART_Disable_RX();
	UART_Dynamic_INIT(CommSize,SyncMode,SyncPolarity,ParityMode,Stopbit,X2SpeedMode,BudRateX);
	UART_Enable_TX();
	UART_Enable_RX();
	//Bluetooth Communication HERE!!
	UART_Send_String_Polling_8("TEST IS WELL DONE!!\n");
}

// WELL DONE!
void App_34_LVL_1_write_EEPROM_then_read_eeprom_then_config_uart(){
	//EEPROM WRITE HERE, READ HERE, UART INIT HERE
	EEPROM_Init();
	uint8 CommSize = 8;			// Comm_Size_5.6.7.8.9
	uint8 SyncMode	= 1;		// Async_Mode  (1) -- Sync_Mode  (0)
	uint8 SyncPolarity = 0;		//TX_Rising_XCK(0) TX_Falling_XCK(1)
	uint8 ParityMode = 0;		// Parity_Even (2) -- Parity_Odd (1) -- Parity_Disable (0)
	uint8 Stopbit = 2;			// Stop2_Bit   (2) -- Stop1_Bit  (1)
	uint8 X2SpeedMode = 0;		// Disable 0 , Enable 1
	uint32 UART_BAUD = 9600;	// 2400UL ~~ 250000UL
	EEPROM_Write_String(0x0000,"X"); //RANDOM DATA TO READ
	EEPROM_Write_Byte(0x0011,SyncMode);//1Byte
	EEPROM_Write_Byte(0x0012,SyncPolarity);//1Byte
	EEPROM_Write_Byte(0x0013,ParityMode);//1Byte
	EEPROM_Write_Byte(0x0014,Stopbit);//1Byte
	EEPROM_Write_Byte(0x0015,X2SpeedMode);//1Byte
	EEPROM_Write_Number_32(0x0016,UART_BAUD);//4Bytes
	uint8 test = EEPROM_Read_Byte(0x0000);//RANDOM DATA TO READ
 	SyncMode	= EEPROM_Read_Byte(0x0011);
 	SyncPolarity= EEPROM_Read_Byte(0x0012);
 	ParityMode	= EEPROM_Read_Byte(0x0013);
	Stopbit		= EEPROM_Read_Byte(0x0014);
	X2SpeedMode	= EEPROM_Read_Byte(0x0015);
	UART_BAUD = EEPROM_Read_Number_32(0x0016);//4Bytes
	UART_Dynamic_INIT(CommSize,SyncMode,SyncPolarity,ParityMode,Stopbit,X2SpeedMode,UART_BAUD);
	UART_Enable_TX();
	UART_Enable_RX();
	//Bluetooth Communication HERE!!
	UART_Send_String_Polling_8("TEST IS WELL DONE!!\n");
	UART_Send_Byte_Polling_8(test);
}


void App_031_UART_Create_New_User_Password(){
	UART_Init();
	EEPROM_Init();
	sint8 RecieveUsername[16];
	sint8 RecievePassword[16];
	uint16 StartAddress = 0x00E0;
	sint8 ReadArray[16];
	UART_Send_String_Polling_8("Create New User \n");
	UART_Send_String_Polling_8("Enter UserName: (Max 16 char) \n");
	UART_Recieve_String_8(RecieveUsername);
	UART_Send_String_Polling_8("Enter Password: (Max 16 char)\n");
	UART_Recieve_String_8(RecievePassword);
	EEPROM_Write_String(StartAddress+16,RecieveUsername);//0x0010
	EEPROM_Write_String(StartAddress+32,RecievePassword);//0x0020
	UART_Send_String_Polling_8("Success!\n");
	
	UART_Send_String_Polling_8("\n UserName is : ");
	EEPROM_Read_String((StartAddress+16),ReadArray);
	UART_Send_String_Polling_8(ReadArray);
	UART_Send_String_Polling_8("\n Password is : ");
	EEPROM_Read_String((StartAddress+32),ReadArray);
	UART_Send_String_Polling_8(ReadArray);
	UART_Send_String_Polling_8("\n");

}

/***********************************************************/

void App_030_Save_Data_EEPROM_Read_LCD(){
	sint8 arr[20];// = '\0';
	TWI_Init();
	EEPROM_Init();
	LCD_Init();
	uint16 lastAddress = EEPROM_Write_String(0x0000,"Kxreem.Atef");
	//EEPROM_Write_Byte(0x000B,'0');// PROBLEM write to null, erased the stop null for previous data
	EEPROM_Write_Byte(lastAddress,'x');
	EEPROM_Read_String(0x0000,arr);
	LCD_Send_String(arr);
	while(1);
}

void App_029_SEND_USERNAME_PASSWORD_UART_BLUETOOTH_LOGIN_SYS(){//Sys lock after 2 trials
	BUZZER_Init();
	UART_Init();
	uint8 count = 0; // MAX COUNT IS 3 THEN BUZZER AND LOCK 
	uint8 user[6] = "ADMIN";
	uint8 password[5] = "1234";
	sint8 RecieveUsername[11];
	sint8 RecievePassword[11];
	while(1){
		UART_Send_String_Polling_8("Enter Username:\n");
		UART_Recieve_String_8(RecieveUsername);
		uint8 Userchecker = memcmp(RecieveUsername,user,5);
		UART_Send_String_Polling_8("Enter Password:");
		UART_Send_Byte_Polling_8('\n');
		UART_Recieve_String_8(RecievePassword);
		uint8 Passwordchecker = memcmp(RecievePassword,password,4);
		//Username is correct NEXT
		if((Passwordchecker == 0) && (Userchecker == 0)){
			UART_Send_String_Polling_8("Success!");
			//Choice :
			// 1) Turn On AC     2) Turn On LEDs...
			// 3) Turn On Dimmer 4) Door(ADMIN)
			// 5)
			while(1);
		}
		else{
			if(count == 3)
			{
				UART_Send_String_Polling_8("System LOCKED!");
				BUZZER_On();
				while(1);
			}
			else
			{
				UART_Send_String_Polling_8("TryAgain!");
				count++;
			}
		}
	}
}

void App_028_Bluetooth_UART_STRING_LED_ON_OFF(){
	UART_Init();
	sint8 Recieve[11];
	LED0_Init();LED1_Init();LED2_Init();
	while(1){
		UART_Recieve_String_8(Recieve);
		if (Recieve[9] == '\n')
		{
			if (memcmp(Recieve,"LED 0 ON",8) == 0)
				{LED_0_On();}
			else if (memcmp(Recieve,"LED 1 ON",8) == 0)
				{LED_1_On();}
			else if (memcmp(Recieve,"LED 2 ON",8) == 0)
				{LED_2_On();}
		}
		if(Recieve[10] == '\n'){
			if (memcmp(Recieve,"LED 0 OFF",9) == 0)
			{LED_0_Off();}
			else if (memcmp(Recieve,"LED 1 OFF",9) == 0)
			{LED_1_Off();}
			else if (memcmp(Recieve,"LED 2 OFF",9) == 0)
			{LED_2_Off();}
		}
	}
}

void App_027_Servo_Timer2_Interrupt(){
	// Timer2 Config : Timer_M_CTC Timer_COM_Pin_TOGGLE  Timer_Pre_1024
	//FREQ_EXIT = 16000000 / (PRESCALER * OCR0) AS FReq = 50 >>> OCR0 =~ 311 BUT max255 ?
	Servo_Init();
	Timer2_Init();
	Timer2_Set_OCR2_Reg(16);
	Timer2_Enable_CTC_Interrupt();
	GIE_Enable();
	while(1);
}

void App_027_ISR(){
	Timer2_Set_OCR2_Reg(60);
	static uint32 Loop_counter = 0;
	static uint8 flag = 0;
	uint8 placement_Var = 5;//1~5
	Loop_counter++;
	if((Loop_counter == (40-placement_Var)) && (flag == 0) ){
		DIO_Set_Pin_Output(PORTD,Pin7,High);
		flag = 1;Loop_counter = 0;
	}
	else if ((Loop_counter == placement_Var) && (flag == 1)){
		DIO_Set_Pin_Output(PORTD,Pin7,Low);
		flag =0;Loop_counter = 0;
	}
}

void App_026_Servo_Delay(){
    Servo_Init();
	Servo_0_Degree_Delay();
    while (1)
    {
		//for(int i =0;i<50;i++)Servo_0_Degree_Delay();
		for(int i =0;i<50;i++)Servo_90_Degree_Delay();
		//for(int i =0;i<50;i++)Servo_180_Degree_Delay();
    }
}
/***********************************************************/
void App_021_MOTOR_FASTPWM(){
    ///FAST PWM LED POWER UP AND DOWN
    // SET FASTPWM FOR TIMER 1
    //DIO_Set_Pin_Direction(PORTB,Pin3,Out);
    uint8 digital = 126;
    //uint8 old_digital = 126;
    Timer0_Set_OCR0_Reg(digital);
    Timer0_Init();
    Timer0_Enable_CTC_Interrupt();
    GIE_Enable();
    while (1)
    {
        //digital = ADC_Convert_8bit(ADC_Ch1);
        /*if((abs(digital-old_digital) > 10))
        {
            old_digital = digital;
            Timer0_Set_OCR0_Reg(digital);
        }*/
    }
}

/***********************************************************/
