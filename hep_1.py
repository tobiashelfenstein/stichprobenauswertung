from pywinauto import Desktop, Application

app = Application().connect(path=r"Z:\Downloads\HEPWFP\RhPf.exe")
hep = app.window(title_re=".*Holzaufnahme LF Rheinland-Pfalz")

hep.type_keys("22")
hep.type_keys("{ENTER}")
hep.type_keys("21")
hep.type_keys("{ENTER}")
hep.type_keys("25")
hep.type_keys("{ENTER}")
hep.type_keys("26")
hep.type_keys("{ENTER}")
hep.type_keys("21")
hep.type_keys("{ENTER}")
hep.type_keys("11")
hep.type_keys("{ENTER}")
hep.type_keys("18")
hep.type_keys("{ENTER}")
hep.type_keys("12")
hep.type_keys("{ENTER}")
hep.type_keys("13")
hep.type_keys("{ENTER}")
hep.type_keys("38")
hep.type_keys("{ENTER}")
hep.type_keys("28")
hep.type_keys("{ENTER}")


#hep.type_keys("{ESC}")