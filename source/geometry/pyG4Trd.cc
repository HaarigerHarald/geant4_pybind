#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Trd.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Trd(py::module &m)
{
   py::class_<G4Trd, G4VSolid, std::unique_ptr<G4Trd, py::nodelete>>(m, "G4Trd", "Trapezoild solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>())

      .def("GetXHalfLength1", &G4Trd::GetXHalfLength1)
      .def("GetXHalfLength2", &G4Trd::GetXHalfLength2)
      .def("GetYHalfLength1", &G4Trd::GetYHalfLength1)
      .def("GetYHalfLength2", &G4Trd::GetYHalfLength2)
      .def("GetZHalfLength", &G4Trd::GetZHalfLength)
      .def("SetXHalfLength1", &G4Trd::SetXHalfLength1)
      .def("SetXHalfLength2", &G4Trd::SetXHalfLength2)
      .def("SetYHalfLength1", &G4Trd::SetYHalfLength1)
      .def("SetYHalfLength2", &G4Trd::SetYHalfLength2)
      .def("SetZHalfLength", &G4Trd::SetZHalfLength)

      .def(
         "__str__",
         [](const G4Trd &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
