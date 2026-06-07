#include <cal_Stepping_Motor.h>
#include "./SYSTEM/delay/delay.h"
#include "stm32f1xx_hal.h"
#include "./BSP/KEY/key.h"

void CAL_GPIO_Stepping_Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC__1_IO_GPIO_Port_CLK_ENABLE();  
	__HAL_RCC__2_IO_GPIO_Port_CLK_ENABLE();
	__HAL_RCC__3_IO_GPIO_Port_CLK_ENABLE();
	__HAL_RCC__4_IO_GPIO_Port_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE() ;
  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 */
  GPIO_InitStruct.Pin = __1_IO2_GPIO_Pin|__1_IO3_GPIO_Pin|__1_IO4_GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = __1_IO1_GPIO_Pin;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOG, __1_IO1_GPIO_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, __1_IO2_GPIO_Pin|__1_IO3_GPIO_Pin|__1_IO4_GPIO_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(__1_IO1_GPIO_Port, __1_IO4_GPIO_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = __2_IO1_GPIO_Pin;
	HAL_GPIO_Init(__2_IO1_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(__2_IO1_GPIO_Port, __2_IO1_GPIO_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = __2_IO2_GPIO_Pin;
	HAL_GPIO_Init(__2_IO2_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(__2_IO2_GPIO_Port, __2_IO2_GPIO_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = __2_IO3_GPIO_Pin;
	HAL_GPIO_Init(__2_IO3_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(__2_IO3_GPIO_Port, __2_IO3_GPIO_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = __2_IO4_GPIO_Pin;
	HAL_GPIO_Init(__2_IO4_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(__2_IO4_GPIO_Port, __2_IO4_GPIO_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = __3_IO1_GPIO_Pin;
	HAL_GPIO_Init(__3_IO1_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(__3_IO1_GPIO_Port, __3_IO1_GPIO_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = __3_IO2_GPIO_Pin;
	HAL_GPIO_Init(__3_IO2_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(__3_IO2_GPIO_Port, __3_IO2_GPIO_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = __3_IO3_GPIO_Pin;
	HAL_GPIO_Init(__3_IO3_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(__3_IO3_GPIO_Port, __3_IO3_GPIO_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = __3_IO4_GPIO_Pin;
	HAL_GPIO_Init(__3_IO4_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(__3_IO4_GPIO_Port, __3_IO4_GPIO_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = __4_IO1_GPIO_Pin;
	HAL_GPIO_Init(__4_IO1_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(__4_IO1_GPIO_Port, __4_IO1_GPIO_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = __4_IO2_GPIO_Pin;
	HAL_GPIO_Init(__4_IO2_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(__4_IO2_GPIO_Port, __4_IO2_GPIO_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = __4_IO3_GPIO_Pin;
	HAL_GPIO_Init(__4_IO3_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(__4_IO3_GPIO_Port, __4_IO3_GPIO_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = __4_IO4_GPIO_Pin;
	HAL_GPIO_Init(__4_IO4_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(__4_IO4_GPIO_Port, __4_IO4_GPIO_Pin, GPIO_PIN_RESET);
}


void CAL_GPIO1_Stepping_Motor_Forward(unsigned int Speed,unsigned int Angle)
{
	unsigned int i = 1;
	double n = (Angle/5.625)*80;
		 while(n-- > 0){
		 if(i == 1){
				 __1_IO1_H();
				 __1_IO2_L();
				 __1_IO3_L();
				 __1_IO4_L();
			 }
			if(i == 2){
				 __1_IO1_H();
				 __1_IO2_H();
				 __1_IO3_L();
				 __1_IO4_L();
			 }
			 if(i == 3){
				 __1_IO1_L();
				 __1_IO2_H();
				 __1_IO3_L();
				 __1_IO4_L();
			 }
			 if(i == 4){
				 __1_IO1_L();
				 __1_IO2_H();
				 __1_IO3_H();
				 __1_IO4_L();
			 }
			 if(i == 5){
				 __1_IO1_L();
				 __1_IO2_L();
				 __1_IO3_H();
				 __1_IO4_L();
			 }
			 if(i == 6){
				 __1_IO1_L();
				 __1_IO2_L();
				 __1_IO3_H();
				 __1_IO4_H();
			 }
			 if(i == 7){
				 __1_IO1_L();
				 __1_IO2_L();
				 __1_IO3_L();
				 __1_IO4_H();
			 }
			 if(i == 8){
				 __1_IO1_H();
				 __1_IO2_L();
				 __1_IO3_L();
				 __1_IO4_H();
			 }
			 HAL_Delay(1);
			 
		  ++i;
			 if(i == 9){
				 i = 1;
		 }
	 }
		__1_IO1_L();
		__1_IO2_L();
		__1_IO3_L();
		__1_IO4_L();
}

void CAL_GPIO1_Stepping_Motor_UnForward(unsigned int Speed,unsigned int Angle)
{
	unsigned int i = 1;
	double n = (Angle/5.625)*80;
		 while(n-- > 0){
		 if(i == 1){
				 __1_IO1_H();
				 __1_IO2_L();
				 __1_IO3_L();
				 __1_IO4_L();
			 }
			if(i == 2){
				 __1_IO1_H();
				 __1_IO2_L();
				 __1_IO3_L();
				 __1_IO4_H();
			 }
			 if(i == 3){
				 __1_IO1_L();
				 __1_IO2_L();
				 __1_IO3_L();
				 __1_IO4_H();
			 }
			 if(i == 4){
				 __1_IO1_L();
				 __1_IO2_L();
				 __1_IO3_H();
				 __1_IO4_H();
			 }
			 if(i == 5){
				 __1_IO1_L();
				 __1_IO2_L();
				 __1_IO3_H();
				 __1_IO4_L();
			 }
			 if(i == 6){
				 __1_IO1_L();
				 __1_IO2_H();
				 __1_IO3_H();
				 __1_IO4_L();
			 }
			 if(i == 7){
				 __1_IO1_L();
				 __1_IO2_H();
				 __1_IO3_L();
				 __1_IO4_L();
			 }
			 if(i == 8){
				 __1_IO1_H();
				 __1_IO2_H();
				 __1_IO3_L();
				 __1_IO4_L();
			 }	 
		  HAL_Delay(1);
		  ++i;
			 if(i == 9){
				 i = 1;
		 }
	 }
		__1_IO1_L();
		__1_IO2_L();
		__1_IO3_L();
		__1_IO4_L();

}


void CAL_GPIO2_Stepping_Motor_Forward(unsigned int Speed,unsigned int Angle)
{
	unsigned int i = 1;
	double n = (Angle/5.625)*80;
		 while(n-- > 0){
		 if(i == 1){
				 __2_IO1_H();
				 __2_IO2_L();
				 __2_IO3_L();
				 __2_IO4_L();
			 }
			if(i == 2){
				 __2_IO1_H();
				 __2_IO2_H();
				 __2_IO3_L();
				 __2_IO4_L();
			 }
			 if(i == 3){
				 __2_IO1_L();
				 __2_IO2_H();
				 __2_IO3_L();
				 __2_IO4_L();
			 }
			 if(i == 4){
				 __2_IO1_L();
				 __2_IO2_H();
				 __2_IO3_H();
				 __2_IO4_L();
			 }
			 if(i == 5){
				 __2_IO1_L();
				 __2_IO2_L();
				 __2_IO3_H();
				 __2_IO4_L();
			 }
			 if(i == 6){
				 __2_IO1_L();
				 __2_IO2_L();
				 __2_IO3_H();
				 __2_IO4_H();
			 }
			 if(i == 7){
				 __2_IO1_L();
				 __2_IO2_L();
				 __2_IO3_L();
				 __2_IO4_H();
			 }
			 if(i == 8){
				 __2_IO1_H();
				 __2_IO2_L();
				 __2_IO3_L();
				 __2_IO4_H();
			 }	 
		  HAL_Delay(1);
		  ++i;
			 if(i == 9){
				 i = 1;
		 }
	 }
		__2_IO1_L();
		__2_IO2_L();
		__2_IO3_L();
		__2_IO4_L();
}

void CAL_GPIO2_Stepping_Motor_UnForward(unsigned int Speed,unsigned int Angle)
{
	
	unsigned int i = 1;
	double n = (Angle/5.625)*80;
		 while(n-- > 0){
		 if(i == 1){
				 __2_IO1_H();
				 __2_IO2_L();
				 __2_IO3_L();
				 __2_IO4_L();
			 }
			if(i == 2){
				 __2_IO1_H();
				 __2_IO2_L();
				 __2_IO3_L();
				 __2_IO4_H();
			 }
			 if(i == 3){
				 __2_IO1_L();
				 __2_IO2_L();
				 __2_IO3_L();
				 __2_IO4_H();
			 }
			 if(i == 4){
				 __2_IO1_L();
				 __2_IO2_L();
				 __2_IO3_H();
				 __2_IO4_H();
			 }
			 if(i == 5){
				 __2_IO1_L();
				 __2_IO2_L();
				 __2_IO3_H();
				 __2_IO4_L();
			 }
			 if(i == 6){
				 __2_IO1_L();
				 __2_IO2_H();
				 __2_IO3_H();
				 __2_IO4_L();
			 }
			 if(i == 7){
				 __2_IO1_L();
				 __2_IO2_H();
				 __2_IO3_L();
				 __2_IO4_L();
			 }
			 if(i == 8){
				 __2_IO1_H();
				 __2_IO2_H();
				 __2_IO3_L();
				 __2_IO4_L();
			 }	 
		  HAL_Delay(1);
		  ++i;
			 if(i == 9){
				 i = 1;
		 }
	 }
		__2_IO1_L();
		__2_IO2_L();
		__2_IO3_L();
		__2_IO4_L();

}
void CAL_GPIO3_Stepping_Motor_Forward(unsigned int Speed,unsigned int Angle)
{
	unsigned int i = 1;
	double n = (Angle/5.625)*80;
		 while(n-- > 0){
		 if(i == 1){
				 __3_IO1_H();
				 __3_IO2_L();
				 __3_IO3_L();
				 __3_IO4_L();
			 }
			if(i == 2){
				 __3_IO1_H();
				 __3_IO2_L();
				 __3_IO3_L();
				 __3_IO4_H();
			 }
			 if(i == 3){
				 __3_IO1_L();
				 __3_IO2_L();
				 __3_IO3_L();
				 __3_IO4_H();
			 }
			 if(i == 4){
				 __3_IO1_L();
				 __3_IO2_L();
				 __3_IO3_H();
				 __3_IO4_H();
			 }
			 if(i == 5){
				 __3_IO1_L();
				 __3_IO2_L();
				 __3_IO3_H();
				 __3_IO4_L();
			 }
			 if(i == 6){
				 __3_IO1_L();
				 __3_IO2_H();
				 __3_IO3_H();
				 __3_IO4_L();
			 }
			 if(i == 7){
				 __3_IO1_L();
				 __3_IO2_H();
				 __3_IO3_L();
				 __3_IO4_L();
			 }
			 if(i  == 8){
				 __3_IO1_H();
				 __3_IO2_H();
				 __3_IO3_L();
				 __3_IO4_L();
			 }	 
		  HAL_Delay(1);
		  ++i;
			 if(i == 9){
				 i = 1;
		 }
	 }
		__3_IO1_L();
		__3_IO2_L();
		__3_IO3_L();
		__3_IO4_L();
}

void CAL_GPIO3_Stepping_Motor_UnForward(unsigned int Speed,unsigned int Angle)
{
	
		 unsigned int i = 1;
	double n = (Angle/5.625)*80;
		 while(n-- > 0){
		 if(i == 1){
				 __3_IO1_H();
				 __3_IO2_L();
				 __3_IO3_L();
				 __3_IO4_L();
			 }
			if(i == 2){
				 __3_IO1_H();
				 __3_IO2_H();
				 __3_IO3_L();
				 __3_IO4_L();
			 }
			 if(i == 3){
				 __3_IO1_L();
				 __3_IO2_H();
				 __3_IO3_L();
				 __3_IO4_L();
			 }
			 if(i == 4){
				 __3_IO1_L();
				 __3_IO2_H();
				 __3_IO3_H();
				 __3_IO4_L();
			 }
			 if(i == 5){
				 __3_IO1_L();
				 __3_IO2_L();
				 __3_IO3_H();
				 __3_IO4_L();
			 }
			 if(i == 6){
				 __3_IO1_L();
				 __3_IO2_L();
				 __3_IO3_H();
				 __3_IO4_H();
			 }
			 if(i == 7){
				 __3_IO1_L();
				 __3_IO2_L();
				 __3_IO3_L();
				 __3_IO4_H();
			 }
			 if(i == 8){
				 __3_IO1_H();
				 __3_IO2_L();
				 __3_IO3_L();
				 __3_IO4_H();
			 }	 
		  HAL_Delay(1);
		  ++i;
			 if(i == 9){
				 i = 1;
		 }
	 }
		__3_IO1_L();
		__3_IO2_L();
		__3_IO3_L();
		__3_IO4_L();

}
void CAL_GPIO4_Stepping_Motor_Forward(unsigned int Speed,unsigned int Angle)
{
	unsigned int i = 1;
	double n = (Angle/5.625)*80;
		 while(n-- > 0){
		 if(i == 1){
				 __4_IO1_H();
				 __4_IO2_L();
				 __4_IO3_L();
				 __4_IO4_L();
			 }
			if(i == 2){
				 __4_IO1_H();
				 __4_IO2_H();
				 __4_IO3_L();
				 __4_IO4_L();
			 }
			 if(i == 3){
				 __4_IO1_L();
				 __4_IO2_H();
				 __4_IO3_L();
				 __4_IO4_L();
			 }
			 if(i == 4){
				 __4_IO1_L();
				 __4_IO2_H();
				 __4_IO3_H();
				 __4_IO4_L();
			 }
			 if(i == 5){
				 __4_IO1_L();
				 __4_IO2_L();
				 __4_IO3_H();
				 __4_IO4_L();
			 }
			 if(i == 6){
				 __4_IO1_L();
				 __4_IO2_L();
				 __4_IO3_H();
				 __4_IO4_H();
			 }
			 if(i == 7){
				 __4_IO1_L();
				 __4_IO2_L();
				 __4_IO3_L();
				 __4_IO4_H();
			 }
			 if(i == 8){
				 __4_IO1_H();
				 __4_IO2_L();
				 __4_IO3_L();
				 __4_IO4_H();
			 }	 
		  HAL_Delay(1);
		  ++i;
			 if(i == 9){
				 i = 1;
		 }
	 }
		__4_IO1_L();
		__4_IO2_L();
		__4_IO3_L();
		__4_IO4_L();
}

void CAL_GPIO4_Stepping_Motor_UnForward(unsigned int Speed,unsigned int Angle)
{
	unsigned int i = 1;
	double n = (Angle/5.625)*80;
		 while(n-- > 0){
		 if(i == 1){
				 __4_IO1_H();
				 __4_IO2_L();
				 __4_IO3_L();
				 __4_IO4_L();
			 }
			if(i == 2){
				 __4_IO1_H();
				 __4_IO2_L();
				 __4_IO3_L();
				 __4_IO4_H();
			 }
			 if(i == 3){
				 __4_IO1_L();
				 __4_IO2_L();
				 __4_IO3_L();
				 __4_IO4_H();
			 }
			 if(i == 4){
				 __4_IO1_L();
				 __4_IO2_L();
				 __4_IO3_H();
				 __4_IO4_H();
			 }
			 if(i == 5){
				 __4_IO1_L();
				 __4_IO2_L();
				 __4_IO3_H();
				 __4_IO4_L();
			 }
			 if(i == 6){
				 __4_IO1_L();
				 __4_IO2_H();
				 __4_IO3_H();
				 __4_IO4_L();
			 }
			 if(i == 7){
				 __4_IO1_L();
				 __4_IO2_H();
				 __4_IO3_L();
				 __4_IO4_L();
			 }
			 if(i  == 8){
				 __4_IO1_H();
				 __4_IO2_H();
				 __4_IO3_L();
				 __4_IO4_L();
			 }	 
		  HAL_Delay(1);
		  ++i;
			 if(i == 9){
				 i = 1;
		 }
	 }
		__4_IO1_L();
		__4_IO2_L();
		__4_IO3_L();
		__4_IO4_L();

}

void Stepping_motor_test(){
		/*CAL_GPIO1_Stepping_Motor_Forward(2,90);
		HAL_Delay(200);
		CAL_GPIO1_Stepping_Motor_UnForward(2,90);
		HAL_Delay(200);
	CAL_GPIO2_Stepping_Motor_Forward(2,90);
		HAL_Delay(200);
		CAL_GPIO2_Stepping_Motor_UnForward(2,90);
		HAL_Delay(200);*/
	  //HAL_Delay(200000);
	  HAL_Delay(1000);
	  //CAL_GPIO2_Stepping_Motor_Forward(2,90);
		//HAL_Delay(7000);
	  CAL_GPIO2_Stepping_Motor_UnForward(2,90);
		HAL_Delay(20000);
	/*CAL_GPIO4_Stepping_Motor_Forward(2,90);
		HAL_Delay(200);
		CAL_GPIO4_Stepping_Motor_UnForward(2,90);
		HAL_Delay(200);  */
	}
	
