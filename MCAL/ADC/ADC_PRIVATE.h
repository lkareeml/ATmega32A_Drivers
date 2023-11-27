/****************************************/
/*          Author: Kareem Atef		    */
/*          Date: 10-11-2023		    */
/*          Version: 1.0				*/
/*          Module : ADC Private        */
/****************************************/
#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
/****************************************
Analog to Digital Converter
Register Description
*****************************************/

/// 5 Registers : 

///     ($27) ADMUX – ADC Multiplexer Selection Register: {REFS1 REFS0 ADLAR MUX4 MUX3 MUX3 MUX2 MUX1 MUX0}
///     Bit 7:6 – REFS1:0: Reference Selection           ---  AREF(0,0)          AVCC(0,1)     Internal 2.56V(1,1)
///     Bit 5 – ADLAR: ADC Left Adjust Result            ---  left adjust(1)     Right Adjust(0)
///     Bits 4:0 – MUX4:0: Analog Channel/Gain Selection ---  ADC0(0) ADC1(1) ... ADC6(6) ADC7(7)

///     ($26) ADCSRA – ADC Control and Status Register A: {ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0}
///          Bit 7 – ADEN: ADC Enable
///          Bit 6 – ADSC: ADC Start Conversion
///          Bit 5 – ADATE: ADC Auto Trigger Enable
///          Bit 4 – ADIF: ADC Interrupt Flag     //Bit 3 – ADIE: ADC Interrupt Enable
///          Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits (2,4,8,...128)-(1,2,3...7)
///          Division Factor(2) means the Clock Hz is divided by 2 we write (1) on these 3 bits

///     ($24) ADCL ($25) ADCH – The ADC Data Register
///          ADCLR = 0 --- ADCH (00000011) ADCL (11111111) --- Right Adjust
///          ADCLR = 1 --- ADCH (11111111) ADCL (11000000) --- Left Adjust

///     ($50) SFIOR – Special FunctionIO Register:  {ADTS2 ADTS1 ADTS0 – ACME PUD PSR2 PSR10}
///     Bit 7:5 – ADTS2:0: ADC Auto Trigger Source
///     Free Running mode(0) - Analog Comparator(1) - External Interrupt Request 0(2)
///     Timer (3,4,5,6,7) 
///     Bit 4 – Reserved Bit Must be 0

#define ADC_AVCC          0
#define ADC_AREF          1
#define ADC_INTERNAL      2
#define ADC_Left_Adjust   3
#define ADC_Right_Adjust  4
#define ADC_PRE_2         1
#define ADC_PRE_4         2
#define ADC_PRE_8         3
#define ADC_PRE_16        4
#define ADC_PRE_32        5
#define ADC_PRE_64        6
#define ADC_PRE_128       7


#define ADCL_Reg    *((volatile uint8 *)0x24)
#define ADCH_Reg    *((volatile uint8 *)0x25)
#define ADCSRA_Reg  *((volatile uint8 *)0x26)
#define ADCMUX_Reg  *((volatile uint8 *)0x27)
#define SFIOR_Reg   *((volatile uint8 *)0x50)

#endif