#include <pybind11/pybind11.h>

#include <G4Hype.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4Hype(py::module &m)
{
   py::class_<G4Hype, G4VSolid, std::unique_ptr<G4Hype, py::nodelete>>(m, "G4Hype", "hyperbolic solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>())

      .def("GetInnerRadius", &G4Hype::GetInnerRadius)
      .def("GetOuterRadius", &G4Hype::GetOuterRadius)
      .def("GetZHalfLength", &G4Hype::GetZHalfLength)
      .def("GetInnerStereo", &G4Hype::GetInnerStereo)
      .def("GetOuterStereo", &G4Hype::GetOuterStereo)
      .def("SetInnerRadius", &G4Hype::SetInnerRadius)
      .def("SetOuterRadius", &G4Hype::SetOuterRadius)
      .def("SetZHalfLength", &G4Hype::SetZHalfLength)
      .def("SetInnerStereo", &G4Hype::SetInnerStereo)
      .def("SetOuterStereo", &G4Hype::SetOuterStereo)

      .def(
         "__str__",
         [](const G4Hype &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
