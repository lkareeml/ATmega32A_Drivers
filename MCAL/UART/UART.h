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
#define Parity_Disable     0
#define Parity_Even        1
#define Parity_Odd         2
#define Stop1_Bit          0
#define Stop2_Bit          1
#define Comm_Size_5        5
#define Comm_Size_6        6
#define Comm_Size_7        7
#define Comm_Size_8        8
#define Comm_Size_9        9
#define TX_Rising_XCK      0
#define TX_Falling_XCK     1


uint8 String_Comparitor(uint8 *String1,uint8 *String2);

void UART_Dynamic_INIT(uint8 CommSize,uint8 SyncMode,uint8 SyncPolarity,uint8 ParityMode,uint8 Stopbit,uint8 X2SpeedMode,uint32 baudRate);
void UART_Enable_TX();
void UART_Disable_TX();
void UART_Enable_RX();
void UART_Disable_RX();
void UART_Enable_TX_Interrupt();
void UART_Disable_TX_Interrupt();
void UART_Enable_RX_Interrupt();
void UART_Disable_RX_Interrupt();
void UART_Enable_DataReg_Empty_Interrupt();
void UART_Disable_DataReg_Empty_Interrupt();

void   UART_Init();

void   UART_Send_Byte_Polling_8(uint8 Data);
uint8  UART_Receive_Byte_8(void);

void   UART_Send_String_Polling_8(sint8 *String);
void   UART_Recieve_String_8(sint8 *String);

void   UART_Send_Number_Polling_32(uint32 Number);
uint32 UART_Recieve_Number_Polling_32(void);

// void   UART_Send_Byte_Polling16(uint16 Data);
// uint16 UART_Receive_Byte16(void);
// void   UART_Send_String_Polling16(uint16 *String);
// void   UART_Recieve_String16(uint16 *String);

#endif /* UART_H_ */