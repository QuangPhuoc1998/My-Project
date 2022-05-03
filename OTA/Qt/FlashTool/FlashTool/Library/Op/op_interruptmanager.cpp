#include "op_interruptmanager.h"

Op_InterruptManager::Op_InterruptManager(QObject *parent) : QObject(parent)
{
    SERIALPORT_IS_RUNNING = C_OFF;
    SERIALPROT_IS_SELECT  = C_OFF;
}

Op_InterruptManager::~Op_InterruptManager()
{

}

void Op_InterruptManager::btn_ConnectOnClick()
{
    qDebug() << "Connect click";
    if(SERIALPORT_IS_RUNNING == C_ON)
    {
        ser_DisconncetComPort();
    }
    else
    {
        ser_ConnectComPort();
    }
}

void Op_InterruptManager::btn_ServiceOnClick()
{
    qDebug() << "Service click";
}

void Op_InterruptManager::btn_RefeshOnClick()
{
    qDebug() << "Scan click";
    emit cb_ClearComPort();
    /*--- Update serial port ---*/
    foreach (const QSerialPortInfo &ThisPort, QSerialPortInfo::availablePorts())
    {
        emit cb_UpdateComPort(ThisPort.portName());
    }
}

void Op_InterruptManager::btn_OpenFileOnClick()
{
    qDebug() << "Open click";
    if(SERIALPORT_IS_RUNNING == C_ON)
    {
        SerialPort->write("Hello");
    }
    else
    {
        qDebug() << "Open comport first";
    }

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
}

void Op_InterruptManager::btn_CheckOnClick()
{

}

void Op_InterruptManager::ser_ConnectComPort()
{
    if(SERIALPROT_IS_SELECT != C_ON)
    {
        qDebug() << "Select comport";
    }
    else if(SERIALPORT_IS_RUNNING == C_OFF)
    {
        SerialPort = new QSerialPort();
        SerialPort->setPortName(ComPortName);
        SerialPort->setBaudRate(QSerialPort::Baud9600);
        SerialPort->setDataBits(QSerialPort::Data8);
        SerialPort->setParity(QSerialPort::NoParity);
        SerialPort->setStopBits(QSerialPort::OneStop);

        SerialPort->open((QIODevice::ReadWrite));

        connect(SerialPort,SIGNAL(readyRead()),this,SLOT(ser_DataReceive()));

        SERIALPORT_IS_RUNNING = C_ON;
        emit btn_UpdateBtnConnect("Disconnect");
    }
    else
    {
        qDebug() << "Comport already";
    }
}

void Op_InterruptManager::ser_DisconncetComPort()
{
    if(SERIALPORT_IS_RUNNING == C_ON)
    {
        SerialPort->close();
        SERIALPORT_IS_RUNNING = C_OFF;
        emit btn_UpdateBtnConnect("Connect");
    }
    else
    {
        qDebug() << "Comport not open";
    }
}

void Op_InterruptManager::ser_SetComPort(QString PortName)
{
    SERIALPROT_IS_SELECT = C_ON;
    ComPortName = PortName;
    qDebug() << PortName;
}

void Op_InterruptManager::ser_SetBaudRate(QString BaudRateIndex)
{
    qDebug() << BaudRateIndex;
}

void Op_InterruptManager::ser_DataReceive()
{

}
