import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.12


Rectangle {
    id: root
    color: "#303030"

    signal setBlackToYellowGradient()
    signal setGreenToRedGradient()
    signal drawWireFrame(bool checked)
    signal enableFlatShading(bool checked)
    signal setDataSet(string dataSet)
    signal showSurface(bool show)
    signal pauseSimulation(bool pause)
    signal hueRotation(double value)
    signal scaleGraph(double value)
    signal setGridType(string type)
    signal setGlypColor(bool show)
    signal setRandomArrows(double value);
    signal heightGlyphs(double value);


    Material.theme: Material.Dark
    Material.accent: Material.Blue

    TabBar {
        id: bar
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        TabButton {
            text: qsTr("Home")
        }
        TabButton {
            text: qsTr("Glyphs")
        }
    }

    StackLayout {
        anchors.top: bar.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 0
        currentIndex: bar.currentIndex
        Loader {
           source:"pages/Home.qml";
        }
        Loader {
           source:"pages/Glyphs.qml";
        }
    }

}




/*##^## Designer {
    D{i:0;autoSize:true;height:800;width:300}D{i:1;anchors_width:300;autoSize:true;height:800;width:300}
D{i:5;anchors_height:400;anchors_width:200}D{i:6;anchors_height:400;anchors_width:200}
D{i:4;anchors_height:50;anchors_width:300}
}
 ##^##*/
