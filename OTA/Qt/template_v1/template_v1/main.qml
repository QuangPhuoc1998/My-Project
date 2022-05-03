import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

Window {
    width: 370
    height: 700
    visible: true
    color: "#23323f"
    title: qsTr("AnyOTA")

    Connections
    {
        target: Op_InterruptManager

        onCb_ClearDevice:
        {
            cb_SelectDevice.model.clear()
        }
        onCb_UpdateDevice:
        {
            cb_SelectDevice.model.append( {"text": NewDevice})
        }

        onCb_ClearService:
        {
            cb_SelectService.model.clear()
        }
        onCb_UpdateService:
        {
            cb_SelectService.model.append({"text": NewService});
        }

        onTxt_UpdateMonitor:
        {
            txt_Monitor.append(NewData)
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
                    }

                    contentItem: Text
                    {
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
                    id: cb_SelectDevice
                    width: 230
                    height: 40
                    textRole: "text"
                    model: ListModel
                    {
                        id: listmodel
                    }
                    onActivated:
                    {
                        Op_InterruptManager.qml_ChooseBLEDevice(currentIndex)
                        console.log("Index: ",currentIndex);
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
                    flat: true
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
                        text: qsTr("Service")
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                }

                ComboBox {
                    id: cb_SelectService
                    width: 230
                    height: 40
                    textRole: "text"
                    model: ListModel
                    {
                        id: listmodelservice
                    }
                    onActivated:
                    {
                        //Op_InterruptManager.qml_ChooseBLEDevice(currentIndex)
                        //console.log("Index: ",currentIndex);
                    }
                }
            }

            Button {
                id: btn_Refesh
                width: 350
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
            width: 350
            height: 175
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
                    width: 210
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
                width: 350
                height: 121
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
                    width: 330
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
                    width: 330
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
                    width: 330
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
                    width: 330
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

    ScrollView {
        id: scrollView
        x: 9
        y: 325
        width: 350
        height: 337
        hoverEnabled: false
        clip: false

        TextArea {
            id: txt_Monitor
            x: 0
            y: 0
            width: 350
            height: 337
            enabled: false
            color: "#ffffff"
            textFormat: Text.AutoText
            font.pointSize: 15
            placeholderText: qsTr("Text Area")
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/
