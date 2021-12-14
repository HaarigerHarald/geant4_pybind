#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SafetyHelper.hh>
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
#include <G4PathFinder.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SafetyHelper(py::module &m)
{
   py::class_<G4SafetyHelper>(m, "G4SafetyHelper")

      .def(py::init<>())
      .def("__copy__", [](const G4SafetyHelper &self) { return G4SafetyHelper(self); })
      .def("__deepcopy__", [](const G4SafetyHelper &self, py::dict) { return G4SafetyHelper(self); })
      .def("CheckNextStep", &G4SafetyHelper::CheckNextStep, py::arg("position"), py::arg("direction"),
           py::arg("currentMaxStep"), py::arg("newSafety"))

      .def("ComputeSafety", &G4SafetyHelper::ComputeSafety, py::arg("pGlobalPoint"), py::arg("maxRadius") = DBL_MAX)
      .def("Locate", &G4SafetyHelper::Locate, py::arg("pGlobalPoint"), py::arg("direction"))
      .def("ReLocateWithinVolume", &G4SafetyHelper::ReLocateWithinVolume, py::arg("pGlobalPoint"))
      .def("EnableParallelNavigation", &G4SafetyHelper::EnableParallelNavigation, py::arg("parallel"))
      .def("InitialiseNavigator", &G4SafetyHelper::InitialiseNavigator)
      .def("SetVerboseLevel", &G4SafetyHelper::SetVerboseLevel, py::arg("lev"))
      .def("GetWorldVolume", &G4SafetyHelper::GetWorldVolume, py::return_value_policy::reference)
      .def("SetCurrentSafety", &G4SafetyHelper::SetCurrentSafety, py::arg("val"), py::arg("pos"))
      .def("InitialiseHelper", &G4SafetyHelper::InitialiseHelper);
}
