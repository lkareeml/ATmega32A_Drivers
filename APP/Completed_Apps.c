/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 24-11-2023            */
/*          Version: 1.0                */
/*          Module: 7 Apps              */
/****************************************/

#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>

#include "../MCAL/DIO/STD_Types.h"
#include "../MCAL/DIO/DIO_Header.h"
#include "../MCAL/ADC/ADC_INIT.h"
#include "../MCAL/ADC/ADC_CONFIG.h"
#include "../MCAL/INTERRUPT/Interrupt_H.h"
#include "../MCAL/TIMER/Timer_Init.h"
#include "../HAL/Seven_Segment/Seven_Segment.h"
#include "../HAL/LCD16/LCD_Driver.h"
#include "../HAL/KEYPAD/KEYPAD.h"
#include "../HAL/Buttons/Buttons.h"
#include "../HAL/LEDS/LEDS.h"
#include "Helper.h"

uint8 button0_State;
uint8 button1_State;
uint8 button2_State;


void App_019_TIMER_FASTPWM_LED(){
    ///FAST PWM LED POWER UP AND DOWN
    // SET FASTPWM
    ADC_Init();
    DIO_Set_Pin_Direction(PORTB,Pin3,Out);
    uint8 digital = 2;
    uint8 old_digital = 2;
    digital = ADC_Convert_8bit(ADC_Ch1);
    old_digital = digital;
    Timer0_Set_OCR0_Reg(digital);
    Timer0_Init();
    Timer0_Enable_CTC_Interrupt();
    GIE_Enable();
    while (1)
    {
        digital = ADC_Convert_8bit(ADC_Ch1);
        if((abs(digital-old_digital) > 10))
        {
            old_digital = digital;
            Timer0_Set_OCR0_Reg(digital);
        }
    }
}


void App_018_TIMER_CTC_ADC_POTENTIOMETER(){
    // SET CTC TIMER0
    ADC_Init();
    DIO_Set_Pin_Direction(PORTB,Pin3,Out);
    uint8 digital = 2;
    uint8 old_digital = 2;
    digital = ADC_Convert_8bit(ADC_Ch1);
    old_digital = digital;
    Timer0_Set_OCR0_Reg(digital);
    Timer0_Init();
    Timer0_Enable_CTC_Interrupt();
    GIE_Enable();
    while (1)
    {
        digital = ADC_Convert_8bit(ADC_Ch1);
        if((abs(digital-old_digital) > 10))
        {
            old_digital = digital;
            Timer0_Set_OCR0_Reg(digital);
        }
    }
}
void App_017_TIMER_CTC_Freq(){
    DIO_Set_Pin_Direction(PORTA,Pin0,Out);
    DIO_Set_Pin_Output(PORTA,Pin0,Low);
    Timer0_Init();
    Timer0_Set_OCR0_Reg(200);
    Timer0_Enable_CTC_Interrupt();
    GIE_Enable();
    while (1)
    {
    }
}
void App_017_ISR(){
    //Timer0_Set_OCR0_Reg(195);
    static uint32 Loop_counter = 0;
    static uint8 flag = 0;
    Loop_counter++;
    if(Loop_counter == 1){
        Loop_counter = 0;
        if(flag == 0){
            DIO_Set_Pin_Output(PORTA,Pin0,High);
            flag = 1;
        }
        else if (flag == 1){
            DIO_Set_Pin_Output(PORTA,Pin0,Low);
            flag = 0;
        }
    }
}
void App_016_TIMER_SQRWAVE_NORMAL(){
    DIO_Set_Pin_Direction(PORTD,Pin7,Out);
    DIO_Set_Pin_Output(PORTD,Pin7,Low);
    Timer0_Init();
    //Timer0_Set_TCNT0_Reg(200);
    Timer0_Enable_Overflow_Interrupt();
    GIE_Enable();
    while (1)
    {
    }
}
void App_016_ISR(){
     static uint32 Loop_counter = 0;
     static uint8 flag = 0;
     Loop_counter++;
     if(Loop_counter == 13){
        Loop_counter = 0;
        //Timer0_Set_TCNT0_Reg(195);
         if(flag == 0){
             DIO_Set_Pin_Output(PORTD,Pin7,High);
             flag = 1;
         }
         else if (flag == 1){
             DIO_Set_Pin_Output(PORTD,Pin7,Low);
             flag = 0;
         }
    }
}
void App_015_TIMER_LED(){
    LED1_Init();
    Timer0_Init();
    Timer0_Set_TCNT0_Reg(247);
    Timer0_Enable_Overflow_Interrupt();
    GIE_Enable();
	while(1);
}
void App_015_ISR(){//TIMER0_OVF_vect
    static uint8 counter = 0;
    static uint8 flag = 0;
    counter++;
    if(counter == 62){
        if(flag == 0){
            LED_1_On();
            flag = 1;
        }
        else if (flag == 1){
            LED_1_Off();
            flag = 0;
        }
        counter = 0;
        Timer0_Set_TCNT0_Reg(247);
    }
}

