#include <pybind11/pybind11.h>

#include <G4ASCIITree.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4ASCIITree(py::module &m)
{
   py::class_<G4ASCIITree, G4VGraphicsSystem, owntrans_ptr<G4ASCIITree>>(m, "G4ASCIITree",
                                                                         "ASCII tree visualization module")
      .def(py::init<>());
   // TOOD
}
