/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 10-11-2023            */
/*          Version: 1.0                */
/*          Module: Seven Segment       */
/****************************************/

#include "../../MCAL/DIO/STD_Types.h"
#include "../../MCAL/DIO/DIO_Header.h"

void SSEG_Void_Init(){
	DIO_Set_Pin_Direction(PORTB,1,Out);///EN2	PB1
	DIO_Set_Pin_Direction(PORTB,2,Out);///EN1	PB2
	DIO_Set_Pin_Direction(PORTB,3,Out);///DIP	PB3
	DIO_Set_Pin_Direction(PORTA,4,Out);///A		PA4
	DIO_Set_Pin_Direction(PORTA,5,Out);///B		PA5
	DIO_Set_Pin_Direction(PORTA,6,Out);///C		PA6
	DIO_Set_Pin_Direction(PORTA,7,Out);///D		PA7
}

void SSEG_Void_Diaplay(uint8 segmentID, uint8 data){
	if(segmentID == 0){
		DIO_Set_Pin_Output(PORTB,1,Low);///EN2 Disable Low
		DIO_Set_Pin_Output(PORTB,2,High);///EN1 Enable High
	}
	else if (segmentID == 1){
		DIO_Set_Pin_Output(PORTB,2,Low);///EN1 Disable Low
		DIO_Set_Pin_Output(PORTB,1,High);///EN2 Enable High
	}
	if(data<10){
		///DCBA 00000000 PORTA 4,5,6,7
		DIO_Set_Pin_Output(PORTA,4,(data>>0)&(0x01));
		DIO_Set_Pin_Output(PORTA,5,(data>>1)&(0x01));
		DIO_Set_Pin_Output(PORTA,6,(data>>2)&(0x01));
		DIO_Set_Pin_Output(PORTA,7,(data>>3)&(0x01));
	}
}
