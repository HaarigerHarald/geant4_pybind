#include <pybind11/pybind11.h>

#include <G4Ellipsoid.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4Ellipsoid(py::module &m)
{
   py::class_<G4Ellipsoid, G4VSolid, std::unique_ptr<G4Ellipsoid, py::nodelete>>(m, "G4Ellipsoid", "ellipsoid class")

      .def(py::init<const G4String &, G4double, G4double, G4double>())
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double>())
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>())

      .def("GetSemiAxisMax", &G4Ellipsoid::GetSemiAxisMax)
      .def("GetZBottomCut", &G4Ellipsoid::GetZBottomCut)
      .def("GetZTopCut", &G4Ellipsoid::GetZTopCut)
      .def("SetSemiAxis", &G4Ellipsoid::SetSemiAxis)
      .def("SetZCuts", &G4Ellipsoid::SetZCuts)

      .def("__str__", [](const G4Ellipsoid &self) {
         std::stringstream ss;
         ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
         return ss.str();
      });
}
