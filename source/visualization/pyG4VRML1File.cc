#include <pybind11/pybind11.h>

#include <G4VRML1File.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4VRML1File(py::module &m)
{
   py::class_<G4VRML1File, G4VGraphicsSystem, owntrans_ptr<G4VRML1File>>(m, "G4VRML1File",
                                                                         "VRML-1(file) visualization module")
      .def(py::init<>());
}
