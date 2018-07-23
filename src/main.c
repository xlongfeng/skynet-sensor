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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os.h"
#include "jiffies.h"
#include "utility.h"

typedef enum {
    BLINK_PATTERN_DISCONNECTED,
    BLINK_PATTERN_CONNECTED
} BlinkPattern;

static BlinkPattern blinkPattern = BLINK_PATTERN_DISCONNECTED;

#define HEARDBEAT_PERIOD    1260

void led_heartbeat(void)
{
    static uint32_t delay_time;
    static uint8_t phase = 0;
    bool value = FALSE;

    if (time_before(jiffies, delay_time))
        return;

    switch (phase) {
    case 0:
        ++phase;
        delay_time = jiffies + msecs_to_jiffies(70);
        value = TRUE;
        break;
    case 1:
        ++phase;
        delay_time = jiffies + msecs_to_jiffies(HEARDBEAT_PERIOD / 4) - msecs_to_jiffies(70);
        break;
    case 2:
        ++phase;
        delay_time = jiffies + msecs_to_jiffies(70);
        value = blinkPattern == BLINK_PATTERN_CONNECTED ? TRUE : FALSE;
        break;
    default:
        phase = 0;
        delay_time = jiffies + msecs_to_jiffies(HEARDBEAT_PERIOD) - msecs_to_jiffies(HEARDBEAT_PERIOD / 4) - msecs_to_jiffies(70);
        break;
    }

    if (value)
        GPIO_WriteLow(GPIOB, (GPIO_Pin_TypeDef)GPIO_PIN_5);
    else
        GPIO_WriteHigh(GPIOB, (GPIO_Pin_TypeDef)GPIO_PIN_5);
}

static CmdBuf cmd;
static pCmdBuf pCmd = &cmd;
#define ACTION_LEN_MAX      8
char action[ACTION_LEN_MAX];
uint32_t live_tick;

void cmd_transaction(void)
{
    char cbyte;
    uint8_t addr;
    uint16_t arg;
    int res;

    res = getchar();
    if (res != -1) {
        cbyte = (char)res;
        if (cbyte == '\r' || cbyte == '\n') {
            cmdBufPushEnd(pCmd);
            if (cmdBufSize(pCmd) > 0) {
                cmdBufGetAddr(pCmd, &addr);
                cmdBufGetAction(pCmd, action, ACTION_LEN_MAX);
                cmdBufGetArg(pCmd, &arg);
                if (cmdBufValidation(pCmd) == CMD_BUF_OK) {
                    live_tick = jiffies;
                    blinkPattern = BLINK_PATTERN_CONNECTED;
                    if (strcmp(action, "Query") == 0 && addr == read_device_id()) {
                        arg = query_device();
                        cmdBufBuild(pCmd, addr, action, arg);
                        hdprintf("%s", pCmd->buf);
                    } else if (strcmp(action, "SetID") == 0 && addr == 0x7e) {
                        write_device_id(arg);
                        arg = read_device_id();
                        cmdBufBuild(pCmd, addr, action, arg);
                        hdprintf("%s", pCmd->buf);
                    } else if (strcmp(action, "GetID") == 0 && addr == 0x7e) {
                        arg = read_device_id();
                        cmdBufBuild(pCmd, addr, action, arg);
                        hdprintf("%s", pCmd->buf);
                    } else if (strcmp(action, "SetType") == 0 && addr == read_device_id()) {
                        write_device_type(arg);
                        device_switch(read_device_type());
                        arg = read_device_type();
                        cmdBufBuild(pCmd, addr, action, arg);
                        hdprintf("%s", pCmd->buf);
                    } else if (strcmp(action, "GetType") == 0 && addr == read_device_id()) {
                        arg = read_device_type();
                        cmdBufBuild(pCmd, addr, action, arg);
                        hdprintf("%s", pCmd->buf);
                    }
#ifdef DEBUG
                    else {
                        hdprintf("Unknown action %s, %x, %x\n", action, addr, read_device_id());
                    }
#endif
                }
#ifdef DEBUG
                else {
                    hdprintf("CMD valid failed\n");
                }
#endif
            }
            cmdBufReset(pCmd);
        } else {
            cmdBufPushByte(pCmd, cbyte);
        }
    } else {
        if (time_after(jiffies, live_tick + msecs_to_jiffies(5000))) {
            blinkPattern = BLINK_PATTERN_DISCONNECTED;
        }
    }
}

void main(void)
{
    os_init();
    cmdBufInit(pCmd);

    for (;;) {
        led_heartbeat();
        cmd_transaction();
        watchdog();
    }
}
