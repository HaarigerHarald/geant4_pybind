#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIcmdWithAString.hh>
#include <G4UImessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UIcmdWithAString(py::module &m)
{
   py::class_<G4UIcmdWithAString, G4UIcommand>(m, "G4UIcmdWithAString")

      .def(py::init<const char *, G4UImessenger *>(), py::arg("theCommandPath"), py::arg("theMessenger"))
      .def("SetParameterName", &G4UIcmdWithAString::SetParameterName, py::arg("theName"), py::arg("omittable"),
           py::arg("currentAsDefault") = false)

      .def("SetCandidates", &G4UIcmdWithAString::SetCandidates)
      .def("SetDefaultValue", &G4UIcmdWithAString::SetDefaultValue);
}
