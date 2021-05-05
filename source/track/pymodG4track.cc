#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Track(py::module &);
void export_G4TrackStatus(py::module &);
void export_G4Step(py::module &);
void export_G4StepPoint(py::module &);
void export_G4StepStatus(py::module &);

void export_modG4track(py::module &m)
{
   export_G4Track(m);
   export_G4TrackStatus(m);
   export_G4Step(m);
   export_G4StepPoint(m);
   export_G4StepStatus(m);
}