void App_010_ADC_Manual_Interrupt(){    // ADC with interrupt not polling
    ADC_Init();
    LCD_Init();
    ADC_Manual_Interrupt();
    GIE_Enable();
    while (1);
}
void App_010_ISR_ADC(){
    uint8 digital = 0;
    uint8 old_digital=0;
    float analog = 0;
    digital = ADC_Return_Result();
    sint8 string[20];
    if((abs(digital-old_digital) > 2))
    {
        analog = digital * (50.0/256.0);
        dtostrf(analog,5,3,string);//3 Decimal points
        old_digital = digital;
        LCD_Send_Clear_Screen();
        LCD_Send_String(string);
        _delay_ms(1000);
    }
    ADC_Manual_Interrupt();
}
void App_011_ADC_Timer_No_Interrupt(){    //ADC Triggered By Timer0 Polling Version
    LCD_Init();
    Timer0_Init();
    ADC_Timer_No_Interrupt();// MAKE SURE TIMER ON NORMAL MODE!!
    while (1)
    {
        uint8 digital = ADC_Timer_Polling_Result();
        uint8 old_digital=0;
        float analog = digital * (50.0/256.0);    //0--255 >>> 0 -- 50 Temp
        sint8 string[20];
        if((abs(digital-old_digital) > 2))
        {
            dtostrf(analog,5,3,string);//3 Decimal points
            old_digital = digital;
            LCD_Send_Clear_Screen();
            LCD_Send_String(string);
            _delay_ms(500);
        }
    }
}
void App_012_ADC_Timer_With_Interrupt()
{
    ADC_Init();
    LCD_Init();
    Timer0_Init();
    //Timer0_Enable_Overflow_Interrupt();
    ADC_Timer_With_Interrupt();/*
    SFIOR_Reg = SFIOR_Reg | 0b10000000;
    ADCMUX_Reg = ((ADCMUX_Reg & 0b11100000) | ADC_Ch1);
    */
    GIE_Enable();
    while (1)
    {
    }
}
void App_012_ISR_ADC_Timer(){
        uint8 digital = ADC_Return_Result();// Returns ADCH 
        static uint8 old_digital = 0;
        float analog = digital * (50.0/256.0);    //0--255 >>> 0 -- 50 Temp
        sint8 string[20];
        if((abs(digital-old_digital) > 2))
        {
            dtostrf(analog,5,3,string);//3 Decimal points
            old_digital = digital;
            LCD_Send_Clear_Screen();
            LCD_Send_String(string);
        }
        ADC_Start();
        //Bit 4 – ADIF: ADC Interrupt Flag
        //Bit 6 – ADSC: ADC Start Conversion
        /* THIS IS A MUST TO BE ABLE TO WORK FULLY
        #include <avr/interrupt.h>
        ISR(TIMER0_COMP_vect){
            return;
        }
        ISR(ADC_vect){
                App_012_ISR_ADC_Timer();
        }
        */
}

void App_013_KEYPAD_LCD_INTERRUPT()
{
    LCD_Init();
    LED1_Init();
    EXTI0_Set_Direction_Input();
    EXTI0_Set_Internal_Pull_Up();
    LED_0_Off();
    EXTI0_Init();
    EXTI0_Enable();
    GIE_Enable();
    while(1);
}
void App_013_ISR()
{
    KEYPAD_Init();
    uint8 x='\0';
    x= KEYPAD_Get_Pressed_Key();
    LCD_Send_Char(x);
}



