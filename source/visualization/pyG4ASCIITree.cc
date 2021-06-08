#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ASCIITree.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ASCIITree(py::module &m)
{
   py::class_<G4ASCIITree, G4VGraphicsSystem>(m, "G4ASCIITree", "ASCII tree visualization module").def(py::init<>());
   // TOOD
}
