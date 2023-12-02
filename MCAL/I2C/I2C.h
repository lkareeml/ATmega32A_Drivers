/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 31-11-2023            */
/*          Version: 1.0                */
/*          Module: I2C                 */
/****************************************/

#ifndef I2C_H_
#define I2C_H_
/*
Two-wire Serial Interface / (I2C)
Pins: SCL, SDA
Frame: (Start)(?) -- (Address)(7) -- (R/W)(1) -- (ACK)(1) -- (Data)(7) -- (ACK)(1) -- (Stop)(?)
Frequency : SCL MAX 400KHZ 

SCL_frequency =CPU_Clock_Frequency / ( 16 + ( 2*(TWBR)* (4^TWPS) ) )

TWINT Flag: 
START / REPEATED START /  SLA+R/W / address byte / lost arbitration
has been addressed by own slave address or general call
After the TWI has received a data byte
After a STOP or REPEATED START has been received while still addressed as a slave
 When a bus error has occurred due to an illegal START or STOP condition


MODE: Master Transmitter (MT), Master Receiver
(MR), Slave Transmitter (ST) and Slave Receiver (SR)


TWI can use MT mode to write data into a TWI EEPROM, MR mode to read the data back
from the EEPROM.

Master Transmitter/Receiver Mode
Status(TWSR)	Condition Received
08		TR		START transmitted
10		TR		repeated START transmitted
18		T		SLA/W transmitted, ACK received
20		T		SLA/W transmitted, NOT ACK received
28		T		Data byte transmitted, ACK received
30		T		Data byte transmitted, NOT ACK received
38		TR		Arbitration lost SLA+W OR SLA+R OR data
40		R		SLA/R ACK received
48		R		SLA/R NO ACK received
50		R		Data byte ACK received
58		R		Data byte NO ACK received

Slave Receiver/Transmitter Mode
Status(TWSR)	Condition Received
60		R		SLA+W received, ACK returned
68		R		Arbitration lost SLA+R/W master; own SLA+W received; ACK returned
70		R		General call received; ACK returned
78		R		Arbitration lost SLA+R/W master; General call received; ACK returned
80		R		Previously addressed with own SLA+W; data received;ACK returned
88		R		Previously addressed with own SLA+W; data received;NOT ACK returned
90		R		Previously addressed with general call; data received; ACK returned
98		R		Previously addressed with general call; data received; NOT ACK returned
A0		R		STOP condition/repeated START condition received while still as slave

A8		T		OWN SLA+R received, ACK returned
B0		T		Arbitration lost SLA+R/W master; own SLA+R received; ACK returned
B8		T		Data TWDR Transmitted; ACK received
C0		T		Data TWDR Transmitted; NOT ACK received
C8		T		Last data TWDR transmitted (TWEA = “0”); ACK received

Miscellaneous States
F8				No relevant state information available; TWINT = “0”
00				Bus error due to an illegal START or STOP condition


TWBR – TWI Bit Rate Register
Bits 7:0 – TWI Bit Rate Register


TWCR – TWI Control Register
//Bit 7 – TWINT: TWI Interrupt Flag
//Bit 6 – TWEA: TWI Enable Acknowledge Bit
//Bit 5 – TWSTA: TWI START Condition Bit
//Bit 4 – TWSTO: TWI STOP Condition Bit
//Bit 3 – TWWC: TWI Write Collision Flag
//Bit 2 – TWEN: TWI Enable Bit
//Bit 0 – TWIE: TWI Interrupt Enable


TWSR – TWI Status Register
Bits 7:3 – TWS: TWI Status
Bits 1:0 – TWPS: TWI Prescaler Bits 1(00) 4(01) 16(10) 64(11)

TWDR – TWI Data Register
Bits 7:0 – TWD: TWI Data Register

TWAR – TWI (Slave) Address Register
Bits 7:1 – TWA: TWI (Slave) Address Register
Bit 0 – TWGCE: TWI General Call Recognition Enable Bit


























*/
#endif /* I2C_H_ */