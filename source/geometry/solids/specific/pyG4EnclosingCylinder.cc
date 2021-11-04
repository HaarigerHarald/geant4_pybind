#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EnclosingCylinder.hh>
#include <G4ReduciblePolygon.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4EnclosingCylinder(py::module &m)
{
   py::class_<G4EnclosingCylinder>(m, "G4EnclosingCylinder")

      .def(py::init<const G4ReduciblePolygon *, G4bool, G4double, G4double>(), py::arg("rz"), py::arg("phiIsOpen"),
           py::arg("startPhi"), py::arg("totalPhi"))

      .def("__copy__", [](const G4EnclosingCylinder &self) { return G4EnclosingCylinder(self); })
      .def("__deepcopy__", [](const G4EnclosingCylinder &self, py::dict) { return G4EnclosingCylinder(self); })
      .def("MustBeOutside", &G4EnclosingCylinder::MustBeOutside, py::arg("p"))
      .def("ShouldMiss", &G4EnclosingCylinder::ShouldMiss, py::arg("p"), py::arg("v"));
}
