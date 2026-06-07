/**
 ****************************************************************************************************
 * @file        exti.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-19
 * @brief       外部中断 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20200420
 * 第一次发布
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/EXTI/exti.h"
#include "./BSP/KEY/key.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/TIMER/gtim.h"
#include <cal_Wave.h>

extern task task_temp;
void Echo_INT_IRQHandler(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

extern TIM_HandleTypeDef g_timx_handle; 
uint32_t Distance;
/**
 * @brief       KEY0 外部中断服务程序
 * @param       无
 * @retval      无
 */
void KEY0_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY0_INT_GPIO_PIN);         /* 调用中断处理公用函数 清除KEY0所在中断线 的中断标志位 */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY0_INT_GPIO_PIN);         /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}

/**
 * @brief       KEY1 外部中断服务程序
 * @param       无
 * @retval      无
 */
void KEY1_INT_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KEY1_INT_GPIO_PIN);         /* 调用中断处理公用函数 清除KEY1所在中断线 的中断标志位，中断下半部在HAL_GPIO_EXTI_Callback执行 */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);         /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}


/**
 * @brief       WK_UP 外部中断服务程序
 * @param       无
 * @retval      无
 */
void WKUP_INT_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(WKUP_INT_GPIO_PIN);        /* 调用中断处理公用函数 清除KEY_UP所在中断线 的中断标志位，中断下半部在HAL_GPIO_EXTI_Callback执行 */
    __HAL_GPIO_EXTI_CLEAR_IT(WKUP_INT_GPIO_PIN);        /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}


void EXTI15_10_IRQHandler(void)
{
	 //printf("no\r\n");
	 GPIO_TypeDef *GPIOx;
	 uint16_t GPIO_Pin = 0;
	 int i = 0;
	int m=0;
	 i = __HAL_GPIO_EXTI_GET_FLAG(Echo1_INT_GPIO_PIN);
	 if(i){
		 GPIOx = Echo1_INT_GPIO_PORT;
		 GPIO_Pin = Echo1_INT_GPIO_PIN;
		 m = 1;
	 }else{
		   i = __HAL_GPIO_EXTI_GET_FLAG(Echo2_INT_GPIO_PIN);
		   if(i){
		       GPIOx = Echo2_INT_GPIO_PORT;
		      GPIO_Pin = Echo2_INT_GPIO_PIN;
		     	 m = 2;
	     }else{
			     i = __HAL_GPIO_EXTI_GET_FLAG(Echo3_INT_GPIO_PIN);
		       if(i){
		           GPIOx = Echo3_INT_GPIO_PORT;
		           GPIO_Pin = Echo3_INT_GPIO_PIN;
		        	 m = 3;
	         } else{
						 	 i = __HAL_GPIO_EXTI_GET_FLAG(Echo4_INT_GPIO_PIN);
								if(i){
									GPIOx = Echo4_INT_GPIO_PORT;
									GPIO_Pin = Echo4_INT_GPIO_PIN;
									m = 4;
							}
		       }
		   }
	 }
	 if(!m){
		 __HAL_GPIO_EXTI_CLEAR_IT(Echo1_INT_GPIO_PIN); 
		 __HAL_GPIO_EXTI_CLEAR_IT(Echo2_INT_GPIO_PIN); 
		 __HAL_GPIO_EXTI_CLEAR_IT(Echo3_INT_GPIO_PIN); 
		 __HAL_GPIO_EXTI_CLEAR_IT(Echo4_INT_GPIO_PIN); 
		 //HAL_TIM_Base_Stop(&g_timx_handle);
		 return;
	 }
	 HAL_TIM_Base_Start(&g_timx_handle);
	 delay_us(2);
	//if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin)!=RESET)
	 //if(1)
	{
		//HAL_TIM_Base_Start(&g_timx_handle);
    while(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == SET); 
    HAL_TIM_Base_Stop(&g_timx_handle);
    Distance = __HAL_TIM_GET_COUNTER(&g_timx_handle);
    __HAL_TIM_SET_COUNTER(&g_timx_handle,0);
		if(Distance > 2 && Distance < 9)
		{
			if(m == 1){
			 task_temp.Height_chuyu = Distance;
			 task_temp.signal |= 0x01;
			 //printf("Distance:%d %d,%fcm\r\n",Distance,m,Distance*340/200.0);
			}
			if(m == 2){
			 task_temp.Height_kehuishou = Distance;
				task_temp.signal |= 0x02;
			 //printf("Distance:%d %d,%fcm\r\n",Distance,m,Distance*340/200.0);
			}
			if(m == 3){
			 task_temp.Height_qita = Distance;
				task_temp.signal |= 0x04;
			 //printf("Distance:%d %d,%fcm\r\n",Distance,m,Distance*340/200.0);
			}
			if(m == 4){
			 task_temp.Height_youhai = Distance;
				task_temp.signal |= 0x08;
			 //printf("Distance:%d %d,%fcm\r\n",Distance,m,Distance*340/200.0);
			}
		}
	}
	//else{
	//	    //HAL_TIM_Base_Stop(&g_timx_handle);
	//			printf("no responce,%d\r\n",m);
	//}
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);        
}
/**
 * @brief       中断服务程序中需要做的事情
                在HAL库中所有的外部中断服务函数都会调用此函数
 * @param       GPIO_Pin:中断引脚号
 * @retval      无
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(20);      /* 消抖 */
    switch(GPIO_Pin)
    {
        case KEY0_INT_GPIO_PIN:
            if (KEY0 == 0)
            {
                LED0_TOGGLE();  /* LED0 状态取反 */ 
                LED1_TOGGLE();  /* LED1 状态取反 */ 
            }
            break;
        case KEY1_INT_GPIO_PIN:
            if (KEY1 == 0)
            {
                LED0_TOGGLE();  /* LED0 状态取反 */ 
            }
            break;
        case WKUP_INT_GPIO_PIN:
            if (WK_UP == 1)
            {
                LED0_TOGGLE();  /* 蜂鸣器状态取反 */ 
            }
            break;
    }
}

