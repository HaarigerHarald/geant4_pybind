#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIcmdWith3Vector.hh>
#include <G4UImessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UIcmdWith3Vector(py::module &m)
{
   py::class_<G4UIcmdWith3Vector, G4UIcommand>(m, "G4UIcmdWith3Vector")

      .def(py::init<const char *, G4UImessenger *>(), py::arg("theCommandPath"), py::arg("theMessenger"))

      .def_static("GetNew3VectorValue", &G4UIcmdWith3Vector::GetNew3VectorValue)
      .def("SetParameterName", &G4UIcmdWith3Vector::SetParameterName, py::arg("theNameX"), py::arg("theNameY"),
           py::arg("theNameZ"), py::arg("omittable"), py::arg("currentAsDefault") = false)

      .def("SetDefaultValue", &G4UIcmdWith3Vector::SetDefaultValue);
}
