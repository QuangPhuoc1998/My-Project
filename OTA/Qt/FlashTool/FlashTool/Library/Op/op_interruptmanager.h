#ifndef OP_INTERRUPTMANAGER_H
#define OP_INTERRUPTMANAGER_H

#include <QObject>
#include <QDebug>
#include "qserialport.h"
#include <QSerialPortInfo>
#include "Library/Op/Op_HeaderFlag.h"

class Op_InterruptManager : public QObject
{
    Q_OBJECT
public:
    explicit Op_InterruptManager(QObject *parent = nullptr);
    ~Op_InterruptManager();
private:
    QString ComPortName;
    QSerialPort * SerialPort;
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
    void btn_OpenFileOnClick(void);
    void btn_FlashOnClick(void);
    void btn_EraseOnClick(void);
    void btn_ResetOnClick(void);
    void btn_CheckOnClick(void);

    void ser_ConnectComPort(void);
    void ser_DisconncetComPort(void);
    void ser_SetComPort(QString PortName);
    void ser_SetBaudRate(QString BaudRateIndex);
    void ser_DataReceive(void);
};

#endif // OP_INTERRUPTMANAGER_H
