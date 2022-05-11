QT += quick serialport gui widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Library/Mid/Mid_PCubeProcess.cpp \
        Library/Mid/Mid_ReadFile.cpp \
        Library/Op/Op_HeaderFunction.cpp \
        Library/Op/op_interruptmanager.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Library/Mid/Mid_PCubeProcess.h \
    Library/Mid/Mid_ReadFile.h \
    Library/Op/Op_HeaderDefine.h \
    Library/Op/Op_HeaderFlag.h \
    Library/Op/Op_HeaderFunction.h \
    Library/Op/Op_HeaderVariable.h \
    Library/Op/op_interruptmanager.h
