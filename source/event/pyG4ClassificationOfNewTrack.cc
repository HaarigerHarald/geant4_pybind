#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ClassificationOfNewTrack.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ClassificationOfNewTrack(py::module &m)
{
   py::enum_<G4ClassificationOfNewTrack>(m, "G4ClassificationOfNewTrack")
      .value("fUrgent", fUrgent)
      .value("fWaiting", fWaiting)
      .value("fPostpone", fPostpone)
      .value("fKill", fKill)
      .value("fWaiting_1", fWaiting_1)
      .value("fWaiting_2", fWaiting_2)
      .value("fWaiting_3", fWaiting_3)
      .value("fWaiting_4", fWaiting_4)
      .value("fWaiting_5", fWaiting_5)
      .value("fWaiting_6", fWaiting_6)
      .value("fWaiting_7", fWaiting_7)
      .value("fWaiting_8", fWaiting_8)
      .value("fWaiting_9", fWaiting_9)
      .value("fWaiting_10", fWaiting_10)
      .export_values();
}
