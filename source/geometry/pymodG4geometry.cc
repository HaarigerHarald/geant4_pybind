#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define EXPORT_G4HEADER(header, mod)   \
   void export_##header(py::module &); \
   export_##header(mod)

void export_modG4geometry(py::module &m)
{
   EXPORT_G4HEADER(G4AffineTransform, m);
   EXPORT_G4HEADER(G4ChargeState, m);
   EXPORT_G4HEADER(G4ModifiedMidpoint, m);

   EXPORT_G4HEADER(G4VGCellFinder, m);
   EXPORT_G4HEADER(G4VImportanceAlgorithm, m);
   EXPORT_G4HEADER(G4VImportanceSplitExaminer, m);
   EXPORT_G4HEADER(G4VIStore, m);
   EXPORT_G4HEADER(G4VWeightWindowAlgorithm, m);
   EXPORT_G4HEADER(G4VWeightWindowStore, m);
   EXPORT_G4HEADER(G4GeometryCell, m);
   EXPORT_G4HEADER(G4GeometryCellComp, m);
   EXPORT_G4HEADER(G4GeometryCellStep, m);
   EXPORT_G4HEADER(G4ImportanceAlgorithm, m);
   EXPORT_G4HEADER(G4IStore, m);
   EXPORT_G4HEADER(G4WeightWindowAlgorithm, m);
   EXPORT_G4HEADER(G4WeightWindowStore, m);

   EXPORT_G4HEADER(G4EquationOfMotion, m);
   EXPORT_G4HEADER(G4EqGravityField, m);
   EXPORT_G4HEADER(G4EqMagElectricField, m);
   EXPORT_G4HEADER(G4EqEMFieldWithEDM, m);
   EXPORT_G4HEADER(G4EqEMFieldWithSpin, m);
   EXPORT_G4HEADER(G4Mag_EqRhs, m);
   EXPORT_G4HEADER(G4MonopoleEq, m);
   EXPORT_G4HEADER(G4RepleteEofM, m);
   EXPORT_G4HEADER(G4Mag_UsualEqRhs, m);
   EXPORT_G4HEADER(G4ErrorMag_UsualEqRhs, m);
   EXPORT_G4HEADER(G4Mag_SpinEqRhs, m);
   EXPORT_G4HEADER(G4LineSection, m);
   EXPORT_G4HEADER(G4FieldTrack, m);
   EXPORT_G4HEADER(G4FieldUtils, m);
   EXPORT_G4HEADER(G4BulirschStoer, m);

   EXPORT_G4HEADER(G4Field, m);
   EXPORT_G4HEADER(G4ElectroMagneticField, m);
   EXPORT_G4HEADER(G4MagneticField, m);
   EXPORT_G4HEADER(G4ElectricField, m);
   EXPORT_G4HEADER(G4CachedMagneticField, m);
   EXPORT_G4HEADER(G4DELPHIMagField, m);
   EXPORT_G4HEADER(G4HarmonicPolMagField, m);
   EXPORT_G4HEADER(G4LineCurrentMagField, m);
   EXPORT_G4HEADER(G4QuadrupoleMagField, m);
   EXPORT_G4HEADER(G4SextupoleMagField, m);
   EXPORT_G4HEADER(G4TQuadrupoleMagField, m);
   EXPORT_G4HEADER(G4UniformElectricField, m);
   EXPORT_G4HEADER(G4UniformGravityField, m);
   EXPORT_G4HEADER(G4UniformMagField, m);

   EXPORT_G4HEADER(G4MagIntegratorStepper, m);
   EXPORT_G4HEADER(G4MagHelicalStepper, m);
   EXPORT_G4HEADER(G4ExactHelixStepper, m);
   EXPORT_G4HEADER(G4HelixMixedStepper, m);
   EXPORT_G4HEADER(G4MagErrorStepper, m);
   EXPORT_G4HEADER(G4RKG3_Stepper, m);
   EXPORT_G4HEADER(G4VFSALIntegrationStepper, m);
   EXPORT_G4HEADER(G4BogackiShampine23, m);
   EXPORT_G4HEADER(G4BogackiShampine45, m);
   EXPORT_G4HEADER(G4CashKarpRKF45, m);
   EXPORT_G4HEADER(G4ClassicalRK4, m);
   EXPORT_G4HEADER(G4ConstRK4, m);
   EXPORT_G4HEADER(G4DoLoMcPriRK34, m);
   EXPORT_G4HEADER(G4DormandPrince745, m);
   EXPORT_G4HEADER(G4DormandPrinceRK56, m);
   EXPORT_G4HEADER(G4DormandPrinceRK78, m);
   EXPORT_G4HEADER(G4ExplicitEuler, m);
   EXPORT_G4HEADER(G4FSALBogackiShampine45, m);
   EXPORT_G4HEADER(G4FSALDormandPrince745, m);
   EXPORT_G4HEADER(G4HelixExplicitEuler, m);
   EXPORT_G4HEADER(G4HelixHeum, m);
   EXPORT_G4HEADER(G4HelixImplicitEuler, m);
   EXPORT_G4HEADER(G4HelixSimpleRunge, m);
   EXPORT_G4HEADER(G4ImplicitEuler, m);
   EXPORT_G4HEADER(G4NystromRK4, m);
   EXPORT_G4HEADER(G4RK547FEq1, m);
   EXPORT_G4HEADER(G4RK547FEq2, m);
   EXPORT_G4HEADER(G4RK547FEq3, m);
   EXPORT_G4HEADER(G4SimpleHeum, m);
   EXPORT_G4HEADER(G4SimpleRunge, m);
   EXPORT_G4HEADER(G4TsitourasRK45, m);

   EXPORT_G4HEADER(G4VIntegrationDriver, m);
   EXPORT_G4HEADER(G4BFieldIntegrationDriver, m);
   EXPORT_G4HEADER(G4MagIntegratorDriver, m);
   EXPORT_G4HEADER(G4OldMagIntDriver, m);
   EXPORT_G4HEADER(G4DriverReporter, m);
   EXPORT_G4HEADER(G4TrialsCounter, m);

   EXPORT_G4HEADER(G4ChordFinder, m);

   EXPORT_G4HEADER(G4FieldManager, m);
   EXPORT_G4HEADER(G4FieldManagerStore, m);
   EXPORT_G4HEADER(G4TransportationManager, m);

   EXPORT_G4HEADER(G4GlobalMagFieldMessenger, m);
   EXPORT_G4HEADER(G4GeometryMessenger, m);

   EXPORT_G4HEADER(G4NavigationHistory, m);
   EXPORT_G4HEADER(G4VoxelLimits, m);

   EXPORT_G4HEADER(G4VTouchable, m);
   EXPORT_G4HEADER(G4GRSSolid, m);
   EXPORT_G4HEADER(G4GRSVolume, m);
   EXPORT_G4HEADER(G4TouchableHistory, m);

   EXPORT_G4HEADER(G4VSolid, m);
   EXPORT_G4HEADER(G4ReflectedSolid, m);
   EXPORT_G4HEADER(G4SolidStore, m);

   EXPORT_G4HEADER(G4CSGSolid, m);
   EXPORT_G4HEADER(G4Box, m);
   EXPORT_G4HEADER(G4Cons, m);
   EXPORT_G4HEADER(G4CutTubs, m);
   EXPORT_G4HEADER(G4Orb, m);
   EXPORT_G4HEADER(G4Para, m);
   EXPORT_G4HEADER(G4Sphere, m);
   EXPORT_G4HEADER(G4Torus, m);
   EXPORT_G4HEADER(G4Trap, m);
   EXPORT_G4HEADER(G4Trd, m);
   EXPORT_G4HEADER(G4Tubs, m);

   EXPORT_G4HEADER(G4BooleanSolid, m);
   EXPORT_G4HEADER(G4DisplacedSolid, m);
   EXPORT_G4HEADER(G4IntersectionSolid, m);
   EXPORT_G4HEADER(G4MultiUnion, m);
   EXPORT_G4HEADER(G4ScaledSolid, m);
   EXPORT_G4HEADER(G4SubtractionSolid, m);
   EXPORT_G4HEADER(G4UnionSolid, m);

   EXPORT_G4HEADER(G4VCSGface, m);
   EXPORT_G4HEADER(G4VCSGfaceted, m);
   EXPORT_G4HEADER(G4VFacet, m);
   EXPORT_G4HEADER(G4VTwistedFaceted, m);
   EXPORT_G4HEADER(G4VTwistSurface, m);
   EXPORT_G4HEADER(G4TessellatedSolid, m);
   EXPORT_G4HEADER(G4SurfBits, m);
   EXPORT_G4HEADER(G4Voxelizer, m);
   EXPORT_G4HEADER(G4ClippablePolygon, m);
   EXPORT_G4HEADER(G4Ellipsoid, m);
   EXPORT_G4HEADER(G4EllipticalCone, m);
   EXPORT_G4HEADER(G4EllipticalTube, m);
   EXPORT_G4HEADER(G4EnclosingCylinder, m);
   EXPORT_G4HEADER(G4ExtrudedSolid, m);
   EXPORT_G4HEADER(G4GenericPolycone, m);
   EXPORT_G4HEADER(G4GenericTrap, m);
   EXPORT_G4HEADER(G4Hype, m);
   EXPORT_G4HEADER(G4IntersectingCone, m);
   EXPORT_G4HEADER(G4Paraboloid, m);
   EXPORT_G4HEADER(G4Polycone, m);
   EXPORT_G4HEADER(G4PolyconeHistorical, m);
   EXPORT_G4HEADER(G4PolyconeSide, m);
   EXPORT_G4HEADER(G4Polyhedra, m);
   EXPORT_G4HEADER(G4PolyhedraHistorical, m);
   EXPORT_G4HEADER(G4PolyhedraSide, m);
   EXPORT_G4HEADER(G4PolyPhiFace, m);
   EXPORT_G4HEADER(G4QuadrangularFacet, m);
   EXPORT_G4HEADER(G4ReduciblePolygon, m);
   EXPORT_G4HEADER(G4SolidExtentList, m);
   EXPORT_G4HEADER(G4SolidsWorkspace, m);
   EXPORT_G4HEADER(G4TessellatedGeometryAlgorithms, m);
   EXPORT_G4HEADER(G4Tet, m);
   EXPORT_G4HEADER(G4TriangularFacet, m);
   EXPORT_G4HEADER(G4TwistBoxSide, m);
   EXPORT_G4HEADER(G4TwistedBox, m);
   EXPORT_G4HEADER(G4TwistedTrap, m);
   EXPORT_G4HEADER(G4TwistedTrd, m);
   EXPORT_G4HEADER(G4TwistedTubs, m);
   EXPORT_G4HEADER(G4TwistTrapAlphaSide, m);
   EXPORT_G4HEADER(G4TwistTrapFlatSide, m);
   EXPORT_G4HEADER(G4TwistTrapParallelSide, m);
   EXPORT_G4HEADER(G4TwistTubsFlatSide, m);
   EXPORT_G4HEADER(G4TwistTubsHypeSide, m);
   EXPORT_G4HEADER(G4TwistTubsSide, m);

   EXPORT_G4HEADER(G4LogicalVolume, m);
   EXPORT_G4HEADER(G4LogicalCrystalVolume, m);
   EXPORT_G4HEADER(G4LogicalVolumeStore, m);

   EXPORT_G4HEADER(G4VPVParameterisation, m);
   EXPORT_G4HEADER(G4VNestedParameterisation, m);
   EXPORT_G4HEADER(G4VDivisionParameterisation, m);
   EXPORT_G4HEADER(G4ParameterisationBox, m);
   EXPORT_G4HEADER(G4ParameterisationCons, m);
   EXPORT_G4HEADER(G4ParameterisationPara, m);
   EXPORT_G4HEADER(G4ParameterisationPolycone, m);
   EXPORT_G4HEADER(G4ParameterisationPolyhedra, m);
   EXPORT_G4HEADER(G4ParameterisationTrd, m);
   EXPORT_G4HEADER(G4ParameterisationTubs, m);
   EXPORT_G4HEADER(G4PhantomParameterisation, m);
   EXPORT_G4HEADER(G4PartialPhantomParameterisation, m);

   EXPORT_G4HEADER(G4VPhysicalVolume, m);
   EXPORT_G4HEADER(G4PVDivision, m);
   EXPORT_G4HEADER(G4VExternalPhysicalVolume, m);
   EXPORT_G4HEADER(G4PVPlacement, m);
   EXPORT_G4HEADER(G4PVReplica, m);
   EXPORT_G4HEADER(G4ReplicatedSlice, m);
   EXPORT_G4HEADER(G4PVParameterised, m);
   EXPORT_G4HEADER(G4PhysicalVolumeStore, m);

   EXPORT_G4HEADER(G4VPVDivisionFactory, m);
   EXPORT_G4HEADER(G4PVDivisionFactory, m);

   EXPORT_G4HEADER(G4VUserRegionInformation, m);
   EXPORT_G4HEADER(G4Region, m);
   EXPORT_G4HEADER(G4RegionStore, m);

   EXPORT_G4HEADER(G4BlockingList, m);
   EXPORT_G4HEADER(G4BoundingEnvelope, m);
   EXPORT_G4HEADER(G4ErrorTarget, m);
   EXPORT_G4HEADER(G4ErrorTanPlaneTarget, m);
   EXPORT_G4HEADER(G4ErrorSurfaceTarget, m);
   EXPORT_G4HEADER(G4ErrorCylSurfaceTarget, m);
   EXPORT_G4HEADER(G4ErrorPlaneSurfaceTarget, m);
   EXPORT_G4HEADER(G4GeomTools, m);
   EXPORT_G4HEADER(G4LogicalSurface, m);
   EXPORT_G4HEADER(G4SmartVoxelNode, m);
   EXPORT_G4HEADER(G4SmartVoxelProxy, m);
   EXPORT_G4HEADER(G4SmartVoxelHeader, m);
   EXPORT_G4HEADER(G4SmartVoxelStat, m);
   EXPORT_G4HEADER(G4VCurvedTrajectoryFilter, m);
   EXPORT_G4HEADER(G4IdentityTrajectoryFilter, m);
   EXPORT_G4HEADER(G4VVolumeMaterialScanner, m);

   EXPORT_G4HEADER(G4VIntersectionLocator, m);
   EXPORT_G4HEADER(G4VoxelNavigation, m);
   EXPORT_G4HEADER(G4VoxelSafety, m);
   EXPORT_G4HEADER(G4VExternalNavigation, m);
   EXPORT_G4HEADER(G4Navigator, m);
   EXPORT_G4HEADER(G4AuxiliaryNavServices, m);
   EXPORT_G4HEADER(G4BrentLocator, m);
   EXPORT_G4HEADER(G4DrawVoxels, m);
   EXPORT_G4HEADER(G4ErrorPropagationNavigator, m);
   EXPORT_G4HEADER(G4GeomTestVolume, m);
   EXPORT_G4HEADER(G4LocatorChangeRecord, m);
   EXPORT_G4HEADER(G4LocatorChangeLogger, m);
   EXPORT_G4HEADER(G4MultiLevelLocator, m);
   EXPORT_G4HEADER(G4MultiNavigator, m);
   EXPORT_G4HEADER(G4NavigationLogger, m);
   EXPORT_G4HEADER(G4NormalNavigation, m);
   EXPORT_G4HEADER(G4ParameterisedNavigation, m);
   EXPORT_G4HEADER(G4PathFinder, m);
   EXPORT_G4HEADER(G4PropagatorInField, m);
   EXPORT_G4HEADER(G4RegularNavigation, m);
   EXPORT_G4HEADER(G4RegularNavigationHelper, m);
   EXPORT_G4HEADER(G4ReplicaNavigation, m);
   EXPORT_G4HEADER(G4SafetyHelper, m);
   EXPORT_G4HEADER(G4SimpleLocator, m);

   EXPORT_G4HEADER(G4GeometryManager, m);

   EXPORT_G4HEADER(G4AssemblyVolume, m);
   EXPORT_G4HEADER(G4AssemblyTriplet, m);
   EXPORT_G4HEADER(G4AssemblyStore, m);
   EXPORT_G4HEADER(G4GeometryWorkspace, m);
   EXPORT_G4HEADER(G4LogicalBorderSurface, m);
   EXPORT_G4HEADER(G4LogicalSkinSurface, m);
   EXPORT_G4HEADER(G4NavigationHistoryPool, m);
   EXPORT_G4HEADER(G4NavigationLevel, m);
   EXPORT_G4HEADER(G4NavigationLevelRep, m);
   EXPORT_G4HEADER(G4ReflectionFactory, m);
}
