from PyQt5.QtWidgets import QDialog
from PyQt5.QtWidgets import QWidget
from PyQt5.QtWidgets import QHBoxLayout
from PyQt5.QtWidgets import QVBoxLayout
from PyQt5.QtWidgets import QPushButton
from PyQt5.QtWidgets import QFileDialog
from PyQt5.QtWidgets import QComboBox
from PyQt5.QtWidgets import QListView
from PyQt5.QtWidgets import QFileSystemModel
from PyQt5.QtWidgets import QLabel
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QFileIconProvider
from PyQt5.QtCore import QSize

import os.path
import sys


__version__ = "0.0.1"


class FileImportDialog(QDialog):

    # define device list
    DEVICES = (
            "Masser Excaliper",
            "Haglöf MDII Caliper",
        )

    FORMATS = (
            "*.txt",
            "*.xml",
        )

    def __init__(self):
        super().__init__()
        #self.setAttribute(Qt.WA_DeleteOnClose)

        # initialize class attributes
        #self._ICON_PATH_32 = os.path.join("resources", "icons", "oxygen", "32")

        self.model = QFileSystemModel()
        self.model.setIconProvider(EmptyIconProvider())
        self.model.setNameFilterDisables(False)

        # setup gui
        #self.setMinimumSize(800, 500)

        # create basic elements
        self.setupUi()

        # connect signals
        self.deviceComboBox.currentIndexChanged.connect(self.updateFileList)
        self.abortImportBtn.clicked.connect(self.reject)
        self.startImportBtn.clicked.connect(self.accept)

        # update file list
        self.updateFileList()

    def setupUi(self):
        self.setWindowTitle("Stichprobe öffnen")

        mainLayout = QVBoxLayout()
        self.setLayout(mainLayout)

        # device selection
        self.deviceLabel = QLabel("Kluppentyp:")
        self.deviceComboBox = QComboBox()
        self.deviceComboBox.setMinimumHeight(60)
        self.deviceComboBox.addItems(self.DEVICES)

        mainLayout.addWidget(self.deviceLabel)
        mainLayout.addWidget(self.deviceComboBox)
        mainLayout.addSpacing(20)

        # file list
        self.fileLabel = QLabel("Stichprobe:")
        self.fileListView = QListView()
        self.fileListView.setMinimumHeight(300)
        self.fileListView.setMinimumWidth(500)
        self.fileListView.setModel(self.model)

        mainLayout.addWidget(self.fileLabel)
        mainLayout.addWidget(self.fileListView)
        mainLayout.addSpacing(20)

        # buttons
        abortIcon = QIcon(os.path.join("resources", "icons", "application-back.svg"))
        self.abortImportBtn = QPushButton(abortIcon, "")
        self.abortImportBtn.setMinimumHeight(60)
        self.abortImportBtn.setIconSize(QSize(40, 40))

        startIcon = QIcon(os.path.join("resources", "icons", "application-next.svg"))
        self.startImportBtn = QPushButton(startIcon, "")
        self.startImportBtn.setMinimumHeight(60)
        self.startImportBtn.setIconSize(QSize(40, 40))
        self.startImportBtn.setDefault(True)
        #self.startImportBtn.setFocus()

        buttonLayout = QHBoxLayout()
        mainLayout.addLayout(buttonLayout)
        buttonLayout.addWidget(self.abortImportBtn)
        buttonLayout.addWidget(self.startImportBtn)

    def updateFileList(self, index=0):
        self.model.setNameFilters((self.FORMATS[index],))
        self.fileListView.setRootIndex(self.model.setRootPath("examples"))

    def getDeviceName(self):
        return self.deviceComboBox.currentText()

    def getFilePath(self):
        return self.model.filePath(self.fileListView.currentIndex())


class EmptyIconProvider(QFileIconProvider):

    def __init__(self):
        super().__init__()

    def icon(self, fileInfo):
        return QIcon()
