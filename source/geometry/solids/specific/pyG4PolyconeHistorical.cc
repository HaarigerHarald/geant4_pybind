#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PolyconeHistorical.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4PolyconeHistorical(py::module &m)
{
   py::class_<G4PolyconeHistorical>(m, "G4PolyconeHistorical")

      .def(py::init<>())
      .def(py::init<G4int>(), py::arg("z_planes"))
      .def("__copy__", [](const G4PolyconeHistorical &self) { return G4PolyconeHistorical(self); })
      .def("__deepcopy__", [](const G4PolyconeHistorical &self, py::dict) { return G4PolyconeHistorical(self); })
      .def_readwrite("Start_angle", &G4PolyconeHistorical::Start_angle)
      .def_readwrite("Opening_angle", &G4PolyconeHistorical::Opening_angle)
      .def_readwrite("Num_z_planes", &G4PolyconeHistorical::Num_z_planes)
      .def_readwrite("Z_values", &G4PolyconeHistorical::Z_values)
      .def_readwrite("Rmin", &G4PolyconeHistorical::Rmin)
      .def_readwrite("Rmax", &G4PolyconeHistorical::Rmax);
}
