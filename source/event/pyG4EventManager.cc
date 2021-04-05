#include <pybind11/pybind11.h>

#include <G4Event.hh>
#include <G4EventManager.hh>
#include <G4UserEventAction.hh>
#include <G4UserStackingAction.hh>
#include <G4UserTrackingAction.hh>
#include <G4UserSteppingAction.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4EventManager(py::module &m)
{
   py::class_<G4EventManager, std::unique_ptr<G4EventManager, py::nodelete>>(m, "G4EventManager", "event manager class")

      .def(py::init<>())
      .def_static("GetEventManager", &G4EventManager::GetEventManager, py::return_value_policy::reference)
      .def("GetConstCurrentEvent", &G4EventManager::GetConstCurrentEvent, py::return_value_policy::reference_internal)
      .def("GetNonconstCurrentEvent", &G4EventManager::GetNonconstCurrentEvent,
           py::return_value_policy::reference_internal)

      .def("AbortCurrentEvent", &G4EventManager::AbortCurrentEvent)
      .def("SetNumberOfAdditionalWaitingStacks", &G4EventManager::SetNumberOfAdditionalWaitingStacks)
      .def("GetStackManager", &G4EventManager::GetStackManager, py::return_value_policy::reference)
      .def("GetTrackingManager", &G4EventManager::GetTrackingManager, py::return_value_policy::reference)
      .def("GetVerboseLevel", &G4EventManager::GetVerboseLevel)
      .def("SetVerboseLevel", &G4EventManager::SetVerboseLevel)
      .def("SetUserInformation", &G4EventManager::SetUserInformation) // TODO pass ownership
      .def("GetUserInformation", &G4EventManager::GetUserInformation, py::return_value_policy::reference)

      .def("ProcessOneEvent", py::overload_cast<G4Event *>(&G4EventManager::ProcessOneEvent))
      .def("ProcessOneEvent", py::overload_cast<G4TrackVector *, G4Event *>(&G4EventManager::ProcessOneEvent),
           py::arg("trackVector"), py::arg("anEvent") = nullptr)

      .def("GetConstCurrentEvent", &G4EventManager::GetConstCurrentEvent, py::return_value_policy::reference_internal)
      .def("GetNonconstCurrentEvent", &G4EventManager::GetNonconstCurrentEvent,
           py::return_value_policy::reference_internal)

      .def("SetUserAction",
           [](G4EventManager &self, G4UserEventAction *action) {
              self.SetUserAction(action);
              TRAMPOLINE_REF_INCREASE(G4UserEventAction, action);
              owntrans_ptr<G4UserEventAction>::remove(action);
           })

      .def("SetUserAction",
           [](G4EventManager &self, G4UserStackingAction *action) {
              self.SetUserAction(action);
              TRAMPOLINE_REF_INCREASE(G4UserStackingAction, action);
              owntrans_ptr<G4UserStackingAction>::remove(action);
           })

      .def("SetUserAction",
           [](G4EventManager &self, G4UserTrackingAction *action) {
              self.SetUserAction(action);
              TRAMPOLINE_REF_INCREASE(G4UserTrackingAction, action);
              owntrans_ptr<G4UserTrackingAction>::remove(action);
           })

      .def("SetUserAction",
           [](G4EventManager &self, G4UserSteppingAction *action) {
              self.SetUserAction(action);
              TRAMPOLINE_REF_INCREASE(G4UserSteppingAction, action);
              owntrans_ptr<G4UserSteppingAction>::remove(action);
           })

      .def("GetUserEventAction", &G4EventManager::GetUserEventAction, py::return_value_policy::reference_internal)
      .def("GetUserStackingAction", &G4EventManager::GetUserStackingAction, py::return_value_policy::reference_internal)

      .def("GetUserTrackingAction", &G4EventManager::GetUserTrackingAction, py::return_value_policy::reference_internal)
      .def("GetUserSteppingAction", &G4EventManager::GetUserSteppingAction, py::return_value_policy::reference_internal)

      .def("SetNumberOfAdditionalWaitingStacks", &G4EventManager::SetNumberOfAdditionalWaitingStacks)

      .def("KeepTheCurrentEvent", &G4EventManager::KeepTheCurrentEvent)
      .def("GetStackManager", &G4EventManager::GetStackManager, py::return_value_policy::reference_internal)
      .def("GetTrackingManager", &G4EventManager::GetTrackingManager, py::return_value_policy::reference_internal)

      .def("GetPrimaryTransformer", &G4EventManager::GetPrimaryTransformer, py::return_value_policy::reference_internal)
      .def("SetPrimaryTransformer", &G4EventManager::SetPrimaryTransformer) // TODO pass ownership
      .def("StoreRandomNumberStatusToG4Event", &G4EventManager::StoreRandomNumberStatusToG4Event);
}
