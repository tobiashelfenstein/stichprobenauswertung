from PyQt5.QtCore import pyqtSignal
from PyQt5.QtCore import QObject
from HaglofFileImporter import HaglofXMLFileReader

class SampleModel(QObject):

    def __init__(self, manufacturer='haglof'):
        super().__init__()

        self.manufacturer = manufacturer
        self.importer = None

        self.species = {}

        if self.manufacturer == 'haglof':
            self.importer = HaglofXMLFileReader()
        else:
            pass

    def sampleImport(self, filename):
        self.importer.importXMLFile(filename)
        self.importer.setDataRoot("Data")

        self.species = self.importer.readAllTreeSpecies()

    def getSampleBySpecies(self, species):
        return self.importer.readDiameterBySpecies(species)


