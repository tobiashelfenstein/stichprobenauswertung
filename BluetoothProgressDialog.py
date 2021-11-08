from PyQt5.QtWidgets import QDialog
from PyQt5.QtWidgets import QWidget
from PyQt5.QtWidgets import QHBoxLayout
from PyQt5.QtWidgets import QPushButton
from PyQt5.QtWidgets import QFileDialog
from PyQt5.QtWidgets import QComboBox

import os.path
import sys


__version__ = "0.0.1"


class BluetoothProgressDialog(QDialog):
    def __init__(self, parent):
        super().__init__(parent)
        #self.setAttribute(Qt.WA_DeleteOnClose)

        # initialize class attributes
        #self._ICON_PATH_32 = os.path.join("resources", "icons", "oxygen", "32")

        # setup gui
        #self.setMinimumSize(800, 500)

        # create basic elements
        self.setupUi()

        # connect signals
        self.finishImportBtn.clicked.connect(self.accept)

    def setupUi(self):
        self.setWindowTitle("Bluetooth Datenübertragung")

        layout = QHBoxLayout()

        # start import button
        self.finishImportBtn = QPushButton("Fertig")
        self.finishImportBtn.setMinimumHeight(60)
        layout.addWidget(self.finishImportBtn)

        self.setLayout(layout)
