#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VExternalNavigation.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4VPVParameterisation.hh>
#include <G4ProductionCuts.hh>
#include <G4Material.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VSensitiveDetector.hh>
#include <G4SmartVoxelHeader.hh>
#include <G4VisAttributes.hh>
#include <G4VoxelLimits.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VExternalNavigation : public G4VExternalNavigation, public py::trampoline_self_life_support {
public:
   using G4VExternalNavigation::G4VExternalNavigation;

   G4bool LevelLocate(G4NavigationHistory &history, const G4VPhysicalVolume *blockedVol, const G4int blockedNum,
                      const G4ThreeVector &globalPoint, const G4ThreeVector *globalDirection,
                      const G4bool pLocatedOnEdge, G4ThreeVector &localPoint) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VExternalNavigation, LevelLocate, std::addressof(history), blockedVol,
                             blockedNum, globalPoint, globalDirection, pLocatedOnEdge, std::addressof(localPoint));
   }

   G4double ComputeStep(const G4ThreeVector &localPoint, const G4ThreeVector &localDirection,
                        const G4double currentProposedStepLength, G4double &newSafety, G4NavigationHistory &history,
                        G4bool &validExitNormal, G4ThreeVector &exitNormal, G4bool &exiting, G4bool &entering,
                        G4VPhysicalVolume **pBlockedPhysical, G4int &blockedReplicaNo) override
   {
      // PYBIND11_OVERRIDE_PURE(G4double, G4VExternalNavigation, ComputeStep, localPoint, localDirection,
      //                        currentProposedStepLength, newSafety, history, validExitNormal, exitNormal, exiting,
      //                        entering, pBlockedPhysical, blockedReplicaNo);
   }

   G4double ComputeSafety(const G4ThreeVector &globalpoint, const G4NavigationHistory &history,
                          const G4double pMaxLength) override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VExternalNavigation, ComputeSafety, globalpoint, history, pMaxLength);
   }

   G4VExternalNavigation *Clone() override
   {
      PYBIND11_OVERRIDE_PURE(G4VExternalNavigation *, G4VExternalNavigation, Clone, );
   }

   EInside Inside(const G4VSolid *solid, const G4ThreeVector &position, const G4ThreeVector &direction) override
   {
      PYBIND11_OVERRIDE(EInside, G4VExternalNavigation, Inside, solid, position, direction);
   }

   void RelocateWithinVolume(G4VPhysicalVolume *motherPhysical, const G4ThreeVector &localPoint) override
   {
      PYBIND11_OVERRIDE(void, G4VExternalNavigation, RelocateWithinVolume, motherPhysical, localPoint);
   }
};

void export_G4VExternalNavigation(py::module &m)
{
   py::class_<G4VExternalNavigation, PyG4VExternalNavigation>(m, "G4VExternalNavigation")

      //.def(py::init<>())
      //.def("__copy__", [](const PyG4VExternalNavigation &self) { return PyG4VExternalNavigation(self); })
      //.def("__deepcopy__", [](const PyG4VExternalNavigation &self, py::dict) { return PyG4VExternalNavigation(self);
      //})
      .def("LevelLocate", &G4VExternalNavigation::LevelLocate, py::arg("history"), py::arg("blockedVol"),
           py::arg("blockedNum"), py::arg("globalPoint"), py::arg("globalDirection"), py::arg("pLocatedOnEdge"),
           py::arg("localPoint"))

      // .def("ComputeStep", &G4VExternalNavigation::ComputeStep, py::arg("localPoint"), py::arg("localDirection"),
      //      py::arg("currentProposedStepLength"), py::arg("newSafety"), py::arg("history"),
      //      py::arg("validExitNormal"), py::arg("exitNormal"), py::arg("exiting"), py::arg("entering"),
      //      py::arg("pBlockedPhysical"), py::arg("blockedReplicaNo"))

      .def("ComputeSafety", &G4VExternalNavigation::ComputeSafety, py::arg("globalpoint"), py::arg("history"),
           py::arg("pMaxLength") = DBL_MAX)

      .def("Clone", &G4VExternalNavigation::Clone, py::return_value_policy::reference)
      .def("Inside", &G4VExternalNavigation::Inside, py::arg("solid"), py::arg("position"), py::arg("direction"))

      .def("RelocateWithinVolume", &G4VExternalNavigation::RelocateWithinVolume, py::arg("motherPhysical"),
           py::arg("localPoint"))

      .def("GetVerboseLevel", &G4VExternalNavigation::GetVerboseLevel)
      .def("SetVerboseLevel", &G4VExternalNavigation::SetVerboseLevel, py::arg("level"))
      .def("CheckMode", &G4VExternalNavigation::CheckMode, py::arg("mode"));
}
