import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.12


Page {
    anchors.centerIn: parent

    Column {
        id: column
        anchors.fill: parent
        spacing: 15
        padding: 15

        Row {
            width: column.width - 2 * column.padding
            spacing: 15
            Text {
                height: 20
                color: "#ffffff"
                text: qsTr("Visuals")
                anchors.topMargin: 15
                anchors.top: parent.top
                verticalAlignment: Text.AlignTop
                font.pixelSize: 13
            }
        }

        Frame {
            width: column.width - 2 * column.padding
            spacing: 15

            ColumnLayout {
                anchors.fill: parent

                Flow {
                    width: column.width - 2 * column.padding
                    spacing: 15
                    anchors.fill: parent

                    RadioDelegate {
                        id: radioDelegate1
                        text: qsTr("Velocity")
                        checked: true
                        onClicked: root.setDataSet("velocity")
                        width: parent.width / 2 - 7.5
                    }

                    RadioDelegate {
                        id: radioDelegate2
                        text: qsTr("Force")
                        onClicked: root.setDataSet("force")
                        width: parent.width / 2 - 7.5
                    }
                }

                Row {
                    id: row1
                    width: column.width - 2 * column.padding
                    spacing: 15
                    Text {
                        id: slidertext1
                        height: 20
                        color: "#ffffff"
                        text: qsTr("Glyphs height")
                        anchors.topMargin: 15
                        anchors.top: parent.top
                        verticalAlignment: Text.AlignTop
                        font.pixelSize: 13
                    }

                    Slider {
                        id: scales
                        from: 0.0
                        stepSize: 0.5
                        value: 0.5
                        to: 10.0
                        onValueChanged: {
                            if(modeItemRB.checked){
                                root.heightGlyphs(value)
                            }else{
                                scales.value = 0.5
                            }
                        }
                    }
                }

                Row {
                    width: column.width - 2 * column.padding
                    spacing: 15

                    SwitchDelegate {
                        text: qsTr("Wireframe")
                        onToggled: root.drawWireFrame(checked)
                        font.pixelSize: 12
                    }

                    SwitchDelegate {
                        text: qsTr("Gouraud shading")
                        onToggled: root.enableFlatShading(checked)
                        font.pixelSize: 12
                    }
                }



            }
        }



        Row {
            width: column.width - 2 * column.padding
            spacing: 15
            Text {
                height: 20
                color: "#ffffff"
                text: qsTr("Glyphs")
                anchors.topMargin: 15
                anchors.top: parent.top
                verticalAlignment: Text.AlignTop
                font.pixelSize: 13
            }
        }



        Frame {
            width: column.width - 2 * column.padding
            spacing: 15

            Column {
                anchors.fill: parent

                Row {
                    SwitchDelegate {
                        id: modeItemRB
                        width: column.width - 2 * column.padding - 20
                        text: qsTr("Enable Glyphs")
                        font.pixelSize: 12
                        onToggled: {
                            root.showSurface(checked)
                            if(modeItemRB.checked){
                                switchDelegate.checked = true
                            }else{
                                switchDelegate.checked = false
                                switchDelegate1.checked = false
                            }
                        }

                    }
                }

                Rectangle {
                    id: highlight1
                    width: parent.width - 2 * parent.padding
                    height: 20
                    color: "#ffffff"
                    border.width: 0
                    border.color: "white"
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "green" }
                        GradientStop { position: 1.0; color: "darkgreen" }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            highlight1.border.width = 3
                            highlight2.border.width = 0
                            root.setGlypColor(false)
                        }
                    }
                }

                Row {
                    id: arow3
                    width: parent.width - 2 * parent.padding
                    spacing: 15

                    Column {
                        id: caolumn0
                        anchors.top: parent.top
                        width: arow3.width / 6 - 5
                        Text {
                            id: element0
                            height: 20
                            color: "#ffffff"
                            text: qsTr("0")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: caolumn2
                        anchors.top: parent.top
                        width: arow3.width / 6 - 5
                        Text {
                            id: element2
                            height: 20
                            color: "#ffffff"
                            text: qsTr("2")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: caolumn4
                        anchors.top: parent.top
                        width: arow3.width / 6 - 5
                        Text {
                            id: element4
                            height: 20
                            color: "#ffffff"
                            text: qsTr("4")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: caolumn6
                        anchors.top: parent.top
                        width: arow3.width / 6 - 5
                        Text {
                            id: element6
                            height: 20
                            color: "#ffffff"
                            text: qsTr("6")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: caolumn8
                        anchors.top: parent.top
                        width: arow3.width / 6 - 5
                        Text {
                            id: element8
                            height: 20
                            color: "#ffffff"
                            text: qsTr("8")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: caolumn10
                        anchors.top: parent.top
                        width: arow3.width / 6 - 5
                        Text {
                            id: element10
                            height: 20
                            color: "#ffffff"
                            text: qsTr("10")
                            font.pixelSize: 13
                        }
                    }

                }

                Rectangle {
                    id: highlight2
                    width: parent.width - 2 * parent.padding
                    height: 20
                    color: "#ffffff"
                    border.width: 0
                    border.color: "white"
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "green" }
                        GradientStop { position: 0.5; color: "yellow" }
                        GradientStop { position: 1.0; color: "red" }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            highlight1.border.width = 0
                            highlight2.border.width = 3
                            root.setGlypColor(true)
                        }

                    }
                }

                Row {
                    id: row3
                    width: parent.width - 2 * parent.padding
                    spacing: 15

                    Column {
                        id: column0
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement0
                            height: 20
                            color: "#ffffff"
                            text: qsTr("0")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column2
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement2
                            height: 20
                            color: "#ffffff"
                            text: qsTr("2")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column4
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement4
                            height: 20
                            color: "#ffffff"
                            text: qsTr("4")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column6
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement6
                            height: 20
                            color: "#ffffff"
                            text: qsTr("6")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column8
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement8
                            height: 20
                            color: "#ffffff"
                            text: qsTr("8")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column10
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement10
                            height: 20
                            color: "#ffffff"
                            text: qsTr("10")
                            font.pixelSize: 13
                        }
                    }

                }

                Row {
                    width: column.width - 2 * column.padding
                    spacing: 15
                    Text {
                        height: 20
                        color: "#ffffff"
                        text: qsTr("Arrow Size")
                        anchors.topMargin: 15
                        anchors.top: parent.top
                        verticalAlignment: Text.AlignTop
                        font.pixelSize: 13
                    }
                }


                Row {
                    width: column.width - 2 * column.padding
                    spacing: 15
                    Slider {
                        width: column.width - 2 * column.padding
                        id: arrowSize
                        from: 0.2
                        stepSize: 0.2
                        value: 1
                        live: false
                        to: 2
                        onValueChanged: {
                            if(modeItemRB.checked){
                                root.setArrowSize(arrowSize.value)
                            }else{
                                arrowSize.value = 1
                            }
                        }
                    }
                }

            }
        }

        Row {
            width: column.width - 2 * column.padding
            spacing: 15
            Text {
                height: 20
                color: "#ffffff"
                text: qsTr("Grid")
                anchors.topMargin: 15
                anchors.top: parent.top
                verticalAlignment: Text.AlignTop
                font.pixelSize: 13
            }
        }

        Frame {
                width: column.width - 2 * column.padding
                spacing: 15

                ColumnLayout {
                    anchors.fill: parent

                    Row {
                        SwitchDelegate {
                            width: column.width - 2 * column.padding - 20
                            text: qsTr("Uniform Grid")
                            id: switchDelegate
                            font.pixelSize: 12
                            onToggled: {
                                if(modeItemRB.checked){
                                    root.setGridType("uniform")
                                    switchDelegate1.checked = false
                                }else{
                                    switchDelegate.checked = false
                                }
                            }

                        }
                    }

                    Row {
                        SwitchDelegate {
                            width: column.width - 2 * column.padding - 20
                            text: qsTr("Random Grid")
                            id: switchDelegate1
                            font.pixelSize: 12
                            onToggled: {
                                if(modeItemRB.checked){
                                    root.setGridType("random")
                                    switchDelegate.checked = false
                                }else{
                                    switchDelegate1.checked = false
                                }
                            }

                        }
                    }

                    Row {
                        width: column.width - 2 * column.padding
                        spacing: 15
                        Text {
                            height: 20
                            color: "#ffffff"
                            text: qsTr("Amount of Arrows")
                            anchors.topMargin: 15
                            anchors.top: parent.top
                            verticalAlignment: Text.AlignTop
                            font.pixelSize: 13
                        }
                    }

                    Slider {
                        width: column.width - 2 * column.padding
                        id: randomPoints
                        from: 1000
                        stepSize: 1000
                        value: 10000
                        live: false
                        to: 12000
                        onValueChanged: {
                            if(switchDelegate1.checked){
                                root.setRandomArrows(randomPoints.value)
                            }else{
                                randomPoints.value = 10000
                            }
                        }
                    }

                    Row {
                        id: row4
                        width: parent.width - 2 * parent.padding
                        spacing: 15

                        Column {
                            id: column11
                            anchors.top: parent.top
                            width: row3.width / 6 - 5
                            Text {
                                id: aelement11
                                height: 20
                                color: "#ffffff"
                                text: qsTr("1000")
                                font.pixelSize: 13
                            }
                        }

                        Column {
                            id: column12
                            anchors.top: parent.top
                            width: row3.width / 6 - 5
                            Text {
                                id: aelement12
                                height: 20
                                color: "#ffffff"
                                text: qsTr("5000")
                                font.pixelSize: 13
                            }
                        }
                        Column {
                            id: column13
                            anchors.top: parent.top
                            width: row3.width / 6 - 5
                            Text {
                                id: aelement13
                                height: 20
                                color: "#ffffff"
                                text: qsTr("10000")
                                font.pixelSize: 13
                            }
                        }

                    }

                }
        }



    }

}

/*##^## Designer {
    D{i:0;height:200;width:200}
}
 ##^##*/
