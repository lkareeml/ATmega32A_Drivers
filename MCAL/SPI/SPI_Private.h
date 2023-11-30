/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 26-11-2023            */
/*          Version: 1.0                */
/*          Module: SPI Private         */
/****************************************/


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define SPDR_Reg       *((volatile uint8*)0x2F) // SPI
#define SPSR_Reg       *((volatile uint8*)0x2E) // SPI
#define SPCR_Reg       *((volatile uint8*)0x2D) // SPI

#endif /* UART_PRIVATE_H_ */