/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 26-11-2023            */
/*          Version: 1.0                */
/*          Module: UART                */
/****************************************/

#include "../DIO/STD_Types.h"
#include "../DIO/Bit_Math.h"
#include "UART_Private.h"
#include "UART_Config.h"
#include "UART.h"

#define F_CPU            16000000UL
//#define UART_BAUD      9600UL
#define UBRR_16          ((uint16)((F_CPU)/(16*UART_BAUD)-1))
#define UBRR_8           ((uint16)((F_CPU)/(8*UART_BAUD)-1))

void UART_Init(){
/****************************   Setting The Double Speed Configuration  *******************************/
    #if    (Double_Speed_Mode == Disabled)
        Clear(UCSRA_Reg,1);
        uint16 UBRR_value = UBRR_16;    
    #elif (Double_Speed_Mode == Enabled)
        Set(UCSRA_Reg,1);
        uint16 UBRR_value = UBRR_8;
    #endif

/****************************   Setting The Baud Rate Configuration  *******************************/
    Clear(UBRRH_Reg,7);    // To Select UBBRR Reg
    UBRR_value = UBRR_value & 0b0000111111111111; //0b 0000 1111 11111111 FILTER
    UBRRH_Reg = (uint8)(UBRR_value >> 8);
    UBRRL_Reg = (uint8)UBRR_value;

/****************************   Setting Frame Format :   *******************************/
    //Setting Parity Mode:
    Set(UCSRC_Reg,7);    // To Select UCSRC Reg
    #if   (Parity_Mode == Parity_Even)
        Set(UCSRC_Reg,5);Clear(UCSRC_Reg,4);
    #elif (Parity_Mode == Parity_Odd)
        Set(UCSRC_Reg,5);Set(UCSRC_Reg,4);
    #endif
    //Setting Sync Mode:
    #if   (Sync_Mode_Select == Async_Mode)
        Clear(UCSRC_Reg,6);
    #elif (Sync_Mode_Select == Sync_Mode)
        Set(UCSRC_Reg,6);
        #if (Sync_Mode_Clock_Polarity == TX_Rising_XCK)
            Clear(UCSRC_Reg,0);
        #elif (Sync_Mode_Clock_Polarity == TX_Falling_XCK)
            Set(UCSRC_Reg,0);        
        #endif
    #endif
    //Setting Stop Bit Count:
    #if   (Stop_bit_size == Stop1_Bit)
        Clear(UCSRC_Reg,3);
    #elif (Stop_bit_size == Stop2_Bit)
        Set(UCSRC_Reg,3);
    #endif
    //Setting Communication Character Size:
    #if   (Comm_Character_Size == Comm_Size_5)
        Clear(UCSRB_Reg,2);Clear(UCSRC_Reg,2);Clear(UCSRC_Reg,1);//000
    #elif (Comm_Character_Size == Comm_Size_6)
        Clear(UCSRB_Reg,2);Clear(UCSRC_Reg,2);  Set(UCSRC_Reg,1);//001
    #elif (Comm_Character_Size == Comm_Size_7)
        Clear(UCSRB_Reg,2);  Set(UCSRC_Reg,2); Clear(UCSRC_Reg,1);//010
    #elif (Comm_Character_Size == Comm_Size_8)
        Clear(UCSRB_Reg,2);  Set(UCSRC_Reg,2);  Set(UCSRC_Reg,1);//011
    #elif (Comm_Character_Size == Comm_Size_9)
          Set(UCSRB_Reg,2);  Set(UCSRC_Reg,2);  Set(UCSRC_Reg,1);//111
    #endif

/****************************   Setting The TX/RX State  *******************************/
    //Enabling the Transmitter 
    #if (UART_TX_Enable == Enabled)
        Set(UCSRB_Reg,4);
    #endif
    //Enabling the Receiver
    #if (UART_RX_Enable == Enabled)
        Set(UCSRB_Reg,3);
    #endif
    
/****************************   Setting The Interrupt  *******************************/
    //Enabling the RX Complete Interrupt 
    #if (UART_TX_Complete_Interrupt == Enabled)
        Set(UCSRB_Reg,6);
    #endif
    //Enabling the Complete Interrupt 
    #if (UART_RX_Complete_Interrupt == Enabled)
        Set(UCSRB_Reg,7);
    #endif
    //Enabling the  Data Register Empty Interrupt
    #if (UART_Data_Reg_Empty_Interrupt == Enabled)
        Set(UCSRB_Reg,5);
    #endif    
}


#if (Comm_Character_Size == Comm_Size_9)
    void UART_Send_Byte_Polling16(uint16 Data){
        while(!Get(UCSRA_Reg,5));// Polling Method On Pin5 UCSRA Reg /Data Register Empty
        if(1&(Data>>8)){
            Set(UCSRB_Reg,0);
        }else{
            Clear(UCSRB_Reg,0);
        }
        UDR_Reg = (uint8)(Data & 0b0000000011111111);
    }
    uint16 UART_Receive_Byte16(void)
    {
        while(!Get(UCSRA_Reg,7));
        uint16 Received_Data = 0;
        if(Get(UCSRB_Reg,1)){
            Received_Data = ((1<<8) | UDR_Reg);
            }else{
            Received_Data = UDR_Reg;
        }
        return Received_Data;
    }
    void UART_Send_String_Polling16(uint16 *String){
        uint8 count = 0;
        while(String[count] != '\0'){
            UART_Send_Byte_Polling16(String[count]);
            count++;
        }
    }
    void UART_Recieve_String16(uint16 *String){
        uint8 count = 0;
        while(1){
            String[count] = UART_Receive_Byte16();
            if(String[count] == 4){// ASCII 4 is [END TRANSMISSION]
                break;
            }
            else{
                count++;
            }
        }
    }
#endif

#if (Comm_Character_Size != Comm_Size_9)
    void UART_Send_Byte_Polling8(uint8 Data){
        while(!Get(UCSRA_Reg,5));// Polling Method On Pin5 UCSRA Reg /Data Register Empty
        UDR_Reg = Data; 
    }
    uint8 UART_Receive_Byte8(void){
        while(!Get(UCSRA_Reg,7));// Polling Method
        return UDR_Reg;
    }
    void UART_Send_String_Polling8(uint8 *String){
        uint8 count = 0;
        while(String[count] != '\0'){
            UART_Send_Byte_Polling8(String[count]);
            count++;
        }
    }
    void UART_Recieve_String8(uint8 *String){
        uint8 count = 0;
        while(1){
            String[count] = UART_Receive_Byte8();
            if(String[count] == 4){// ASCII 4 is [END TRANSMISSION]
                break;
            }
            else{
                count++;
            }
        }
    }
#endif









