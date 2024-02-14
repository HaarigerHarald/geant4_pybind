from geant4_pybind import *

import multiprocessing.pool
import math
import sys
import os


class B1DetectorConstruction(G4VUserDetectorConstruction):

    def __init__(self):
        super().__init__()
        self.fScoringVolume = None

    def Construct(self):
        nist = G4NistManager.Instance()
        env_sizeXY = 20*cm
        env_sizeZ = 30*cm
        env_mat = nist.FindOrBuildMaterial("G4_WATER")

        # Option to switch on/off checking of volumes overlaps
        checkOverlaps = True

        # World
        world_sizeXY = 1.2*env_sizeXY
        world_sizeZ = 1.2*env_sizeZ
        world_mat = nist.FindOrBuildMaterial("G4_AIR")

        solidWorld = G4Box("World", 0.5*world_sizeXY, 0.5 *
                           world_sizeXY, 0.5*world_sizeZ)

        logicWorld = G4LogicalVolume(solidWorld, world_mat, "World")

        physWorld = G4PVPlacement(None,              # no rotation
                                  G4ThreeVector(),   # at (0,0,0)
                                  logicWorld,        # its logical volume
                                  "World",           # its name
                                  None,              # its mother  volume
                                  False,             # no boolean operation
                                  0,                 # copy number
                                  checkOverlaps)     # overlaps checking

        # Envelope
        solidEnv = G4Box("Envelope", 0.5*env_sizeXY,
                         0.5*env_sizeXY, 0.5*env_sizeZ)

        logicEnv = G4LogicalVolume(solidEnv,    # its solid
                                   env_mat,     # its material
                                   "Envelope")  # its name

        G4PVPlacement(None,              # no rotation
                      G4ThreeVector(),   # at (0,0,0)
                      logicEnv,          # its logical volume
                      "Envelope",        # its name
                      logicWorld,        # its mother  volume
                      True,              # no boolean operation
                      0,                 # copy number
                      checkOverlaps)     # overlaps checking

        # Shape
        shape1_mat = nist.FindOrBuildMaterial("G4_A-150_TISSUE")
        pos1 = G4ThreeVector(0, 2*cm, -7*cm)

        # Conical section shape
        shape1_rmina = 0*cm
        shape1_rmaxa = 2*cm
        shape1_rminb = 0*cm
        shape1_rmaxb = 4*cm
        shape1_hz = 3*cm
        shape1_phimin = 0*deg
        shape1_phimax = 360*deg
        solidShape1 = G4Cons("Shape1", shape1_rmina, shape1_rmaxa, shape1_rminb,
                             shape1_rmaxb, shape1_hz, shape1_phimin, shape1_phimax)

        logicShape1 = G4LogicalVolume(solidShape1,  # its solid
                                      shape1_mat,   # its material
                                      "Shape1")     # its name

        G4PVPlacement(None,           # no rotation
                      pos1,           # at position
                      logicShape1,    # its logical volume
                      "Shape1",       # its name
                      logicEnv,       # its mother  volume
                      False,          # no boolean operation
                      0,              # copy number
                      checkOverlaps)  # overlaps checking

        # Shape 2
        shape2_mat = nist.FindOrBuildMaterial("G4_BONE_COMPACT_ICRU")
        pos2 = G4ThreeVector(0, -1*cm, 7*cm)

        # Trapezoid shape
        shape2_dxa = 12*cm
        shape2_dxb = 12*cm
        shape2_dya = 10*cm
        shape2_dyb = 16*cm
        shape2_dz = 6*cm
        solidShape2 = G4Trd("Shape2",  # its name
                            0.5*shape2_dxa, 0.5*shape2_dxb,
                            0.5*shape2_dya, 0.5*shape2_dyb, 0.5*shape2_dz)  # its size

        logicShape2 = G4LogicalVolume(solidShape2,  # its solid
                                      shape2_mat,   # its material
                                      "Shape2")     # its name

        G4PVPlacement(None,            # no rotation
                      pos2,            # at position
                      logicShape2,     # its logical volume
                      "Shape2",        # its name
                      logicEnv,        # its mother  volume
                      False,           # no boolean operation
                      0,               # copy number
                      checkOverlaps)   # overlaps checking

        # Set Shape2 as scoring volume
        self.fScoringVolume = logicShape2

        # always return the physical World
        return physWorld


class B1RunAction(G4UserRunAction):

    def __init__(self):
        super().__init__()

        self.edep = G4Accumulable(0)
        self.edep2 = G4Accumulable(0)

        accumulableManager = G4AccumulableManager.Instance()
        accumulableManager.RegisterAccumulable(self.edep)
        accumulableManager.RegisterAccumulable(self.edep2)

    def BeginOfRunAction(self, aRun):
        G4RunManager.GetRunManager().SetRandomNumberStore(False)

        accumulableManager = G4AccumulableManager.Instance()
        accumulableManager.Reset()

    def EndOfRunAction(self, aRun):
        self.nofEvents = aRun.GetNumberOfEvent()
        if self.nofEvents == 0:
            return

        # Merge accumulables
        accumulableManager = G4AccumulableManager.Instance()
        accumulableManager.Merge()

        edep = self.edep.GetValue()
        edep2 = self.edep2.GetValue()

    def AddEdep(self, edep):
        self.edep += edep
        self.edep2 += edep*edep


class B1EventAction(G4UserEventAction):

    def __init__(self, runAction):
        super().__init__()
        self.fRunAction = runAction

    def BeginOfEventAction(self, anEvent):
        self.fEdep = 0

    def EndOfEventAction(self, anEvent):
        self.fRunAction.AddEdep(self.fEdep)

    def AddEdep(self, edep):
        self.fEdep += edep


