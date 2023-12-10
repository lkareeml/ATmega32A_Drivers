/****************************************/
/*          Author: Kareem Atef		    */
/*          Date: 09-12-2023		    */
/*          Version: 1.0				*/
/*          Content: Proof Of Concept   */
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

#include "../../HAL/Seven_Segment/Seven_Segment.h"
#include "../../HAL/LCD16/LCD_Driver.h"
#include "../../HAL/KEYPAD/KEYPAD.h"
#include "../../HAL/Buttons/Buttons.h"
#include "../../HAL/LEDS/LEDS.h"
#include "../../HAL/SERVO/SERVO.h"
#include "../../HAL/BUZZER/BUZZER.h"
#include "../../HAL/EEPROM/EEPROM.h"
#include "../../MCAL/TWI/TWI.h"

#include "../Helper.h"

#include "Proof.h"

/************** IN PROGRESS USING SIMULATION 2 MCROCONTROLLR ***************/
void  App_025_SPI_RFID_MASTER();
void  App_025_SPI_RFID_SLAVE();

void  App_024_LED_SPI_Blinking_Slave();
void  App_024_LED_SPI_Blinking_Master();

/***************************************************************************/
uint8 App_023_Receive_With_DIO_UartFrame_RECEIVER(uint8 Parity_Type){
	// RECEIVE UNKNOWN CHARACTER FOR EXAMPLE RECEIVE 'A'
	uint16 received_Data = 0; // 1 Start_Bit + 8 bit data + 1 Parity_bit + 2 stop_bits
	uint8 parity_error_flag = 0;
	uint8 character = 0;
	uint8 parity_bit = 0;
	DIO_Set_Pin_Direction(PORTA,Pin0,In);
	while(Get(PORTA,Pin0));//Wait for Start Bit(LOW)
	for(int i =0;i < 12*sizeof(uint8);i++)
	{
		received_Data = received_Data | ( (Get(PORTA,Pin0)<<i) );
		_delay_ms(1);
	}
	//Check Stop Bits
	if((received_Data & (1<<0)) == 0 && (received_Data & (1<<1)) == 0){// 0b 0000 0 00000000 0 00
		//Check Parity Bit
		//Parity_Type = 1; Argument
		parity_bit = (uint8)(received_Data|0b0000000000000100) >> 2;
		character = (uint8)(received_Data|0b0000011111111000) >> 3;
		parity_error_flag = App_023_Private_PARITY_Checker(character,parity_bit, Parity_Type);
	}
	if(parity_error_flag == 0){
		return character;
	}
	else if(parity_error_flag == 1){
		return 4;
	}
	return 4;
}
/***************************************************************************/
uint8 App_023_Private_PARITY_Checker(uint8 character,uint8 parity_bit, uint8 Parity_Type){
	uint8 Counter = 0;
	//Parity Checker :
	for(int i =0;i < 8*sizeof(uint8);i++){
		if( (character >> i) & ( 0b00000001 ) )
		Counter++;
	}
	// Parity Agreed on Even
	if(Parity_Type == 0){
		if( ( (Counter+parity_bit)/2 ) == 0){    return 0;} // Even Overall Return 0 To indicate Good Parity
		else if( ( (Counter+parity_bit)/2 ) == 1){return 1;}// ODD Overall // Return 1 To indicate Bad Parity
	}
	// Parity Agreed on ODD
	else if(Parity_Type == 1)
	{
		if( ( (Counter+parity_bit)/2 ) == 1){return 0;}  // ODD Overall Return 0 To indicate Good Parity
		else if( ( (Counter+parity_bit)/2 ) == 0){ return 1;} //ODD Overall Return 0 To indicate Bad Parity
	}
	return 1;
}
/***************************************************************************/
uint8 App_023_Private_PARITY_Generator(uint8 character, uint8 Parity_Type){
	uint8 parity = 0;
	//Parity Generator :
	for(int i =0;i < 8*sizeof(uint8);i++){
		if( (character >> i) & ( 0b00000001 ) )
		parity++;
	}
	if((parity/2) == 0)
	{
		if(Parity_Type == 0)//EVEN REQUIRED
		parity = 0;
		else if(Parity_Type == 1)//ODD REQUIRED
		parity = 1;
	}
	else if((parity/2) == 1) // ODD
	{
		if(Parity_Type == 0)//EVEN REQUIRED
		parity = 1;
		else if(Parity_Type == 1)//ODD REQUIRED
		parity = 0;
	}
	return parity;
}
/***************************************************************************/
void  App_023_Send_With_DIO_UartFrame_SENDER(uint8 character){
	// FOR EXAMPLE SEND 'A'
	//Make Parity
	uint8 parity = 0;
	parity = App_023_Private_PARITY_Generator(character,0);//0 for even, 1 for odd
	
	DIO_Set_Pin_Direction(PORTA,Pin0,Out);// Set Pin Direction
	DIO_Set_Pin_Output(PORTA,Pin0,High);//Start idle Waiting
	_delay_ms(1000);
	// Send Start Bit
	DIO_Set_Pin_Output(PORTA,Pin0,Low);    //Send Start Bit SIGNAL NOW!!
	_delay_ms(1);
	// Send Data
	for(int i =0;i < 8*sizeof(uint8);i++)
	{
		if(character & (1<<i))
		{
			DIO_Set_Pin_Output(PORTA,Pin0,(character & (1<<i)));
			_delay_ms(1);
			}else{
			DIO_Set_Pin_Output(PORTA,Pin0,(character & (1<<i)));
			_delay_ms(1);
		}
	}
	// Send Parity Bit
	if(parity == 1){
		DIO_Set_Pin_Output(PORTA,Pin0,High); // Send Parity Bit
		_delay_ms(1);
	}
	else if(parity == 0){
		DIO_Set_Pin_Output(PORTA,Pin0,Low); // Send Parity Bit
		_delay_ms(1);
	}
	// Send Stop Bit
	DIO_Set_Pin_Output(PORTA,Pin0,Low); // Send Parity Bit
	_delay_ms(1);
	DIO_Set_Pin_Output(PORTA,Pin0,Low); // Send Parity Bit
	_delay_ms(1);
}

