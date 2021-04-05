#include <pybind11/pybind11.h>

#include <G4EllipticalTube.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4EllipticalTube(py::module &m)
{
   py::class_<G4EllipticalTube, G4VSolid, std::unique_ptr<G4EllipticalTube, py::nodelete>>(
      m, "G4EllipticalTube", "elliptical tube solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double>())

      .def("GetDx", &G4EllipticalTube::GetDx)
      .def("GetDy", &G4EllipticalTube::GetDy)
      .def("GetDz", &G4EllipticalTube::GetDz)
      .def("SetDx", &G4EllipticalTube::SetDx)
      .def("SetDy", &G4EllipticalTube::SetDy)
      .def("SetDz", &G4EllipticalTube::SetDz)

      .def("__str__", [](const G4EllipticalTube &self) {
         std::stringstream ss;
         ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
         return ss.str();
      });
}
