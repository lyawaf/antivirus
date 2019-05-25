// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2

import "./Pages/"

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Antivirus")

    StackView {
        id: stackView
        anchors.fill: parent

        function replacePage(component, properties) {
            // just in case; currentItem gets deleted in most cases anyway
            currentItem.changePage.disconnect(stackView.replacePage)

            var newItem = stackView.replace(component, properties, StackView.ReplaceTransition)
            if (newItem == null) {
                console.log("Couldn't create a page")
            } else {
                newItem.changePage.connect(stackView.replacePage)
            }
        }

        initialItem: NewScan {
            anchors.fill: parent

            onChangePage: {
                stackView.replacePage(component, properties)
            }
        }
    }
}
