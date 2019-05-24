// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2

ColumnLayout {
    id: page
    signal changePage(var component)

    RowLayout {
        Layout.alignment: Qt.AlignBottom
        Label {
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
            page.changePage(Qt.resolvedUrl("Threats.qml"))
        }
    }
}
