// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2

Item {
    id: page
    property real masterSize: 1
    signal changePage(var component, var properties)

    // no implicit sizes are set, please only use this anchored to a window or frame

    Item {
        anchors {
            top: parent.top
            bottom: checkStatus.top
            left: parent.left
            right: parent.right
        }

        Image {
            anchors.centerIn: parent
            source: "../Assets/Logo.png"
        }
    }

    Label {
        id: checkStatus
        // this label is positioned just above the select row
        // it shows when the last scan was and tells to scan again

        anchors.bottom: selectRow.top
        anchors.left: selectRow.left
        width: page.width / 3

        text: qsTr("Last check: %1").arg(qsTr("never"))
    }

    RowLayout {
        id: selectRow
        // a row with buttons to start a new scan on files

        anchors.bottom: page.bottom
        anchors.left: page.left
        anchors.right: page.right

        Label {
            id: chooseLabel
            Layout.alignment: Qt.AlignLeft
            Layout.fillWidth: true
            text: qsTr("Choose new files to scan")
            font.pixelSize: masterSize * 1.5
        }

        Button {
            id: folderButton

            Layout.alignment: Qt.AlignRight
            text: qsTr("Select folder")
            font.pixelSize: masterSize * 1.5

            onClicked: {
                fileDialog.selectMultiple = false
                fileDialog.selectFolder = true
                fileDialog.open()
            }
        }

        Button {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Select files")
            font.pixelSize: masterSize * 1.5

            onClicked: {
                fileDialog.selectMultiple = true
                fileDialog.selectFolder = false
                fileDialog.open()
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: qsTr("Select files")

        onAccepted: {
            console.log("Chose: " + fileUrls)

            var component = Qt.resolvedUrl("ScanProgress.qml")
            var params = {
                "masterSize": masterSize
                ,"files": fileUrls
            }
            page.changePage(component, params)
        }
    }
}
