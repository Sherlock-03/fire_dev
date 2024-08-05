#include "stm32f1xx_hal.h"
#include "tim.h"
#include "lib/led/led_breath.h"
#include "lib/type/lib_type.h"
#include "freeRTOS.h"
#include "cmsis_os.h"
#include "task.h"
#include "lib/cli/lib_cli.h"
#include "stdlib.h"

static uint8_t g_breath_led_sw = 0;

/* Forward function */
static void breath_led_task(void *parameter);

status_t breath_led_init(void)
{
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
    xTaskCreate(breath_led_task, "breath_led_task", 128, NULL, tskIDLE_PRIORITY + 1, NULL);

    return status_ok;
}

static void breath_led_task(void *parameter)
{
    while (1)
    {
        if (g_breath_led_sw == 1) {
            breathe_led();
        }
        osDelay(10);
    }
}

void breathe_led(void) {
    static uint8_t direction = 1;
    static uint16_t brightness = 0;
    static uint8_t current_color = 0; // 0: Red, 1: Green, 2: Blue

    // 调整亮度
    if (direction) {
        brightness++;
        if (brightness >=100) {
            direction = 0;
        }
    } else {
        brightness--;
        if (brightness == 0) {
            direction = 1;
            current_color = (current_color + 1) % 3; // 切换到下一种颜色
        }
    }

    // 设置PWM占空比
    switch (current_color) {
        case 0: // Red
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100 - brightness);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 100);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 100);
            break;
        case 1: // Green
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 100 - brightness);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 100);
            break;
        case 2: // Blue
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 100);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 100 - brightness);
            break;
    }

//    HAL_Delay(10); // 控制呼吸灯速度
}

static void prv_cli_cmd_en_breath_led(cli_printf cliprintf, int argc, char **argv)
{
    if (2 == argc)
    {
        uint8_t on_off = atoi(argv[1]);
        g_breath_led_sw = on_off != 0 ? 1 : 0;
        if (g_breath_led_sw != 0) {
            cliprintf("Enable breath_led ok\n");
        }
        else {
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 100);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 100);
            cliprintf("Disable breath_led ok\r\n");
        }
    }
    else
    {
        cliprintf("CLI error: wrong parameters\r\n");
    }
    return;
}
CLI_CMD_EXPORT(en_breath_led, enable cli, prv_cli_cmd_en_breath_led)
