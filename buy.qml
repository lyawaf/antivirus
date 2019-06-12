// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 640
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

                width: Math.min(parent.width, implicitWidth)
                height: Math.min(parent.height, implicitHeight, width)
                fillMode: Image.PreserveAspectFit

                source: "./Assets/Excl.png"
            }
        }

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Consider buying this product to unlock a full set of features")

            Layout.fillWidth: true
            font.pixelSize: masterValues.font.pixelSize * 2
            wrapMode: Text.WordWrap

            background: Rectangle {
                color: "#ffffff"
            }
        }
    }
}
