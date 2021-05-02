#include <pybind11/pybind11.h>

#include <G4UIcmdWithABool.hh>
#include <G4UImessenger.hh>

#include "typecast.hh"

namespace py = pybind11;

void export_G4UIcmdWithABool(py::module &m)
{
   py::class_<G4UIcmdWithABool, G4UIcommand, std::unique_ptr<G4UIcmdWithABool>>(m, "G4UIcmdWithABool")

      .def(py::init<const char *, G4UImessenger *>(), py::arg("theCommandPath"), py::arg("theMessenger"))
      .def_static("GetNewBoolValue", &G4UIcmdWithABool::GetNewBoolValue)
      .def("SetParameterName", &G4UIcmdWithABool::SetParameterName, py::arg("theName"), py::arg("omittable"),
           py::arg("currentAsDefault") = false)

      .def("SetDefaultValue", &G4UIcmdWithABool::SetDefaultValue);
}
