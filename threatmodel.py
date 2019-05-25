# Description: class that represents a threat (a virus) for ui. It should have
# the information about virus and methods to execute upon it

from PyQt5.QtCore import QObject, pyqtProperty, pyqtSignal, pyqtSlot


class ThreatModel(QObject):
    """
    Description: A class with virus info
    Fields:
        name: short name of file
        filepath: full path to virus
        threat_type: trojan, virus, suspect, etc
        description: complete description with other info
    """

    def __init__(self, name, filepath, threat_type, description, parent=None):
        super.__init__(parent=None)
        self._name        = name
        self._filepath    = filepath
        self._threat_type = threat_type
        self._description = description


    #Q_PROPERTY
    @pyqtProperty('QString', constant=True)
    def name(self):
        return self._name
    @pyqtProperty('QString', constant=True)
    def filePath(self):
        return self._filepath
    @pyqtProperty('QString', constant=True)
    def threatType(self):
        return self._threat_type
    @pyqtProperty('QString', constant=True)
    def description(self):
        return self._description
