#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Navigator.hh>
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

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4Navigator : public G4Navigator, public py::trampoline_self_life_support {
public:
   using G4Navigator::G4Navigator;

   G4double ComputeStep(const G4ThreeVector &pGlobalPoint, const G4ThreeVector &pDirection,
                        const G4double pCurrentProposedStepLength, G4double &pNewSafety) override
   {
      PYBIND11_OVERRIDE(G4double, G4Navigator, ComputeStep, pGlobalPoint, pDirection, pCurrentProposedStepLength,
                        pNewSafety);
   }

   G4VPhysicalVolume *ResetHierarchyAndLocate(const G4ThreeVector &point, const G4ThreeVector &direction,
                                              const G4TouchableHistory &h) override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4Navigator, ResetHierarchyAndLocate, point, direction, h);
   }

   G4VPhysicalVolume *LocateGlobalPointAndSetup(const G4ThreeVector &point, const G4ThreeVector *direction,
                                                const G4bool pRelativeSearch, const G4bool ignoreDirection) override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4Navigator, LocateGlobalPointAndSetup, point, direction, pRelativeSearch,
                        ignoreDirection);
   }

   void LocateGlobalPointWithinVolume(const G4ThreeVector &position) override
   {
      PYBIND11_OVERRIDE(void, G4Navigator, LocateGlobalPointWithinVolume, position);
   }

   G4double ComputeSafety(const G4ThreeVector &globalpoint, const G4double pProposedMaxLength,
                          const G4bool keepState) override
   {
      PYBIND11_OVERRIDE(G4double, G4Navigator, ComputeSafety, globalpoint, pProposedMaxLength, keepState);
   }

   G4TouchableHistoryHandle CreateTouchableHistoryHandle() const override
   {
      PYBIND11_OVERRIDE(G4TouchableHistoryHandle, G4Navigator, CreateTouchableHistoryHandle, );
   }

   G4ThreeVector GetLocalExitNormal(G4bool *valid) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Navigator, GetLocalExitNormal, valid);
   }

   G4ThreeVector GetLocalExitNormalAndCheck(const G4ThreeVector &point, G4bool *valid) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Navigator, GetLocalExitNormalAndCheck, point, valid);
   }

   G4ThreeVector GetGlobalExitNormal(const G4ThreeVector &point, G4bool *valid) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Navigator, GetGlobalExitNormal, point, valid);
   }

   void ResetState() override { PYBIND11_OVERRIDE(void, G4Navigator, ResetState, ); }

   void SetupHierarchy() override { PYBIND11_OVERRIDE(void, G4Navigator, SetupHierarchy, ); }
};

