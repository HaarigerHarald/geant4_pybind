#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VoxelSafety.hh>
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
#include <G4SmartVoxelNode.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VoxelSafety(py::module &m)
{
   py::class_<G4VoxelSafety>(m, "G4VoxelSafety")

      .def(py::init<>())
      .def("__copy__", [](const G4VoxelSafety &self) { return G4VoxelSafety(self); })
      .def("__deepcopy__", [](const G4VoxelSafety &self, py::dict) { return G4VoxelSafety(self); })
      //  .def("VoxelLocate", &G4VoxelSafety::VoxelLocate, py::arg("pHead"), py::arg("localPoint"),
      //       py::return_value_policy::reference)

      .def("ComputeSafety", &G4VoxelSafety::ComputeSafety, py::arg("localPoint"), py::arg("currentPhysical"),
           py::arg("maxLength") = DBL_MAX)

      .def("GetVerboseLevel", &G4VoxelSafety::GetVerboseLevel)
      .def("SetVerboseLevel", &G4VoxelSafety::SetVerboseLevel, py::arg("level"));
}
