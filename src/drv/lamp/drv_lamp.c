#include "stm32f1xx_hal.h"
#include "tim.h"
#include "drv/lamp/drv_lamp.h"

void led_color()
{
  static uint16_t color = 0;
      
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
}

void led_brightness()
{
static uint16_t brightness = 0;
    

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 100);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);

}