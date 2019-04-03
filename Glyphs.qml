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
            SwitchDelegate {
                id: modeItemRB
                width: column.width - 2 * column.padding
                text: qsTr("Enable Glyphs")
                font.pixelSize: 12
                onToggled: root.showSurface(checked)
            }
        }

        Row {
            id: row
            width: column.width - 2 * column.padding
            spacing: 15

            RadioDelegate {
                id: radioDelegate1
                text: qsTr("Velocity")
                onClicked: root.setDataSet("velocity")
                checked: true
            }

            RadioDelegate {
                id: radioDelegate2
                text: qsTr("Force")
                onClicked: root.setDataSet("force")
            }

        }

        Row {
            width: column.width - 2 * column.padding
            spacing: 15

            RadioDelegate {
                id: radioDelegate3
                text: qsTr("Uniform Grid")
                onClicked: root.setGridType("uniform")
                checked: true
            }

            RadioDelegate {
                id: radioDelegate4
                text: qsTr("Random Grid")
                    onClicked: root.setGridType("random")
            }

        }

    }

}

/*##^## Designer {
    D{i:0;height:200;width:200}
}
 ##^##*/
