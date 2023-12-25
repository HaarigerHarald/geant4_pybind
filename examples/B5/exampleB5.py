from geant4_pybind import *
import sys
import math


kNofHodoscopes1 = 15
kNofHodoscopes2 = 25
kNofChambers = 5
kNofEmColumns = 20
kNofEmRows = 4
kNofEmCells = kNofEmColumns * kNofEmRows
kNofHadColumns = 10
kNofHadRows = 2
kNofHadCells = kNofHadColumns * kNofHadRows

G4AnalysisManager = G4GenericAnalysisManager


class B5CellParameterisation(G4VPVParameterisation):

    def __init__(self):
        super().__init__()
        self.fXCell = [0] * kNofEmCells
        self.fYCell = [0] * kNofEmCells
        for copyNo in range(kNofEmCells):
            column = int(copyNo / kNofEmRows)
            row = copyNo % kNofEmRows
            self.fXCell[copyNo] = (column-9)*15*cm - 7.5*cm
            self.fYCell[copyNo] = (row-1)*15*cm - 7.5*cm

    def ComputeTransformation(self, copyNo, physVol):
        physVol.SetTranslation(G4ThreeVector(self.fXCell[copyNo], self.fYCell[copyNo], 0))


class B5MagneticField(G4MagneticField):

    def __init__(self):
        super().__init__()
        self.fBy = 1*tesla

        # define commands for this class
        # Define /B5/field command directory using generic messenger class
        self.fMessenger = G4GenericMessenger(self, "/B5/field/", "Field control")

        # fieldValue command
        valueCmd = self.fMessenger.DeclareMethodWithUnit("value", "tesla", self.SetField,
                                                         "Set field strength.")
        valueCmd.SetParameterName("field", True)
        valueCmd.SetDefaultValue("1")

    def GetFieldValue(self, point, Bfield):
        Bfield[0] = 0
        Bfield[1] = self.fBy
        Bfield[2] = 0
        # Alternatively you can return the field as an array
        # return [0, self.fBy, 0]

    # Providing argument type information helps Geant4 to know what to register (default: float)
    def SetField(self, val: float):
        self.fBy = val


