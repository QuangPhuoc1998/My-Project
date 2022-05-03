#include "op_interruptmanager.h"

Op_InterruptManager::Op_InterruptManager(QObject *parent) : QObject(parent)
{
    m_bleInterface = new BLEInterface(this);

    connect(m_bleInterface, &BLEInterface::dataReceived,
            this, &Op_InterruptManager::BLEUDataReceive);

    connect(m_bleInterface, &BLEInterface::devicesNamesChanged,
            this, &Op_InterruptManager::BLEUpdateDevice);

    connect(m_bleInterface, &BLEInterface::servicesChanged,
            this, &Op_InterruptManager::BLEUpdateService);

    connect(m_bleInterface, &BLEInterface::statusInfoChanged,
            this, &Op_InterruptManager::BLEStatusInforChange);

    m_bleInterface->set_currentDevice(0);

    m_bleInterface->scanDevices();
}

Op_InterruptManager::~Op_InterruptManager()
{

}

void Op_InterruptManager::btn_ConnectOnClick()
{
    qDebug() << "Connect click";
    m_bleInterface->connectCurrentDevice();
}

void Op_InterruptManager::btn_ServiceOnClick()
{
    qDebug() << "Service click";
    emit cb_ClearService();
    QStringList test = {"PHAM","PHUOC"};
    for(uint8_t i = 0 ; i < test.size() ; i++)
    {
        emit cb_UpdateService(test[i]);
    }
}

void Op_InterruptManager::btn_RefeshOnClick()
{
    qDebug() << "Scan click";
    m_bleInterface->scanDevices();
}

void Op_InterruptManager::btn_OpenFileOnClick()
{

}

void Op_InterruptManager::btn_FlashOnClick()
{

}

void Op_InterruptManager::btn_EraseOnClick()
{

}

void Op_InterruptManager::btn_ResetOnClick()
{
    qDebug() << "Reset click";
    emit txt_UpdateMonitor("Pham Quang Phuoc");
}

void Op_InterruptManager::btn_CheckOnClick()
{

}

void Op_InterruptManager::BLEUDataReceive(QByteArray data)
{

}

void Op_InterruptManager::BLEUpdateDevice(QStringList devices)
{
    emit cb_ClearDevice();
    for(uint8_t i = 0 ; i < devices.size() ; i++)
    {
        emit cb_UpdateDevice(devices[i]);
    }
}

void Op_InterruptManager::BLEUpdateService(QStringList services)
{

}

void Op_InterruptManager::BLEStatusInforChange(QString info, bool)
{

}

void Op_InterruptManager::qml_ChooseBLEDevice(int index)
{
    m_bleInterface->set_currentDevice(index);
}
