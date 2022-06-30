#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NistElementBuilder.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4NistElementBuilder(py::module &m)
{
   py::class_<G4NistElementBuilder>(m, "G4NistElementBuilder")

      .def("__copy__", [](const G4NistElementBuilder &self) { return new G4NistElementBuilder(self); })
      .def("__deepcopy__", [](const G4NistElementBuilder &self, py::dict) { return new G4NistElementBuilder(self); })
      .def(py::init<G4int>(), py::arg("vb"))
      .def("FindElement", &G4NistElementBuilder::FindElement, py::arg("Z"), py::return_value_policy::reference)
      .def("FindOrBuildElement", py::overload_cast<G4int, G4bool>(&G4NistElementBuilder::FindOrBuildElement),
           py::arg("Z"), py::arg("buildIsotopes") = true, py::return_value_policy::reference)

      .def("FindOrBuildElement", py::overload_cast<const G4String &, G4bool>(&G4NistElementBuilder::FindOrBuildElement),
           py::arg("symb"), py::arg("buildIsotopes") = true, py::return_value_policy::reference)

      .def("GetAtomicMass", &G4NistElementBuilder::GetAtomicMass, py::arg("Z"), py::arg("N"))
      .def("GetAtomicMassAmu", py::overload_cast<const G4String &>(&G4NistElementBuilder::GetAtomicMassAmu, py::const_),
           py::arg("symb"))

      .def("GetAtomicMassAmu", py::overload_cast<G4int>(&G4NistElementBuilder::GetAtomicMassAmu, py::const_),
           py::arg("Z"))

      .def("GetElementNames", &G4NistElementBuilder::GetElementNames)
      .def("GetIsotopeAbundance", &G4NistElementBuilder::GetIsotopeAbundance, py::arg("Z"), py::arg("N"))
      .def("GetIsotopeMass", &G4NistElementBuilder::GetIsotopeMass, py::arg("Z"), py::arg("N"))
      .def("GetMaxNumElements", &G4NistElementBuilder::GetMaxNumElements)
      .def("GetNistFirstIsotopeN", &G4NistElementBuilder::GetNistFirstIsotopeN, py::arg("Z"))
      .def("GetNumberOfNistIsotopes", &G4NistElementBuilder::GetNumberOfNistIsotopes, py::arg("Z"))
      .def("GetTotalElectronBindingEnergy", &G4NistElementBuilder::GetTotalElectronBindingEnergy, py::arg("Z"))
      .def("GetZ", &G4NistElementBuilder::GetZ, py::arg("symb"))
      .def("PrintElement", &G4NistElementBuilder::PrintElement, py::arg("Z"))
      .def("SetVerbose", &G4NistElementBuilder::SetVerbose);
}