void App_014_LED_BUTTON_INTERRUPT()
{
    LED0_Init();
    EXTI0_Set_Direction_Input();
    EXTI0_Set_Internal_Pull_Up();
    LED_0_Off();
    EXTI0_Init();
    EXTI0_Enable();//PIE
    GIE_Enable();//GIE
    while(1){
		
	}
}

void App_014_ISR()
{
    static uint8 EXTI0_Flag = 0;
    if(EXTI0_Flag == 0)
    {
        LED_0_On();
        EXTI0_Flag = 1;
    }
    else
    {
        LED_0_Off();
        EXTI0_Flag = 0;
    }
}
/***********************************************************/
void App_009_ADC_Potentiometer_Temperature_LCD()
{
    ADC_Init();
    LCD_Init();
    LED0_Init();
    LED1_Init();
    LED2_Init();
    uint8 digital = 0;
    uint8 old_digital=0;
    float analog = 0;
    sint8 string[20];
    uint16 temp = 0;
    while (1)
    {
        digital = ADC_Convert_8bit(ADC_Ch1);
        analog = digital * (5.0/256.0);//0--5 >>> 0 -- 500 Temp
        temp = analog * 100;
        
        if(temp >=0 && temp < 100){
            LED_0_Off();LED_1_Off();LED_2_Off();
        }
        if((temp >= 100) && (temp <250)){
            LED_0_On();LED_1_Off();LED_2_Off();
        }
        if(temp >= 250 && temp < 400){
            LED_0_On();LED_1_On();LED_2_Off();
        }
        if(temp >400){
            LED_0_On();LED_1_On();LED_2_On();
        }
        dtostrf(temp,5,3,string);
        if((abs(digital-old_digital) > 0.1))
        {
            old_digital = digital;
            LCD_Send_Clear_Screen();
            LCD_Send_String(string);
            _delay_ms(1000);
        }
    }
}
void App_008_ADC_Potentiometer()
{
    ADC_Init();
    LCD_Init();
    Button_Init();
    uint8 digital = 0;
    uint8 old_digital=0;
    float analog = 0;
    sint8 string[20];
    while (1)
    {
        digital = ADC_Convert_8bit(ADC_Ch1);
        analog = digital * (5.0/256.0);
        dtostrf(analog,5,7,string);
        if((abs(digital-old_digital) > 0.1))
        {
            old_digital = digital;
            LCD_Send_Clear_Screen();
            LCD_Send_String(string);
            _delay_ms(1000);
        }
    }
}

void App_007_Password_Checker_LCD_KEYPAD()
{
	LCD_Init();
	KEYPAD_Init();
	uint8 x='\0';
	uint8 registered_username[4] = "1234";
	uint8 registered_password[4] = "5432";
	while(1)
	{
		uint8 username[6] = "";
		uint8 password[6] = "";
		uint8 username_counter = 0;
		uint8 password_counter = 0;
		uint8 username_check = 0;
		uint8 password_check = 0;
		LCD_Send_String("User:");
		while(username_counter <= 6)
		{
			x='\0';
			x = KEYPAD_Get_Pressed_Key();
			if(x == '\0') continue;

			
			if(x >= '0' && x <='9')
			{
				LCD_Send_Char(x);
				username[username_counter] = x;
				username_counter++;
			}
			else if(x == '*' && username_counter > 0)
			{
				LCD_Delete_Last_Written();
				username[username_counter] = '\0';
				username_counter--;
			}
			else if(x >= 'A' && x <='D')
			{
				for(int i=0;i<username_counter;i++){
					if(username[i] == registered_username[i])
					continue;
					else username_check = 1;
				}
				break;
			}
			if(username_counter > 5)
			{
				username_check = 1;break;
			}
		}
		
		LCD_Send_Clear_Screen();
		if(username_check == 1)
		{
			LCD_Send_String("Wrong User");
			_delay_ms(3000);
			LCD_Send_Clear_Screen();
		}
		else if(username_check == 0)
		{
			LCD_Send_String("Correct User");
			_delay_ms(3000);
			LCD_Send_Clear_Screen();
			LCD_Send_String("Password:");
			while(password_counter <= 6)
			{
				x='\0';
				x = KEYPAD_Get_Pressed_Key();
				if(x == '\0') continue;
				_delay_ms(50);
				if(x >= '0' && x <='9')
				{
					LCD_Send_Char(x);
					password[password_counter] = x;
					password_counter++;
				}
				else if(x == '*' && password_counter >0)
				{
					LCD_Delete_Last_Written();
					password[password_counter] = '\0';
					password_counter--;
				}
				else if(password_counter > 0 && x >= 'A' && x <='D')
				{
					for(int i = 0;i<password_counter;i++){
						if(password[i] == registered_password[i])
						continue;
						else password_check = 1;
					}
					break;
				}
				if(password_counter >4)
				{
					password_check = 1;break;
				}
			}
			LCD_Send_Clear_Screen();
			if(password_check == 1)
			{
				LCD_Send_String("Wrong Password");
				_delay_ms(3000);
				LCD_Send_Clear_Screen();
			}
			else if(password_check == 0)
			{
				LCD_Send_String("Correct Password");
				_delay_ms(3000);
				LCD_Send_String("Welcome 1234");
				_delay_ms(3000);
				LCD_Send_Clear_Screen();
			}
		}
	}
}

