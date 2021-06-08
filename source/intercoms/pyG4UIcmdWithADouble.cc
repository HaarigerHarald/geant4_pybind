#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIcmdWithADouble.hh>
#include <G4UImessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UIcmdWithADouble(py::module &m)
{
   py::class_<G4UIcmdWithADouble, G4UIcommand>(m, "G4UIcmdWithADouble")

      .def(py::init<const char *, G4UImessenger *>(), py::arg("theCommandPath"), py::arg("theMessenger"))
      .def_static("GetNewDoubleValue", &G4UIcmdWithADouble::GetNewDoubleValue)
      .def("SetParameterName", &G4UIcmdWithADouble::SetParameterName, py::arg("theName"), py::arg("omittable"),
           py::arg("currentAsDefault") = false)

      .def("SetDefaultValue", &G4UIcmdWithADouble::SetDefaultValue);
}
