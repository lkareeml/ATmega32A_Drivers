/****************************************/
/*          Author: Kareem Atef		    */
/*          Date: 10-11-2023		    */
/*          Version: 1.0				*/
/*          Module: LCD Driver          */
/****************************************/

#define F_CPU 16000000UL
#include <util/delay.h>
#include "../../MCAL/DIO/STD_Types.h"
#include "../../MCAL/DIO/DIO_Header.h"
#include "./LCD_Driver.h"

static uint8 Cursor_Position = 0;

#define Get_Bit_Value(Byte_Data,Bit_Order)	((Byte_Data>>Bit_Order)&(0x01)) /// 0,1

void Send_Data_FallingEdge(){
	DIO_Set_Pin_Output(PORTB,3,High);///E HIGH
	_delay_ms(3);
	DIO_Set_Pin_Output(PORTB,3,Low);///E LOW
	_delay_ms(3);
}

void LCD_Init(){
	DIO_Set_Pin_Direction(PORTB,1,Out); ///B1 RS OUT
	DIO_Set_Pin_Direction(PORTB,2,Out); ///B2 RW OUT
	DIO_Set_Pin_Direction(PORTB,3,Out); ///B3 E  OUT
	DIO_Set_Pin_Direction(PORTA,4,Out); ///D4 OUT
	DIO_Set_Pin_Direction(PORTA,5,Out); ///D5 OUT
	DIO_Set_Pin_Direction(PORTA,6,Out); ///D6 OUT
	DIO_Set_Pin_Direction(PORTA,7,Out); ///D7 OUT
	_delay_ms(35);
	LCD_Send_Cmd(0x33);
	_delay_ms(2);
	LCD_Send_Cmd(0x32);
	_delay_ms(2);
	LCD_Send_Cmd(0x28);
	_delay_ms(2);
	LCD_Send_Cmd(0x0F);
	_delay_ms(2);
	LCD_Send_Cmd(0x06);
	_delay_ms(2);
	LCD_Send_Cmd(0x01);
	_delay_ms(2);
	Cursor_Position = 0;
}

void LCD_Send_Cmd(uint8 cmd){
	DIO_Set_Pin_Output(PORTB,1,Low);///RS LOW
	DIO_Set_Pin_Output(PORTB,2,Low);///RW LOW
	
	DIO_Set_Pin_Output(PORTA,4,Get_Bit_Value(cmd,4));///A4 CMD
	DIO_Set_Pin_Output(PORTA,5,Get_Bit_Value(cmd,5));///A5 CMD
	DIO_Set_Pin_Output(PORTA,6,Get_Bit_Value(cmd,6));///A6 CMD
	DIO_Set_Pin_Output(PORTA,7,Get_Bit_Value(cmd,7));///A7 CMD
	Send_Data_FallingEdge();_delay_ms(5);
	DIO_Set_Pin_Output(PORTA,4,Get_Bit_Value(cmd,0));///A0 CMD
	DIO_Set_Pin_Output(PORTA,5,Get_Bit_Value(cmd,1));///A1 CMD
	DIO_Set_Pin_Output(PORTA,6,Get_Bit_Value(cmd,2));///A2 CMD
	DIO_Set_Pin_Output(PORTA,7,Get_Bit_Value(cmd,3));///A3 CMD
	Send_Data_FallingEdge();_delay_ms(5);
}

void LCD_Send_Char(uint8 character){
	if((character >= 32) && (character <= 125))
	{
		DIO_Set_Pin_Output(PORTB,1,High);///RS High For DATA
		DIO_Set_Pin_Output(PORTB,2,Low);///RW LOW
		DIO_Set_Pin_Output(PORTA,4,Get_Bit_Value(character,4));///A4 CMD
		DIO_Set_Pin_Output(PORTA,5,Get_Bit_Value(character,5));///A5 CMD
		DIO_Set_Pin_Output(PORTA,6,Get_Bit_Value(character,6));///A6 CMD
		DIO_Set_Pin_Output(PORTA,7,Get_Bit_Value(character,7));///A7 CMD
		Send_Data_FallingEdge();_delay_ms(5);
		DIO_Set_Pin_Output(PORTA,4,Get_Bit_Value(character,0));///A0 CMD
		DIO_Set_Pin_Output(PORTA,5,Get_Bit_Value(character,1));///A1 CMD
		DIO_Set_Pin_Output(PORTA,6,Get_Bit_Value(character,2));///A2 CMD
		DIO_Set_Pin_Output(PORTA,7,Get_Bit_Value(character,3));///A3 CMD
		Send_Data_FallingEdge();_delay_ms(5);
		LCD_Position_Handler(RIGHT);
	}
}

void LCD_Set_Cursor_Position(uint8 row, uint8 col){
	uint8 address = 0;
	address = ((row*(0x40))+(col));
	///Address + 1 bit for enable location move
	LCD_Send_Cmd(address|0x80);
	if(row == 0 && col <= 15){
		Cursor_Position = col;
		}else if(row == 1 && col <= 15){
		Cursor_Position = col + 16;
	}
}

void LCD_Send_Clear_Screen(){
	LCD_Send_Cmd(0x01);
	_delay_ms(2);
	Cursor_Position = 0;
}

void LCD_Cursor_Shift(Dir Direction){
	if (Direction == RIGHT && Cursor_Position < 31)
	{
		LCD_Send_Cmd(0x14);
		LCD_Position_Handler(Direction);
	}
	else if (Direction == LEFT && Cursor_Position >=0)
	{
		LCD_Send_Cmd(0x10);
		LCD_Position_Handler(Direction);
	}
}

void LCD_Delete_Last_Written(){
	if(Cursor_Position >=0){
		LCD_Cursor_Shift(LEFT);_delay_ms(2);
		LCD_Send_Char(' ');_delay_ms(2);
		LCD_Cursor_Shift(LEFT);_delay_ms(2);
	}
}

void LCD_Position_Handler(Dir Direction){
	if(Direction == RIGHT){// INCREASE
		if(Cursor_Position <= 14){
			Cursor_Position++;
			}else if(Cursor_Position == 15){
			Cursor_Position++;
			LCD_Set_Cursor_Position(1,0);
			}else if(Cursor_Position > 15 && Cursor_Position <= 30){
			Cursor_Position++;
			}else if(Cursor_Position == 31){
			Cursor_Position = 0;
			LCD_Set_Cursor_Position(0,0);
		}
	}
	if(Direction == LEFT){// DECREASE
		if(Cursor_Position > 0 && Cursor_Position <=15 ){
			Cursor_Position--;
			}else if(Cursor_Position == 16){
			LCD_Set_Cursor_Position(0,15);
			}else if(Cursor_Position > 16 && Cursor_Position <= 31){
			Cursor_Position--;
			}else if(Cursor_Position == 0){
			LCD_Set_Cursor_Position(1,15);
		}
	}
	
}

void LCD_Send_String(sint8 * str){
	uint8 index =0;
	while(str[index] != '\0'){
		LCD_Send_Char(str[index]);
		index++;
		_delay_ms(10);
	}
	_delay_ms(5);
}