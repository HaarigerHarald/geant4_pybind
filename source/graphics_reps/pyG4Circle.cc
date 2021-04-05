#include <pybind11/pybind11.h>

#include <G4Circle.hh>

#include "typecast.hh"

namespace py = pybind11;

void export_G4Circle(py::module &m)
{
   py::class_<G4Circle, G4VMarker, std::unique_ptr<G4Circle>>(m, "G4Circle")
      .def(py::init<>())
      .def(py::init<const G4VMarker &>())
      .def(py::init<const G4Point3D &>());
}
