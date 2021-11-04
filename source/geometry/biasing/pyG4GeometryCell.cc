#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GeometryCell.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GeometryCell(py::module &m)
{
   py::class_<G4GeometryCell>(m, "G4GeometryCell")

      .def(py::init<const G4VPhysicalVolume &, G4int>(), py::arg("aVolume"), py::arg("RepNum"))
      .def("__copy__", [](const G4GeometryCell &self) { return G4GeometryCell(self); })
      .def("__deepcopy__", [](const G4GeometryCell &self, py::dict) { return G4GeometryCell(self); })
      .def("GetPhysicalVolume", &G4GeometryCell::GetPhysicalVolume)
      .def("GetReplicaNumber", &G4GeometryCell::GetReplicaNumber);
}
