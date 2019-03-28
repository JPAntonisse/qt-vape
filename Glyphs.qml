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
            id: switchDelegate
            width: column.width - 2 * column.padding
            text: qsTr("Switch Delegate")
        }


    }

}

/*##^## Designer {
    D{i:0;height:200;width:200}
}
 ##^##*/
