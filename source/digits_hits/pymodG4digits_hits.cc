#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VSensitiveDetector(py::module &);
void export_G4VHit(py::module &);
void export_G4SDManager(py::module &);
void export_G4VHitsCollection(py::module &);
void export_G4HCofThisEvent(py::module &);
void export_G4MultiFunctionalDetector(py::module &);
void export_G4VSDFilter(py::module &);
void export_G4SDFilter(py::module &);
void export_G4VPrimitiveScorer(py::module &);
void export_G4VPrimitivePlotter(py::module &);
void export_G4Scorer(py::module &);

void export_modG4digit_hits(py::module &m)
{
   export_G4VSensitiveDetector(m);
   export_G4VHit(m);
   export_G4SDManager(m);
   export_G4VHitsCollection(m);
   export_G4HCofThisEvent(m);
   export_G4MultiFunctionalDetector(m);
   export_G4VSDFilter(m);
   export_G4SDFilter(m);
   export_G4VPrimitiveScorer(m);
   export_G4VPrimitivePlotter(m);
   export_G4Scorer(m);
}
