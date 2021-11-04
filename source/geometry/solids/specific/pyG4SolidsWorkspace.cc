#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SolidsWorkspace.hh>
#include <G4TWorkspacePool.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4SolidExtentList.hh>
#include <G4IntersectingCone.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SolidsWorkspace(py::module &m)
{
   py::class_<G4SolidsWorkspace>(m, "G4SolidsWorkspace")

      .def(py::init<G4bool>(), py::arg("verbose") = false)
      .def("__copy__", [](const G4SolidsWorkspace &self) { return G4SolidsWorkspace(self); })
      .def("__deepcopy__", [](const G4SolidsWorkspace &self, py::dict) { return G4SolidsWorkspace(self); })
      .def("UseWorkspace", &G4SolidsWorkspace::UseWorkspace)
      .def("ReleaseWorkspace", &G4SolidsWorkspace::ReleaseWorkspace)
      .def("DestroyWorkspace", &G4SolidsWorkspace::DestroyWorkspace)
      .def("InitialiseWorkspace", &G4SolidsWorkspace::InitialiseWorkspace)
      .def("SetVerbose", &G4SolidsWorkspace::SetVerbose, py::arg("v"))
      .def("GetVerbose", &G4SolidsWorkspace::GetVerbose)
      .def_static("GetPool", &G4SolidsWorkspace::GetPool, py::return_value_policy::reference);
}
