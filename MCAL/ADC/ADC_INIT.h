/****************************************/
/*          Author: Kareem Atef		    */
/*          Date: 10-11-2023		    */
/*          Version: 1.0				*/
/*          Module : ADC                */
/****************************************/

#ifndef ADC_INIT_H_
#define ADC_INIT_H_

#define ADC_Ch0 0
#define ADC_Ch1 1
#define ADC_Ch2 2
#define ADC_Ch3 3
#define ADC_Ch4 4
#define ADC_Ch5 5
#define ADC_Ch6 6
#define ADC_Ch7 7

void ADC_Init(void);
void ADC_Enable(void);
void ADC_Disable(void);
void ADC_Wait(void);
void ADC_Start(void);

uint8 ADC_Return_Result();
uint8 ADC_Timer_Polling_Result();

void ADC_Interrupt_Enable();
void ADC_Interrupt_Disable();
void ADC_Auto_Trigger_Enable();
void ADC_Auto_Trigger_Disable();

void ADC_Manual_Interrupt();
void ADC_Timer_No_Interrupt();
void ADC_Timer_With_Interrupt();
void ADC_Interrupt_Flag_Clear();


uint8 ADC_Convert_8bit(uint8 channel);
uint16 ADC_Convert_16bit(uint8 channel);
#endif