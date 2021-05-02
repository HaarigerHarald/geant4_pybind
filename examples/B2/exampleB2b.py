from geant4_pybind import *
import sys


class B2bDetectorMessenger(G4UImessenger):

    def __init__(self, detector):
        super().__init__()
        self.fDetectorConstruction = detector

        self.fB2Directory = G4UIdirectory("/B2/")
        self.fB2Directory.SetGuidance("UI commands specific to this example.")

        self.fDetDirectory = G4UIdirectory("/B2/det/")
        self.fDetDirectory.SetGuidance("Detector construction control")

        self.fTargMatCmd = G4UIcmdWithAString("/B2/det/setTargetMaterial", self)
        self.fTargMatCmd.SetGuidance("Select Material of the Target.")
        self.fTargMatCmd.SetParameterName("choice", False)
        self.fTargMatCmd.AvailableForStates(G4State_PreInit, G4State_Idle)

        self.fChamMatCmd = G4UIcmdWithAString("/B2/det/setChamberMaterial", self)
        self.fChamMatCmd.SetGuidance("Select Material of the Chamber.")
        self.fChamMatCmd.SetParameterName("choice", False)
        self.fChamMatCmd.AvailableForStates(G4State_PreInit, G4State_Idle)

        self.fStepMaxCmd = G4UIcmdWithADoubleAndUnit("/B2/det/stepMax", self)
        self.fStepMaxCmd.SetGuidance("Define a step max")
        self.fStepMaxCmd.SetParameterName("stepMax", False)
        self.fStepMaxCmd.SetUnitCategory("Length")
        self.fStepMaxCmd.AvailableForStates(G4State_Idle)

    def SetNewValue(self, command, newValue):
        if command == self.fTargMatCmd:
            self.fDetectorConstruction.SetTargetMaterial(newValue)
        elif command == self.fChamMatCmd:
            self.fDetectorConstruction.SetChamberMaterial(newValue)
        elif command == self.fStepMaxCmd:
            self.fDetectorConstruction.SetMaxStep(
                G4UIcmdWithADoubleAndUnit.GetNewDoubleValue(newValue))


class B2TrackerHit(G4VHit):

    def __init__(self, trackID, chamberNb, edep, pos):
        super().__init__()
        self.fTrackID = trackID
        self.fChamberNb = chamberNb
        self.fEdep = edep
        self.fPos = pos

    def Draw(self):
        vVisManager = G4VVisManager.GetConcreteInstance()
        if vVisManager != None:
            circle = G4Circle(self.fPos)
            circle.SetScreenSize(4)
            circle.SetFillStyle(G4Circle.filled)
            colour = G4Colour(1, 0, 0)
            attribs = G4VisAttributes(colour)
            circle.SetVisAttributes(attribs)
            vVisManager.Draw(circle)

    def Print(self):
        print("trackID:", self.fTrackID, "chamberNb:", self.fChamberNb, "Edep:", end=" ")
        print(G4BestUnit(self.fEdep, "Energy"), "Position:", G4BestUnit(self.fPos, "Length"))


class B2HitsCollection(G4VHitsCollection):

    def __init__(self, detName, colNam):
        super().__init__(detName, colNam)
        self.collection = []

    def __getitem__(self, i):
        return self.collection[i]

    def insert(self, item):
        self.collection.append(item)

    def entries(self):
        return len(self.collection)

    def GetSize(self):
        return len(self.collection)


class B2TrackerSD(G4VSensitiveDetector):

    def __init__(self, name, hitsCollectionName):
        super().__init__(name)
        self.collectionName.insert(hitsCollectionName)

    def Initialize(self, hce):
        # Create hits collection
        # self.fHitsCollection = None
        self.fHitsCollection = B2HitsCollection(
            self.SensitiveDetectorName, self.collectionName[0])

        # Add this collection in hce
        hcID = G4SDManager.GetSDMpointer().GetCollectionID(self.collectionName[0])
        hce.AddHitsCollection(hcID, self.fHitsCollection)

    def ProcessHits(self, aStep, rOhist):
        # energy deposit
        edep = aStep.GetTotalEnergyDeposit()
        if edep == 0:
            return False

        newHit = B2TrackerHit(aStep.GetTrack().GetTrackID(),
                              aStep.GetPreStepPoint().GetTouchable().GetCopyNumber(),
                              edep,
                              aStep.GetPostStepPoint().GetPosition())

        self.fHitsCollection.insert(newHit)
        # newHit.Print()
        return True

    def EndOfEvent(self, hce):
        if self.verboseLevel > 1:
            nofHits = self.fHitsCollection.entries()
            print("-------->Hits Collection: in this event there are", nofHits,
                  "hits in the tracker chambers:")
            for i in range(nofHits):
                self.fHitsCollection[i].Print()


