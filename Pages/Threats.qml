// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2

ColumnLayout {
    id: page
    property real masterSize: 1
    signal changePage(var component, var properties)

    Label {
        Layout.alignment: Qt.AlignHCenter
        text: listModel.count > 0
              ? qsTr("%1 threats detected").arg(listModel.count)
              : qsTr("Your computer is clean")
    }

    ScrollView {
        width: parent.width
        Layout.fillHeight: true

        ListView {
            delegate: RowLayout {
                CheckBox {
                    checkState: Qt.Unchecked
                }
                Label {
                    text: modelData
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
            text: "Actions:"
        }
        Button {
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignRight
            text: qsTr("Delete selected")
        }
    }
}
