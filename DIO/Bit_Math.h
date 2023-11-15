/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 10-11-2023            */
/*          Version: 1.0                */
/*          Module : Bit Math           */
/****************************************/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define Set(Port,pin)               Port |= (1<<pin)
#define Clear(Port,pin)             Port &= (~(1<<pin))
#define Toggle(Port,pin)            Port ^= (1<<pin)
#define Get(Port,pin)               (Port>>pin)&(0x01)
#define Check_Cls(Port,pin)         (!((Port>>pin)&(0x01)))

#endif
