/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 17-11-2023            */
/*          Version: 1.0                */
/*          Module: Interrupt           */
/****************************************/

#ifndef INTERRUPT_PRIVATE_H_
#define INTERRUPT_PRIVATE_H_

#define SREG_Reg        *((volatile uint8*)0x5F) ///General Interrupt Enable Bit 
/// EXTERNAL INTERRUPT 0,1 // Bit 0,1,2,3 – ISC0123 //  Interrupt Sense Control
/// LowLvl 00 // Raising 11  // Falling 01 // AnyChange 10 // Bit(0,1)
#define MCUCR_Reg       *((volatile uint8*)0x55) /// INT0 , INT1
/// EXTERNAL INTERRUPT 2 // Bit 6 – ISC2 //  Interrupt Sense Control
#define MCUCSR_Reg      *((volatile uint8*)0x54) /// INT2

#define GICR_Reg        *((volatile uint8*)0x5B) /// 76543210 >> INT1 INT0 INT2 .....
#define GIFR_Reg        *((volatile uint8*)0x5A) /// 76543210 >> INTF1 INTF0 INTF2 .....

#define EXTI0_Raising_Edge    0
#define EXTI0_Falling_Edge    1
#define EXTI0_Any_Change      2
#define EXTI0_Low_Level       3

#define EXTI1_Raising_Edge    0
#define EXTI1_Falling_Edge    1
#define EXTI1_Any_Change      2
#define EXTI1_Low_Level       3

#define EXTI2_Raising_Edge    0
#define EXTI2_Falling_Edge    1

/*
01    $000    RESET External Pin, Power-on Reset, Brown-out Reset, Watchdog Reset, and JTAG AVR Reset
02    $002    INT0 External Interrupt Request 0
03    $004    INT1 External Interrupt Request 1
04    $006    INT2 External Interrupt Request 2
05    $008    TIMER2 COMP Timer2 Compare Match
06    $00A    TIMER2 OVF Timer2 Overflow
07    $00C    TIMER1 CAPT Timer1 Capture Event
08    $00E    TIMER1 COMPA Timer1 Compare Match A
09    $010    TIMER1 COMPB Timer1 Compare Match B
10    $012    TIMER1 OVF Timer1 Overflow
11    $014    TIMER0 COMP Timer0 Compare Match
12    $016    TIMER0 OVF Timer0 Overflow
13    $018    SPI, STC Serial Transfer Complete
14    $01A    USART, RXC USART, Rx Complete
15    $01C    USART, UDRE USART Data Register Empty
16    $01E    USART, TXC USART, Tx Complete
17    $020    ADC ADC Conversion Complete
18    $022    EE_RDY EEPROM Ready
19    $024    ANA_COMP Analog Comparator
20    $026    TWI Two-wire Serial Interface
21    $028    SPM_RDY Store Program Memory Ready
*/
#endif