class B5DetectorConstruction(G4VUserDetectorConstruction):

    def __init__(self):
        super().__init__()
        self.fArmAngle = 30 * deg
        self.fArmRotation = G4RotationMatrix().rotateY(self.fArmAngle)
        self.fVisAttributes = []

        # define commands for this class
        self.DefineCommands()

    def DefineCommands(self):
        # Define /B5/detector command directory using generic messenger class
        self.fMessenger = G4GenericMessenger(self, "/B5/detector/", "Detector control")

        # armAngle command
        armAngleCmd = self.fMessenger.DeclareMethodWithUnit("armAngle", "deg", self.SetArmAngle,
                                                            "Set rotation angle of the second arm.")

        armAngleCmd.SetParameterName("angle", True)
        armAngleCmd.SetRange("angle >= 0 && angle < 180")
        armAngleCmd.SetDefaultValue("30")

    # Providing argument type information helps Geant4 to know what to register (default: float)
    def SetArmAngle(self, val: float):
        if self.fSecondArmPhys == None:
            print("Detector has not yet been constructed.", file=sys.stderr)
            return

        self.fArmAngle = val
        self.fArmRotation = G4RotationMatrix()  # make it unit vector
        self.fArmRotation.rotateY(self.fArmAngle)
        x = -5*m * math.sin(self.fArmAngle)
        z = 5*m * math.cos(self.fArmAngle)
        self.fSecondArmPhys.SetTranslation(G4ThreeVector(x, 0, z))
        self.fSecondArmPhys.SetRotation(self.fArmRotation)

        # tell G4RunManager that we change the geometry
        G4RunManager.GetRunManager().GeometryHasBeenModified()

    def ConstructMaterials(self):
        nistManager = G4NistManager.Instance()

        # Air
        nistManager.FindOrBuildMaterial("G4_AIR")

        # Argon gas
        nistManager.FindOrBuildMaterial("G4_Ar")
        # With a density different from the one defined in NIST
        # density = 1.782e-03*g/cm3
        # nistManager.BuildMaterialWithNewDensity("B5_Ar","G4_Ar",density)
        # !! cases segmentation fault

        # Scintillator
        # (PolyVinylToluene, C_9H_10)
        nistManager.FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE")

        # CsI
        nistManager.FindOrBuildMaterial("G4_CESIUM_IODIDE")

        # Lead
        nistManager.FindOrBuildMaterial("G4_Pb")

        # Vacuum "Galactic"
        # nistManager.FindOrBuildMaterial("G4_Galactic")

        # Vacuum "Air with low density"
        # air = G4Material.GetMaterial("G4_AIR")
        # G4double density = 1.0e-5*air->GetDensity()
        # nistManager.BuildMaterialWithNewDensity("Air_lowDensity", "G4_AIR", density)

        print("The materials defined are :\n\n", G4Material.GetMaterialTable())

    def Construct(self):
        # Construct materials
        self.ConstructMaterials()
        air = G4Material.GetMaterial("G4_AIR")
        # argonGas = G4Material.GetMaterial("B5_Ar")
        argonGas = G4Material.GetMaterial("G4_Ar")
        scintillator = G4Material.GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE")
        csI = G4Material.GetMaterial("G4_CESIUM_IODIDE")
        lead = G4Material.GetMaterial("G4_Pb")

        # Option to switch on/off checking of volumes overlaps
        checkOverlaps = True

        # geometries --------------------------------------------------------------
        # experimental hall (world volume)
        worldSolid = G4Box("worldBox", 10*m, 3*m, 10*m)
        worldLogical = G4LogicalVolume(worldSolid, air, "worldLogical")
        worldPhysical = G4PVPlacement(None, G4ThreeVector(), worldLogical, "worldPhysical", None,
                                      False, 0, checkOverlaps)

        # Tube with Local Magnetic field
        magneticSolid = G4Tubs("magneticTubs", 0, 1*m, 1*m, 0, 360*deg)

        self.fMagneticLogical = G4LogicalVolume(magneticSolid, air, "magneticLogical")

        # placement of Tube
        fieldRot = G4RotationMatrix().rotateX(90*deg)

        G4PVPlacement(fieldRot, G4ThreeVector(), self.fMagneticLogical,
                      "magneticPhysical", worldLogical,
                      False, 0, checkOverlaps)

        # set step limit in tube with magnetic field
        userLimits = G4UserLimits(1*m)
        self.fMagneticLogical.SetUserLimits(userLimits)

        # first arm
        firstArmSolid = G4Box("firstArmBox", 1.5*m, 1*m, 3*m)
        firstArmLogical = G4LogicalVolume(firstArmSolid, air, "firstArmLogical")
        G4PVPlacement(None, G4ThreeVector(0, 0, -5*m), firstArmLogical,
                      "firstArmPhysical", worldLogical,
                      False, 0, checkOverlaps)

        # second arm
        secondArmSolid = G4Box("secondArmBox", 2*m, 2*m, 3.5*m)
        secondArmLogical = G4LogicalVolume(secondArmSolid, air, "secondArmLogical")
        x = -5*m * math.sin(self.fArmAngle)
        z = 5*m * math.cos(self.fArmAngle)
        self.fSecondArmPhys = G4PVPlacement(self.fArmRotation, G4ThreeVector(x, 0, z), secondArmLogical,
                                            "fSecondArmPhys", worldLogical, False, 0, checkOverlaps)

        # hodoscopes in first arm
        hodoscope1Solid = G4Box("hodoscope1Box", 5*cm, 20*cm, 0.5*cm)
        self.fHodoscope1Logical = G4LogicalVolume(
            hodoscope1Solid, scintillator, "hodoscope1Logical")

        for i in range(kNofHodoscopes1):
            x1 = (i-int(kNofHodoscopes1/2))*10*cm
            G4PVPlacement(None, G4ThreeVector(x1, 0, -1.5*m), self.fHodoscope1Logical,
                          "hodoscope1Physical", firstArmLogical,
                          False, i, checkOverlaps)

        # drift chambers in first arm
        chamber1Solid = G4Box("chamber1Box", 1*m, 30*cm, 1*cm)
        chamber1Logical = G4LogicalVolume(chamber1Solid, argonGas, "chamber1Logical")
        for i in range(kNofChambers):
            z1 = (i-int(kNofChambers/2))*0.5*m
            G4PVPlacement(None, G4ThreeVector(0, 0, z1), chamber1Logical,
                          "chamber1Physical", firstArmLogical, False, i, checkOverlaps)

        # "virtual" wire plane
        wirePlane1Solid = G4Box("wirePlane1Box", 1*m, 30*cm, 0.1*mm)
        self.fWirePlane1Logical = G4LogicalVolume(wirePlane1Solid, argonGas, "wirePlane1Logical")
        G4PVPlacement(None, G4ThreeVector(0, 0, 0), self.fWirePlane1Logical,
                      "wirePlane1Physical", chamber1Logical, False, 0, checkOverlaps)

        # hodoscopes in second arm
        hodoscope2Solid = G4Box("hodoscope2Box", 5*cm, 20*cm, 0.5*cm)
        self.fHodoscope2Logical = G4LogicalVolume(
            hodoscope2Solid, scintillator, "hodoscope2Logical")

        for i in range(kNofHodoscopes2):
            x2 = (i-int(kNofHodoscopes2/2))*10*cm
            G4PVPlacement(None, G4ThreeVector(x2, 0, 0), self.fHodoscope2Logical,
                          "hodoscope2Physical", secondArmLogical, False, i, checkOverlaps)

        # drift chambers in second arm
        chamber2Solid = G4Box("chamber2Box", 1.5*m, 30*cm, 1*cm)
        chamber2Logical = G4LogicalVolume(chamber2Solid, argonGas, "chamber2Logical")

        for i in range(kNofChambers):
            z2 = (i-int(kNofChambers/2))*0.5*m - 1.5*m
            G4PVPlacement(None, G4ThreeVector(0, 0, z2), chamber2Logical,
                          "chamber2Physical", secondArmLogical, False, i, checkOverlaps)

        # "virtual" wire plane
        wirePlane2Solid = G4Box("wirePlane2Box", 1.5*m, 30*cm, 0.1*mm)
        self.fWirePlane2Logical = G4LogicalVolume(wirePlane2Solid, argonGas, "wirePlane2Logical")
        G4PVPlacement(None, G4ThreeVector(0, 0, 0), self.fWirePlane2Logical,
                      "wirePlane2Physical", chamber2Logical, False, 0, checkOverlaps)

        # CsI calorimeter
        emCalorimeterSolid = G4Box("EMcalorimeterBox", 1.5*m, 30*cm, 15*cm)
        emCalorimeterLogical = G4LogicalVolume(emCalorimeterSolid, csI, "EMcalorimeterLogical")
        G4PVPlacement(None, G4ThreeVector(0, 0, 2*m), emCalorimeterLogical,
                      "EMcalorimeterPhysical", secondArmLogical, False, 0, checkOverlaps)

        # EMcalorimeter cells
        cellSolid = G4Box("cellBox", 7.5*cm, 7.5*cm, 15*cm)
        self.fCellLogical = G4LogicalVolume(cellSolid, csI, "cellLogical")
        cellParam = B5CellParameterisation()
        G4PVParameterised("cellPhysical", self.fCellLogical, emCalorimeterLogical,
                          kXAxis, kNofEmCells, cellParam)

        # hadron calorimeter
        hadCalorimeterSolid = G4Box("HadCalorimeterBox", 1.5*m, 30*cm, 50*cm)
        hadCalorimeterLogical = G4LogicalVolume(hadCalorimeterSolid, lead, "HadCalorimeterLogical")
        G4PVPlacement(None, G4ThreeVector(0, 0, 3*m), hadCalorimeterLogical,
                      "HadCalorimeterPhysical", secondArmLogical, False, 0, checkOverlaps)

        # hadron calorimeter column
        HadCalColumnSolid = G4Box("HadCalColumnBox", 15*cm, 30*cm, 50*cm)
        HadCalColumnLogical = G4LogicalVolume(HadCalColumnSolid, lead, "HadCalColumnLogical")
        G4PVReplica("HadCalColumnPhysical", HadCalColumnLogical,
                    hadCalorimeterLogical, kXAxis, kNofHadColumns, 30*cm)

        # hadron calorimeter cell
        HadCalCellSolid = G4Box("HadCalCellBox", 15*cm, 15*cm, 50*cm)
        HadCalCellLogical = G4LogicalVolume(HadCalCellSolid, lead, "HadCalCellLogical")
        G4PVReplica("HadCalCellPhysical", HadCalCellLogical,
                    HadCalColumnLogical, kYAxis, kNofHadRows, 30*cm)

        # hadron calorimeter layers
        HadCalLayerSolid = G4Box("HadCalLayerBox", 15*cm, 15*cm, 2.5*cm)
        HadCalLayerLogical = G4LogicalVolume(HadCalLayerSolid, lead, "HadCalLayerLogical")
        G4PVReplica("HadCalLayerPhysical", HadCalLayerLogical,
                    HadCalCellLogical, kZAxis, kNofHadCells, 5*cm)

        # scintillator plates
        HadCalScintiSolid = G4Box("HadCalScintiBox", 15*cm, 15*cm, 0.5*cm)
        self.fHadCalScintiLogical = G4LogicalVolume(
            HadCalScintiSolid, scintillator, "HadCalScintiLogical")

        G4PVPlacement(None, G4ThreeVector(0, 0, 2*cm), self.fHadCalScintiLogical,
                      "HadCalScintiPhysical", HadCalLayerLogical, False, 0, checkOverlaps)

        # visualization attributes
        visAttributes = G4VisAttributes(G4Colour(1, 1, 1))
        visAttributes.SetVisibility(False)
        worldLogical.SetVisAttributes(visAttributes)
        self.fVisAttributes.append(visAttributes)

        visAttributes = G4VisAttributes(G4Colour(0.9, 0.9, 0.9))   # LightGray
        self.fMagneticLogical.SetVisAttributes(visAttributes)
        self.fVisAttributes.append(visAttributes)

        visAttributes = G4VisAttributes(G4Colour(1, 1, 1))
        visAttributes.SetVisibility(False)
        firstArmLogical.SetVisAttributes(visAttributes)
        secondArmLogical.SetVisAttributes(visAttributes)
        self.fVisAttributes.append(visAttributes)

        visAttributes = G4VisAttributes(G4Colour(0.8888, 0, 0))
        self.fHodoscope1Logical.SetVisAttributes(visAttributes)
        self.fHodoscope2Logical.SetVisAttributes(visAttributes)
        self.fVisAttributes.append(visAttributes)

        visAttributes = G4VisAttributes(G4Colour(0, 1, 0))
        chamber1Logical.SetVisAttributes(visAttributes)
        chamber2Logical.SetVisAttributes(visAttributes)
        self.fVisAttributes.append(visAttributes)

        visAttributes = G4VisAttributes(G4Colour(0, 0.8888, 0))
        visAttributes.SetVisibility(False)
        self.fWirePlane1Logical.SetVisAttributes(visAttributes)
        self.fWirePlane2Logical.SetVisAttributes(visAttributes)
        self.fVisAttributes.append(visAttributes)

        visAttributes = G4VisAttributes(G4Colour(0.8888, 0.8888, 0))
        visAttributes.SetVisibility(False)
        emCalorimeterLogical.SetVisAttributes(visAttributes)
        self.fVisAttributes.append(visAttributes)

        visAttributes = G4VisAttributes(G4Colour(0.9, 0.9, 0))
        self.fCellLogical.SetVisAttributes(visAttributes)
        self.fVisAttributes.append(visAttributes)

        visAttributes = G4VisAttributes(G4Colour(0, 0, 0.9))
        hadCalorimeterLogical.SetVisAttributes(visAttributes)
        self.fVisAttributes.append(visAttributes)

        visAttributes = G4VisAttributes(G4Colour(0, 0, 0.9))
        visAttributes.SetVisibility(False)
        HadCalColumnLogical.SetVisAttributes(visAttributes)
        HadCalCellLogical.SetVisAttributes(visAttributes)
        HadCalLayerLogical.SetVisAttributes(visAttributes)
        self.fHadCalScintiLogical.SetVisAttributes(visAttributes)
        self.fVisAttributes.append(visAttributes)

        # return the world physical volume
        return worldPhysical

    def ConstructSDandField(self):
        # sensitive detectors -----------------------------------------------------
        sdManager = G4SDManager.GetSDMpointer()

        hodoscope1 = B5HodoscopeSD("/hodoscope1")
        sdManager.AddNewDetector(hodoscope1)
        self.fHodoscope1Logical.SetSensitiveDetector(hodoscope1)

        hodoscope2 = B5HodoscopeSD("/hodoscope2")
        sdManager.AddNewDetector(hodoscope2)
        self.fHodoscope2Logical.SetSensitiveDetector(hodoscope2)

        chamber1 = B5DriftChamberSD("/chamber1")
        sdManager.AddNewDetector(chamber1)
        self.fWirePlane1Logical.SetSensitiveDetector(chamber1)

        chamber2 = B5DriftChamberSD("/chamber2")
        sdManager.AddNewDetector(chamber2)
        self.fWirePlane2Logical.SetSensitiveDetector(chamber2)

        emCalorimeter = B5EmCalorimeterSD("/EMcalorimeter")
        sdManager.AddNewDetector(emCalorimeter)
        self.fCellLogical.SetSensitiveDetector(emCalorimeter)

        hadCalorimeter = B5HadCalorimeterSD("/HadCalorimeter")
        sdManager.AddNewDetector(hadCalorimeter)
        self.fHadCalScintiLogical.SetSensitiveDetector(hadCalorimeter)

        # magnetic field
        self.fMagneticField = B5MagneticField()
        self.fFieldMgr = G4FieldManager()
        self.fFieldMgr.SetDetectorField(self.fMagneticField)
        self.fFieldMgr.CreateChordFinder(self.fMagneticField)
        forceToAllDaughters = True
        self.fMagneticLogical.SetFieldManager(self.fFieldMgr, forceToAllDaughters)


