#include <pybind11/pybind11.h>

#include <G4ExceptionSeverity.hh>

#include "typecast.hh"

namespace py = pybind11;

void export_G4ExceptionSeverity(py::module &m)
{
   py::enum_<G4ExceptionSeverity>(m, "G4ExceptionSeverity")
      .value("FatalException", FatalException)
      .value("FatalErrorInArgument", FatalErrorInArgument)
      .value("RunMustBeAborted", RunMustBeAborted)
      .value("EventMustBeAborted", EventMustBeAborted)
      .value("JustWarning", JustWarning)
      .export_values();
}
