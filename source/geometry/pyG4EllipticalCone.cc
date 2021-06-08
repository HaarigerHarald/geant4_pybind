#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EllipticalCone.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4EllipticalCone(py::module &m)
{
   py::class_<G4EllipticalCone, G4VSolid, py::nodelete>(m, "G4EllipticalCone", "elliptical cone solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double>())

      .def("GetSimiAxisMax", &G4EllipticalCone::GetSemiAxisMax)
      .def("GetZTopCut", &G4EllipticalCone::GetZTopCut)
      .def("SetSemiAxis", &G4EllipticalCone::SetSemiAxis)
      .def("SetZCut", &G4EllipticalCone::SetZCut)

      .def("__str__",
           [](const G4EllipticalCone &self) {
              std::stringstream ss;
              ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
              return ss.str();
           },
           py::is_operator());
}
