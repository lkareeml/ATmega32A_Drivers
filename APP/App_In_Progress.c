/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 10-11-2023            */
/*          Version: 1.0                */
/*          Module: App                 */
/****************************************/

#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>

#include "../MCAL/DIO/STD_Types.h"
#include "../MCAL/DIO/Bit_Math.h"
#include "../MCAL/DIO/DIO_Header.h"
#include "../MCAL/ADC/ADC_INIT.h"
#include "../MCAL/ADC/ADC_CONFIG.h"
#include "../MCAL/INTERRUPT/Interrupt_H.h"
#include "../MCAL/TIMER/Timer_Init.h"
#include "../MCAL/UART/UART.h"

#include "../HAL/Seven_Segment/Seven_Segment.h"
#include "../HAL/LCD16/LCD_Driver.h"
#include "../HAL/KEYPAD/KEYPAD.h"
#include "../HAL/Buttons/Buttons.h"
#include "../HAL/LEDS/LEDS.h"
#include "../HAL/SERVO/SERVO.h"

#include "App_In_Progress.h"
#include "Helper.h"

#include <string.h>

extern uint8 button0_State;
extern uint8 button1_State;
extern uint8 button2_State;
void reverse(char str[], int length);
char * citoa(int num, char* str, int base);





void TASK34_Bluetooth_UART_STRING(){
	UART_Init();
	uint8 Recieve[11];
	LED0_Init();LED1_Init();LED2_Init();
	while(1){
		UART_Recieve_String8(Recieve);
		if (Recieve[9] == '\n')
		{
			if (memcmp(Recieve,"LED 0 ON",8) == 0)
				{LED_0_On();}
			else if (memcmp(Recieve,"LED 1 ON",8) == 0)
				{LED_1_On();}
			else if (memcmp(Recieve,"LED 2 ON",8) == 0)
				{LED_2_On();}
		}
		if(Recieve[10] == '\n'){
			if (memcmp(Recieve,"LED 0 OFF",9) == 0)
			{LED_0_Off();}
			else if (memcmp(Recieve,"LED 1 OFF",9) == 0)
			{LED_1_Off();}
			else if (memcmp(Recieve,"LED 2 OFF",9) == 0)
			{LED_2_Off();}
		}
	}
}


