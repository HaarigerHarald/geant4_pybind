#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Material(py::module &);
void export_G4MaterialTable(py::module &);
void export_G4Element(py::module &);
void export_G4ElementTable(py::module &);
void export_G4Isotope(py::module &);
void export_G4NistManager(py::module &);
void export_G4AtomicShells(py::module &);

void export_modG4materials(py::module &m)
{
   export_G4Material(m);
   export_G4MaterialTable(m);
   export_G4Element(m);
   export_G4ElementTable(m);
   export_G4Isotope(m);
   export_G4NistManager(m);
   export_G4AtomicShells(m);
}
