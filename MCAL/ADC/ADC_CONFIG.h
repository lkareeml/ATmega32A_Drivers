/****************************************/
/*          Author: Kareem Atef		    */
/*          Date: 10-11-2023		    */
/*          Version: 1.0				*/
/*          Module : ADC Config         */
/****************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

#define ADC_REF_VOLT      ADC_AVCC            /// Options: ADC_AVCC - ADC_AREF - ADC_INTERNAL
#define ADC_ADJUSTMENT    ADC_Left_Adjust     /// Options: ADC_Left_Adjust - ADC_Right_Adjust
#define ADC_PRESCALER     ADC_PRE_2           /// Options: ADC_PRE_2 - ADC_PRE_4 ... ADC_PRE_128

#endif 