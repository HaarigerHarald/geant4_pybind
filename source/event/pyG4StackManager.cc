#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4StackManager.hh>
#include <G4VTrajectory.hh>
#include <G4Track.hh>
#include <G4ClassificationOfNewTrack.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4StackManager(py::module &m)
{
   py::class_<G4StackManager>(m, "G4StackManager")

      .def("__copy__", [](const G4StackManager &self) { return new G4StackManager(self); })
      .def("__deepcopy__", [](const G4StackManager &self, py::dict) { return new G4StackManager(self); })
      .def(py::init<>())
      .def("ClearPostponeStack", &G4StackManager::ClearPostponeStack)
      .def("ClearUrgentStack", &G4StackManager::ClearUrgentStack)
      .def("ClearWaitingStack", &G4StackManager::ClearWaitingStack, py::arg("i") = 0)
      .def("GetNPostponedTrack", &G4StackManager::GetNPostponedTrack)
      .def("GetNTotalTrack", &G4StackManager::GetNTotalTrack)
      .def("GetNUrgentTrack", &G4StackManager::GetNUrgentTrack)
      .def("GetNWaitingTrack", &G4StackManager::GetNWaitingTrack, py::arg("i") = 0)
      //.def("PopNextTrack", &G4StackManager::PopNextTrack, py::arg("newTrajectory"),
      // py::return_value_policy::reference)
      .def("PrepareNewEvent", &G4StackManager::PrepareNewEvent)
      .def("PushOneTrack", &G4StackManager::PushOneTrack, py::arg("newTrack"),
           py::arg("newTrajectory") = static_cast<G4VTrajectory *>(nullptr))

      .def("ReClassify", &G4StackManager::ReClassify)
      .def("SetNumberOfAdditionalWaitingStacks", &G4StackManager::SetNumberOfAdditionalWaitingStacks, py::arg("iAdd"))
      .def(
         "SetUserStackingAction",
         [](G4StackManager &self, py::disown_ptr<G4UserStackingAction> value) { self.SetUserStackingAction(value); },
         py::arg("value"))

      .def("SetVerboseLevel", &G4StackManager::SetVerboseLevel, py::arg("value"))
      .def("TransferOneStackedTrack", &G4StackManager::TransferOneStackedTrack, py::arg("origin"),
           py::arg("destination"))

      .def("TransferStackedTracks", &G4StackManager::TransferStackedTracks, py::arg("origin"), py::arg("destination"))
      .def("clear", &G4StackManager::clear);
}
