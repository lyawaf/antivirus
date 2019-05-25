# Description: classes to start a job in a non-ui thread, and provide updates about progress

from PyQt5.QtCore import QThread, pyqtProperty, pyqtSignal, pyqtSlot


class Worker(QThread):
    """
    Description: A class that is used by UI to get notifications about event progress.
    Usage: Make a subclass and reimplement run() method to do useful work.
           While runnning you can use method log() to log some text for UI.
    """

    #Q_SIGNALS
    logUpdated = pyqtSignal('QString')

    def __init__(self, parent=None):
        super().__init__(parent)
        self._full_log = ""

    #Q_PROPERTY
    @pyqtProperty('QString')
    def fullLog(self):
        return self._full_log

    def log(self, text):
        self._full_log += text
        self.logUpdated.emit(text)


class ProgressWorker(Worker):
    """
    Description: A worker that can provide a progress bar.
    Usage: Same as above + when creating you can provide amount of steps it
           will take to complete an action. When working you can advance steps
           by calling the advance() method.
    """

    #Q_SIGNALS
    progressChanged = pyqtSignal(int)

    def __init__(self, end=1, progress_current=0, parent=None):
        super().__init__(parent)
        self._progress = status
        self._progress_end = end


    #Q_PROPERTY
    @pyqtProperty(int)
    def progress(self):
        return self._status

    @status.setter
    def set_progress(self, val):
        self._progress = val
        slef.progressChanged.emit(self._progress)

    # increase progress by 1
    def advance(self):
        if self._progress == self._progress_end:
            return
        self.progress += 1
