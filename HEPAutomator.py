from pywinauto import Application

class HEPAutomator():

    def __init__(self, hepExecutable):
        app = Application().connect(path=hepExecutable)
        self.hep = app.window(title_re=".*Holzaufnahme LF Rheinland-Pfalz")

    def sendSample(self, sample):
        for value in sample:
            self.hep.type_keys(value)
            self.hep.type_keys("{ENTER}")

        return True
