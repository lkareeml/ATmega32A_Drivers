/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 26-11-2023            */
/*          Version: 1.0                */
/*          Module: SPI                 */
/****************************************/

#define F_CPU        16000000UL
#include "../DIO/STD_Types.h"
#include "../DIO/Bit_Math.h"
#include "SPI_Private.h"
#include "SPI_Config.h"
#include "SPI.h"


void SPI_Init(){
/****************************   Setting The Data_Order Configuration  *******************************/
    #if   (Data_Order == SPI_LSB_First)
        Set(SPCR_Reg,5);
    #elif (Data_Order == SPI_MSB_First)
        Clear(SPCR_Reg,5);
    #endif
/****************************   Setting Clock_Polarity Configuration  *******************************/
    #if   (Clock_Polarity == SPI_Leading_Edge_Raising)
        Clear(SPCR_Reg,3);
    #elif (Clock_Polarity == SPI_Leading_Edge_Falling)
        Set(SPCR_Reg,3);
    #endif
/****************************   Setting Clock_Phase Configuration  *******************************/
    #if   (Clock_Phase == SPI_Leading_Edge_Sample)
            Clear(SPCR_Reg,2);
    #elif (Clock_Phase == SPI_Leading_Edge_Setup)
            Set(SPCR_Reg,2);
    #endif
/****************************   Setting Clock_Rate Configuration  *******************************/
    #if   (Clock_Rate_Select == SPI_F_4)
        Clear(SPSR_Reg,0);Clear(SPCR_Reg,1);Clear(SPCR_Reg,0);
    #elif (Clock_Rate_Select == SPI_F_16)
        Clear(SPSR_Reg,0);Clear(SPCR_Reg,1);Set(SPCR_Reg,0);
    #elif (Clock_Rate_Select == SPI_F_64)
        Clear(SPSR_Reg,0);Set(SPCR_Reg,1);Clear(SPCR_Reg,0);
    #elif (Clock_Rate_Select == SPI_F_128)
        Clear(SPSR_Reg,0);Set(SPCR_Reg,1);Set(SPCR_Reg,0);
    #elif (Clock_Rate_Select == SPI_F_2)
        Set(SPSR_Reg,0);Clear(SPCR_Reg,1);Clear(SPCR_Reg,0);
    #elif (Clock_Rate_Select == SPI_F_8)
        Set(SPSR_Reg,0);Clear(SPCR_Reg,1);Set(SPCR_Reg,0);
    #elif (Clock_Rate_Select == SPI_F_32)
        Set(SPSR_Reg,0);Set(SPCR_Reg,1);Clear(SPCR_Reg,0);
    #endif
/****************************   Setting Master_Slave Configuration  *******************************/
    #if   (Master_Slave_Select == SPI_Master)
        Set(SPCR_Reg,4);
    #elif (Master_Slave_Select == SPI_Slave)
        Clear(SPCR_Reg,4);
    #endif
}

//SPDR – SPI Data Register
uint8 SPI_Transmit(uint8 Send_Data){
    SPDR_Reg = Send_Data;
    while(!Get(SPSR_Reg,7));//While Interrupt Flag is Off Polling
    if(Get(SPSR_Reg,6))//If 1 return error Because of Write Collision Flag
        return 1;
    else{
        uint8 Received_Data = SPDR_Reg;
        return Received_Data;
    }
}

//SPCR – SPI Control Register
void SPI_Enable(void)           {      Set(SPCR_Reg,6);    }
void SPI_Disable(void)          {    Clear(SPCR_Reg,6);    }
void SPI_Interrupt_Enable(void) {      Set(SPCR_Reg,7);    }
void SPI_Interrupt_Disable(void){    Clear(SPCR_Reg,7);    }