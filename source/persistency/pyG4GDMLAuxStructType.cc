#ifdef G4_HAS_GDML

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <G4GDMLAuxStructType.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GDMLAuxStructType(py::module &m)
{
   py::class_<G4GDMLAuxStructType>(m, "G4GDMLAuxStructType")

      .def(py::init<>())
      .def("__copy__", [](const G4GDMLAuxStructType &self) { return new G4GDMLAuxStructType(self); })
      .def("__deepcopy__", [](const G4GDMLAuxStructType &self, py::dict) { return new G4GDMLAuxStructType(self); })
      .def_readwrite("auxList", &G4GDMLAuxStructType::auxList)
      .def_readwrite("type", &G4GDMLAuxStructType::type)
      .def_readwrite("unit", &G4GDMLAuxStructType::unit)
      .def_readwrite("value", &G4GDMLAuxStructType::value);

   py::bind_vector<G4GDMLAuxListType>(m, "G4GDMLAuxListType");
}

#endif // G4_HAS_GDML