class B5HitsCollection(G4VHitsCollection):

    def __init__(self, detName, colNam):
        super().__init__(detName, colNam)
        self.collection = []

    def __getitem__(self, i):
        return self.collection[i]

    def insert(self, item):
        self.collection.append(item)

    def GetSize(self):
        return len(self.collection)

    def GetHit(self, i):
        return self.collection[i]

    def __iter__(self):
        return self.collection.__iter__()


class B5DriftChamberHit(G4VHit):

    def __init__(self, layerID=-1):
        super().__init__()
        self.fLayerID = layerID
        self.fTime = 0
        self.fWorldPos = None
        self.fLocalPos = None

    def Draw(self):
        visManager = G4VVisManager.GetConcreteInstance()
        if visManager == None:
            return

        circle = G4Circle(self.fWorldPos)
        circle.SetScreenSize(2)
        circle.SetFillStyle(G4Circle.filled)
        attribs = G4VisAttributes(G4Colour(1, 1, 0))
        circle.SetVisAttributes(attribs)
        visManager.Draw(circle)

    def GetAttDefs(self):
        store, isNew = G4AttDefStore.GetInstance("B5DriftChamberHit")

        if isNew:
            store["HitType"] = G4AttDef("HitType", "Hit Type", "Physics", "", "G4String")
            store["ID"] = G4AttDef("ID", "ID", "Physics", "", "G4int")
            store["Time"] = G4AttDef("Time", "Time", "Physics", "G4BestUnit", "G4double")
            store["Pos"] = G4AttDef("Pos", "Position", "Physics", "G4BestUnit", "G4ThreeVector")

        return store

    def CreateAttValues(self):
        return [G4AttValue("HitType", "DriftChamberHit", ""),
                G4AttValue("ID", G4UIcommand.ConvertToString(self.fLayerID), ""),
                G4AttValue("Time", G4BestUnit(self.fTime, "Time"), ""),
                G4AttValue("Pos", G4BestUnit(self.fWorldPos, "Length"), "")]

    def Print(self):
        print("  Layer[", self.fLayerID, "] : time", self.fTime/ns,
              "(nsec) --- local (x,y)", self.fLocalPos.x, ",", self.fLocalPos.y)


