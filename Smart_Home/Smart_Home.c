/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 06-12-2023            */
/*          Version: 1.0                */
/*          Module: Smart Home          */
/****************************************/

/*

#include "../MCAL/DIO/STD_Types.h"
#include "../MCAL/UART/UART.h"

#include "../HAL/EEPROM/EEPROM.h"
#include "../HAL/SERVO/SERVO.h"
#include "../HAL/LEDS/LEDS.h"
#include "../HAL/AirConditioner/AC.h"
#include "../HAL/LCD16/LCD_Driver.h"
#include "../HAL/BUZZER/BUZZER.h"

#include "Smart_Home.h"
#include <string.h>
#include <stdio.h>

Login_Mode Current_Login_Mode = Not_Logged;
uint8 Logged_In_ID = 0;// 0 Means Not logged in

void All_Initialization(){
	Servo_Init();
	LED_Init_All();
	AC_Init();
	BUZZER_Init();
	EEPROM_Init();
	LCD_Init();
	UART_Init();
}

void Appliances_Controller(State Current_State,Device Appliance){
	switch(Appliance){
		case Door_Lock_Servo://Servo on PD7
			if(Current_State == Turn_On) Servo_180_Degree_Delay();///EDIT
			else if(Current_State == Turn_Off) Servo_0_Degree_Delay();///EDIT
			break;
		case Dim_Lamp_Device://PA0
			if(Current_State == Turn_On) Lamp_Dimmer_On();
			else if(Current_State == Turn_Off) Lamp_Dimmer_Off();
			break;
		case Air_Conditioner_Device://AC ON RELAY ON PA2
			if(Current_State == Turn_On) AC_On();
			else if(Current_State == Turn_Off) AC_Off();
			break;
		case LED_0_Device://LED0 ON KIT is PC2
			if(Current_State == Turn_On) LED_0_On();
			else if(Current_State == Turn_Off) LED_0_Off();
			break;
		case LED_1_Device://LED1 ON KIT is PC7
			if(Current_State == Turn_On) LED_1_On();
			else if(Current_State == Turn_Off) LED_1_Off();
			break;
		case LED_2_Device://LED2 ON KIT is PD3
			if(Current_State == Turn_On) LED_2_On();
			else if(Current_State == Turn_Off) LED_2_Off();
			break;
		case LED_3_Device://LED3 RESERVE PIN PD4
			if(Current_State == Turn_On) LED_3_On();
			else if(Current_State == Turn_Off) LED_3_Off();
			break;		
		case LED_4_Device://LED4 RESERVE PIN PD5
			if(Current_State == Turn_On) LED_4_On();
			else if(Current_State == Turn_Off) LED_4_Off();
			break;
	}
}


void User_Login_LCD(){
	
}

Profile Admin = {1,"Administrator\0","123456789\0",80} ;

void Initial_Configuration_EEPROM(){
	//IF this is first time flashing this software
	uint8 Temp;
	// First 16 Bytes Indicates if this Micro controller is Configured OR not
	// If 0x0000 Contains : 255 >> Means it has been configured
	// Else it is not configured!
	Temp = EEPROM_Read_Byte(0x0000);
	if(Temp == 255){
		return;//As it is already configured
	}else{
		EEPROM_Save_New_User(16,Admin);
		EEPROM_Write_Byte(0,255);
	}
}

void EEPROM_Save_New_User(uint16 Start_Address,Profile User){
	uint8 UserID[16];
	// sprintf concatenates string and number together
	// Automatically Adds '\0' at end
	sprintf(UserID, "%s%d", "UserID:0",(User.UserID + 48));
	// Write the UserID To EEPROM
	EEPROM_Write_String(Start_Address,UserID);
	// Write the Username To EEPROM
	EEPROM_Write_String(Start_Address + 16,User.Username);
	// Write The Password To EEPROM
	EEPROM_Write_String(Start_Address + 32,User.Password);
}

void EEPROM_Read_Existing_User(uint16 UserID){
	uint8 Username[16];             //16
	uint8 Password[16];             //16
	uint16 ID_Address;	
	// Read the UserID From EEPROM
// 	UserProfile.UserID = EEPROM_Read_Byte(UserProfile.Next_Node - 64);
// 	// Read the Username From EEPROM
// 	EEPROM_Read_String(UserProfile.Next_Node - 48,Username,16);
// 	// Write The Password To EEPROM
// 	EEPROM_Read_String(UserProfile.Next_Node - 32,Password,16);
}

void User_Login_Bluetooth(){
	uint8 count = 0; // MAX COUNT IS 3 THEN BUZZER AND LOCK
	uint8 Temp[16];
	uint8 RecieveUsername[16];
	uint8 RecievePassword[16];
	while(4){
		UART_Send_String_Polling8("Enter Username:\n");
		UART_Recieve_String8(RecieveUsername);
		EEPROM_Read_String(0x0010,Temp,16);
		uint8 Userchecker = memcmp(RecieveUsername,Temp,14);
		
		UART_Send_String_Polling8("Enter Password:\n");
		EEPROM_Read_String(0x0020,Temp,16);
		UART_Recieve_String8(RecievePassword);
		
		uint8 Passwordchecker = memcmp(RecievePassword,Temp,9);
		//Username is correct NEXT
		if((Passwordchecker == 0) && (Userchecker == 0)){
			UART_Send_String_Polling8("Success!\n");
			//Choice :
			// 1) Turn On AC     2) Turn On LEDs...
			// 3) Turn On Dimmer 4) Door(ADMIN)
			// 5)
			//
		}
		else{
			if(count == 3)
			{
				UART_Send_String_Polling8("System LOCKED!");
				BUZZER_On();
				while(1);
			}
			else
			{
				UART_Send_String_Polling8("TryAgain!\n");
				count++;
			}
		}
	}
}


void Parsing_Existing_Users(){}


void Show_Existing_Users(){}
void Edit_Existing_Users(){}

void AC_Automatic_work(){
	//ADC POT  RELAY
	ADC_Init();LCD_Init();
	uint8 digital = 0;
	uint8 old_digital = 0;
	float analog = 0;
	uint8 string[20];
	uint16 temp = 0;
	while (1) {
		digital = ADC_Convert_8bit(ADC_Ch1);
		analog = digital * (5.0 / 256.0); //0--5 >>> 0 -- 50 Temp
		temp = analog * 10;
		dtostrf(temp, 5, 3, string);
		if ((abs(digital - old_digital) > 3)) {
			old_digital = digital;
			LCD_Send_Clear_Screen();
			LCD_Send_String(string);
		}
	}
}


void Show_Options_LCD(){
	//ONLY NOTMAL USER
}

void Show_Options_Bluetooth(uint8 User_Type){
	//ADMIN OR NORMAL USER
}

void All_Choose_Handler(uint8 User_Type){
	//IF ADMIN >>
	
	//If NOT Admin
}






//EEPROM MEMORY MANAGEMENT : 


//Define Data Structures:
typedef struct {
	uint16_t userID;
	char username[20];
	// Add other data fields as needed
} UserData;

//Identify Memory Layout:
// Define memory offsets for different data fields
Determine how the data structures will be stored in the EEPROM. 
Consider the size of each data structure, and if necessary, define a memory layout.
	
#define USER_ID_OFFSET      0
#define USERNAME_OFFSET     2
// Adjust offsets based on data structure

Read and Write Functions:
void readFromEEPROM(uint16_t address, void* data, size_t size) {
	// Implement EEPROM read operation
	// Adjust the code according to your EEPROM communication protocol
}

void writeToEEPROM(uint16_t address, const void* data, size_t size) {
	// Implement EEPROM write operation
	// Adjust the code according to your EEPROM communication protocol
}


//Memory Management Functions:
uint16_t allocateMemory(size_t size) {
	// Find a suitable space in EEPROM to store data
	// Return the starting address of the allocated space
}

void deallocateMemory(uint16_t address, size_t size) {
	// Mark the space in EEPROM as free for reuse
}

//Initialization 

void initializeEEPROM() {
	// Perform EEPROM initialization if needed
}


USAGE:

// Example usage
UserData user;
user.userID = 123;
strcpy(user.username, "JohnDoe");

uint16_t address = allocateMemory(sizeof(UserData));
writeToEEPROM(address + USER_ID_OFFSET, &(user.userID), sizeof(user.userID));
writeToEEPROM(address + USERNAME_OFFSET, user.username, sizeof(user.username));

// To read the data back
readFromEEPROM(address + USER_ID_OFFSET, &(user.userID), sizeof(user.userID));
readFromEEPROM(address + USERNAME_OFFSET, user.username, sizeof(user.username));

*/