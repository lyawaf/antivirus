// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2

ColumnLayout {
    id: page
    property real masterSize: undefined
    property alias headerText: header.text
    property alias logText: logLabel.text
    property alias progressFrom: progressBar.from
    property alias progressTo: progressBar.to
    property alias progressValue: progressBar.value

    Label {
        id: header
        text: qsTr("Working...")
        font.pixelSize: masterSize * 1.5
    }

    Frame {
        Layout.fillWidth: true
        Layout.fillHeight: true

        Flickable {
            anchors.fill: parent
            clip: true
            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AsNeeded
            }

            // force the scroll to be at the bottom when new log comes
            contentHeight: logLabel.height
            contentY: Math.max(contentHeight - height, 0)

            Label {
                id: logLabel

                width: parent.width
                font.family: "Monospace"
                font.pixelSize: masterSize * 1.5

                text: ""
            }
        }
    }

    Label {
        Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
        horizontalAlignment: Text.AlignHCenter
        text: "" + worker.progress + "/" + worker.progressEnd
    }

    ProgressBar {
        id: progressBar

        Layout.alignment: Qt.AlignBottom
        Layout.fillWidth: true
    }
}
