from geant4_pybind import *
import sys

ui = G4UIExecutive(len(sys.argv), sys.argv)
ui.SessionStart()
