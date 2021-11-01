import xml.etree.ElementTree as ElementTree
import math

class HaglofXMLFileReader():

    def __init__(self):
        self.root = None

    def importXMLFile(self, xmlfile, rootTag=""):
        xml = ElementTree.parse(xmlfile)
        self.root = xml.getroot()

        # set data root, if given
        self.dataRoot = None
        if rootTag:
            self.dataRoot = self.root.find(rootTag)

        return True

    def setDataRoot(self, rootTag=""):
        self.dataRoot = self.root.find(rootTag)

        return True

    def readDiameterBySpecies(self, species):
        diameters = []

        for tree in self.dataRoot:
            if str(tree.findtext("SpeciesText")) == species:
                d = int(tree.findtext("Diameter")) / 10
                diameters.append(math.floor(d))

        return diameters

    def readAllTreeSpecies(self):
        species = []

        for tree in self.dataRoot:
            s = str(tree.findtext("SpeciesText"))
            if s not in species:
                species.append(s)
        
        return species
