#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Torus.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Torus(py::module &m)
{
   py::class_<G4Torus, G4VSolid, py::nodelete>(m, "G4Torus", "Torus solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>())

      .def("GetRmin", &G4Torus::GetRmin)
      .def("GetRmax", &G4Torus::GetRmax)
      .def("GetRtor", &G4Torus::GetRtor)
      .def("GetSPhi", &G4Torus::GetSPhi)
      .def("GetDPhi", &G4Torus::GetDPhi)

      .def("__str__",
           [](const G4Torus &self) {
              std::stringstream ss;
              ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
              return ss.str();
           },
           py::is_operator());
}
