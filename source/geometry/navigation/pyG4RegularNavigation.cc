#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RegularNavigation.hh>
#include <G4NormalNavigation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4Navigator.hh>
#include <G4NavigationHistory.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4RegularNavigation(py::module &m)
{
   py::class_<G4RegularNavigation>(m, "G4RegularNavigation")

      .def(py::init<>())
      .def("__copy__", [](const G4RegularNavigation &self) { return G4RegularNavigation(self); })
      .def("__deepcopy__", [](const G4RegularNavigation &self, py::dict) { return G4RegularNavigation(self); })

      .def("LevelLocate", &G4RegularNavigation::LevelLocate, py::arg("history"), py::arg("blockedVol"),
           py::arg("blockedNum"), py::arg("globalPoint"), py::arg("globalDirection"), py::arg("pLocatedOnEdge"),
           py::arg("localPoint"))

      //  .def("ComputeStep", &G4RegularNavigation::ComputeStep, py::arg("globalPoint"), py::arg("globalDirection"),
      //       py::arg("currentProposedStepLength"), py::arg("newSafety"), py::arg("history"),
      //       py::arg("validExitNormal"), py::arg("exitNormal"), py::arg("exiting"), py::arg("entering"),
      //       py::arg("pBlockedPhysical"), py::arg("blockedReplicaNo"))

      //  .def("ComputeStepSkippingEqualMaterials", &G4RegularNavigation::ComputeStepSkippingEqualMaterials,
      //       py::arg("localPoint"), py::arg("globalDirection"), py::arg("currentProposedStepLength"),
      //       py::arg("newSafety"), py::arg("history"), py::arg("validExitNormal"), py::arg("exitNormal"),
      //       py::arg("exiting"), py::arg("entering"), py::arg("pBlockedPhysical"), py::arg("blockedReplicaNo"),
      //       py::arg("pCurrentPhysical"))

      .def("ComputeSafety", &G4RegularNavigation::ComputeSafety, py::arg("localPoint"), py::arg("history"),
           py::arg("pProposedMaxLength") = DBL_MAX)

      .def("SetVerboseLevel", &G4RegularNavigation::SetVerboseLevel, py::arg("level"))
      .def("CheckMode", &G4RegularNavigation::CheckMode, py::arg("mode"))
      .def("SetNormalNavigation", &G4RegularNavigation::SetNormalNavigation, py::arg("fnormnav"));
}
