void App_035_SEND_USERNAME_PASSWORD_UART_BLUETOOTH_LOGIN_SYS()
{//Sys lock after 2 trials
	BUZZER_Init();
	UART_Init();
	uint8 count = 0; // MAX COUNT IS 3 THEN BUZZER AND LOCK 
	uint8 user[6] = "ADMIN";
	uint8 password[5] = "1234";
	uint8 RecieveUsername[11];
	uint8 RecievePassword[11];
	while(1){
		UART_Send_String_Polling8("Enter Username:");
		UART_Send_Byte_Polling8('\n');
		UART_Recieve_String8(RecieveUsername);
		uint8 Userchecker = memcmp(RecieveUsername,user,5);
		UART_Send_String_Polling8("Enter Password:");
		UART_Send_Byte_Polling8('\n');
		UART_Recieve_String8(RecievePassword);
		uint8 Passwordchecker = memcmp(RecievePassword,password,4);
		
		//Username is correct NEXT
		if((Passwordchecker == 0) && (Userchecker == 0)){
			UART_Send_String_Polling8("Success!");
			while(1);
		}
		else{
			if(count == 3)
			{
				UART_Send_String_Polling8("System LOCKED!");
				BUZZER_On();
				while(1);
			}
			else
			{
				UART_Send_String_Polling8("TryAgain!");
				count++;
			}
		}
	}
}
