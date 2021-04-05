from geant4_pybind import *
import sys
import math


class B3DetectorConstruction(G4VUserDetectorConstruction):

    def __init__(self):
        super().__init__()
        self.fCheckOverlaps = True
        self.DefineMaterials()

    def DefineMaterials(self):
        man = G4NistManager.Instance()

        isotopes = False
        O = man.FindOrBuildElement("O", isotopes)
        Si = man.FindOrBuildElement("Si", isotopes)
        Lu = man.FindOrBuildElement("Lu", isotopes)

        self.LSO = G4Material("Lu2SiO5", 7.4*g/cm3, 3)
        self.LSO.AddElement(Lu, 2)
        self.LSO.AddElement(Si, 1)
        self.LSO.AddElement(O, 5)

    def Construct(self):
        # Gamma detector Parameters
        cryst_dX = 6*cm
        cryst_dY = 6*cm
        cryst_dZ = 3*cm
        nb_cryst = 32
        nb_rings = 9

        dPhi = twopi/nb_cryst
        half_dPhi = 0.5*dPhi
        cosdPhi = math.cos(half_dPhi)
        tandPhi = math.tan(half_dPhi)

        ring_R1 = 0.5*cryst_dY/tandPhi
        ring_R2 = (ring_R1+cryst_dZ)/cosdPhi
        detector_dZ = nb_rings*cryst_dX
        nist = G4NistManager.Instance()
        default_mat = nist.FindOrBuildMaterial("G4_AIR")
        cryst_mat = nist.FindOrBuildMaterial("Lu2SiO5")

        # World
        world_sizeXY = 2.4*ring_R2
        world_sizeZ = 1.2*detector_dZ

        solidWorld = G4Box("World", 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ)

        logicWorld = G4LogicalVolume(solidWorld,   # its solid
                                     default_mat,  # its material
                                     "World")      # its name

        physWorld = G4PVPlacement(None,                 # no rotation
                                  G4ThreeVector(),      # at (0,0,0)
                                  logicWorld,           # its logical volume
                                  "World",              # its name
                                  None,                 # its mother  volume
                                  False,                # no boolean operation
                                  0,                    # copy number
                                  self.fCheckOverlaps)  # checking overlaps

        # ring
        solidRing = G4Tubs("Ring", ring_R1, ring_R2, 0.5*cryst_dX, 0, twopi)

        logicRing = G4LogicalVolume(solidRing,    # its solid
                                    default_mat,  # its material
                                    "Ring")       # its name

        # define crystal
        gap = 0.5*mm  # a gap for wrapping
        dX = cryst_dX - gap
        dY = cryst_dY - gap
        solidCryst = G4Box("crystal", dX/2, dY/2, cryst_dZ/2)

        logicCryst = G4LogicalVolume(solidCryst,   # its solid
                                     cryst_mat,    # its material
                                     "CrystalLV")  # its name

        # place crystals within a ring
        for icrys in range(nb_cryst):
            phi = icrys*dPhi
            rotm = G4RotationMatrix()
            rotm.rotateY(90*deg)
            rotm.rotateZ(phi)
            uz = G4ThreeVector(math.cos(phi), math.sin(phi), 0)
            position = (ring_R1+0.5*cryst_dZ)*uz
            transform = G4Transform3D(rotm, position)

            G4PVPlacement(transform,             # rotation,position
                          logicCryst,            # its logical volume
                          "crystal",             # its name
                          logicRing,             # its mother  volume
                          False,                 # no boolean operation
                          icrys,                 # copy number
                          self.fCheckOverlaps)   # checking overlaps

        # full detector
        solidDetector = G4Tubs("Detector", ring_R1, ring_R2, 0.5*detector_dZ, 0, twopi)

        logicDetector = G4LogicalVolume(solidDetector,   # its solid
                                        default_mat,     # its material
                                        "Detector")      # its name

        #  place rings within detector
        OG = -0.5*(detector_dZ + cryst_dX)
        for iring in range(nb_rings):
            OG += cryst_dX
            G4PVPlacement(None,                     # no rotation
                          G4ThreeVector(0, 0, OG),  # position
                          logicRing,                # its logical volume
                          "ring",                   # its name
                          logicDetector,            # its mother  volume
                          False,                    # no boolean operation
                          iring,                    # copy number
                          self.fCheckOverlaps)      # checking overlaps

        # place detector in world
        G4PVPlacement(None,                    # no rotation
                      G4ThreeVector(),         # at (0,0,0)
                      logicDetector,           # its logical volume
                      "Detector",              # its name
                      logicWorld,              # its mother  volume
                      False,                   # no boolean operation
                      0,                       # copy number
                      self.fCheckOverlaps)     # checking overlaps

        # patient
        patient_radius = 8*cm
        patient_dZ = 10*cm
        patient_mat = nist.FindOrBuildMaterial("G4_BRAIN_ICRP")

        solidPatient = G4Tubs("Patient", 0, patient_radius, 0.5*patient_dZ, 0, twopi)

        logicPatient = G4LogicalVolume(solidPatient,   # its solid
                                       patient_mat,    # its material
                                       "PatientLV")    # its name

        # place patient in world
        G4PVPlacement(None,                  # no rotation
                      G4ThreeVector(),       # at (0,0,0)
                      logicPatient,          # its logical volume
                      "Patient",             # its name
                      logicWorld,            # its mother  volume
                      False,                 # no boolean operation
                      0,                     # copy number
                      self.fCheckOverlaps)   # checking overlaps

        #  Visualization attributes
        logicRing.SetVisAttributes(G4VisAttributes.GetInvisible())
        logicDetector.SetVisAttributes(G4VisAttributes.GetInvisible())

        #  Print materials
        print(G4Material.GetMaterialTable())

        # always return the physical World
        return physWorld

    def ConstructSDandField(self):
        G4SDManager.GetSDMpointer().SetVerboseLevel(1)

        # declare crystal as a MultiFunctionalDetector scorer
        cryst = G4MultiFunctionalDetector("crystal")
        G4SDManager.GetSDMpointer().AddNewDetector(cryst)

        primitiv1 = G4PSEnergyDeposit("edep")
        cryst.RegisterPrimitive(primitiv1)
        self.SetSensitiveDetector("CrystalLV", cryst)

        # declare patient as a MultiFunctionalDetector scorer
        patient = G4MultiFunctionalDetector("patient")
        G4SDManager.GetSDMpointer().AddNewDetector(patient)
        primitiv2 = G4PSDoseDeposit("dose")
        patient.RegisterPrimitive(primitiv2)
        self.SetSensitiveDetector("PatientLV", patient)


