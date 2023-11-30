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

#include "../HAL/Seven_Segment/Seven_Segment.h"
#include "../HAL/LCD16/LCD_Driver.h"
#include "../HAL/KEYPAD/KEYPAD.h"
#include "../HAL/Buttons/Buttons.h"
#include "../HAL/LEDS/LEDS.h"
#include "../HAL/SERVO/SERVO.h"

#include "ALLAPPS.h"
#include "Helper.h"

extern uint8 button0_State;
extern uint8 button1_State;
extern uint8 button2_State;
void reverse(char str[], int length);
char * citoa(int num, char* str, int base);









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
		for(int i =0;i<50;i++)Servo_0_Degree_Delay();
		for(int i =0;i<50;i++)Servo_90_Degree_Delay();
		for(int i =0;i<50;i++)Servo_180_Degree_Delay();
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
void TASK19_TIMER_FASTPWM_LED(){
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
/***********************************************************/
void TASK18_TIMER_CTC_ADC_POTENTIOMETER(){
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
void TASK17_TIMER_CTC_Freq(){
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
void TASK17_ISR(){
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
void TASK16_TIMER_SQRWAVE_NORMAL(){
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
void TASK16_ISR(){
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
void TASK15_TIMER_LED(){
    LED1_Init();
    Timer0_Init();
    Timer0_Set_TCNT0_Reg(247);
    Timer0_Enable_Overflow_Interrupt();
    GIE_Enable();
	while(1);
}
void TASK15_ISR(){//TIMER0_OVF_vect
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
/********************* GOOD **************************/
void TASK10_ADC_Manual_Interrupt(){    // ADC with interrupt not polling
    ADC_Init();
    LCD_Init();
    ADC_Manual_Interrupt();
    GIE_Enable();
    while (1);
}
void TASK10_ISR_ADC(){
    uint8 digital = 0;
    uint8 old_digital=0;
    float analog = 0;
    digital = ADC_Return_Result();
    int8 string[20];
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
void TASK11_ADC_Timer_No_Interrupt(){    //ADC Triggered By Timer0 Polling Version
    LCD_Init();
    Timer0_Init();
    ADC_Timer_No_Interrupt();// MAKE SURE TIMER ON NORMAL MODE!!
    while (1)
    {
        uint8 digital = ADC_Timer_Polling_Result();
        uint8 old_digital=0;
        float analog = digital * (50.0/256.0);    //0--255 >>> 0 -- 50 Temp
        int8 string[20];
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
void TASK12_ADC_Timer_With_Interrupt()
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
void TASK12_ISR_ADC_Timer(){
        uint8 digital = ADC_Return_Result();// Returns ADCH 
        static uint8 old_digital = 0;
        float analog = digital * (50.0/256.0);    //0--255 >>> 0 -- 50 Temp
        int8 string[20];
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
                TASK12_ISR_ADC_Timer();
        }
        */
}
/***********************************************************/
void TASK13_KEYPAD_LCD_INTERRUPT()
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
void TASK13_ISR()
{
    KEYPAD_Init();
    uint8 x='\0';
    x= KEYPAD_Get_Pressed_Key();
    LCD_Send_Char(x);
}
void TASK14_LED_BUTTON_INTERRUPT()
{
    LED0_Init();
    EXTI0_Set_Direction_Input();
    EXTI0_Set_Internal_Pull_Up();
    LED_0_Off();
    EXTI0_Init();
    EXTI0_Enable();
    GIE_Enable();
    while(1);
}
void TASK14_ISR()
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
void TASK9_ADC_Potentiometer_Temperature_LCD()
{
    ADC_Init();
    LCD_Init();
    LED0_Init();
    LED1_Init();
    LED2_Init();
    uint8 digital = 0;
    uint8 old_digital=0;
    float analog = 0;
    int8 string[20];
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
void TASK8_ADC_Potentiometer()
{
    ADC_Init();
    LCD_Init();
    Button_Init();
    uint8 digital = 0;
    uint8 old_digital=0;
    float analog = 0;
    int8 string[20];
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
/***********************************************************/
