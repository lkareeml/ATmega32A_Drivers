/****************************************/
/*          Author: Kareem Atef		    */
/*          Date: 09-12-2023		    */
/*          Version: 1.0				*/
/*          Content: Proof Of Concept   */
/****************************************/


#ifndef PROOF_H_
#define PROOF_H_

/************** IN PROGRESS USING SIMULATION 2 MCROCONTROLLR ***************/

void  App_025_SPI_RFID_MASTER();
void  App_025_SPI_RFID_SLAVE();

void  App_024_LED_SPI_Blinking_Slave();
void  App_024_LED_SPI_Blinking_Master();

/****************** UART WITHOUT PREFERAL **************/

uint8 App_023_Receive_With_DIO_UartFrame_RECEIVER(uint8 Parity_Type);
uint8 App_023_Private_PARITY_Checker(uint8 character,uint8 parity_bit, uint8 Parity_Type);
uint8 App_023_Private_PARITY_Generator(uint8 character, uint8 Parity_Type);
void  App_023_Send_With_DIO_UartFrame_SENDER(uint8 character);
/******************* HALF-Dublex Manual Theory ********************/
uint8 App_022_RECEIVE_WITH_DIO_MICRO_RECEIVER();
void  App_022_SEND_WITH_DIO_MICRO_SENDER(uint8 character);


#endif /* PROOF_H_ */