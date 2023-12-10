/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 08-12-2023            */
/*          Version: 1.0                */
/*          Module: RELAY               */
/****************************************/

#include "../../MCAL/DIO/DIO_Header.h"

void Relay_Init(){
	DIO_Set_Pin_Direction(PORTA,Pin2,Out);
}
void Relay_On(){
	DIO_Set_Pin_Output(PORTA,Pin2,High);
}
void Relay_Off(){
	DIO_Set_Pin_Output(PORTA,Pin2,Low);
}