/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 19-11-2023            */
/*          Version: 1.0                */
/*          Module: Timers              */
/****************************************/

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_
/*************************************************************/
#define Timer_M_Normal      0
#define Timer_M_CTC         1
#define Timer_M_FastPWM     2
#define Timer_M_PhasePWM    3

#define	Timer1_Normal								0
#define	Timer1_PWM_Phase_Correct_8bit				1
#define	Timer1_PWM_Phase_Correct_9bit				2
#define	Timer1_PWM_Phase_Correct_10bit				3
#define	Timer1_CTC_OCR1A							4
#define	Timer1_Fast_PWM_8bit						5
#define	Timer1_Fast_PWM_9bit						6
#define	Timer1_Fast_PWM_10bit						7
#define	Timer1_PWM_Phase_Frequency_Correct_ICR1		8
#define	Timer1_PWM_Phase_Frequency_Correct_OCR1A	9
#define	Timer1_PWM_Phase_Correct_ICR1				10
#define	Timer1_PWM_Phase_Correct_OCR1A				11
#define	Timer1_CTC_ICR1								12
#define	Timer1_FastPWM_ICR1							14
#define	Timer1_FastPWM_OCR1A						15 /// SEND PWM TO OCR1A
/*************************************************************/
#define Timer_Pre_1         1
#define Timer_Pre_8         2
#define Timer_Pre_64        3
#define Timer_Pre_256       4
#define Timer_Pre_1024      5

#define Timer_Pre_STOP		0
#define Timer_Pre_External_T1_Falling 6
#define Timer_Pre_External_T1_Raising 7
/*************************************************************/
#define Timer_COM_Pin_OFF       0
#define Timer_COM_Pin_TOGGLE    1
#define Timer_COM_Pin_SET       2	//INVERT
#define Timer_COM_Pin_CLEAR     3	//NON INVERT
/*************************************************************/
#define IC_Noise_Canceler_OFF		0
#define IC_Noise_Canceler_ON		1

/*************************************************************/
#define TIMSK_Reg       (*(volatile uint8*)0x59)
#define TIFR_Reg        (*(volatile uint8*)0x58)
/*************************************************************/
#define TCCR0_Reg    (*(volatile uint8*)0x53)
#define TCNT0_Reg    (*(volatile uint8*)0x52)
#define OCR0_Reg     (*(volatile uint8*)0x5C)
#define TCCR2_Reg    (*(volatile uint8*)0x45)
#define TCNT2_Reg    (*(volatile uint8*)0x44)
#define OCR2_Reg     (*(volatile uint8*)0x43)
/*************************************************************/
/*******************    Timer 1 16-Bit  **********************/
/*************************************************************/
#define TCNT1H_Reg      (*(volatile uint8*)0x4D) // High
#define TCNT1L_Reg      (*(volatile uint8*)0x4C) // LOW
#define TCCR1A_Reg      (*(volatile uint8*)0x4F) // TIMER1 ICP FREQ Normal Mode
#define TCCR1B_Reg      (*(volatile uint8*)0x4E) // TIMER1 ICP FREQ Normal Mode
#define OCR1AH_Reg      (*(volatile uint8*)0x4B) // TIMER1
#define OCR1AL_Reg      (*(volatile uint8*)0x4A) // TIMER1
#define OCR1BH_Reg      (*(volatile uint8*)0x49) // TIMER1
#define OCR1BL_Reg      (*(volatile uint8*)0x48) // TIMER1
#define ICR1H_Reg       (*(volatile uint8*)0x47) // TIMER1
#define ICR1L_Reg       (*(volatile uint8*)0x46) // TIMER1

/*************************************************************/
#endif /* TIMER_PRIVATE_H_ */