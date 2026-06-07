/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-23
 * @brief       单通道ADC采集 实验
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
 ****************************************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/TIMER/btim.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/ADC/adc.h"
#include <cal_Stepping_Motor.h>
#include "./BSP/EXTI/exti.h"
#include <cal_Wave.h>

task task_temp;

int main(void)
{
	  int i = 1;
    task_temp.signal = 0;
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
    delay_init(72);                         /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
	  btim_timx_int_init(5000,7199);
    led_init();                             /* 初始化LED */
    lcd_init();                             /* 初始化LCD */
    adc_init();                             /* 初始化ADC */
    CAL_GPIO_Stepping_Motor_Init();
	  extix_init();
	  CAL_GPIO_Wave_Init();
    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "ADC TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);
    lcd_show_string(30, 110, 200, 16, 16, "ADC1_CH1_VAL:", BLUE);
    lcd_show_string(30, 130, 200, 16, 16, "ADC1_CH1_VOL:0.000V", BLUE); /* 先在固定位置显示小数点 */
  //CAL_GPIO1_Stepping_Motor_UnForward(2,15);
	/*
	CAL_GPIO1_Stepping_Motor_UnForward(2,90);
					CAL_GPIO2_Stepping_Motor_UnForward(2,100);
					CAL_GPIO3_Stepping_Motor_UnForward(2,90);
					CAL_GPIO4_Stepping_Motor_UnForward(2,110);
					*/
					//CAL_GPIO3_Stepping_Motor_UnForward(2,40);
    while (1)
    {
			//CAL_Wave_1_Start();
			  if(i == 10){
          Upload_Wave_task();
					adc_task();
					i = 0;
				}
				else{
					Upload_Wave_task();
					i++;
				}
        LED0_TOGGLE();
        delay_ms(200);
			  UART_Task();
    }
}



















