from PyQt5.QtCore import pyqtSignal
from PyQt5.QtCore import QObject
from PyQt5.QtCore import QThread
from HaglofFileImporter import HaglofXMLFileReader
from HaglofBluetoothImporter import HaglofSPPComReader

class SampleModel(QObject):

    measuredValuesReady = pyqtSignal()

    def __init__(self, manufacturer="haglof"):
        super().__init__()

        self.manufacturer = manufacturer
        self.importer = None

        self.withLength = False

        self.species = {}
        self.measuredValues = (0, 0)

        if self.manufacturer == 'haglof':
            self.importer = HaglofXMLFileReader()
        else:
            pass

    def initializeImporter(self, method):
        # always clear importer
        self.thread = QThread(parent=self)
        self.importer = None

        # TODO: error control
        if self.manufacturer == "haglof":
            if method == "xml":
                self.importer = HaglofXMLFileReader()
            elif method == "bluetooth":
                self.importer = HaglofSPPComReader()
                self.importer.openConnection("COM7", 9600)


    def sampleImport(self, filename):
        self.importer.importXMLFile(filename)
        self.importer.setDataRoot("Data")

        self.species = self.importer.readAllTreeSpecies()

    def getSampleBySpecies(self, species):
        return self.importer.readDiameterBySpecies(species)

    def bluetoothImport(self, withLength=False):
        self.withLength = withLength
        self.importer.moveToThread(self.thread)

        # connect signals and slots
        self.thread.started.connect(self.importer.readDiameter)
        self.importer.diameter.connect(self.setBluetoothDiameter)
        self.importer.finished.connect(self.importer.deleteLater)
        self.thread.finished.connect(self.thread.deleteLater)

        # start the thread
        self.thread.start()

    def stopBluetoothImport(self):
        self.importer.stopReading()

    def setBluetoothDiameter(self, d):
        if self.withLength:
            pass
        else:
            self.measuredValues = 0, d
            self.measuredValuesReady.emit()

        # always read diameter
        #d = self.importer.readDiameter()
        #l = 0

        # we need the length also
        #if withLength:
        #    l = self.importer.readLength()

        # return tubple with diameter and length
        # TODO
        #if d == 0:
        #    return None
        #else:
        #    return 0, d
        #with open('out.txt', 'w') as f:
        #    print(d, file=f)

    def getMeasuredValues(self):
        return self.measuredValues