void App_006_Calculator_LCD_Keypad()
{
	LCD_Init();
	KEYPAD_Init();
	uint8 x='\0';
	uint32 first_Num = 0;
	uint32 second_Num = 0;
	uint32 final_Num = 0;
	uint8 operand = '0';
	uint8 stage = 0;
	while(1)
	{
		x = '\0';
		x = KEYPAD_Get_Pressed_Key();
		_delay_ms(50);
		
		if(x=='\0') continue;
		
		///Reset Everything New Start
		if(stage == 2)
		{
			LCD_Send_Clear_Screen();
			stage=0;
			second_Num = 0;
			operand = '0';
			if ((x >= '0' && x <= '9') || (x == '*'))
			{
				first_Num = 0;
			}
			/// IF USER PRESSED OPRAND TO CONTINUE WITH THE PREVIOUS ANSWER
			else if ((x >= 'A' && x <= 'D'))
			{
				first_Num = final_Num;
				LCD_Send_String("ANS");
				stage = 1;
			}
		}


		/// ----------------------------------			OPERAND
		if((x >= 'A' && x <= 'D') && (first_Num > 0) && (second_Num == 0))
		{
			if(stage == 1 && operand != '0')
			{
				LCD_Delete_Last_Written();
			}
			switch(x)
			{
				case 'A': operand = '+';break;
				case 'B': operand = '-';break;
				case 'C': operand = '*';break;
				case 'D': operand = '/';break;
			}
			LCD_Send_Char(operand);
			stage = 1;
		}
		/// ----------------------------------			FIRST NUMBER
		else if((stage == 0) && (x >= '0' && x <= '9'))
		{
			first_Num = (first_Num * 10) + (x- '0');///55  >> 5*10 ==50 + 5 == 55
			if(first_Num > 0) LCD_Send_Char(x);
		}
		/// ----------------------------------			SECOND NUMBER
		else if((stage == 1) && (x >= '0' && x <= '9'))
		{
			second_Num = (second_Num * 10) + (x - '0');
			if(second_Num > 0) LCD_Send_Char(x);
		}
		/// ----------------------------------			EQUAL SIGN
		else if((stage == 1) && (x=='#') && (second_Num >0))
		{
			switch(operand)
			{
				case '+': final_Num = first_Num + second_Num;break;
				case '-': final_Num = first_Num - second_Num;break;
				case '*': final_Num = first_Num * second_Num;break;
				case '/':
				final_Num = (first_Num/second_Num);
				break;
				default:LCD_Send_String("Error Retry");break;
			}
			char snum[6];
			citoa(final_Num, snum, 10);
			LCD_Send_Char('=');
			LCD_Send_String(snum);
			stage = 2;
		}

		/// ----------------------------------			CLEAR ENTRY ALL CASES
		else if((x == '*') && (first_Num > 0))
		{
			LCD_Delete_Last_Written();
			///FIRST CASE ONLY THE FIRST NUMBER IS WRITTEN
			if((stage==0) && (second_Num == 0))
			{
				first_Num = first_Num / 10;
			}
			///SECOND CASE THE FIRST NUMBER IS WRITTEN AND THE OPERAND IS WRITTEN
			else if((stage==1) && (second_Num == 0))
			{
				operand = '0';
				stage = 0;
			}
			///THIRD CASE  THE FIRST NUMBER IS WRITTEN OPERAND WRITTEN AND SECOND NUMBER IS WRITTEN
			else if((stage==1) && (second_Num > 0))
			{
				second_Num = second_Num / 10;
			}
		}
		
	}
}

