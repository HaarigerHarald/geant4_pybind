from geant4_pybind import *

import sys

# Choose specific analysis manager
G4AnalysisManager = G4RootAnalysisManager


class B4cDetectorConstruction(G4VUserDetectorConstruction):

    def __init__(self):
        super().__init__()
        self.fCheckOverlaps = True

    def DefineMaterials(self):
        # Lead material defined using NIST Manager
        nistManager = G4NistManager.Instance()
        nistManager.FindOrBuildMaterial("G4_Pb")

        # Liquid argon material
        G4Material("liquidArgon", z=18, a=39.95*g/mole, density=1.390*g/cm3)
        # The argon by NIST Manager is a gas with a different density

        # Vacuum
        G4Material("Galactic", z=1, a=1.01*g/mole, density=universe_mean_density,
                   state=kStateGas, temp=2.73*kelvin, pressure=3e-18*pascal)

        # Print materials
        print(G4Material.GetMaterialTable())

    def DefineVolumes(self):
        # Geometry parameters
        self.fNofLayers = 10
        absoThickness = 10*mm
        gapThickness = 5*mm
        calorSizeXY = 10*cm

        layerThickness = absoThickness + gapThickness
        calorThickness = self.fNofLayers * layerThickness
        worldSizeXY = 1.2 * calorSizeXY
        worldSizeZ = 1.2 * calorThickness

        # Get materials
        defaultMaterial = G4Material.GetMaterial("Galactic")
        absorberMaterial = G4Material.GetMaterial("G4_Pb")
        gapMaterial = G4Material.GetMaterial("liquidArgon")

        if defaultMaterial == None or absorberMaterial == None or gapMaterial == None:
            msg = "Cannot retrieve materials already defined."
            G4Exception("B4DetectorConstruction::DefineVolumes()",
                        "MyCode0001", FatalException, msg)

        # World
        worldS = G4Box("World",                                     # its name
                       worldSizeXY/2, worldSizeXY/2, worldSizeZ/2)  # its size

        worldLV = G4LogicalVolume(worldS,           # its solid
                                  defaultMaterial,  # its material
                                  "World")          # its name

        worldPV = G4PVPlacement(None,                 # no rotation
                                G4ThreeVector(),      # at (0,0,0)
                                worldLV,              # its logical volume
                                "World",              # its name
                                None,                 # its mother  volume
                                False,                # no boolean operation
                                0,                    # copy number
                                self.fCheckOverlaps)  # checking overlaps

        # Calorimeter
        calorimeterS = G4Box("Calorimeter",                                   # its name
                             calorSizeXY/2, calorSizeXY/2, calorThickness/2)  # its size

        calorLV = G4LogicalVolume(calorimeterS,     # its solid
                                  defaultMaterial,  # its material
                                  "Calorimeter")    # its name

        G4PVPlacement(None,                 # no rotation
                      G4ThreeVector(),      # at (0,0,0)
                      calorLV,              # its logical volume
                      "Calorimeter",        # its name
                      worldLV,              # its mother  volume
                      False,                # no boolean operation
                      0,                    # copy number
                      self.fCheckOverlaps)  # checking overlaps

        # Layer
        layerS = G4Box("Layer",                                         # its name
                       calorSizeXY/2, calorSizeXY/2, layerThickness/2)  # its size

        layerLV = G4LogicalVolume(layerS,           # its solid
                                  defaultMaterial,  # its material
                                  "Layer")          # its name

        G4PVReplica("Layer",          # its name
                    layerLV,          # its logical volume
                    calorLV,          # its mother
                    kZAxis,           # axis of replication
                    self.fNofLayers,  # number of replica
                    layerThickness)   # width of replica

        # Absorber
        absorberS = G4Box("Abso",                                         # its name
                          calorSizeXY/2, calorSizeXY/2, absoThickness/2)  # its size

        absorberLV = G4LogicalVolume(absorberS,         # its solid
                                     absorberMaterial,  # its material
                                     "AbsoLV")          # its name

        self.fAbsorberPV = G4PVPlacement(None,                                  # no rotation
                                         G4ThreeVector(0, 0, -gapThickness/2),  # its position
                                         absorberLV,                            # its logical volume
                                         "Abso",                                # its name
                                         layerLV,                               # its mother  volume
                                         False,                                 # no boolean operation
                                         0,                                     # copy number
                                         self.fCheckOverlaps)                   # checking overlaps

        # Gap
        gapS = G4Box("Gap",                                         # its name
                     calorSizeXY/2, calorSizeXY/2, gapThickness/2)  # its size

        gapLV = G4LogicalVolume(gapS,         # its solid
                                gapMaterial,  # its material
                                "GapLV")      # its name

        self.fGapPV = G4PVPlacement(None,                                  # no rotation
                                    G4ThreeVector(0, 0, absoThickness/2),  # its position
                                    gapLV,                                 # its logical volume
                                    "Gap",                                 # its name
                                    layerLV,                               # its mother volume
                                    False,                                 # no boolean operation
                                    0,                                     # copy number
                                    self.fCheckOverlaps)                   # checking overlaps

        # print parameters
        print("")
        print("------------------------------------------------------------")
        print("---> The calorimeter is", self.fNofLayers, "layers of: [", end="")
        print(absoThickness/mm, "mm of",  absorberMaterial.GetName(), "+", end="")
        print(gapThickness/mm, "mm of", gapMaterial.GetName(), "]")
        print("------------------------------------------------------------")

        # Visualization attributes
        worldLV.SetVisAttributes(G4VisAttributes.GetInvisible())

        simpleBoxVisAtt = G4VisAttributes(G4Colour(1, 1, 1))
        simpleBoxVisAtt.SetVisibility(True)
        calorLV.SetVisAttributes(simpleBoxVisAtt)

        # Always return the physical World
        return worldPV

    def Construct(self):
        self.DefineMaterials()
        return self.DefineVolumes()

    def ConstructSDandField(self):
        # G4SDManager::GetSDMpointer()->SetVerboseLevel(1)

        # Sensitive detectors
        absoSD = B4cCalorimeterSD("AbsorberSD", "AbsorberHitsCollection", self.fNofLayers)
        G4SDManager.GetSDMpointer().AddNewDetector(absoSD)
        self.SetSensitiveDetector("AbsoLV", absoSD)

        gapSD = B4cCalorimeterSD("GapSD", "GapHitsCollection", self.fNofLayers)
        G4SDManager.GetSDMpointer().AddNewDetector(gapSD)
        self.SetSensitiveDetector("GapLV", gapSD)

        # Create global magnetic field messenger.
        # Uniform magnetic field is then created automatically if
        # the field value is not zero.
        fieldValue = G4ThreeVector()
        self.fMagFieldMessenger = G4GlobalMagFieldMessenger(fieldValue)
        self.fMagFieldMessenger.SetVerboseLevel(1)


