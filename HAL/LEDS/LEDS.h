/****************************************/
/*          Author: Kareem Atef		    */
/*          Date: 06-12-2023		    */
/*          Version: 2.0				*/
/*          Module: 3-LEDs              */
/****************************************/
#ifndef LEDS_H_
#define LEDS_H_
void LED_Init_All();
void LED0_Init();
void LED1_Init();
void LED2_Init();
void LED3_Init();
void LED4_Init();
void Lamp_Dimmer_Init();

void LED_0_On();
void LED_1_On();
void LED_2_On();
void LED_3_On();
void LED_4_On();
void Lamp_Dimmer_On();


void LED_0_Off();
void LED_1_Off();
void LED_2_Off();
void LED_3_Off();
void LED_4_Off();
void Lamp_Dimmer_Off();


#endif /* LEDS_H_ */