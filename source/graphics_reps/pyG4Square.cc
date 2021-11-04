#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Square.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Square(py::module &m)
{
   py::class_<G4Square, G4VMarker>(m, "G4Square")
      .def(py::init<>())
      .def(py::init<const G4VMarker &>())
      .def(py::init<const G4Point3D &>(), py::arg("position"))

      .def(
         "__str__",
         [](const G4Square &self) {
            std::stringstream ss;
            ss << self;
            return ss.str();
         },
         py::is_operator());
}
