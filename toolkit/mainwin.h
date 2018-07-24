/*
 * sensor config toolkit
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

#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QTime>

#include "utility.h"

namespace Ui {
class MainWin;
}

class QSerialPort;
class QTimer;

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = 0);
    ~MainWin();

private slots:
    void onReadyRead();
    void onTransactionTimeout();
    void onHeartBeatTimer();
    void on_getIDButton_pressed();
    void on_setIDButton_pressed();
    void on_getTypeButton_pressed();
    void on_setTypeButton_pressed();
    void on_queryButton_pressed();
    void on_heartbeatButton_pressed();

private:
    uint8_t deviceID();
    uint8_t deviceType();
    void cmdTransaction(uint8_t id, char *action, uint16_t arg);

private:
    Ui::MainWin *ui;
    CmdBuf cmd;
    pCmdBuf pCmd;
    QSerialPort *serialPort;
    QTimer *transactionTimeout;
    QTimer *heartbeatTimer;
    QTime latency;
    int latencyTestTimes;
    uint8_t hostCount = 1, guestCount = 1;
};

#endif // MAINWIN_H
