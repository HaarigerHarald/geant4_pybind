#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VRML2File.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VRML2File(py::module &m)
{
   py::class_<G4VRML2File, G4VGraphicsSystem>(m, "G4VRML2File", "VRML-2(file) visualization module").def(py::init<>());
}
