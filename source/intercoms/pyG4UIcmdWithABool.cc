#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIcmdWithABool.hh>
#include <G4UImessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UIcmdWithABool(py::module &m)
{
   py::class_<G4UIcmdWithABool, G4UIcommand>(m, "G4UIcmdWithABool")

      .def(py::init<const char *, G4UImessenger *>(), py::arg("theCommandPath"), py::arg("theMessenger"))
      .def_static("GetNewBoolValue", &G4UIcmdWithABool::GetNewBoolValue)
      .def("SetParameterName", &G4UIcmdWithABool::SetParameterName, py::arg("theName"), py::arg("omittable"),
           py::arg("currentAsDefault") = false)

      .def("SetDefaultValue", &G4UIcmdWithABool::SetDefaultValue);
}