class B4PrimaryGeneratorAction(G4VUserPrimaryGeneratorAction):

    def __init__(self):
        super().__init__()
        nofParticles = 1
        self.fParticleGun = G4ParticleGun(nofParticles)

        # default particle kinematic
        particleDefinition = G4ParticleTable.GetParticleTable().FindParticle("e-")
        self.fParticleGun.SetParticleDefinition(particleDefinition)
        self.fParticleGun.SetParticleMomentumDirection(G4ThreeVector(0, 0, 1))
        self.fParticleGun.SetParticleEnergy(50*MeV)

    def GeneratePrimaries(self, anEvent):
        # This function is called at the begining of an event

        # In order to avoid dependence of PrimaryGeneratorAction
        # on DetectorConstruction class we get world volume
        # from G4LogicalVolumeStore
        worldZHalfLength = 0
        worldLV = G4LogicalVolumeStore.GetInstance().GetVolume("World")

        # Check that the world volume has box shape
        worldBox = None
        if worldLV != None:
            worldBox = worldLV.GetSolid()

        if worldBox != None:
            worldZHalfLength = worldBox.GetZHalfLength()
        else:
            msg = "World volume of box shape not found."
            msg += "Perhaps you have changed geometry."
            msg += "The gun will be place in the center."
            G4Exception("B4PrimaryGeneratorAction::GeneratePrimaries()",
                        "MyCode0002", JustWarning, msg)

        # Set gun position
        self.fParticleGun.SetParticlePosition(G4ThreeVector(0, 0, -worldZHalfLength))
        self.fParticleGun.GeneratePrimaryVertex(anEvent)


