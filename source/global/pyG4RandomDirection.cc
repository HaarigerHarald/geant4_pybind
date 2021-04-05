#include <pybind11/pybind11.h>

#include <G4RandomDirection.hh>

#include "typecast.hh"

namespace py = pybind11;

void export_G4RandomDirection(py::module &m)
{
   m.def("G4RandomDirection", py::overload_cast<>(&G4RandomDirection));
   m.def("G4RandomDirection", py::overload_cast<double>(&G4RandomDirection));
}
