#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Circle.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Circle(py::module &m)
{
   py::class_<G4Circle, G4VMarker>(m, "G4Circle")
      .def(py::init<>())
      .def(py::init<const G4VMarker &>())
      .def(py::init<const G4Point3D &>())

      .def(
         "__str__",
         [](const G4Circle &self) {
            std::stringstream ss;
            ss << self;
            return ss.str();
         },
         py::is_operator());
}
