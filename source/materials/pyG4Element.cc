#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Element.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Element(py::module &m)
{
   py::class_<G4Element>(m, "G4Element")

      .def(py::init<const G4String &, const G4String &, G4double, G4double>(), py::arg("name"), py::arg("symbol"),
           py::arg("Zeff"), py::arg("Aeff"))

      .def(py::init<const G4String &, const G4String &, G4int>(), py::arg("name"), py::arg("symbol"),
           py::arg("nbIsotopes"))

      .def("AddIsotope", &G4Element::AddIsotope, py::arg("isotope"), py::arg("RelativeAbundance"))
      .def("GetA", &G4Element::GetA)
      .def("GetAtomicMassAmu", &G4Element::GetAtomicMassAmu)
      .def("GetAtomicShell", &G4Element::GetAtomicShell, py::arg("index"))
      .def_static("GetElement", &G4Element::GetElement, py::arg("name"), py::arg("warning") = true,
                  py::return_value_policy::reference)
      .def_static("GetElementTable", &G4Element::GetElementTable, py::return_value_policy::reference)
      .def("GetIndex", &G4Element::GetIndex)
      .def("GetIonisation", &G4Element::GetIonisation, py::return_value_policy::reference)
      .def("GetIsotope", &G4Element::GetIsotope, py::arg("iso"), py::return_value_policy::reference)
      .def("GetIsotopeVector", &G4Element::GetIsotopeVector, py::return_value_policy::reference)
      .def("GetN", &G4Element::GetN)
      .def("GetName", &G4Element::GetName)
      .def("GetNaturalAbundanceFlag", &G4Element::GetNaturalAbundanceFlag)
      .def("GetNbOfAtomicShells", &G4Element::GetNbOfAtomicShells)
      .def("GetNbOfShellElectrons", &G4Element::GetNbOfShellElectrons, py::arg("index"))
      .def_static("GetNumberOfElements", &G4Element::GetNumberOfElements)
      .def("GetNumberOfIsotopes", &G4Element::GetNumberOfIsotopes)
      .def("GetRelativeAbundanceVector", &G4Element::GetRelativeAbundanceVector, py::return_value_policy::reference)
      .def("GetSymbol", &G4Element::GetSymbol)
      .def("GetZ", &G4Element::GetZ)
      .def("GetZasInt", &G4Element::GetZasInt)
      .def("GetfCoulomb", &G4Element::GetfCoulomb)
      .def("GetfRadTsai", &G4Element::GetfRadTsai)
      .def("SetName", &G4Element::SetName, py::arg("name"))
      .def("SetNaturalAbundanceFlag", &G4Element::SetNaturalAbundanceFlag);
}
