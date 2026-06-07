
#ifndef __CAL_WAVE_H
#define __CAL_WAVE_H
#include "./SYSTEM/sys/sys.h"
typedef struct task{
	 uint8_t Content_Yanwu;
	 uint8_t Content_Jiawan;
	 uint8_t Height_chuyu;
	 uint8_t Height_youhai;
	 uint8_t Height_qita;
	 uint8_t Height_kehuishou;
	 uint8_t signal;
 }task;

#define Trig1_Pin GPIO_PIN_9
#define Trig1_Port GPIOG
#define Trig1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)      

#define Trig2_Pin GPIO_PIN_2
#define Trig2_Port GPIOE
#define Trig2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define Trig3_Pin GPIO_PIN_1
#define Trig3_Port GPIOE
#define Trig3_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define Trig4_Pin GPIO_PIN_0
#define Trig4_Port GPIOE
#define Trig4_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

void CAL_Wave_1_Start(void);
void CAL_Wave_2_Start(void);
void CAL_Wave_3_Start(void);
void CAL_Wave_4_Start(void);

void CAL_GPIO_Wave_Init(void);
void Upload_Wave_task(void);
void adc_task(void);
#endif /* __CAL_GPIO_KEY_H */