class B4cCalorHit(G4VHit):

    def __init__(self):
        super().__init__()
        self.fEdep = 0
        self.fTrackLength = 0

    def Add(self, de, dl):
        self.fEdep += de
        self.fTrackLength += dl

    def Print(self):
        print("Edep: {:.5g} track length: {:.5g}".format(G4BestUnit(
            self.fEdep, "Energy"), G4BestUnit(self.fTrackLength, "Length")))


class B4cCalorHitsCollection(G4VHitsCollection):

    def __init__(self, detName, colNam):
        super().__init__(detName, colNam)
        self.collection = []

    def __getitem__(self, i):
        return self.collection[i]

    def insert(self, item):
        self.collection.append(item)

    def GetHit(self, i):
        return self.collection[i]

    def GetSize(self):
        return len(self.collection)


class B4cCalorimeterSD(G4VSensitiveDetector):

    def __init__(self, name, hitsCollectionName, nofCells):
        super().__init__(name)
        self.collectionName.insert(hitsCollectionName)
        self.fNofCells = nofCells

    def Initialize(self, hce):
        # Create hits collection
        self.fHitsCollection = B4cCalorHitsCollection(
            self.SensitiveDetectorName, self.collectionName[0])

        # Add this collection in hce
        hcID = G4SDManager.GetSDMpointer().GetCollectionID(self.collectionName[0])
        hce.AddHitsCollection(hcID, self.fHitsCollection)

        # Create hits
        # fNofCells for cells + one more for total sums
        for i in range(self.fNofCells + 1):
            self.fHitsCollection.insert(B4cCalorHit())

    def ProcessHits(self, step, history):
        # energy deposit
        edep = step.GetTotalEnergyDeposit()

        # step length
        stepLength = 0
        if step.GetTrack().GetDefinition().GetPDGCharge() != 0:
            stepLength = step.GetStepLength()

        if edep == 0 and stepLength == 0:
            return False

        touchable = step.GetPreStepPoint().GetTouchable()

        # Get calorimeter cell id
        layerNumber = touchable.GetReplicaNumber(1)

        # Get hit accounting data for this cell
        hit = self.fHitsCollection[layerNumber]
        if hit == None:
            msg = "Cannot access hit " + str(layerNumber)
            G4Exception("B4cCalorimeterSD::ProcessHits()",
                        "MyCode0004", FatalException, msg)

        # Get hit for total accounting
        hitTotal = self.fHitsCollection[self.fHitsCollection.GetSize()-1]

        # Add values
        hit.Add(edep, stepLength)
        hitTotal.Add(edep, stepLength)

        return True

    def EndOfEvent(self, hCofThisEvent):
        if self.verboseLevel > 1:
            nofHits = self.fHitsCollection.GetSize()
            print("")
            print("-------->Hits Collection: in this event they are", nofHits, end="")
            print(" hits in the tracker chambers: ")
            for i in range(nofHits):
                self.fHitsCollection[i].Print()


