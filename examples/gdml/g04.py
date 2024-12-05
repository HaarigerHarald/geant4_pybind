from geant4_pybind import *
import sys


class G04SensitiveDetector(G4VSensitiveDetector):

    def ProcessHits(self, step, history):
        print("Processing hits ....")
        return True


class G04DetectorConstruction(G4VUserDetectorConstruction):

    def __init__(self, parser):
        super().__init__()
        self.fParser = parser

    def Construct(self):
        return self.fParser.GetWorldVolume()

    def ConstructSDandField(self):
        # Sensitive detectors
        SDman = G4SDManager.GetSDMpointer()

        aTrackerSD = G04SensitiveDetector("Tracker")
        SDman.AddNewDetector(aTrackerSD)

        # Example how to retrieve Auxiliary Information for sensitive detector
        auxmap = self.fParser.GetAuxMap()
        print("Found", len(auxmap), "volume(s) with auxiliary information.\n")

        for volume, auxList in auxmap.items():
            print("Volume", volume.GetName(), "has the following list of auxiliary information:\n")

            for aux in auxList:
                print("--> Type:", aux.type, "Value:", aux.value)

        print()

        # The same as above, but now we are looking for
        # sensitive detectors setting them for the volumes
        for volume, auxList in auxmap.items():
            print("Volume", volume.GetName(), "has the following list of auxiliary information:\n")

            for aux in auxList:
                if aux.type == "SensDet":
                    print("Attaching sensitive detector", aux.value,
                          "to volume", volume.GetName(), "\n")

                    mydet = SDman.FindSensitiveDetector(aux.value)
                    if mydet != None:
                        volume.SetSensitiveDetector(mydet)
                    else:
                        print(aux.value, "detector not found")


class G04PrimaryGeneratorAction(G4VUserPrimaryGeneratorAction):

    def __init__(self):
        super().__init__()
        self.fParticleGun = G4ParticleGun(1)

        particleTable = G4ParticleTable.GetParticleTable()
        self.fParticleGun.SetParticleDefinition(particleTable.FindParticle("geantino"))
        self.fParticleGun.SetParticleEnergy(1.0*GeV)
        self.fParticleGun.SetParticlePosition(G4ThreeVector(-2.0*m, 0.1, 0.1))

    def GeneratePrimaries(self, anEvent):
        i = anEvent.GetEventID() % 3
        v = G4ThreeVector(1, 0, 0)
        if i == 1:
            v.y = 0.1
        elif i == 2:
            v.z = 0.1

        self.fParticleGun.SetParticleMomentumDirection(v)
        self.fParticleGun.GeneratePrimaryVertex(anEvent)


class G04ActionInitialization(G4VUserActionInitialization):

    def Build(self):
        self.SetUserAction(G04PrimaryGeneratorAction())


print("Usage: python3 gdml_det.py <intput_gdml_file:mandatory>\n")
if len(sys.argv) < 2:
    print("Error! Mandatory input file is not specified!\n")
    exit(-1)

# Detect interactive mode (if only one argument) and define UI session
ui = None
if len(sys.argv) == 2:
    ui = G4UIExecutive(len(sys.argv), sys.argv)


parser = G4GDMLParser()
parser.Read(sys.argv[1], False)

runManager = G4RunManagerFactory.CreateRunManager(G4RunManagerType.Serial)

runManager.SetUserInitialization(G04DetectorConstruction(parser))
runManager.SetUserInitialization(FTFP_BERT())

# User action initialization
runManager.SetUserInitialization(G04ActionInitialization())
runManager.Initialize()

# Initialize visualization
visManager = G4VisExecutive()
visManager.Initialize()

# Get the pointer to the User Interface manager
UImanager = G4UImanager.GetUIpointer()

# Process macro or start UI session
if ui == None:  # batch mode
    command = "/control/execute "
    fileName = sys.argv[2]
    UImanager.ApplyCommand(command+fileName)
else:  # interactive mode
    UImanager.ApplyCommand("/control/execute vis.mac")
    ui.SessionStart()
