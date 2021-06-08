#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Element.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Element(py::module &m)
{
   py::class_<G4Element>(m, "G4Element", "element class")

      .def(py::init<const G4String &, const G4String &, G4double, G4double>())
      .def(py::init<const G4String &, const G4String &, G4int>())

      .def("AddIsotope", &G4Element::AddIsotope)
      .def("GetName", &G4Element::GetName, py::return_value_policy::reference)
      .def("GetSymbol", &G4Element::GetSymbol, py::return_value_policy::reference)
      .def("SetName", &G4Element::SetName)
      .def("GetZ", &G4Element::GetZ)
      .def("GetN", &G4Element::GetN)
      .def("GetA", &G4Element::GetA)
      .def("GetNbOfAtomicShells", &G4Element::GetNbOfAtomicShells)
      .def("GetAtomicShell", &G4Element::GetAtomicShell)
      .def("GetNumberOfIsotopes", &G4Element::GetNumberOfIsotopes)
      .def("GetIsotopeVector", &G4Element::GetIsotopeVector)
      .def("GetRelativeAbundanceVector",
           [](const G4Element &self) {
              py::list        aList;
              const G4double *aVec = self.GetRelativeAbundanceVector();
              size_t          niso = self.GetNumberOfIsotopes();
              for (size_t i = 0; i < niso; i++) {
                 aList.append(aVec[i]);
              }
              return aList;
           })

      .def("GetIsotope", &G4Element::GetIsotope, py::return_value_policy::reference)
      .def_static("GetElementTable", &G4Element::GetElementTable, py::return_value_policy::reference)
      .def_static("GetNumberOfElements", &G4Element::GetNumberOfElements)
      .def("GetIndex", &G4Element::GetIndex)
      .def_static("GetElement", &G4Element::GetElement, py::return_value_policy::reference)
      .def("GetfCoulomb", &G4Element::GetfCoulomb)
      .def("GetfRadTsai", &G4Element::GetfRadTsai)
      .def("GetIonisation", &G4Element::GetIonisation, py::return_value_policy::reference_internal);
}
