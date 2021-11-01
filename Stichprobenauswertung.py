
import sys
from PyQt5.QtWidgets import QApplication
from SampleModel import SampleModel
from MainController import MainController
from MainWindow import MainWindow

__version__ = "1.0.0"


def main():
    app = QApplication(sys.argv)

    model = SampleModel()
    controller = MainController(model)
    window = MainWindow(model, controller)
    
    window.show()

    app.exec()

if __name__ == '__main__':
    main()