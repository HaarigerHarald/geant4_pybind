#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIdirectory.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UIdirectory(py::module &m)
{
   py::class_<G4UIdirectory, G4UIcommand>(m, "G4UIdirectory")
      .def(py::init<char *, G4bool>(), py::arg("theCommandPath"), py::arg("commandsToBeBroadcasted") = true)
      .def(py::init<const char *, G4bool>(), py::arg("theCommandPath"), py::arg("commandsToBeBroadcasted") = true);
}
