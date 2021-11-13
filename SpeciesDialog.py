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


class SpeciesDialog(QDialog):
    def __init__(self):
        super().__init__()
        #self.setAttribute(Qt.WA_DeleteOnClose)

        # initialize class attributes
        #self._ICON_PATH_32 = os.path.join("resources", "icons", "oxygen", "32")

        # setup gui
        #self.setMinimumSize(800, 500)

        # create basic elements
        self.setupUi()

        # connect signals
        self.abortImportBtn.clicked.connect(self.reject)
        self.startImportBtn.clicked.connect(self.accept)

    def setupUi(self):
        self.setWindowTitle("Baumartenwahl")

        mainLayout = QVBoxLayout()
        self.setLayout(mainLayout)

        # information label
        self.infoLabel = QLabel("Baumart:")
        mainLayout.addWidget(self.infoLabel)

        # species selection
        self.speciesComboBox = QComboBox()
        self.speciesComboBox.setMinimumHeight(60)
        self.speciesComboBox.setMinimumWidth(200)
        mainLayout.addWidget(self.speciesComboBox)
        mainLayout.addSpacing(20)

        # buttons
        abortIcon = QIcon(os.path.join("resources", "icons", "application-back.svg"))
        self.abortImportBtn = QPushButton(abortIcon, "")
        self.abortImportBtn.setMinimumHeight(60)
        self.abortImportBtn.setIconSize(QSize(40, 40))

        startIcon = QIcon(os.path.join("resources", "icons", "application-next.svg"))
        self.startImportBtn = QPushButton(startIcon, "")
        self.startImportBtn.setMinimumHeight(60)
        self.startImportBtn.setIconSize(QSize(40, 40))
        self.startImportBtn.setDefault(True)
        #self.startImportBtn.setFocus()

        buttonLayout = QHBoxLayout()
        mainLayout.addLayout(buttonLayout)
        buttonLayout.addWidget(self.abortImportBtn)
        buttonLayout.addWidget(self.startImportBtn)

    def setSpecies(self, species):
        self.speciesComboBox.insertItems(0, species)

    def getSpecies(self):
        return self.speciesComboBox.currentText()
