/****************************************/
/*          Author: Kareem Atef		    */
/*          Date: 10-11-2023		    */
/*          Version: 1.0				*/
/*          Module: LCD Driver          */
/****************************************/
typedef enum{
	RIGHT,
	LEFT
}Dir;

#ifndef DRIVERS_HAL_LCD_LCD_H_
#define DRIVERS_HAL_LCD_LCD_H_
//extern uint8 LCD_GLOBAL_POSITION;
void LCD_Init();
void LCD_Send_Cmd(uint8 cmd);
void LCD_Send_Char(uint8 data);
void LCD_Send_String(char * str);
void LCD_Set_Cursor_Position(uint8 row, uint8 col);
void LCD_Send_Clear_Screen();
void LCD_Cursor_Shift(Dir Direction);
void LCD_Delete_Last_Written();
void LCD_Position_Handler(Dir Direction);
#endif /* DRIVERS_HAL_LCD_LCD_H_ */
