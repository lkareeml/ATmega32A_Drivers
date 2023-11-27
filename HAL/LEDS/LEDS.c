/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 10-11-2023            */
/*          Version: 1.0                */
/*          Module: AMIT Kit 3-LEDs     */
/****************************************/

#include "../../MCAL/DIO/STD_Types.h"
#include "../../MCAL/DIO/DIO_Header.h"

void LED0_Init(){
	DIO_Set_Pin_Direction(PORTC,2,Out);
	}
void LED1_Init(){
	DIO_Set_Pin_Direction(PORTC,7,Out);
	}
void LED2_Init(){
	DIO_Set_Pin_Direction(PORTD,3,Out);
	}

void LED_0_On(){
	DIO_Set_Pin_Output(PORTC,2,High);
}

void LED_1_On(){
	DIO_Set_Pin_Output(PORTC,7,High);
}

void LED_2_On(){
	DIO_Set_Pin_Output(PORTD,3,High);
}

void LED_2_Off(){
	DIO_Set_Pin_Output(PORTD,3,Low);
}

void LED_0_Off(){
	DIO_Set_Pin_Output(PORTC,2,Low);
}

void LED_1_Off(){
	DIO_Set_Pin_Output(PORTC,7,Low);
}