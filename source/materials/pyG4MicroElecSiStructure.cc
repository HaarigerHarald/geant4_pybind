#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MicroElecSiStructure.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4MicroElecSiStructure(py::module &m)
{
   py::class_<G4MicroElecSiStructure>(m, "G4MicroElecSiStructure")

      .def("__copy__", [](const G4MicroElecSiStructure &self) { return new G4MicroElecSiStructure(self); })
      .def("__deepcopy__",
           [](const G4MicroElecSiStructure &self, py::dict) { return new G4MicroElecSiStructure(self); })

      .def(py::init<>())
      .def("Energy", &G4MicroElecSiStructure::Energy, py::arg("level"))
      .def("NumberOfLevels", &G4MicroElecSiStructure::NumberOfLevels);
}
