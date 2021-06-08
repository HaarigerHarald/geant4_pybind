#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VisExecutive.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VisExecutive(py::module &m)
{
   py::class_<G4VisExecutive, G4VisManager>(m, "G4VisExecutive")
      .def(py::init<const G4String &>(), py::arg("verbosity") = "warnings");
}
