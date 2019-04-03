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
            id: row
            width: column.width - 2 * column.padding
            spacing: 15

            RadioDelegate {
                id: radioDelegate
                text: qsTr("Density")
                checked: true
                onClicked: root.setDataSet("density")
            }

            RadioDelegate {
                id: radioDelegate1
                text: qsTr("Velocity")
                onClicked: root.setDataSet("velocity")
            }

            RadioDelegate {
                id: radioDelegate2
                text: qsTr("Force")
                onClicked: root.setDataSet("force")
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
                text: qsTr("Scale graph")
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

        SwitchDelegate {
            id: modeItemRB
            width: column.width - 2 * column.padding
            text: qsTr("Enable wireframe")
            onToggled: root.drawWireFrame(checked)
            font.pixelSize: 12
        }



        Rectangle {
            width: column.width - 2 * column.padding
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
            width: column.width - 2 * column.padding
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
            width: column.width - 2 * column.padding
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
            width: column.width - 2 * column.padding
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
            width: column.width - 2 * column.padding
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













































/*##^## Designer {
    D{i:0;height:800;width:300}
}
 ##^##*/
