#include <pybind11/pybind11.h>

#include <G4DAWNFILE.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4DAWNFILE(py::module &m)
{
   py::class_<G4DAWNFILE, G4VGraphicsSystem, owntrans_ptr<G4DAWNFILE>>(m, "G4DAWNFILE",
                                                                       "DAWN(file) visualization module")
      .def(py::init<>());
   // TODO
}
