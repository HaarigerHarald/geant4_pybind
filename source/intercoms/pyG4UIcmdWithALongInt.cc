#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIcmdWithALongInt.hh>
#include <G4UImessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UIcmdWithALongInt(py::module &m)
{
   py::class_<G4UIcmdWithALongInt, G4UIcommand>(m, "G4UIcmdWithALongInt")

      .def(py::init<const char *, G4UImessenger *>(), py::arg("theCommandPath"), py::arg("theMessenger"))
      .def_static("GetNewLongIntValue", &G4UIcmdWithALongInt::GetNewLongIntValue)
      .def("SetParameterName", &G4UIcmdWithALongInt::SetParameterName, py::arg("theName"), py::arg("omittable"),
           py::arg("currentAsDefault") = false)

      .def("SetDefaultValue", &G4UIcmdWithALongInt::SetDefaultValue);
}
