#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Color.hh>
#include <G4Colour.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Colour(py::module &m)
{
   py::class_<G4Colour>(m, "G4Colour", "colour class")

      .def(py::init<>())
      .def(py::init<G4double>())
      .def(py::init<G4double, G4double>())
      .def(py::init<G4double, G4double, G4double>())
      .def(py::init<G4double, G4double, G4double, G4double>())
      .def(py::init<G4ThreeVector>())

      .def("GetRed", &G4Colour::GetRed)
      .def("GetGreen", &G4Colour::GetGreen)
      .def("GetBlue", &G4Colour::GetBlue)
      .def("GetAlpha", &G4Colour::GetAlpha)

      .def(
         "__str__",
         [](const G4Colour &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator())

      .def(py::self != py::self);

   m.attr("G4Color") = m.attr("G4Colour");
}