class B4cEventAction(G4UserEventAction):

    def __init__(self):
        super().__init__()
        self.fAbsHCID = None
        self.fGapHCID = None

    def GetHitsCollection(self, hcID, event):
        hitsCollection = event.GetHCofThisEvent().GetHC(hcID)

        if hitsCollection == None:
            msg = "Cannot access hitsCollection ID " + str(hcID)
            G4Exception("B4cEventAction::GetHitsCollection()",
                        "MyCode0003", FatalException, msg)

        return hitsCollection

    def EndOfEventAction(self, event):
        # Get hits collections IDs (only once)
        if self.fAbsHCID == None:
            self.fAbsHCID = G4SDManager.GetSDMpointer().GetCollectionID("AbsorberHitsCollection")
            self.fGapHCID = G4SDManager.GetSDMpointer().GetCollectionID("GapHitsCollection")

        # Get hits collections
        absoHC = self.GetHitsCollection(self.fAbsHCID, event)
        gapHC = self.GetHitsCollection(self.fGapHCID, event)

        # Get hit with total values
        absoHit = absoHC[absoHC.GetSize()-1]
        gapHit = gapHC[gapHC.GetSize()-1]

        # Print per event (modulo n)
        eventID = event.GetEventID()
        printModulo = G4RunManager.GetRunManager().GetPrintProgress()
        if printModulo > 0 and eventID % printModulo == 0:
            print("---> End of event:", eventID)
            print("   Absorber: total energy:", G4BestUnit(absoHit.fEdep, "Energy"), end="")
            print("       total track length:", G4BestUnit(absoHit.fTrackLength, "Length"))
            print("        Gap: total energy:", G4BestUnit(gapHit.fEdep, "Energy"), end="")
            print("       total track length:", G4BestUnit(gapHit.fTrackLength, "Length"))

        # Fill histograms, ntuple
        # get analysis manager
        analysisManager = G4AnalysisManager.Instance()

        # fill histograms
        analysisManager.FillH1(0, absoHit.fEdep)
        analysisManager.FillH1(1, gapHit.fEdep)
        analysisManager.FillH1(2, absoHit.fTrackLength)
        analysisManager.FillH1(3, gapHit.fTrackLength)

        # fill ntuple
        analysisManager.FillNtupleDColumn(0, absoHit.fEdep)
        analysisManager.FillNtupleDColumn(1, gapHit.fEdep)
        analysisManager.FillNtupleDColumn(2, absoHit.fTrackLength)
        analysisManager.FillNtupleDColumn(3, gapHit.fTrackLength)
        analysisManager.AddNtupleRow()


class B4RunAction(G4UserRunAction):

    def __init__(self):
        super().__init__()

        # set printing event number per each event
        G4RunManager.GetRunManager().SetPrintProgress(1)

        # Create analysis manager
        analysisManager = G4AnalysisManager.Instance()
        print("Using", analysisManager.GetType())

        # Create directories
        # analysisManager.SetHistoDirectoryName("histograms")
        # analysisManager.SetNtupleDirectoryName("ntuple")
        analysisManager.SetVerboseLevel(1)
        analysisManager.SetNtupleMerging(True)
        # Note: merging ntuples is available only with Root output

        # Book histograms, ntuple
        # Creating histograms
        analysisManager.CreateH1("Eabs", "Edep in absorber", 100, 0, 800*MeV)
        analysisManager.CreateH1("Egap", "Edep in gap", 100, 0, 100*MeV)
        analysisManager.CreateH1("Labs", "trackL in absorber", 100, 0, 1*m)
        analysisManager.CreateH1("Lgap", "trackL in gap", 100, 0, 50*cm)

        # Creating ntuple
        analysisManager.CreateNtuple("B4", "Edep and TrackL")
        analysisManager.CreateNtupleDColumn("Eabs")
        analysisManager.CreateNtupleDColumn("Egap")
        analysisManager.CreateNtupleDColumn("Labs")
        analysisManager.CreateNtupleDColumn("Lgap")
        analysisManager.FinishNtuple()

    def BeginOfRunAction(self, run):
        # inform the runManager to save random number seed
        # G4RunManager.GetRunManager().SetRandomNumberStore(True)

        # Get analysis manager
        analysisManager = G4AnalysisManager.Instance()

        # Open an output file
        fileName = "B4"
        analysisManager.OpenFile(fileName)

    def EndOfRunAction(self, run):

        # print histogram statistics
        analysisManager = G4AnalysisManager.Instance()
        if analysisManager.GetH1(1) != None:
            print("\n ----> print histograms statistic ", end="")

            if self.IsMaster():
                print("for the entire run \n")
            else:
                print("for the local thread \n")

            print(" EAbs : mean =", G4BestUnit(analysisManager.GetH1(0).mean(), "Energy"), end="")
            print(" rms =", G4BestUnit(analysisManager.GetH1(0).rms(),  "Energy"))

            print(" EGap : mean =", G4BestUnit(analysisManager.GetH1(1).mean(), "Energy"), end="")
            print(" rms =", G4BestUnit(analysisManager.GetH1(1).rms(),  "Energy"))

            print(" LAbs : mean = ", G4BestUnit(analysisManager.GetH1(2).mean(), "Length"), end="")
            print(" rms =", G4BestUnit(analysisManager.GetH1(2).rms(),  "Length"))

            print(" LGap : mean =", G4BestUnit(analysisManager.GetH1(3).mean(), "Length"), end="")
            print(" rms =", G4BestUnit(analysisManager.GetH1(3).rms(),  "Length"))

        # save histograms & ntuple
        analysisManager.Write()
        analysisManager.CloseFile()


