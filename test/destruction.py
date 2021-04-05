from geant4_pybind import *

runManager = G4RunManagerFactory.CreateRunManager(G4RunManagerType.Default)

physicsList1 = QBBC()

del physicsList1

physicsList2 = QBBC()
physicsList3 = QBBC()
runManager.SetUserInitialization(physicsList2)

del physicsList2

del runManager
