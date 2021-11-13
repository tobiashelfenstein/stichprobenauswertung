from PyQt5.QtWidgets import QMainWindow
from PyQt5.QtWidgets import QWidget
from PyQt5.QtWidgets import QVBoxLayout
from PyQt5.QtWidgets import QPushButton
from PyQt5.QtWidgets import QFileDialog
from PyQt5.QtWidgets import QDialog

from FileImportDialog import FileImportDialog
from SpeciesDialog import SpeciesDialog
from BluetoothProgressDialog import BluetoothProgressDialog
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
        #self.setMinimumSize(800, 500)

        # create basic elements
        self.setupUi()

        # connect signals
        self.fileImportBtn.clicked.connect(self.fileImportAction)
        self.blueImportBtn.clicked.connect(self.blueImportAction)
        self.quitBtn.clicked.connect(self.close)


    def setupUi(self):
        self.setWindowTitle("Stichprobenauswertung")

        centralWidget = QWidget()

        layout = QVBoxLayout()

        # file import button
        self.fileImportBtn = QPushButton("Stichprobe einlesen")
        self.fileImportBtn.setMinimumHeight(60)
        layout.addWidget(self.fileImportBtn)

        # bluetooth import button
        self.blueImportBtn = QPushButton("Bluetooth übertragen")
        self.blueImportBtn.setMinimumHeight(60)
        layout.addWidget(self.blueImportBtn)
        layout.addSpacing(30)

        # quit button
        self.quitBtn = QPushButton("Beenden")
        self.quitBtn.setMinimumHeight(60)
        layout.addWidget(self.quitBtn)

        centralWidget.setLayout(layout)
        self.setCentralWidget(centralWidget)

    def fileImportAction(self):
        importFile = ""
        deviceName = ""

        importDialog = FileImportDialog()
        if importDialog.exec() == QDialog.Accepted:
            importFile = importDialog.getFilePath()
            deviceName = importDialog.getDeviceName()

            # start importing
            self.controller.readSampleFile(importFile)

            # select species
            speciesDialog = SpeciesDialog()
            speciesDialog.setSpecies(self.model.species)
            if speciesDialog.exec() == QDialog.Accepted:
                self.controller.sendSampleToHEP(speciesDialog.getSpecies())

    def blueImportAction(self):
        # question for length
        
        # TODO Reihenfolge
        self.controller.startBluetoothMeasuring()

        progressDialog = BluetoothProgressDialog(self)
        progressDialog.accepted.connect(self.model.stopBluetoothImport)
        #progressDialog.setModal(True)
        progressDialog.show()



