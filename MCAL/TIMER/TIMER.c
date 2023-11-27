/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 19-11-2023            */
/*          Version: 1.0                */
/*          Module: Timers              */
/****************************************/
#include "../DIO/STD_Types.h"
#include "../DIO/Bit_Math.h"
#include "Timer_Init.h"
#include "Timer_Private.h"
#include "Timer_Config.h"
// TCNT Fires at 256 Ticks
// Tick_Time = Prescaler/Frequency 
// OverFlow_Time = Tick_Time * (2^(Resolution))
// OverFlow_Time = Tick_Time * (2^(256?1024?...))
// Prescaler
// AT TCNT Fire overflow_Flag OVF
// SFIOR_Reg : Bit 0 – PSR10: Prescaler Reset T1 and T0

/***********************************************************************************/
/********************************    Timer 1    ************************************/
/***********************************************************************************/
//    These registers control the mode of operation, waveform generation, 
//		and Prescaler settings for Timer/Counter1
//	TCCR1A – Timer1 Control Register A
//		Bit 7:6 – COM1A1:0: Compare Output Mode for Compare unit A
//		Bit 5:4 – COM1B1:0: Compare Output Mode for Compare unit B
//		Bit 3 – FOC1A: Force Output Compare for Compare unit A
//		Bit 2 – FOC1B: Force Output Compare for Compare unit B
//	TCCR1B – Timer1 Control Register B
//		Bit 7 – ICNC1: Input Capture Noise Canceler 
//			Set(TCCR1B_Reg,7);Clear(TCCR1B_Reg,7);
//		Bit 6 – ICES1: Input Capture Edge Select    
//			Set(TCCR1B_Reg,6);Clear(TCCR1B_Reg,6);
//		Bit 5 – Reserved Bit						
//		Bit 2:0 – CS12:0: Clock Select /// PRESCALING
//
//	ICR1H ICR1L TO READ ICR1
//
//	TIFR – Timer Interrupt Flag Register
//		Bit 5 – ICF1:  Timer1, Input Capture Flag
//		Bit 4 – OCF1A: Timer1, Output Compare A Match Flag
//		Bit 3 – OCF1B: Timer1, Output Compare B Match Flag
//		Bit 2 – TOV1:  Timer1, Overflow Flag

