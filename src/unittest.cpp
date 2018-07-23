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


#include "gtest/gtest.h"
#include "os.h"
#include "utility.h"

TEST(SmallStdioTest, SmallStdio) {
    char tmp[128];

    EXPECT_EQ(sprintf_small(tmp, "%c", 'X'), 1);
    EXPECT_STREQ(tmp, "X");

    EXPECT_EQ(sprintf_small(tmp, "%s", "hello"), 5);
    EXPECT_STREQ(tmp, "hello");

    EXPECT_EQ(sprintf_small(tmp, "%d", 12345), 5);
    EXPECT_STREQ(tmp, "12345");

    EXPECT_EQ(sprintf_small(tmp, "%ld", 1234567890), 10);
    EXPECT_STREQ(tmp, "1234567890");

    EXPECT_EQ(sprintf_small(tmp, "%x", 0x1234), 4);
    EXPECT_STREQ(tmp, "1234");

    EXPECT_EQ(sprintf_small(tmp, "%lx", 0x12345678), 8);
    EXPECT_STREQ(tmp, "12345678");
}

TEST(CmdBufTest, CmdBuf) {
    CmdBuf cmd;
    pCmdBuf pCmd = &cmd;
#define ACTION_LEN_MAX      8
    char action[ACTION_LEN_MAX];
    uint8_t addr;
    uint16_t arg;

    cmdBufInit(pCmd);

    cmdBufReset(pCmd);
    cmdBufPushString(pCmd, "@01,Query,00,6f\r\n");
    cmdBufPushEnd(pCmd);
    EXPECT_GT(cmdBufSize(pCmd), 0);
    cmdBufGetAddr(pCmd, &addr);
    EXPECT_EQ(addr, 1);
    cmdBufGetAction(pCmd, action, ACTION_LEN_MAX);
    EXPECT_STREQ(action, "Query");
    cmdBufGetArg(pCmd, &arg);
    EXPECT_EQ(arg, 0);
    EXPECT_EQ(cmdBufValidation(pCmd), CMD_BUF_OK);

    cmdBufReset(pCmd);
    cmdBufPushString(pCmd, "@@01,Query,00,6f\r\n");
    cmdBufPushEnd(pCmd);
    EXPECT_GT(cmdBufSize(pCmd), 0);
    cmdBufGetAddr(pCmd, &addr);
    EXPECT_EQ(addr, 1);
    cmdBufGetAction(pCmd, action, ACTION_LEN_MAX);
    EXPECT_STREQ(action, "Query");
    cmdBufGetArg(pCmd, &arg);
    EXPECT_EQ(arg, 0);
    EXPECT_EQ(cmdBufValidation(pCmd), CMD_BUF_OK);

    cmdBufReset(pCmd);
    cmdBufPushString(pCmd, "@7e,SetID,01,4e\r\n");
    cmdBufPushEnd(pCmd);
    EXPECT_GT(cmdBufSize(pCmd), 0);
    cmdBufGetAddr(pCmd, &addr);
    EXPECT_EQ(addr, 0x7e);
    cmdBufGetAction(pCmd, action, ACTION_LEN_MAX);
    EXPECT_STREQ(action, "SetID");
    cmdBufGetArg(pCmd, &arg);
    EXPECT_EQ(arg, 1);
    EXPECT_EQ(cmdBufValidation(pCmd), CMD_BUF_OK);

    cmdBufReset(pCmd);
    cmdBufPushString(pCmd, "@7e,GetID,00,41\r\n");
    cmdBufPushEnd(pCmd);
    EXPECT_GT(cmdBufSize(pCmd), 0);
    cmdBufGetAddr(pCmd, &addr);
    EXPECT_EQ(addr, 0x7e);
    cmdBufGetAction(pCmd, action, ACTION_LEN_MAX);
    EXPECT_STREQ(action, "GetID");
    cmdBufGetArg(pCmd, &arg);
    EXPECT_EQ(arg, 0);
    EXPECT_EQ(cmdBufValidation(pCmd), CMD_BUF_OK);

    cmdBufReset(pCmd);
    cmdBufPushString(pCmd, "@01,SetType,01,28\r\n");
    cmdBufPushEnd(pCmd);
    EXPECT_GT(cmdBufSize(pCmd), 0);
    cmdBufGetAddr(pCmd, &addr);
    EXPECT_EQ(addr, 1);
    cmdBufGetAction(pCmd, action, ACTION_LEN_MAX);
    EXPECT_STREQ(action, "SetType");
    cmdBufGetArg(pCmd, &arg);
    EXPECT_EQ(arg, 1);
    EXPECT_EQ(cmdBufValidation(pCmd), CMD_BUF_OK);

    cmdBufReset(pCmd);
    cmdBufPushString(pCmd, "@01,GetType,00,1b\r\n");
    cmdBufPushEnd(pCmd);
    EXPECT_GT(cmdBufSize(pCmd), 0);
    cmdBufGetAddr(pCmd, &addr);
    EXPECT_EQ(addr, 1);
    cmdBufGetAction(pCmd, action, ACTION_LEN_MAX);
    EXPECT_STREQ(action, "GetType");
    cmdBufGetArg(pCmd, &arg);
    EXPECT_EQ(arg, 0);
    EXPECT_EQ(cmdBufValidation(pCmd), CMD_BUF_OK);

    cmdBufReset(pCmd);
    cmdBufPushString(pCmd, "@7e,SetID,01,4e\r\n");
    cmdBufPushEnd(pCmd);
    EXPECT_GT(cmdBufSize(pCmd), 0);
    cmdBufGetAddr(pCmd, &addr);
    EXPECT_EQ(addr, 0x7e);
    cmdBufGetAction(pCmd, action, ACTION_LEN_MAX);
    EXPECT_STREQ(action, "SetID");
    cmdBufGetArg(pCmd, &arg);
    EXPECT_EQ(arg, 1);
    EXPECT_EQ(cmdBufValidation(pCmd), CMD_BUF_OK);
}
