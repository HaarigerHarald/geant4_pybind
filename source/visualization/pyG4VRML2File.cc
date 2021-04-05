#include <pybind11/pybind11.h>

#include <G4VRML2File.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4VRML2File(py::module &m)
{
   py::class_<G4VRML2File, G4VGraphicsSystem, owntrans_ptr<G4VRML2File>>(m, "G4VRML2File",
                                                                         "VRML-2(file) visualization module")
      .def(py::init<>());
}
