#ifndef __LED_BREATH_H__
#define __LED_BREATH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "lib/type/lib_type.h"

status_t breath_led_init(void);
void led_status(void);
void breathe_led(void);

#ifdef __cplusplus
}
#endif
#endif /*__LED_BREATH_H__*/
