#ifndef OP_INTERRUPTMANAGER_H
#define OP_INTERRUPTMANAGER_H

#include <QObject>
#include <QDebug>
#include "Library/Mid/bleinterface.h"

class Op_InterruptManager : public QObject
{
    Q_OBJECT
public:
    explicit Op_InterruptManager(QObject *parent = nullptr);
    ~Op_InterruptManager();
private:
    BLEInterface *m_bleInterface;
signals:
    void cb_ClearDevice(void);
    void cb_UpdateDevice(QString NewDevice);
    void cb_ClearService(void);
    void cb_UpdateService(QString NewService);
    void txt_UpdateMonitor(QString NewData);
public slots:
    void btn_ConnectOnClick(void);
    void btn_ServiceOnClick(void);
    void btn_RefeshOnClick(void);
    void btn_OpenFileOnClick(void);
    void btn_FlashOnClick(void);
    void btn_EraseOnClick(void);
    void btn_ResetOnClick(void);
    void btn_CheckOnClick(void);

    void BLEUDataReceive(QByteArray data);
    void BLEUpdateDevice(QStringList devices);
    void BLEUpdateService(QStringList services);
    void BLEStatusInforChange(QString info, bool);

    void qml_ChooseBLEDevice(int index);
};

#endif // OP_INTERRUPTMANAGER_H
