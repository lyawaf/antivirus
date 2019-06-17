#!/usr/bin/env python3

from PyQt5.QtCore import QUrl
from PyQt5.QtWidgets import QApplication
from PyQt5.QtQml import QQmlApplicationEngine, qmlRegisterType
import sys

from threatmodel import ThreatModel
from scanworker import ScanWorker

if __name__ == "__main__":
    app = QApplication(sys.argv)

    # register python classes in qml
    qmlRegisterType(ThreatModel, 'PyModels', 1, 0, 'ThreatModel')
    qmlRegisterType(ScanWorker, 'PyWorkers', 1, 0, 'ScanWorker')

    engine = QQmlApplicationEngine()
    engine.load(QUrl("main.qml"))
    app.exec()
