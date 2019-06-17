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
            elide: Text.ElideRight
        }
        Button {
            id: button

            Layout.alignment: Qt.AlignRight
            Layout.preferredWidth: height

            text: "lalal"
            font.pixelSize: masterSize * 0.5

            onClicked: {
                frame.collapsed = !frame.collapsed
            }

            background: Item {
                // here i'm creating an item to center the rectangle in it
                // otherwise as i set the rectangle's dimensions to be smaller
                // than those of the button, it would be dangling in the top
                // left corner
                width: button.width
                height: button.height
                Rectangle {
                    anchors.centerIn: parent
                    color: frame.collapsed ? "#ffffff" : "#b0b0b0"
                    border.color: "#b0b0b0"

                    height: button.height * 0.8
                    width: height

                    border.width: 0.5
                    radius: height / 4
                }
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
            wrapMode: Text.Wrap
        }
    }
}