class B5DriftChamberSD(G4VSensitiveDetector):

    def __init__(self, name):
        super().__init__(name)
        self.fHCID = -1
        self.collectionName.insert("driftChamberColl")

    def Initialize(self, hce):
        self.fHitsCollection = B5HitsCollection(self.SensitiveDetectorName, self.collectionName[0])

        if self.fHCID < 0:
            self.fHCID = G4SDManager.GetSDMpointer().GetCollectionID(self.fHitsCollection)

        hce.AddHitsCollection(self.fHCID, self.fHitsCollection)

    def ProcessHits(self, step, touchableHist):
        charge = step.GetTrack().GetDefinition().GetPDGCharge()
        if charge == 0:
            return True

        preStepPoint = step.GetPreStepPoint()

        touchable = step.GetPreStepPoint().GetTouchable()
        motherPhysical = touchable.GetVolume(1)  # mother
        copyNo = motherPhysical.GetCopyNo()

        worldPos = preStepPoint.GetPosition()
        localPos = touchable.GetHistory().GetTopTransform().TransformPoint(worldPos)

        hit = B5DriftChamberHit(copyNo)
        hit.fWorldPos = worldPos
        hit.fLocalPos = localPos
        hit.fTime = preStepPoint.GetGlobalTime()
        self.fHitsCollection.insert(hit)

        return True


class B5EmCalorimeterHit(G4VHit):

    def __init__(self, cellID=-1):
        super().__init__()
        self.fCellID = cellID
        self.fEdep = 0
        self.fPLogV = None

    def Draw(self):
        visManager = G4VVisManager.GetConcreteInstance()
        if visManager == None or self.fEdep == 0:
            return

        # Draw a calorimeter cell with a color corresponding to its energy deposit
        trans = G4Transform3D(self.fRot.inverse(), self.fPos)
        attribs = G4VisAttributes()
        pVA = self.fPLogV.GetVisAttributes()
        if pVA != None:
            attribs = pVA

        rcol = self.fEdep/(0.7*GeV)
        if rcol > 1:
            rcol = 1
        if rcol < 0.4:
            rcol = 0.4

        colour = G4Colour(rcol, 0, 0)
        attribs.SetColour(colour)
        attribs.SetForceSolid(True)
        visManager.Draw(self.fPLogV, attribs, trans)

    def GetAttDefs(self):
        store, isNew = G4AttDefStore.GetInstance("B5EmCalorimeterHit")

        if isNew:
            store["HitType"] = G4AttDef("HitType", "Hit Type", "Physics", "", "G4String")
            store["ID"] = G4AttDef("ID", "ID", "Physics", "", "G4int")
            store["Energy"] = G4AttDef("Energy", "Energy Deposited",
                                       "Physics", "G4BestUnit", "G4double")
            store["Pos"] = G4AttDef("Pos", "Position", "Physics", "G4BestUnit", "G4ThreeVector")
            store["LVol"] = G4AttDef("LVol", "Logical Volume", "Physics", "", "G4String")

        return store

    def CreateAttValues(self):
        values = [G4AttValue("HitType", "EmCalorimeterHit", ""),
                  G4AttValue("ID", G4UIcommand.ConvertToString(self.fCellID), ""),
                  G4AttValue("Energy", G4BestUnit(self.fEdep, "Energy"), ""),
                  G4AttValue("Pos", G4BestUnit(self.fPos, "Length"), "")]

        if self.fPLogV != None:
            values.append(G4AttValue("LVol", self.fPLogV.GetName(), ""))
        else:
            values.append(G4AttValue("LVol", " ", ""))

        return values

    def Print(self):
        print("  Cell[", self.fCellID, "]", self.fEdep/MeV, "(MeV)")


