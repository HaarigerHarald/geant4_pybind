#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4MaterialPropertyVector(py::module &m)
{
   m.attr("G4MaterialPropertyVector") = m.attr("G4PhysicsFreeVector");
}