void export_G4Navigator(py::module &m)
{
   py::class_<G4Navigator, PyG4Navigator>(m, "G4Navigator")

      .def(py::init<>())
      .def("ComputeStep", &G4Navigator::ComputeStep, py::arg("pGlobalPoint"), py::arg("pDirection"),
           py::arg("pCurrentProposedStepLength"), py::arg("pNewSafety"))

      .def("CheckNextStep", &G4Navigator::CheckNextStep, py::arg("pGlobalPoint"), py::arg("pDirection"),
           py::arg("pCurrentProposedStepLength"), py::arg("pNewSafety"))

      .def("ResetHierarchyAndLocate", &G4Navigator::ResetHierarchyAndLocate, py::arg("point"), py::arg("direction"),
           py::arg("h"), py::return_value_policy::reference)

      .def("LocateGlobalPointAndSetup", &G4Navigator::LocateGlobalPointAndSetup, py::arg("point"),
           py::arg("direction") = static_cast<const G4ThreeVector *>(nullptr), py::arg("pRelativeSearch") = true,
           py::arg("ignoreDirection") = true, py::return_value_policy::reference)

      .def("LocateGlobalPointWithinVolume", &G4Navigator::LocateGlobalPointWithinVolume, py::arg("position"))
      .def("LocateGlobalPointAndUpdateTouchableHandle", &G4Navigator::LocateGlobalPointAndUpdateTouchableHandle,
           py::arg("position"), py::arg("direction"), py::arg("oldTouchableToUpdate"), py::arg("RelativeSearch") = true)

      .def("LocateGlobalPointAndUpdateTouchable",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, G4VTouchable *, const G4bool>(
              &G4Navigator::LocateGlobalPointAndUpdateTouchable),
           py::arg("position"), py::arg("direction"), py::arg("touchableToUpdate"), py::arg("RelativeSearch") = true)

      .def("LocateGlobalPointAndUpdateTouchable",
           py::overload_cast<const G4ThreeVector &, G4VTouchable *, const G4bool>(
              &G4Navigator::LocateGlobalPointAndUpdateTouchable),
           py::arg("position"), py::arg("touchableToUpdate"), py::arg("RelativeSearch") = true)

      .def("SetGeometricallyLimitedStep", &G4Navigator::SetGeometricallyLimitedStep)
      .def("ComputeSafety", &G4Navigator::ComputeSafety, py::arg("globalpoint"),
           py::arg("pProposedMaxLength") = DBL_MAX, py::arg("keepState") = true)

      .def("GetWorldVolume", &G4Navigator::GetWorldVolume, py::return_value_policy::reference)
      .def("SetWorldVolume", &G4Navigator::SetWorldVolume, py::arg("pWorld"))
      .def("CreateGRSVolume", &G4Navigator::CreateGRSVolume, py::return_value_policy::reference)
      .def("CreateGRSSolid", &G4Navigator::CreateGRSSolid, py::return_value_policy::reference)
      .def("CreateTouchableHistory", py::overload_cast<>(&G4Navigator::CreateTouchableHistory, py::const_),
           py::return_value_policy::reference)

      .def("CreateTouchableHistory",
           py::overload_cast<const G4NavigationHistory *>(&G4Navigator::CreateTouchableHistory, py::const_),
           py::return_value_policy::reference)

      .def("CreateTouchableHistoryHandle", &G4Navigator::CreateTouchableHistoryHandle)
      .def("GetLocalExitNormal", &G4Navigator::GetLocalExitNormal, py::arg("valid"))
      .def("GetLocalExitNormalAndCheck", &G4Navigator::GetLocalExitNormalAndCheck, py::arg("point"), py::arg("valid"))
      .def("GetGlobalExitNormal", &G4Navigator::GetGlobalExitNormal, py::arg("point"), py::arg("valid"))
      .def("GetVerboseLevel", &G4Navigator::GetVerboseLevel)
      .def("SetVerboseLevel", &G4Navigator::SetVerboseLevel, py::arg("level"))
      .def("IsActive", &G4Navigator::IsActive)
      .def("Activate", &G4Navigator::Activate, py::arg("flag"))
      .def("EnteredDaughterVolume", &G4Navigator::EnteredDaughterVolume)
      .def("ExitedMotherVolume", &G4Navigator::ExitedMotherVolume)
      .def("CheckMode", &G4Navigator::CheckMode, py::arg("mode"))
      .def("IsCheckModeActive", &G4Navigator::IsCheckModeActive)
      .def("SetPushVerbosity", &G4Navigator::SetPushVerbosity, py::arg("mode"))
      .def("PrintState", &G4Navigator::PrintState)
      .def("GetGlobalToLocalTransform", &G4Navigator::GetGlobalToLocalTransform)
      .def("GetLocalToGlobalTransform", &G4Navigator::GetLocalToGlobalTransform)
      .def("GetMotherToDaughterTransform", &G4Navigator::GetMotherToDaughterTransform, py::arg("dVolume"),
           py::arg("dReplicaNo"), py::arg("dVolumeType"))

      .def("ResetStackAndState", &G4Navigator::ResetStackAndState)
      .def("SeverityOfZeroStepping", &G4Navigator::SeverityOfZeroStepping, py::arg("noZeroSteps"))
      .def("GetCurrentLocalCoordinate", &G4Navigator::GetCurrentLocalCoordinate)
      .def("NetTranslation", &G4Navigator::NetTranslation)
      .def("NetRotation", &G4Navigator::NetRotation)
      .def("EnableBestSafety", &G4Navigator::EnableBestSafety, py::arg("value") = false)
      .def("GetExternalNavigation", &G4Navigator::GetExternalNavigation, py::return_value_policy::reference)
      .def("SetExternalNavigation", &G4Navigator::SetExternalNavigation, py::arg("externalNav"))
      .def("Clone", &G4Navigator::Clone, py::return_value_policy::reference)
      .def(
         "__str__",
         [](const G4Navigator &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
