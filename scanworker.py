#!/usr/bin/env python3

# Description: a dummy worker that will "scan" the files given for viruses
# and give the answer randomly (whats the difference hahahhaaaa)

from PyQt5.QtCore import pyqtProperty, pyqtSignal, pyqtSlot, QUrl, QTemporaryDir
from PyQt5.QtQml import QQmlListProperty

from worker import ProgressWorker
from threatmodel import ThreatModel

from superwrapper import scan


class ScanWorker(ProgressWorker):
    """
    Description: A virus scanner.
    Usage: Create an instance in QML, assign the files property, and run.
           The result will be in the result property
    """

    #Q_SIGNALS
    filesChanged = pyqtSignal('QList<QUrl>')
    resultChanged = pyqtSignal(QQmlListProperty)

    def __init__(self, parent=None):
        super().__init__(start=0, parent=parent)
        self._files = []
        self._result = []


    #property setters
    def setFiles(self, files):
        self._files = files
        self.filesChanged.emit(self.files)
        self.set_end(len(self._files))
    def setResult(self, result):
        self._result = result
        self.resultChanged.emit(self.result)


    #Q_PROPERTY
    @pyqtProperty('QList<QUrl>', fset=setFiles, notify=filesChanged)
    def files(self):
        return self._files
    @pyqtProperty(QQmlListProperty, notify=resultChanged)
    def result(self):
        return QQmlListProperty(ThreatModel, self, self._result)

    def run(self):
        threats_found = []

        for file_url in self.files:
            name = file_url.toString()
            self.log_line("Checking {}".format(name))
            
            tdir = QTemporaryDir()
            if tdir.isValid():
                path = tdir.path()
            else:
                self.log_line("Could not create temporary directory")
                continue

            scan_result = scan(file_url.toLocalFile(), path, self.log_line)

            threat = ThreatModel(file_url, file_url, "yoba"
                                ,"Be careful, that's some advanced magics")
            threats_found += [threat]
            self.advance()
        self.log_line("Found {} threats".format(len(threats_found)))
        self.setResult(threats_found)
