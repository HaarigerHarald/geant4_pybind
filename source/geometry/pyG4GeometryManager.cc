#include <pybind11/pybind11.h>

#include <G4GeometryManager.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"

namespace py = pybind11;

void export_G4GeometryManager(py::module &m)
{
   py::class_<G4GeometryManager, std::unique_ptr<G4GeometryManager, py::nodelete>>(m, "G4GeometryManager",
                                                                                   "geometry manager")

      .def_static("GetInstance", &G4GeometryManager::GetInstance, py::return_value_policy::reference)

      .def("CloseGeometry", &G4GeometryManager::CloseGeometry, py::arg("pOptimise") = true, py::arg("verbose") = false,
           py::arg("vol") = static_cast<G4VPhysicalVolume *>(nullptr))

      .def("OpenGeometry", &G4GeometryManager::OpenGeometry, py::arg("vol") = static_cast<G4VPhysicalVolume *>(nullptr))
      .def("IsGeometryClosed", &G4GeometryManager::IsGeometryClosed)
      .def("SetWorldMaximumExtent", &G4GeometryManager::SetWorldMaximumExtent);
}