void Timer1_Init(){
	/***********************   Timer1 ALL 15 Modes   **************************/
	#if  (Timer1_Mode == Timer1_Normal)						//0		ICR1-YES
		Clear(TCCR1B_Reg,4);Clear(TCCR1B_Reg,3);Clear(TCCR1A_Reg,1);Clear(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_PWM_Phase_Correct_8bit)	//1		
		Clear(TCCR1B_Reg,4);Clear(TCCR1B_Reg,3);Clear(TCCR1A_Reg,1);Set(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_PWM_Phase_Correct_9bit)	//2
		Clear(TCCR1B_Reg,4);Clear(TCCR1B_Reg,3);Set(TCCR1A_Reg,1);Clear(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_PWM_Phase_Correct_10bit)	//3
		Clear(TCCR1B_Reg,4);Clear(TCCR1B_Reg,3);Set(TCCR1A_Reg,1);Set(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_CTC_OCR1A)					//4
		Clear(TCCR1B_Reg,4);Set(TCCR1B_Reg,3);Clear(TCCR1A_Reg,1);Clear(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_Fast_PWM_8bit)				//5
		Clear(TCCR1B_Reg,4);Set(TCCR1B_Reg,3);Clear(TCCR1A_Reg,1);Set(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_Fast_PWM_9bit)				//6
		Clear(TCCR1B_Reg,4);Set(TCCR1B_Reg,3);Set(TCCR1A_Reg,1);Clear(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_Fast_PWM_10bit)			//7
		Clear(TCCR1B_Reg,4);Set(TCCR1B_Reg,3);Set(TCCR1A_Reg,1);Set(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_PWM_Phase_Frequency_Correct_ICR1)			//8
		Set(TCCR1B_Reg,4);Clear(TCCR1B_Reg,3);Clear(TCCR1A_Reg,1);Clear(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_PWM_Phase_Frequency_Correct_OCR1A)			//9
		Set(TCCR1B_Reg,4);Clear(TCCR1B_Reg,3);Clear(TCCR1A_Reg,1);Set(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_PWM_Phase_Correct_ICR1)					//10
		Set(TCCR1B_Reg,4);Clear(TCCR1B_Reg,3);Set(TCCR1A_Reg,1);Clear(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_PWM_Phase_Correct_OCR1A)					//11
		Set(TCCR1B_Reg,4);Clear(TCCR1B_Reg,3);Set(TCCR1A_Reg,1);Set(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_CTC_ICR1)									//12
		Set(TCCR1B_Reg,4);Set(TCCR1B_Reg,3);Clear(TCCR1A_Reg,1);Clear(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_FastPWM_ICR1)								//14
		Set(TCCR1B_Reg,4);Set(TCCR1B_Reg,3);Set(TCCR1A_Reg,1);Clear(TCCR1A_Reg,0);
		
	#elif (Timer1_Mode == Timer1_FastPWM_OCR1A)								//15	ICR1-NO
		Set(TCCR1B_Reg,4);Set(TCCR1B_Reg,3);Set(TCCR1A_Reg,1);Set(TCCR1A_Reg,0);
		
	#endif
	/***********************   Timer1 PreScaler   **************************/
	#if  (Timer0_PreScaler == Timer_Pre_STOP)
		Clear(TCCR1B_Reg,2);	Clear(TCCR1B_Reg,1);	Clear(TCCR1B_Reg,0);
	#elif (Timer0_PreScaler == Timer_Pre_1)
		Clear(TCCR1B_Reg,2);	Clear(TCCR1B_Reg,1);	Set(TCCR1B_Reg,0);
	#elif (Timer0_PreScaler == Timer_Pre_8)
		Clear(TCCR1B_Reg,2);	Set(TCCR1B_Reg,1);		Clear(TCCR1B_Reg,0);
	#elif (Timer0_PreScaler == Timer_Pre_64)
		Clear(TCCR1B_Reg,2);	Set(TCCR1B_Reg,1);		Set(TCCR1B_Reg,0);
	#elif (Timer0_PreScaler == Timer_Pre_256)
		Set(TCCR1B_Reg,2);		Clear(TCCR1B_Reg,1);	Clear(TCCR1B_Reg,0);
	#elif (Timer0_PreScaler == Timer_Pre_1024)
		Set(TCCR1B_Reg,2);		Clear(TCCR1B_Reg,1);	Set(TCCR1B_Reg,0);
	#elif (Timer0_PreScaler == Timer_Pre_External_T1_Falling)
		Set(TCCR1B_Reg,2);		Set(TCCR1B_Reg,1);		Clear(TCCR1B_Reg,0);
	#elif (Timer0_PreScaler == Timer_Pre_External_T1_Raising)
		Set(TCCR1B_Reg,2);		Set(TCCR1B_Reg,1);		Set(TCCR1B_Reg,0);
	#endif
	/***********************   Timer1 OCR1A Pin   **************************/
	#if  (Timer0_OC0_Pin == Timer_COM_Pin_OFF)
	Clear(TCCR0_Reg,5);Clear(TCCR0_Reg,4);
	#elif (Timer0_OC0_Pin == Timer_COM_Pin_TOGGLE)
	Clear(TCCR0_Reg,5);	 Set(TCCR0_Reg,4);
	#elif (Timer0_OC0_Pin == Timer_COM_Pin_CLEAR)
	Set(TCCR0_Reg,5);Clear(TCCR0_Reg,4);
	#elif (Timer0_OC0_Pin == Timer_COM_Pin_SET)
	Set(TCCR0_Reg,5);  Set(TCCR0_Reg,4);
	/***********************   Timer1 OCR1B Pin   **************************/







	//Clear the reserved pin to ensure compatibility :
	Clear(TCCR1B_Reg,5);
	#endif
}

//	TIMSK – Timer Interrupt Mask Register
//		Bit 5 – TICIE1: Timer1, PIE-Input Capture Interrupt Enable
void Timer1_Enable_Input_Capture_Interrupt()	{	  Set(TIMSK_Reg,5);	}
void Timer1_Disable_Input_Capture_Interrupt()	{	Clear(TIMSK_Reg,5);	}
//		Bit 4 – OCIE1A: Timer1, PIE-Output Compare A Match Interrupt Enable
void Timer1_Enable_Compare_A_Interrupt()		{	  Set(TIMSK_Reg,4);	}
void Timer1_Disable_Compare_A_Interrupt()		{	Clear(TIMSK_Reg,4);	}
//		Bit 3 – OCIE1B: Timer1, PIE-Output Compare B Match Interrupt Enable
void Timer1_Enable_Compare_B_Interrupt()		{	  Set(TIMSK_Reg,3);	}
void Timer1_Disable_Compare_B_Interrupt()		{	Clear(TIMSK_Reg,3);	}
//		Bit 2 – TOIE1:  Timer1, PIE-Overflow Interrupt Enable
void Timer1_Enable_Overflow_Interrupt()			{	  Set(TIMSK_Reg,2);	}
void Timer1_Disable_Overflow_Interrupt()		{	Clear(TIMSK_Reg,2);	}

