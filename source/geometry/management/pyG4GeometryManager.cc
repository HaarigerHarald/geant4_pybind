#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GeometryManager.hh>
#include <G4LogicalVolume.hh>
#include <G4SmartVoxelHeader.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GeometryManager(py::module &m)
{
   py::class_<G4GeometryManager, py::nodelete>(m, "G4GeometryManager")

      .def("__copy__", [](const G4GeometryManager &self) { return G4GeometryManager(self); })
      .def("__deepcopy__", [](const G4GeometryManager &self, py::dict) { return G4GeometryManager(self); })
      .def("CloseGeometry", &G4GeometryManager::CloseGeometry, py::arg("pOptimise") = true, py::arg("verbose") = false,
           py::arg("vol") = static_cast<G4VPhysicalVolume *>(nullptr))

      .def("OpenGeometry", &G4GeometryManager::OpenGeometry, py::arg("vol") = static_cast<G4VPhysicalVolume *>(nullptr))
      .def_static("IsGeometryClosed", &G4GeometryManager::IsGeometryClosed)
      .def("SetWorldMaximumExtent", &G4GeometryManager::SetWorldMaximumExtent, py::arg("worldExtent"))
      .def_static("GetInstance", &G4GeometryManager::GetInstance, py::return_value_policy::reference)
      .def_static("GetInstanceIfExist", &G4GeometryManager::GetInstanceIfExist, py::return_value_policy::reference);
}
