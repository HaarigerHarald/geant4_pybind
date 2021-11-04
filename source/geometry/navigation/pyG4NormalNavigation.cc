#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NormalNavigation.hh>
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
#include <G4NavigationLogger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4NormalNavigation(py::module &m)
{
   py::class_<G4NormalNavigation>(m, "G4NormalNavigation")

      .def(py::init<>())
      .def("__copy__", [](const G4NormalNavigation &self) { return G4NormalNavigation(self); })
      .def("__deepcopy__", [](const G4NormalNavigation &self, py::dict) { return G4NormalNavigation(self); })
      .def("LevelLocate", &G4NormalNavigation::LevelLocate, py::arg("history"), py::arg("blockedVol"),
           py::arg("blockedNum"), py::arg("globalPoint"), py::arg("globalDirection"), py::arg("pLocatedOnEdge"),
           py::arg("localPoint"))

      //  .def("ComputeStep", &G4NormalNavigation::ComputeStep, py::arg("localPoint"), py::arg("localDirection"),
      //       py::arg("currentProposedStepLength"), py::arg("newSafety"), py::arg("history"),
      //       py::arg("validExitNormal"), py::arg("exitNormal"), py::arg("exiting"), py::arg("entering"),
      //       py::arg("pBlockedPhysical"), py::arg("blockedReplicaNo"))

      .def("ComputeSafety", &G4NormalNavigation::ComputeSafety, py::arg("globalpoint"), py::arg("history"),
           py::arg("pMaxLength") = DBL_MAX)

      .def("GetVerboseLevel", &G4NormalNavigation::GetVerboseLevel)
      .def("SetVerboseLevel", &G4NormalNavigation::SetVerboseLevel, py::arg("level"))
      .def("CheckMode", &G4NormalNavigation::CheckMode, py::arg("mode"));
}
