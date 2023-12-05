/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 31-11-2023            */
/*          Version: 1.0                */
/*          Module: I2C                 */
/****************************************/

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define Pre_1	0
#define Pre_4	1
#define Pre_16	2
#define Pre_64	3

#define TWCR_Reg        *((volatile uint8*)0x56) // TWI (I2C)
#define TWDR_Reg        *((volatile uint8*)0x23) // TWI (I2C)
#define TWAR_Reg        *((volatile uint8*)0x22) // TWI (I2C)
#define TWSR_Reg        *((volatile uint8*)0x21) // TWI (I2C)
#define TWBR_Reg        *((volatile uint8*)0x20) // TWI (I2C)

#endif /* I2C_PRIVATE_H_ */