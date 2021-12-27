#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4Visible.hh>
#include <G4VisAttributes.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Visible(py::module &m)
{
   py::class_<G4Visible>(m, "G4Visible")

      .def(py::init<>())
      .def("__copy__", [](const G4Visible &self) { return new G4Visible(self); })
      .def("__deepcopy__", [](const G4Visible &self, py::dict) { return new G4Visible(self); })
      .def(py::init<const G4VisAttributes *>())
      .def("GetVisAttributes", &G4Visible::GetVisAttributes, py::return_value_policy::reference)
      .def("SetVisAttributes", py::overload_cast<const G4VisAttributes &>(&G4Visible::SetVisAttributes))
      .def(py::self != py::self)
      .def(
         "__str__",
         [](const G4Visible &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
