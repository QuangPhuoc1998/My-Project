#ifndef MID_PCUBEPROCESS_H
#define MID_PCUBEPROCESS_H

#include <QThread>
#include <QDebug>
#include "Library/Op/Op_HeaderFlag.h"
#include "Library/Op/Op_HeaderFunction.h"
#include "Library/Op/Op_HeaderVariable.h"

#define FLASH_DONE          0
#define FLASH_ERROR         1
#define FLASH_TIMEOUT       2
#define FLASH_CHECK_ACK     3
#define FLASH_CHECK_NACK    4

#define ADDRESS_SECTOR_1 0x08008000

class Mid_PCubeProcess : public QThread
{
    Q_OBJECT
public:
    explicit Mid_PCubeProcess(QObject *parent = nullptr);
    ~Mid_PCubeProcess() override;
signals:
    void _PCubeSendData(void);
    void qml_UpdateMonitor(QString NewData);
public:
    void _PCubeProcess(void);
    void _PCubeProcessData(void);
    void _PCubeProcessRead();
    void _PCubeProcessReadResponse();
    void _PCubeProcessWrite();
    void _PCubeProcessWriteResponse();

    void _PCubeProgramData(void);
    void _PCubeEraseData(void);
    void _PCubeFlashData(void);
    uint8_t _PCubeCalculateSector(uint32_t FileSize);
protected:
    void run() override;
};

#endif // MID_PCUBEPROCESS_H
