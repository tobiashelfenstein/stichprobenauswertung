
import sys
from PyQt5.QtWidgets import QApplication
from PyQt5.QtGui import QFont
from SampleModel import SampleModel
from MainController import MainController
from MainWindow import MainWindow

__version__ = "1.0.0"


def main():
    app = QApplication(sys.argv)

    # general font settings
    font = app.font()
    font.setPointSize(24)
    app.setFont(font)

    model = SampleModel()
    controller = MainController(model)
    window = MainWindow(model, controller)
    
    window.show()

    app.exec()

if __name__ == '__main__':
    main()