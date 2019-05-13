// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Antivirus")

    Label {
        anchors.centerIn: parent
        text: "I'm an antivirus"
    }
}
