
#ifndef __CAL_STEPPING_MOTOR_H
#define __CAL_STEPPING_MOTOR_H

#define __1_IO1_GPIO_Port    GPIOG
#define __1_IO2_GPIO_Port    GPIOG
#define __1_IO3_GPIO_Port    GPIOG
#define __1_IO4_GPIO_Port    GPIOG
#define __HAL_RCC__1_IO_GPIO_Port_CLK_ENABLE()  __HAL_RCC_GPIOG_CLK_ENABLE() 

#define __1_IO1_GPIO_Pin    GPIO_PIN_2
#define __1_IO2_GPIO_Pin    GPIO_PIN_3
#define __1_IO3_GPIO_Pin    GPIO_PIN_4
#define __1_IO4_GPIO_Pin    GPIO_PIN_5

#define __2_IO1_GPIO_Port    GPIOF
#define __2_IO2_GPIO_Port    GPIOF
#define __2_IO3_GPIO_Port    GPIOF
#define __2_IO4_GPIO_Port    GPIOF
#define __HAL_RCC__2_IO_GPIO_Port_CLK_ENABLE()  __HAL_RCC_GPIOF_CLK_ENABLE() 

#define __2_IO1_GPIO_Pin    GPIO_PIN_0
#define __2_IO2_GPIO_Pin    GPIO_PIN_1
#define __2_IO3_GPIO_Pin    GPIO_PIN_2
#define __2_IO4_GPIO_Pin    GPIO_PIN_3

#define __3_IO1_GPIO_Port    GPIOF
#define __3_IO2_GPIO_Port    GPIOF
#define __3_IO3_GPIO_Port    GPIOF
#define __3_IO4_GPIO_Port    GPIOF
#define __HAL_RCC__3_IO_GPIO_Port_CLK_ENABLE()  __HAL_RCC_GPIOF_CLK_ENABLE() 

#define __3_IO1_GPIO_Pin    GPIO_PIN_4
#define __3_IO2_GPIO_Pin    GPIO_PIN_5
#define __3_IO3_GPIO_Pin    GPIO_PIN_6
#define __3_IO4_GPIO_Pin    GPIO_PIN_7

#define __4_IO1_GPIO_Port    GPIOF
#define __4_IO2_GPIO_Port    GPIOF
#define __4_IO3_GPIO_Port    GPIOF
#define __4_IO4_GPIO_Port    GPIOF
#define __HAL_RCC__4_IO_GPIO_Port_CLK_ENABLE()  __HAL_RCC_GPIOF_CLK_ENABLE() 

#define __4_IO1_GPIO_Pin    GPIO_PIN_12
#define __4_IO2_GPIO_Pin    GPIO_PIN_13
#define __4_IO3_GPIO_Pin    GPIO_PIN_14
#define __4_IO4_GPIO_Pin    GPIO_PIN_15

#define __1_IO1_H() HAL_GPIO_WritePin(__1_IO1_GPIO_Port, __1_IO1_GPIO_Pin, GPIO_PIN_SET)
#define	__1_IO1_L() HAL_GPIO_WritePin(__1_IO1_GPIO_Port, __1_IO1_GPIO_Pin, GPIO_PIN_RESET)
#define	__1_IO2_H() HAL_GPIO_WritePin(__1_IO2_GPIO_Port, __1_IO2_GPIO_Pin, GPIO_PIN_SET)
#define	__1_IO2_L() HAL_GPIO_WritePin(__1_IO2_GPIO_Port, __1_IO2_GPIO_Pin, GPIO_PIN_RESET);
#define	__1_IO3_L() HAL_GPIO_WritePin(__1_IO3_GPIO_Port, __1_IO3_GPIO_Pin, GPIO_PIN_RESET);
#define	__1_IO3_H() HAL_GPIO_WritePin(__1_IO3_GPIO_Port, __1_IO3_GPIO_Pin, GPIO_PIN_SET);
#define	__1_IO4_H() HAL_GPIO_WritePin(__1_IO4_GPIO_Port, __1_IO4_GPIO_Pin, GPIO_PIN_SET);
#define	__1_IO4_L() HAL_GPIO_WritePin(__1_IO4_GPIO_Port, __1_IO4_GPIO_Pin, GPIO_PIN_RESET);

