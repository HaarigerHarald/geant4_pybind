#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Event.hh>
#include <G4EventManager.hh>
#include <G4UserEventAction.hh>
#include <G4UserStackingAction.hh>
#include <G4UserTrackingAction.hh>
#include <G4UserSteppingAction.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4EventManager(py::module &m)
{
   py::class_<G4EventManager, py::nodelete>(m, "G4EventManager", "event manager class")

      .def(py::init<>())
      .def(py::init<>())
      .def("AbortCurrentEvent", &G4EventManager::AbortCurrentEvent)
      .def("GetConstCurrentEvent", &G4EventManager::GetConstCurrentEvent, py::return_value_policy::reference)
      .def_static("GetEventManager", &G4EventManager::GetEventManager, py::return_value_policy::reference)
      .def("GetNonconstCurrentEvent", &G4EventManager::GetNonconstCurrentEvent, py::return_value_policy::reference)
      .def("GetPrimaryTransformer", &G4EventManager::GetPrimaryTransformer, py::return_value_policy::reference)
      .def("GetStackManager", &G4EventManager::GetStackManager, py::return_value_policy::reference)
      .def("GetTrackingManager", &G4EventManager::GetTrackingManager, py::return_value_policy::reference)
      .def("GetUserEventAction", &G4EventManager::GetUserEventAction, py::return_value_policy::reference)
      .def("GetUserInformation", &G4EventManager::GetUserInformation, py::return_value_policy::reference)
      .def("GetUserStackingAction", &G4EventManager::GetUserStackingAction, py::return_value_policy::reference)
      .def("GetUserSteppingAction", &G4EventManager::GetUserSteppingAction, py::return_value_policy::reference)
      .def("GetUserTrackingAction", &G4EventManager::GetUserTrackingAction, py::return_value_policy::reference)
      .def("GetVerboseLevel", &G4EventManager::GetVerboseLevel)
      .def("KeepTheCurrentEvent", &G4EventManager::KeepTheCurrentEvent)
      .def("ProcessOneEvent", py::overload_cast<G4Event *>(&G4EventManager::ProcessOneEvent), py::arg("anEvent"))
      .def("ProcessOneEvent", py::overload_cast<G4TrackVector *, G4Event *>(&G4EventManager::ProcessOneEvent),
           py::arg("trackVector"), py::arg("anEvent") = static_cast<G4Event *>(nullptr))

      .def("SetNumberOfAdditionalWaitingStacks", &G4EventManager::SetNumberOfAdditionalWaitingStacks, py::arg("iAdd"))
      .def(
         "SetPrimaryTransformer",
         [](G4EventManager &self, py::disown_ptr<G4PrimaryTransformer> tf) { self.SetPrimaryTransformer(tf); },
         py::arg("tf"))

      .def("SetUserAction",
           [](G4EventManager &self, py::disown_ptr<G4UserEventAction> action) { self.SetUserAction(action); })

      .def("SetUserAction",
           [](G4EventManager &self, py::disown_ptr<G4UserStackingAction> action) { self.SetUserAction(action); })

      .def("SetUserAction",
           [](G4EventManager &self, py::disown_ptr<G4UserTrackingAction> action) { self.SetUserAction(action); })

      .def("SetUserAction",
           [](G4EventManager &self, py::disown_ptr<G4UserSteppingAction> action) { self.SetUserAction(action); })

      .def(
         "SetUserInformation",
         [](G4EventManager &self, py::disown_ptr<G4VUserEventInformation> anInfo) { self.SetUserInformation(anInfo); },
         py::arg("anInfo"))

      .def("SetVerboseLevel", &G4EventManager::SetVerboseLevel, py::arg("value"))
      .def("StackTracks", &G4EventManager::StackTracks, py::arg("trackVector"), py::arg("IDhasAlreadySet") = false)
      .def("StoreRandomNumberStatusToG4Event", &G4EventManager::StoreRandomNumberStatusToG4Event, py::arg("vl"));
}
