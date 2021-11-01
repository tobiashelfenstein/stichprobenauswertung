from PyQt5.QtWidgets import QDialog
from PyQt5.QtWidgets import QWidget
from PyQt5.QtWidgets import QHBoxLayout
from PyQt5.QtWidgets import QPushButton
from PyQt5.QtWidgets import QFileDialog
from PyQt5.QtWidgets import QComboBox

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
        self.startImportBtn.clicked.connect(self.accept)

    def setupUi(self):
        self.setWindowTitle("Baumartenauswahl")

        layout = QHBoxLayout()

        # species selection
        self.speciesComboBox = QComboBox()
        layout.addWidget(self.speciesComboBox)

        # start import button
        self.startImportBtn = QPushButton("Starten")
        layout.addWidget(self.startImportBtn)

        self.setLayout(layout)

    def setSpecies(self, species):
        self.speciesComboBox.insertItems(0, species)

    def getSpecies(self):
        return self.speciesComboBox.currentText()