#define __2_IO1_H() HAL_GPIO_WritePin(__2_IO1_GPIO_Port, __2_IO1_GPIO_Pin, GPIO_PIN_SET)
#define	__2_IO1_L() HAL_GPIO_WritePin(__2_IO1_GPIO_Port, __2_IO1_GPIO_Pin, GPIO_PIN_RESET)
#define	__2_IO2_H() HAL_GPIO_WritePin(__2_IO2_GPIO_Port, __2_IO2_GPIO_Pin, GPIO_PIN_SET)
#define	__2_IO2_L() HAL_GPIO_WritePin(__2_IO2_GPIO_Port, __2_IO2_GPIO_Pin, GPIO_PIN_RESET);
#define	__2_IO3_L() HAL_GPIO_WritePin(__2_IO3_GPIO_Port, __2_IO3_GPIO_Pin, GPIO_PIN_RESET);
#define	__2_IO3_H() HAL_GPIO_WritePin(__2_IO3_GPIO_Port, __2_IO3_GPIO_Pin, GPIO_PIN_SET);
#define	__2_IO4_H() HAL_GPIO_WritePin(__2_IO4_GPIO_Port, __2_IO4_GPIO_Pin, GPIO_PIN_SET);
#define	__2_IO4_L() HAL_GPIO_WritePin(__2_IO4_GPIO_Port, __2_IO4_GPIO_Pin, GPIO_PIN_RESET);

#define __3_IO1_H() HAL_GPIO_WritePin(__3_IO1_GPIO_Port, __3_IO1_GPIO_Pin, GPIO_PIN_SET)
#define	__3_IO1_L() HAL_GPIO_WritePin(__3_IO1_GPIO_Port, __3_IO1_GPIO_Pin, GPIO_PIN_RESET)
#define	__3_IO2_H() HAL_GPIO_WritePin(__3_IO2_GPIO_Port, __3_IO2_GPIO_Pin, GPIO_PIN_SET)
#define	__3_IO2_L() HAL_GPIO_WritePin(__3_IO2_GPIO_Port, __3_IO2_GPIO_Pin, GPIO_PIN_RESET);
#define	__3_IO3_L() HAL_GPIO_WritePin(__3_IO3_GPIO_Port, __3_IO3_GPIO_Pin, GPIO_PIN_RESET);
#define	__3_IO3_H() HAL_GPIO_WritePin(__3_IO3_GPIO_Port, __3_IO3_GPIO_Pin, GPIO_PIN_SET);
#define	__3_IO4_H() HAL_GPIO_WritePin(__3_IO4_GPIO_Port, __3_IO4_GPIO_Pin, GPIO_PIN_SET);
#define	__3_IO4_L() HAL_GPIO_WritePin(__3_IO4_GPIO_Port, __3_IO4_GPIO_Pin, GPIO_PIN_RESET);

#define __4_IO1_H() HAL_GPIO_WritePin(__4_IO1_GPIO_Port, __4_IO1_GPIO_Pin, GPIO_PIN_SET)
#define	__4_IO1_L() HAL_GPIO_WritePin(__4_IO1_GPIO_Port, __4_IO1_GPIO_Pin, GPIO_PIN_RESET)
#define	__4_IO2_H() HAL_GPIO_WritePin(__4_IO2_GPIO_Port, __4_IO2_GPIO_Pin, GPIO_PIN_SET)
#define	__4_IO2_L() HAL_GPIO_WritePin(__4_IO2_GPIO_Port, __4_IO2_GPIO_Pin, GPIO_PIN_RESET);
#define	__4_IO3_L() HAL_GPIO_WritePin(__4_IO3_GPIO_Port, __4_IO3_GPIO_Pin, GPIO_PIN_RESET);
#define	__4_IO3_H() HAL_GPIO_WritePin(__4_IO3_GPIO_Port, __4_IO3_GPIO_Pin, GPIO_PIN_SET);
#define	__4_IO4_H() HAL_GPIO_WritePin(__4_IO4_GPIO_Port, __4_IO4_GPIO_Pin, GPIO_PIN_SET);
#define	__4_IO4_L() HAL_GPIO_WritePin(__4_IO4_GPIO_Port, __4_IO4_GPIO_Pin, GPIO_PIN_RESET);

void CAL_GPIO_Stepping_Motor_Init(void);
void CAL_GPIO1_Stepping_Motor_Forward(unsigned int Speed,unsigned int Angle);
void CAL_GPIO1_Stepping_Motor_UnForward(unsigned int Speed,unsigned int Angle);
void CAL_GPIO2_Stepping_Motor_Forward(unsigned int Speed,unsigned int Angle);
void CAL_GPIO2_Stepping_Motor_UnForward(unsigned int Speed,unsigned int Angle);
void CAL_GPIO3_Stepping_Motor_Forward(unsigned int Speed,unsigned int Angle);
void CAL_GPIO3_Stepping_Motor_UnForward(unsigned int Speed,unsigned int Angle);
void CAL_GPIO4_Stepping_Motor_Forward(unsigned int Speed,unsigned int Angle);
void CAL_GPIO4_Stepping_Motor_UnForward(unsigned int Speed,unsigned int Angle);
void Stepping_motor_test(void);
#endif /* __CAL_GPIO_KEY_H */