class B4cActionInitialization(G4VUserActionInitialization):

    def __init__(self, detConstruction):
        super().__init__()
        self.fDetConstruction = detConstruction

    def BuildForMaster(self):
        self.SetUserAction(B4RunAction())

    def Build(self):
        self.SetUserAction(B4PrimaryGeneratorAction())
        self.SetUserAction(B4RunAction())
        self.SetUserAction(B4cEventAction())


def PrintUsage():
    print(" Usage: ", file=sys.stderr)
    print(" python exampleB4a.py [-m macro ] [-u UIsession] [-t nThreads]", file=sys.stderr)
    print("   note: -t option is available only for multi-threaded mode.", file=sys.stderr)


# Evaluate arguments
if len(sys.argv) > 7:
    PrintUsage()
    sys.exit(1)

macro = ""
session = ""

for i in range(1, len(sys.argv), 2):
    if sys.argv[i] == "-m":
        macro = sys.argv[i+1]
    elif sys.argv[i] == "-u":
        session = sys.argv[i+1]
    else:
        PrintUsage()
        sys.exit(1)

# Detect interactive mode (if no macro provided) and define UI session
ui = None
if len(macro) == 0:
    ui = G4UIExecutive(len(sys.argv), sys.argv, session)

# Optionally: choose a different Random engine...
# G4Random.setTheEngine(MTwistEngine())

# Construct the default run manager
runManager = G4RunManagerFactory.CreateRunManager(G4RunManagerType.Default)

# Set mandatory initialization classes
detConstruction = B4cDetectorConstruction()
runManager.SetUserInitialization(detConstruction)

physicsList = FTFP_BERT()
runManager.SetUserInitialization(physicsList)

actionInitialization = B4cActionInitialization(detConstruction)
runManager.SetUserInitialization(actionInitialization)

# Initialize visualization
visManager = G4VisExecutive()
# G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
# visManager = G4VisExecutive("Quiet")
visManager.Initialize()

# Get the User Interface manager
UImanager = G4UImanager.GetUIpointer()

# Process macro or start UI session
if len(macro) > 0:
    # batch mode
    command = "/control/execute "
    UImanager.ApplyCommand(command+macro)
else:
    # interactive mode : define UI session
    UImanager.ApplyCommand("/control/execute init_vis.mac")
    if ui.IsGUI():
        UImanager.ApplyCommand("/control/execute gui.mac")
    ui.SessionStart()
