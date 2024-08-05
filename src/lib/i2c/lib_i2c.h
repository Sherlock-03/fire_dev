/*
	i2c.h

	Implementation file for i2c module
*/

/* Copyright © 2024 Jasper. All rights reserved. */

/*
	modification history
	--------------------
	01a, 18May24, Jasper Created
*/
#ifndef __LIB_I2C_H
#define __LIB_I2C_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Includes */
#include "lib/type/lib_type.h"
#include "app/arm_application/config.h"

#if SORTWARE_I2C_ENABLE

/* Defines */
//#if 0
///* AHT30 */
//#define I2C_SCL_PORT GPIOB
//#define I2C_SCL_PIN GPIO_PIN_13
//#define I2C_SDA_PORT GPIOB
//#define I2C_SDA_PIN GPIO_PIN_12

//#else
///* DS1338 */
//#define I2C_SCL_PORT GPIOA
//#define I2C_SCL_PIN GPIO_PIN_5
//#define I2C_SDA_PORT GPIOA
//#define I2C_SDA_PIN GPIO_PIN_4

//#endif

///* YH-MPU6050 */
#define I2C_SCL_PORT GPIOB
#define I2C_SCL_PIN  GPIO_PIN_6
#define I2C_SDA_PORT GPIOB
#define I2C_SDA_PIN  GPIO_PIN_7

#define I2C_SCL(state) HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN, (state ? GPIO_PIN_SET : GPIO_PIN_RESET))
#define I2C_SDA(state) HAL_GPIO_WritePin(I2C_SDA_PORT, I2C_SDA_PIN, (state ? GPIO_PIN_SET : GPIO_PIN_RESET))
#define I2C_SDA_READ() HAL_GPIO_ReadPin(I2C_SDA_PORT, I2C_SDA_PIN)

#define USE_SYS_TICK_DELAY_US 0

	typedef enum
	{
		high = 1,
		low = 0
	} i2c_line_status_t;

	status_t i2c_start(void);
	status_t i2c_stop(void);
	status_t i2c_write_byte(uint8_t data);
	status_t i2c_read_byte(uint8_t *data, uint8_t ack);
	status_t i2c_write_data(uint8_t device_address, uint8_t *data, uint16_t length);
	status_t i2c_read_data(uint8_t device_address, uint8_t *data, uint16_t length, uint8_t ack);
	status_t i2c_write_register(uint8_t device_address, uint8_t register_address, uint8_t *data, uint8_t length);
	status_t i2c_read_register(uint8_t device_address, uint8_t register_address, uint8_t *data, uint8_t length);

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LIB_I2C_H */
