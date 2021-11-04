#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <G4Isotope.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Isotope(py::module &m)
{
   py::bind_vector<G4IsotopeTable>(m, "G4IsotopeTable");

   py::class_<G4Isotope>(m, "G4Isotope", "isotope class")

      .def(py::init<const G4String &, G4int, G4int>())
      .def(py::init<const G4String &, G4int, G4int, G4double>())

      .def("GetName", &G4Isotope::GetName, py::return_value_policy::reference)
      .def("SetName", &G4Isotope::SetName)
      .def("GetZ", &G4Isotope::GetZ)
      .def("GetN", &G4Isotope::GetN)
      .def("GetA", &G4Isotope::GetA)
      .def_static("GetIsotope", &G4Isotope::GetIsotope, py::arg("name"), py::arg("warning") = false,
                  py::return_value_policy::reference)

      .def_static("GetIsotopeTable", &G4Isotope::GetIsotopeTable, py::return_value_policy::reference)
      .def_static("GetNumberOfIsotopes", &G4Isotope::GetNumberOfIsotopes)
      .def("GetIndex", &G4Isotope::GetIndex)

      .def("Print",
           [](const G4Isotope &self) {
              {
                 G4cout << self;
              }
           })

      .def(py::self == py::self)
      .def(py::self != py::self);
}
