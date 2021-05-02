#include <pybind11/pybind11.h>

#include <G4Tubs.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4Tubs(py::module &m)
{
   py::class_<G4Tubs, G4VSolid, std::unique_ptr<G4Tubs, py::nodelete>>(m, "G4Tubs", "Tube solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>())

      .def("GetInnerRadius", &G4Tubs::GetInnerRadius)
      .def("GetOuterRadius", &G4Tubs::GetOuterRadius)
      .def("GetZHalfLength", &G4Tubs::GetZHalfLength)
      .def("GetStartPhiAngle", &G4Tubs::GetStartPhiAngle)
      .def("GetDeltaPhiAngle", &G4Tubs::GetDeltaPhiAngle)
      .def("SetInnerRadius", &G4Tubs::SetInnerRadius)
      .def("SetOuterRadius", &G4Tubs::SetOuterRadius)
      .def("SetZHalfLength", &G4Tubs::SetZHalfLength)
      .def("SetStartPhiAngle", &G4Tubs::SetStartPhiAngle, py::arg("newSPhi"), py::arg("compute") = true)
      .def("SetDeltaPhiAngle", &G4Tubs::SetDeltaPhiAngle)
      .def("GetRMin", &G4Tubs::GetRMin)
      .def("GetRMax", &G4Tubs::GetRMax)
      .def("GetDz", &G4Tubs::GetDz)
      .def("GetSPhi", &G4Tubs::GetSPhi)
      .def("GetDPhi", &G4Tubs::GetDPhi)

      .def(
         "__str__",
         [](const G4Tubs &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