/**
 * @brief       外部中断初始化程序
 * @param       无
 * @retval      无
 */
void extix_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    KEY0_GPIO_CLK_ENABLE();                                  /* KEY0时钟使能 */
    KEY1_GPIO_CLK_ENABLE();                                  /* KEY1时钟使能 */
    WKUP_GPIO_CLK_ENABLE();                                  /* WKUP时钟使能 */
    Echo1_INT_GPIO_CLK_ENABLE();
	  Echo2_INT_GPIO_CLK_ENABLE();
	  Echo3_INT_GPIO_CLK_ENABLE();
	  Echo4_INT_GPIO_CLK_ENABLE();
	
    gpio_init_struct.Pin = KEY0_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* 下升沿触发 */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY0_INT_GPIO_PORT, &gpio_init_struct);    /* KEY0配置为下降沿触发中断 */

    gpio_init_struct.Pin = KEY1_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* 下升沿触发 */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY1_INT_GPIO_PORT, &gpio_init_struct);    /* KEY1配置为下降沿触发中断 */
    
    gpio_init_struct.Pin = WKUP_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;             /* 上升沿触发 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(WKUP_GPIO_PORT, &gpio_init_struct);        /* WKUP配置为下降沿触发中断 */
		
		gpio_init_struct.Pin = Echo1_INT_GPIO_PIN; 
		gpio_init_struct.Mode = GPIO_MODE_IT_RISING;   
    gpio_init_struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(Echo1_INT_GPIO_PORT, &gpio_init_struct); 
		
	  gpio_init_struct.Pin = Echo2_INT_GPIO_PIN; 
		gpio_init_struct.Mode = GPIO_MODE_IT_RISING;   
    gpio_init_struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(Echo2_INT_GPIO_PORT, &gpio_init_struct); 
		
		gpio_init_struct.Pin = Echo3_INT_GPIO_PIN; 
		gpio_init_struct.Mode = GPIO_MODE_IT_RISING;   
    gpio_init_struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(Echo3_INT_GPIO_PORT, &gpio_init_struct); 
		
		gpio_init_struct.Pin = Echo4_INT_GPIO_PIN; 
		gpio_init_struct.Mode = GPIO_MODE_IT_RISING;   
    gpio_init_struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(Echo4_INT_GPIO_PORT, &gpio_init_struct); 
		
		HAL_NVIC_SetPriority(Echo1_INT_IRQn, 4, 2);               /* 抢占0，子优先级2 */
    HAL_NVIC_EnableIRQ(Echo1_INT_IRQn);                       /* 使能中断线4 */

    HAL_NVIC_SetPriority(Echo2_INT_IRQn, 4, 2);               /* 抢占0，子优先级2 */
    HAL_NVIC_EnableIRQ(Echo2_INT_IRQn);  
		
		HAL_NVIC_SetPriority(Echo3_INT_IRQn, 4, 2);               /* 抢占0，子优先级2 */
    HAL_NVIC_EnableIRQ(Echo3_INT_IRQn);  
		
		HAL_NVIC_SetPriority(Echo4_INT_IRQn, 4, 2);               /* 抢占0，子优先级2 */
    HAL_NVIC_EnableIRQ(Echo4_INT_IRQn);  

    HAL_NVIC_SetPriority(KEY0_INT_IRQn, 4, 2);               /* 抢占0，子优先级2 */
    HAL_NVIC_EnableIRQ(KEY0_INT_IRQn);                       /* 使能中断线4 */

    HAL_NVIC_SetPriority(KEY1_INT_IRQn, 4, 2);               /* 抢占1，子优先级2 */
    HAL_NVIC_EnableIRQ(KEY1_INT_IRQn);                       /* 使能中断线3 */

    HAL_NVIC_SetPriority(WKUP_INT_IRQn, 4, 2);               /* 抢占2，子优先级2 */
    HAL_NVIC_EnableIRQ(WKUP_INT_IRQn);                       /* 使能中断线0 */
}









