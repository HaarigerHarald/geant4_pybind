#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AtomicBond.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AtomicBond(py::module &m)
{
   py::class_<G4AtomicBond> mG4AtomicBond(m, "G4AtomicBond");

   py::enum_<G4AtomicBond::theBondType>(mG4AtomicBond, "theBondType")
      .value("Ionic", G4AtomicBond::theBondType::Ionic)
      .value("Covalent", G4AtomicBond::theBondType::Covalent)
      .value("Metallic", G4AtomicBond::theBondType::Metallic)
      .value("NA", G4AtomicBond::theBondType::NA)
      .export_values();

   mG4AtomicBond.def("__copy__", [](const G4AtomicBond &self) { return new G4AtomicBond(self); })
      .def("__deepcopy__", [](const G4AtomicBond &self, py::dict) { return new G4AtomicBond(self); })
      .def(py::init<G4AtomicBond::theBondType, G4Element *, G4int, G4Element *, G4int>(), py::arg("aType"),
           py::arg("firstAtomKind"), py::arg("firstAtomNumber"), py::arg("secondAtomKind"), py::arg("secondAtomNumber"))

      .def("GetAromaticity", &G4AtomicBond::GetAromaticity)
      .def("GetFirstAtomKind", &G4AtomicBond::GetFirstAtomKind, py::return_value_policy::reference)
      .def("GetFirstAtomNumber", &G4AtomicBond::GetFirstAtomNumber)
      .def("GetSecondAtomKind", &G4AtomicBond::GetSecondAtomKind, py::return_value_policy::reference)
      .def("GetSecondAtomNumber", &G4AtomicBond::GetSecondAtomNumber)
      .def("GetType", &G4AtomicBond::GetType)
      .def("SetAromaticity", &G4AtomicBond::SetAromaticity, py::arg("aBool"))
      .def("SetFirstAtomKind", &G4AtomicBond::SetFirstAtomKind, py::arg("aElement"))
      .def("SetFirstAtomNumber", &G4AtomicBond::SetFirstAtomNumber, py::arg("aInt"))
      .def("SetSecondAtomKind", &G4AtomicBond::SetSecondAtomKind, py::arg("aElement"))
      .def("SetSecondAtomNumber", &G4AtomicBond::SetSecondAtomNumber, py::arg("aInt"))
      .def("SetType", &G4AtomicBond::SetType, py::arg("aType"));
}
