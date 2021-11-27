#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GeometryWorkspace.hh>
#include <G4TWorkspacePool.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4Material.hh>
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
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4ProductionCuts.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VSensitiveDetector.hh>
#include <G4SmartVoxelHeader.hh>
#include <G4VisAttributes.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GeometryWorkspace(py::module &m)
{
   py::class_<G4GeometryWorkspace>(m, "G4GeometryWorkspace")

      .def(py::init<>())
      .def("__copy__", [](const G4GeometryWorkspace &self) { return G4GeometryWorkspace(self); })
      .def("__deepcopy__", [](const G4GeometryWorkspace &self, py::dict) { return G4GeometryWorkspace(self); })
      .def("UseWorkspace", &G4GeometryWorkspace::UseWorkspace)
      .def("ReleaseWorkspace", &G4GeometryWorkspace::ReleaseWorkspace)
      .def("DestroyWorkspace", &G4GeometryWorkspace::DestroyWorkspace)
      .def("InitialiseWorkspace", &G4GeometryWorkspace::InitialiseWorkspace)
      .def_static("GetPool", &G4GeometryWorkspace::GetPool, py::return_value_policy::reference);
}
