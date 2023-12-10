/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 19-11-2023            */
/*          Version: 1.0                */
/*          Module: Timers              */
/****************************************/

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_
//    Timer_M_Normal        Timer_M_CTC 
//    Timer_M_FastPWM        Timer_M_PhasePWM
#define Timer0_Mode            Timer_M_Normal
#define Timer2_Mode            Timer_M_CTC

//    Timer_Pre_1 Timer_Pre_8 Timer_Pre_1024 Timer_Pre_256 Timer_Pre_64 
#define Timer0_PreScaler    Timer_Pre_1024
#define Timer2_PreScaler    Timer_Pre_1024

//    Timer_COM_Pin_OFF        Timer_COM_Pin_CLEAR
//    Timer_COM_Pin_TOGGLE    Timer_COM_Pin_SET 
#define Timer0_OC0_Pin        Timer_COM_Pin_OFF
#define Timer2_OC2_Pin        Timer_COM_Pin_OFF
// OC2 == PD7 // OC1B == PD4 // OC1A == PD5 // OC0 == PB3 //
/********************************    Timer 1    ************************************/
#define Timer1_Mode                    Timer1_Normal
#define Timer1_PreScaler               Timer_Pre_1024
#define Timer1_IC_Noise_Canceller      Disabled
#define Timer1_IC_Edge_Select          Timer1_IC_Falling_Edge
#define Compare_Output_Mode_A          Normal_Disconnect
#define Compare_Output_Mode_B          Normal_Disconnect
/*********************************************************/
#endif /* TIMER_CONFIG_H_ */