class B2bChamberParameterisation(G4VPVParameterisation):

    def __init__(self, noChambers, startZ, spacingZ, widthChamber, lengthInitial, lengthFinal):
        super().__init__()
        self.fNoChambers = noChambers
        self.fStartZ = startZ
        self.fHalfWidth = 0.5*widthChamber
        self.fSpacing = spacingZ
        self.fRmaxFirst = 0.5*lengthInitial
        if noChambers > 0:
            self.fRmaxIncr = 0.5*(lengthFinal-lengthInitial)/(noChambers-1)
            if spacingZ < widthChamber:
                G4Exception("B2bChamberParameterisation::B2bChamberParameterisation()",
                            "InvalidSetup", G4ExceptionSeverity.FatalException,
                            "Width>Spacing")

    def ComputeTransformation(self, copyNo, physVol):
        # Note: copyNo will start with zero!
        Zposition = self.fStartZ + copyNo * self.fSpacing
        origin = G4ThreeVector(0, 0, Zposition)
        physVol.SetTranslation(origin)
        physVol.SetRotation(None)

    def ComputeDimensions(self, trackerChamber, copyNo, vol):
        # Note: copyNo will start with zero!
        rmax = self.fRmaxFirst + copyNo * self.fRmaxIncr
        trackerChamber.SetInnerRadius(0)
        trackerChamber.SetOuterRadius(rmax)
        trackerChamber.SetZHalfLength(self.fHalfWidth)
        trackerChamber.SetStartPhiAngle(0*deg)
        trackerChamber.SetDeltaPhiAngle(360*deg)


