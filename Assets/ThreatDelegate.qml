// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2

Column {
    property real masterSize: undefined

    property alias checkState: itemCheckBox.checkState
    property alias nameText: nameLabel.text
    property alias detailsText: detailsLabel.text

    RowLayout {
        width: parent.width
        CheckBox {
            id: itemCheckBox
            checkState: Qt.Checked
        }
        Label {
            id: nameLabel
            Layout.fillWidth: true
            font.pixelSize: masterSize * 1.5
        }
        Button {
            Layout.alignment: Qt.AlignRight
            Layout.preferredWidth: height

            text: frame.currentText
            font.pixelSize: masterSize * 1.5

            onClicked: {
                frame.collapsed = !frame.collapsed
            }
        }
    }

    CollapseFrame {
        id: frame
        width: parent.width
        collapsed: true

        showText: "+"
        collapseText: "-"

        Label {
            id: detailsLabel
            width: parent.width
        }
    }
}
