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
                    }

                    RadioDelegate {
                        text: qsTr("Velocity")
                        onClicked: root.setDataSet("velocity")
                        width: parent.width / 2 - 7.5
                    }

                    RadioDelegate {
                        text: qsTr("Force")
                        onClicked: root.setDataSet("force")
                        width: parent.width / 2 - 7.5
                    }
                    RadioDelegate {
                        text: qsTr("Divergence")
                        onClicked: root.setDataSet("divergence")
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
                        text: qsTr("Graph scaling")
                        anchors.topMargin: 15
                        anchors.top: parent.top
                        verticalAlignment: Text.AlignTop
                        font.pixelSize: 13
                    }

                    Slider {
                        id: scales
                        stepSize: 0.01
                        value: 0.2
                        onValueChanged: {
                            root.scaleGraph(value)
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
                    width: parent.width - 2 * parent.padding
                    height: 20
                    color: "#ffffff"
                    border.width: 0
                    border.color: "black"
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
                    width: parent.width - 2 * parent.padding
                    height: 20
                    color: "#ffffff"
                    border.width: 0
                    border.color: "black"
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

                Rectangle {
                    width: parent.width - 2 * parent.padding
                    height: 20
                    color: "#ffffff"
                    border.width: 0
                    border.color: "black"
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: (-0.0 + hue.value); color: "black" }
                        GradientStop { position: (-0.1 + hue.value); color: "black" }
                        GradientStop { position: (-0.101 + hue.value); color: "white" }
                        GradientStop { position: (-0.102 + hue.value); color: "white" }
                        GradientStop { position: (-0.103 + hue.value); color: "black" }
                        GradientStop { position: (-0.2 + hue.value); color: "black" }
                        GradientStop { position: (-0.201 + hue.value); color: "white" }
                        GradientStop { position: (-0.202 + hue.value); color: "white" }
                        GradientStop { position: (-0.203 + hue.value); color: "black" }
                        GradientStop { position: (-0.3 + hue.value); color: "black" }
                        GradientStop { position: (-0.301 + hue.value); color: "white" }
                        GradientStop { position: (-0.302 + hue.value); color: "white" }
                        GradientStop { position: (-0.303 + hue.value); color: "black" }
                        GradientStop { position: (-0.4 + hue.value); color: "black" }
                        GradientStop { position: (-0.401 + hue.value); color: "white" }
                        GradientStop { position: (-0.402 + hue.value); color: "white" }
                        GradientStop { position: (-0.403 + hue.value); color: "black" }
                        GradientStop { position: (-0.5 + hue.value); color: "black" }
                        GradientStop { position: (-0.501 + hue.value); color: "white" }
                        GradientStop { position: (-0.502 + hue.value); color: "white" }
                        GradientStop { position: (-0.503 + hue.value); color: "black" }
                        GradientStop { position: (-0.6 + hue.value); color: "black" }
                        GradientStop { position: (-0.601 + hue.value); color: "white" }
                        GradientStop { position: (-0.602 + hue.value); color: "white" }
                        GradientStop { position: (-0.603 + hue.value); color: "black" }
                        GradientStop { position: (-0.7 + hue.value); color: "black" }
                        GradientStop { position: (-0.701 + hue.value); color: "white" }
                        GradientStop { position: (-0.702 + hue.value); color: "white" }
                        GradientStop { position: (-0.703 + hue.value); color: "black" }
                        GradientStop { position: (-0.8 + hue.value); color: "black" }
                        GradientStop { position: (-0.801 + hue.value); color: "white" }
                        GradientStop { position: (-0.802 + hue.value); color: "white" }
                        GradientStop { position: (-0.803 + hue.value); color: "black" }
                        GradientStop { position: (-0.9 + hue.value); color: "black" }
                        GradientStop { position: (-0.901 + hue.value); color: "white" }
                        GradientStop { position: (-0.902 + hue.value); color: "white" }
                        GradientStop { position: (-0.903 + hue.value); color: "black" }
                        GradientStop { position: (-1 + hue.value); color: "black" }


                        GradientStop { position: (0.0 + hue.value); color: "black" }
                        GradientStop { position: (0.001 + hue.value); color: "white" }
                        GradientStop { position: (0.002 + hue.value); color: "white" }
                        GradientStop { position: (0.003 + hue.value); color: "black" }
                        GradientStop { position: (0.1 + hue.value); color: "black" }
                        GradientStop { position: (0.101 + hue.value); color: "white" }
                        GradientStop { position: (0.102 + hue.value); color: "white" }
                        GradientStop { position: (0.103 + hue.value); color: "black" }
                        GradientStop { position: (0.2 + hue.value); color: "black" }
                        GradientStop { position: (0.201 + hue.value); color: "white" }
                        GradientStop { position: (0.202 + hue.value); color: "white" }
                        GradientStop { position: (0.203 + hue.value); color: "black" }
                        GradientStop { position: (0.3 + hue.value); color: "black" }
                        GradientStop { position: (0.301 + hue.value); color: "white" }
                        GradientStop { position: (0.302 + hue.value); color: "white" }
                        GradientStop { position: (0.303 + hue.value); color: "black" }
                        GradientStop { position: (0.4 + hue.value); color: "black" }
                        GradientStop { position: (0.401 + hue.value); color: "white" }
                        GradientStop { position: (0.402 + hue.value); color: "white" }
                        GradientStop { position: (0.403 + hue.value); color: "black" }
                        GradientStop { position: (0.5 + hue.value); color: "black" }
                        GradientStop { position: (0.501 + hue.value); color: "white" }
                        GradientStop { position: (0.502 + hue.value); color: "white" }
                        GradientStop { position: (0.503 + hue.value); color: "black" }
                        GradientStop { position: (0.6 + hue.value); color: "black" }
                        GradientStop { position: (0.601 + hue.value); color: "white" }
                        GradientStop { position: (0.602 + hue.value); color: "white" }
                        GradientStop { position: (0.603 + hue.value); color: "black" }
                        GradientStop { position: (0.7 + hue.value); color: "black" }
                        GradientStop { position: (0.701 + hue.value); color: "white" }
                        GradientStop { position: (0.702 + hue.value); color: "white" }
                        GradientStop { position: (0.703 + hue.value); color: "black" }
                        GradientStop { position: (0.8 + hue.value); color: "black" }
                        GradientStop { position: (0.801 + hue.value); color: "white" }
                        GradientStop { position: (0.802 + hue.value); color: "white" }
                        GradientStop { position: (0.803 + hue.value); color: "black" }
                        GradientStop { position: (0.9 + hue.value); color: "black" }
                        GradientStop { position: (0.901 + hue.value); color: "white" }
                        GradientStop { position: (0.902 + hue.value); color: "white" }
                        GradientStop { position: (0.903 + hue.value); color: "black" }
                        GradientStop { position: (1 + hue.value); color: "black" }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            root.setIsoLineGradient()
                        }
                    }
                }

                Row {
                    id: row32
                    width: parent.width - 2 * parent.padding
                    spacing: 15

                    Column {
                        id: column02
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement02
                            height: 20
                            color: "#ffffff"
                            text: qsTr("0")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column22
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement22
                            height: 20
                            color: "#ffffff"
                            text: qsTr("2")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column42
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement42
                            height: 20
                            color: "#ffffff"
                            text: qsTr("4")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column62
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement62
                            height: 20
                            color: "#ffffff"
                            text: qsTr("6")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column81
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement81
                            height: 20
                            color: "#ffffff"
                            text: qsTr("8")
                            font.pixelSize: 13
                        }
                    }
                    Column {
                        id: column101
                        anchors.top: parent.top
                        width: row3.width / 6 - 5
                        Text {
                            id: aelement201
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
                    }

                    Button {
                        id: continue_sim
                        text: qsTr("Resume Simulation")
                        onClicked: root.pauseSimulation(false)
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
