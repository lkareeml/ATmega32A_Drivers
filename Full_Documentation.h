/*
 * Full_Documentation.h
 *  Author: Kareem Atef
 */ 


#ifndef FULL_DOCUMENTATION_H_
#define FULL_DOCUMENTATION_H_

/*
// TCNT Fires at 256 Ticks
// Tick_Time = Prescaler/Frequency
// OverFlow_Time = Tick_Time * (2^(Resolution))
// OverFlow_Time = Tick_Time * (2^(256?1024?...))
// SFIOR_Reg : Bit 0 – PSR10: Prescaler Reset T1 and T0
*/
//    TCCR1A – Timer1 Control Register A
//        Bit 7:6 – COM1A1:0: Compare Output Mode for Compare unit A
//        Bit 5:4 – COM1B1:0: Compare Output Mode for Compare unit B
//        Bit 3 – FOC1A: Force Output Compare for Compare unit A
//        Bit 2 – FOC1B: Force Output Compare for Compare unit B
//    ICR1H ICR1L TO READ ICR1
//    TIFR – Timer Interrupt Flag Register
//        Bit 5 – ICF1:  Timer1, Input Capture Flag
//        Bit 4 – OCF1A: Timer1, Output Compare A Match Flag
//        Bit 3 – OCF1B: Timer1, Output Compare B Match Flag
//        Bit 2 – TOV1:  Timer1, Overflow Flag

//    TIMSK – Timer Interrupt Mask Register
//        Bit 1 – OCIE0: Timer0 PIE-Output Compare Match Interrupt Enable
//        Bit 0 – TOIE0: Timer0 PIE-Overflow Interrupt Enable

// ONLY FOR TIMER 2 >>> //ASSR – Asynchronous Status Register EXIST
//        Bit 3 – AS2: Asynchronous Timer2
//        Bit 2 – TCN2UB: Timer2 Update Busy
//        Bit 1 – OCR2UB: Output Compare Register2 Update Busy
//        Bit 0 – TCR2UB: Timer Control Register2 Update Busy
// TIMER2 Cant be used as counter

//    TIMSK – Timer Interrupt Mask Register
//        Bit 7 – OCIE2: Timer2 PIE-Output Compare Match Interrupt Enable.
//        Bit 6 – TOIE2: Timer2 PIE-Overflow Interrupt Enable

//    TIMSK – Timer Interrupt Mask Register
//        Bit 5 – TICIE1: Timer1, PIE-Input Capture Interrupt Enable
//        Bit 4 – OCIE1A: Timer1, PIE-Output Compare A Match Interrupt Enable
//        Bit 3 – OCIE1B: Timer1, PIE-Output Compare B Match Interrupt Enable
//        Bit 2 – TOIE1:  Timer1, PIE-Overflow Interrupt Enable

//    TCNT1H and TCNT1L – Timer1
//    This 16-bit register holds the current count value of Timer/Counter1.
//    OCR1AH and OCR1AL – Output Compare Register 1 A
//    OCR1BH and OCR1BL – Output Compare Register 1 B

//    ICR1H and ICR1L – Input Capture Register 1
//    ICR1H and ICR1L – Input Capture Register 1

//    TCCR1A – Timer1 Control Register A
//        Bit 7:6 – COM1A1:0: Compare Output Mode for Compare unit A
//        Bit 5:4 – COM1B1:0: Compare Output Mode for Compare unit B
//        Bit 3 – FOC1A: Force Output Compare for Compare unit A Clear(TCCR1A_Reg,3);Set(TCCR1A_Reg,3);
//        Bit 2 – FOC1B: Force Output Compare for Compare unit B Clear(TCCR1A_Reg,2);Set(TCCR1A_Reg,2);
//    TIFR – Timer Interrupt Flag Register
//        Bit 5 – ICF1:  Timer1, Input Capture Flag
//        Bit 4 – OCF1A: Timer1, Output Compare A Match Flag
//        Bit 3 – OCF1B: Timer1, Output Compare B Match Flag
//        Bit 2 – TOV1:  Timer1, Overflow Flag

*/
//WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).
//	Timer1_Normal								0
//	Timer1_PWM_Phase_Correct_8bit				1
//	Timer1_PWM_Phase_Correct_9bit				2
//	Timer1_PWM_Phase_Correct_10bit				3
//	Timer1_CTC_OCR1A							4
//	Timer1_Fast_PWM_8bit						5
//	Timer1_Fast_PWM_9bit						6
//	Timer1_Fast_PWM_10bit						7
//	Timer1_PWM_Phase_Frequency_Correct_ICR1		8
//	Timer1_PWM_Phase_Frequency_Correct_OCR1A	9
//	Timer1_PWM_Phase_Correct_ICR1				10
//	Timer1_PWM_Phase_Correct_OCR1A				11
//	Timer1_CTC_ICR1								12
//	Timer1_FastPWM_ICR1							14
//	Timer1_FastPWM_OCR1A						15 /// SEND PWM TO OCR1A

