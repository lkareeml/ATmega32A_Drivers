/****************************************/
/*          Author: Kareem Atef		      */
/*          Date: 10-11-2023		        */
/*          Version: 1.0				        */
/*          Module : DIO Header         */
/****************************************/

#ifndef DRIVERS_MCAL_DIO_DIO_H_
#define DRIVERS_MCAL_DIO_DIO_H_

void DIO_Set_Port_Direction	(PORT Port,DIO_IO Direction);
void DIO_Set_Port_Output	(PORT Port,DIO_VALUE Output);
void DIO_Set_Pin_Direction	(PORT Port,PIN pin,DIO_IO Direction);
void DIO_Set_Pin_Output		(PORT Port,PIN pin,DIO_VALUE Output);
DIO_VALUE DIO_Get_Pin_Value	(PORT Port,PIN pin);

#endif
