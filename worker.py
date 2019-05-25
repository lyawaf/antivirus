# Description: classes to start a job in a non-ui thread, and provide updates about progress

from PyQt5.QtCore import QThread, pyqtProperty, pyqtSignal, pyqtSlot


class Worker(QThread):
    """
    Description: A class that is used by UI to get notifications about event
                 progress.
    Usage: Make a subclass and reimplement run() method to do useful work.
           While runnning you can use method log() or log_line() to log some
           text for UI.

           For ease of use with QML, it's best for the parameters of the
           worker function to be properties of the class. The QML code would
           assign them some values, and then call start().
    """

    #Q_SIGNALS
    logUpdated = pyqtSignal('QString') # gives only last update
    logChanged = pyqtSignal('QString') # gives whole log

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
        self.logChanged.emit(self._full_log)

    def log_line(self, line):
        self.log(line + "\n")


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
        self._progress = progress_current
        self._progress_end = end


    #Q_PROPERTY
    @pyqtProperty(int, notify=progressChanged)
    def progress(self):
        return self._progress

    @pyqtProperty(int, constant=True)
    def progressEnd(self):
        return self._progress_end


    def set_progress(self, val):
        self._progress = val
        self.progressChanged.emit(self._progress)

    # increase progress by 1
    def advance(self):
        if self._progress == self._progress_end:
            return
        self.set_progress(self.progress + 1)
