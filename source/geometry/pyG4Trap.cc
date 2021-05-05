#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Trap.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Trap(py::module &m)
{
   py::class_<G4Trap, G4VSolid, std::unique_ptr<G4Trap, py::nodelete>>(m, "G4Trap", "Generic trapezoild soild class")

      .def(py::init<const G4String &>())
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double>())
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>())
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double>())
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double, G4double, G4double,
                    G4double, G4double, G4double>())

      .def("GetZHalfLength", &G4Trap::GetZHalfLength)
      .def("GetYHalfLength1", &G4Trap::GetYHalfLength1)
      .def("GetXHalfLength1", &G4Trap::GetXHalfLength1)
      .def("GetXHalfLength2", &G4Trap::GetXHalfLength2)
      .def("GetTanAlpha1", &G4Trap::GetTanAlpha1)
      .def("GetYHalfLength2", &G4Trap::GetYHalfLength2)
      .def("GetXHalfLength3", &G4Trap::GetXHalfLength3)
      .def("GetXHalfLength4", &G4Trap::GetXHalfLength4)
      .def("GetTanAlpha2", &G4Trap::GetTanAlpha2)
      .def("GetSidePlane", &G4Trap::GetSidePlane)
      .def("GetSymAxis", &G4Trap::GetSymAxis)
      .def("SetAllParameters", &G4Trap::SetAllParameters)

      .def(
         "__str__",
         [](const G4Trap &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
