#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4HepRep.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4HepRep(py::module &m)
{
   py::class_<G4HepRep, G4VGraphicsSystem>(m, "G4HepRep", "HepRep visualization module").def(py::init<>());
}