class B5EmCalorimeterSD(G4VSensitiveDetector):

    def __init__(self, name):
        super().__init__(name)
        self.fHCID = -1
        self.collectionName.insert("EMcalorimeterColl")

    def Initialize(self, hce):
        self.fHitsCollection = B5HitsCollection(self.SensitiveDetectorName, self.collectionName[0])

        if self.fHCID < 0:
            self.fHCID = G4SDManager.GetSDMpointer().GetCollectionID(self.fHitsCollection)

        hce.AddHitsCollection(self.fHCID, self.fHitsCollection)

        # fill calorimeter hits with zero energy deposition
        for i in range(kNofEmCells):
            self.fHitsCollection.insert(B5EmCalorimeterHit(i))

    def ProcessHits(self, step, touchableHist):
        edep = step.GetTotalEnergyDeposit()
        if edep == 0:
            return True

        touchable = step.GetPreStepPoint().GetTouchable()
        physical = touchable.GetVolume()
        copyNo = physical.GetCopyNo()

        hit = self.fHitsCollection[copyNo]
        # check if it is first touch
        if hit.fPLogV == None:
            # fill volume information
            hit.fPLogV = physical.GetLogicalVolume()
            transform = touchable.GetHistory().GetTopTransform().Invert()
            hit.fRot = transform.NetRotation()
            hit.fPos = transform.NetTranslation()

        # add energy deposition
        hit.fEdep += edep
        return True


class B5HadCalorimeterHit(G4VHit):

    def __init__(self, columnID=-1, rowID=-1):
        super().__init__()
        self.fColumnID = columnID
        self.fRowID = rowID
        self.fEdep = 0

    def Draw(self):
        visManager = G4VVisManager.GetConcreteInstance()
        if visManager == None or self.fEdep == 0:
            return

        # Draw a calorimeter cell with depth proportional to the energy deposition
        trans = G4Transform3D(self.fRot.inverse(), self.fPos)
        attribs = G4VisAttributes()
        colour = G4Colour(1, 0, 0)
        attribs.SetColour(colour)
        attribs.SetForceSolid(True)
        box = G4Box("dummy", 15*cm, 15*cm, 1*m*self.fEdep/(0.1*GeV))
        visManager.Draw(box, attribs, trans)

    def GetAttDefs(self):
        store, isNew = G4AttDefStore.GetInstance("B5HadCalorimeterHit")

        if isNew:
            store["HitType"] = G4AttDef("HitType", "Hit Type", "Physics", "", "G4String")
            store["Column"] = G4AttDef("Column", "Column ID", "Physics", "", "G4int")
            store["Row"] = G4AttDef("Row", "Row ID", "Physics", "", "G4int")
            store["Energy"] = G4AttDef("Energy", "Energy Deposited",
                                       "Physics", "G4BestUnit", "G4double")
            store["Pos"] = G4AttDef("Pos", "Position", "Physics", "G4BestUnit", "G4ThreeVector")

        return store

    def CreateAttValues(self):
        return [G4AttValue("HitType", "HadCalorimeterHit", ""),
                G4AttValue("Column", G4UIcommand.ConvertToString(self.fColumnID), ""),
                G4AttValue("Row", G4UIcommand.ConvertToString(self.fRowID), ""),
                G4AttValue("Energy", G4BestUnit(self.fEdep, "Energy"), ""),
                G4AttValue("Pos", G4BestUnit(self.fPos, "Length"), "")]

    def Print(self):
        print("  Cell[", self.fRowID, ",", self.fColumnID, "]", self.fEdep/MeV, "(MeV)", self.fPos)


class B5HadCalorimeterSD(G4VSensitiveDetector):

    def __init__(self, name):
        super().__init__(name)
        self.fHCID = -1
        self.collectionName.insert("HadCalorimeterColl")

    def Initialize(self, hce):
        self.fHitsCollection = B5HitsCollection(self.SensitiveDetectorName, self.collectionName[0])

        if self.fHCID < 0:
            self.fHCID = G4SDManager.GetSDMpointer().GetCollectionID(self.fHitsCollection)

        hce.AddHitsCollection(self.fHCID, self.fHitsCollection)

        # fill calorimeter hits with zero energy deposition
        for column in range(kNofHadColumns):
            for row in range(kNofHadRows):
                self.fHitsCollection.insert(B5HadCalorimeterHit())

    def ProcessHits(self, step, touchableHist):
        edep = step.GetTotalEnergyDeposit()
        if edep == 0:
            return True

        touchable = step.GetPreStepPoint().GetTouchable()
        rowNo = touchable.GetCopyNumber(2)
        columnNo = touchable.GetCopyNumber(3)
        hitID = kNofHadRows*columnNo+rowNo
        hit = self.fHitsCollection[hitID]

        # check if it is first touch
        if hit.fColumnID < 0:
            hit.fColumnID = columnNo
            hit.fRowID = rowNo
            depth = touchable.GetHistory().GetDepth()
            transform = touchable.GetHistory().GetTransform(depth-2).Invert()
            hit.fRot = transform.NetRotation()
            hit.fPos = transform.NetTranslation()

        # add energy deposition
        hit.fEdep += edep
        return True


