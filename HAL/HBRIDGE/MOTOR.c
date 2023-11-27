/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 23-11-2023            */
/*          Version: 1.0                */
/*          Module: MOTOR               */
/****************************************/

#include "../../MCAL/DIO/STD_Types.h"
#include "../../MCAL/DIO/DIO_Reg.h"
#include "../../MCAL/DIO/DIO_Header.h"

#include "MOTOR.h"
/*
void Motor_Direction_Speed(Motor_Num motorNum,Motor_Dir motorD, uint8 Mototr_Speed){
	if(motorNum == Motor1)
	{	//PC3 -- A1  //  PC4 -- A2 // PD4 H-En1 .. A
		DIO_Set_Pin_Direction(PORTD,Pin4,Out);
		DIO_Set_Pin_Direction(PORTC,Pin3,Out);
		DIO_Set_Pin_Direction(PORTC,Pin4,Out);
		Timer1_Set_OCR1A_Reg( (Mototr_Speed & 0b0000000011111111) );
		if(motorD == ClockWise)
		{
			DIO_Set_Pin_Output(PORTC,Pin3,Low);
			DIO_Set_Pin_Output(PORTC,Pin4,High);
		}
		else if(motorD == Counter_ClockWise)
		{
			DIO_Set_Pin_Output(PORTC,Pin3,High);
			DIO_Set_Pin_Output(PORTC,Pin4,Low);
		}
	}
	else if(motorNum == Motor2)
	{	//PC5 -- A3  //  PC6 -- A4 // PD5 H-En2 .. B
		DIO_Set_Pin_Direction(PORTD,Pin5,Out);
		DIO_Set_Pin_Direction(PORTC,Pin5,Out);
		DIO_Set_Pin_Direction(PORTC,Pin6,Out);
		Timer1_Set_OCR1B_Reg( (Mototr_Speed & 0b0000000011111111) );
		if(motorD == ClockWise)
		{
			DIO_Set_Pin_Output(PORTC,Pin5,Low);
			DIO_Set_Pin_Output(PORTC,Pin6,High);
		}
		else if(motorD == Counter_ClockWise)
		{
			DIO_Set_Pin_Output(PORTC,Pin5,High);
			DIO_Set_Pin_Output(PORTC,Pin6,Low);
		}
	}
}



*/