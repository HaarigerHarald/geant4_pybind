#include <pybind11/pybind11.h>

#include <G4StepStatus.hh>

#include "typecast.hh"

namespace py = pybind11;

void export_G4StepStatus(py::module &m)
{
   py::enum_<G4StepStatus>(m, "G4StepStatus")
      .value("fWorldBoundary", fWorldBoundary)
      .value("fGeomBoundary", fGeomBoundary)
      .value("fAtRestDoItProc", fAtRestDoItProc)
      .value("fAlongStepDoItProc", fAlongStepDoItProc)
      .value("fPostStepDoItProc", fPostStepDoItProc)
      .value("fUserDefinedLimit", fUserDefinedLimit)
      .value("fExclusivelyForcedProc", fExclusivelyForcedProc)
      .value("fUndefined", fUndefined)
      .export_values();
}
