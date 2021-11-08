
import sys
import os
from cx_Freeze import setup, Executable

# delete old build folder
os.system("rd /s /q build")


base = None
if sys.platform == 'win32':
    base = 'Win32GUI'


options = {
    'build_exe': {
        #"excludes": ["PyQt5.QtSensors", "PyQt5.QtWebChannel", "PyQt5.QtMultimedia"],
        "packages": ["os", "sys", "pywinauto", "serial"],
        #"includes": ["atexit"],
        "include_files" : ["examples"],
        "include_msvcr": True
    }
}

executables = [
    Executable('Stichprobenauswertung.py',
               base=base,
               targetName = 'stichprobenauswertung.exe')
]

setup(name='Stichprobenauswertung',
      version = '0.0.1',
      description = 'Stichprobenauswertung',
      options = options,
      executables = executables)