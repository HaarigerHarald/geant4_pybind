#include <pybind11/pybind11.h>

#include "typecast.hh"

namespace py = pybind11;

void export_G4VAnalysisManager(py::module &);
void export_G4TScoreNtupleWriter(py::module &);

void export_modG4analysis(py::module &m)
{
   export_G4VAnalysisManager(m);
   export_G4TScoreNtupleWriter(m);
}
