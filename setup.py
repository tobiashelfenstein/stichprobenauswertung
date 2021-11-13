
import sys
import os
from cx_Freeze import setup, Executable

# delete old build folder
os.system("rd /s /q build")

try:
    from cx_Freeze.hooks import get_qt_plugins_paths
except ImportError:
    include_files = []
else:
    # Inclusion of extra plugins (new in cx_Freeze 6.8b2)
    # cx_Freeze imports automatically the following plugins depending of the
    # use of some modules:
    # imageformats - QtGui
    # platforms - QtGui
    # mediaservice - QtMultimedia
    # printsupport - QtPrintSupport
    #
    # So, "platforms" is used here for demonstration purposes.
    include_files = get_qt_plugins_paths("PyQt5", "platforms")

base = None
if sys.platform == 'win32':
    base = 'Win32GUI'


build_exe_options = {
    "excludes": ["tkinter"],
    "include_files": include_files,
    "include_files" : ["examples", "resources"],
    "include_msvcr": True
}

executables = [
    Executable("Stichprobenauswertung.py",
               base=base,
               target_name="stichprobenauswertung")
]

setup(
    name="Stichprobenauswertung",
    version="0.0.1",
    description="Stichprobenauswertung für HEP",
    options={
        "build_exe": build_exe_options,
    },
    executables=executables,
)
