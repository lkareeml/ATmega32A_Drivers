/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 06-12-2023            */
/*          Version: 1.0                */
/*          Module: Smart Home          */
/****************************************/


#ifndef SMART_HOME_H_
#define SMART_HOME_H_


/*
Login and user system:
Admin Users: Username : Admin, UserID: 1, Password: 4321
Normal Users: Username : ?, UserID: 2, Password: 1234
EEPROM_Add_Data_Byte();
EEPROM_Read_Data_Byte();
EEPROM_Add_New_User();//MAX 3 USERS
EEPROM_Delete_Normal_User();
EEPROM_Increase_User_Count();
EEPROM_Decrease_User_Count();
*/

// MEMORY MANAGEMENT USE LINKED LIST AND STRUCT
typedef struct Profile{//48
	uint16 UserID;                     //2
	uint16 MyAddress;//Current Address //2
	uint16 Next_Node;//Next Address    //2
	uint8 Empty[10];				   //10
	uint8 Username[16];                //16
	uint8 Password[16];                //16
}Profile;


typedef enum{
	Admin_Mode_Logged_In,
	User_Mode_Logged_In,
	Not_Logged
}Login_Mode;

typedef enum{
	Door_Lock_Servo,
	Dim_Lamp_Device,
	Air_Conditioner_Device,
	LED_0_Device,
	LED_1_Device,
	LED_2_Device,
	LED_3_Device,
	LED_4_Device,
}Device;

typedef enum{
	Turn_Off,
	Turn_On
}State;


void EEPROM_Save_New_User(uint16 Start_Address,Profile User);

#endif /* SMART_HOME_H_ */

/*

[****************] 
[*********(0)more]

Start
[Welcome To *****]
[Kiak Smart home*]

LCD-KEYPAD-IDLE_NO_LOGIN
[AC(ON) Temp(30c)] -- [AC(OFF)Temp(20c)]
[****(0) To Login] -- [****(0) To Login]

LCD_LOGIN_KEYPAD
[Enter UserID:***][Enter Password:*][Welcome Back!***]
[*...************][*...************][*Username*******]


Admin_Choose_Handler()
User_Choose_Handler()
Appliances_Controller(uint8 State,uint8 Appliance)

*/

/*
Login and user system:
Admin Users: Username : Admin, UserID: 1, Password: 4321
Normal Users: Username : ?, UserID: 2, Password: 1234
EEPROM_Add_Data_Byte();
EEPROM_Read_Data_Byte();

EEPROM_Add_New_User();//MAX 3 USERS
EEPROM_Delete_Normal_User();
EEPROM_Increase_User_Count();
EEPROM_Decrease_User_Count();


0x0000 --0x07FF (0--2047) -- 2048

First 256 Byte Reserved (0x000 -- 0x0100)
	224 Bytes To indicate written Address (1 is full, 0 is empty)
		(0x000 -- 0x00E0)
	Byte number 225,226 for pointer to last address Written
Free To use (0x0100 -- 0x0800) (1792 Bytes)
*/
/* 
PIN CALCULATION:8 8 8 8 
UNUSED FOR THIS PROJECT: KIT_BUTTONS: D2-D6-B0

Communication And Storage:
		BLUETOOTH		2 PIN		PD0/PD1 {TX-RX} (UART)
		EXT.EEPROM		2 PIN		PC0/PC1 {SCL-SDA} (I2C)	SAVE_NEW_USER()
Input:
		TEMP_SENS(POT)	1 PIN		PA1
		KEYPAD			8 PIN		PB4-PB5-PB6-PB7-PC3-PC4-PC5-PC6
Output:
		LCD				7 PIN		PA4 - PA5 - PA6 - PA7 -- PB1 - PB2 - PB3
		ALARM/BUZZER	1 PIN		PA3					ALARM_TILL_RESET()
Controllable Appliances:
		DOOR_SERVO		1 PIN		PD7		ADMIN_ONLY	DOOR_ON() DOOR_OFF()
		5LAMP			5 PIN		PC2-PC7-PD3-PD4-PD5
		DIMMING_LAMP	1 PIN		A0 //PWM
		AC/RELAY		1 PIN		PA2

	Remoted controlled by mobile or lab top.
		For emergency use LCD and Keypad “user mode only”.
		The controllable things are :
		5 on/off lamps,										(3LEDS+2)
		one dimming lamp,									(RELAY?)
		door,												(SERVO)
		air-condition according to the ambient temperature	(POT-RELAY)
		
	Login system admin and user “admin is remoted only.
	--->    Admin mode can register any user or remove.
	--->    Usernames and password must be kept into memory even at powered off. .... EEPROM
	--->    If any user/admin/passwords wrong more than 3 trial, system must break down and fire alarm until reset.
	--->    Admin and user can access to all applies except user cant control the door opening
	
	// Specifications –LCD & keypad USER MODE ONLY 
		They are used to login to system as a user only.
		After login, user can control all features except opening door.
		USER MODE can control the system even if any user login by remoted mode except admin until allowing of admin.
		OPTION(RUNNING DEVICES) The LCD must display running devices if the keypad-LCD system is not used.(IDLE)
		The user’s usernames in this system different than the user’s usernames in the remoting system
	
	// Specifications –EEPROM
		Storing the new user to the system “registration”..
		It must be Read/write in ADMIN_MODE AND It must be read only in USER_MODE
	
	// Specifications –TTL/Bluetooth
		Transmitting/Receiving between MC and PC/mobile.
		Every action, Message must be printed on Mobile/PC screen, like: Hey, please Enter your username:.
		Transmitting/Receiving the commands to run the system.
	
	// Specifications –Lamps, Relay, Dimmer
		Lamps must be RELAY isolated because of high power.
		Dimmer circuit can control current flow to lamp depending on the input voltage “0 – 5V”
	
	// Specifications – Door
		The actuator used is a SERVO_MOTOR to control the opening door only in admin mode, 
		it is controlled by COMMAND send by	Mobile/PC OPEN / CLOSE DOOR
	
	// Component you may need
		24C08 EEPROM, or use the internal.
		Bluetooth module HC-05 or TTL (PL2003 or CH340or CP2102).
		5 transistors and relays (Not mandatory they can be replaced by LEDs.
		1 transistor and Solid-state Relay for dimming circuit.
		LM35 temperature sensor or equivalent.
		2 NPN and DC motor
		Keypad & Lm01602A Character LCD.
		Servo motor.
	// Specifications –Temperature Sensor, DC motor
		Temp.sensor reads ambient temp, if the temp higher than 28 °C, Air condition TURN_ON DC_Motor
		if the temp becomes lower than 21 °C, Air condition	TURN_OFF DC_Motor
	*/


