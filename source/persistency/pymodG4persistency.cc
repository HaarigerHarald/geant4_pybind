#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#ifdef G4_HAS_GDML
void export_G4GDMLParser(py::module &);
#endif

void export_modG4persistency(py::module &m)
{
#ifdef G4_HAS_GDML
   export_G4GDMLParser(m);
#endif
}