class B2bDetectorConstruction(G4VUserDetectorConstruction):

    def __init__(self):
        super().__init__()
        self.fMessenger = B2bDetectorMessenger(self)

        self.fNbOfChambers = 5
        self.fLogicChamber = []
        self.fCheckOverlaps = True

    def DefineMaterials(self):
        nistManager = G4NistManager.Instance()

        # Air defined using NIST Manager
        nistManager.FindOrBuildMaterial("G4_AIR")

        # Lead defined using NIST Manager
        self.fTargetMaterial = nistManager.FindOrBuildMaterial("G4_Pb")

        # Xenon gas defined using NIST Manager
        self.fChamberMaterial = nistManager.FindOrBuildMaterial("G4_Xe")

        # Print materials
        print(G4Material.GetMaterialTable())

    def DefineVolumes(self):
        air = G4Material.GetMaterial("G4_AIR")

        # Sizes of the principal geometrical components (solids)

        chamberSpacing = 80*cm  # from chamber center to center!

        chamberWidth = 20*cm  # width of the chambers
        targetLength = 5*cm   # full length of Target

        trackerLength = (self.fNbOfChambers+1)*chamberSpacing

        worldLength = 1.2 * (2*targetLength + trackerLength)

        targetRadius = 0.5*targetLength   # Radius of Target
        targetLength = 0.5*targetLength   # Half length of the Target
        trackerSize = 0.5*trackerLength   # Half length of the Tracker

        # Definitions of Solids, Logical Volumes, Physical Volumes  World
        G4GeometryManager.GetInstance().SetWorldMaximumExtent(worldLength)

        print("Computed tolerance =",
              G4GeometryTolerance.GetInstance().GetSurfaceTolerance()/mm, "mm")

        worldS = G4Box("world",                                      # its name
                       worldLength/2, worldLength/2, worldLength/2)  # its size

        worldLV = G4LogicalVolume(
            worldS,    # its solid
            air,       # its material
            "World")   # its name

        # Must place the World Physical volume unrotated at (0,0,0).
        worldPV = G4PVPlacement(
            None,                  # no rotation
            G4ThreeVector(),       # at (0,0,0)
            worldLV,               # its logical volume
            "World",               # its name
            None,                  # its mother  volume
            False,                 # no boolean operations
            0,                     # copy number
            self.fCheckOverlaps)   # checking overlaps

        # Target
        positionTarget = G4ThreeVector(0, 0, -(targetLength+trackerSize))

        targetS = G4Tubs("target", 0, targetRadius, targetLength, 0*deg, 360*deg)
        self.fLogicTarget = G4LogicalVolume(
            targetS, self.fTargetMaterial, "Target", None, None, None)

        G4PVPlacement(None,                 # no rotation
                      positionTarget,       # at (x,y,z)
                      self.fLogicTarget,    # its logical volume
                      "Target",             # its name
                      worldLV,              # its mother volume
                      False,                # no boolean operations
                      0,                    # copy number
                      self.fCheckOverlaps)  # checking overlaps

        print("Target is", 2*targetLength/cm, "cm of", self.fTargetMaterial.GetName())

        # Tracker
        positionTracker = G4ThreeVector(0, 0, 0)
        trackerS = G4Tubs("tracker", 0, trackerSize, trackerSize, 0*deg, 360*deg)

        trackerLV = G4LogicalVolume(trackerS, air, "Tracker", None, None, None)

        G4PVPlacement(None,                 # no rotation
                      positionTracker,      # at (x,y,z)
                      trackerLV,            # its logical volume
                      "Tracker",            # its name
                      worldLV,              # its mother  volume
                      False,                # no boolean operations
                      0,                    # copy number
                      self.fCheckOverlaps)  # checking overlaps

        # Tracker segments

        # An example of Parameterised volumes
        # Dummy values for G4Tubs -- modified by parameterised volume
        chamberS = G4Tubs("tracker", 0, 100*cm, 100*cm, 0*deg, 360*deg)
        self.fLogicChamber = G4LogicalVolume(
            chamberS, self.fChamberMaterial, "Chamber", None, None, None)

        firstPosition = -trackerSize + chamberSpacing
        firstLength = trackerLength/10
        lastLength = trackerLength

        chamberParam = B2bChamberParameterisation(self.fNbOfChambers,  # NoChambers
                                                  firstPosition,       # Z of center of first
                                                  chamberSpacing,      # Z spacing of centers
                                                  chamberWidth,        # chamber width
                                                  firstLength,         # initial length
                                                  lastLength)          # final length

        # dummy value : kZAxis -- modified by parameterised volume
        G4PVParameterised("Chamber",            # their name
                          self.fLogicChamber,   # their logical volume
                          trackerLV,            # Mother logical volume
                          EAxis.kZAxis,         # Are placed along this axis
                          self.fNbOfChambers,   # Number of chambers
                          chamberParam,         # The parametrisation
                          self.fCheckOverlaps)  # checking overlaps

        print("There are", self.fNbOfChambers, "chambers in the tracker region.")
        print("The chambers are", chamberWidth/cm, "cm of", self.fChamberMaterial.GetName())
        print("The distance between chamber is", chamberSpacing/cm, "cm")

        # Visualization attributes
        boxVisAtt = G4VisAttributes(G4Colour(1, 1, 1))
        worldLV.SetVisAttributes(boxVisAtt)
        self.fLogicTarget.SetVisAttributes(boxVisAtt)
        trackerLV.SetVisAttributes(boxVisAtt)

        chamberVisAtt = G4VisAttributes(G4Colour(1, 1, 0))
        self.fLogicChamber.SetVisAttributes(chamberVisAtt)

        # Example of User Limits
        # Below is an example of how to set tracking constraints in a given
        # logical volume
        # Sets a max step length in the tracker region, with G4StepLimiter

        maxStep = 0.5*chamberWidth
        self.fStepLimit = G4UserLimits(maxStep)
        trackerLV.SetUserLimits(self.fStepLimit)

        # Set additional constraints on the track, with G4UserSpecialCuts
        #
        # maxLength = 2*trackerLength
        # maxTime = 0.1*ns
        # minEkin = 10*MeV
        # trackerLV.SetUserLimits(G4UserLimits(maxStep, maxLength, maxTime, minEkin))

        # Always return the physical world
        return worldPV

    def Construct(self):
        self.DefineMaterials()
        return self.DefineVolumes()

    def ConstructSDandField(self):
        # Sensitive detectors
        trackerChamberSDname = "B2/TrackerChamberSD"
        aTrackerSD = B2TrackerSD(trackerChamberSDname, "TrackerHitsCollection")
        G4SDManager.GetSDMpointer().AddNewDetector(aTrackerSD)
        self.SetSensitiveDetector(self.fLogicChamber, aTrackerSD)

        # Create global magnetic field messenger.
        # Uniform magnetic field is then created automatically if
        # the field value is not zero.
        fieldValue = G4ThreeVector()
        self.fMagFieldMessenger = G4GlobalMagFieldMessenger(fieldValue)
        self.fMagFieldMessenger.SetVerboseLevel(1)

    def SetTargetMaterial(self, materialName):
        nistManager = G4NistManager.Instance()
        pttoMaterial = nistManager.FindOrBuildMaterial(materialName)
        if self.fTargetMaterial != pttoMaterial:
            if pttoMaterial != None:
                self.fTargetMaterial = pttoMaterial
                if self.fLogicTarget != None:
                    self.fLogicTarget.SetMaterial(self.fTargetMaterial)
                print("\n----> The target is made of", materialName)
            else:
                print("\n-->  WARNING from SetTargetMaterial :", materialName, "not found")

    def SetChamberMaterial(self, materialName):
        nistManager = G4NistManager.Instance()
        pttoMaterial = nistManager.FindOrBuildMaterial(materialName)
        if self.fChamberMaterial != pttoMaterial:
            if pttoMaterial != None:
                self.fChamberMaterial = pttoMaterial
                if self.fLogicChamber != None:
                    self.fLogicChamber.SetMaterial(self.fChamberMaterial)
                print("\n----> The chambers are made of", materialName)
            else:
                print("\n-->  WARNING from SetChamberMaterial :", materialName, "not found")

    def SetMaxStep(self, maxStep):
        if self.fStepLimit != None and maxStep > 0:
            self.fStepLimit.SetMaxAllowedStep(maxStep)

    def SetCheckOverlaps(self, checkOverlaps):
        self.fCheckOverlaps = checkOverlaps


