#include <pybind11/pybind11.h>

#include <G4Box.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4Box(py::module &m)
{
   py::class_<G4Box, G4VSolid, std::unique_ptr<G4Box, py::nodelete>>(m, "G4Box", "box solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double>())

      .def("GetXHalfLength", &G4Box::GetXHalfLength)
      .def("GetYHalfLength", &G4Box::GetYHalfLength)
      .def("GetZHalfLength", &G4Box::GetZHalfLength)
      .def("SetXHalfLength", &G4Box::SetXHalfLength)
      .def("SetYHalfLength", &G4Box::SetYHalfLength)
      .def("SetZHalfLength", &G4Box::SetZHalfLength)

      .def("__str__", [](const G4Box &self) {
         std::stringstream ss;
         ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
         return ss.str();
      });
}
