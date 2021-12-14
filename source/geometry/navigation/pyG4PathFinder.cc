#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PathFinder.hh>
#include <G4TransportationManager.hh>
#include <G4Allocator.hh>
#include <G4ReferenceCountedHandle.hh>
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
#include <G4PropagatorInField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4PathFinder(py::module &m)
{
   py::class_<G4PathFinder, py::nodelete>(m, "G4PathFinder")

      .def("__copy__", [](const G4PathFinder &self) { return G4PathFinder(self); })
      .def("__deepcopy__", [](const G4PathFinder &self, py::dict) { return G4PathFinder(self); })
      .def_static("GetInstance", &G4PathFinder::GetInstance, py::return_value_policy::reference)
      .def_static("GetInstanceIfExist", &G4PathFinder::GetInstanceIfExist, py::return_value_policy::reference)
      .def("ComputeStep", &G4PathFinder::ComputeStep, py::arg("pFieldTrack"), py::arg("pCurrentProposedStepLength"),
           py::arg("navigatorId"), py::arg("stepNo"), py::arg("pNewSafety"), py::arg("limitedStep"),
           py::arg("EndState"), py::arg("currentVolume"))

      .def("Locate", &G4PathFinder::Locate, py::arg("position"), py::arg("direction"), py::arg("relativeSearch") = true)
      .def("ReLocate", &G4PathFinder::ReLocate, py::arg("position"))
      .def("PrepareNewTrack", &G4PathFinder::PrepareNewTrack, py::arg("position"), py::arg("direction"),
           py::arg("massStartVol") = static_cast<G4VPhysicalVolume *>(nullptr))

      .def("EndTrack", &G4PathFinder::EndTrack)
      .def("CreateTouchableHandle", &G4PathFinder::CreateTouchableHandle, py::arg("navId"))
      .def("GetLocatedVolume", &G4PathFinder::GetLocatedVolume, py::arg("navId"), py::return_value_policy::reference)
      //.def("IsParticleLooping", &G4PathFinder::IsParticleLooping)
      .def("GetCurrentSafety", &G4PathFinder::GetCurrentSafety)
      .def("GetMinimumStep", &G4PathFinder::GetMinimumStep)
      .def("GetNumberGeometriesLimitingStep", &G4PathFinder::GetNumberGeometriesLimitingStep)
      .def("ComputeSafety", &G4PathFinder::ComputeSafety, py::arg("globalPoint"))
      .def("ObtainSafety", &G4PathFinder::ObtainSafety, py::arg("navId"), py::arg("globalCenterPoint"))
      .def("EnableParallelNavigation", &G4PathFinder::EnableParallelNavigation, py::arg("enableChoice") = true)
      .def("SetVerboseLevel", &G4PathFinder::SetVerboseLevel, py::arg("lev") = -1)
      //.def("GetMaxLoopCount", &G4PathFinder::GetMaxLoopCount)
      //.def("SetMaxLoopCount", &G4PathFinder::SetMaxLoopCount, py::arg("new_max"))
      .def("MovePoint", &G4PathFinder::MovePoint)
      .def("LastPreSafety", &G4PathFinder::LastPreSafety, py::arg("navId"), py::arg("globalCenterPoint"),
           py::arg("minSafety"))

      .def("PushPostSafetyToPreSafety", &G4PathFinder::PushPostSafetyToPreSafety)
      .def("LimitedString", &G4PathFinder::LimitedString, py::arg("lim"));
}