class B3aRunAction(G4UserRunAction):

    def __init__(self):
        super().__init__()

        # add new units for dose
        milligray = 1.e-3*gray
        microgray = 1.e-6*gray
        nanogray = 1.e-9*gray
        picogray = 1.e-12*gray

        G4UnitDefinition("milligray", "milliGy", "Dose", milligray)
        G4UnitDefinition("microgray", "microGy", "Dose", microgray)
        G4UnitDefinition("nanogray", "nanoGy", "Dose", nanogray)
        G4UnitDefinition("picogray", "picoGy", "Dose", picogray)

    def BeginOfRunAction(self, run):
        print("### Run", run.GetRunID(), "start.")

        # reset accumulables to their initial values
        self.fGoodEvents = 0
        self.fSumDose = 0

        # inform the runManager to save random number seed
        G4RunManager.GetRunManager().SetRandomNumberStore(False)

    def EndOfRunAction(self, run):
        nofEvents = run.GetNumberOfEvent()
        if nofEvents == 0:
            return

        # Run conditions
        #  note: There is no primary generator action object for "master"
        #        run manager for multi-threaded mode.
        partName = ""
        generatorAction = G4RunManager.GetRunManager().GetUserPrimaryGeneratorAction()
        if generatorAction != None:
            particle = generatorAction.fParticleGun.GetParticleDefinition()
            partName = particle.GetParticleName()

        # Print results
        if self.IsMaster():
            print("--------------------End of Global Run-----------------------")
            print(" The run was", nofEvents, "events", end="")
        else:
            print("--------------------End of Local Run------------------------")
            print(" The run was", nofEvents, partName, end="")

        print(", Nb of 'good' e+ annihilations:", self.fGoodEvents)
        print(" Total dose in patient:", G4BestUnit(self.fSumDose, "Dose"))
        print("------------------------------------------------------------")

    def CountEvent(self):
        self.fGoodEvents += 1

    def SumDose(self, dose):
        self.fSumDose += dose


class B3aEventAction(G4UserEventAction):

    def __init__(self, runAction):
        super().__init__()
        self.fRunAction = runAction
        self.fCollID_cryst = -1
        self.fCollID_patient = -1

    def EndOfEventAction(self, evt):
        HCE = evt.GetHCofThisEvent()
        if HCE == None:
            return

        # Get hits collections IDs
        if self.fCollID_cryst < 0:
            SDMan = G4SDManager.GetSDMpointer()
            self.fCollID_cryst = SDMan.GetCollectionID("crystal/edep")
            self.fCollID_patient = SDMan.GetCollectionID("patient/dose")

        # Energy in crystals : identify 'good events'
        eThreshold = 500*keV
        nbOfFired = 0

        evtMap = HCE.GetHC(self.fCollID_cryst)
        for copyNb, edep in evtMap:
            if edep > eThreshold:
                nbOfFired += 1
                # print("cryst", copyNb, ":", edep/keV, "keV")

        if nbOfFired == 2:
            self.fRunAction.CountEvent()

        # Dose deposit in patient
        dose = 0
        evtMap = HCE.GetHC(self.fCollID_patient)
        for copyNb, edep in evtMap:
            dose = edep

        if dose > 0:
            self.fRunAction.SumDose(dose)


