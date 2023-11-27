/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 19-11-2023            */
/*          Version: 1.0                */
/*          Module: Timers              */
/****************************************/

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_


typedef enum{
	Normal_Mode,CTC_Mode,FastPWM_Mode,PhasePWM
}Timer_Mode;

//	Timer_M_Normal		Timer_M_CTC 
//	Timer_M_FastPWM		Timer_M_PhasePWM
#define Timer0_Mode			Timer_M_Normal
#define Timer2_Mode			Timer_M_Normal

//	Timer_Pre_1 Timer_Pre_8 Timer_Pre_1024 Timer_Pre_256 Timer_Pre_64 
#define Timer0_PreScaler	Timer_Pre_1024
#define Timer2_PreScaler	Timer_Pre_1024

//	Timer_COM_Pin_OFF		Timer_COM_Pin_CLEAR
//	Timer_COM_Pin_TOGGLE	Timer_COM_Pin_SET 
#define Timer0_OC0_Pin		Timer_COM_Pin_OFF
#define Timer2_OC2_Pin		Timer_COM_Pin_OFF



//WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).
//	Timer1_Normal								0
//	Timer1_PWM_Phase_Correct_8bit				1
//	Timer1_PWM_Phase_Correct_9bit				2
//	Timer1_PWM_Phase_Correct_10bit				3
//	Timer1_CTC_OCR1A							4
//	Timer1_Fast_PWM_8bit						5
//	Timer1_Fast_PWM_9bit						6
//	Timer1_Fast_PWM_10bit						7
//	Timer1_PWM_Phase_Frequency_Correct_ICR1		8
//	Timer1_PWM_Phase_Frequency_Correct_OCR1A	9
//	Timer1_PWM_Phase_Correct_ICR1				10
//	Timer1_PWM_Phase_Correct_OCR1A				11
//	Timer1_CTC_ICR1								12
//	Timer1_FastPWM_ICR1							14
//	Timer1_FastPWM_OCR1A						15 /// SEND PWM TO OCR1A

#define Timer1_Mode				Timer1_Normal
#define Timer1_PreScaler		Timer_Pre_1024
#define Timer1_OC1_Pin			Timer_COM_Pin_SET

#endif /* TIMER_CONFIG_H_ */