/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 26-11-2023            */
/*          Version: 1.0                */
/*          Module: UART                */
/****************************************/

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_
//		Option_Name							Selected_Option			Available_Options
#define Double_Speed_Mode					Disabled				// Enabled -- Disabled
#define UART_BAUD							9600UL					// 2400UL ~~ 250000UL
#define Sync_Mode_Select					Async_Mode				// Async_Mode -- Sync_Mode
#define Parity_Mode							Parity_Disable			// Parity_Even -- Parity_Odd
#define Stop_bit_size						Stop1_Bit				// Stop2_Bit -- Stop1_Bit
#define Comm_Character_Size					Comm_Size_8				// Comm_Size_5.6.7.8.9
#define Sync_Mode_Clock_Polarity			TX_Rising_XCK			// TX_Rising_XCK -- TX_Falling_XCK
#define UART_TX_Enable						Enabled					// Enabled -- Disabled
#define UART_RX_Enable						Enabled					// Enabled -- Disabled
#define UART_TX_Complete_Interrupt			Disabled				// Enabled -- Disabled
#define UART_RX_Complete_Interrupt			Disabled				// Enabled -- Disabled
#define UART_Data_Reg_Empty_Interrupt		Disabled				// Enabled -- Disabled

//#define Multi_processor_Com_Mode	 >>>> (UCSRA_Reg,0);	Only operate for
// (the first stop or the ninth bit) is one  the frame contains an address. 
// (the first stop or the ninth bit) is zero the frame is a data frame

#endif /* UART_CONFIG_H_ */