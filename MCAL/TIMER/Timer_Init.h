/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 19-11-2023            */
/*          Version: 1.0                */
/*          Module: Timers              */
/****************************************/

#ifndef TIMER_INIT_H_
#define TIMER_INIT_H_

/***********************************************************************************/
void Timer0_Init();
void Timer0_Set_TCNT0_Reg(uint8 value);
void Timer0_Set_OCR0_Reg(uint8 value);
void Timer0_Enable_Overflow_Interrupt();
void Timer0_Disable_Overflow_Interrupt();
void Timer0_Enable_CTC_Interrupt();
void Timer0_Disable_CTC_Interrupt();
/***********************************************************************************/
void Timer2_Init();
void Timer2_Enable_Overflow_Interrupt();
void Timer2_Disable_Overflow_Interrupt();
void Timer2_Enable_CTC_Interrupt();
void Timer2_Disable_CTC_Interrupt();
void Timer2_Set_TCNT2_Reg(uint8 value);
void Timer2_Set_OCR2_Reg(uint8 value);
/***********************************************************************************/
void Timer1_Init();

void Timer1_Set_ICR1_Reg(uint16 value);
void Timer1_Set_TCNT1_Reg(uint16 value);
void Timer1_Set_OCR1A_Reg(uint16 value);
void Timer1_Set_OCR1B_Reg(uint16 value);

void Timer1_Input_Capture_Interrupt_Enable();
void Timer1_Input_Capture_Interrupt_Disable();
void Timer1_Compare_A_Interrupt_Enable();
void Timer1_Compare_A_Interrupt_Disable();
void Timer1_Compare_B_Interrupt_Enable();
void Timer1_Compare_B_Interrupt_Disable();
void Timer1_Overflow_Interrupt_Enable();
void Timer1_Overflow_Interrupt_Disable();

#endif /* TIMER_INIT_H_ */