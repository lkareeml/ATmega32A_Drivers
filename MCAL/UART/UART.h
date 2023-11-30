/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 26-11-2023            */
/*          Version: 1.0                */
/*          Module: UART                */
/****************************************/

#ifndef UART_H_
#define UART_H_

#define Disabled           0
#define Enabled            1
#define Async_Mode         0
#define Sync_Mode          1
#define Parity_Even        2
#define Parity_Odd         3
#define Stop1_Bit          0
#define Stop2_Bit          1
#define Comm_Size_5        5
#define Comm_Size_6        6
#define Comm_Size_7        7
#define Comm_Size_8        8
#define Comm_Size_9        9
#define TX_Rising_XCK      0
#define TX_Falling_XCK     1

void   UART_Init();

void   UART_Send_Byte_Polling8(uint8 Data);
uint8  UART_Receive_Byte8(void);
void   UART_Send_String_Polling8(uint8 *String);
void   UART_Recieve_String8(uint8 *String);

void   UART_Send_Byte_Polling16(uint16 Data);
uint16 UART_Receive_Byte16(void);
void   UART_Send_String_Polling16(uint16 *String);
void   UART_Recieve_String16(uint16 *String);

#endif /* UART_H_ */