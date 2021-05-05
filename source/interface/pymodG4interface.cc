#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VUIshell(py::module &);
void export_G4UIExecutive(py::module &);

void export_modG4interface(py::module &m)
{
   export_G4VUIshell(m);
   export_G4UIExecutive(m);
}
