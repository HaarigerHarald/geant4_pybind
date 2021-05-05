#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Version.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Version(py::module &m)
{
   m.attr("G4VERSION_NUMBER") = G4VERSION_NUMBER;
   m.attr("G4Version")        = G4Version.c_str();
   m.attr("G4Date")           = G4Date.c_str();
}
