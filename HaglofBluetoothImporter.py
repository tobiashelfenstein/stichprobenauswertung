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
        # qt process event
        #while True:
        nmea = self.connection.readline().decode("utf-8")
        print("Test")
        print(nmea)
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


#def parseGPS(data):
##    print "raw:", data #prints raw data
#    if data[0:5] == "$PHGF":
#        sdata = data.split(",")
#        if sdata[2] == 'V':
#            print "no satellite data available"
#            return
#        print "---Parsing GPRMC---",
#        time = sdata[1][0:2] + ":" + sdata[1][2:4] + ":" + sdata[1][4:6]
#       lat = decode(sdata[3]) #latitude
#        dirLat = sdata[4]      #latitude direction N/S
#        lon = decode(sdata[5]) #longitute
#        dirLon = sdata[6]      #longitude direction E/W
#        speed = sdata[7]       #Speed in knots
#        trCourse = sdata[8]    #True course
#        date = sdata[9][0:2] + "/" + sdata[9][2:4] + "/" + sdata[9][4:6]#date
# 
#        print "time : %s, latitude : %s(%s), longitude : %s(%s), speed : %s, True Course : %s, Date : %s" %  (time,lat,dirLat,lon,dirLon,speed,trCourse,date)
 
