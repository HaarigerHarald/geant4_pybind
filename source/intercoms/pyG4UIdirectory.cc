#include <pybind11/pybind11.h>

#include <G4UIdirectory.hh>

#include "typecast.hh"

namespace py = pybind11;

void export_G4UIdirectory(py::module &m)
{
   py::class_<G4UIdirectory, G4UIcommand, std::unique_ptr<G4UIdirectory>>(m, "G4UIdirectory")
      .def(py::init<char *, G4bool>(), py::arg("theCommandPath"), py::arg("commandsToBeBroadcasted") = true)
      .def(py::init<const char *, G4bool>(), py::arg("theCommandPath"), py::arg("commandsToBeBroadcasted") = true);
}
