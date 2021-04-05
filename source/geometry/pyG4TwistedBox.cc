#include <pybind11/pybind11.h>

#include <G4TwistedBox.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4TwistedBox(py::module &m)
{
   py::class_<G4TwistedBox, G4VSolid, std::unique_ptr<G4TwistedBox, py::nodelete>>(m, "G4TwistedBox",
                                                                                   "twisted box solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double>())

      .def("GetXHalfLength", &G4TwistedBox::GetXHalfLength)
      .def("GetYHalfLength", &G4TwistedBox::GetYHalfLength)
      .def("GetZHalfLength", &G4TwistedBox::GetZHalfLength)
      .def("GetPhiTwist", &G4TwistedBox::GetPhiTwist)

      .def("__str__", [](const G4TwistedBox &self) {
         std::stringstream ss;
         ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
         return ss.str();
      });
}
