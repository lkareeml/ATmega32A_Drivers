/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 23-11-2023            */
/*          Version: 1.0                */
/*          Module: MOTOR               */
/****************************************/



//SET OCR FOR DUTYCYCLE


#ifndef MOTOR_H_
#define MOTOR_H_

typedef enum{
	Motor1,
	Motor2
}Motor_Num;

typedef enum{
	ClockWise,
	Counter_ClockWise
}Motor_Dir;

void Motor_Direction_Speed(Motor_Num motorNum,Motor_Dir motorD, uint8 Mototr_Speed);

#endif /* MOTOR_H_ */