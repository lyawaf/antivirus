// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2

import "../Assets"

ColumnLayout {
    id: page
    property real masterSize: undefined
    signal changePage(var component, var properties)

    property alias threats: threatView.model

    // no implicit sizes are set, please only use this anchored to a window or frame

    Label {
        id: threatLabel
        Layout.alignment: Qt.AlignLeft
        font.pixelSize: masterSize * 1.5
        text: threatView.count > 0
              ? qsTr("%1 threats detected").arg(threatView.count)
              : qsTr("Your computer is clean")
    }

    ListView {
        id: threatView
        width: parent.width
        Layout.fillHeight: true

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
        }

        delegate: ThreatDelegate {
            // a "feature" i encountered long ago: listview and scrollview
            // don't expose correct width, so to size their children you
            // should use a visual parent of listview, in this case it's
            // page itself
            width: page.width

            masterSize: page.masterSize
            nameText: modelData.name
            detailsText: modelData.description
        }
    }

    RowLayout {
        Label {
            Layout.alignment: Qt.AlignLeft
            Layout.fillWidth: true
            text: qsTr("Actions:")
            font.pixelSize: masterSize * 1.5
        }
        Button {
            Layout.alignment: Qt.AlignRight
            Layout.fillWidth: false
            text: qsTr("Delete selected")
            font.pixelSize: masterSize * 1.5
        }
    }
}
