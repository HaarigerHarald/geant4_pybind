#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/stl_bind.h>

#include <G4Isotope.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Isotope(py::module &m)
{
   py::class_<G4Isotope>(m, "G4Isotope")

      .def(py::init<const G4String &, G4int, G4int, G4double, G4int>(), py::arg("name"), py::arg("z"), py::arg("n"),
           py::arg("a") = 0., py::arg("mlevel") = 0)

      .def("GetA", &G4Isotope::GetA)
      .def("GetIndex", &G4Isotope::GetIndex)
      .def_static("GetIsotope", &G4Isotope::GetIsotope, py::arg("name"), py::arg("warning") = false,
                  py::return_value_policy::reference)
      .def_static("GetIsotopeTable", &G4Isotope::GetIsotopeTable, py::return_value_policy::reference)
      .def("GetN", &G4Isotope::GetN)
      .def("GetName", &G4Isotope::GetName)
      .def_static("GetNumberOfIsotopes", &G4Isotope::GetNumberOfIsotopes)
      .def("GetZ", &G4Isotope::GetZ)
      .def("Getm", &G4Isotope::Getm)
      .def("SetName", &G4Isotope::SetName, py::arg("name"))
      .def(py::self != py::self)
      .def(py::self == py::self)
      .def(
         "__str__",
         [](const G4Isotope &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());

   py::bind_vector<G4IsotopeTable>(m, "G4IsotopeTable");
}
