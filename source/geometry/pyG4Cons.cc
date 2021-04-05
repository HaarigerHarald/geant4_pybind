#include <pybind11/pybind11.h>

#include <G4Cons.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4Cons(py::module &m)
{
   py::class_<G4Cons, G4VSolid, std::unique_ptr<G4Cons, py::nodelete>>(m, "G4Cons", "Cone solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double, G4double>())

      .def("GetInnerRadiusMinusZ", &G4Cons::GetInnerRadiusMinusZ)
      .def("GetOuterRadiusMinusZ", &G4Cons::GetOuterRadiusMinusZ)
      .def("GetInnerRadiusPlusZ", &G4Cons::GetInnerRadiusPlusZ)
      .def("GetOuterRadiusPlusZ", &G4Cons::GetOuterRadiusPlusZ)
      .def("GetZHalfLength", &G4Cons::GetZHalfLength)
      .def("GetStartPhiAngle", &G4Cons::GetStartPhiAngle)
      .def("GetDeltaPhiAngle", &G4Cons::GetDeltaPhiAngle)
      .def("SetInnerRadiusMinusZ", &G4Cons::SetInnerRadiusMinusZ)
      .def("SetOuterRadiusMinusZ", &G4Cons::SetOuterRadiusMinusZ)
      .def("SetInnerRadiusPlusZ", &G4Cons::SetInnerRadiusPlusZ)
      .def("SetOuterRadiusPlusZ", &G4Cons::SetOuterRadiusPlusZ)
      .def("SetZHalfLength", &G4Cons::SetZHalfLength)
      .def("SetStartPhiAngle", &G4Cons::SetStartPhiAngle, py::arg("newSPhi"), py::arg("compute") = true)
      .def("SetDeltaPhiAngle", &G4Cons::SetDeltaPhiAngle)

      .def("__str__", [](const G4Cons &self) {
         std::stringstream ss;
         ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
         return ss.str();
      });
}
