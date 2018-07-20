/*
 * skynet sensor
 *
 * Copyright (c) 2018, longfeng.xiao <xlongfeng@126.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef __OS_H
#define __OS_H

#ifdef __linux__

#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

__BEGIN_DECLS

void _ultoa(unsigned long value, char* string, unsigned char radix);
void _ltoa(long value, char* string, unsigned char radix);

typedef void (*pfn_outputchar)(char c, void* p);

int sprintf_small(char *buf, const char *fmt,  ...);
void printf_small(char *fmt, ... );
#define hdprintf(args...)       printf_small(args)

#define watchdog()

void os_init(void);

#define TRUE                    true
#define FALSE                   false

#define GPIO_DeInit(a)          printf("GPIO_DeInit(%s)\n", #a)
#define GPIO_Init(a, b, c)      printf("GPIO_Init(%s, %s, %s)\n", #a, #b, #c)

#ifdef DEBUG
#define GPIO_WriteHigh(a, b)    printf("GPIO_WriteHigh(%s, %s)\n", #a, #b)
#define GPIO_WriteLow(a, b)     printf("GPIO_WriteLow(%s, %s)\n", #a, #b)
#define GPIO_WriteReverse(a, b) printf("GPIO_WriteReverse(%s, %s)\n", #a, #b)
#else
#define GPIO_WriteHigh(a, b)
#define GPIO_WriteLow(a, b)
#define GPIO_WriteReverse(a, b)
#endif

__END_DECLS

#else

#include "stm8s.h"
#include "stm8s_it.h"

int sprintf_small(char *buf, const char *fmt,  ...);
#define hdprintf(args...)       uart_mode_transmit();   \
                                printf_small(args);     \
                                uart_mode_receive()

void watchdog(void);
void uart_mode_transmit(void);
void uart_mode_receive(void);
void os_init(void);

#endif

#endif // __OS_H