class B5HodoscopeHit(G4VHit):

    def __init__(self, id, time):
        super().__init__()
        self.fId = id
        self.fTime = time

    def Draw(self):
        visManager = G4VVisManager.GetConcreteInstance()
        if visManager == None:
            return

        trans = G4Transform3D(self.fRot.inverse(), self.fPos)
        attribs = G4VisAttributes()
        pVA = self.fPLogV.GetVisAttributes()
        if pVA != None:
            attribs = pVA

        colour = G4Colour(0, 1, 1)
        attribs.SetColour(colour)
        attribs.SetForceSolid(True)
        visManager.Draw(self.fPLogV, attribs, trans)

    def GetAttDefs(self):
        store, isNew = G4AttDefStore.GetInstance("B5HodoscopeHit")

        if isNew:
            store["HitType"] = G4AttDef("HitType", "Hit Type", "Physics", "", "G4String")
            store["ID"] = G4AttDef("ID", "ID", "Physics", "", "G4int")
            store["Time"] = G4AttDef("Time", "Time", "Physics", "G4BestUnit", "G4double")
            store["Pos"] = G4AttDef("Pos", "Position", "Physics", "G4BestUnit", "G4ThreeVector")
            store["LVol"] = G4AttDef("LVol", "Logical Volume", "Physics", "", "G4String")

        return store

    def CreateAttValues(self):
        values = [G4AttValue("HitType", "HodoscopeHit", ""),
                  G4AttValue("ID", G4UIcommand.ConvertToString(self.fId), ""),
                  G4AttValue("Time", G4BestUnit(self.fTime, "Time"), ""),
                  G4AttValue("Pos", G4BestUnit(self.fPos, "Length"), "")]

        if self.fPLogV != None:
            values.append(G4AttValue("LVol", self.fPLogV.GetName(), ""))
        else:
            values.append(G4AttValue("LVol", " ", ""))

        return values

    def Print(self):
        print("  Hodoscope[", self.fId, "]", self.fTime/ns, "(nsec)")


class B5HodoscopeSD(G4VSensitiveDetector):

    def __init__(self, name):
        super().__init__(name)
        self.fHCID = -1
        self.collectionName.insert("hodoscopeColl")

    def Initialize(self, hce):
        self.fHitsCollection = B5HitsCollection(self.SensitiveDetectorName, self.collectionName[0])

        if self.fHCID < 0:
            self.fHCID = G4SDManager.GetSDMpointer().GetCollectionID(self.fHitsCollection)

        hce.AddHitsCollection(self.fHCID, self.fHitsCollection)

    def ProcessHits(self, step, touchableHist):
        edep = step.GetTotalEnergyDeposit()
        if edep == 0:
            return True

        preStepPoint = step.GetPreStepPoint()
        touchable = preStepPoint.GetTouchable()
        copyNo = touchable.GetVolume().GetCopyNo()
        hitTime = preStepPoint.GetGlobalTime()

        # check if this finger already has a hit
        ix = -1
        for i, hit in enumerate(self.fHitsCollection):
            if hit.fId == copyNo:
                ix = i
                break

        if ix >= 0:
            # if it has, then take the earlier time
            if self.fHitsCollection[ix].fTime > hitTime:
                self.fHitsCollection[ix].fTime = hitTime
        else:
            # if not, create a new hit and set it to the collection
            hit = B5HodoscopeHit(copyNo, hitTime)
            physical = touchable.GetVolume()
            hit.fPLogV = physical.GetLogicalVolume()
            transform = touchable.GetHistory().GetTopTransform().Invert()
            hit.fRot = transform.NetRotation()
            hit.fPos = transform.NetTranslation()
            self.fHitsCollection.insert(hit)

        return True


class B5PrimaryGeneratorAction(G4VUserPrimaryGeneratorAction):

    def __init__(self):
        super().__init__()
        nofParticles = 1
        self.fParticleGun = G4ParticleGun(nofParticles)

        particleTable = G4ParticleTable.GetParticleTable()
        self.fPositron = particleTable.FindParticle("e+")
        self.fMuon = particleTable.FindParticle("mu+")
        self.fPion = particleTable.FindParticle("pi+")
        self.fKaon = particleTable.FindParticle("kaon+")
        self.fProton = particleTable.FindParticle("proton")

        # default particle kinematics
        self.fParticleGun.SetParticlePosition(G4ThreeVector(0, 0, -8*m))
        self.fParticleGun.SetParticleDefinition(self.fPositron)

        # G4GenericMessenger.Property is a wrapper around python's
        # primitive types to allow them to be referenced
        self.fMomentum = G4GenericMessenger.Property(1000*MeV)
        self.fSigmaMomentum = G4GenericMessenger.Property(50*MeV)
        self.fSigmaAngle = G4GenericMessenger.Property(2*deg)
        self.fRandomizePrimary = G4GenericMessenger.Property(True)

        # define commands for this class
        # Define /B5/generator command directory using generic messenger class
        self.fMessenger = G4GenericMessenger(self, "/B5/generator/", "Primary generator control")

        # momentum command
        momentumCmd = self.fMessenger.DeclarePropertyWithUnit(
            "momentum", "GeV", self.fMomentum, "Mean momentum of primaries.")

        momentumCmd.SetParameterName("p", True)
        momentumCmd.SetRange("p >= 0")
        momentumCmd.SetDefaultValue("1")
        # ok
        # momentumCmd.SetParameterName("p", True)
        # momentumCmd.SetRange("p >= 0")

        # sigmaMomentum command
        sigmaMomentumCmd = self.fMessenger.DeclarePropertyWithUnit(
            "sigmaMomentum", "MeV", self.fSigmaMomentum, "Sigma momentum of primaries.")

        sigmaMomentumCmd.SetParameterName("sp", True)
        sigmaMomentumCmd.SetRange("sp >= 0")
        sigmaMomentumCmd.SetDefaultValue("50")

        # sigmaAngle command
        sigmaAngleCmd = self.fMessenger.DeclarePropertyWithUnit(
            "sigmaAngle", "deg", self.fSigmaAngle, "Sigma angle divergence of primaries.")
        sigmaAngleCmd.SetParameterName("t", True)
        sigmaAngleCmd.SetRange("t >= 0")
        sigmaAngleCmd.SetDefaultValue("2")

        # randomizePrimary command
        randomCmd = self.fMessenger.DeclareProperty("randomizePrimary", self.fRandomizePrimary)
        guidance = "Boolean flag for randomizing primary particle types.\n"
        guidance += "In case this flag is false, you can select the primary particle\n"
        guidance += "  with /gun/particle command."
        randomCmd.SetGuidance(guidance)
        randomCmd.SetParameterName("flg", True)
        randomCmd.SetDefaultValue("true")

    def GeneratePrimaries(self, event):
        if self.fRandomizePrimary.value:
            i = int(5 * G4UniformRand())
            if i == 0:
                particle = self.fPositron
            elif i == 1:
                particle = self.fMuon
            elif i == 2:
                particle = self.fPion
            elif i == 3:
                particle = self.fKaon
            else:
                particle = self.fProton

            self.fParticleGun.SetParticleDefinition(particle)
        else:
            particle = self.fParticleGun.GetParticleDefinition()

        pp = self.fMomentum.value + (G4UniformRand()-0.5)*self.fSigmaMomentum.value
        mass = particle.GetPDGMass()
        ekin = math.sqrt(pp*pp+mass*mass)-mass
        self.fParticleGun.SetParticleEnergy(ekin)

        angle = (G4UniformRand()-0.5)*self.fSigmaAngle.value
        self.fParticleGun.SetParticleMomentumDirection(
            G4ThreeVector(math.sin(angle), 0, math.cos(angle)))

        self.fParticleGun.GeneratePrimaryVertex(event)


