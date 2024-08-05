#include "stm32f1xx_hal.h"
#include "lib/capbutn/capbutn.h"
#include "lib/type/lib_type.h"
#include "tim.h"
#include "freeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "lib/debug/lib_debug.h"

#if CAPBUTN_DEBUG || 0
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* CAPBUTN */



#define TOUCHPAD_GPIO_RCC_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define TOUCHPAD_GPIO_PIN                    GPIO_PIN_1
#define TOUCHPAD_GPIO                        GPIOA
#define TOUCHPAD_TIM_CHANNEL                 TIM_CHANNEL_2
#define TOUCHPAD_TIM_FLAG_CCR                TIM_FLAG_CC2


uint32_t capture_time = 0;
uint32_t charge_time = 65;
//static uint16_t g_ir_stat = 0;


static void TPAD_Reset(void)
{
     /* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStruct;
	
	/* 使能电容按键引脚对应IO端口时钟 */  
  TOUCHPAD_GPIO_RCC_CLK_ENABLE();
  
  /* 设置引脚输出为低电平 */
  HAL_GPIO_WritePin(TOUCHPAD_GPIO, TOUCHPAD_GPIO_PIN, GPIO_PIN_RESET);  
  
  /* 设定电容按键对应引脚IO编号 */
  GPIO_InitStruct.Pin = TOUCHPAD_GPIO_PIN;
  /* 设定电容按键对应引脚IO为输出模式 */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  /* 设定电容按键对应引脚IO操作速度 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  /* 初始化电容按键对应引脚IO */
  HAL_GPIO_Init(TOUCHPAD_GPIO, &GPIO_InitStruct);  

	osDelay(5);

	__HAL_TIM_SET_COUNTER(&htim2,0); // 清零定时器计数  
  __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE|TIM_FLAG_CC2);//清除中断标志
  
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TOUCHPAD_GPIO, &GPIO_InitStruct);
  
  HAL_TIM_IC_Start(&htim2,TOUCHPAD_TIM_CHANNEL);  
}

status_t capbutn_get_value (void)
{
    // 检查捕获的值
    TPAD_Reset();
    capture_time = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);

    TRACE("capture_time : %d\n", capture_time);
    if (capture_time < charge_time)
    {
        TRACE("capture_time : %d\n", capture_time);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 100);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 100);
    }
    else
    {
        TRACE("capture_time : %d\n", capture_time);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);

    }
    return status_ok;

}
