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
                        text: qsTr("Density")
                        checked: true
                        onClicked: root.setDataSet("density")
                        width: parent.width / 2 - 7.5
                        font.pixelSize: 13
                    }

                    RadioDelegate {
                        text: qsTr("Velocity")
                        onClicked: root.setDataSet("velocity")
                        width: parent.width / 2 - 7.5
                        font.pixelSize: 13
                    }

                    RadioDelegate {
                        text: qsTr("Force")
                        onClicked: root.setDataSet("force")
                        width: parent.width / 2 - 7.5
                        font.pixelSize: 13
                    }
                    RadioDelegate {
                        text: qsTr("Divergence")
                        onClicked: root.setDataSet("divergence")
                        width: parent.width / 2 - 7.5
                        font.pixelSize: 13
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
                        text: qsTr("Graph size")
                        anchors.topMargin: 15
                        anchors.top: parent.top
                        verticalAlignment: Text.AlignTop
                        font.pixelSize: 13
                    }

                    Slider {
                        id: scales
                        stepSize: 0.01
                        value: 0.2
                        width: 120
                        onValueChanged: {
                            root.scaleGraph(value)
                        }
                    }

                    SwitchDelegate {
                        text: qsTr("Show Axis")
                        checked: true
                        onToggled: root.enableAxis(checked)
                        font.pixelSize: 12
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
                text: qsTr("Colors & Gradients")
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


                Rectangle {
                    id: highlight1
                    width: parent.width - 2 * parent.padding
                    height: 20
                    color: "#ffffff"
                    border.width: 0
                    border.color: "white"
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: (-1.0 + hue.value); color: "yellow" }
                        GradientStop { position: (-0.67 + hue.value); color: "red" }
                        GradientStop { position: (-0.33 + hue.value); color: "blue" }
                        GradientStop { position: (0.0 + hue.value); color: "black" }
                        GradientStop { position: (0.33 + hue.value); color: "blue" }
                        GradientStop { position: (0.67 + hue.value); color: "red" }
                        GradientStop { position: (1.0 + hue.value); color: "yellow" }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            highlight1.border.width = 3
                            highlight2.border.width = 0
                            highlight3.border.width = 0
                            highlight4.border.width = 0

                            root.setBlackToYellowGradient()
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
                        GradientStop { position: (-0.99 + hue.value); color: "darkred" }
                        GradientStop { position: (-0.67 + hue.value); color: "red" }
                        GradientStop { position: (-0.33 + hue.value); color: "yellow" }
                        GradientStop { position: (0.0 + hue.value); color: "darkgreen" }
                        GradientStop { position: (0.33 + hue.value); color: "yellow" }
                        GradientStop { position: (0.67 + hue.value); color: "red" }
                        GradientStop { position: (0.99 + hue.value); color: "darkred" }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            highlight1.border.width = 0
                            highlight2.border.width = 3
                            highlight3.border.width = 0
                            highlight4.border.width = 0
                            root.setGreenToRedGradient()
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
                    id: row2
                    width: parent.width - 2 * parent.padding
                    spacing: 15
                    Text {
                        id: element21
                        height: 20
                        color: "#ffffff"
                        text: qsTr("Hue rotation")
                        anchors.topMargin: 15
                        anchors.top: parent.top
                        verticalAlignment: Text.AlignTop
                        font.pixelSize: 13
                    }

                    Slider {
                        id: hue
                        stepSize: 0.01
                        value: 0
                        onValueChanged: {
                            root.hueRotation(value)
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
                text: qsTr("Simulation")
                anchors.topMargin: 15
                anchors.top: parent.top
                verticalAlignment: Text.AlignTop
                font.pixelSize: 13
            }
        }

        Frame {
            id: frame
            width: column.width - 2 * column.padding
            spacing: 15

            ColumnLayout {
                anchors.fill: parent
                Row {
                    id: row4
                    x: 153
                    y: 203
                    width: column.width - 2 * column.padding
                    spacing: 15

                    Button {
                        id: pause_sim
                        text: qsTr("Pause Simulation")
                        onClicked: root.pauseSimulation(true)
                        font.pixelSize: 13
                    }

                    Button {
                        id: continue_sim
                        text: qsTr("Resume Simulation")
                        onClicked: root.pauseSimulation(false)
                        font.pixelSize: 13
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
                text: qsTr("Isolines")
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
                Rectangle {
                    id: highlight3
                    width: parent.width - 2 * parent.padding
                    height: 20
                    color: "#ffffff"
                    border.width: 0
                    border.color: "white"
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: (-0.0 + hue2.value); color: "black" }
                        GradientStop { position: (-0.1 + hue2.value); color: "black" }
                        GradientStop { position: (-0.101 + hue2.value); color: "white" }
                        GradientStop { position: (-0.102 + hue2.value); color: "white" }
                        GradientStop { position: (-0.103 + hue2.value); color: "black" }
                        GradientStop { position: (-0.2 + hue2.value); color: "black" }
                        GradientStop { position: (-0.201 + hue2.value); color: "white" }
                        GradientStop { position: (-0.202 + hue2.value); color: "white" }
                        GradientStop { position: (-0.203 + hue2.value); color: "black" }
                        GradientStop { position: (-0.3 + hue2.value); color: "black" }
                        GradientStop { position: (-0.301 + hue2.value); color: "white" }
                        GradientStop { position: (-0.302 + hue2.value); color: "white" }
                        GradientStop { position: (-0.303 + hue2.value); color: "black" }
                        GradientStop { position: (-0.4 + hue2.value); color: "black" }
                        GradientStop { position: (-0.401 + hue2.value); color: "white" }
                        GradientStop { position: (-0.402 + hue2.value); color: "white" }
                        GradientStop { position: (-0.403 + hue2.value); color: "black" }
                        GradientStop { position: (-0.5 + hue2.value); color: "black" }
                        GradientStop { position: (-0.501 + hue2.value); color: "white" }
                        GradientStop { position: (-0.502 + hue2.value); color: "white" }
                        GradientStop { position: (-0.503 + hue2.value); color: "black" }
                        GradientStop { position: (-0.6 + hue2.value); color: "black" }
                        GradientStop { position: (-0.601 + hue2.value); color: "white" }
                        GradientStop { position: (-0.602 + hue2.value); color: "white" }
                        GradientStop { position: (-0.603 + hue2.value); color: "black" }
                        GradientStop { position: (-0.7 + hue2.value); color: "black" }
                        GradientStop { position: (-0.701 + hue2.value); color: "white" }
                        GradientStop { position: (-0.702 + hue2.value); color: "white" }
                        GradientStop { position: (-0.703 + hue2.value); color: "black" }
                        GradientStop { position: (-0.8 + hue2.value); color: "black" }
                        GradientStop { position: (-0.801 + hue2.value); color: "white" }
                        GradientStop { position: (-0.802 + hue2.value); color: "white" }
                        GradientStop { position: (-0.803 + hue2.value); color: "black" }
                        GradientStop { position: (-0.9 + hue2.value); color: "black" }
                        GradientStop { position: (-0.901 + hue2.value); color: "white" }
                        GradientStop { position: (-0.902 + hue2.value); color: "white" }
                        GradientStop { position: (-0.903 + hue2.value); color: "black" }
                        GradientStop { position: (-1 + hue2.value); color: "black" }


                        GradientStop { position: (0.0 + hue2.value); color: "black" }
                        GradientStop { position: (0.001 + hue2.value); color: "white" }
                        GradientStop { position: (0.002 + hue2.value); color: "white" }
                        GradientStop { position: (0.003 + hue2.value); color: "black" }
                        GradientStop { position: (0.1 + hue2.value); color: "black" }
                        GradientStop { position: (0.101 + hue2.value); color: "white" }
                        GradientStop { position: (0.102 + hue2.value); color: "white" }
                        GradientStop { position: (0.103 + hue2.value); color: "black" }
                        GradientStop { position: (0.2 + hue2.value); color: "black" }
                        GradientStop { position: (0.201 + hue2.value); color: "white" }
                        GradientStop { position: (0.202 + hue2.value); color: "white" }
                        GradientStop { position: (0.203 + hue2.value); color: "black" }
                        GradientStop { position: (0.3 + hue2.value); color: "black" }
                        GradientStop { position: (0.301 + hue2.value); color: "white" }
                        GradientStop { position: (0.302 + hue2.value); color: "white" }
                        GradientStop { position: (0.303 + hue2.value); color: "black" }
                        GradientStop { position: (0.4 + hue2.value); color: "black" }
                        GradientStop { position: (0.401 + hue2.value); color: "white" }
                        GradientStop { position: (0.402 + hue2.value); color: "white" }
                        GradientStop { position: (0.403 + hue2.value); color: "black" }
                        GradientStop { position: (0.5 + hue2.value); color: "black" }
                        GradientStop { position: (0.501 + hue2.value); color: "white" }
                        GradientStop { position: (0.502 + hue2.value); color: "white" }
                        GradientStop { position: (0.503 + hue2.value); color: "black" }
                        GradientStop { position: (0.6 + hue2.value); color: "black" }
                        GradientStop { position: (0.601 + hue2.value); color: "white" }
                        GradientStop { position: (0.602 + hue2.value); color: "white" }
                        GradientStop { position: (0.603 + hue2.value); color: "black" }
                        GradientStop { position: (0.7 + hue2.value); color: "black" }
                        GradientStop { position: (0.701 + hue2.value); color: "white" }
                        GradientStop { position: (0.702 + hue2.value); color: "white" }
                        GradientStop { position: (0.703 + hue2.value); color: "black" }
                        GradientStop { position: (0.8 + hue2.value); color: "black" }
                        GradientStop { position: (0.801 + hue2.value); color: "white" }
                        GradientStop { position: (0.802 + hue2.value); color: "white" }
                        GradientStop { position: (0.803 + hue2.value); color: "black" }
                        GradientStop { position: (0.9 + hue2.value); color: "black" }
                        GradientStop { position: (0.901 + hue2.value); color: "white" }
                        GradientStop { position: (0.902 + hue2.value); color: "white" }
                        GradientStop { position: (0.903 + hue2.value); color: "black" }
                        GradientStop { position: (1 + hue2.value); color: "black" }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            highlight1.border.width = 0
                            highlight2.border.width = 0
                            highlight3.border.width = 3
                            highlight4.border.width = 0
                            root.setIsoLineGradient()
                        }
                    }
                }

                Row {
                    id: row34
                    width: parent.width - 2 * parent.padding
                    spacing: 15

                    Column {
                        id: column03
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement03
                            height: 20
                            color: "#ffffff"
                            text: qsTr("0")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column23
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement23
                            height: 20
                            color: "#ffffff"
                            text: qsTr("2")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column43
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement43
                            height: 20
                            color: "#ffffff"
                            text: qsTr("4")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column63
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement63
                            height: 20
                            color: "#ffffff"
                            text: qsTr("6")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column83
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement83
                            height: 20
                            color: "#ffffff"
                            text: qsTr("8")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column103
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement203
                            height: 20
                            color: "#ffffff"
                            text: qsTr("10")
                            font.pixelSize: 13
                        }
                    }

                }

                Row {
                    id: row5
                    width: parent.width - 2 * parent.padding
                    spacing: 15
                    Text {
                        id: element25
                        height: 20
                        color: "#ffffff"
                        text: qsTr("Isoline Shift")
                        anchors.topMargin: 15
                        anchors.top: parent.top
                        verticalAlignment: Text.AlignTop
                        font.pixelSize: 13
                    }

                    Slider {
                        id: hue2
                        stepSize: 0.01
                        value: 0
                        from: 0
                        to: 0.1
                        onValueChanged: {
                            root.isolineRotation(value)
                        }
                    }
                }

                Row {
                    Text {
                        id: customText
                        height: 50
                        color: "#ffffff"
                        text: qsTr("Custom Isolines")
                        anchors.topMargin: 15
                        anchors.top: parent.top
                        verticalAlignment: Text.AlignTop
                        font.pixelSize: 13
                    }
                }

                Rectangle {
                    id: highlight4
                    width: parent.width - 2 * parent.padding
                    height: 20
                    color: "#ffffff"
                    border.width: 0
                    border.color: "white"
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: (0.000); color: "black" }
                        GradientStop { position: (min.value*0.1 - 0.002); color: "black" }
                        GradientStop { position: (min.value*0.1 - 0.001); color: "white" }
                        GradientStop { position: (min.value*0.1 + 0.001); color: "white" }
                        GradientStop { position: (min.value*0.1 + 0.002); color: "black" }

                        GradientStop { position: (max.value*0.1 - 0.002); color: "black" }
                        GradientStop { position: (max.value*0.1 - 0.001); color: "white" }
                        GradientStop { position: (max.value*0.1 + 0.001); color: "white" }
                        GradientStop { position: (max.value*0.1 + 0.002); color: "black" }
                        GradientStop { position: (1.000); color: "black" }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            highlight1.border.width = 0
                            highlight2.border.width = 0
                            highlight3.border.width = 0
                            highlight4.border.width = 3
                            root.setCustomIsoLineGradient()
                        }
                    }
                }

                Row {
                    id: row35
                    width: parent.width - 2 * parent.padding
                    spacing: 15

                    Column {
                        id: column04
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement04
                            height: 20
                            color: "#ffffff"
                            text: qsTr("0")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column24
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement24
                            height: 20
                            color: "#ffffff"
                            text: qsTr("2")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column44
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement44
                            height: 20
                            color: "#ffffff"
                            text: qsTr("4")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column64
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement64
                            height: 20
                            color: "#ffffff"
                            text: qsTr("6")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column84
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement84
                            height: 20
                            color: "#ffffff"
                            text: qsTr("8")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column104
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement204
                            height: 20
                            color: "#ffffff"
                            text: qsTr("10")
                            font.pixelSize: 13
                        }
                    }

                }
                Row {
                    id: row6
                    width: column.width - 2 * column.padding
                    spacing: 15
                    Text {
                        id: slidertext2
                        height: 20
                        color: "#ffffff"
                        text: qsTr("Min")
                        anchors.topMargin: 15
                        anchors.top: parent.top
                        verticalAlignment: Text.AlignTop
                        font.pixelSize: 13
                    }

                    Slider {
                        id: min
                        stepSize: 0.5
                        value: 5.0
                        from: 0
                        to: 9
                        width: 120
                        onValueChanged: {
                            if(min.value+1 <= max.value){
                                root.setCustomIsolineMin(value)
                            }else{
                                min.value = min.value-0.5
                            }
                        }
                    }

                    Text {
                        id: slidertext3
                        height: 20
                        color: "#ffffff"
                        text: qsTr("Max")
                        anchors.topMargin: 15
                        anchors.top: parent.top
                        verticalAlignment: Text.AlignTop
                        font.pixelSize: 13
                    }

                    Slider {
                        id: max
                        stepSize: 0.5
                        value: 9.0
                        from: 1
                        to: 10
                        width: 120
                        onValueChanged: {
                            if(min.value+1 <= max.value){
                                root.setCustomIsolineMax(value)
                            }else{
                                max.value = max.value+0.5
                            }
                        }
                    }
                }

                Row {
                    id: row8
                    width: column.width - 2 * column.padding
                    spacing: 15
                    Text {
                        id: slidertext4
                        height: 20
                        color: "#ffffff"
                        text: qsTr("Interval")
                        anchors.topMargin: 15
                        anchors.top: parent.top
                        verticalAlignment: Text.AlignTop
                        font.pixelSize: 13
                    }

                    Slider {
                        id: interval
                        stepSize: 1
                        value: 3
                        from: 1
                        to: 10
                        width: 120
                        onValueChanged: {
                            root.setCustomIsolineInterval(value)
                        }
                    }
                }
            }
        }

    }

}

/*##^## Designer {
    D{i:0;height:800;width:300}
}
 ##^##*/