class B3PrimaryGeneratorAction(G4VUserPrimaryGeneratorAction):

    def __init__(self):
        super().__init__()
        n_particle = 1
        self.fParticleGun = G4ParticleGun(n_particle)

        # default particle kinematic
        particleTable = G4ParticleTable.GetParticleTable()
        particle = particleTable.FindParticle("chargedgeantino")
        self.fParticleGun.SetParticleDefinition(particle)
        self.fParticleGun.SetParticlePosition(G4ThreeVector(0, 0, 0))
        self.fParticleGun.SetParticleEnergy(1*eV)
        self.fParticleGun.SetParticleMomentumDirection(G4ThreeVector(1, 0, 0))

    def GeneratePrimaries(self, anEvent):
        particle = self.fParticleGun.GetParticleDefinition()
        if particle == G4ChargedGeantino.ChargedGeantino():
            # fluorine
            Z = 9
            A = 18
            ionCharge = 0 * eplus
            excitEnergy = 0 * keV

            ion = G4IonTable.GetIonTable().GetIon(Z, A, excitEnergy)
            self.fParticleGun.SetParticleDefinition(ion)
            self.fParticleGun.SetParticleCharge(ionCharge)

        # randomized position
        x0 = 4*cm + 1*cm*(G4UniformRand()-0.5)
        y0 = 4*cm + 1*cm*(G4UniformRand()-0.5)
        z0 = 4*cm + 1*cm*(G4UniformRand()-0.5)
        self.fParticleGun.SetParticlePosition(G4ThreeVector(x0, y0, z0))

        # create vertex
        self.fParticleGun.GeneratePrimaryVertex(anEvent)


class B3StackingAction(G4UserStackingAction):

    def ClassifyNewTrack(self, track):
        # keep primary particle
        if track.GetParentID() == 0:
            return G4ClassificationOfNewTrack.fUrgent

        # kill secondary neutrino
        if track.GetDefinition() == G4NeutrinoE.NeutrinoE():
            return G4ClassificationOfNewTrack.fKill
        else:
            return G4ClassificationOfNewTrack.fUrgent


class B3PhysicsList(G4VModularPhysicsList):

    def __init__(self):
        super().__init__()
        # Default physics
        self.RegisterPhysics(G4DecayPhysics())

        # EM physics
        self.RegisterPhysics(G4EmStandardPhysics())

        # Radioactive decay
        self.RegisterPhysics(G4RadioactiveDecayPhysics())


class B3aActionInitialization(G4VUserActionInitialization):

    def BuildForMaster(self):
        self.SetUserAction(B3aRunAction())

    def Build(self):
        runAction = B3aRunAction()
        self.SetUserAction(runAction)

        self.SetUserAction(B3aEventAction(runAction))
        self.SetUserAction(B3PrimaryGeneratorAction())
        self.SetUserAction(B3StackingAction())


# Detect interactive mode (if no arguments) and define UI session
ui = None
if len(sys.argv) == 1:
    ui = G4UIExecutive(len(sys.argv), sys.argv)

# Construct the default run manager
runManager = G4RunManagerFactory.CreateRunManager(G4RunManagerType.Default)

# Set mandatory initialization classes
runManager.SetUserInitialization(B3DetectorConstruction())
runManager.SetUserInitialization(B3PhysicsList())

# Set user action classes
runManager.SetUserInitialization(B3aActionInitialization())

# Initialize visualization
visManager = G4VisExecutive()
# G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
# visManager = G4VisExecutive("Quiet");
visManager.Initialize()

# Get the pointer to the User Interface manager
UImanager = G4UImanager.GetUIpointer()

# Activate ROOT score ntuple writer
# The verbose level can be also set via UI commands
# /score/ntuple/writerVerbose level
scoreNtupleWriter = G4RootScoreNtupleWriter()
scoreNtupleWriter.SetVerboseLevel(1)

# Process macro or start UI session
if ui == None:
    # batch mode
    command = "/control/execute "
    fileName = sys.argv[1]
    UImanager.ApplyCommand(command+fileName)
else:
    # interactive mode
    UImanager.ApplyCommand("/control/execute init_vis.mac")
    ui.SessionStart()