class B2RunAction(G4UserRunAction):

    def __init__(self):
        super().__init__()
        G4RunManager.GetRunManager().SetPrintProgress(1000)

    def BeginOfRunAction(self, aRun):
        # inform the runManager to save random number seed
        G4RunManager.GetRunManager().SetRandomNumberStore(False)


class B2PrimaryGeneratorAction(G4VUserPrimaryGeneratorAction):

    def __init__(self):
        super().__init__()
        nofParticles = 1
        self.fParticleGun = G4ParticleGun(nofParticles)

        # default particle kinematic
        particleDefinition = G4ParticleTable.GetParticleTable().FindParticle("proton")
        self.fParticleGun.SetParticleDefinition(particleDefinition)
        self.fParticleGun.SetParticleMomentumDirection(G4ThreeVector(0, 0, 1))
        self.fParticleGun.SetParticleEnergy(3*GeV)

    def GeneratePrimaries(self, anEvent):
        # This function is called at the begining of event

        # In order to avoid dependence of PrimaryGeneratorAction
        # on DetectorConstruction class we get world volume
        # from G4LogicalVolumeStore.
        worldZHalfLength = 0
        worldLV = G4LogicalVolumeStore.GetInstance().GetVolume("World")
        worldBox = None
        if worldLV != None:
            worldBox = worldLV.GetSolid()

        if worldBox != None:
            worldZHalfLength = worldBox.GetZHalfLength()
        else:
            print("World volume of box not found.", file=sys.stderr)
            print("Perhaps you have changed geometry.", file=sys.stderr)
            print("The gun will be place in the center.", file=sys.stderr)

        # Note that this particular case of starting a primary particle on the world boundary
        # requires shooting in a direction towards inside the world.
        self.fParticleGun.SetParticlePosition(G4ThreeVector(0, 0, -worldZHalfLength))
        self.fParticleGun.GeneratePrimaryVertex(anEvent)


class B2EventAction(G4UserEventAction):
    def EndOfEventAction(self, event):
        # get number of stored trajectories
        trajectoryContainer = event.GetTrajectoryContainer()
        n_trajectories = 0
        if trajectoryContainer != None:
            n_trajectories = trajectoryContainer.entries()

        # periodic printing
        eventID = event.GetEventID()
        if eventID < 100 or eventID % 100 == 0:
            print(">>> Event:", eventID)
            if trajectoryContainer != None:
                print("   ", n_trajectories, "trajectories stored in this event.")

            hc = event.GetHCofThisEvent().GetHC(0)
            print("   ", hc.GetSize(), "hits stored in this event")


class B2ActionInitialization(G4VUserActionInitialization):

    def BuildForMaster(self):
        self.SetUserAction(B2RunAction())

    def Build(self):
        self.SetUserAction(B2PrimaryGeneratorAction())
        self.SetUserAction(B2RunAction())
        self.SetUserAction(B2EventAction())


# Detect interactive mode (if no arguments) and define UI session
ui = None
if len(sys.argv) == 1:
    ui = G4UIExecutive(len(sys.argv), sys.argv)

# Optionally: choose a different Random engine...
# G4Random.setTheEngine(MTwistEngine())

# Construct the default run manager
runManager = G4RunManagerFactory.CreateRunManager(G4RunManagerType.Default)

# Set mandatory initialization classes
runManager.SetUserInitialization(B2bDetectorConstruction())

physicsList = FTFP_BERT()
physicsList.RegisterPhysics(G4StepLimiterPhysics())
runManager.SetUserInitialization(physicsList)

# Set user action classes
runManager.SetUserInitialization(B2ActionInitialization())

# Initialize visualization
visManager = G4VisExecutive()
# G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
# visManager = G4VisExecutive("Quiet");
visManager.Initialize()

# Get the pointer to the User Interface manager
UImanager = G4UImanager.GetUIpointer()

# Process macro or start UI session
if ui == None:
    # batch mode
    command = "/control/execute "
    fileName = sys.argv[1]
    UImanager.ApplyCommand(command+fileName)
else:
    # interactive mode
    UImanager.ApplyCommand("/control/execute init_vis.mac")
    if ui.IsGUI():
        UImanager.ApplyCommand("/control/execute gui.mac")
    ui.SessionStart()
