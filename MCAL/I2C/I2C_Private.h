/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 31-11-2023            */
/*          Version: 1.0                */
/*          Module: I2C                 */
/****************************************/

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

typedef enum{
	MSTR_TR_START=0x08,
	MSTR_TR_REPEAT_START=0x10,
	MSTR_T_SLA_W_ACK = 0x18,
	MSTR_T_SLA_W_NO_ACK = 0x20,
	MSTR_T_DATA_ACK = 0x28,
	MSTR_T_DATA_NO_ACK = 0x30,
	MSTR_TR_ARB_LOST = 0x38,
	MSTR_R_SLA_R_ACK = 0x40,
	MSTR_R_SLA_R_NO_ACK = 0x48,
	MSTR_R_DATA_ACK = 0x50,
	MSTR_R_DATA_NO_ACK = 0x58,

	SLAV_R_SLA_W_ACK = 0x60,
	SLAV_R_ARB_LOST_SLA_W_ACK = 0x68,
	SLAV_R_GEN_CALL_ACK = 0x70,
	SLAV_R_ARB_LOST_GEN_W_ACK = 0x78,
	SLAV_R_SLA_W_DATA_ACK = 0x80,
	SLAV_R_SLA_W_DATA_NO_ACK = 0x88,
	SLAV_R_Gen_DATA_ACK = 0x90,
	SLAV_R_Gen_DATA_NO_ACK = 0x98,
	SLAV_R_STOP_OR_REPEATED_START = 0xA0,

	SLAV_T_SLA_R_ACK = 0xA8,
	SLAV_T_ARB_LOST_SLA_R_ACK = 0xB0,
	SLAV_T_DATA_ACK = 0xB8,
	SLAV_T_DATA_NO_ACK = 0xC0,
	SLAV_T_LAST_DATA_ACK = 0xC8,
	
	MIS_NO_INFO = 0xF8,
	MIS_BUS_ERROR_ILLIGAL = 0x00
}TWI_STATE;

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