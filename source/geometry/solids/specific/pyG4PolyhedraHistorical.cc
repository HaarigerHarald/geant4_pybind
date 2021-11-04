#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PolyhedraHistorical.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4PolyhedraHistorical(py::module &m)
{
   py::class_<G4PolyhedraHistorical>(m, "G4PolyhedraHistorical")

      .def(py::init<>())
      .def(py::init<G4int>(), py::arg("z_planes"))
      .def("__copy__", [](const G4PolyhedraHistorical &self) { return G4PolyhedraHistorical(self); })
      .def("__deepcopy__", [](const G4PolyhedraHistorical &self, py::dict) { return G4PolyhedraHistorical(self); })
      .def_readwrite("Start_angle", &G4PolyhedraHistorical::Start_angle)
      .def_readwrite("Opening_angle", &G4PolyhedraHistorical::Opening_angle)
      .def_readwrite("numSide", &G4PolyhedraHistorical::numSide)
      .def_readwrite("Num_z_planes", &G4PolyhedraHistorical::Num_z_planes)
      .def_readwrite("Z_values", &G4PolyhedraHistorical::Z_values)
      .def_readwrite("Rmin", &G4PolyhedraHistorical::Rmin)
      .def_readwrite("Rmax", &G4PolyhedraHistorical::Rmax);
}
