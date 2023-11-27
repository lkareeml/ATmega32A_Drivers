/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 26-11-2023            */
/*          Version: 1.0                */
/*          Module: UART                */
/****************************************/


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define Enabled			1
#define Disabled		0

#define Async_Mode		0 
#define Sync_Mode		1

#define Parity_Even		2
#define Parity_Odd		3

#define Stop1_Bit		0
#define Stop2_Bit		1

#define Comm_Size_5		5
#define Comm_Size_6		6
#define Comm_Size_7		7
#define Comm_Size_8		8
#define Comm_Size_9		9

#define TX_Rising_XCK	0
#define TX_Falling_XCK	1





#define UDR_Reg         *((volatile uint8*)0x2C) // UART
#define UBRRH_Reg       *((volatile uint8*)0x40) // UART
#define UBRRL_Reg       *((volatile uint8*)0x29) // UART
#define UCSRA_Reg       *((volatile uint8*)0x2B) // UART
#define UCSRB_Reg       *((volatile uint8*)0x2A) // UART
#define UCSRC_Reg       *((volatile uint8*)0x40) // UART

#endif /* UART_PRIVATE_H_ */