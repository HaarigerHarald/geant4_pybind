#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AttValue.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AttValue(py::module &m)
{
   py::class_<G4AttValue>(m, "G4AttValue")
      .def(py::init<const G4String &, const G4String &, const G4String &>())
      .def(py::init<>())

      .def("GetName", &G4AttValue::GetName)
      .def("GetValue", &G4AttValue::GetValue)
      .def("GetShowLabel", &G4AttValue::GetShowLabel)

      .def("SetName", &G4AttValue::SetName)
      .def("SetValue", &G4AttValue::SetValue)
      .def("SetShowLabel", &G4AttValue::SetShowLabel);
}
