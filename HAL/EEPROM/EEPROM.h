/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 4-12-2023             */
/*          Version: 1.0                */
/*          Module: EEPROM              */
/****************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

void  EEPROM_Init(void);

void EEPROM_ALL_Wiper();
void EEPROM_Address_Checker();

void  EEPROM_Write_Byte(uint16 Address , uint8 Data);
uint8 EEPROM_Read_Byte(uint16 Address);
void  EEPROM_Remove_Byte(uint16 Address);

void  EEPROM_Write_String(uint16 Address , sint8 String[16]);
void  EEPROM_Read_String(uint16 Address , sint8* String, uint8 size);
void  EEPROM_Remove_String(uint16 Start_Address, uint16 End_Address);

#endif /* EEPROM_H_ */