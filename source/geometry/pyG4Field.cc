#include <pybind11/pybind11.h>

#include <G4Field.hh>

#include "typecast.hh"

namespace py = pybind11;

void export_G4Field(py::module &m)
{
   py::class_<G4Field, std::unique_ptr<G4Field>>(m, "G4Field", "base class of field");
}
