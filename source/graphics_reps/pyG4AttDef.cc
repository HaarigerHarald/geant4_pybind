#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AttDef.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AttDef(py::module &m)
{
   py::class_<G4AttDef>(m, "G4AttDef")
      .def(py::init<const G4String &, const G4String &, const G4String &, const G4String &, const G4String &>())
      .def(py::init<const G4String &, const G4String &, const G4String &, const G4String &, const G4TypeKey &>())
      .def(py::init<>())

      .def("GetName", &G4AttDef::GetName)
      .def("GetDesc", &G4AttDef::GetDesc)
      .def("GetCategory", &G4AttDef::GetCategory)
      .def("GetExtra", &G4AttDef::GetExtra)
      .def("GetValueType", &G4AttDef::GetValueType)

      .def("SetName", &G4AttDef::SetName)
      .def("SetDesc", &G4AttDef::SetDesc)
      .def("SetCategory", &G4AttDef::SetCategory)
      .def("SetExtra", &G4AttDef::SetExtra)
      .def("SetValueType", &G4AttDef::SetValueType);
}
