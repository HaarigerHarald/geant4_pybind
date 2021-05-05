#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VProcess(py::module &);
void export_G4ProcVector(py::module &);
void export_G4ProcessType(py::module &);
void export_G4EmCalculator(py::module &);
void export_G4ProductionCutsTable(py::module &);
void export_G4VCrossSectionHandler(py::module &);
void export_G4CrossSectionHandler(py::module &);
void export_G4ProcessTable(py::module &);
void export_G4ProcessManager(py::module &);

void export_modG4processes(py::module &m)
{
   export_G4VProcess(m);
   export_G4ProcessType(m);
   export_G4ProcVector(m);
   export_G4EmCalculator(m);
   export_G4ProductionCutsTable(m);
   export_G4VCrossSectionHandler(m);
   export_G4CrossSectionHandler(m);
   export_G4ProcessTable(m);
   export_G4ProcessManager(m);
}
