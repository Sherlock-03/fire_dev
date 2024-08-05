/*
	type.h

	Common Type Defines Head File For The Whole Project
*/

/* Copyright © 2019 Jasper. All rights reserved. */

/*
	modification history
	--------------------
	01a, 15Jul19, Karl Created
	01b, 16May24, Jasper Reconstrured type library
*/

#ifndef __TYPE_H
#define __TYPE_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Includes */
#include <time.h>
#include <stdint.h>

	/* Types */
	typedef enum
	{
        status_err,
		status_ok
		
	} status_t;

	typedef uint8_t Bool_t;
	typedef struct tm Time_t;

	typedef int SOCKET;

/* Defines */
#ifndef TRUE
#define TRUE (1)
#endif
#ifndef FALSE
#define FALSE (0)
#endif
#ifndef NULL
#define NULL (0)
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET (-1)
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR (-1)
#endif

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef INOUT
#define INOUT
#endif

#ifndef SECTION
#define SECTION(x) __attribute__((section(x)))
#endif
#ifndef USED
#define USED __attribute__((used))
#endif
#ifndef ALIGN
#define ALIGN(n) __attribute__((aligned(n)))
#endif
#ifndef WEAK
#define WEAK __attribute__((weak))
#endif
#ifndef INLINE
#define INLINE static __inline
#endif
#ifndef API
#define API
#endif

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /*__TYPE_H__*/
