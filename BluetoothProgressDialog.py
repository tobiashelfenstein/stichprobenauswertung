from PyQt5.QtWidgets import QDialog
from PyQt5.QtWidgets import QWidget
from PyQt5.QtWidgets import QHBoxLayout
from PyQt5.QtWidgets import QVBoxLayout
from PyQt5.QtWidgets import QPushButton
from PyQt5.QtWidgets import QFileDialog
from PyQt5.QtWidgets import QComboBox
from PyQt5.QtWidgets import QLabel
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import QSize

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
        self.abortImportBtn.clicked.connect(self.reject)
        self.finishImportBtn.clicked.connect(self.accept)

    def setupUi(self):
        self.setWindowTitle("Datenübertragung")

        mainLayout = QVBoxLayout()
        self.setLayout(mainLayout)

        # status label
        self.statusLabel = QLabel("Kluppdaten: übertragen ...")
        mainLayout.addWidget(self.statusLabel)

        # buttons
        abortIcon = QIcon(os.path.join("resources", "icons", "application-back.svg"))
        self.abortImportBtn = QPushButton(abortIcon, "")
        self.abortImportBtn.setMinimumHeight(60)
        self.abortImportBtn.setIconSize(QSize(40, 40))

        finishIcon = QIcon(os.path.join("resources", "icons", "application-next.svg"))
        self.finishImportBtn = QPushButton(finishIcon, "")
        self.finishImportBtn.setMinimumHeight(60)
        self.finishImportBtn.setIconSize(QSize(40, 40))
        self.finishImportBtn.setDefault(True)
        #self.finishImportBtn.setFocus()

        buttonLayout = QHBoxLayout()
        mainLayout.addLayout(buttonLayout)
        buttonLayout.addWidget(self.abortImportBtn)
        buttonLayout.addWidget(self.finishImportBtn)

