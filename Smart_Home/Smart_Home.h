/*
 * Smart_Home.h
 *
 * Created: 12/2/2023 11:48:12 AM
 *  Author: Kareem
 */ 


#ifndef SMART_HOME_H_
#define SMART_HOME_H_


#endif /* SMART_HOME_H_ */

	/* 
	PIN CALCULATION:8 8 8 8 
		KEYPAD			8 PIN		
		LCD				7 PIN		PA4 - PA5 - PA6 - PA7 -- PB1 - PB2 - PB3
		ALARM/BUZZER	1 PIN		PA3
		5LAMP			5 PIN		
		DIMMING_LAMP	1 PIN		
		BLUETOOTH		2 PIN			PD0 - PD1	{TX-RX}
		DOOR_SERVO		1 PIN		PD7
		EXT.EEPROM		2 PIN		PC0 - PC1	{SCL-SDA}	{I2C}	
		TEMP_SENS(POT)	1 PIN		PA2
		
		
			TWBR: TWI Bit Rate Register:
			{TWBR7 	TWBR6 	TWBR5 	TWBR4 	TWBR3 	TWBR2 	TWBR1 	TWBR0}
			TWCR: TWI Control Register:
			{TWINT 	TWEA 	TWSTA 	TWSTO 	TWWC 	TWEN 	 – 	  TWIE}
		
	Remoted controlled by mobile or lab top.
		For emergency use LCD and Keypad “user mode only”.
		The controllable things are :
		5 on/off lamps, 
		one dimming lamp, 
		door, 
		air-condition according to the ambient temperature
		
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


