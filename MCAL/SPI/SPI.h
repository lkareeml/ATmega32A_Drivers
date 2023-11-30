/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 28-11-2023            */
/*          Version: 1.0                */
/*          Module: SPI                 */
/****************************************/
    
#ifndef SPI_H_
#define SPI_H_

#define SPI_LSB_First                1
#define SPI_MSB_First                0
#define SPI_Leading_Edge_Raising     0
#define SPI_Leading_Edge_Falling     1
#define SPI_Leading_Edge_Sample      0
#define SPI_Leading_Edge_Setup       1
#define SPI_F_4                      0
#define SPI_F_16                     1
#define SPI_F_64                     2
#define SPI_F_128                    3
#define SPI_F_2                      4
#define SPI_F_8                      5
#define SPI_F_32                     6
#define SPI_Master                   1
#define SPI_Slave                    0
//#define SPI_F_64  111

void SPI_Init();
uint8 SPI_Transmit(uint8 Send_Data);
void SPI_Enable(void);
void SPI_Disable(void);
void SPI_Interrupt_Enable(void);
void SPI_Interrupt_Disable(void);

#endif /* SPI_H_ */