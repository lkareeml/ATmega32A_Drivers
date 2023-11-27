/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 10-11-2023            */
/*          Version: 1.0                */
/*          Module: AMIT Kit Buttons    */
/****************************************/

#ifndef BUTTON_H_
#define BUTTON_H_

extern uint8 button0_State;
extern uint8 button1_State;
extern uint8 button2_State;
void Button_Init();
void Check_Button0_Clicked(uint8 * button0_State);
void Check_Button1_Clicked(uint8 * button1_State);
void Check_Button2_Clicked(uint8 * button02_State);

#endif