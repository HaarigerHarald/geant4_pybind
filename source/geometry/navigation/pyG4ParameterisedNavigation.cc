#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParameterisedNavigation.hh>
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
#include <G4VoxelLimits.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4VoxelSafety.hh>
#include <G4VTouchable.hh>
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

class PyG4ParameterisedNavigation : public G4ParameterisedNavigation, public py::trampoline_self_life_support {
public:
   using G4ParameterisedNavigation::G4ParameterisedNavigation;

   G4bool LevelLocate(G4NavigationHistory &history, const G4VPhysicalVolume *blockedVol, const G4int blockedNum,
                      const G4ThreeVector &globalPoint, const G4ThreeVector *globalDirection,
                      const G4bool pLocatedOnEdge, G4ThreeVector &localPoint) override
   {
      PYBIND11_OVERRIDE_IMPL(G4bool, G4ParameterisedNavigation, "LevelLocate", std::addressof(history), blockedVol,
                             blockedNum, globalPoint, globalDirection, pLocatedOnEdge, std::addressof(localPoint));

      return G4ParameterisedNavigation::LevelLocate(history, blockedVol, blockedNum, globalPoint, globalDirection,
                                                    pLocatedOnEdge, localPoint);
   }

   //    G4double ComputeStep(const G4ThreeVector &globalPoint, const G4ThreeVector &globalDirection,
   //                         const G4double currentProposedStepLength, G4double &newSafety, G4NavigationHistory
   //                         &history, G4bool &validExitNormal, G4ThreeVector &exitNormal, G4bool &exiting, G4bool
   //                         &entering, G4VPhysicalVolume **pBlockedPhysical, G4int &blockedReplicaNo) override
   //    {
   //       PYBIND11_OVERRIDE(G4double, G4ParameterisedNavigation, ComputeStep, globalPoint, globalDirection,
   //                         currentProposedStepLength, newSafety, history, validExitNormal, exitNormal, exiting,
   //                         entering, pBlockedPhysical, blockedReplicaNo);
   //    }

   G4double ComputeSafety(const G4ThreeVector &localPoint, const G4NavigationHistory &history,
                          const G4double pProposedMaxLength) override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisedNavigation, ComputeSafety, localPoint, history, pProposedMaxLength);
   }
};

void export_G4ParameterisedNavigation(py::module &m)
{
   py::class_<G4ParameterisedNavigation, PyG4ParameterisedNavigation, G4VoxelNavigation>(m, "G4ParameterisedNavigation")

      .def(py::init<>())
      .def("__copy__", [](const PyG4ParameterisedNavigation &self) { return PyG4ParameterisedNavigation(self); })
      .def("__deepcopy__",
           [](const PyG4ParameterisedNavigation &self, py::dict) { return PyG4ParameterisedNavigation(self); })

      .def("ParamVoxelLocate", &G4ParameterisedNavigation::ParamVoxelLocate, py::arg("pHead"), py::arg("localPoint"),
           py::return_value_policy::reference)

      .def("LevelLocate", &G4ParameterisedNavigation::LevelLocate, py::arg("history"), py::arg("blockedVol"),
           py::arg("blockedNum"), py::arg("globalPoint"), py::arg("globalDirection"), py::arg("pLocatedOnEdge"),
           py::arg("localPoint"))

      //  .def("ComputeStep", &G4ParameterisedNavigation::ComputeStep, py::arg("globalPoint"),
      //  py::arg("globalDirection"),
      //       py::arg("currentProposedStepLength"), py::arg("newSafety"), py::arg("history"),
      //       py::arg("validExitNormal"), py::arg("exitNormal"), py::arg("exiting"), py::arg("entering"),
      //       py::arg("pBlockedPhysical"), py::arg("blockedReplicaNo"))

      .def("ComputeSafety", &G4ParameterisedNavigation::ComputeSafety, py::arg("localPoint"), py::arg("history"),
           py::arg("pProposedMaxLength") = DBL_MAX);
}
