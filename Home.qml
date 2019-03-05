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


        SwitchDelegate {
            id: modeItemRB
            width: column.width - 2 * column.padding
            text: qsTr("Draw Wire Frame")
            onToggled: root.drawWireFrame(checked)
        }

        Rectangle {
            width: column.width - 2 * column.padding
            height: 20
            color: "#ffffff"
            border.width: 0
            border.color: "black"
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color: "black" }
                GradientStop { position: 0.33; color: "blue" }
                GradientStop { position: 0.67; color: "red" }
                GradientStop { position: 1.0; color: "yellow" }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.setBlackToYellowGradient()
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
                GradientStop { position: 0.0; color: "darkgreen" }
                GradientStop { position: 0.33; color: "yellow" }
                GradientStop { position: 0.67; color: "red" }
                GradientStop { position: 1.0; color: "darkred" }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.setGreenToRedGradient()
                }
            }
        }


        Text {
            id: element
            color: "#ffffff"
            text: qsTr("Brush size")
            font.pixelSize: 15
        }

        Slider {
            id: slider
            width: column.width - 2 * column.padding
            stepSize: 0.1
            value: 0.5
        }



        Button {
            text: qsTr("Click me")
        }


    }

}





/*##^## Designer {
    D{i:0;height:800;width:300}
}
 ##^##*/
