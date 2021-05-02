#include <pybind11/pybind11.h>

#include <G4TwistedTrap.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4TwistedTrap(py::module &m)
{
   py::class_<G4TwistedTrap, G4VSolid, std::unique_ptr<G4TwistedTrap, py::nodelete>>(m, "G4TwistedTrap",
                                                                                     "twisted trapezoid solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>())
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double, G4double, G4double,
                    G4double, G4double, G4double>())

      .def(
         "__str__",
         [](const G4TwistedTrap &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
