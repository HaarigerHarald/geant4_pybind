#include <pybind11/pybind11.h>

#include <G4TwistedTrd.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4TwistedTrd(py::module &m)
{
   py::class_<G4TwistedTrd, G4VSolid, std::unique_ptr<G4TwistedTrd, py::nodelete>>(m, "G4TwistedTrd",
                                                                                   "twisted trapezoid solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double>())

      .def("GetX1HalfLength", &G4TwistedTrd::GetX1HalfLength)
      .def("GetX2HalfLength", &G4TwistedTrd::GetX2HalfLength)
      .def("GetY1HalfLength", &G4TwistedTrd::GetY1HalfLength)
      .def("GetY2HalfLength", &G4TwistedTrd::GetY2HalfLength)
      .def("GetZHalfLength", &G4TwistedTrd::GetZHalfLength)
      .def("GetPhiTwist", &G4TwistedTrd::GetPhiTwist)

      .def("__str__", [](const G4TwistedTrd &self) {
         std::stringstream ss;
         ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
         return ss.str();
      });
}
