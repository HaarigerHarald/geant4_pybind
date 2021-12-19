#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_histo(py::module &);
void export_G4VAnalysisManager(py::module &);
void export_G4AnalysisManager(py::module &);
void export_G4TScoreNtupleWriter(py::module &);
void export_G4MergeMode(py::module &m);
void export_G4VAccumulable(py::module &m);
void export_G4Accumulable(py::module &m);
void export_G4AccumulableManager(py::module &m);

void export_modG4analysis(py::module &m)
{
   export_histo(m);
   export_G4VAnalysisManager(m);
   export_G4AnalysisManager(m);
   export_G4TScoreNtupleWriter(m);
   export_G4MergeMode(m);
   export_G4VAccumulable(m);
   export_G4Accumulable(m);
   export_G4AccumulableManager(m);
}
