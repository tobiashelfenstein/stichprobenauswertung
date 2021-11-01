from PyQt5.QtWidgets import QMainWindow
from PyQt5.QtWidgets import QWidget
from PyQt5.QtWidgets import QHBoxLayout
from PyQt5.QtWidgets import QPushButton
from PyQt5.QtWidgets import QFileDialog
from PyQt5.QtWidgets import QDialog

from SpeciesDialog import SpeciesDialog

import os.path
import sys


__version__ = "0.0.1"


class MainWindow(QMainWindow):
    def __init__(self, mainModel, mainCtrl, parent=None):
        super().__init__(parent)
        #self.setAttribute(Qt.WA_DeleteOnClose)

        # initialize class attributes
        #self._ICON_PATH_32 = os.path.join("resources", "icons", "oxygen", "32")

        # model for imported data
        self.model = mainModel
        self.controller = mainCtrl

        # setup gui
        self.setMinimumSize(800, 500)

        # create basic elements
        self.setupUi()

        # connect signals
        self.fileImportBtn.clicked.connect(self.fileImportAction)


    def setupUi(self):
        self.setWindowTitle("Stichprobenauswertung")

        centralWidget = QWidget()

        layout = QHBoxLayout()

        # file import button
        self.fileImportBtn = QPushButton("Stichprobe einlesen")
        layout.addWidget(self.fileImportBtn)

        centralWidget.setLayout(layout)
        self.setCentralWidget(centralWidget)

    def fileImportAction(self):
        # TODO
        #filename = QFileDialog.getOpenFileName(self, "Stichprobe öffnen", "z:\\source\\repos", "XML Datei (*.xml)", None, QFileDialog.DontUseNativeDialog)
        filename = QFileDialog.getOpenFileName(self, "Stichprobe öffnen", "c:\\hepwfp_helper\\stichprobenauswertung\\kluppdaten", "XML Datei (*.xml)", None, QFileDialog.DontUseNativeDialog)

        if filename[0]:
            self.controller.readSampleFile(filename[0])

        speciesDialog = SpeciesDialog()
        speciesDialog.setSpecies(self.model.species)
        if speciesDialog.exec() == QDialog.Accepted:
            self.controller.sendSampleToHEP(speciesDialog.getSpecies())



