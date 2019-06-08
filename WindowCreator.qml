// vim: expandtab
import QtQuick 2.9
import QtQuick.Controls 2.2

// Description: this component is used to force a window to stay open. It
// creates an object, and upon closing recreates it
// Usage: create an instance and assign componentUrl to a qml file of a window
// you want to be shown

Item {
    id: notifier
    property url componentUrl: undefined

    function createObject() {
        var instance;

        var component = Qt.createComponent(componentUrl);
        if (component.status == Component.Ready) {
            finishCreation();
        } else {
            component.statusChanged.connect(finishCreation);
        }

        function finishCreation() {
            if (component.status == Component.Ready) {
                instance = component.createObject(notifier, {});
                if (instance == null) {
                    // Error Handling
                    console.log("Error creating object");
                }
            } else if (component.status == Component.Error) {
                // Error Handling
                console.log("Error loading component:", component.errorString());
            }
        }

        instance.closing.connect(notifier.createObject)
    }

    Component.onCompleted: {
        if (componentUrl !== undefined){
            createObject();
        }
    }
}
