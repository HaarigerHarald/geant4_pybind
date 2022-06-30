#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AtomicFormFactor.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AtomicFormFactor(py::module &m)
{
   py::class_<G4AtomicFormFactor>(m, "G4AtomicFormFactor")

      .def("__copy__", [](const G4AtomicFormFactor &self) { return new G4AtomicFormFactor(self); })
      .def("__deepcopy__", [](const G4AtomicFormFactor &self, py::dict) { return new G4AtomicFormFactor(self); })
      .def("Get", &G4AtomicFormFactor::Get, py::arg("kScatteringVector"), py::arg("Z"), py::arg("charge") = 0)
      .def_static("GetManager", &G4AtomicFormFactor::GetManager, py::return_value_policy::reference);
}
