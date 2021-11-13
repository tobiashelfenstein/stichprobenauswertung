from PyQt5.QtCore import pyqtSignal
from PyQt5.QtCore import QObject
from serial import Serial
import math

class HaglofSPPComReader(QObject):

    finished = pyqtSignal()
    diameter = pyqtSignal(int)
    length = pyqtSignal(int)

    def __init__(self):
        super().__init__()
        self.connection = None
        self.stop = False

    def openConnection(self, port, rate):
        self.connection = Serial(port=port, baudrate=rate, timeout=0.5)

    def read(self):
        nmea = self.connection.readline().decode("utf-8")
        return self.parseHaglofNMEA(nmea)

    def parseHaglofNMEA(self, nmea):
        if nmea[0:5] == "$PHGF":
            return nmea.split(",")
        else:
            return ""

    def readDiameter(self):
        while not self.stop is True:
            nmea = self.read()
            if nmea is "":
                continue
            if nmea[1] == "DIA":
                d = int(nmea[3]) / 10
                #return math.floor(d)
                self.diameter.emit(math.floor(d))
            else:
                # never the diameter is 0
                #self.diameter.emit(0)
                continue

        self.finished.emit()

    def readLength(self):
        while True:
            nmea = self.read()
            if nmea[1] == "LEN":
                l = int(nmea[3]) / 10
                return l
            else:
                # never the length is 0
                return 0

    def stopReading(self):
        print("Stop!")
        self.stop = True
