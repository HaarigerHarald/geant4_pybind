#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIcmdWithAnInteger.hh>
#include <G4UImessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UIcmdWithAnInteger(py::module &m)
{
   py::class_<G4UIcmdWithAnInteger, G4UIcommand>(m, "G4UIcmdWithAnInteger")

      .def(py::init<const char *, G4UImessenger *>(), py::arg("theCommandPath"), py::arg("theMessenger"))
      .def_static("GetNewIntValue", &G4UIcmdWithAnInteger::GetNewIntValue)
      .def("SetParameterName", &G4UIcmdWithAnInteger::SetParameterName, py::arg("theName"), py::arg("omittable"),
           py::arg("currentAsDefault") = false)

      .def("SetDefaultValue", &G4UIcmdWithAnInteger::SetDefaultValue);
}