/***************************************************************************/
uint8 App_022_RECEIVE_WITH_DIO_MICRO_RECEIVER()
{
	// RECEIVE UNKNOWN CHARACTER FOR EXAMPLE RECEIVE 'A'
	uint8 received_Char = 0;
	DIO_Set_Pin_Direction(PORTA,Pin0,In);
	//WAIT TILL LOW
	while(Get(PORTA,Pin0));
	//SIGNAL SENDING  STARTED!!!
	for(int i =0;i < 8*sizeof(uint8);i++)
	{
		received_Char = received_Char | ( (Get(PORTA,Pin0)<<i) );
		_delay_ms(1);
	}
	return received_Char;
}
void  App_022_SEND_WITH_DIO_MICRO_SENDER(uint8 character)
{
	// FOR EXAMPLE SEND 'A'
	DIO_Set_Pin_Direction(PORTA,Pin0,Out);// Set Pin Direction
	DIO_Set_Pin_Output(PORTA,Pin0,High);//Start Waiting
	_delay_ms(1000);
	DIO_Set_Pin_Output(PORTA,Pin0,Low);    //START SENDING SIGNAL NOW!!
	// For Example : 01000001
	for(int i =0;i < 8*sizeof(uint8);i++)
	{
		if(character & (1<<i))
		{
			DIO_Set_Pin_Output(PORTA,Pin0,(character & (1<<i)));
			_delay_ms(1);
			}else{
			DIO_Set_Pin_Output(PORTA,Pin0,(character & (1<<i)));
			_delay_ms(1);
		}
	}
}