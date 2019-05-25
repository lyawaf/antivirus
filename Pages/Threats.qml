// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2

ColumnLayout {
    id: page
    property real masterSize: 1
    signal changePage(var component, var properties)

    // no implicit sizes are set, please only use this anchored to a window or frame

    Label {
        id: threatLabel
        Layout.alignment: Qt.AlignLeft
        font.pixelSize: masterSize * 1.5
        text: listModel.count > 0
        ? qsTr("%1 threats detected").arg(listModel.count)
        : qsTr("Your computer is clean")
    }

    ScrollView {
        width: parent.width
        Layout.fillHeight: true

        ListView {
            id: threatView
            delegate: RowLayout {
                readonly property CheckBox checkBox: itemCheckBox

                CheckBox {
                    id: itemCheckBox
                    checkState: Qt.Checked
                }
                Label {
                    text: modelData
                    font.pixelSize: masterSize * 1.5
                }
            }

            model: ListModel {
                id: listModel

                ListElement {
                    modelData: "file1"
                }
                ListElement {
                    modelData: "file2"
                }
                ListElement {
                    modelData: "file3"
                }
                ListElement {
                    modelData: "file4"
                }
            }
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
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignRight
            text: qsTr("Delete selected")
            font.pixelSize: masterSize * 1.5
        }
    }
}
