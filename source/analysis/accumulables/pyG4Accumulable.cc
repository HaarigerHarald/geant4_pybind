#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4Accumulable.hh>
#include <G4AccumulableManager.hh>

#include <cmath>
#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Accumulable(py::module &m)
{
   py::class_<G4Accumulable<G4double>, G4VAccumulable>(m, "G4Accumulable")

      .def(py::init<const G4String &, G4double, G4MergeMode>(), py::arg("name"), py::arg("initialValue"),
           py::arg("mergeMode") = G4MergeMode::kAddition)

      .def(py::init<G4double, G4MergeMode>(), py::arg("initialValue"), py::arg("mergeMode") = G4MergeMode::kAddition)

      .def(py::init<const G4String &, G4int, G4MergeMode>(), py::arg("name"), py::arg("initialValue"),
           py::arg("mergeMode") = G4MergeMode::kAddition)

      .def(py::init<G4int, G4MergeMode>(), py::arg("initialValue"), py::arg("mergeMode") = G4MergeMode::kAddition)

      .def("__copy__", [](const G4Accumulable<G4double> &self) { return new G4Accumulable<G4double>(self); })
      .def("__deepcopy__",
           [](const G4Accumulable<G4double> &self, py::dict) { return new G4Accumulable<G4double>(self); })

      .def(py::self *= py::self)
      .def(py::self += py::self)

      .def(py::self += G4double())
      .def(py::self *= G4double())

      .def(
         "__int__", [](const G4Accumulable<G4double> &self) { return (G4int)self.GetValue(); }, py::is_operator())

      .def(
         "__float__", [](const G4Accumulable<G4double> &self) { return self.GetValue(); }, py::is_operator())

      .def("Merge", &G4Accumulable<G4double>::Merge, py::arg("other"))
      .def("Reset", &G4Accumulable<G4double>::Reset)

      .def("GetValue",
           [](const G4Accumulable<G4double> &self) -> py::object {
              G4double value = self.GetValue();
              if (std::fmod(value, 1.0) == 0) {
                 return py::int_((G4int)value);
              } else {
                 return py::float_(value);
              }
           })

      .def(
         "__str__",
         [](const G4Accumulable<G4double> &self) {
            std::stringstream ss;
            G4double          value = self.GetValue();

            if (std::fmod(value, 1.0) == 0) {
               ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << (G4int)self.GetValue();
            } else {
               ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self.GetValue();
            }

            return ss.str();
         },
         py::is_operator())

      .def(
         "__format__",
         [](const G4Accumulable<G4double> &self, const py::str &spec) {
            G4double   value  = self.GetValue();
            py::object format = py::module::import("builtins").attr("format");

            if (std::fmod(value, 1.0) == 0) {
               return format(py::int_((G4int)self.GetValue()), spec);
            } else {
               return format(py::float_(self.GetValue()), spec);
            }
         },
         py::is_operator());
}
