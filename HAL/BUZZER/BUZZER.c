/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 3-12-2023             */
/*          Version: 1.0                */
/*          Module: BUZZER              */
/****************************************/
#include "../../MCAL/DIO/DIO_Header.h"
#include "../../MCAL/DIO/STD_Types.h"
#include "../../MCAL/DIO/Bit_Math.h"

void BUZZER_Init(){
	DIO_Set_Pin_Direction(PORTA,Pin3,Out);
}
void BUZZER_On(){
	DIO_Set_Pin_Output(PORTA,Pin3,High);
}
void BUZZER_Off(){
	DIO_Set_Pin_Output(PORTA,Pin3,Low);
}