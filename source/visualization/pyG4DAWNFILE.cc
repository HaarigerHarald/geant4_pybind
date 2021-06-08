#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DAWNFILE.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4DAWNFILE(py::module &m)
{
   py::class_<G4DAWNFILE, G4VGraphicsSystem>(m, "G4DAWNFILE", "DAWN(file) visualization module").def(py::init<>());
   // TODO
}
