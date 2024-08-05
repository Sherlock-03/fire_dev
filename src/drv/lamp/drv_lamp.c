#include "stm32f1xx_hal.h"
#include "tim.h"
#include "drv/lamp/drv_lamp.h"
#include "lib/cli/lib_cli.h"
#include <stdlib.h>

/* global variable */
static uint16_t g_last_color = 50;
static uint16_t g_last_brightness = 0;

void led_init(void)
{
    set_led_color(g_last_color);
    set_led_brightness(g_last_brightness);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

void set_led_color(uint16_t color)
{
    g_last_color = color;
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, color * g_last_brightness / 100);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, (100-color) * g_last_brightness / 100);
}

void set_led_brightness(uint16_t brightness)
{
    g_last_brightness = brightness;
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, g_last_color * brightness / 100);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, (100 - g_last_color) * brightness / 100);

}

static void prv_cli_cmd_set_led_color(cli_printf cliprintf, int argc, char **argv)
{
    if (argc == 2) {
        uint16_t color = atoi(argv[1]);
        if (!(color>100)) {
            set_led_color(color);
        } 
        else {
            cliprintf("error: wrong parameters\r\n");
        }
    }
    else {
        cliprintf("CLI error: wrong parameters\r\n");
    }
    return;
}
CLI_CMD_EXPORT(set_led_color, set_led_color, prv_cli_cmd_set_led_color)

static void prv_cli_cmd_set_led_brightness(cli_printf cliprintf, int argc, char **argv)
{
    if (argc == 2) {
        uint16_t brightness = atoi(argv[1]);
        if (!(brightness>100)) {
            set_led_brightness(brightness);
        } 
        else {
            cliprintf("error: wrong parameters\r\n");
        }
    }
    else {
        cliprintf("CLI error: wrong parameters\r\n");
    }
    return;
}
CLI_CMD_EXPORT(set_led_brightness, set_led_brightness, prv_cli_cmd_set_led_brightness)
