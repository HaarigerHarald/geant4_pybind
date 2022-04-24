#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SmartTrackStack.hh>
#include <G4VTrajectory.hh>
#include <G4Track.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SmartTrackStack(py::module &m)
{
   py::class_<G4SmartTrackStack>(m, "G4SmartTrackStack")

      .def("__copy__", [](const G4SmartTrackStack &self) { return new G4SmartTrackStack(self); })
      .def("__deepcopy__", [](const G4SmartTrackStack &self, py::dict) { return new G4SmartTrackStack(self); })
      .def(py::init<>())
      .def("GetMaxNTrack", &G4SmartTrackStack::GetMaxNTrack)
      .def("GetNTrack", &G4SmartTrackStack::GetNTrack)
      .def("PopFromStack", &G4SmartTrackStack::PopFromStack)
      .def("PushToStack", &G4SmartTrackStack::PushToStack, py::arg("aStackedTrack"))
      .def("TransferTo", &G4SmartTrackStack::TransferTo, py::arg("aStack"))
      .def("clear", &G4SmartTrackStack::clear)
      .def("clearAndDestroy", &G4SmartTrackStack::clearAndDestroy)
      .def("dumpStatistics", &G4SmartTrackStack::dumpStatistics);
      //.def("getEnergyOfStack", &G4SmartTrackStack::getEnergyOfStack, py::arg("aTrackStack"));
}
