/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 26-11-2023            */
/*          Version: 1.0                */
/*          Module: UART                */
/****************************************/


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define UDR_Reg         *((volatile uint8*)0x2C) // UART
#define UBRRH_Reg       *((volatile uint8*)0x40) // UART
#define UBRRL_Reg       *((volatile uint8*)0x29) // UART
#define UCSRA_Reg       *((volatile uint8*)0x2B) // UART
#define UCSRB_Reg       *((volatile uint8*)0x2A) // UART
#define UCSRC_Reg       *((volatile uint8*)0x40) // UART

#endif /* UART_PRIVATE_H_ */