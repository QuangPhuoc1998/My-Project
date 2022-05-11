#ifndef OP_INTERRUPTMANAGER_H
#define OP_INTERRUPTMANAGER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "qserialport.h"
#include <QSerialPortInfo>
#include <QTimer>
#include "Library/Op/Op_HeaderFlag.h"
#include "Library/Op/Op_HeaderFunction.h"
#include "Library/Op/Op_HeaderVariable.h"
#include "Library/Mid/Mid_PCubeProcess.h"

class Op_InterruptManager : public QObject
{
    Q_OBJECT
public:
    explicit Op_InterruptManager(QObject *parent = nullptr);
    ~Op_InterruptManager();
    bool g_ubStopFlag = false;
private:
    QString ComPortName;
    QSerialPort * SerialPort;
    Mid_PCubeProcess * Mid_PCubeProcessThread;
    QTimer * timer10ms;
    QTimer * timer50ms;
    QTimer * timer100ms;
    QTimer * timer1000ms;
signals:
    void cb_ClearComPort(void);
    void cb_UpdateComPort(QString NewComPort);
    void cb_ClearService(void);
    void cb_UpdateService(QString NewService);
    void txt_UpdateMonitor(QString NewData);
    void btn_UpdateBtnConnect(QString NewStatus);
public slots:
    void btn_ConnectOnClick(void);
    void btn_ServiceOnClick(void);
    void btn_RefeshOnClick(void);
    void btn_OpenFileOnClick(QString FileName);
    void btn_FlashOnClick(void);
    void btn_EraseOnClick(void);
    void btn_ResetOnClick(void);
    void btn_CheckOnClick(void);

    void ser_ConnectComPort(void);
    void ser_DisconncetComPort(void);
    void ser_SetComPort(QString PortName);
    void ser_SetBaudRate(QString BaudRateIndex);
    void ser_DataReceive(void);

    void Timer10msEvent(void);
    void Timer50msEvent(void);
    void Timer100msEvent(void);
    void Timer1000msEvent(void);
private slots:
    void ser_SendData(void);
    void qml_UpdateMonitor(QString NewData);
};

#endif // OP_INTERRUPTMANAGER_H
