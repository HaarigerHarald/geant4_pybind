#include <pybind11/pybind11.h>

#include <G4TwistedTubs.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4TwistedTubs(py::module &m)
{
   py::class_<G4TwistedTubs, G4VSolid, std::unique_ptr<G4TwistedTubs, py::nodelete>>(m, "G4TwistedTubs",
                                                                                     "twisted tube solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>())
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4int, G4double>())
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double>())
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4int, G4double>())

      .def("GetDPhi", &G4TwistedTubs::GetDPhi)
      .def("GetPhiTwist", &G4TwistedTubs::GetPhiTwist)
      .def("GetInnerRadius", &G4TwistedTubs::GetInnerRadius)
      .def("GetOuterRadius", &G4TwistedTubs::GetOuterRadius)
      .def("GetInnerStereo", &G4TwistedTubs::GetInnerStereo)
      .def("GetOuterStereo", &G4TwistedTubs::GetOuterStereo)
      .def("GetZHalfLength", &G4TwistedTubs::GetZHalfLength)
      .def("GetKappa", &G4TwistedTubs::GetKappa)
      .def("GetTanInnerStereo", &G4TwistedTubs::GetTanInnerStereo)
      .def("GetTanInnerStereo2", &G4TwistedTubs::GetTanInnerStereo2)
      .def("GetTanOuterStereo", &G4TwistedTubs::GetTanOuterStereo)
      .def("GetTanOuterStereo2", &G4TwistedTubs::GetTanOuterStereo2)
      .def("GetEndZ", &G4TwistedTubs::GetEndZ)
      .def("GetEndPhi", &G4TwistedTubs::GetEndPhi)
      .def("GetEndInnerRadius", py::overload_cast<G4int>(&G4TwistedTubs::GetEndInnerRadius, py::const_))
      .def("GetEndInnerRadius", py::overload_cast<>(&G4TwistedTubs::GetEndInnerRadius, py::const_))
      .def("GetEndOuterRadius", py::overload_cast<G4int>(&G4TwistedTubs::GetEndOuterRadius, py::const_))
      .def("GetEndOuterRadius", py::overload_cast<>(&G4TwistedTubs::GetEndOuterRadius, py::const_))

      .def(
         "__str__",
         [](const G4TwistedTubs &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
