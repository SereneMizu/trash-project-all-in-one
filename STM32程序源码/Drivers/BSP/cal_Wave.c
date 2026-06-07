#include <cal_Wave.h>
#include "./SYSTEM/delay/delay.h"
#include "stm32f1xx_hal.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/LCD/lcd.h"

uint8_t hex_Return_Wave_Array[] = {0x3F, 0xFF};
uint8_t hex = 0xFE;
extern task task_temp;
extern UART_HandleTypeDef g_uart1_handle;
void CAL_GPIO_Wave_Init(void)
{ 
		GPIO_InitTypeDef gpio_init_struct;
    Trig1_GPIO_CLK_ENABLE(); 
    Trig2_GPIO_CLK_ENABLE();
    Trig3_GPIO_CLK_ENABLE();
    Trig4_GPIO_CLK_ENABLE();	
	
    gpio_init_struct.Pin = Trig1_Pin;                   
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(Trig1_Port, &gpio_init_struct);     
	
    gpio_init_struct.Pin = Trig2_Pin;                   
    HAL_GPIO_Init(Trig2_Port, &gpio_init_struct);     
	
    gpio_init_struct.Pin = Trig3_Pin;                   
    HAL_GPIO_Init(Trig3_Port, &gpio_init_struct);     
		
    gpio_init_struct.Pin = Trig4_Pin;                   
    HAL_GPIO_Init(Trig4_Port, &gpio_init_struct);     
}

void CAL_Wave_1_Start(){
  HAL_GPIO_WritePin(Trig1_Port,Trig1_Pin,GPIO_PIN_SET);
	delay_ms(20);
	HAL_GPIO_WritePin(Trig1_Port,Trig1_Pin,GPIO_PIN_RESET);
}

void CAL_Wave_2_Start(){
  HAL_GPIO_WritePin(Trig2_Port,Trig2_Pin,GPIO_PIN_SET);
	delay_ms(20);
	HAL_GPIO_WritePin(Trig2_Port,Trig2_Pin,GPIO_PIN_RESET);
}

void CAL_Wave_3_Start(){
  HAL_GPIO_WritePin(Trig3_Port,Trig3_Pin,GPIO_PIN_SET);
	delay_ms(20);
	HAL_GPIO_WritePin(Trig3_Port,Trig3_Pin,GPIO_PIN_RESET);
	
}


void CAL_Wave_4_Start(){
  HAL_GPIO_WritePin(Trig4_Port,Trig4_Pin,GPIO_PIN_SET);
	delay_ms(20);
	HAL_GPIO_WritePin(Trig4_Port,Trig4_Pin,GPIO_PIN_RESET);
	
}

void Upload_Wave_task(){
	int i;
	uint8_t tasktemp2[2];
	tasktemp2[0] = 0xFD;
	tasktemp2[1] = 0xFF;
	//#if 0
	   for(i = 0;i < 51;i++){
			 if((task_temp.signal & 0x01) != 1){
			 CAL_Wave_1_Start();
			 delay_ms(500);
				 //printf("1  testing!\r\n");
				 if(i == 50){
					 HAL_UART_Transmit(&g_uart1_handle,(uint8_t*)tasktemp2, 2, 1000); 
					 return;
				 }
			 }
			 else{
				  
			    break;
			 }
		 }
	//#endif
    for(i = 0;i < 51;i++){
			 //printf("%d",task_temp.signal);
			 if((task_temp.signal & 0x02) == 0){
			 CAL_Wave_2_Start();
			 delay_ms(200);
				 if(i == 50){
					 HAL_UART_Transmit(&g_uart1_handle,(uint8_t*)tasktemp2, 2, 1000); 
					 return;
				 }
			 }
			 else{
			    break;
			 }
		 }
		 for(i = 0;i < 51;i++){
			 if((task_temp.signal & 0x04) == 0){
			 CAL_Wave_3_Start();
			 delay_ms(200);
				 if(i == 50){
					 HAL_UART_Transmit(&g_uart1_handle,(uint8_t*)tasktemp2, 2, 1000); 
					 return;
				 }
			 }
			 else{
			    break;
			 }
		 }
		 for(i = 0;i < 51;i++){
			 if((task_temp.signal & 0x08) == 0){
			 CAL_Wave_4_Start();
			 delay_ms(200);
				 if(i == 50){
					 HAL_UART_Transmit(&g_uart1_handle,(uint8_t*)tasktemp2, 2, 1000); 
					 return;
				 }
			 }
			 else{
			    break;
			 }
		 }
		 //#endif
	 }
void adc_task(){
	uint16_t adcx,i;
	uint8_t m;
    float temp;
	 uint8_t tasktemp[4];
		 i = adc_get_result_average(ADC_ADCX_CHY, 10);
		 adcx = i;
		  lcd_show_xnum(134, 110, adcx, 5, 16, 0, BLUE);      /* 显示ADCC采样后的原始值 */
 
        temp = (float)adcx * (3.3 / 4096);                  /* 获取计算后的带小数的实际电压值，比如3.1111 */
        adcx = temp;                                        /* 赋值整数部分给adcx变量，因为adcx为u16整形 */
	      m = (i *256)/(4096);
				task_temp.Content_Yanwu = m;
        lcd_show_xnum(134, 130, adcx, 1, 16, 0, BLUE);      /* 显示电压值的整数部分，3.1111的话，这里就是显示3 */
         
        temp -= adcx;                                       /* 把已经显示的整数部分去掉，留下小数部分，比如3.1111-3=0.1111 */
        temp *= 1000;                                       /* 小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。 */
        lcd_show_xnum(150, 130, temp, 3, 16, 0X80, BLUE);   /* 显示小数部分（前面转换为了整形显示），这里显示的就是111. */
		 
		 i = adc_get_result_average(ADC_ADCX_CHX, 10);
		    adcx = i;
		    temp = (float)adcx * (3.3 / 4096); 
		    adcx = temp;                                        /* 赋值整数部分给adcx变量，因为adcx为u16整形 */
	      m = (i *256)/(4096);
				task_temp.Content_Jiawan = m;
        lcd_show_xnum(134, 150, adcx, 1, 16, 0, BLUE);      /* 显示电压值的整数部分，3.1111的话，这里就是显示3 */
        
        temp -= adcx;                                       /* 把已经显示的整数部分去掉，留下小数部分，比如3.1111-3=0.1111 */
        temp *= 1000;                                       /* 小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。 */
        lcd_show_xnum(150, 150, temp, 3, 16, 0X80, BLUE);   /* 显示小数部分（前面转换为了整形显示），这里显示的就是111. */
		 
		 tasktemp[0] = 0xFE;
		 tasktemp[1] = task_temp.Content_Jiawan;
		 tasktemp[2] = task_temp.Content_Yanwu;
		 tasktemp[3] = 0xFF;
		 //printf("%c%d%d%d%d%d%d%d%c\r\n",0xff,task_temp.Content_Jiawan,task_temp.Content_Yanwu,task_temp.Height_chuyu,task_temp.Height_kehuishou,task_temp.Height_qita,task_temp.Height_youhai,hex,0xFE);
		 HAL_UART_Transmit(&g_uart1_handle,(uint8_t*)tasktemp, 4, 1000); 
		//printf(【);
		 task_temp.signal = 0;
}