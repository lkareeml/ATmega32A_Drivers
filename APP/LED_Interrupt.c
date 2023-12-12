void LED_2_Toggle(uint8 *flag_2){
	if(*flag_2 == 0){LED_2_On();*flag_2 = 1;}
	else if(*flag_2 == 1){LED_2_Off();*flag_2 = 0;}
}
void LED_1_Toggle(uint8 *flag_1){
	if(*flag_1 == 0){LED_1_On();*flag_1 = 1;}
	else if(*flag_1 == 1){LED_1_Off();*flag_1 = 0;}
}

void LED_0_Toggle(uint8 *flag_0){
	if(*flag_0 == 0){LED_0_On();*flag_0 = 1;}
	else if(*flag_0 == 1){LED_0_Off();*flag_0 = 0;}
}

void App_040_TIMER_LED() {
	LED0_Init();LED1_Init();LED2_Init();
	LED_0_Off();LED_1_Off();LED_2_Off();
	LCD_Init();
	Timer0_Init();
	//Timer0_Set_TCNT0_Reg(247);
	Timer0_Enable_Overflow_Interrupt();
	GIE_Enable();
	while (1);
}
void App_040_ISR() { //TIMER0_OVF_vect
	static uint16 counter = 0;
	static uint8 flag_0 = 0;
	static uint8 flag_1 = 0;
	static uint8 flag_2 = 0;
	counter++;
	//1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 
	//  X   X   X   X   X   X   X   X   X
	//    X     X     X     X     X     X
	//X X X X X X X X X X X X X X X X X X
	if (counter >= 50 && counter%50 == 0){//1 sec
		LCD_Send_Clear_Screen();
		LED_0_Toggle(&flag_0);
		LCD_Send_String("LED_0 Process");
	}
	if(counter >= 100 && counter%100 == 0){//2 sec
		LCD_Send_Clear_Screen();
		LED_1_Toggle(&flag_1);
		LCD_Send_String("LED_1 Process");
	}
	if (counter>=150 && counter%150 == 0){
		LCD_Send_Clear_Screen();
		LED_2_Toggle(&flag_2);counter = 0;
		LCD_Send_String("LED_2 Process");
	}
}
