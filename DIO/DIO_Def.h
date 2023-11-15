/****************************************/
/*          Author: Kareem Atef		    */
/*          Date: 10-11-2023		    */
/*          Version: 1.0				*/
/*          Module : DIO Definition     */
/****************************************/

#ifndef DRIVERS_MCAL_DIO_DIO_DEF_H_
#define DRIVERS_MCAL_DIO_DIO_DEF_H_

typedef enum{
	PORTA,
	PORTB,
	PORTC,
	PORTD
}PORT;

typedef enum{
	Pin0,
	Pin1,
	Pin2,
	Pin3,
	Pin4,
	Pin5,
	Pin6,
	Pin7
}PIN;

typedef enum{
	In,
	Out
}DIO_IO;

typedef enum{
	Low,
	High
}DIO_VALUE;
#endif /* DRIVERS_MCAL_DIO_DIO_DEF_H_ */
