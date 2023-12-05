/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 10-11-2023            */
/*          Version: 1.0                */
/*          Module: App                 */
/****************************************/
#include "../MCAL/DIO/STD_Types.h"


#ifndef ALLAPPS_H_
#define ALLAPPS_H_

//Sys lock after 2 trials
//
void App_038_USERMANAGEMENT_SYSTEM();

void App_037_Save_Data_EEPROM_Read_LCD();
void App_036_SEND_CHAT_LCDNOTPHONE_AND_PHONE_UART_BLUETOOTH_LOGIN_SYS();
void App_035_SEND_USERNAME_PASSWORD_UART_BLUETOOTH_LOGIN_SYS();

/***************************************/
void App_034_Bluetooth_UART_STRING_LED_ON_OFF();
void App_033_Bluetooth_UART_Receive_Reply();
void App_032_ISR();
void App_032_Servo_Timer2_Interrupt();
void App_031_Servo_Delay();
/************** IN PROGRESS ***************/
void  App_030_SPI_RFID_MASTER();
void  App_029_SPI_RFID_SLAVE();
void  App_028_LED_SPI_Blinking_Slave();
void  App_027_LED_SPI_Blinking_Master();
/***************************************/
uint8 App_026_Receive_With_DIO_UartFrame_RECEIVER(uint8 Parity_Type);
uint8 App_025_Private_PARITY_Checker(uint8 character,uint8 parity_bit, uint8 Parity_Type);
uint8 App_024_Private_PARITY_Generator(uint8 character, uint8 Parity_Type);
void  App_023_Send_With_DIO_UartFrame_SENDER(uint8 character);
/******************* HALF-Dublex ********************/
uint8 App_024_Receive_With_DIO_UartFrame_RECEIVER();
void  App_023_Send_WITH_DIO_UartFrame_SENDER(uint8 character);
uint8 App_022_RECEIVE_WITH_DIO_MICRO_RECEIVER();
void  App_021_SEND_WITH_DIO_MICRO_SENDER(uint8 character);
/************** IN PROGRESS ***************/
void  App_020_MOTOR_FASTPWM();
/***************************************/
#endif /* ALLAPPS_H_ */