class B1SteppingAction(G4UserSteppingAction):

    def __init__(self, eventAction):
        super().__init__()
        self.fEventAction = eventAction
        self.fScoringVolume = None

    def UserSteppingAction(self, aStep):
        if self.fScoringVolume == None:
            detectorConstruction = G4RunManager.GetRunManager().GetUserDetectorConstruction()
            self.fScoringVolume = detectorConstruction.fScoringVolume

        volume = aStep.GetPreStepPoint().GetTouchable().GetVolume().GetLogicalVolume()

        # check if we are in scoring volume
        if volume != self.fScoringVolume:
            return

        # collect energy deposited in this step
        edepStep = aStep.GetTotalEnergyDeposit()
        self.fEventAction.AddEdep(edepStep)


class B1PrimaryGeneratorAction(G4VUserPrimaryGeneratorAction):

    def __init__(self):
        super().__init__()
        self.fEnvelopeBox = None
        self.fParticleGun = G4ParticleGun(1)

        # default particle kinematic
        particleTable = G4ParticleTable.GetParticleTable()
        particle = particleTable.FindParticle("gamma")
        self.fParticleGun.SetParticleDefinition(particle)
        self.fParticleGun.SetParticleMomentumDirection(G4ThreeVector(0, 0, 1))
        self.fParticleGun.SetParticleEnergy(6*MeV)

    def GeneratePrimaries(self, anEvent):
        # this function is called at the begining of each event

        # In order to avoid dependence of PrimaryGeneratorAction
        # on DetectorConstruction class we get Envelope volume
        # from G4LogicalVolumeStore.
        envSizeXY = 0
        envSizeZ = 0
        if self.fEnvelopeBox == None:
            envLV = G4LogicalVolumeStore.GetInstance().GetVolume("Envelope")
            if envLV != None:
                self.fEnvelopeBox = envLV.GetSolid()

        if self.fEnvelopeBox != None:
            envSizeXY = self.fEnvelopeBox.GetXHalfLength()*2
            envSizeZ = self.fEnvelopeBox.GetZHalfLength()*2
        else:
            msg = "Envelope volume of box shape not found.\n"
            msg += "Perhaps you have changed geometry.\n"
            msg += "The gun will be place at the center."
            G4Exception("B1PrimaryGeneratorAction::GeneratePrimaries()",
                        "MyCode0002", G4ExceptionSeverity.JustWarning, msg)

        size = 0.8
        x0 = size * envSizeXY * (G4UniformRand()-0.5)
        y0 = size * envSizeXY * (G4UniformRand()-0.5)
        z0 = -0.5 * envSizeZ

        self.fParticleGun.SetParticlePosition(G4ThreeVector(x0, y0, z0))
        self.fParticleGun.GeneratePrimaryVertex(anEvent)


class B1ActionInitialization(G4VUserActionInitialization):

    def BuildForMaster(self):
        self.SetUserAction(B1RunAction())

    def Build(self):
        self.SetUserAction(B1PrimaryGeneratorAction())

        runAction = B1RunAction()
        self.SetUserAction(runAction)

        eventAction = B1EventAction(runAction)
        self.SetUserAction(eventAction)

        self.SetUserAction(B1SteppingAction(eventAction))



def runSim(processNum):
    sys.stdout = open(os.devnull, 'w') # Prevent log spam

    # Important: initialize the random engine with a different seed for each process
    G4Random.getTheEngine().setSeed(processNum + 1, 0)

    runManager = G4RunManagerFactory.CreateRunManager(G4RunManagerType.Serial)

    runManager.SetUserInitialization(B1DetectorConstruction())

    # Physics list
    physicsList = QBBC()

    runManager.SetUserInitialization(physicsList)

    # User action initialization
    runManager.SetUserInitialization(B1ActionInitialization())

    runManager.Initialize()
    runManager.BeamOn(10000)

    mass = runManager.GetUserDetectorConstruction().fScoringVolume.GetMass()
    edep = runManager.GetUserRunAction().edep.GetValue()
    edep2 = runManager.GetUserRunAction().edep2.GetValue()
    nofEvents = runManager.GetUserRunAction().nofEvents

    return edep, edep2, mass, nofEvents


if __name__ == "__main__":
    NUM_PROCESSES = 8

    edep, edep2, mass, nofEvents = 0, 0, 0, 0

    with multiprocessing.pool.Pool(NUM_PROCESSES) as pool:
        for edep_i, edep2_i, mass_i, nofEvents_i in pool.map(runSim, range(NUM_PROCESSES)):
            edep += edep_i
            edep2 += edep2_i
            mass = mass_i
            nofEvents += nofEvents_i


    # Compute dose = total energy deposit in a run and its variance
    rms = edep2 - edep*edep/nofEvents
    if rms > 0:
        rms = math.sqrt(rms)
    else:
        rms = 0

    dose = edep/mass
    rmsDose = rms/mass

    milligray = 1.e-3*gray
    microgray = 1.e-6*gray
    nanogray = 1.e-9*gray
    picogray = 1.e-12*gray

    G4UnitDefinition("milligray", "milliGy", "Dose", milligray)
    G4UnitDefinition("microgray", "microGy", "Dose", microgray)
    G4UnitDefinition("nanogray", "nanoGy", "Dose", nanogray)
    G4UnitDefinition("picogray", "picoGy", "Dose", picogray)

    print("--------------------End of Global Run-----------------------")
    print(" The run consists of", nofEvents, "Events")
    print(" Cumulated dose per run, in scoring volume: ", end="")
    print("{:.5f} rms = {:.5f}".format(G4BestUnit(dose, "Dose"), G4BestUnit(rmsDose, "Dose")))
    print("------------------------------------------------------------")

