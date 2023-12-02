/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 31-11-2023            */
/*          Version: 1.0                */
/*          Module: I2C                 */
/****************************************/
#include "../DIO/STD_Types.h"
#include "../DIO/Bit_Math.h"

#include "I2C_Private.h"
#include "I2C_Config.h"
//MSTR , SLAV

//Interrupt Flag >> Get(TWCR_Reg,7);
// Write Collision Flag Get(TWCR_Reg,3);

//Master Transmit//Master Receive
//Slave Transmit//Slave Receive
void TWI_Init(){
// Setup Bit Rate 0 ~ 255
	TWBR_Reg = 10;
//Setup Prescaler	1(00) -- 4(01) -- 16(10) -- 64(11)
	#if (TWI_Prescaler == Pre_1)
	Clear(TWSR_Reg,0);Clear(TWSR_Reg,1);
	#elif (TWI_Prescaler == Pre_4)
	Clear(TWSR_Reg,0);Set(TWSR_Reg,1);
	#elif (TWI_Prescaler == Pre_16)
	Set(TWSR_Reg,0);Clear(TWSR_Reg,1);
	#elif (TWI_Prescaler == Pre_64)
	Set(TWSR_Reg,0);Set(TWSR_Reg,1);
	#endif
//Enable TWI
	Set(TWCR_Reg,2);
}

uint8 TWI_Check_Status(TWI_STATE State){
	uint8 TWSR_Temp = TWSR_Reg;
	if(State==(TWSR_Temp & 0xF8))
	//Filter TWSR register to get only Status Bits, Then compare to argument
		return 1;	// Same State
	else return 0;	//Different state
}
void TWI_Interrupt_Enable(){Set(TWCR_Reg,0);}
void TWI_Interrupt_Disable(){Clear(TWCR_Reg,0);}
void TWI_Send_Stop()
{
	Set(TWCR_Reg,7);//INTERRUPT FLAG CLEAR
	Set(TWCR_Reg,2);//ENABLE TWI
	Set(TWCR_Reg,4);//SEND STOP
}
void TWI_MSTR_Send_Start()
{
	Set(TWCR_Reg,7);// INTERRUPT FLAG CLEAR
	Set(TWCR_Reg,2);//Enable TWI
	Set(TWCR_Reg,5);//SEND START
	while(Get(TWCR_Reg ,7)  == 0);//Wait till Send Successfully(INT_FLAG DOWN)
}
void TWI_Set_My_Address(uint8 Address)
{
	TWAR_Reg = (TWAR_Reg & 0x01) | (Address<<1);
}
uint8 TWI_Receive_Data(uint8 ACK_State){
	if(ACK_State == 1)
		Set(TWCR_Reg,6);		//SEND ACK IF Input is 1 for ACK
	Set(TWCR_Reg,7);			//Set Interrupt Flag to Clear it
	Set(TWCR_Reg,2);			//Enable TWI
	while(Get(TWCR_Reg,7)== 0);	//Wait for flag to be 0
	return TWDR_Reg;			//Send back DATA Received Value
}
void TWI_Send_Data(uint8 Data){
	TWDR_Reg = Data;
	Set(TWCR_Reg,7);// Clear Interrupt Flag
	Set(TWCR_Reg,2);// Enable TWI
	while(Get(TWCR_Reg,7)== 0);	//Wait for flag to be 0
}