import QtQuick 2.9
import QtQuick.Controls 2.2

import PyWorkers 1.0

AbstractProgress {
    id: page
    signal changePage(var component, var properties)
    property alias files: worker.files

    headerText: qsTr("Scanning files...")
    logText: ""

    progressFrom: 0
    progressTo: worker.progressEnd
    progressValue: worker.progress

    ScanWorker {
        id: worker

        Component.onCompleted: {
            worker.logUpdated.connect(function(text) {logText += text})
            worker.start()
            logText += "Started\n"
        }

        onFinished: {
            logText += "Finished\n"
        }
    }
}
