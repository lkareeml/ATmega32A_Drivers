/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 17-11-2023            */
/*          Version: 1.0                */
/*          Module: Interrupt           */
/****************************************/
#ifndef INTERRUPT_CONFIG_H_
#define INTERRUPT_CONFIG_H_

//EXTI0 Peripheral Interrupt
/// Options : EXTI0_Raising_Edge , EXTI0_Falling_Edge , EXTI0_Any_Change, EXTI0_Low_Level
#define EXTI0_ISC EXTI0_Raising_Edge

//EXTI1 Peripheral Interrupt
/// Options : EXTI1_Raising_Edge , EXTI1_Falling_Edge , EXTI1_Any_Change, EXTI1_Low_Level
#define EXTI1_ISC EXTI1_Raising_Edge

//EXTI02 Peripheral Interrupt
/// Options : EXTI2_Raising_Edge , EXTI2_Falling_Edge
#define EXTI2_ISC EXTI2_Raising_Edge

#endif /* INTERRUPT_CONFIG_H_ */