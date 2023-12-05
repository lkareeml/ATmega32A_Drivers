/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 4-12-2023             */
/*          Version: 1.0                */
/*          Module: EEPROM              */
/****************************************/
#define F_CPU 16000000UL
#include "../../MCAL/DIO/STD_Types.h"
#include "../../MCAL/TWI/TWI.h"
#include <util/delay.h>


/*
Login and user system:
Admin Users: Username : Admin, UserID: 1, Password: 4321
Normal Users: Username : ?, UserID: 2, Password: 1234
EEPROM_Add_Data_Byte();
EEPROM_Read_Data_Byte();
EEPROM_Add_New_User();//MAX 3 USERS
EEPROM_Delete_Normal_User();
EEPROM_Increase_User_Count();
EEPROM_Decrease_User_Count();
*/
void  EEPROM_Init(void){
	TWI_Init();
}
void EEPROM_ALL_Wiper(){
	
}
void EEPROM_Address_Checker(){
	
}


uint8 EEPROM_Read_Byte(uint16 Address){
	uint8 Data = 0;
	Address &= 0b0000011111111111 ; // Filter the address for protection
	uint8 SLA_W_address = 0b10100000;
	SLA_W_address |= ((((Address >> 10)&1)<<3) | (((Address >> 9)&1)<<2) | (((Address >> 8)&1)<<1));
	uint8 SLA_R_address = SLA_W_address +1;
	TWI_MSTR_Send_Start();
	if(TWI_Check_Status(MSTR_TR_START)==1){
		TWI_Send_Data(SLA_W_address);
		if(TWI_Check_Status(MSTR_T_SLA_W_ACK)==1){
			TWI_Send_Data((uint8)Address);
			if(TWI_Check_Status(MSTR_T_DATA_ACK)==1){
				TWI_MSTR_Send_Start();
				if(TWI_Check_Status(MSTR_TR_REPEAT_START)==1){
					TWI_Send_Data(SLA_R_address);
					if(TWI_Check_Status(MSTR_R_SLA_R_ACK)==1){
						Data = TWI_Receive_Data(0);
						TWI_Send_Stop();
					}
				}
			}
		}
	}
	return Data;
}

void  EEPROM_Write_Byte(uint16 Address , uint8 Data){
	Address &= 0b0000011111111111 ; // Filter the address for protection
	uint8 SLA_W_address = 0b10100000; // Frame For EXT EEPROM
	SLA_W_address |= ((((Address >> 10)&1)<<3) | (((Address >> 9)&1)<<2) | (((Address >> 8)&1)<<1));
	TWI_MSTR_Send_Start();
	if(TWI_Check_Status(MSTR_TR_START)==1){
		TWI_Send_Data(SLA_W_address);
		if(TWI_Check_Status(MSTR_T_SLA_W_ACK)==1){
			TWI_Send_Data((uint8)Address);
			if(TWI_Check_Status(MSTR_T_DATA_ACK)){
				TWI_Send_Data(Data);
				if(TWI_Check_Status(MSTR_T_DATA_ACK)){
				TWI_Send_Stop();
				}
			}
		}
	}
}

void  EEPROM_Write_String(uint16 Address , sint8 String[16]){
	int i =0;
	while(String[i] != '\n'){
		EEPROM_Write_Byte(Address + i,String[i]);
		_delay_ms(5);
		i++;
	}
}

void  EEPROM_Read_String(uint16 Address , uint8* String, uint8 size){
	int i =0;
	for(i =0;i<size;i++){
		String[i] = EEPROM_Read_Byte(Address+i);
	}
	String[i+1] = '\0';
}


void  EEPROM_Remove_Byte(uint16 Address);
void  EEPROM_Remove_String(uint16 Start_Address, uint16 End_Address);
