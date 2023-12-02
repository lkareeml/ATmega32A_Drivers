/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 10-11-2023            */
/*          Version: 1.0                */
/*          Module: App                 */
/****************************************/
#include "../MCAL/DIO/STD_Types.h"


#ifndef ALLAPPS_H_
#define ALLAPPS_H_

void TASK34_Bluetooth_UART_STRING();
void TASK33_Bluetooth_UART_Receive_Reply();

/***************************************/
void TASK32_ISR();
void TASK32_Servo_Timer2_Interrupt();
void TASK31_Servo_Delay();
/***************************************/
void TASK30_SPI_RFID_MASTER();//???
void TASK29_SPI_RFID_SLAVE();//??
void TASK28_LED_SPI_Blinking_Slave();//???
void TASK27_LED_SPI_Blinking_Master();//??
uint8 TASK26_Receive_With_DIO_UartFrame_RECEIVER(uint8 Parity_Type);
uint8 TASK25_Private_PARITY_Checker(uint8 character,uint8 parity_bit, uint8 Parity_Type);
uint8 TASK24_Private_PARITY_Generator(uint8 character, uint8 Parity_Type);
void TASK23_Send_With_DIO_UartFrame_SENDER(uint8 character);
/******************* HALF-Dublex ********************/
uint8 TASK24_Receive_With_DIO_UartFrame_RECEIVER();
void TASK23_Send_WITH_DIO_UartFrame_SENDER(uint8 character);
/********************* HALF-Dublex ******************/
uint8 TASK22_RECEIVE_WITH_DIO_MICRO_RECEIVER();
void TASK21_SEND_WITH_DIO_MICRO_SENDER(uint8 character);
/***************************************/
void TASK20_MOTOR_FASTPWM();

#endif /* ALLAPPS_H_ */