/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 26-11-2023            */
/*          Version: 1.0                */
/*          Module: UART                */
/****************************************/

#ifndef UART_H_
#define UART_H_

void UART_Init();

void UART_Send_Byte_Polling(uint8 Data);
uint8 UART_Receive_Byte(void);
void UART_Send_String_Polling(uint8 *String);
void UART_Recieve_String(uint8 *String);

void UART_Send_Byte_Polling(uint16 Data);
uint16 UART_Receive_Byte(void);
void UART_Send_String_Polling(uint16 *String);
void UART_Recieve_String(uint16 *String);






/*
UART == USART : Universal Synchronous/Asynchronous Receiver Transmitter

Simplex : One party is transmitter, one party is receiver : Like TV and radio
Half Duplex : Like COP Press police walkie talkie Send OR receive at a time
Full Duplex : Send and receive at the same time like Phone call

Serial   :  on one line, Or Two lines max, one to send one to receive
Parallel : 8 bit = 8 lines, 16 bit = 16 lines , ... each pin have a line like a bus
Parallel problem : complex connection with many wires
Parallel problem : cross-talk : magnetic field effect each wire and the fellow wire
Parallel problem : Timing Skew : each bit arrives defferently in speed;

synchronous  : Both share a wire sending a clock so both get same clock speed (LIN)
asynchronous : Both agree on specific speed, on code itself (BITRATE)(SERIAL)

Master : Initiate communication , Generate Clock , Select slave
Single Master-Multi slaves (SPI)(LIN)	
Multi Masters - Multi Slaves (I2C)
Multi Masters - No slave (CAN)
Pair-Pair (UART)

++++ UART : ++++
 RX : Receive  using TX --- TX : Transmit using RX
 Full-Duplex  -- Wired -- Serial -- Asynchronous -- Pair to Pair
 Baud rate : 9600baud/sec if baud = 1bit >>> 9600 bit / second
 Baud rate : 9600baud/sec if baud = 2bit >>> 2*9600 bit / second

 Frame      : Start_Bit ++++ 5-9Bit_Data ++++ Parity_Bit ++++ Stop_Bit
 Parity_Bit : Even or Odd (The add of all Data+Parity Bits)
 Stop_Bit   : can be 1 or 2 bit, as High only
 throughput : Data/Frame
 PAGE_138
 max_throughput  = maxData/Frame = 9 / ( 1+9+1) %100 = 81.8%
 min_throughput  = minData/Frame = 5 / ( 1+5+2) %100 = 55.5%
 REWRITE THE DRIVER

Equations for Calculating Baud Rate Register Setting
	Asynchronous Normal Mode : UBBRR = (fosc/(16*BAUD)) - (1)
	Asynchronous Double Speed Mode (U2X = 1) : UBBRR = (fosc/(8*BAUD)) - (1)

Frame Formats : 
	Start_Bit(1) ++++ Data_Bit(5~9) ++++ Parity_Bit(1~2) ++++ Stop_Bit(1~2)
	Start bit, always low
	Data bits (0 to 8)
	Parity bit. Can be odd or even
	Stop bit, always high
	No transfers on (RxD or TxD). An IDLE line must be high

initialization process normally consists of:

	setting the baud rate,  : 
		U2X = 0, 
		URSEL: Register Select (0_UBRRH)
		Normal Mode : UBBRR = (fosc/(16*BAUD)) - (1) OR 2X Mode UBBRR = (fosc/(8*BAUD)) - (1)
		
	setting frame format :
			URSEL: Register Select (1_UCSRC)
			UMSEL: USART Mode Select (0_Async 1_Sync)
			UPM1:0: Parity Mode (10_Even/11_Odd)
			USBS: Stop Bit Select (0_1Bit/1_2Bit)	
			Choose Size : UCSZ2 (d0_5/d3_8/d7_9)
			
	enabling the Transmitter or the Receiver depending usage
		**Bit 4 – RXEN: Receiver Enable							Enable_Bit
		**Bit 3 – TXEN: Transmitter Enable						Enable_Bit
		
	interrupt driven USART operation, 
	
	*** Data Transmission – The USART Transmitter
			Sending Frames with 5 to 8 Data Bit
			Sending Frames with 9 Data Bit ---- the ninth bit must be written before writing to UDR
			Transmitter Flags and Interrupts
			Parity Generator
			Disabling the Transmitter

	***	Data Reception – The USART Receiver
			Receiving Frames with 5 to 8 Data Bits
			Receiving Frames with 9 Data bits
			Receive Compete Flag and Interrupt
			Receiver Error Flags
			Parity Checker
			Disabling the Receiver
			Flushing the Receive Buffer
Asynchronous Data Reception
*Asynchronous Clock Recovery
*Asynchronous Data Recovery
*Asynchronous Operational Range

Multi-processor Communication Mode

Accessing UBRRH/UCSRC Registers
*Write Access
**If URSEL is zero during a write operation,UBRRH will be updated. 
**If URSEL is one, the UCSRC setting will be updated.
*Read Access

++++UDR – USART I/O Data Register
** UDR (Read) / UDR (Write)								Data_Reg

++++UCSRA – USART Control and Status Register A
**Bit 7 – RXC: USART Receive Complete					Flag-Bit	G
**Bit 6 – TXC: USART Transmit Complete					Flag-Bit	G
**Bit 5 – UDRE:Data Register Empty						Flag-Bit	G
**Bit 4 – FE: Frame Error								Flag-Bit	G
**Bit 3 – DOR: Data OverRun								Flag-Bit	G
**Bit 2 – PE: Parity Error								Flag-Bit	G
**Bit 1 – U2X: Double.USART.Trans.Speed (1_En/0_Dis)	Choice_Bit	0
**Bit 0 – MPCM: Multi-processor.ComMode (1_En/0_Dis)	Choice_Bit	0
	
++++UCSRB – USART Control and Status Register B
**Bit 7 – RXCIE: RX Complete Interrupt Enable			Enable_Bit	
**Bit 6 – TXCIE: TX Complete Interrupt Enable			Enable_Bit		
**Bit 5 – UDRIE: Data Reg Empty Interrupt Enable		Enable_Bit
**Bit 4 – RXEN: Receiver Enable							Enable_Bit
**Bit 3 – TXEN: Transmitter Enable						Enable_Bit
**Bit 2 – UCSZ2: Character Size							Choice_Bit
**Bit 1 – RXB8: Receive Data Bit 8						Extra_Bit
**Bit 0 – TXB8: Transmit Data Bit 8						Extra_Bit

++++UCSRC – USART Control and Status Register C
**Bit 7 – URSEL: Register Select						Choice_Bit
**Bit 6 – UMSEL: USART Mode Select (0_Async 1_Sync)		Choice_Bit
**Bit 5:4 – UPM1:0: Parity Mode (10_Even/11_Odd)		Choice_Bit
**Bit 3 – USBS: Stop Bit Select (0_1Bit/1_2Bit)			Choice_Bit
**Bit 2:1 –UCSZ1:0: Character Size (d0_5/d3_8/d7_9)		Choice_Bit
**Bit 0 – UCPOL: Clock Polarity (For Sync Mode)			Choice_Bit

++++UBRRL and UBRRH – USART Baud Rate Registers
**Bit 15 – URSEL: Register Select(0_UBRRH/1_UCSRC)		Choice_Bit
**Bit 14:12 – Reserved Bits
**Bit 11:0 – UBRR11:0: USART Baud Rate Register(Table)	Choice_Bit
Examples of Baud Rate Setting

*/
#endif /* UART_H_ */