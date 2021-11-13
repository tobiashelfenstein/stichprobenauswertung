#from PyQt5.QtWidgets import QObject
from PyQt5.QtWidgets import QMainWindow
from PyQt5.QtWidgets import QHBoxLayout
from PyQt5.QtWidgets import QPushButton

from HEPAutomator import HEPAutomator

import pywinauto
from PyQt5.QtWidgets import QMessageBox


__version__ = "0.0.1"


class MainController():
    def __init__(self, model):
        super().__init__()
        self.model = model
        try:
            #self.automator = HEPAutomator("z:\\downloads\\hepwfp\\rhpf.exe")
            self.automator = HEPAutomator("c:\\hepwfp\\rhpf.exe")
        except (pywinauto.application.ProcessNotFoundError) as e:
            dlg = QMessageBox()
            dlg.setIcon(QMessageBox.Critical)
            dlg.setText("HEP wurde nicht gestartet!")
            dlg.exec()

        # connect signals
        self.model.measuredValuesReady.connect(self.sendBluetoothToHEP)

    def readSampleFile(self, filename):
        self.model.initializeImporter("xml")
        self.model.sampleImport(filename)

    def sendSampleToHEP(self, species):
        self.automator.sendSample(self.model.getSampleBySpecies(species))

    def startBluetoothMeasuring(self, withLength=False):
        self.model.initializeImporter("bluetooth")
        self.model.bluetoothImport(withLength)
            #values = self.model.bluetoothImport(withLength)
            #if not values is None:
            #    print(values)
            #    #self.automator.sendMeasuredValue(values)

    def sendBluetoothToHEP(self):
        values = self.model.getMeasuredValues()
        if not values is None:
            self.automator.sendMeasuredValues(values)