class B5EventAction(G4UserEventAction):

    def __init__(self):
        super().__init__()
        self.fHodHCID = [-1, -1]
        self.fDriftHCID = [-1, -1]
        self.fCalHCID = [-1, -1]
        self.fDriftHistoID = [[-1, -1], [-1, -1]]
        self.fCalEdep = [[0] * kNofEmCells, [0] * kNofHadCells]

        # set printing per each event
        G4RunManager.GetRunManager().SetPrintProgress(1)

    def BeginOfEventAction(self, event):
        # Find hit collections and histogram Ids by names (just once)
        # and save them in the data members of this class

        if self.fHodHCID[0] == -1:
            sdManager = G4SDManager.GetSDMpointer()
            analysisManager = G4AnalysisManager.Instance()

            # hits collections names
            hHCName = ["hodoscope1/hodoscopeColl", "hodoscope2/hodoscopeColl"]
            dHCName = ["chamber1/driftChamberColl", "chamber2/driftChamberColl"]
            cHCName = ["EMcalorimeter/EMcalorimeterColl", "HadCalorimeter/HadCalorimeterColl"]

            # histograms names
            histoName = [["Chamber1", "Chamber2"], ["Chamber1 XY", "Chamber2 XY"]]

            for iDet in range(2):
                # hit collections IDs
                self.fHodHCID[iDet] = sdManager.GetCollectionID(hHCName[iDet])
                self.fDriftHCID[iDet] = sdManager.GetCollectionID(dHCName[iDet])
                self.fCalHCID[iDet] = sdManager.GetCollectionID(cHCName[iDet])
                # histograms IDs
                self.fDriftHistoID[0][iDet] = analysisManager.GetH1Id(histoName[0][iDet])
                self.fDriftHistoID[1][iDet] = analysisManager.GetH2Id(histoName[1][iDet])

    def GetHC(self, event, collId):
        hce = event.GetHCofThisEvent()
        if hce == None:
            G4Exception("B5EventAction::EndOfEventAction()", "B5Code001",
                        JustWarning, "No hits collection of this event found.")
            return None

        hc = hce.GetHC(collId)
        if hc == None:
            G4Exception("B5EventAction::EndOfEventAction()", "B5Code001", JustWarning,
                        "Hits collection " + str(collId) + " of this event not found.")

        return hc

    def EndOfEventAction(self, event):
        # Fill histograms & ntuple

        # Get analysis manager
        analysisManager = G4AnalysisManager.Instance()

        # Drift chambers hits
        for iDet in range(2):
            hc = self.GetHC(event, self.fDriftHCID[iDet])

            if hc == None:
                return

            nhit = hc.GetSize()
            analysisManager.FillH1(self.fDriftHistoID[0][iDet], nhit)

            # columns 0, 1
            analysisManager.FillNtupleIColumn(iDet, nhit)

            for hit in hc:
                localPos = hit.fLocalPos
                analysisManager.FillH2(self.fDriftHistoID[1][iDet], localPos.x, localPos.y)

        # Em/Had Calorimeters hits
        totalCalHit = [0, 0]
        totalCalEdep = [0, 0]

        for iDet in range(2):
            hc = self.GetHC(event, self.fCalHCID[iDet])
            if hc == None:
                return

            for i, hit in enumerate(hc):
                edep = hit.fEdep

                if edep > 0:
                    totalCalHit[iDet] += 1
                    totalCalEdep[iDet] += edep

                self.fCalEdep[iDet][i] = edep

            # columns 2, 3
            analysisManager.FillNtupleDColumn(iDet + 2, totalCalEdep[iDet])

        # Hodoscopes hits
        for iDet in range(2):
            hc = self.GetHC(event, self.fHodHCID[iDet])
            if hc == None:
                return

            for hit in hc:
                # columns 4, 5
                analysisManager.FillNtupleDColumn(iDet + 4, hit.fTime)

        for emCalEdep in self.fCalEdep[0]:
            analysisManager.FillNtupleDColumn(6, emCalEdep)
        for hadCalEdep in self.fCalEdep[1]:
            analysisManager.FillNtupleDColumn(7, hadCalEdep)

        analysisManager.AddNtupleRow()

        # Print diagnostics
        printModulo = G4RunManager.GetRunManager().GetPrintProgress()
        if printModulo == 0 or event.GetEventID() % printModulo != 0:
            return

        primary = event.GetPrimaryVertex(0).GetPrimary(0)
        print(">>> Event", event.GetEventID(), ">>> Simulation truth :", primary.GetG4code().GetParticleName(),
              primary.GetMomentum())

        # Hodoscopes
        for iDet in range(2):
            hc = self.GetHC(event, self.fHodHCID[iDet])
            if hc == None:
                return

            print("Hodoscope", iDet + 1, "has", hc.GetSize(), "hits.")
            for hit in hc:
                hit.Print()

        # Drift chambers
        for iDet in range(2):
            hc = self.GetHC(event, self.fDriftHCID[iDet])
            if hc == None:
                return

            print("Drift Chamber", iDet + 1, "has",  hc.GetSize(), "hits.")
            for layer in range(kNofChambers):
                for hit in hc:
                    if hit.fLayerID == layer:
                        hit.Print()

        # Calorimeters
        calName = ["EM", "Hadron"]
        for iDet in range(2):
            print(calName[iDet], "Calorimeter has", totalCalHit[iDet],
                  "hits.", "Total Edep is", totalCalEdep[iDet]/MeV, "(MeV)")


