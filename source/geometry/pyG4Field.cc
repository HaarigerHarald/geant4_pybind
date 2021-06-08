#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Field.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Field(py::module &m)
{
   py::class_<G4Field>(m, "G4Field", "base class of field");
}
