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

#include <cstring>

#include <QSerialPort>
#include <QTimer>
#include <QDebug>

#include "mainwin.h"
#include "ui_mainwin.h"


MainWin::MainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWin),
    pCmd(&cmd)
{
    ui->setupUi(this);

    cmdBufInit(pCmd);

    serialPort = new QSerialPort(this);
    serialPort->setPortName("ttyUSB1");
    serialPort->setBaudRate(38400);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->open(QIODevice::ReadWrite);
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    transactionTimeout = new QTimer(this);
    transactionTimeout->setSingleShot(true);
    connect(transactionTimeout, SIGNAL(timeout()), this, SLOT(onTransactionTimeout()));

    heartbeatTimer = new QTimer(this);
    heartbeatTimer->setSingleShot(true);
    connect(heartbeatTimer, SIGNAL(timeout()), this, SLOT(onHeartBeatTimer()));

    latency.start();
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::onReadyRead()
{
#define ACTION_LEN_MAX      16
    char action[ACTION_LEN_MAX];
    uint8_t addr;
    uint16_t arg;
    char cbyte;

    int bytes = serialPort->bytesAvailable();
    if (bytes > 0) {
        QByteArray buf = serialPort->readAll();
        for (int i = 0; i < buf.size(); i++) {
            cbyte = buf[i];
            if (cbyte == '\r' || cbyte == '\n') {
                cmdBufPushEnd(pCmd);
                if (cmdBufSize(pCmd) > 0) {
                    cmdBufGetAddr(pCmd, &addr);
                    cmdBufGetAction(pCmd, action, ACTION_LEN_MAX);
                    cmdBufGetArg(pCmd, &arg);
                    if (cmdBufValidation(pCmd) == CMD_BUF_OK) {
                        cmdTransaction(addr, action, arg);
                    }
                }
                cmdBufReset(pCmd);
            }  else {
                cmdBufPushByte(pCmd, cbyte);
            }
        }
    }
}

void MainWin::onTransactionTimeout()
{
    qDebug() << "transaction timeout";
}

void MainWin::onHeartBeatTimer()
{
    CmdBuf cmd;
    cmdBufBuild(&cmd, deviceID(), "Heartbeat", hostCount);
    serialPort->write(cmd.buf);
    transactionTimeout->start(200);
    latency.restart();
}

void MainWin::on_getIDButton_pressed()
{
    CmdBuf cmd;
    cmdBufBuild(&cmd, 0x7e, "GetID", 0);
    serialPort->write(cmd.buf);
    transactionTimeout->start(200);
}

void MainWin::on_setIDButton_pressed()
{
    CmdBuf cmd;
    cmdBufBuild(&cmd, 0x7e, "SetID", deviceID());
    serialPort->write(cmd.buf);
    transactionTimeout->start(200);
}

void MainWin::on_getTypeButton_pressed()
{
    CmdBuf cmd;
    cmdBufBuild(&cmd, deviceID(), "GetType", 0);
    serialPort->write(cmd.buf);
    transactionTimeout->start(200);
}

void MainWin::on_setTypeButton_pressed()
{
    CmdBuf cmd;
    cmdBufBuild(&cmd, deviceID(), "SetType", deviceType());
    serialPort->write(cmd.buf);
    transactionTimeout->start(200);
}

void MainWin::on_queryButton_pressed()
{
    CmdBuf cmd;
    cmdBufBuild(&cmd, deviceID(), "Query", 0);
    serialPort->write(cmd.buf);
    transactionTimeout->start(200);
}

void MainWin::on_heartbeatButton_pressed()
{
    heartbeatTimer->start(10);
    latencyTestTimes = 0;
    hostCount = 1;
    guestCount = 1;
}

uint8_t MainWin::deviceID()
{
    return ui->deviceIDLineEdit->text().toInt();
}

uint8_t MainWin::deviceType()
{
    return ui->deviceTypeLineEdit->text().toInt();
}

void MainWin::cmdTransaction(uint8_t id, char *action, uint16_t arg)
{
    transactionTimeout->stop();
    if (strcmp(action, "Query") == 0) {
        if (deviceType() == 2)
            ui->queryLineEdit->setText(QString::number(arg * 340 / 1000 / 2));
        else
            ui->queryLineEdit->setText(QString::number(arg));
    } else if (strcmp(action, "SetID") == 0) {
        ui->deviceIDLineEdit->setText(QString::number(arg));
    } else if (strcmp(action, "GetID") == 0) {
        ui->deviceIDLineEdit->setText(QString::number(arg));
    } else if (strcmp(action, "SetType") == 0) {
        ui->deviceTypeLineEdit->setText(QString::number(arg));
    } else if (strcmp(action, "GetType") == 0) {
        ui->deviceTypeLineEdit->setText(QString::number(arg));
    } else if (strcmp(action, "Heartbeat") == 0) {
        hostCount = arg & 0xff;
        guestCount = arg >> 8;
        heartbeatTimer->start(500);
        if (++latencyTestTimes < 50) {
            qDebug() << "Latency: " << latency.elapsed();
        } else {
            latencyTestTimes = 100;
        }
    } else {
        qDebug() << "Unknown action:" << action;
    }
}
