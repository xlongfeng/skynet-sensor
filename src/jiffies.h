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

#ifndef __JIFFIES_H
#define __JIFFIES_H

#include <stdint.h>

#define HZ                      (1000)

/* Parameters used to convert the timespec values: */
#define MSEC_PER_SEC            1000L
#define USEC_PER_MSEC           1000L
#define USEC_PER_SEC            1000000L

/*
 *	These inlines deal with timer wrapping correctly. You are
 *	strongly encouraged to use them
 *	1. Because people otherwise forget
 *	2. Because if the timer wrap changes in future you won't have to
 *	   alter your driver code.
 *
 * time_after(a,b) returns true if the time a is after time b.
 *
 * Do this with "<0" and ">=0" to only test the sign of the result. A
 * good compiler would generate better code (and a really good compiler
 * wouldn't care). Gcc is currently neither.
 */
#define time_after(a,b)		((int32_t)(b) - (int32_t)(a) < 0)
#define time_before(a,b)	time_after(b,a)

#define time_after_eq(a,b)	((int32_t)(a) - (int32_t)(b) >= 0)
#define time_before_eq(a,b)	time_after_eq(b,a)

/*
 * Calculate whether a is in the range of [b, c].
 */
#define time_in_range(a,b,c) \
    (time_after_eq(a,b) && \
    time_before_eq(a,c))

/*
 * Calculate whether a is in the range of [b, c).
 */
#define time_in_range_open(a,b,c) \
    (time_after_eq(a,b) && \
    time_before(a,c))

/*
 * Change timeval to jiffies, trying to avoid the
 * most obvious overflows..
 *
 * And some not so obvious.
 *
 * Note that we don't want to return LONG_MAX, because
 * for various timeout reasons we often end up having
 * to wait "jiffies+1" in order to guarantee that we wait
 * at _least_ "jiffies" - so "jiffies+1" had better still
 * be positive.
 */
#define MAX_JIFFY_OFFSET    ((INT32_MAX >> 1)-1)

extern volatile uint32_t jiffies;

/*
 * Convert various time units to each other:
 */
uint32_t jiffies_to_msecs(const uint32_t j);
uint32_t jiffies_to_usecs(const uint32_t j);
uint32_t msecs_to_jiffies(const uint32_t m);
uint32_t usecs_to_jiffies(const uint32_t u);

#endif // __JIFFIES_H