//	ICR1H and ICR1L – Input Capture Register 1
void Timer1_Set_ICR1_Reg(uint16 value){
	//	ICR1H and ICR1L – Input Capture Register 1
	ICR1H_Reg= (uint8)(value >> 8);
	ICR1L_Reg= (uint8)(value & 0b0000000011111111);
}
void Timer1_Set_TCNT1_Reg(uint16 value){
//	TCNT1H and TCNT1L – Timer1
//	This 16-bit register holds the current count value of Timer/Counter1.
	TCNT1H_Reg= (uint8)(value >> 8);
	TCNT1L_Reg= (uint8)(value & 0b0000000011111111);
}
void Timer1_Set_OCR1A_Reg(uint16 value){
	//	OCR1AH and OCR1AL – Output Compare Register 1 A
	OCR1AH_Reg =  (uint8)(value >> 8);
	OCR1AL_Reg =  (uint8)(value & 0b0000000011111111);
}
void Timer1_Set_OCR1B_Reg(uint16 value){
	//	OCR1BH and OCR1BL – Output Compare Register 1 B
	OCR1BH_Reg =  (uint8)(value >> 8);
	OCR1BL_Reg =  (uint8)(value & 0b0000000011111111);
}

/***********************************************************************************/
/******************************    END Timer 1    **********************************/
/***********************************************************************************/


/***********************************************************************************/
/********************************    Timer 0    ************************************/
/***********************************************************************************/

void Timer0_Init(){
	/***********************   Timer0 Mode   **************************/
	#if  (Timer0_Mode == Timer_M_Normal)
		Clear(TCCR0_Reg,6);		Clear(TCCR0_Reg,3);
	#elif (Timer0_Mode == Timer_M_CTC)
		Clear(TCCR0_Reg,6);		  Set(TCCR0_Reg,3);
	#elif (Timer0_Mode == Timer_M_FastPWM)
		Set(TCCR0_Reg,6);		  Set(TCCR0_Reg,3);
	#elif (Timer0_Mode == Timer_M_PhasePWM)
		Set(TCCR0_Reg,6);		Clear(TCCR0_Reg,3);
	#endif
	/***********************   Timer0 PreScaler   **************************/
	#if  (Timer0_PreScaler == Timer_Pre_1)
	Clear(TCCR0_Reg,2);Clear(TCCR0_Reg,1);  Set(TCCR0_Reg,0);
	#elif (Timer0_PreScaler == Timer_Pre_8)
	Clear(TCCR0_Reg,2);  Set(TCCR0_Reg,1);Clear(TCCR0_Reg,0);
	#elif (Timer0_PreScaler == Timer_Pre_64)
	Clear(TCCR0_Reg,2);  Set(TCCR0_Reg,1);  Set(TCCR0_Reg,0);
	#elif (Timer0_PreScaler == Timer_Pre_256)
	Set(TCCR0_Reg,2);Clear(TCCR0_Reg,1);Clear(TCCR0_Reg,0);
	#elif (Timer0_PreScaler == Timer_Pre_1024)
	Set(TCCR0_Reg,2);Clear(TCCR0_Reg,1);  Set(TCCR0_Reg,0);
	#endif
	/***********************   Timer0 OCR0 Pin   **************************/
	#if  (Timer0_OC0_Pin == Timer_COM_Pin_OFF)
	Clear(TCCR0_Reg,5);Clear(TCCR0_Reg,4);
	#elif (Timer0_OC0_Pin == Timer_COM_Pin_TOGGLE)
	Clear(TCCR0_Reg,5);	 Set(TCCR0_Reg,4);
	#elif (Timer0_OC0_Pin == Timer_COM_Pin_CLEAR)
	Set(TCCR0_Reg,5);Clear(TCCR0_Reg,4);
	#elif (Timer0_OC0_Pin == Timer_COM_Pin_SET)
	Set(TCCR0_Reg,5);  Set(TCCR0_Reg,4);
	#endif
}

void Timer0_Set_TCNT0_Reg(uint8 value)	{	TCNT0_Reg= value;	}//Timer Register
void Timer0_Set_OCR0_Reg(uint8 value)	{	OCR0_Reg = value;	}//Output Compare Register
	