void App_005_Keypad_Prints_LCD()
{
	LCD_Init();
	KEYPAD_Init();
	uint8 x='\0';
	while(1){
		x='\0';
		while(x=='\0'){
			do{
				x = KEYPAD_Get_Pressed_Key();
			}while(x=='\0');
			_delay_ms(50);
			LCD_Send_Char(x);
		}
	}
}

void App_004_Traffic_Light()
{
	///App_004: 3 led Traffic ,7seg number red 10s yellow 10s green 10s
	LED0_Init();
	LED1_Init();
	LED2_Init();
	SSEG_Void_Init();
	uint8 count = 9,color = 1;
	///LEDS  PC2 >> LED0 // PC7 >> LED1 // PD3 >> LED2
	DIO_Set_Pin_Output(PORTC,2,Low);DIO_Set_Pin_Output(PORTC,7,Low);DIO_Set_Pin_Output(PORTD,3,High);
	while(1){
		if(count==0){
			SSEG_Void_Diaplay(1,count);
			_delay_ms(1000);
			count = 9;
			switch(color){
				case 1:color++;DIO_Set_Pin_Output(PORTC,2,High);DIO_Set_Pin_Output(PORTC,7,Low);DIO_Set_Pin_Output(PORTD,3,Low);break;
				case 2:color++;DIO_Set_Pin_Output(PORTC,2,Low);DIO_Set_Pin_Output(PORTC,7,High);DIO_Set_Pin_Output(PORTD,3,Low);break;
				case 3:color++;DIO_Set_Pin_Output(PORTC,2,Low);DIO_Set_Pin_Output(PORTC,7,Low);DIO_Set_Pin_Output(PORTD,3,High);break;
				case 4:color = 1;break;
				default:break;
			}
		}
		while(count>0){
			SSEG_Void_Diaplay(1,count);
			_delay_ms(1000);
			count--;
		}
	}
}

void App_003_Seven_Segment_Keypad_Numbers()
{
	SSEG_Void_Init();
	SSEG_Void_Diaplay(0,0);
	SSEG_Void_Diaplay(1,0);
	uint8 x ='\0';
	while(1){
		x = KEYPAD_Get_Pressed_Key();
		_delay_ms(50);
		if((x > 47) && (x < 58)){
			SSEG_Void_Diaplay(1, (x - 48));
		}
	}
}

void App_002_Seven_Segment_3Buttons()
{
	///App_002: 7seg counter 3 buttons, up down and reset to 0
	SSEG_Void_Init();
	Button_Init();
	uint8 button0_State =0;
	uint8 button1_State =0;
	uint8 button2_State =0;
	uint8 count=0;
	SSEG_Void_Diaplay(1,0);
	while(1)
	{
		SSEG_Void_Diaplay(1,count);
		Check_Button0_Clicked(& button0_State);
		Check_Button1_Clicked(& button1_State);
		Check_Button2_Clicked(& button2_State);
		if((button0_State == 10)){///Increase Button Pressed
			if(count<=9)count++;
			button0_State = 0;
		}
		if((button1_State == 10)){ ///Decrease Button Pressed
			if(count > 0) count--;
			button1_State = 0;
		}
		if((button2_State == 10)){///Reset Button Pressed
			if(count > 0) count = 0;
			button2_State = 0;
		}
	}
}

void App_001_Seven_Segment_Timer()
{
	///App_001: 7seg COUNTER from 0 to 9 count each second
	int i = 0;
	SSEG_Void_Init();
	while(1)
	{
		if(i<=9)
		{
			SSEG_Void_Diaplay(1,i);
			_delay_ms(1000);
			i++;
		}
		else if (i>9)
		{
			i=0;
		}
	}
}
