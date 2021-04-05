#include <pybind11/pybind11.h>

#include <G4Tet.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4Tet(py::module &m)
{
   py::class_<G4Tet, G4VSolid, std::unique_ptr<G4Tet, py::nodelete>>(m, "G4Tet", "tetrahedra solid class")

      .def(py::init<const G4String &, const G4ThreeVector &, const G4ThreeVector &, const G4ThreeVector &,
                    const G4ThreeVector &, G4bool *>())
      .def(py::init<const G4String &, const G4ThreeVector &, const G4ThreeVector &, const G4ThreeVector &,
                    const G4ThreeVector &>())

      .def("__str__", [](const G4Tet &self) {
         std::stringstream ss;
         ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
         return ss.str();
      });
}
