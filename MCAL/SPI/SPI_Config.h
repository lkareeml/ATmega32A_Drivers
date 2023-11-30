/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 28-11-2023            */
/*          Version: 1.0                */
/*          Module: SPI Config          */
/****************************************/

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

//Option_Name                   Selected_Option              Available_Options
#define Data_Order              SPI_LSB_First                // SPI_LSB_First// SPI_MSB_First
#define Clock_Polarity          SPI_Leading_Edge_Raising     // SPI_Leading_Edge_Falling // SPI_Leading_Edge_Raising
#define Clock_Phase             SPI_Leading_Edge_Sample      // SPI_Leading_Edge_Sample // SPI_Leading_Edge_Setup
#define Clock_Rate_Select       SPI_F_4                      // SPI_F_2 / 4 / 8 / 16 / 32 / 64 / 128 /
#define Master_Slave_Select     SPI_Master                   // SPI_Master // SPI_Slave

#endif /* SPI_CONFIG_H_ */