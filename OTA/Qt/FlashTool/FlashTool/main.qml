import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

Window {
    width: 600
    height: 700
    visible: true
    color: "#23323f"
    title: qsTr("AnyOTA")

    Connections
    {
        target: Op_InterruptManager;
        onCb_UpdateComPort:
        {
            cb_Com.model.append( {"text": NewComPort});
        }
        onCb_ClearComPort:
        {
            cb_Com.model.clear()
        }
        onBtn_UpdateBtnConnect:
        {
            btn_connect_content.text = NewStatus;
            if(btn_connect_content.text === "Connect")
            {
                btn_connect_background.color = btn_connect.down ? "#10D87E" : "#10937E"
            }
            else
            {
                btn_connect_background.color = btn_connect.down ? "#980F0D" : "#DD0F0D"
            }


        }
    }
    Column {
        id: cl_WorkArea
        x: 9
        y: 6
        width: 350
        height: 395

        Column {
            id: cl_ConnectDevice
            width: 350
            height: 140

            Row {
                id: rw_Choose
                width: 500
                height: 50

                Button {
                    id: btn_connect
                    width: 120
                    height: 40
                    flat: true
                    highlighted: true
                    onClicked:
                    {
                        Op_InterruptManager.btn_ConnectOnClick()
                        txt_Monitor.append("HIHI")
                    }

                    contentItem: Text
                    {
                        id: btn_connect_content
                        width: 100
                        height: 30
                        text: qsTr("Connect")
                        opacity: enabled ? 1.0 : 0.3
                        color: "#FFFFFF"
                        font.pointSize: 10
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle
                    {
                        id: btn_connect_background
                        implicitWidth: 100
                        implicitHeight: 40
                        opacity: enabled ? 1 : 0.3
                        border.color: btn_connect.down ? "#10D87E" : "#10937E"
                        color: btn_connect.down ? "#10D87E" : "#10937E"
                        border.width: 1
                        radius: 2
                    }
                }

                ComboBox {
                    id: cb_Com
                    width: 460
                    height: 40
                    textRole: "text"
                    model: ListModel
                    {
                        id: listmodel
                    }
                    onActivated:
                    {
                        Op_InterruptManager.ser_SetComPort(currentText);
                    }
                }
            }

            Row {
                id: rw_ChooseService
                width: 520
                height: 50

                Button {
                    id: btn_Service
                    width: 120
                    height: 40
                    visible: true
                    flat: true
                    enabled: false
                    onClicked:
                    {
                        Op_InterruptManager.btn_ServiceOnClick()
                    }
                    background: Rectangle
                    {
                        opacity: enabled ? 1 : 0.3
                        color: btn_Service.down ? "#10D87E" : "#10937E"
                        radius: 2
                        border.color: btn_Service.down ? "#10D87E" : "#10937E"
                        border.width: 1
                        implicitWidth: 100
                        implicitHeight: 40
                    }
                    highlighted: true
                    contentItem: Text {
                        width: 100
                        height: 30
                        opacity: enabled ? 1.0 : 0.3
                        color: "#ffffff"
                        text: qsTr("Baudrate")
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                }

                ComboBox {
                    id: cb_Baudrate
                    width: 460
                    height: 40
                    textRole: "text"
                    model: ListModel
                    {
                        id: listmodelservice
                        ListElement { text: "9600"}
                        ListElement { text: "19200"}
                        ListElement { text: "115200"}
                    }
                    onActivated:
                    {
                        Op_InterruptManager.ser_SetBaudRate(currentIndex);
                    }
                }
            }

            Button {
                id: btn_Refesh
                width: 580
                height: 30
                flat: true
                onClicked:
                {
                    Op_InterruptManager.btn_RefeshOnClick()
                }
                background: Rectangle {
                    opacity: enabled ? 1 : 0.3
                    color: btn_Refesh.down ? "#10D87E" : "#10937E"
                    radius: 2
                    border.color: btn_Refesh.down ? "#10D87E" : "#10937E"
                    border.width: 1
                    implicitWidth: 100
                    implicitHeight: 40
                }
                highlighted: true
                contentItem: Text {
                    width: 100
                    height: 30
                    opacity: enabled ? 1.0 : 0.3
                    color: "#ffffff"
                    text: qsTr("Refesh")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 10
                }
            }
        }

        Rectangle {
            id: re_Operation
            width: 580
            height: 180
            color: "#23323f"
            border.color: "#607d79"

            Row {
                id: row1
                x: 0
                y: 0
                width: 350
                height: 47
                bottomPadding: 8
                leftPadding: 10

                Button {
                    id: btn_Openfile
                    x: 10
                    y: 10
                    width: 120
                    height: 30
                    flat: true
                    onClicked:
                    {
                        Op_InterruptManager.btn_OpenFileOnClick();
                    }

                    background: Rectangle {
                        opacity: enabled ? 1 : 0.3
                        color: btn_Openfile.down ? "#10D87E" : "#10937E"
                        radius: 2
                        border.color: btn_Openfile.down ? "#10D87E" : "#10937E"
                        border.width: 1
                        implicitWidth: 100
                        implicitHeight: 40
                    }
                    highlighted: true
                    contentItem: Text {
                        width: 100
                        opacity: enabled ? 1.0 : 0.3
                        color: "#ffffff"
                        text: qsTr("Open File")
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                }

                TextArea {
                    id: txt_ChooseFile
                    y: 10
                    width: 440
                    height: 30
                    enabled: false
                    text: qsTr("Nop")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 10
                    placeholderText: qsTr("Text Area")
                    background: Rectangle
                    {
                        color: "#FFFFFF"
                    }

                }
            }

            Grid {
                id: gr_Operation
                x: 0
                y: 45
                width: 572
                height: 130
                leftPadding: 10
                verticalItemAlignment: Grid.AlignVCenter
                horizontalItemAlignment: Grid.AlignHCenter
                layoutDirection: Qt.LeftToRight
                flow: Grid.TopToBottom
                spacing: 2
                rows: 4
                columns: 1
                scale: 1

                Button {
                    id: btn_Flash
                    width: 560
                    height: 30
                    flat: true
                    background: Rectangle {
                        opacity: enabled ? 1 : 0.3
                        color: btn_Flash.down ? "#10D87E" : "#10937E"
                        radius: 2
                        border.color: btn_Flash.down ? "#10D87E" : "#10937E"
                        border.width: 1
                        implicitWidth: 100
                        implicitHeight: 40
                    }
                    highlighted: true
                    contentItem: Text {
                        opacity: enabled ? 1.0 : 0.3
                        color: "#ffffff"
                        text: qsTr("Flash")
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                }

                Button {
                    id: btn_Erase
                    x: 130
                    width: 560
                    height: 30
                    flat: true
                    background: Rectangle {
                        opacity: enabled ? 1 : 0.3
                        color: btn_Erase.down ? "#10D87E" : "#10937E"
                        radius: 2
                        border.color: btn_Erase.down ? "#10D87E" : "#10937E"
                        border.width: 1
                        implicitWidth: 100
                        implicitHeight: 40
                    }
                    highlighted: true
                    contentItem: Text {
                        opacity: enabled ? 1.0 : 0.3
                        color: "#ffffff"
                        text: qsTr("Erase")
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                }

                Button {
                    id: btn_Check
                    x: 130
                    width: 560
                    height: 30
                    flat: true
                    background: Rectangle {
                        opacity: enabled ? 1 : 0.3
                        color: btn_Check.down ? "#10D87E" : "#10937E"
                        radius: 2
                        border.color: btn_Check.down ? "#10D87E" : "#10937E"
                        border.width: 1
                        implicitWidth: 100
                        implicitHeight: 40
                    }
                    highlighted: true
                    contentItem: Text {
                        opacity: enabled ? 1.0 : 0.3
                        color: "#ffffff"
                        text: qsTr("Check")
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                }

                Button {
                    id: btn_Reset
                    x: 130
                    width: 560
                    height: 30
                    onClicked:
                    {
                        Op_InterruptManager.btn_ResetOnClick()
                    }

                    background: Rectangle {
                        opacity: enabled ? 1 : 0.3
                        color: btn_Reset.down ? "#10D87E" : "#10937E"
                        radius: 2
                        border.color: btn_Reset.down ? "#10D87E" : "#10937E"
                        border.width: 1
                        implicitWidth: 100
                        implicitHeight: 40
                    }
                    flat: true
                    contentItem: Text {
                        opacity: enabled ? 1.0 : 0.3
                        color: "#ffffff"
                        text: qsTr("Reset")
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                    highlighted: true
                }
            }
        }
    }

    Rectangle {
        id: rectangle
        x: 9
        y: 333
        width: 580
        height: 350
        color: "#ffffff"

        ScrollView {
            id: scrollView
            x: 0
            y: 0
            width: 580
            height: 350
            hoverEnabled: false
            clip: false

            TextArea {
                id: txt_Monitor
                x: -10
                y: -6
                width: 580
                height: 337
                enabled: true
                color: "#000000"
                textFormat: Text.AutoText
                font.pointSize: 15
                placeholderText: qsTr("Monitor display")
                wrapMode: TextArea.WrapAnywhere
                placeholderTextColor: "#000000"
            }


        }
    }
}
