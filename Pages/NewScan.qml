// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2

Item {
    id: page
    signal changePage(var component, var properties)

    // no implicit sizes are set, please only use this anchored to a window or frame

    Label {
        id: checkStatus
        anchors.bottom: selectRow.top
        anchors.right: folderButton.right
        anchors.leftMargin: chooseLabel.width
        width: page.width / 3

        text: qsTr("Last check: %1").arg(qsTr("never"))

        Component.onCompleted: {
            console.log("choose label width: " + chooseLabel.width)
        }
    }

    RowLayout {
        id: selectRow
        anchors.bottom: page.bottom
        anchors.leftMargin: chooseLabel.font.pixelSize
        anchors.rightMargin: chooseLabel.font.pixelSize
        width: page.width

        Label {
            id: chooseLabel
            Layout.alignment: Qt.AlignLeft
            Layout.fillWidth: true
            text: qsTr("Choose new files to scan")
            font.pixelSize: folderButton.font.pixelSize * 1.5
        }

        Button {
            id: folderButton

            Layout.alignment: Qt.AlignRight
            text: qsTr("Select folder")

            onClicked: {
                fileDialog.selectMultiple = false
                fileDialog.selectFolder = true
                fileDialog.open()
            }
        }

        Button {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Select files")

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
            page.changePage(Qt.resolvedUrl("Threats.qml"), {})
        }
    }
}