void TASK33_Bluetooth_UART_Receive_Reply(){
	UART_Init();
	uint8 Recieve;
	//uint8 String[7] = "Kreez";
	LED0_Init();
	while(1)
	{
		Recieve = UART_Receive_Byte8();
		if(Recieve == '0')
		{
			UART_Send_String_Polling8((uint8*)"REPLY");
			LED_0_On();
		}else if(Recieve == '1'){
			LED_0_Off();
		}
	}
}
/***********************************************************/
void TASK32_ISR(){
	Timer2_Set_OCR2_Reg(60);
	static uint32 Loop_counter = 0;
	static uint8 flag = 0;
	uint8 placement_Var = 5;//1~5
	Loop_counter++;
	if((Loop_counter == (40-placement_Var)) && (flag == 0) ){
		DIO_Set_Pin_Output(PORTD,Pin7,High);
		flag = 1;Loop_counter = 0;
	}
	else if ((Loop_counter == placement_Var) && (flag == 1)){
		DIO_Set_Pin_Output(PORTD,Pin7,Low);
		flag =0;Loop_counter = 0;
	}
}
void TASK32_Servo_Timer2_Interrupt(){
	// Timer2 Config : Timer_M_CTC Timer_COM_Pin_TOGGLE  Timer_Pre_1024
	//FREQ_EXIT = 16000000 / (PRESCALER * OCR0) AS FReq = 50 >>> OCR0 =~ 311 BUT max255 ?
	Servo_Init();
	Timer2_Init();
	Timer2_Set_OCR2_Reg(16);
	Timer2_Enable_CTC_Interrupt();
	GIE_Enable();
	while(1);
}
void TASK31_Servo_Delay(){
    Servo_Init();
	Servo_0_Degree_Delay();
    while (1)
    {
		//for(int i =0;i<50;i++)Servo_0_Degree_Delay();
		for(int i =0;i<50;i++)Servo_90_Degree_Delay();
		//for(int i =0;i<50;i++)Servo_180_Degree_Delay();
    }
}
/***********************************************************/
void TASK30_SPI_RFID_MASTER();//???
void TASK29_SPI_RFID_SLAVE();//??
void TASK28_LED_SPI_Blinking_Slave();//???
void TASK27_LED_SPI_Blinking_Master();//??
/***********************************************************/
uint8 TASK26_Receive_With_DIO_UartFrame_RECEIVER(uint8 Parity_Type){
        // RECEIVE UNKNOWN CHARACTER FOR EXAMPLE RECEIVE 'A'
        uint16 received_Data = 0; // 1 Start_Bit + 8 bit data + 1 Parity_bit + 2 stop_bits
        uint8 parity_error_flag = 0;
        uint8 character = 0;
        uint8 parity_bit = 0;
        DIO_Set_Pin_Direction(PORTA,Pin0,In);
        while(Get(PORTA,Pin0));//Wait for Start Bit(LOW)
        for(int i =0;i < 12*sizeof(uint8);i++)
        {
            received_Data = received_Data | ( (Get(PORTA,Pin0)<<i) );
            _delay_ms(1);
        }
        //Check Stop Bits
        if((received_Data & (1<<0)) == 0 && (received_Data & (1<<1)) == 0){// 0b 0000 0 00000000 0 00
            //Check Parity Bit
            //Parity_Type = 1; Argument
            parity_bit = (uint8)(received_Data|0b0000000000000100) >> 2;
            character = (uint8)(received_Data|0b0000011111111000) >> 3;
            parity_error_flag = TASK25_Private_PARITY_Checker(character,parity_bit, Parity_Type);
        }
        if(parity_error_flag == 0){
            return character;
        }
        else if(parity_error_flag == 1){
            return 4;
        }
        return 4;
}
uint8 TASK25_Private_PARITY_Checker(uint8 character,uint8 parity_bit, uint8 Parity_Type){
    uint8 Counter = 0;
    //Parity Checker :
    for(int i =0;i < 8*sizeof(uint8);i++){
        if( (character >> i) & ( 0b00000001 ) )
        Counter++;
    }
    // Parity Agreed on Even
    if(Parity_Type == 0){                        
        if( ( (Counter+parity_bit)/2 ) == 0){    return 0;} // Even Overall Return 0 To indicate Good Parity
        else if( ( (Counter+parity_bit)/2 ) == 1){return 1;}// ODD Overall // Return 1 To indicate Bad Parity
    }
    // Parity Agreed on ODD
    else if(Parity_Type == 1)
    {                        
        if( ( (Counter+parity_bit)/2 ) == 1){return 0;}  // ODD Overall Return 0 To indicate Good Parity
        else if( ( (Counter+parity_bit)/2 ) == 0){ return 1;} //ODD Overall Return 0 To indicate Bad Parity
    }
    return 1;
}
uint8 TASK24_Private_PARITY_Generator(uint8 character, uint8 Parity_Type){
    uint8 parity = 0;
    //Parity Generator : 
    for(int i =0;i < 8*sizeof(uint8);i++){
        if( (character >> i) & ( 0b00000001 ) )
        parity++;
    }
    if((parity/2) == 0)
    {
        if(Parity_Type == 0)//EVEN REQUIRED
            parity = 0;
        else if(Parity_Type == 1)//ODD REQUIRED
            parity = 1;
    }
    else if((parity/2) == 1) // ODD
    {
        if(Parity_Type == 0)//EVEN REQUIRED
            parity = 1;
        else if(Parity_Type == 1)//ODD REQUIRED
            parity = 0;
    }
    return parity;
}
void TASK23_Send_With_DIO_UartFrame_SENDER(uint8 character){    
    // FOR EXAMPLE SEND 'A'
    //Make Parity
    uint8 parity = 0;
    parity = TASK24_Private_PARITY_Generator(character,0);//0 for even, 1 for odd
    
    DIO_Set_Pin_Direction(PORTA,Pin0,Out);// Set Pin Direction
    DIO_Set_Pin_Output(PORTA,Pin0,High);//Start idle Waiting
    _delay_ms(1000);
    // Send Start Bit
        DIO_Set_Pin_Output(PORTA,Pin0,Low);    //Send Start Bit SIGNAL NOW!!
        _delay_ms(1);
    // Send Data
        for(int i =0;i < 8*sizeof(uint8);i++)
        {
            if(character & (1<<i))
            {
                DIO_Set_Pin_Output(PORTA,Pin0,(character & (1<<i)));
                _delay_ms(1);
                }else{
                DIO_Set_Pin_Output(PORTA,Pin0,(character & (1<<i)));
                _delay_ms(1);
            }
        }
    // Send Parity Bit
        if(parity == 1){
            DIO_Set_Pin_Output(PORTA,Pin0,High); // Send Parity Bit
            _delay_ms(1);
        }
        else if(parity == 0){
            DIO_Set_Pin_Output(PORTA,Pin0,Low); // Send Parity Bit
            _delay_ms(1);
        }
    // Send Stop Bit
        DIO_Set_Pin_Output(PORTA,Pin0,Low); // Send Parity Bit
        _delay_ms(1);
        DIO_Set_Pin_Output(PORTA,Pin0,Low); // Send Parity Bit
        _delay_ms(1);
}
/***********************************************************/
uint8 TASK22_RECEIVE_WITH_DIO_MICRO_RECEIVER()
{
    // RECEIVE UNKNOWN CHARACTER FOR EXAMPLE RECEIVE 'A' 
    uint8 received_Char = 0;
    DIO_Set_Pin_Direction(PORTA,Pin0,In);
    //WAIT TILL LOW
    while(Get(PORTA,Pin0));
    //SIGNAL SENDING  STARTED!!!
    for(int i =0;i < 8*sizeof(uint8);i++)
    {        
        received_Char = received_Char | ( (Get(PORTA,Pin0)<<i) );
        _delay_ms(1);
    }
    return received_Char;
}