class B5RunAction(G4UserRunAction):

    def __init__(self, eventAction):
        super().__init__()
        self.fEventAction = eventAction

        # Create the generic analysis manager
        # The choice of analysis technology is done according to the file extension
        analysisManager = G4AnalysisManager.Instance()
        analysisManager.SetDefaultFileType("root")
        # If the filename extension is not provided, the default file type (root)
        # will be used for all files specified without extension.
        analysisManager.SetVerboseLevel(1)

        # Default settings
        analysisManager.SetNtupleMerging(True)
        # Note: merging ntuples is available only with Root output
        analysisManager.SetFileName("B5")
        # If the filename extension is not provided, the default file type (root)
        # will be used for all files specified without extension.
        # analysisManager->SetDefaultFileType("xml")
        # The default file type (root) can be redefined by the user.

        # Book histograms, ntuple

        # Creating 1D histograms
        analysisManager.CreateH1("Chamber1", "Drift Chamber 1 # Hits", 50, 0, 50)  # h1 Id = 0
        analysisManager.CreateH1("Chamber2", "Drift Chamber 2 # Hits", 50, 0, 50)  # h1 Id = 1

        # Creating 2D histograms
        analysisManager.CreateH2("Chamber1 XY", "Drift Chamber 1 X vs Y",
                                 50, -1000, 1000, 50, -300, 300)  # h2 Id = 0
        analysisManager.CreateH2("Chamber2 XY", "Drift Chamber 2 X vs Y",
                                 50, -1500, 1500, 50, -300, 300)  # h2 Id = 1

        # Creating ntuple
        if self.fEventAction != None:
            analysisManager.CreateNtuple("B5", "Hits")
            analysisManager.CreateNtupleIColumn("Dc1Hits")         # column Id = 0
            analysisManager.CreateNtupleIColumn("Dc2Hits")         # column Id = 1
            analysisManager.CreateNtupleDColumn("ECEnergy")        # column Id = 2
            analysisManager.CreateNtupleDColumn("HCEnergy")        # column Id = 3
            analysisManager.CreateNtupleDColumn("Time1")           # column Id = 4
            analysisManager.CreateNtupleDColumn("Time2")           # column Id = 5
            analysisManager.CreateNtupleDColumn("ECEnergyVector")  # column Id = 6
            analysisManager.CreateNtupleDColumn("HCEnergyVector")  # column Id = 7
            analysisManager.FinishNtuple()

        # Set ntuple output file
        analysisManager.SetNtupleFileName(0, "B4ntuple")

    def BeginOfRunAction(self, run):
        # inform the runManager to save random number seed
        # G4RunManager.GetRunManager().SetRandomNumberStore(True)

        # Get analysis manager
        analysisManager = G4AnalysisManager.Instance()

        # Reset histograms from previous run
        analysisManager.Reset()

        # Open an output file
        # The default file name is set in B5RunAction.B5RunAction()
        # it can be overwritten in a macro
        analysisManager.OpenFile()

    def EndOfRunAction(self, run):
        # save histograms & ntuple
        analysisManager = G4AnalysisManager.Instance()
        analysisManager.Write()
        analysisManager.CloseFile(False)


class B5ActionInitialization(G4VUserActionInitialization):

    def BuildForMaster(self):
        self.SetUserAction(B5RunAction(B5EventAction()))

    def Build(self):
        self.SetUserAction(B5PrimaryGeneratorAction())
        eventAction = B5EventAction()
        self.SetUserAction(eventAction)
        self.SetUserAction(B5RunAction(eventAction))


# Detect interactive mode (if no arguments) and define UI session
ui = None
if len(sys.argv) == 1:
    ui = G4UIExecutive(len(sys.argv), sys.argv)

# Construct the default run manager
runManager = G4RunManagerFactory.CreateRunManager(G4RunManagerType.Serial)

# Mandatory user initialization classes
runManager.SetUserInitialization(B5DetectorConstruction())

physicsList = FTFP_BERT()
physicsList.RegisterPhysics(G4StepLimiterPhysics())
runManager.SetUserInitialization(physicsList)

# User action initialization
runManager.SetUserInitialization(B5ActionInitialization())

visManager = G4VisExecutive()
# G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
# visManager = G4VisExecutive("Quiet")
visManager.Initialize()

# Get the User Interface manager
UImanager = G4UImanager.GetUIpointer()

# # Process macro or start UI session
if ui == None:
    # execute an argument macro file if exist
    command = "/control/execute "
    fileName = sys.argv[1]
    UImanager.ApplyCommand(command+fileName)
else:
    # interactive mode
    UImanager.ApplyCommand("/control/execute init_vis.mac")
    if ui.IsGUI():
        UImanager.ApplyCommand("/control/execute gui.mac")

    # start interactive session
    ui.SessionStart()
