#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VoxelNavigation.hh>
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
#include <G4VisAttributes.hh>
#include <G4VoxelLimits.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4VoxelSafety.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VoxelNavigation : public G4VoxelNavigation, public py::trampoline_self_life_support {
public:
   using G4VoxelNavigation::G4VoxelNavigation;

   G4bool LevelLocate(G4NavigationHistory &history, const G4VPhysicalVolume *blockedVol, const G4int blockedNum,
                      const G4ThreeVector &globalPoint, const G4ThreeVector *globalDirection,
                      const G4bool pLocatedOnEdge, G4ThreeVector &localPoint) override
   {
      PYBIND11_OVERRIDE_IMPL(G4bool, G4VoxelNavigation, "LevelLocate", std::addressof(history), blockedVol, blockedNum,
                             globalPoint, globalDirection, pLocatedOnEdge, std::addressof(localPoint));

      return G4VoxelNavigation::LevelLocate(history, blockedVol, blockedNum, globalPoint, globalDirection,
                                            pLocatedOnEdge, localPoint);
   }

   // G4double ComputeStep(const G4ThreeVector &globalPoint, const G4ThreeVector &globalDirection,
   //                      const G4double currentProposedStepLength, G4double &newSafety, G4NavigationHistory &history,
   //                      G4bool &validExitNormal, G4ThreeVector &exitNormal, G4bool &exiting, G4bool &entering,
   //                      G4VPhysicalVolume **pBlockedPhysical, G4int &blockedReplicaNo) override
   // {
   //    PYBIND11_OVERRIDE(G4double, G4VoxelNavigation, ComputeStep, globalPoint, globalDirection,
   //                      currentProposedStepLength, newSafety, history, validExitNormal, exitNormal, exiting,
   //                      entering, pBlockedPhysical, blockedReplicaNo);
   // }

   G4double ComputeSafety(const G4ThreeVector &globalpoint, const G4NavigationHistory &history,
                          const G4double pMaxLength) override
   {
      PYBIND11_OVERRIDE(G4double, G4VoxelNavigation, ComputeSafety, globalpoint, history, pMaxLength);
   }
};

void export_G4VoxelNavigation(py::module &m)
{
   py::class_<G4VoxelNavigation, PyG4VoxelNavigation>(m, "G4VoxelNavigation")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VoxelNavigation &self) { return PyG4VoxelNavigation(self); })
      .def("__deepcopy__", [](const PyG4VoxelNavigation &self, py::dict) { return PyG4VoxelNavigation(self); })
      .def("VoxelLocate", &G4VoxelNavigation::VoxelLocate, py::arg("pHead"), py::arg("localPoint"),
           py::return_value_policy::reference)

      .def("LevelLocate", &G4VoxelNavigation::LevelLocate, py::arg("history"), py::arg("blockedVol"),
           py::arg("blockedNum"), py::arg("globalPoint"), py::arg("globalDirection"), py::arg("pLocatedOnEdge"),
           py::arg("localPoint"))

      // .def("ComputeStep", &G4VoxelNavigation::ComputeStep, py::arg("globalPoint"), py::arg("globalDirection"),
      //      py::arg("currentProposedStepLength"), py::arg("newSafety"), py::arg("history"),
      //      py::arg("validExitNormal"), py::arg("exitNormal"), py::arg("exiting"), py::arg("entering"),
      //      py::arg("pBlockedPhysical"), py::arg("blockedReplicaNo"))

      .def("ComputeSafety", &G4VoxelNavigation::ComputeSafety, py::arg("globalpoint"), py::arg("history"),
           py::arg("pMaxLength") = DBL_MAX)

      .def("GetVerboseLevel", &G4VoxelNavigation::GetVerboseLevel)
      .def("SetVerboseLevel", &G4VoxelNavigation::SetVerboseLevel, py::arg("level"))
      .def("CheckMode", &G4VoxelNavigation::CheckMode, py::arg("mode"))
      .def("EnableBestSafety", &G4VoxelNavigation::EnableBestSafety, py::arg("flag") = false);
}
