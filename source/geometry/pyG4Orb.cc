#include <pybind11/pybind11.h>

#include <G4Orb.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4Orb(py::module &m)
{
   py::class_<G4Orb, G4VSolid, std::unique_ptr<G4Orb, py::nodelete>>(m, "G4Orb", "Orb solid class")

      .def(py::init<const G4String &, G4double>())

      .def("GetRadius", &G4Orb::GetRadius)
      .def("SetRadius", &G4Orb::SetRadius)

      .def("__str__", [](const G4Orb &self) {
         std::stringstream ss;
         ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
         return ss.str();
      });
}