void TASK21_SEND_WITH_DIO_MICRO_SENDER(uint8 character)
{
    // FOR EXAMPLE SEND 'A' 
    DIO_Set_Pin_Direction(PORTA,Pin0,Out);// Set Pin Direction
    DIO_Set_Pin_Output(PORTA,Pin0,High);//Start Waiting
    _delay_ms(1000);
    DIO_Set_Pin_Output(PORTA,Pin0,Low);    //START SENDING SIGNAL NOW!!
    // For Example : 01000001 
    for(int i =0;i < 8*sizeof(uint8);i++)
    {
        if(character & (1<<i))
        {
            DIO_Set_Pin_Output(PORTA,Pin0,(character & (1<<i)));
            _delay_ms(1);
        }else{
            DIO_Set_Pin_Output(PORTA,Pin0,(character & (1<<i)));
            _delay_ms(1);
        }
    }
}
/***********************************************************/
void TASK20_MOTOR_FASTPWM(){
    ///FAST PWM LED POWER UP AND DOWN
    // SET FASTPWM FOR TIMER 1
    //DIO_Set_Pin_Direction(PORTB,Pin3,Out);
    uint8 digital = 126;
    //uint8 old_digital = 126;
    Timer0_Set_OCR0_Reg(digital);
    Timer0_Init();
    Timer0_Enable_CTC_Interrupt();
    GIE_Enable();
    while (1)
    {
        //digital = ADC_Convert_8bit(ADC_Ch1);
        /*if((abs(digital-old_digital) > 10))
        {
            old_digital = digital;
            Timer0_Set_OCR0_Reg(digital);
        }*/
    }
}

/***********************************************************/
