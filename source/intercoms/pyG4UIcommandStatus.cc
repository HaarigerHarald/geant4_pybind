#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIcommandStatus.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UIcommandStatus(py::module &m)
{
   py::enum_<G4UIcommandStatus>(m, "G4UIcommandStatus")
      .value("fCommandSucceeded", fCommandSucceeded)
      .value("fCommandNotFound", fCommandNotFound)
      .value("fIllegalApplicationState", fIllegalApplicationState)
      .value("fParameterOutOfRange", fParameterOutOfRange)
      .value("fParameterUnreadable", fParameterUnreadable)
      .value("fParameterOutOfCandidates", fParameterOutOfCandidates)
      .value("fAliasNotFound", fAliasNotFound)
      .export_values();
}
