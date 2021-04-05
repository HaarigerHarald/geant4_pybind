#include <pybind11/pybind11.h>

#include "typecast.hh"

namespace py = pybind11;

void export_G4VisAttributes(py::module &);
void export_G4TypeKey(py::module &);
void export_G4AttValue(py::module &);
void export_G4AttDef(py::module &);
void export_G4Colour(py::module &);
void export_G4VMarker(py::module &);
void export_G4Circle(py::module &);
void export_G4VVisManager(py::module &);

void export_modG4graphics_reps(py::module &m)
{
   export_G4VisAttributes(m);
   export_G4TypeKey(m);
   export_G4AttValue(m);
   export_G4AttDef(m);
   export_G4Colour(m);
   export_G4VMarker(m);
   export_G4Circle(m);
   export_G4VVisManager(m);
}
