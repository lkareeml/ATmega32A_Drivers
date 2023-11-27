/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 17-11-2023            */
/*          Version: 1.0                */
/*          Module: Interrupt           */
/****************************************/
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

void GIE_Enable();
void GIE_Disable();

void EXTI0_Init();
void EXTI0_Set_Direction_Input();
void EXTI0_Set_Internal_Pull_Up();
void EXTI0_Enable();
void EXTI0_Disable();

void EXTI1_Init();
void EXTI1_Enable();
void EXTI1_Disable();

void EXTI2_Init();
void EXTI2_Enable();
void EXTI2_Disable();

#endif /* INTERRUPT_INIT_H_ */