from geant4_pybind import *

import math
import sys
import os
import psutil


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

        G4PVPlacement(G4RotationMatrix(),           # no rotation
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

        G4PVPlacement(G4RotationMatrix(),            # no rotation
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
        milligray = 1.e-3*gray
        microgray = 1.e-6*gray
        nanogray = 1.e-9*gray
        picogray = 1.e-12*gray

        G4UnitDefinition("milligray", "milliGy", "Dose", milligray)
        G4UnitDefinition("microgray", "microGy", "Dose", microgray)
        G4UnitDefinition("nanogray", "nanoGy", "Dose", nanogray)
        G4UnitDefinition("picogray", "picoGy", "Dose", picogray)

    def BeginOfRunAction(self, aRun):
        G4RunManager.GetRunManager().SetRandomNumberStore(False)
        self.edep = 0
        self.edep2 = 0

    def EndOfRunAction(self, aRun):
        nofEvents = aRun.GetNumberOfEvent()
        if nofEvents == 0:
            return

        # Compute dose = total energy deposit in a run and its variance
        rms = self.edep2 - self.edep*self.edep/nofEvents
        if rms > 0:
            rms = math.sqrt(rms)
        else:
            rms = 0

        detectorConstruction = G4RunManager.GetRunManager().GetUserDetectorConstruction()
        mass = detectorConstruction.fScoringVolume.GetMass()
        dose = self.edep/mass
        rmsDose = rms/mass

        generatorAction = G4RunManager.GetRunManager().GetUserPrimaryGeneratorAction()
        runCondition = ""
        if generatorAction != None and isinstance(generatorAction, B1PrimaryGeneratorAction):
            particleGun = generatorAction.fParticleGun
            runCondition += particleGun.GetParticleDefinition().GetParticleName() + "(s)"
            runCondition += " of "
            particleEnergy = particleGun.GetParticleEnergy()
            runCondition += "{:.5g}".format(G4BestUnit(particleEnergy, "Energy"))

        if self.IsMaster():
            print("--------------------End of Global Run-----------------------")
        else:
            print("--------------------End of Local Run------------------------")

        print(" The run consists of", nofEvents, runCondition)
        print(" Cumulated dose per run, in scoring volume: ", end="")
        print("{:.5f} rms = {:.5f}".format(G4BestUnit(dose, "Dose"), G4BestUnit(rmsDose, "Dose")))
        print("------------------------------------------------------------")
        print("")

        process = psutil.Process(os.getpid())
        print(process.memory_info().rss)

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


runManager = G4RunManagerFactory.CreateRunManager(G4RunManagerType.Default)

runManager.SetUserInitialization(B1DetectorConstruction())

G4Random.setTheEngine(MTwistEngine())

# Physics list
physicsList = QBBC()
physicsList.SetVerboseLevel(1)

runManager.SetUserInitialization(physicsList)

# User action initialization
runManager.SetUserInitialization(B1ActionInitialization())

# Get the User Interface manager
UImanager = G4UImanager.GetUIpointer()

b1_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), "../examples/B1")

UImanager.ApplyCommand("/control/execute " + os.path.join(b1_dir, "run2.mac"))
