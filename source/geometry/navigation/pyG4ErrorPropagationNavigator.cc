#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ErrorPropagationNavigator.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4ProductionCuts.hh>
#include <G4Material.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VisAttributes.hh>
#include <G4Allocator.hh>
#include <G4ReferenceCountedHandle.hh>
#include <G4VoxelLimits.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4VoxelSafety.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Trd.hh>
#include <G4Trap.hh>
#include <G4Cons.hh>
#include <G4Sphere.hh>
#include <G4Orb.hh>
#include <G4Ellipsoid.hh>
#include <G4Torus.hh>
#include <G4Para.hh>
#include <G4Polycone.hh>
#include <G4Polyhedra.hh>
#include <G4Hype.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ErrorPropagationNavigator : public G4ErrorPropagationNavigator, public py::trampoline_self_life_support {
public:
   using G4ErrorPropagationNavigator::G4ErrorPropagationNavigator;

   G4double ComputeStep(const G4ThreeVector &pGlobalPoint, const G4ThreeVector &pDirection,
                        const G4double pCurrentProposedStepLength, G4double &pNewSafety) override
   {
      PYBIND11_OVERRIDE(G4double, G4ErrorPropagationNavigator, ComputeStep, pGlobalPoint, pDirection,
                        pCurrentProposedStepLength, pNewSafety);
   }

   G4double ComputeSafety(const G4ThreeVector &globalpoint, const G4double pProposedMaxLength,
                          const G4bool keepState) override
   {
      PYBIND11_OVERRIDE(G4double, G4ErrorPropagationNavigator, ComputeSafety, globalpoint, pProposedMaxLength,
                        keepState);
   }

   G4ThreeVector GetGlobalExitNormal(const G4ThreeVector &point, G4bool *valid) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4ErrorPropagationNavigator, GetGlobalExitNormal, point, valid);
   }

   G4VPhysicalVolume *ResetHierarchyAndLocate(const G4ThreeVector &point, const G4ThreeVector &direction,
                                              const G4TouchableHistory &h) override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4ErrorPropagationNavigator, ResetHierarchyAndLocate, point, direction, h);
   }

   G4VPhysicalVolume *LocateGlobalPointAndSetup(const G4ThreeVector &point, const G4ThreeVector *direction,
                                                const G4bool pRelativeSearch, const G4bool ignoreDirection) override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4ErrorPropagationNavigator, LocateGlobalPointAndSetup, point, direction,
                        pRelativeSearch, ignoreDirection);
   }

   void LocateGlobalPointWithinVolume(const G4ThreeVector &position) override
   {
      PYBIND11_OVERRIDE(void, G4ErrorPropagationNavigator, LocateGlobalPointWithinVolume, position);
   }

   G4TouchableHistoryHandle CreateTouchableHistoryHandle() const override
   {
      PYBIND11_OVERRIDE(G4TouchableHistoryHandle, G4ErrorPropagationNavigator, CreateTouchableHistoryHandle, );
   }

   G4ThreeVector GetLocalExitNormal(G4bool *valid) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4ErrorPropagationNavigator, GetLocalExitNormal, valid);
   }

   G4ThreeVector GetLocalExitNormalAndCheck(const G4ThreeVector &point, G4bool *valid) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4ErrorPropagationNavigator, GetLocalExitNormalAndCheck, point, valid);
   }

   void ResetState() override { PYBIND11_OVERRIDE(void, G4ErrorPropagationNavigator, ResetState, ); }

   void SetupHierarchy() override { PYBIND11_OVERRIDE(void, G4ErrorPropagationNavigator, SetupHierarchy, ); }
};

void export_G4ErrorPropagationNavigator(py::module &m)
{
   py::class_<G4ErrorPropagationNavigator, PyG4ErrorPropagationNavigator, G4Navigator>(m, "G4ErrorPropagationNavigator")

      .def(py::init<>())
      .def("ComputeStep", &G4ErrorPropagationNavigator::ComputeStep, py::arg("pGlobalPoint"), py::arg("pDirection"),
           py::arg("pCurrentProposedStepLength"), py::arg("pNewSafety"))

      .def("ComputeSafety", &G4ErrorPropagationNavigator::ComputeSafety, py::arg("globalpoint"),
           py::arg("pProposedMaxLength") = DBL_MAX, py::arg("keepState") = true)

      .def("GetGlobalExitNormal", &G4ErrorPropagationNavigator::GetGlobalExitNormal, py::arg("point"), py::arg("valid"))
      .def("TargetSafetyFromPoint", &G4ErrorPropagationNavigator::TargetSafetyFromPoint, py::arg("pGlobalpoint"));
}
