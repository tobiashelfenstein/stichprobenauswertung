#from PyQt5.QtWidgets import QObject
from PyQt5.QtWidgets import QMainWindow
from PyQt5.QtWidgets import QHBoxLayout
from PyQt5.QtWidgets import QPushButton

from HEPAutomator import HEPAutomator


__version__ = "0.0.1"


class MainController():
    def __init__(self, model):
        super().__init__()
        self.model = model
        #self.automator = HEPAutomator("z:\\downloads\\hepwfp\\rhpf.exe")
        self.automator = HEPAutomator("c:\\hepwfp\\rhpf.exe")

    def readSampleFile(self, filename):
        self.model.sampleImport(filename)

    def sendSampleToHEP(self, species):
        self.automator.sendSample(self.model.getSampleBySpecies(species))
        

