/****************************************/
/*          Author: Kareem Atef		    */
/*          Date: 10-11-2023		    */
/*          Version: 1.0				*/
/*          Module : DIO Header         */
/****************************************/

#ifndef DIO_HEADER_H_
#define DIO_HEADER_H_

typedef enum{
	PORTA,
	PORTB,
	PORTC,
	PORTD
}PORT;

typedef enum{
	Pin0, Pin1, Pin2, Pin3, Pin4, Pin5, Pin6, Pin7
}PIN;

typedef enum{
	In, Out
}DIO_IO;

typedef enum{
	Low, High
}DIO_VALUE;

void DIO_Set_Port_Direction	(PORT Port,DIO_IO Direction);
void DIO_Set_Port_Output	(PORT Port,DIO_VALUE Output);
void DIO_Set_Pin_Direction	(PORT Port,PIN pin,DIO_IO Direction);
void DIO_Set_Pin_Output		(PORT Port,PIN pin,DIO_VALUE Output);
DIO_VALUE DIO_Get_Pin_Value	(PORT Port,PIN pin);

#endif