//	TIMSK – Timer Interrupt Mask Register
//		Bit 1 – OCIE0: Timer0 PIE-Output Compare Match Interrupt Enable
//		Bit 0 – TOIE0: Timer0 PIE-Overflow Interrupt Enable
void Timer0_Enable_Overflow_Interrupt()		{	Set(TIMSK_Reg,0);	}
void Timer0_Disable_Overflow_Interrupt()	{	Clear(TIMSK_Reg,0);	}
void Timer0_Enable_CTC_Interrupt()			{	Set(TIMSK_Reg,1);	}
void Timer0_Disable_CTC_Interrupt()			{	Clear(TIMSK_Reg,1);	}
/***********************************************************************************/
/******************************    END Timer 0    **********************************/
/***********************************************************************************/


/***********************************************************************************/
/********************************    Timer 2    ************************************/
/***********************************************************************************/

// ONLY FOR TIMER 2 >>> //ASSR – Asynchronous Status Register EXIST
//		Bit 3 – AS2: Asynchronous Timer2
//		Bit 2 – TCN2UB: Timer2 Update Busy
//		Bit 1 – OCR2UB: Output Compare Register2 Update Busy
//		Bit 0 – TCR2UB: Timer Control Register2 Update Busy
// TIMER2 Cant be used as counter
void Timer2_Init(){
	/***********************   Timer2 Mode   **************************/
	#if   (Timer2_Mode == Timer_M_Normal)
		Clear(TCCR2_Reg,6);		Clear(TCCR2_Reg,3);
	#elif (Timer2_Mode == Timer_M_CTC)
		Clear(TCCR2_Reg,6);		  Set(TCCR2_Reg,3);
	#elif (Timer2_Mode == Timer_M_FastPWM)
		Set(TCCR2_Reg,6);		  Set(TCCR2_Reg,3);
	#elif (Timer2_Mode == Timer_M_PhasePWM)
		Set(TCCR2_Reg,6);		Clear(TCCR2_Reg,3);
	#endif
	/***********************   Timer0 PreScaler   **************************/
	#if   (Timer2_PreScaler == Timer_Pre_1)
		Clear(TCCR2_Reg,2);Clear(TCCR2_Reg,1);  Set(TCCR2_Reg,0);
	#elif (Timer2_PreScaler == Timer_Pre_8)
		Clear(TCCR2_Reg,2);  Set(TCCR2_Reg,1);Clear(TCCR2_Reg,0);
	#elif (Timer2_PreScaler == Timer_Pre_64)
		Clear(TCCR2_Reg,2);  Set(TCCR2_Reg,1);  Set(TCCR2_Reg,0);
	#elif (Timer2_PreScaler == Timer_Pre_256)
		Set(TCCR2_Reg,2);Clear(TCCR2_Reg,1);Clear(TCCR2_Reg,0);
	#elif (Timer2_PreScaler == Timer_Pre_1024)
		Set(TCCR2_Reg,2);Clear(TCCR2_Reg,1);  Set(TCCR2_Reg,0);
	#endif
	/***********************   Timer0 OCR0 Pin   **************************/
	#if   (Timer2_OC2_Pin == Timer_COM_Pin_OFF)
		Clear(TCCR2_Reg,5);Clear(TCCR2_Reg,4);
	#elif (Timer2_OC2_Pin == Timer_COM_Pin_TOGGLE)
		Clear(TCCR2_Reg,5);	 Set(TCCR2_Reg,4);
	#elif (Timer2_OC2_Pin == Timer_COM_Pin_CLEAR)
		Set(TCCR2_Reg,5);Clear(TCCR2_Reg,4);
	#elif (Timer2_OC2_Pin == Timer_COM_Pin_SET)
		Set(TCCR2_Reg,5);  Set(TCCR2_Reg,4);
	#endif
}

void Timer2_Set_TCNT2_Reg(uint8 value)	{	TCNT2_Reg= value;	}//Timer Register
void Timer2_Set_OCR2_Reg(uint8 value)	{	OCR2_Reg = value;	}//Output Compare Register
	
//	TIMSK – Timer Interrupt Mask Register
//		Bit 7 – OCIE2: Timer2 PIE-Output Compare Match Interrupt Enable.
//		Bit 6 – TOIE2: Timer2 PIE-Overflow Interrupt Enable
void Timer2_Enable_Overflow_Interrupt()		{	  Set(TIMSK_Reg,6);	}
void Timer2_Disable_Overflow_Interrupt()	{	Clear(TIMSK_Reg,6);	}
void Timer2_Enable_CTC_Interrupt()			{	  Set(TIMSK_Reg,7);	}
void Timer2_Disable_CTC_Interrupt()			{	Clear(TIMSK_Reg,7);	}
/***********************************************************************************/
/******************************    END Timer 2    **********************************/
/***********************************************************************************/