/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 10-11-2023            */
/*          Version: 1.0                */
/*          Module: AMIT Kit Buttons    */
/****************************************/

#define F_CPU 16000000UL
#include <util/delay.h>
#include "../../MCAL/DIO/STD_Types.h"
#include "../../MCAL/DIO/DIO_Header.h"


void Button_Init(){
	///PD2 Button2 PD6 Button1 PB0 Button0
	/// Clear(DDRD,2);Clear(DDRD,6);Set(DDRB,0);
	DIO_Set_Pin_Direction(PORTD,2,In);
	DIO_Set_Pin_Direction(PORTD,6,In);
	DIO_Set_Pin_Direction(PORTB,0,In);
}
void Check_Button0_Clicked(uint8 * button0_State){
	switch(*button0_State){
		case 0:
			if(DIO_Get_Pin_Value(PORTD,2)){
				_delay_ms(20);
				if(DIO_Get_Pin_Value(PORTD,2)) *button0_State = 1;
			}
			break;
		case 1:	
			if(!(DIO_Get_Pin_Value(PORTD,2)))
			*button0_State = 10 ;
			break;
		default:break;
	}
}

void Check_Button1_Clicked(uint8 * button1_State){
	switch(*button1_State){
		case 0:
		if(DIO_Get_Pin_Value(PORTD,6)){
			_delay_ms(20);
			if(DIO_Get_Pin_Value(PORTD,6)) *button1_State = 1;
		}
		break;
		case 1:
		if(!(DIO_Get_Pin_Value(PORTD,6)))
		*button1_State = 10 ;
		break;
		default:break;
	}
}

void Check_Button2_Clicked(uint8 * button2_State){
	switch(*button2_State){
		case 0:
		if(DIO_Get_Pin_Value(PORTB,0)){
			_delay_ms(20);
			if(DIO_Get_Pin_Value(PORTB,0)) *button2_State = 1;
		}
		break;
		case 1:
		if(!(DIO_Get_Pin_Value(PORTB,0)))
		*button2_State = 10 ;
		break;
		default:break;
	}
}