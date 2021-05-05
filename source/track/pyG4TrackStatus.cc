#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TrackStatus.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TrackStatus(py::module &m)
{
   py::enum_<G4TrackStatus>(m, "G4TrackStatus")
      .value("fAlive", fAlive)
      .value("fStopButAlive", fStopButAlive)
      .value("fStopAndKill", fStopAndKill)
      .value("fKillTrackAndSecondaries", fKillTrackAndSecondaries)
      .value("fSuspend", fSuspend)
      .value("fPostponeToNextEvent", fPostponeToNextEvent)
      .export_values();
}