// Timer_Pre_1 // Timer_Pre_8 // Timer_Pre_64 // Timer_Pre_256 // Timer_Pre_1024
// Timer_Pre_STOP // Timer_Pre_External_T1_Falling // Timer_Pre_External_T1_Raising

/*
#include "MCAL/DIO/STD_Types.h"
#include "MCAL/DIO/Bit_Math.h"
#include "MCAL/ADC/ADC_INIT.h"
#include "MCAL/TIMER/Timer_Init.h"
#include "MCAL/INTERRUPT/Interrupt_H.h"
#include "HAL/LEDS/LEDS.h"
#include "HAL/LCD16/LCD_Driver.h"

#include "APP/ALLAPPS.h"
#include "APP/App1.h"
#include "MCAL/DIO/STD_Types.h"
#include "MCAL/ADC/ADC_INIT.h"
*/
/*
#include <avr/interrupt.h>
ISR(TIMER0_COMP_vect){
	return;
}
ISR(ADC_vect){
		TASK12_ISR_ADC_Timer();
}
*/

/*
UART == USART : Universal Synchronous/Asynchronous Receiver Transmitter

Simplex : One party is transmitter, one party is receiver : Like TV and radio
Half Duplex : Like COP Press police walkie talkie Send OR receive at a time
Full Duplex : Send and receive at the same time like Phone call

Serial   :  on one line, Or Two lines max, one to send one to receive
Parallel : 8 bit = 8 lines, 16 bit = 16 lines , ... each pin have a line like a bus
Parallel problem : complex connection with many wires
Parallel problem : cross-talk : magnetic field effect each wire and the fellow wire
Parallel problem : Timing Skew : each bit arrives defferently in speed;

synchronous  : Both share a wire sending a clock so both get same clock speed (LIN)
asynchronous : Both agree on specific speed, on code itself (BITRATE)(SERIAL)

Master : Initiate communication , Generate Clock , Select slave
Single Master-Multi slaves (SPI)(LIN)    
Multi Masters - Multi Slaves (I2C)
Multi Masters - No slave (CAN)
Pair-Pair (UART)

++++ UART : ++++
 RX : Receive  using TX --- TX : Transmit using RX
 Full-Duplex  -- Wired -- Serial -- Asynchronous -- Pair to Pair
 Baud rate : 9600baud/sec if baud = 1bit >>> 9600 bit / second
 Baud rate : 9600baud/sec if baud = 2bit >>> 2*9600 bit / second

 Frame      : Start_Bit ++++ 5-9Bit_Data ++++ Parity_Bit ++++ Stop_Bit
 Parity_Bit : Even or Odd (The add of all Data+Parity Bits)
 Stop_Bit   : can be 1 or 2 bit, as High only
 throughput : Data/Frame 
 max_throughput  = maxData/Frame = 9 / ( 1+9+1) %100 = 81.8%
 min_throughput  = minData/Frame = 5 / ( 1+5+2) %100 = 55.5%

Equations for Calculating Baud Rate Register Setting
    Asynchronous Normal Mode : UBBRR = (fosc/(16*BAUD)) - (1)
    Asynchronous Double Speed Mode (U2X = 1) : UBBRR = (fosc/(8*BAUD)) - (1)

Frame Formats : 
    Start_Bit(1) ++++ Data_Bit(5~9) ++++ Parity_Bit(1~2) ++++ Stop_Bit(1~2)
    Start bit, always low
    Data bits (0 to 8)
    Parity bit. Can be odd or even
    Stop bit, always high
    No transfers on (RxD or TxD). An IDLE line must be high

initialization process normally consists of:

    setting the baud rate,  : 
        U2X = 0, 
        URSEL: Register Select (0_UBRRH)
        Normal Mode : UBBRR = (fosc/(16*BAUD)) - (1) OR 2X Mode UBBRR = (fosc/(8*BAUD)) - (1)
        
    setting frame format :
            URSEL: Register Select (1_UCSRC)
            UMSEL: USART Mode Select (0_Async 1_Sync)
            UPM1:0: Parity Mode (10_Even/11_Odd)
            USBS: Stop Bit Select (0_1Bit/1_2Bit)    
            Choose Size : UCSZ2 (d0_5/d3_8/d7_9)
            
    enabling the Transmitter or the Receiver depending usage
        **Bit 4 – RXEN: Receiver Enable                            Enable_Bit
        **Bit 3 – TXEN: Transmitter Enable                        Enable_Bit
        
    interrupt driven USART operation, 
    
    *** Data Transmission – The USART Transmitter
            Sending Frames with 5 to 8 Data Bit
            Sending Frames with 9 Data Bit ---- the ninth bit must be written before writing to UDR
            Transmitter Flags and Interrupts
            Parity Generator
            Disabling the Transmitter

    ***    Data Reception – The USART Receiver
            Receiving Frames with 5 to 8 Data Bits
            Receiving Frames with 9 Data bits
            Receive Compete Flag and Interrupt
            Receiver Error Flags
            Parity Checker
            Disabling the Receiver
            Flushing the Receive Buffer
Asynchronous Data Reception
*Asynchronous Clock Recovery
*Asynchronous Data Recovery
*Asynchronous Operational Range

Multi-processor Communication Mode

Accessing UBRRH/UCSRC Registers
*Write Access
**If URSEL is zero during a write operation,UBRRH will be updated. 
**If URSEL is one, the UCSRC setting will be updated.
*Read Access

++++UDR – USART I/O Data Register
** UDR (Read) / UDR (Write)                                Data_Reg

++++UCSRA – USART Control and Status Register A
**Bit 7 – RXC: USART Receive Complete                    Flag-Bit    G
**Bit 6 – TXC: USART Transmit Complete                    Flag-Bit    G
**Bit 5 – UDRE:Data Register Empty                        Flag-Bit    G
**Bit 4 – FE: Frame Error                                Flag-Bit    G
**Bit 3 – DOR: Data OverRun                                Flag-Bit    G
**Bit 2 – PE: Parity Error                                Flag-Bit    G
**Bit 1 – U2X: Double.USART.Trans.Speed (1_En/0_Dis)    Choice_Bit    0
**Bit 0 – MPCM: Multi-processor.ComMode (1_En/0_Dis)    Choice_Bit    0
    
++++UCSRB – USART Control and Status Register B
**Bit 7 – RXCIE: RX Complete Interrupt Enable            Enable_Bit    
**Bit 6 – TXCIE: TX Complete Interrupt Enable            Enable_Bit        
**Bit 5 – UDRIE: Data Reg Empty Interrupt Enable        Enable_Bit
**Bit 4 – RXEN: Receiver Enable                            Enable_Bit
**Bit 3 – TXEN: Transmitter Enable                        Enable_Bit
**Bit 2 – UCSZ2: Character Size                            Choice_Bit
**Bit 1 – RXB8: Receive Data Bit 8                        Extra_Bit
**Bit 0 – TXB8: Transmit Data Bit 8                        Extra_Bit

++++UCSRC – USART Control and Status Register C
**Bit 7 – URSEL: Register Select                        Choice_Bit
**Bit 6 – UMSEL: USART Mode Select (0_Async 1_Sync)        Choice_Bit
**Bit 5:4 – UPM1:0: Parity Mode (10_Even/11_Odd)        Choice_Bit
**Bit 3 – USBS: Stop Bit Select (0_1Bit/1_2Bit)            Choice_Bit
**Bit 2:1 –UCSZ1:0: Character Size (d0_5/d3_8/d7_9)        Choice_Bit
**Bit 0 – UCPOL: Clock Polarity (For Sync Mode)            Choice_Bit

++++UBRRL and UBRRH – USART Baud Rate Registers
**Bit 15 – URSEL: Register Select(0_UBRRH/1_UCSRC)        Choice_Bit
**Bit 14:12 – Reserved Bits
**Bit 11:0 – UBRR11:0: USART Baud Rate Register(Table)    Choice_Bit
Examples of Baud Rate Setting
*/


/*
SPI == Serial Peripheral Interface

(Full Duplex -- Serial --  synchronous -- Single Master-Multi slaves)

SS Pin Functionality
MOSI User Defined Input
MISO Input User Defined
SCK User Defined Input
SS User Defined Input

SPCR – SPI Control Register
    Bit 7 – SPIE: SPI Interrupt Enable
    Bit 6 – SPE: SPI Enable
    Bit 5 – DORD: Data Order
    Bit 4 – MSTR: Master/Slave Select
    Bit 3 – CPOL: Clock Polarity
    Bit 2 – CPHA: Clock Phase
    Bits 1, 0 – SPR1, SPR0: SPI Clock Rate Select 1 and 0
SPSR – SPI Status Register
    Bit 7 – SPIF: SPI Interrupt Flag
    Bit 6 – WCOL: Write COLlision Flag
    Bit 5:1 – Reserved Bits
    Bit 0 – SPI2X: Double SPI Speed Bit
SPDR – SPI Data Register
*/


#endif /* FULL_DOCUMENTATION_H_ */