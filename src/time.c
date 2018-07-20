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

#include "jiffies.h"

volatile uint32_t jiffies = 0;

/*
 * Convert jiffies to milliseconds and back.
 *
 * Avoid unnecessary multiplications/divisions in the
 * two most common HZ cases:
 */
inline uint32_t jiffies_to_msecs(const uint32_t j)
{
#if HZ <= MSEC_PER_SEC && !(MSEC_PER_SEC % HZ)
    return (MSEC_PER_SEC / HZ) * j;
#elif HZ > MSEC_PER_SEC && !(HZ % MSEC_PER_SEC)
    return (j + (HZ / MSEC_PER_SEC) - 1)/(HZ / MSEC_PER_SEC);
#endif
}

inline uint32_t jiffies_to_usecs(const uint32_t j)
{
#if HZ <= USEC_PER_SEC && !(USEC_PER_SEC % HZ)
    return (USEC_PER_SEC / HZ) * j;
#elif HZ > USEC_PER_SEC && !(HZ % USEC_PER_SEC)
    return (j + (HZ / USEC_PER_SEC) - 1)/(HZ / USEC_PER_SEC);
#endif
}

uint32_t msecs_to_jiffies(const uint32_t m)
{
    /*
     * Negative value, means infinite timeout:
     */
    if ((int32_t)m < 0)
        return MAX_JIFFY_OFFSET;

    /*
     * HZ is equal to or smaller than 1000, and 1000 is a nice
     * round multiple of HZ, divide with the factor between them,
     * but round upwards:
     */
    return (m + (MSEC_PER_SEC / HZ) - 1) / (MSEC_PER_SEC / HZ);
}


uint32_t usecs_to_jiffies(const uint32_t u)
{
    if (u > jiffies_to_usecs(MAX_JIFFY_OFFSET))
        return MAX_JIFFY_OFFSET;

    return (u + (USEC_PER_SEC / HZ) - 1) / (USEC_PER_SEC / HZ);
}
