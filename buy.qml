// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Licensing notification")

    Label {
        id: masterValues
        visible: false
        // a hidden label with availible font info
    }

    ColumnLayout {
        anchors.fill: parent

        Item {
            implicitWidth: image.implicitWidth
            implicitHeight: image.implicitHeight
            Layout.fillWidth: true
            Layout.fillHeight: true

            Image {
                id: image
                anchors.centerIn: parent
                // FIXME placeholder image! Yulya narisuy kartinku
                source: "./Assets/Logo.png"
            }
        }

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Consider buying this product to unlock a full set of features")
            background: Rectangle {
                color: "#ffffff"
            }
        }
    }
}
