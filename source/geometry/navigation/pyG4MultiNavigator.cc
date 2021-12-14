#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MultiNavigator.hh>
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
#include <G4TransportationManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4MultiNavigator : public G4MultiNavigator, public py::trampoline_self_life_support {
public:
   using G4MultiNavigator::G4MultiNavigator;

   G4double ComputeStep(const G4ThreeVector &pGlobalPoint, const G4ThreeVector &pDirection,
                        const G4double pCurrentProposedStepLength, G4double &pNewSafety) override
   {
      PYBIND11_OVERRIDE(G4double, G4MultiNavigator, ComputeStep, pGlobalPoint, pDirection, pCurrentProposedStepLength,
                        pNewSafety);
   }

   G4VPhysicalVolume *ResetHierarchyAndLocate(const G4ThreeVector &point, const G4ThreeVector &direction,
                                              const G4TouchableHistory &h) override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4MultiNavigator, ResetHierarchyAndLocate, point, direction, h);
   }

   G4VPhysicalVolume *LocateGlobalPointAndSetup(const G4ThreeVector &point, const G4ThreeVector *direction,
                                                const G4bool pRelativeSearch, const G4bool ignoreDirection) override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4MultiNavigator, LocateGlobalPointAndSetup, point, direction,
                        pRelativeSearch, ignoreDirection);
   }

   void LocateGlobalPointWithinVolume(const G4ThreeVector &position) override
   {
      PYBIND11_OVERRIDE(void, G4MultiNavigator, LocateGlobalPointWithinVolume, position);
   }

   G4double ComputeSafety(const G4ThreeVector &globalpoint, const G4double pProposedMaxLength,
                          const G4bool keepState) override
   {
      PYBIND11_OVERRIDE(G4double, G4MultiNavigator, ComputeSafety, globalpoint, pProposedMaxLength, keepState);
   }

   G4TouchableHistoryHandle CreateTouchableHistoryHandle() const override
   {
      PYBIND11_OVERRIDE(G4TouchableHistoryHandle, G4MultiNavigator, CreateTouchableHistoryHandle, );
   }

   G4ThreeVector GetLocalExitNormal(G4bool *obtained) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4MultiNavigator, GetLocalExitNormal, obtained);
   }

   G4ThreeVector GetLocalExitNormalAndCheck(const G4ThreeVector &E_Pt, G4bool *obtained) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4MultiNavigator, GetLocalExitNormalAndCheck, E_Pt, obtained);
   }

   G4ThreeVector GetGlobalExitNormal(const G4ThreeVector &E_Pt, G4bool *obtained) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4MultiNavigator, GetGlobalExitNormal, E_Pt, obtained);
   }

   void ResetState() override { PYBIND11_OVERRIDE(void, G4MultiNavigator, ResetState, ); }

   void SetupHierarchy() override { PYBIND11_OVERRIDE(void, G4MultiNavigator, SetupHierarchy, ); }
};

void export_G4MultiNavigator(py::module &m)
{
   py::enum_<ELimited>(m, "ELimited")
      .value("kDoNot", kDoNot)
      .value("kUnique", kUnique)
      .value("kSharedTransport", kSharedTransport)
      .value("kSharedOther", kSharedOther)
      .value("kUndefLimited", kUndefLimited)
      .export_values();

   py::class_<G4MultiNavigator, PyG4MultiNavigator, G4Navigator>(m, "G4MultiNavigator")

      .def(py::init<>())
      .def("ComputeSafety", &G4MultiNavigator::ComputeSafety, py::arg("globalpoint"),
           py::arg("pProposedMaxLength") = DBL_MAX, py::arg("keepState") = false)

      .def("ComputeStep", &G4MultiNavigator::ComputeStep, py::arg("pGlobalPoint"), py::arg("pDirection"),
           py::arg("pCurrentProposedStepLength"), py::arg("pNewSafety"))

      .def("CreateTouchableHistoryHandle", &G4MultiNavigator::CreateTouchableHistoryHandle)
      .def("GetGlobalExitNormal", &G4MultiNavigator::GetGlobalExitNormal, py::arg("E_Pt"), py::arg("obtained"))

      .def("GetLocalExitNormal", &G4MultiNavigator::GetLocalExitNormal, py::arg("obtained"))
      .def("GetLocalExitNormalAndCheck", &G4MultiNavigator::GetLocalExitNormalAndCheck, py::arg("E_Pt"),
           py::arg("obtained"))

      .def("GetNavigator", &G4MultiNavigator::GetNavigator, py::arg("n"), py::return_value_policy::reference)
      .def("LocateGlobalPointAndSetup", &G4MultiNavigator::LocateGlobalPointAndSetup, py::arg("point"),
           py::arg("direction") = static_cast<const G4ThreeVector *>(nullptr), py::arg("pRelativeSearch") = true,
           py::arg("ignoreDirection") = true, py::return_value_policy::reference)

      .def("LocateGlobalPointWithinVolume", &G4MultiNavigator::LocateGlobalPointWithinVolume, py::arg("position"))
      .def("ObtainFinalStep", &G4MultiNavigator::ObtainFinalStep, py::arg("navigatorId"), py::arg("pNewSafety"),
           py::arg("minStepLast"), py::arg("limitedStep"))

      .def("PrepareNavigators", &G4MultiNavigator::PrepareNavigators)
      .def("PrepareNewTrack", &G4MultiNavigator::PrepareNewTrack, py::arg("position"), py::arg("direction"))
      .def("ResetHierarchyAndLocate", &G4MultiNavigator::ResetHierarchyAndLocate, py::arg("point"),
           py::arg("direction"), py::arg("h"), py::return_value_policy::reference);
}
